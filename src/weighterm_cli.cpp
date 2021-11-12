#include "src/weighterm_cli.h"

#include <iomanip>
#include <iostream>

bool registerWeight(WeightermData* data, std::string weightString) {
  double weight{0};
  try {
    weight = std::stod(weightString);
  } catch (const std::exception& ex) {
    std::cerr << "Weight must be a numeric value." << std::endl;
    return false;
  }
  auto result{data->RegisterWeight(weight)};
  if (result != DataResult::Ok) {
    std::cerr << "Could not register weight." << std::endl;
    return false;
  }
  return true;
}

bool listWeights(WeightermData* data) {
  auto weight_measures{data->ListWeights()};
  for (const auto& weight : weight_measures) {
    std::cout << "ID: " << std::setw(4) << std::left << weight.get_id()
              << "Weight: " << weight.get_weight() << std::endl;
  }
  return true;
}
