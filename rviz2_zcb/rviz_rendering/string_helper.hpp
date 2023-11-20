#ifndef RVIZ_RENDERING__STRING_HELPER_HPP_
#define RVIZ_RENDERING__STRING_HELPER_HPP_

#include <string>
#include <sstream>
#include <vector>

namespace rviz_rendering
{
namespace string_helper
{
std::vector<std::string>
splitStringIntoTrimmedItems(const std::string &, const char);
}  // namespace string_helper
}  // namespace rviz_rendering

#endif  // RVIZ_RENDERING__STRING_HELPER_HPP_
