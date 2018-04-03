# VTest C++ Testing 'Framework'

I got bored and made this. Usage is simple, just include the `dist/vest.h` header and use vest_runner as below: 
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
