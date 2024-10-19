#ifndef SG_ANALYZER_CIRCULAR_INCLUSION_ANALYZER_H_
#define SG_ANALYZER_CIRCULAR_INCLUSION_ANALYZER_H_

#include "parser/FileList.h"
#include "graph/IncludeGraph.h"

namespace source_graph
{

class CircularInclusionAnalyzer
{
public:
    CircularInclusionAnalyzer(FileList& sources, IncludeGraph& graph)
        : m_igraph(graph), m_sources(sources)
    {}

    bool hasCircularIncludes(int file1, int file2);
    std::vector<int> findIndirectCircularIncludes(int file1, int file2, int depth);

private:
    IncludeGraph& m_igraph;
    FileList& m_sources;



};

} // source_graph

#endif // SG_ANALYZER_CIRCULAR_INCLUSION_ANALYZER_H_