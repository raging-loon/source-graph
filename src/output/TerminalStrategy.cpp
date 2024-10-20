#include "TerminalStrategy.h"
#include <iostream>
using namespace source_graph;

void TerminalStrategy::writeForwardIncludes(const FileList& sources, const FileIndexList& ilist, const IncludeGraph& graph)
{
    for (auto i : ilist)
    {
        auto list = graph.getFilesIncludedBy(i);
        int amnt = printf("---- %s ----\n", sources[i].string().c_str());
        if (!list.has_value())
        {
            std::cerr << sources[i].string() << " has no detected includes, or it is a library/system file\n";
        }
        else
        {
            std::cerr << "Includes: \n";
            for (auto idx : list.value())
                std::cerr << "\t" << sources[idx].string() << "\n";

        }
        std::cerr << std::string(amnt - 1, '-') << '\n';
    }
}

void TerminalStrategy::writeReverseIncludes(const FileList& sources, const FileIndexList& ilist, const IncludeGraph& graph)
{
    for (auto i : ilist)
    {
        auto list = graph.getFilesThatInclude(i);
        int amnt = printf("---- %s ----\n", sources[i].string().c_str());
        if (!list.has_value())
        {
            std::cerr << sources[i].string() << " is not included by any file\n";
        }
        else
        {
            std::cerr << "Included by: \n";
            for (auto idx : list.value())
                std::cerr << "\t" << sources[idx].string() << "\n";
        }
        std::cerr << std::string(amnt - 1, '-') << '\n';
    }
}

void TerminalStrategy::writeTransitiveInclude(const FileList& sources, const FileIndexList& idx)
{
    if (idx.size() < 2)
    {
        std::cerr << "No path between files\n";
        return;
    }
    for (int i = 0; i < idx.size()-1; i++)
        std::cerr << sources[idx[i]].string() << " -> ";

    std::cerr << sources[idx.back()].string() << "\n";

}
