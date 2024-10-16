#include "graph/IncludeGraph.h"
using source_graph::IncludeGraph;
using source_graph::VertexList;

void IncludeGraph::addInclude(uint fidx1, uint fidx2)
{
    m_fwdIncGraph.addVertex(fidx1, fidx2);
    m_revIncGraph.addVertex(fidx2, fidx1);
}

std::optional<
    const VertexList
> IncludeGraph::getFilesIncludedBy(int fidx)
{
    return m_fwdIncGraph.getVertices(fidx);
}

std::optional<
    const VertexList
> IncludeGraph::getFilesThatInclude(int fidx)
{
    return m_revIncGraph.getVertices(fidx);

}