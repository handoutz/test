# VTest C++ Testing 'Framework'

I got bored and made this. Usage is simple, just include the `dist/vest.h` header and use vest_runner as below: 
```C++
#include "dist/vest.h"

int main() {
    vest_runner.new_spec("Basic acceptance testing")
            ->add("should pass", []() {
                EXPECT(true);
            })
            ->add("should fail", []() {
                EXPECT(false);
            })
            ->add("catch exceptions", []() {
                throw std::runtime_error("exceptional!");
            });
    SPEC("Basic macro")
        CASE("should pass", { EXPECT(true); });
        CASE("should fail", { EXPECT(false); });
    ENDSPEC;
    vest_runner.run_all_specs();
    return 0;
}
```
