#include "parser/FileList.h"

#include <filesystem>

using source_graph::FileList;
using source_graph::FileIndexList;
using namespace std::filesystem;
FileList::FileList()
{

}

int FileList::addDirectory(const path& p)
{
    for (auto const& entry : std::filesystem::recursive_directory_iterator{ p })
    {
        if (!entry.is_directory())
        {
            
            auto ext = entry.path().extension();
            if (ext == ".cpp" || ext == ".h" || ext == ".c" ||
                ext == ".cxx" || ext == ".hpp" || ext == ".c++" ||
                ext == ".h++")
            {
                addFile(std::filesystem::relative(entry.path(), p));
            }
        }

    }

    return getNumFiles();
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
    FileIndexList ilist(m_list.size());

    for (int i = 0; i < m_list.size(); i++)
        ilist.push_back(i);

    return ilist;
}
