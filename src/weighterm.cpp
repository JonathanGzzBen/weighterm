#include <docopt/docopt.h>
#include <sqlite3.h>

#include <exception>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#include "src/data_exception.h"
#include "src/weighterm_cli.h"
#include "src/weighterm_data.h"
#include "src/weighterm_data_sqlite.h"

const char USAGE[] =
    R"(weighterm. Weight tracking terminal application

    Usage:
      weighterm register <weight>
      weighterm list
      weighterm (-h | --help)
      weighterm --version

    Options:
      -h --help     Show this screen.
      --version     Show version.
)";

int main(int argc, char **argv) {
  std::map<std::string, docopt::value> args =
      docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "weighterm 0.1");
  for (const auto &arg : args) {
    std::cout << arg.first << " " << arg.second << std::endl;
  }
  std::unique_ptr<WeightermData> data;
  try {
    data = std::make_unique<WeightermDataSqlite>();
  } catch (DataException &e) {
    std::cout << e.what() << std::endl;
  }
  if (args.at("<weight>")) {
    registerWeight(data.get(), args.at("<weight>").asString());
  } else if (args.at("list")) {
    listWeights(data.get());
  }
  return 0;
}
