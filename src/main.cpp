#include <cstdio>
#include "graph/Graph.h"
#include <iostream>
#include "parser/FileList.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include "graph/IncludeGraph.h"
using namespace source_graph;
using std::filesystem::path;
int main(int argc, char** argv)
{
    IncludeGraph sourcegraph;

    auto cur = std::filesystem::current_path();
    std::filesystem::current_path("D:/source-graph/src");
    FileList f("./");
    int iter = 0;
    auto copy = f.getFileList();
    for (auto &file : copy)
    {
        std::ifstream source(file);
        std::string line;
        while (std::getline(source, line))
        {
            if (line.starts_with("#include"))
            {
                std::cout << "Found include: " << line << "\t\tin " << file.string() << std::endl;
                if (line.rfind(">") != std::string::npos && line.rfind(".h") == std::string::npos)
                {
                    int len = line.find(">") - line.find("<")+1;
                    std::string p = line.substr(line.find("<"),len);
                    int index = 0;
                    for (auto& file2 : f.getFileList())
                    {
                        if (file2.string() == p)
                        {
                            sourcegraph.addInclude(iter, index);
                            index = -1;
                            break;
                        }
                        index++;
                    }
                    if (index != -1)
                    {
                        sourcegraph.addInclude(iter, f.getNumFiles());
                        f.addFile(p);
                    }

                }
                else
                {
                    std::string s;
                    //s += "D:\\source-graph\\src\\";
                    s += line.substr(line.find("\"") + 1, line.length() - line.find("\"") - 2);
                    std::replace(s.begin(), s.end(), '/', '\\');
                    int index = 0;
                    for (auto& file2 : f.getFileList())
                    {
                        if (file2.string() == s)
                        {
                            sourcegraph.addInclude(iter, index);
                            break;
                        }
                        index++;
                    }
                }
                
            }

        }
        iter++;
    }

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