#include <iostream>
#include "vest.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    vest_runner.new_spec("lol")->add_tpl([]() {
        EXPECT(true);
    }, "should pass")->add_tpl([]() {
        EXPECT(false);
    }, "should fail");
    vest_runner.run_all_specs();
    return 0;
}