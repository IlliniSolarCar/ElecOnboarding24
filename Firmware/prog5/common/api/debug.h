#include "mbed.h"

#ifndef COMMON_API_DEBUG_H_
#define COMMON_API_DEBUG_H_

#include <cstdio>

#ifndef DEBUG_MODULE
  #define DEBUG_MODULE __FILE__
#endif

namespace debug {
  extern char buffer[];
  void puts(const char* string);
}

#ifdef DEBUG_ENABLED

#define STRINGIFY(X) #X
#define TOSTRING(x) STRINGIFY(x)

#define debugPrint(f, ...)  \
  sprintf(debug::buffer, f, ## __VA_ARGS__);  \
  debug::puts(debug::buffer);  \

#define debugInfo(f, ...)  \
  debug::puts("\033[36mInfo)\033[0m " DEBUG_MODULE " " TOSTRING(__LINE__) ": ");  \
  sprintf(debug::buffer, f, ## __VA_ARGS__);  \
  debug::puts(debug::buffer);  \
  debug::puts("\r\n");

#define debugWarn(f, ...)  \
  debug::puts("\033[33mWarn)\033[0m " DEBUG_MODULE " " TOSTRING(__LINE__) ": ");  \
  sprintf(debug::buffer, f, ## __VA_ARGS__);  \
  debug::puts(debug::buffer);  \
  debug::puts("\r\n");

#else

#define debugInfo(f, ...)  ;
#define debugWarn(f, ...)  ;

#endif

#endif
