# source-graph
Physical Dependency Analyzer for C++ projects using Directed Graphs. 

## Features
- Forward (what a file includes) and Reverse (what includes a file) analysis
- Cycle detection
- Multi-threaded analysis
- Graphviz-compatable output
- "Bacon Number" searching using the Bread First Search algorithm
# Screenshots
## Command line
\~11 million lines in a second
![](https://github.com/raging-loon/source-graph/raw/main/images/image1.png)

Path from [main.cpp](https://github.com/Simula-24/Simula-24/blob/main/simula24/main/main.cpp) to [copy_on_write.h](https://github.com/Simula-24/Simula-24/blob/main/simula24/core/stl/copy_on_write.h)

![](https://github.com/raging-loon/source-graph/raw/main/images/image2.png)
Reverse inclusion
![](https://github.com/raging-loon/source-graph/raw/main/images/image3.png)
Forward inclusion
![](https://github.com/raging-loon/source-graph/raw/main/images/image4.png)

## Graphviz

Files included by [TerminalInterface.cpp](https://github.com/raging-loon/kdl/blob/main/src/cli/TerminalInterface.cpp)
![](https://github.com/raging-loon/source-graph/raw/main/images/one.png)

 
Files that include [Parser.h](https://github.com/raging-loon/kdl/blob/main/src/parser/parser.h)

![](https://github.com/raging-loon/source-graph/raw/main/images/two.png)

Path from [main.cpp](https://github.com/Simula-24/Simula-24/blob/main/simula24/main/main.cpp) to [copy_on_write.h](https://github.com/Simula-24/Simula-24/blob/main/simula24/core/stl/copy_on_write.h)

![<img src="https://github.com/raging-loon/source-graph/raw/main/images/three.png" width="256"/>](https://github.com/raging-loon/source-graph/raw/main/images/three.png)

