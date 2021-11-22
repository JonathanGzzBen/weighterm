#include <sqlite3.h>

#include <CLI/CLI.hpp>
#include <exception>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#include "spdlog/spdlog.h"
#include "src/data_exception.h"
#include "src/weighterm_cli.h"
#include "src/weighterm_data.h"
#include "src/weighterm_data_sqlite.h"

int main(int argc, char **argv) {
  CLI::App cli_global{"weighterm 0.1"};
  auto &register_command = *cli_global.add_subcommand(
      "register", "Register a new weight measurement");
  double weight;
  register_command.add_option("weight", weight, "Weight to register")
      ->required();
  auto const &list_command =
      *cli_global.add_subcommand("list", "List registered weight measurements");
  CLI11_PARSE(cli_global, argc, argv)
  std::unique_ptr<WeightermData> data;
  try {
    data = std::make_unique<WeightermDataSqlite>();
  } catch (const DataException &e) {
    spdlog::error(e.what());
  }
  if (register_command) {
    registerWeight(data.get(), std::to_string(weight));
  }
  if (list_command) {
    listWeights(data.get());
  }
  return 0;
}
