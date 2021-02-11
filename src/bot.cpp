/** This file is parsed by a script to produce a single file source for CodinGame.
 * Every # include <...> are kept as is, while all # include "..." are replaced with the content
 * of the file. To simplify the merge process, put definitions in headers.*/
# include "configuration.h"

int main() {
  configuration::initialize();
  // Write your main loop here
  return 0;
}
