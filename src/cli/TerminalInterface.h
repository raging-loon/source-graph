#ifndef SG_CLI_TERMINAL_INTERFACE_H_
#define SG_CLI_TERMINAL_INTERFACE_H_

#include <string>
#include "parser/FileList.h"
#include "graph/IncludeGraph.h"
namespace source_graph
{

constexpr unsigned int ANALYZER_FORWARD     = 1 << 1;
constexpr unsigned int ANALYZER_REVERSE     = 1 << 2;
constexpr unsigned int ANALYZER_CIRCLE      = 1 << 3;
constexpr unsigned int ANALYZER_ICIRCLE     = 1 << 4;
constexpr unsigned int ANALYZER_TRANSIENT   = 1 << 5;

///
/// @brief
///     Mangages the application, parses arguments, and runs analyzers
/// 
class TerminalInterface
{

public:

    TerminalInterface(int argc, char** argv)
        : m_argc(argc), m_argv(argv), m_oldcwd(std::filesystem::current_path()),
          m_analyzers(0)
    {

    }
    ~TerminalInterface()
    {
        std::filesystem::current_path(m_oldcwd);
    }

    /// parse cmd args
    bool parse();
    
    /// run analyzers
    bool run();

private:

    /// int. parse args
    bool parseArgs();
    
    /// parse an possible analyzer i.e -a <arg>
    bool parseAnalyzerArg(const char* arg);

    /// parse a list of target files i.e -f <arg>
    bool parseTargetFiles(const char* arg);

    bool runAnalyzer();


    // copies provided from main function
    int m_argc;
    char** m_argv;

    /// list of initial sources
    FileList m_sourceList;
    
    /// list of target files
    FileList m_fileList;

    /// our include graph, built from m_sourceList
    IncludeGraph m_igraph;
    
    /// old path to CD back to
    path m_oldcwd;

    /// analyzer to run
    unsigned int m_analyzers;
};


} // source_graph

#endif // SG_CLI_TERMINAL_INTERFACE_H_