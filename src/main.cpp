#include <cstdio>
#include "graph/Graph.h"
#include <iostream>
#include <string>
#include <vector>

using namespace source_graph;

int main(int argc, char** argv)
{
    printf("Hello\n");

    std::vector<std::string> sources
    {
        "test.h", "test2.h", "test3.h", "test4.h",
        "test5.h", "test6.h", "test7.h"
    };

    Graph g;
    g.addVertex(0, 1);
    g.addVertex(1, 2);
    g.addVertex(1, 3);
    g.addVertex(4, 4);
    g.addVertex(3, 5);

    std::cout << std::boolalpha << g.hasEdges(2) << std::endl;
    auto list = g.getVertices(1);
    if (list.has_value())
    {
        for (auto& i : list.value())
        {
            std::cout << i << " " << sources[i] << std::endl;
            auto list2 = g.getVertices(i);
            if (list2.has_value())
            {
                for (auto& j : list2.value())
                    std::cout << j << " " << sources[j] << std::endl;

            }
            
        }
    }
    return 0;
}