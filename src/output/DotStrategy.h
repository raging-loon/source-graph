#ifndef SG_OUTPUT_DOT_STRATEGY_H_
#define SG_OUTPUT_DOT_STRATEGY_H_
#include "parser/FileList.h"
#include "graph/IncludeGraph.h"
#include "OutputStrategy.h"


namespace source_graph
{


class DotStrategy : public OutputStrategy
{
public:
    void writeForwardIncludes(const FileList& sources, const FileIndexList& ilist, const IncludeGraph& graph) override;
    void writeReverseIncludes(const FileList& sources, const FileIndexList& ilist, const IncludeGraph& graph) override;
    void writeTransitiveInclude(const FileList& sources, const FileIndexList& idx) override;



};


} // source_graph

#endif // SG_OUTPUT_DOT_STRATEGY_H_