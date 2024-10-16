#ifndef SG_GRAPH_INCLUDE_GRAPH_H_
#define SG_GRAPH_INCLUDE_GRAPH_H_

#include "graph/Graph.h"
#include <optional>

namespace source_graph
{
    
class IncludeGraph
{
public:
    IncludeGraph() 
        : m_fwdIncGraph{}, m_revIncGraph{} {}

    void addInclude(uint fidx1, uint fidx2);
    
    std::optional<
        const VertexList
    > getFilesIncludedBy(int fidx);

    std::optional<
        const VertexList
    > getFilesThatInclude(int fidx);

private:
    Graph m_fwdIncGraph;
    Graph m_revIncGraph;
};

} // source_graph


#endif //SG_GRAPH_INCLUDE_GRAPH_H_