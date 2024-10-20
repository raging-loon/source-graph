#include "TerminalInterface.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <cassert>
#include "graph/IncludeGraph.h"
#include "analyzer/IncludeAnalyzer.h"
#include <chrono>
#include "utils.h"

#include "output/TerminalStrategy.h"
#include "output/DotStrategy.h"
#include "analyzer/CircularInclusionAnalyzer.h"

using source_graph::TerminalInterface;
using namespace std::chrono;
using namespace std::filesystem;

static constexpr bool hasArg(char** argv, int idx, int totalLen)
{
    return (idx + 1 < totalLen && argv[idx + 1][0] != '-');
}

static inline void printArgRequirment(const char* arg)
{
    printf("%s requires an argument\n", arg);
}

constexpr bool hasFlag(unsigned int value, unsigned int flag)
{
    return (value & flag) == flag;
}


#define CHECK_ARG(arg, argv, idx, totalLen) \
{\
    if (!hasArg(argv, idx, totalLen))\
    {\
        printArgRequirment(arg);\
        return false;\
    }\
}



static void printHelp()
{
    printf(
        "Source Graph - Physical Depdency Analyzer v0.1\n"
        "Usage: ./source-graph <dir> <options>\n"
        "OPTIONS\n"
        " -d <dir>                  Source Code Directory\n"
        " -e, --ext <e1,e2,...,eN>  File extensions to scan, default: cpp,c,h,hpp\n"
        "ANALYSIS OPTIONS\n"
        " -f <files>                Target Files to analyze\n"
        "                           These should be relative to <dir>\n"
        " -o, --output <type>       Output Type\n"
        " Supported Output\n"
        "  stdout (default)         Print to screen\n"
        "  dot                      Output to graphviz-compat. DOT lang. file\n"
        "                           Analyzers below that support DOT are marked with a '*'\n"
        " -a <analyzer>             Analyzer to run\n"
        " Supported Analyzers:\n"
        "  *forward                 List Files include by <files> above\n"
        "  *reverse                 List Files that include any of the <files> above\n"
        "  *circle                  Circular Inclusion Detection\n"
        "  *icircle                 Indirect Inclusion Detection\n"
        "  bacon-num | transient    Same as above, but simply prints a number\n"
    );


}

bool TerminalInterface::parse()
{
    if (m_argc == 1)
    {
        printHelp();
        return false;
    }

    return parseArgs();
}


bool TerminalInterface::run()
{
    if (m_sourceList.getNumFiles() == 0 || m_analyzers == 0)
    {
        std::cerr << "Need at least one directory and one analyzer.\n";
        return false;
    }
    IncludeAnalyzer ia(m_sourceList, m_igraph);
    time_point<steady_clock> start{ steady_clock::now() };
    if (ia.analyze() != 0)
    {
        std::cerr << "Failed to analyze!\n";
        return false;
    }
    auto time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    std::cerr << "Analyzed " << ia.getNumFilesAnalyzed() 
              << " files ("<<ia.getLinesCounted()<<" lines) in "
              <<time/1000.0f<<"s\n";

    return runAnalyzer();
}







bool TerminalInterface::parseArgs()
{
    for (int i = 1; i < m_argc; i++)
    {
        if (strcmp(m_argv[i], "-d") == 0)
        {
            CHECK_ARG("-d", m_argv, i, m_argc);
            if(!std::filesystem::exists(m_argv[i + 1]))
            {
                printf("%s not not found!\n", m_argv[i + 1]);
                return false;
            }
            std::filesystem::current_path(m_argv[i+1]);
            m_sourceList.addDirectory(std::filesystem::current_path());
        }
        
        else if (strcmp(m_argv[i], "-a") == 0)
        {
            CHECK_ARG("-a", m_argv, i, m_argc);
            if (!parseAnalyzerArg(m_argv[i+1]))
                return false;
        }
        else if (strcmp(m_argv[i], "-f") == 0)
        {
            CHECK_ARG("-f", m_argv, i, m_argc);
            if (!parseTargetFiles(m_argv[i+1]))
                return false;
        }

        else if (strcmp(m_argv[i], "-o") == 0)
        {
            CHECK_ARG("-o", m_argv, i, m_argc);
            if (!parseOutputType(m_argv[i + 1]))
                return false;
        }

    }

    if (m_output == nullptr)
        m_output = std::make_shared<TerminalStrategy>();
    return true;
}

