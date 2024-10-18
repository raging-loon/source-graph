#include "utils.h"

std::vector<std::string> source_graph::split(const std::string& str, char delim)
{
    std::vector<std::string> list{};
    size_t last = 0, next = 0;

    while ((next = str.find(delim, last)) != std::string::npos)
    {
        list.push_back(str.substr(last, next - last));
        last = next + 1;

    }
    list.push_back(str.substr(last));
    return list;
}
