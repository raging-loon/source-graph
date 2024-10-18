#ifndef SG_OUTPUT_TERMINAL_TERMINAL_OUTPUT_H_
#define SG_OUTPUT_TERMINAL_TERMINAL_OUTPUT_H_

#include "parser/FileList.h"
#include "graph/IncludeGraph.h"

namespace source_graph
{


class TerminalOuput
{
public:

    static void dumpForwardIncludes(FileList& files, FileList& sources, IncludeGraph& graph);
    static void dumpReverseIncludes(FileList& files, FileList& sources, IncludeGraph& graph);

};


} // source_graph

#endif // SG_OUTPUT_TERMINAL_TERMINAL_OUTPUT_H_