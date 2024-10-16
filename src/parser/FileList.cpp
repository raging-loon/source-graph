#include "parser/FileList.h"

#include <filesystem>

using source_graph::FileList;
using namespace std::filesystem;
FileList::FileList(const std::string& path)
    : m_basepath(path)
{
    for (auto const& entry : std::filesystem::recursive_directory_iterator{ m_basepath })
    {
        if (!entry.is_directory())
            m_list.push_back(entry.path());
    }
}

int FileList::addDirectory(const path& p)
{
    if (!is_directory(p))
        return -1;
    size_t csize = m_list.size();
    for (auto const& entry : std::filesystem::recursive_directory_iterator{ p })
    {
        if (!entry.is_directory())
            m_list.push_back(entry.path());
    }
    return m_list.size() - csize;
}
