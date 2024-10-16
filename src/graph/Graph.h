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

///
/// @brief
///     Directed Graph using an adjacency list
/// 
class Graph
{
public:

    Graph();
    ~Graph();

    ///
    /// @brief
    ///     Add/update vertex list at F
    /// 
    void addVertex(uint f, uint t);
    
    ///
    /// @brief
    ///     Check if "vertex" is a node
    /// 
    bool hasEdges(uint vertex);


    ///
    /// @brief
    ///     Get vertex list for vertex.
    /// 
    /// @return
    ///     std::nullopt on failure
    /// 
    std::optional<const VertexList> getVertices(uint vertex);

private:

    std::unordered_map<
        unsigned int,
        VertexList
    > m_adjacencyMap;

};

} // source_graph

#endif // SG_GRAPH_GRAPH_H_