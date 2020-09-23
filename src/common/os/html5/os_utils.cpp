#include "os/os_utils.h"

namespace waterpine {

std::string OSUtils::GetResourcePath(std::string_view fileName,
                                     std::string_view fileType,
                                     std::string_view rel_path) {
  std::string path(rel_path);
  path.append("/");
  path.append(fileName);
  path.append(".");
  path.append(fileType);
  return path;
}

}  // namespace waterpine
