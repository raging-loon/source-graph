#ifndef SG_CLI_TERMINAL_INTERFACE_H_
#define SG_CLI_TERMINAL_INTERFACE_H_

#include <string>
#include "parser/FileList.h"
#include "graph/IncludeGraph.h"

namespace source_graph
{

class TerminalInterface
{

public:

    TerminalInterface(int argc, char** argv)
        : m_argc(argc), m_argv(argv), m_oldcwd(std::filesystem::current_path())
    {

    }
    ~TerminalInterface()
    {
        std::filesystem::current_path(m_oldcwd);
    }

    bool parse();

    bool validate();

    bool run();

private:

    bool parseArgs();

    // copies provided from main function
    int m_argc;
    char** m_argv;

    FileList m_fileList;
    IncludeGraph m_igraph;
    path m_oldcwd;
};


} // source_graph

#endif // SG_CLI_TERMINAL_INTERFACE_H_