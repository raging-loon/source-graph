#include "IncludeAnalyzer.h"
#include <fstream>
#include <filesystem>
#include <thread>


using source_graph::IncludeAnalyzer;
using namespace std::filesystem;

int IncludeAnalyzer::analyze()
{
    FileList copy = m_outList;
    
    std::vector<std::thread> threadpool;

    int numfiles = m_outList.getNumFiles();
    int num = std::thread::hardware_concurrency();
    //printf("%d | %d\n",numfiles, std::thread::hardware_concurrency());
    int range = numfiles / num;
    int remainder  = numfiles % num;
    int start = 0;
    for (int i = 0; i < num; i++)
    {
        int end = start + range - 1;
        if (i == 3)
        {
            end += remainder;
        }
        threadpool.push_back(std::thread{&IncludeAnalyzer::mtAnalyze, this, start, end, std::ref(copy)});
        start = end + 1;
    }

    for (auto& t : threadpool)
        t.join();
    return 0;// mtAnalyze(0, m_outList.getNumFiles(), copy);
}

int IncludeAnalyzer::mtAnalyze(int startIdx, int endIdx, const FileList& copy)
{

    int curFileIdx = startIdx;

    std::string line;

    for (int i = startIdx; i <= endIdx; i++)
    {
        auto& filename = copy[i];
        ++m_numFilesAnalyzed;
   
        std::ifstream file(filename);
        while (std::getline(file, line))
        {
            ++m_linesCounted;
            if (line.starts_with("#include"))
            {
                //printf("INCLUDE FOUND %s includes %s\n", filename.string().c_str(), line.c_str());
                ++m_pdepFound;
                char startChar, endChar;
                int soffset, eoffset = 0;
                if (line.rfind('"') != std::string::npos)
                {
                    startChar = '"';
                    endChar = '"';
                    soffset = eoffset = 1;
                }
                else if(line.rfind('>') != std::string::npos)
                {
                    soffset = 1; eoffset = 1;
                    startChar = '<';
                    endChar = '>';
                }
                else
                {
                    printf("Possible a macro.cannot analyze %s!",line.c_str());
                    continue;
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
                for (int j = 0; j < m_outList.getNumFiles(); j++)
                {
                    if (m_outList[j].string() == incname)
                    {
                        //printf("%s includes %s (%d -> %d)\n", filename.string().c_str(), m_outList[j].string().c_str(), i, incIdx);
                        m_outGraph.addInclude(i, incIdx);
                        incIdx = -1;
                        break;
                    }
                    incIdx++;
                }


                if (incIdx != -1)
                {
                    m_outGraph.addInclude(i, m_outList.getNumFiles());
                    m_outList.addFile(incname);
                }
            }

        }
        curFileIdx++;
    }

    return 0;
}
