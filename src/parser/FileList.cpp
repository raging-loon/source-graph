#include "parser/FileList.h"

#include <filesystem>
#include <mutex>
using source_graph::FileList;
using source_graph::FileIndexList;
using namespace std::filesystem;
FileList::FileList()
    : m_mtx{}
{

}

int FileList::addDirectory(const path& p)
{
    std::lock_guard lock(m_mtx);

    for (auto const& entry : std::filesystem::recursive_directory_iterator{ p })
    {
        if (!entry.is_directory())
        {
            
            auto ext = entry.path().extension();
            if (ext == ".cpp" || ext == ".h" || ext == ".c" ||
                ext == ".cxx" || ext == ".hpp" || ext == ".c++" ||
                ext == ".h++")
            {
                m_list.push_back(std::filesystem::relative(entry.path(), p));
            }
        }

    }

    return m_list.size();
}

FileIndexList FileList::getIndexListFromNames(const std::vector<path>& names)
{
    FileIndexList indexList{};

    int startIndex = 0;

    for (int i = 0; i < names.size(); i++)
    {
        for (int j = startIndex; j < m_list.size(); j++)
        {
            if (names[i].string() == m_list[j].string())
                indexList.push_back(j);
        }
    }

    return indexList;
}

FileIndexList FileList::getIndexList() const
{
    FileIndexList ilist{};

    for (int i = 0; i < m_list.size(); i++)
        ilist.push_back(i);

    return ilist;
}
