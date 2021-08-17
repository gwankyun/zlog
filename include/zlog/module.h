#pragma once

#ifndef ZLOG_EXPORT_BEGIN
#  if USE_ZLOG_MODULE
#    define ZLOG_EXPORT_BEGIN export {
#  else
#    define ZLOG_EXPORT_BEGIN
#  endif
#endif

#ifndef ZLOG_EXPORT_END
#  if USE_ZLOG_MODULE
#    define ZLOG_EXPORT_END }
#  else
#    define ZLOG_EXPORT_END
#  endif
#endif
