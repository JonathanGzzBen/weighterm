#ifndef SRC_WEIGHTERM_CLI_H_
#define SRC_WEIGHTERM_CLI_H_
#include <string>

#include "src/weighterm_data.h"

bool registerWeight(WeightermData* data, std::string weightString);
bool listWeights(WeightermData* data);
#endif  // SRC_WEIGHTERM_CLI_H_
