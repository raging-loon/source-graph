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

    /// 
    /// @brief
    ///     recursively add all files in a directory
    /// @returns
    ///     Number of files added
    int addDirectory(const path& p);
    
    void addFile(const path& p) { m_list.push_back(p); }
    
    size_t getNumFiles() const { return m_list.size(); }

    const path& getBasePath() const { return m_basepath; }

    const auto& getFileList() const { return m_list; }

    ///
    /// @brief
    ///     Get the indexes of the files in `names` in our own filelist
    /// 
    FileIndexList  getIndexListFromNames(const std::vector<path>& names);
    
    ///
    /// @brief 
    ///     Get our indexes
    FileIndexList getIndexList() const;


    const path& operator[](size_t idx) const { return m_list[idx]; }

private:
    
    std::vector<path> m_list;
    
    path m_basepath;
};

} // source_graph



#endif // SG_PARSER_FILE_LIST_H_