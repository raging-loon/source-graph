#include "IncludeAnalyzer.h"
#include <fstream>
#include <filesystem>
using source_graph::IncludeAnalyzer;
using namespace std::filesystem;
int IncludeAnalyzer::analyze()
{
    FileList copy = m_outList;

    int curFileIdx = 0;
    
    std::string line;

    for (auto& filename : copy.getFileList())
    {
        if (filename.string().ends_with(".txt"))
        {
            curFileIdx++;
            continue;
        }
        std::ifstream file(filename);
        while (std::getline(file, line))
        {
            if (line.starts_with("#include"))
            {
                char startChar, endChar;
                if (line.find('"') != std::string::npos)
                {
                    startChar = '"';
                    endChar = '"';
                }
                else
                {
                    startChar = '<';
                    endChar = '>';
                }

                std::string incname = line.substr(
                    line.find(startChar) + 1,
                    line.rfind(endChar) - line.find(startChar) - 1
                );
                if (endChar == '"')
                {
                    if (exists(filename.parent_path().string() + "/" + incname))
                        incname = filename.parent_path().string() + "/" + incname;
                }
                
                std::replace(incname.begin(), incname.end(), '/', '\\');

                int incIdx = 0;
                for (auto& f : m_outList.getFileList())
                {
                    if (f.string() == incname)
                    {
                        m_outGraph.addInclude(curFileIdx, incIdx);
                        break;
                    }
                    incIdx++;
                }
                if (incIdx == m_outList.getNumFiles())
                {
                    if (!incname.ends_with(".h"))
                        incname = "<" + incname + ">";
                    m_outGraph.addInclude(curFileIdx, m_outList.getNumFiles());
                    m_outList.addFile(incname);
                }
            }

        }
        curFileIdx++;
    }
    
    return 0;
}