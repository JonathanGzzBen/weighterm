#ifndef SRC_WEIGHTERM_CLI_H_
#define SRC_WEIGHTERM_CLI_H_
#include <string>

#include "src/weighterm_data.h"

bool RegisterWeight(WeightermData* data, const std::string& weight_string);
bool ListWeights(const WeightermData* weighterm_data);
#endif  // SRC_WEIGHTERM_CLI_H_
