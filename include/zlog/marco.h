#pragma once
#if !defined(SOURCE_LOCATION_CURRENT) && USE_STD_SOURCE_LOCATION
#  define SOURCE_LOCATION_CURRENT() std::source_location::current()
#endif

#ifndef STRINGIFY_IMPL
#  define STRINGIFY_IMPL(x) #x
#endif

#ifndef STRINGIFY
#  define STRINGIFY(x) STRINGIFY_IMPL(x)
#endif

#ifndef LOG_IF
#  define LOG_IF(_pred) zlog::LogObject<std::ostream>(std::cout, _pred) << zlog::currentTime() << SOURCE_LOCATION_CURRENT()
#endif

#ifndef LOG
#  define LOG() LOG_IF(true)
#endif

#ifndef ZDBG
#  define ZDBG(_value) LOG() << zlog::Expression(STRINGIFY(_value)) << " = " << _value << " (" << zlog::Type(zlog::type(_value)) << ")\n";
#endif
