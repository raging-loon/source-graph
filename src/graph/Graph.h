#ifndef SG_GRAPH_GRAPH_H_
#define SG_GRAPH_GRAPH_H_

#include <unordered_map>
#include <vector>
#include <cctype>
#include <optional>
namespace source_graph
{

using uint = unsigned int;
using VertexList = std::vector<uint>;

class Graph
{
public:

    Graph();
    ~Graph();

    void addVertex(uint f, uint t);
    
    bool hasEdges(uint vertex);

    std::optional<
        const VertexList>
        getVertices(uint vertex);

private:

    std::unordered_map<
        unsigned int,
        VertexList
    > m_adjacencyMap;

};

} // source_graph

#endif // SG_GRAPH_GRAPH_H_