bool TerminalInterface::parseAnalyzerArg(const char* arg)
{
    if (strcmp(arg, "forward") == 0)
        m_analyzers |= ANALYZER_FORWARD;
    else if (strcmp(arg, "reverse") == 0)
        m_analyzers |= ANALYZER_REVERSE;
    else if (strcmp(arg, "circle") == 0)
        m_analyzers |= ANALYZER_CIRCLE;
    else if (strcmp(arg, "icircle") == 0)
        m_analyzers |= ANALYZER_ICIRCLE;
    else if (strcmp(arg, "transient") == 0 || strcmp(arg, "bacon-num") == 0)
        m_analyzers |= ANALYZER_TRANSIENT;
    else
    {
        std::cerr << "Unknown analyzer \"" << arg << "\". "
                  << "Supported analyzers are: forward, reverse, circle, icircle, and transient.\n";
        return false;
    }

    return true;
}

bool TerminalInterface::parseTargetFiles(const char* arg)
{
    assert(arg);

    auto list = split(arg, ',');

    if (list.empty())
        return false;

    for (auto& i : list)
    {
        if (!exists(i))
        {
            std::cerr << i << " does not exist!\n";
            return false;
        }
        m_fileList.addFile(i);
    }

    return true;
}

bool source_graph::TerminalInterface::parseOutputType(const char* arg)
{
    if (strcmp(arg, "stdout") == 0)
        m_output = std::make_shared<TerminalStrategy>();
    else if(strcmp(arg, "dot") == 0 || strcmp(arg, "graphviz") == 0)
        m_output = std::make_shared<DotStrategy>();
    else
    {
        std::cerr << "Unknown output type \"" << arg << "\". Valid options are 'stdout','dot', or 'graphviz'.\n";
        return false;
    }

    return true;
}

// TODO: Figure out how to elimnate code dup. with fwd/rev analyzer
bool TerminalInterface::runAnalyzer()
{
    if (hasFlag(m_analyzers, ANALYZER_FORWARD))
    {
        if (m_fileList.getNumFiles() == 0)
        {
            m_output->writeForwardIncludes(
                m_sourceList,
                m_sourceList.getIndexList(),
                m_igraph
            );

        }
        else
        {
            m_output->writeForwardIncludes(
                m_sourceList,
                m_sourceList.getIndexListFromNames(m_fileList.getFileList()),
                m_igraph
            );
        }
    }

    if (hasFlag(m_analyzers, ANALYZER_REVERSE))
    {
        if (m_fileList.getNumFiles() == 0)
        {
            m_output->writeReverseIncludes(
                m_sourceList,
                m_sourceList.getIndexList(),
                m_igraph
            );

        }
        else
        {
            m_output->writeReverseIncludes(
                m_sourceList,
                m_sourceList.getIndexListFromNames(m_fileList.getFileList()),
                m_igraph
            );
        }
    }

    if (hasFlag(m_analyzers, ANALYZER_ICIRCLE) || hasFlag(m_analyzers, ANALYZER_TRANSIENT))
    {
        if (m_fileList.getNumFiles() != 2)
        {
            std::cerr << "icircle analysis requires exactly two files.\n";
            return false;
        }
        CircularInclusionAnalyzer cia(m_sourceList, m_igraph);
        FileIndexList ilist = m_sourceList.getIndexListFromNames(m_fileList.getFileList());
        auto indexlist = cia.findIndirectCircularIncludes(ilist.front(), ilist.back(), 0);

        if (hasFlag(m_analyzers, ANALYZER_TRANSIENT))
            printf("%zd\n",indexlist.size());
        else
        {
            m_output->writeTransitiveInclude(
                m_sourceList,
                indexlist
            );
        }
    }

    return true;

}
