#include <iostream>

#include "docopt.h"

const char USAGE[] =
    R"(weighterm. Weight tracking terminal application

    Usage:
      weighterm register <weight>
      weighterm (-h | --help)
      weighterm --version

    Options:
      -h --help     Show this screen.
      --version     Show version.
)";

int main(int argc, char** argv) {
  std::map<std::string, docopt::value> args =
      docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "weighterm 0.1");
  for (auto const& arg : args) {
    std::cout << arg.first << " " << arg.second << std::endl;
  }
  if (args.at("<weight>")) {
    std::cout << "Registering weight" << std::endl;
  }
  return 0;
}
