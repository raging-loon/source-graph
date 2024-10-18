#ifndef SG_UTILS_H_
#define SG_UTILS_H_

#include <vector>
#include <string>
namespace source_graph
{

///
/// @brief
///     Split a string by a delimiter
/// 
///     e.g. "1,2,3,4" with a delimiter of ',' would 
///     return a vector holding "1", "2", "3", and "4".   
///     
/// @returns 
///     list of substrings
/// 
std::vector<std::string> split(const std::string& str, char delim);

} // source_graph

#endif // SG_UTILS_H_