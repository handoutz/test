//
// Created by Vince Matonis on 4/2/18.
//

#include "vest_common.h"

extern VTestRunner vest_runner;

#include <memory>

void VTestSpec::run_all() {
    vest_runner.output("Running Spec %s..\n", m_desc.c_str());
    auto start = std::chrono::system_clock::now();
    for (auto vt : m_spec) {
        vest_runner.output("\t'%s'... ", vt->m_desc.c_str());
        try {
            auto dur = vest_runner.run(vt);
            vest_runner.output("\t\033[1;32mSUCCESS!\033[0m %lfms %s\n", dur.count() * 1000, vt->m_desc.c_str());
        } catch (VTestException &e) {
            vest_runner.output("\t\033[1;31mFAIL!\033[0m %s\n", e.as_str().c_str());
        }
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> dur = end - start;
    vest_runner.output("Spec %s took %lfms", m_desc.c_str(), dur.count() * 1000);
}

std::chrono::duration<double> VTestRunner::run(VTestCase *tcase) {
    try {
        auto start = std::chrono::system_clock::now();
        tcase->run();
        auto end = std::chrono::system_clock::now();
        return end - start;
    } catch (VTestException &e) {
        throw e;
    } catch (std::exception &e) {
        throw VTestException(e.what(), HERE_LOC());
    }
}

void VTestRunner::output(text fmt, ...) {
    va_list l;
    va_start(l, fmt);
    vprintf(fmt.c_str(), l);
    //printf("\n");
    va_end(l);
}