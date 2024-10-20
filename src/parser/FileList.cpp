#include "parser/FileList.h"

#include <filesystem>

using source_graph::FileList;
using namespace std::filesystem;
FileList::FileList()
{

}

int FileList::addDirectory(const path& p)
{

printf("%s\n",p.string().c_str());
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

std::vector<size_t> FileList::getIndexListFromNames(const std::vector<path>& names)
{
    std::vector<size_t> indexList{};

    int startIndex = 0;

    for (int i = 0; i < m_list.size(); i++)
    {
        for (int j = startIndex; j < names.size(); j++)
        {
            if (names[j].string() == m_list[i].string())
            {
                indexList.push_back(i);
            }
        }
    }

    return indexList;
}
