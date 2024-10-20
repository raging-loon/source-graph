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
#include "cli/TerminalInterface.h"
#include "utils.h"

using namespace source_graph;
using std::filesystem::path;

int main(int argc, char** argv)
{
    TerminalInterface tui(argc, argv);
    if (!tui.parse())
        return -1;
    if (!tui.run())
        return -1;

    return 0;
}