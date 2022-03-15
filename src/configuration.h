// # define CG_ARENA           // define this symbol for the release version in CodinGame arena
# ifdef CG_ARENA
// Try to improve the performance of the bot by helping the compiler to understand we want optimizations
#  pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")
#  pragma GCC option("arch=native","tune=native","no-zero-upper")
#  pragma GCC target("avx")
#  define TRAP __builtin_trap()// function to call when something unexpected happen in the arena
# else
# ifdef _WIN32
#  define _CRT_SECURE_NO_WARNINGS
# endif
#  include <csignal>
#  define HAS_DEBUG_LOG        // allow logger::debug(...) commands to output text in stderr
#  define HAS_INFO_LOG         // allow logger::info(...) commands to output text in stderr
#  define HAS_CHECKS           // all Check(...), Expects(...), and Ensures(...) commands are kept in the produced binary
#  define PROFILE              // allow the profiler to collect and print statistics
#  ifdef _WIN32
#   define TRAP __debugbreak()
#  else
#   define TRAP raise( SIGTRAP )// send this signal when something unexpected happen
#  endif
# endif

# define MEMORY_MEGA_BYTES 500 // how much memory to keep in the local memory handler
# define BITSTREAM_BYTES 2048  // how much memory to use for bit streams
# include <cinttypes>          // to bring any integral type definition in the scope

namespace configuration {
  void initialize() noexcept {}// call this to make sure all static variables are initialized
}
