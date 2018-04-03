#ifndef VTEST_VEST_H
#define VTEST_VEST_H

#include "vest_common.h"

VTestRunner vest_runner;
#define EXPECT(expr) if(!(expr)) throw VTestException("problem", HERE_LOC())
#endif //VTEST_VEST_H
