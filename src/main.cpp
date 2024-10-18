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
    tui.parse();
    tui.run();

    return 0;
}