#pragma once

#ifndef NOEXCEPT
#  if __cplusplus >= 201103L
#    define NOEXCEPT noexcept
#  else
#    define NOEXCEPT
#  endif // __cplusplus >= 201907L
#endif // !NOEXCEPT

#ifndef NULLPTR
#  if __cplusplus >= 201103L
#    define NULLPTR nullptr
#  else
#    define NULLPTR NULL
#  endif // __cplusplus >= 201103L
#endif // !NULLPTR

#ifndef EQ_DELETE
#  if __cplusplus >= 201103L
#    define EQ_DELETE = delete;
#  else
#    define EQ_DELETE
#  endif // __cplusplus >= 201103L
#endif // !EQ_DELETE

#ifndef EQ_DEFAULT
#  if __cplusplus >= 201103L
#    define EQ_DEFAULT = default
#  else
#    define EQ_DEFAULT {}
#  endif // __cplusplus >= 201103L
#endif // !EQ_DEFAULT

#ifndef RV_REF
#  if defined(__cpp_rvalue_references)
#    define RV_REF(t) t&&
#  else
#    define RV_REF(t) t
#  endif // defined(__cpp_rvalue_references)
#endif // !RV_REF

#ifndef CONSTEXPR
#  if __cplusplus >= 201103L
#    define CONSTEXPR constexpr
#  else
#    define CONSTEXPR inline
#  endif // __cplusplus >= 201103L
#endif // !CONSTEXPR

#ifndef UNIQUE_ID
#  if defined(__COUNTER__) && (__COUNTER__ + 1 == __COUNTER__ + 0)
#    define UNIQUE_ID __COUNTER__
#  else
#    define UNIQUE_ID __LINE__
#  endif // defined(__COUNTER__) && (__COUNTER__ + 1 == __COUNTER__ + 0)
#endif // !UNIQUE_ID

#ifndef UNIQUE_NAME_CAT
#  define UNIQUE_NAME_CAT(name, unique) name##unique
#endif // !UNIQUE_NAME_CAT

#ifndef UNIQUE_VALUE_NAME
#  define UNIQUE_VALUE_NAME(name, unique) UNIQUE_NAME_CAT(name, unique)
#endif // !SCOPE_GUARD_UNIQUE_NAME
