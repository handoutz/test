//
// Created by Vince Matonis on 4/2/18.
//
#include "vest_defs.h"

#ifndef VTEST_VEST_COMMON_H
#define VTEST_VEST_COMMON_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <sstream>
#include "vest_spec.h"


class VTestRunner {
public:
    list<VTestSpec *> m_specs;
    VTestOutputter m_outs;

    ~VTestRunner() {
        for (auto vts :m_specs)
            delete vts;
    }

    VTestSpec *new_spec(text name) {
        auto vts = new VTestSpec(name, &m_outs);
        m_specs.push_back(vts);
        return vts;
    }

    void run_all_specs() {
        for (auto spec:m_specs)
            spec->run_all([](auto c) {
                try {
                    auto start = std::chrono::system_clock::now();
                    c->run();
                    auto end = std::chrono::system_clock::now();
                    return end - start;
                } catch (VTestException &e) {
                    throw e;
                } catch (std::exception &e) {
                    throw VTestException(e.what(), false, HERE_LOC());
                }
            });
    }
};


#endif //VTEST_VEST_COMMON_H
