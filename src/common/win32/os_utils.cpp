#include "os/os_utils.h"

std::string OSUtils::GetResourcePath(const char* const fileName,
                                     const char* const fileType,
                                     const char* const rel_path) {
  std::string path(rel_path);
  path.append("/");
  path.append(fileName);
  path.append(".");
  path.append(fileType);
  return path;
}
