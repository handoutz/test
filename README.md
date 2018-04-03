# VTest C++ Testing 'Framework'
## Intro
I got bored and made this. Usage is simple, just include the `dist/vest.h` header and use the macros as below: 
```C++
#include "dist/vest.h"

int main() {
    SPEC("EXPECT macro")
        CASE("should pass", { EXPECT(true); });
        CASE("should fail", { EXPECT(false); });
    ENDSPEC;
    SPEC("EXPECT_TRUE")
        CASE("expect true pass", { EXPECT_TRUE(true); });
        CASE("expect true fail", { EXPECT_TRUE(false); });
    ENDSPEC;
    SPEC("EXPECT_FALSE")
        CASE("expect false pass", { EXPECT_FALSE(false); });
        CASE("expect false fail", { EXPECT_FALSE(true); });
    ENDSPEC;
    SPEC("EXPECT_EQ")
        CASE("expect eq pass", { EXPECT_EQ(1, 1); });
        CASE("expect eq fail", { EXPECT_EQ(2, 1); });
    ENDSPEC;
    SPEC("EXPECT_NEQ")
        CASE("expect neq pass", { EXPECT_NEQ(2, 1); });
        CASE("expect neq fail", { EXPECT_NEQ(1, 1); });
    ENDSPEC;
    vest_runner.run_all_specs();
    return 0;
}
```
## Assertion Macros
- `EXPECT_TRUE(expr)` expects that (expr) evaluates to true
- `EXPECT_FALSE(expr)` expects that (expr) evaluates to false
- `EXPECT_EQ(expr1, expr2)` expects that (expr1==expr2) evaluates to true
- `EXPECT_NEQ(expr1, expr2)` expects that (expr1!=expr2) evaluates to true
