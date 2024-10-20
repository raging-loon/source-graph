#include "graph/IncludeGraph.h"
#include <thread>
using source_graph::IncludeGraph;
using source_graph::VertexList;

void IncludeGraph::addInclude(uint fidx1, uint fidx2)
{
    std::lock_guard lock(m_mtx);
    m_fwdIncGraph.addVertex(fidx1, fidx2);
    m_revIncGraph.addVertex(fidx2, fidx1);
}

std::optional<
    const VertexList
> IncludeGraph::getFilesIncludedBy(int fidx) const
{
    return m_fwdIncGraph.getVertices(fidx);
}

std::optional<
    const VertexList
> IncludeGraph::getFilesThatInclude(int fidx) const
{
    return m_revIncGraph.getVertices(fidx);

}