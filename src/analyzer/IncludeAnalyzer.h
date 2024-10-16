#ifndef SG_ANALYZER_INCLUDE_ANALYZER_H_
#define SG_ANALYZER_INCLUDE_ANALYZER_H_

#include "graph/Graph.h"
#include "parser/FileList.h"
#include "graph/IncludeGraph.h"


namespace source_graph
{

class IncludeAnalyzer
{
public:

    IncludeAnalyzer(FileList& list, IncludeGraph& graph)
        : m_outList(list), m_outGraph(graph) {}
    
    int analyze();
    

private:

    FileList& m_outList;
    IncludeGraph& m_outGraph;
    
};

} // source_graph

#endif // SG_ANALYZER_INCLUDE_ANALYZER_H_