#pragma once
#ifndef STRINGIFY_IMPL
#  define STRINGIFY_IMPL(x) #x
#endif

#ifndef STRINGIFY
#  define STRINGIFY(x) STRINGIFY_IMPL(x)
#endif

#ifndef LOG_IF
#  define LOG_IF(_pred) lite::LogObject<std::ostream>(std::cout, _pred) << lite::currentTime() << std::source_location::current()
#endif

#ifndef LOG
#  define LOG() LOG_IF(true)
#endif

#ifndef LOG_DBG
#  define LOG_DBG(_value) LOG() << lite::Expression(STRINGIFY(_value)) << " = " << _value << " (" << lite::Type(lite::type(_value)) << ")\n";
#endif
