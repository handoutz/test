//
// Created by Vince Matonis on 4/2/18.
//

#include "vest_defs.h"

#ifndef VTEST_VEST_SPEC_H
#define VTEST_VEST_SPEC_H

class VTestCase {
public:
    text m_desc;
    VTestRunnable run;

    explicit VTestCase(text desc, VTestRunnable runnable)
            : m_desc(desc), run(runnable) {

    }

    virtual ~VTestCase() {

    }
};
#include <chrono>
class VTestSpec {
public:
    list<VTestCase *> m_spec;
    text m_desc;

    explicit VTestSpec(text desc)
            : m_desc(desc) {
    }

    ~VTestSpec() {
        for (auto vt : m_spec)
            delete vt;
    }

    VTestSpec* add(VTestCase *test_case) {
        m_spec.push_back(test_case);
        return this;
    }

    VTestSpec* add_tpl(VTestRunnable runnable, text desc) {
        m_spec.push_back(new VTestCase(desc, runnable));
        return this;
    }

    void run_all();
};


#endif //VTEST_VEST_SPEC_H
