// # define CG_ARENA           // define this symbol for the release version in CodinGame arena
# ifdef CG_ARENA
// Try to improve the performance of the bot by helping the compiler to understand we want optimizations
#  pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")
#  pragma GCC option("arch=native","tune=native","no-zero-upper")
#  pragma GCC target("avx")
#  define TRAP __builtin_trap()// function to call when something unexpected happen in the arena
# else
#  include <csignal>
#  define HAS_DEBUG_LOG        // allow logger::debug(...) commands to output text in stderr
#  define HAS_INFO_LOG         // allow logger::info(...) commands to output text in stderr
#  define HAS_CHECKS           // all Check(...), Expects(...), and Ensures(...) commands are kept in the produced binary
#  define PROFILE              // allow the profiler to collect and print statistics
#  define TRAP raise( SIGTRAP )// send this signal when something unexpected happen
// #  define LOG_INPUT
# endif

# define MEMORY_MEGA_BYTES 500 // how much memory to keep in the local memory handler 

# include <cinttypes>          // to bring any integral type definition in the scope

namespace configuration {
  void initialize() noexcept {}// call this to make sure all static variables are initialized
}
