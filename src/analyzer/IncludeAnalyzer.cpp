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
        ++m_numFilesAnalyzed;
        if (filename.string().ends_with(".txt"))
        {
            curFileIdx++;
            continue;
        }
        std::ifstream file(filename);
        while (std::getline(file, line))
        {
            ++m_linesCounted;
            if (line.starts_with("#include"))
            {
                ++m_pdepFound;
                char startChar, endChar;
                int soffset, eoffset = 0;
                if (line.rfind('"') != std::string::npos)
                {
                    startChar = '"';
                    endChar = '"';
                    soffset = eoffset = 1;
                }
                else
                {
                    soffset = 0; eoffset = -1;
                    startChar = '<';
                    endChar = '>';
                }

                std::string incname = line.substr(
                    line.find(startChar) + soffset,
                    line.rfind(endChar) - line.find(startChar) - eoffset
                );
                if (endChar == '"')
                {
                    if (exists(filename.parent_path().string() + "/" + incname))
                        incname = filename.parent_path().string() + "/" + incname;
                }
#ifdef _WIN32
                std::replace(incname.begin(), incname.end(), '/', '\\');
#else
                std::replace(incname.begin(), incname.end(), '\\', '/');
#endif
                int incIdx = 0;
                for (auto& f : m_outList.getFileList())
                {
                    if (f.string() == incname)
                    {
                        m_outGraph.addInclude(curFileIdx, incIdx);
                        incIdx = -1;
                        break;
                    }
                    incIdx++;
                }


                if (incIdx != -1)
                {
                    m_outGraph.addInclude(curFileIdx, m_outList.getNumFiles());
                    m_outList.addFile(incname);
                }
            }

        }
        curFileIdx++;
    }
    
    return 0;
}