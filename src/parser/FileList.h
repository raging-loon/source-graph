#ifndef SG_PARSER_FILE_LIST_H_
#define SG_PARSER_FILE_LIST_H_

#include <vector>
#include <string>
#include <filesystem>

namespace source_graph
{
using std::filesystem::path;
class FileList
{
public:

    FileList();

    const path& getBasePath() const { return m_basepath; }

    auto& getFileList()  { return m_list; }

    int addDirectory(const path& p);
    void addFile(const path& p) { m_list.push_back(p); }
    size_t getNumFiles() { return m_list.size(); }
private:
    std::vector<path> m_list;
    path m_basepath;
};

} // source_graph



#endif // SG_PARSER_FILE_LIST_H_