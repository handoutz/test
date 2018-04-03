#include "vest.h"

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
    vest_runner.run_all_specs();
    return 0;
}