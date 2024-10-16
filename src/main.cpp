#include <cstdio>
#include "graph/Graph.h"
#include <iostream>
#include "parser/FileList.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include "graph/IncludeGraph.h"
#include "analyzer/IncludeAnalyzer.h"
using namespace source_graph;
using std::filesystem::path;
int main(int argc, char** argv)
{
    IncludeGraph sourcegraph;

    auto cur = std::filesystem::current_path();
    std::filesystem::current_path("D:/simula-24/simula24");
    FileList f(".");
    int iter = 0;

    IncludeAnalyzer ia(f, sourcegraph);
    ia.analyze();

    for (int i = 0; i < f.getNumFiles(); i++)
    {
        auto fwdList = sourcegraph.getFilesIncludedBy(i);
        auto revList = sourcegraph.getFilesThatInclude(i);
    
        int amnt = printf("---- %s ----\n",f.getFileList()[i].string().c_str());
        if (!fwdList.has_value())
            printf("%s has no detected includes, or it is a system file\n", f.getFileList()[i].string().c_str());
        else
        {
            printf("Includes: \n");
            for (auto file : fwdList.value())
                printf("\t%s\n", f.getFileList()[file].string().c_str());
        }    
        if (f.getFileList()[i].string().ends_with(".cpp"))
            printf("Skipping source file...\n");
        else if (!revList.has_value())
            printf("%s is not included by anything\n", f.getFileList()[i].string().c_str());
        else
        {
            printf("Included by: \n");
            for (auto file : revList.value())
                printf("\t%s\n", f.getFileList()[file].string().c_str());
        }
        for (int j = 0; j < amnt-1 ; j++)
            putchar('-');
        putchar('\n');
    }

    return 0;
}