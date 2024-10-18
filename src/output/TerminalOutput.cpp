#include "TerminalOutput.h"
#include <iostream>
using namespace source_graph;

void TerminalOuput::dumpForwardIncludes(FileList& files, FileList& sources, IncludeGraph& graph)
{
    auto indexList = sources.getIndexListFromNames(files.getFileList());
    for (auto& i : indexList)
    {
        std::cout << "Files included by " << sources[i] << "\n";
    
        auto inclist = graph.getFilesIncludedBy(i);

        if (!inclist.has_value())
            std::cout << std::format("File {} has no includes or it is a system/lib file.\n", sources[i].string());
        else {
            for (auto& i : inclist.value())
                std::cout << "\t" << sources[i].string() << "\n";
        }
    }
}

void TerminalOuput::dumpReverseIncludes(FileList& files, FileList& sources, IncludeGraph& graph)
{
    auto indexList = sources.getIndexListFromNames(files.getFileList());
    for (auto& i : indexList)
    {
        std::cout << "Files that include " << sources[i].string() << "\n";

        auto inclist = graph.getFilesThatInclude(i);

        if (!inclist.has_value())
            std::cout << std::format("File {} is not included by any file.\n", sources[i].string());
        else {
            for (auto& i : inclist.value())
                std::cout << "\t" << sources[i].string() << "\n";
        }
    }
}
