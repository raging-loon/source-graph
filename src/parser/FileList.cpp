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
