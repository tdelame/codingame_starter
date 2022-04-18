# pragma once
# ifndef __POPCNT__
#  pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer","inline")// improve code optimization
#  pragma GCC option("arch=native","tune=native","no-zero-upper")           // tuning compilation flags
#  pragma GCC target("bmi,bmi2,lzcnt,popcnt")                               // bit manipulation
#  pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2")          // SIMD
#  pragma GCC target("movbe")                                               // byte swap
#  pragma GCC target("aes,pclmul,rdrnd")                                    // encryption
#  define TRAP __builtin_trap()                                             // halt the program in the arena
#  undef _GLIBCXX_DEBUG
static constexpr bool is_codingame = true;
# else
#  include <csignal>
#  ifdef _WIN32
#   define TRAP __debugbreak()                                              // halt the program on Windows
#   define _CRT_SECURE_NO_WARNINGS
#  else
#   define TRAP raise(SIGTRAP)                                              // halt the program on Linux
#  endif
static constexpr bool is_codingame = false;
# endif
# include <cinttypes>                                                       // to bring any integral type definition in the scope
# include <cstdio>                                                          // to bring all the c standard I/O function (faster than C++ ones)
static constexpr bool with_state_output = true;
static constexpr bool with_debug_logger = true;
static constexpr bool with_info_logger  = true;
static constexpr bool with_error_logger = true;
static constexpr bool with_checks       = true;
static constexpr size_t max_bitstream_bytes = 2048;

# define STRINGIFY_DETAIL(x) #x
# define STRINGIFY(x) STRINGIFY_DETAIL(x)
# define Check(condition) if constexpr (with_checks) {\
  if (__builtin_expect(!(condition),0)) {\
    fprintf(stderr, "FATAL: condition failure %s at %s:%i(%s)\n", STRINGIFY(condition), __FILE__, __LINE__, __PRETTY_FUNCTION__);\
    TRAP;\
  }\
}
# define CheckMsg(condition, arguments...) if constexpr (with_checks) {\
  if (__builtin_expect(!(condition),0)) {\
    fprintf(stderr, "FATAL: condition failure %s at %s:%i(%s)\n    ", STRINGIFY(condition), __FILE__, __LINE__, __PRETTY_FUNCTION__);\
    fprintf(stderr, arguments);\
    TRAP;\
  }\
}
namespace logger {
  template<typename... Args> void debug( const char* format, const Args&... args ) { if constexpr (with_debug_logger) fprintf( stderr, format, args... ); }
  template<typename... Args> void info( const char* format, const Args&... args ) { if constexpr (with_info_logger) fprintf( stderr, format, args... ); }
  template<typename... Args> void error( const char* format, const Args&... args ) { if constexpr (with_error_logger) fprintf( stderr, format, args... ); }
}

// Customize this interface to match the game rules.
struct Output {
  void finish() {
    if constexpr(is_codingame) {fflush(stdout);}
  }
};
