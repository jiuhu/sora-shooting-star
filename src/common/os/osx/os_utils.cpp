#include "os/os_utils.h"

#ifdef __APPLE__

#include <CoreFoundation/CFBundle.h>

namespace waterpine {

std::string OSUtils::GetResourcePath(std::string_view file_name,
                                     std::string_view file_type,
                                     std::string_view /*rel_path*/) {
  auto encoding = CFStringGetSystemEncoding();
  auto name = CFStringCreateWithCString(nullptr, file_name.data(), encoding);
  auto type = CFStringCreateWithCString(nullptr, file_type.data(), encoding);
  CFURLRef cf_url = CFBundleCopyResourceURL(CFBundleGetMainBundle(), name, type, nullptr);
  CFRelease(name);
  CFRelease(type);

  CFStringRef cf_path = CFURLCopyFileSystemPath(cf_url, kCFURLPOSIXPathStyle);
  CFRelease(cf_url);

  std::string path(CFStringGetCStringPtr(cf_path, encoding));
  CFRelease(cf_path);

  return path;
}

}  // namespace waterpine

#endif
