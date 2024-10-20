#ifndef SG_PARSER_FILE_LIST_H_
#define SG_PARSER_FILE_LIST_H_

#include <vector>
#include <string>
#include <filesystem>

namespace source_graph
{
using std::filesystem::path;
using FileIndexList =  std::vector<int>;

///
/// @brief
///     Holds a list of std::filesystem::path objects
///     
///     Operations include
///         - adding files/directories
///         - obtaining indexes/index lists
/// 
class FileList
{
public:

    FileList();

    const path& getBasePath() const { return m_basepath; }

    auto& getFileList()  { return m_list; }

    int addDirectory(const path& p);
    
    void addFile(const path& p) { m_list.push_back(p); }
    
    size_t getNumFiles() { return m_list.size(); }

    std::vector<size_t> getIndexListFromNames(const std::vector<path>& names);

    const path& operator[](size_t idx) const
    {
        return m_list[idx];
    }

private:
    
    std::vector<path> m_list;
    
    path m_basepath;
};

} // source_graph



#endif // SG_PARSER_FILE_LIST_H_