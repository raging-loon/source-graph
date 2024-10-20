#ifndef SG_ANALYZER_INCLUDE_ANALYZER_H_
#define SG_ANALYZER_INCLUDE_ANALYZER_H_

#include "graph/Graph.h"
#include "parser/FileList.h"
#include "graph/IncludeGraph.h"
#include <atomic>
namespace source_graph
{

class IncludeAnalyzer
{
public:

    IncludeAnalyzer(FileList& list, IncludeGraph& graph)
        : m_outList(list), m_outGraph(graph),
          m_numFilesAnalyzed(0), m_linesCounted(0),
          m_locCounted(0),
          m_pdepFound(0)
    {}
    
    int analyze();
    
    inline int getNumFilesAnalyzed() const { return m_numFilesAnalyzed; }
    inline int getLinesCounted() const { return m_linesCounted; }

private:

    int mtAnalyze(int startIdx, int endIdx, const FileList& copy);

    FileList& m_outList;
    IncludeGraph& m_outGraph;
    std::atomic<int> m_numFilesAnalyzed;
    std::atomic<int> m_linesCounted;
    std::atomic<int> m_locCounted;
    std::atomic<int> m_pdepFound;
    std::atomic<int> m_systemHeadersFound;
};

} // source_graph

#endif // SG_ANALYZER_INCLUDE_ANALYZER_H_