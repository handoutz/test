#ifndef VTEST_VEST_H
#define VTEST_VEST_H

#include "vest_common.h"

VTestRunner vest_runner;
#define EXPECT(expr) if(!(expr)) throw VTestException("problem", HERE_LOC())
#define VEST_RUNNER vest_runner

#define SPEC(desc) {auto cur_spec = VEST_RUNNER.new_spec(desc);
#define CASE(desc, blk) cur_spec->add(desc, []()blk)
#define ENDSPEC }


#endif //VTEST_VEST_H
