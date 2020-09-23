#include "os/os_utils.h"

#ifdef __APPLE__

#include <CoreFoundation/CFBundle.h>

std::string OSUtils::GetResourcePath(const char* const file_name,
                                     const char* const file_type,
                                     const char* const /*rel_path*/) {
  CFURLRef cf_url = CFBundleCopyResourceURL(
      CFBundleGetMainBundle(),
      __CFStringMakeConstantString(file_name),
      __CFStringMakeConstantString(file_type),
      nullptr);

  CFStringRef cf_path = CFURLCopyFileSystemPath(cf_url, kCFURLPOSIXPathStyle);
  CFRelease(cf_url);

  std::string path(CFStringGetCStringPtr(cf_path, CFStringGetSystemEncoding()));
  CFRelease(cf_path);

  return path;
}

#endif
