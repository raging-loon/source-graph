#ifndef SG_OUTPUT_OUTPUT_STRATEGY_H_
#define SG_OUTPUT_OUTPUT_STRATEGY_H_
#include "parser/FileList.h"
namespace source_graph
{
class IncludeGraph;

///
/// @brief
///     Output Methods such as DOT/STDOUT
/// 
class OutputStrategy
{
public:

    virtual void writeForwardIncludes(const FileList& sources, const FileIndexList& ilist, const IncludeGraph& graph) = 0;
    virtual void writeReverseIncludes(const FileList& sources, const FileIndexList& ilist, const IncludeGraph& graph) = 0;
    virtual void writeTransitiveInclude(const FileList& sources, const FileIndexList& idx) = 0;
    
private:

};

} // source_graph


#endif // SG_OUTPUT_OUTPUT_STRATEGY_H_