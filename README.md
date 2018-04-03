# VTest C++ Testing 'Framework'

I got bored and made this

```C++
#include "vest.h"

int main() {
    vest_runner.new_spec("lol")->add([]() {
        EXPECT(true);
    }, "should pass")->add([]() {
        EXPECT(false);
    }, "should fail");
    vest_runner.run_all_specs();
    return 0;
}
```
