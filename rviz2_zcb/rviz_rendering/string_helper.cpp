#include "string_helper.hpp"

#include <algorithm>
#include <locale>
#include <string>
#include <vector>

// Used to parse strings derived from CMake
// using the system locale, since CMake seems to take the system locale to parse strings
std::vector<std::string> rviz_rendering::string_helper::splitStringIntoTrimmedItems(
  const std::string & string_to_split, const char delimiter)
{
  std::stringstream stringstream(string_to_split);
  std::string item;
  std::vector<std::string> filenames;
  while (std::getline(stringstream, item, delimiter)) {
    auto whitespace_front = std::find_if_not(
      item.begin(), item.end(), [](char character) {
        return std::isspace<char>(character, std::locale(""));
      });
    auto whitespace_back = std::find_if_not(
      item.rbegin(), item.rend(), [](char character) {
        return std::isspace<char>(character, std::locale(""));
      });
    item.erase(whitespace_back.base(), item.end());
    item.erase(item.begin(), whitespace_front);
    if (!item.empty()) {
      filenames.push_back(item);
    }
  }
  return filenames;
}
