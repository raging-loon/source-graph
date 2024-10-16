#include "graph/Graph.h"

using source_graph::Graph;
using source_graph::uint;
using source_graph::VertexList;

Graph::Graph()
    : m_adjacencyMap{}
{
}

Graph::~Graph()
{
}

void Graph::addVertex(uint f, uint t)
{
    auto place = m_adjacencyMap.find(f);
    if (place != m_adjacencyMap.end())
        place->second.push_back(t);
    else
    {
        m_adjacencyMap[f].push_back(t);
    }
}

bool Graph::hasEdges(uint vertex)
{
    return (m_adjacencyMap.find(vertex) != m_adjacencyMap.end());
}

std::optional<const VertexList> Graph::getVertices(uint vertex)
{
    auto place = m_adjacencyMap.find(vertex);
    if(place == m_adjacencyMap.end())
        return std::nullopt;
    return place->second;
}
