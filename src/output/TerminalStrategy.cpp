#include "TerminalStrategy.h"
#include <iostream>
using namespace source_graph;

//void TerminalStrategy::dumpForwardIncludes(FileList& files, FileList& sources, IncludeGraph& graph)
//{
//    auto indexList = sources.getIndexListFromNames(files.getFileList());
//    for (auto& i : indexList)
//    {
//        std::cout << "Files included by " << sources[i] << "\n";
//    
//        auto inclist = graph.getFilesIncludedBy(i);
//
//        if (!inclist.has_value())
//            std::cout << std::format("File {} has no includes or it is a system/lib file.\n", sources[i].string());
//        else {
//            for (auto& i : inclist.value())
//                std::cout << "\t" << sources[i].string() << "\n";
//        }
//    }
//}
//
//void TerminalStrategy::dumpReverseIncludes(FileList& files, FileList& sources, IncludeGraph& graph)
//{
//    auto indexList = sources.getIndexListFromNames(files.getFileList());
//    for (auto& i : indexList)
//    {
//        std::cout << "Files that include " << sources[i].string() << "\n";
//
//        auto inclist = graph.getFilesThatInclude(i);
//
//        if (!inclist.has_value())
//            std::cout << std::format("File {} is not included by any file.\n", sources[i].string());
//        else {
//            for (auto& i : inclist.value())
//                std::cout << "\t" << sources[i].string() << "\n";
//        }
//    }
//}

void TerminalStrategy::writeForwardIncludes(const FileList& sources, const IncludeGraph& graph)
{
}

void TerminalStrategy::writeReverseIncludes(const FileList& sources, const IncludeGraph& graph)
{
}

void TerminalStrategy::writeTransitiveInclude(const FileList& sources, const FileIndexList& idx)
{
    if (idx.size() == 0)
    {
        std::cerr << "No path between files\n";
        return;
    }
    for (int i = 0; i < idx.size()-1; i++)
        std::cerr << sources[idx[i]].string() << " -> ";

    std::cerr << sources[idx.back()].string() << "\n";

}
