# pragma once
// Request immediately optimization on codingame
# if !defined __POPCNT__ && !defined _WIN32 
#  pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer","inline")// improve code optimization
#  pragma GCC option("arch=native","tune=native","no-zero-upper")           // tuning compilation flags
#  pragma GCC target("bmi,bmi2,lzcnt,popcnt")                               // bit manipulation
#  pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2")          // SIMD
#  pragma GCC target("movbe")                                               // byte swap
#  pragma GCC target("aes,pclmul,rdrnd")                                    // encryption
#  undef _GLIBCXX_DEBUG
#  define WITH_LINUX 1
#  define WITH_WINDOWS 0
static constexpr bool is_codingame = true;
# else
static constexpr bool is_codingame = false;
# endif

// Platform-specific configuration
# if WITH_WINDOWS
#  define _USE_MATH_DEFINES
#  define TRAP __debugbreak()
#  define _CRT_SECURE_NO_WARNINGS
#  define LIKELY(x) x
#  define __PRETTY_FUNCTION__ __FUNCSIG__
#  define START_IGNORE_WARNINGS __pragma(warning(push, 0))
#  define STOP_IGNORE_WARNINGS __pragma(warning(pop))
#  pragma warning(disable : 4201 4774)
# else
#  include <csignal>
#  define TRAP (is_codingame ? __builtin_trap() : (void)raise(SIGTRAP))
#  define LIKELY(x) __builtin_expect(x, 0)
#  define START_IGNORE_WARNINGS _Pragma("GCC diagnostic ignored \"-Weverything\"")
#  define STOP_IGNORE_WARNINGS _Pragma("GCC diagnostic pop")
# endif
static constexpr bool is_linux = WITH_LINUX;
static constexpr bool is_windows = WITH_WINDOWS;

// Remaining configuration
# include <cinttypes>                                                       // to bring any integral type definition in the scope
# include <cstdio>                                                          // to bring all the c standard I/O function (faster than C++ ones)
# include <cstring>                                                         // memset
# include <cmath>
static constexpr bool with_state_output = true;
static constexpr bool with_state_check  = true;
static constexpr bool with_debug_logger = true;
static constexpr bool with_info_logger  = true;
static constexpr bool with_error_logger = true;
static constexpr bool with_checks       = true;
static constexpr bool with_input_print  = true;
static constexpr size_t max_bitstream_bytes = 2048;

# define STRINGIFY_DETAIL(x) #x
# define STRINGIFY(x) STRINGIFY_DETAIL(x)
# define Check(condition) if constexpr (with_checks) {\
  if (LIKELY(!(condition))) {\
    fprintf(stderr, "FATAL: condition failure %s at %s:%i(%s)\n", STRINGIFY(condition), __FILE__, __LINE__, __PRETTY_FUNCTION__);\
    TRAP;\
  }\
}
# define CheckMsg(condition, ...) if constexpr (with_checks) {\
  if (LIKELY(!(condition))) {\
    fprintf(stderr, "FATAL: condition failure %s at %s:%i(%s)\n    ", STRINGIFY(condition), __FILE__, __LINE__, __PRETTY_FUNCTION__);\
    fprintf(stderr, __VA_ARGS__);\
    TRAP;\
  }\
}
namespace logger {
  template<typename... Args> void debug( const char* format, const Args&... args ) { if constexpr (with_debug_logger) fprintf( stderr, format, args... ); }
  template<typename... Args> void info( const char* format, const Args&... args ) { if constexpr (with_info_logger) fprintf( stderr, format, args... ); }
  template<typename... Args> void error( const char* format, const Args&... args ) { if constexpr (with_error_logger) fprintf( stderr, format, args... ); }
}
// < end of general configuration

// Customize this interface to match the game rules.
struct Output {
  void finish() {
    if constexpr(is_codingame) {fflush(stdout);}
  }
};
