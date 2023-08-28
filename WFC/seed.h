#ifndef SEED_H
#define SEED_H

#include <time.h>

namespace wfc {

#define SEED() std::cout << "Seed: " << seed << std::endl

unsigned int seed = time(NULL);

};  // namespace wfc

#endif