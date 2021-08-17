#pragma once
#ifndef USE_STD_SOURCE_LOCATION
#  if defined(__cpp_lib_source_location)
#    define USE_STD_SOURCE_LOCATION 1
#  else
#    define USE_STD_SOURCE_LOCATION 0
#  endif
#endif

#if USE_STD_SOURCE_LOCATION
#  include <source_location>
#else
#  include <lite/source_location.hpp>
#endif

#include "zlog/module.h"

#if !defined(SOURCE_LOCATION_CURRENT) && USE_STD_SOURCE_LOCATION
#  define SOURCE_LOCATION_CURRENT() std::source_location::current()
#endif

ZLOG_EXPORT_BEGIN
namespace zlog
{
    struct source_location
    {
#if USE_STD_SOURCE_LOCATION
        typedef std::source_location type;
#else
        typedef lite::source_location type;
#endif
    };
}
ZLOG_EXPORT_END
