#include "CircularInclusionAnalyzer.h"
#include <unordered_map>
#include <queue>
using namespace source_graph;

bool CircularInclusionAnalyzer::hasCircularIncludes(int file1, int file2)
{

    auto inc1 = m_igraph.getFilesThatInclude(file1);
    auto inc2 = m_igraph.getFilesThatInclude(file2);

    if (!inc1.has_value() || !inc2.has_value())
        return false;
            
    for (int i = 0; i < inc1.value().size(); i++)
    {
        if (inc1.value()[i] == file2)
        {
            for (int j = 0; i < inc2.value().size(); j++)
            {
                if (inc2.value()[j] == file1)
                    return true;
            }

        }
    }   

    
    return false;
}

std::vector<int> CircularInclusionAnalyzer::findIndirectCircularIncludes(int file1, int file2, int depth)
{
    std::vector<int> pathTofile2{};
    std::unordered_map<int, int> touched{};
    std::queue<int> frontier{};
    printf("%s -> %s\n",m_sources[file1].string().c_str(), m_sources[file2].string().c_str());
    touched.insert({ file1, file1 });
    frontier.push(file1);

    while (!frontier.empty())
    {
        int cFileIdx = frontier.front(); frontier.pop();
        if (cFileIdx == file2)
            break;
        auto subIdxList = m_igraph.getFilesIncludedBy(cFileIdx);
        if (!subIdxList.has_value())
            continue;
        for (auto subidx : subIdxList.value())
        {
            if (touched.find(subidx) == touched.end())
            {
                frontier.push(subidx);
                touched[subidx] = cFileIdx;
            }
        }
    }
    if (touched.find(file2) == touched.end())
        return pathTofile2;
    int file = file2;
    while (file != file1)
    {
        pathTofile2.push_back(file);
        file = touched[file];
    }
    pathTofile2.push_back(file1);
    std::reverse(pathTofile2.begin(), pathTofile2.end());
    return pathTofile2;
}
