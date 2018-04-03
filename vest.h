#ifndef VTEST_VEST_H
#define VTEST_VEST_H

#include "vest_common.h"

VTestRunner vest_runner;
#define EXPECT(expr) {auto _ = (expr); if(!_) throw VTestException("EXPECT", _, HERE_LOC());}
#define EXPECT_TRUE(expr) {bool _=(expr);if(_!=true) throw VTestException("EXPECT_TRUE",_, HERE_LOC());}
#define EXPECT_FALSE(expr) {bool _=(expr);if(_!=false) throw VTestException("EXPECT_FALSE",_, HERE_LOC());}
#define EXPECT_EQ(expr1, expr2){bool _ = (expr1)==(expr2); if(!_)throw VTestException("EXPECT_FALSE",_, HERE_LOC());}
#define EXPECT_NEQ(expr1, expr2){bool _ = (expr1)!=(expr2); if(!_)throw VTestException("EXPECT_FALSE",_, HERE_LOC());}
#define EXPECT_
#define VEST_RUNNER vest_runner

#define SPEC(desc) {auto cur_spec = VEST_RUNNER.new_spec(desc);
#define CASE(desc, blk) cur_spec->add(desc, []()blk)
#define ENDSPEC }


#endif //VTEST_VEST_H
