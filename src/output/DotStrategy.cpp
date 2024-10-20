#include "DotStrategy.h"
#include <iostream>
using source_graph::DotStrategy;

void DotStrategy::writeForwardIncludes(const FileList& sources, const FileIndexList& ilist, const IncludeGraph& graph)
{
    for (auto i : ilist)
    {
        auto inclist = graph.getFilesIncludedBy(i);
        if(!inclist.has_value())
            std::cerr << sources[i].string() << " has no detected includes, or it is a library/system file\n";
        else
        {
            std::cout << "digraph " << i << "{\n"
                      << "\tbase [label=\"" << sources[i].string() << "\"];\n";

            for (auto idx : inclist.value())
                std::cout << "\t\"" << sources[idx].string() << "\" -> base\n";

            std::cout << "}\n\n";
        }
    }
}

void DotStrategy::writeReverseIncludes(const FileList& sources, const FileIndexList& ilist, const IncludeGraph& graph)
{
    for (auto i : ilist)
    {
        auto inclist = graph.getFilesThatInclude(i);
        if (!inclist.has_value())
            std::cerr << sources[i].string() << "is not included by any files\n";
        else
        {
            std::cout << "digraph " << "graph" << i << "{\n"
                << "\tbase [label=\"" << sources[i].string() << "\"];\n";

            for (auto idx : inclist.value())
                std::cout << "\tbase -> \"" << sources[idx].string() << "\"\n";


            std::cout << "}\n\n";
        }
    }
}

void DotStrategy::writeTransitiveInclude(const FileList& sources, const FileIndexList& idx)
{
    if (idx.size() < 2)
    {
        std::cerr << "No path between files\n";
        return;
    }

    std::cout << "digraph TransitiveIncludeGraph {\n";

    for (int i = 0; i < idx.size() - 1; i++)
            std::cout << '"' << sources[idx[i]].string() << '"' << " -> ";

    std::cout << '"' << sources[idx.back()].string() << '"' << "\n}\n";

}
