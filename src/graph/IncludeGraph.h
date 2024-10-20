#ifndef SG_GRAPH_INCLUDE_GRAPH_H_
#define SG_GRAPH_INCLUDE_GRAPH_H_

#include "graph/Graph.h"
#include <optional>
#include <mutex>

namespace source_graph
{
    
///
/// @brief
///     Holds two graphs, one for includes and reverse includes     
/// 
class IncludeGraph
{
public:

    IncludeGraph() 
        : m_fwdIncGraph{}, m_revIncGraph{}, m_mtx{} {}

    ///
    /// @brief 
    ///     Add include indices to both forward and reverse graphs
    /// 
    void addInclude(uint fidx1, uint fidx2);
    
    ///
    /// @brief 
    ///     Get vertex list from forward graph
    /// 
    /// @return
    ///     std::nullopt on fail
    ///
    std::optional<const VertexList> getFilesIncludedBy(int fidx) const;


    ///
    /// @brief 
    ///     Get vertex list from reverse graph
    /// 
    /// @return
    ///     std::nullopt on fail
    ///
    std::optional<const VertexList> getFilesThatInclude(int fidx) const;

private:
    /// What a file includes
    Graph m_fwdIncGraph;

    /// What includes a file
    Graph m_revIncGraph;

    std::mutex m_mtx;
};

} // source_graph


#endif //SG_GRAPH_INCLUDE_GRAPH_H_