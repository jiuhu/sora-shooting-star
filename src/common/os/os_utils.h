#ifndef _COMMON_OS_OS_UTILS_H
#define _COMMON_OS_OS_UTILS_H

#include <string>

namespace waterpine {

class OSUtils {
 public:
  static std::string GetResourcePath(std::string_view file_name,
                                     std::string_view file_type,
                                     std::string_view rel_path);
};

}  // namespace waterpine

#endif  // _COMMON_OS_OS_UTILS_H
