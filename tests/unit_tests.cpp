/** I recommend catch2 (https://github.com/catchorg/Catch2) to write your unit tests in c++.
 *
 * Once installed and include directories set in the CMakeLists.txt file, you can write the following in this file:
 * #define CATCH_CONFIG_MAIN
 * #include "catch.hpp"
 *
 * Then you can write one .cpp file by unit you want to test and add those files as dependencies in the CMakeLists.txt:
 * add_executable(unit_tests "tests/unit_tests.cpp" "tests/unit_001.cpp" "tests/unit_002.cpp")
 */

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  return 0; 
}
