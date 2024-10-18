#include "TerminalInterface.h"
#include <cstdio>
#include <cstring>

#include <filesystem>

#include "graph/IncludeGraph.h"
#include "analyzer/IncludeAnalyzer.h"


using source_graph::TerminalInterface;

static constexpr bool hasArg(char** argv, int idx, int totalLen)
{
    return (idx + 1 < totalLen && argv[idx + 1][0] != '-');
}

static inline void printArgRequirment(const char* arg)
{
    printf("%s requires an argument\n", arg);
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
        " -a <analyzer>             Analyzer to run\n"
        " Supported Analyzers:\n"
        "  forward                  List Files include by <files> above\n"
        "  reverse                  List Files that include any of the <files> above\n"
        "  circle                   Circular Inclusion Detection\n"
        "  icircle                  Indirect Inclusion Detection\n"
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

bool TerminalInterface::validate()
{
    return false;
}

bool TerminalInterface::run()
{
    IncludeGraph sg;
    IncludeAnalyzer ia(m_fileList, sg);
    ia.analyze();

    return false;
}

bool TerminalInterface::parseArgs()
{
    for (int i = 1; i < m_argc; i++)
    {
        if (strcmp(m_argv[i], "-d") == 0)
        {
            CHECK_ARG("-d", m_argv, i, m_argc);

            if(!std::filesystem::exists(m_argv[i+1])) 
            {
                printf("%s not not found!\n", m_argv[i+1]);
                return false;
            }
            std::filesystem::current_path(m_argv[i + 1]);
            m_fileList.addDirectory(std::filesystem::current_path());
        }
        
    }
    return true;
}
