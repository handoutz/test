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
    VTestOutputter *m_runner;

    explicit VTestSpec(text desc, VTestOutputter *runner)
            : m_desc(desc), m_runner(runner) {
    }

    ~VTestSpec() {
        for (auto vt : m_spec)
            delete vt;
    }

    VTestSpec *add(text desc, VTestRunnable runnable) {
        m_spec.push_back(new VTestCase(desc, runnable));
        return this;
    }

    void run_all(std::function<std::chrono::duration<double>(VTestCase *)> run) {
        m_runner->output("Running Spec %s..\n", m_desc.c_str());
        auto start = std::chrono::system_clock::now();
        for (auto vt : m_spec) {
            m_runner->output("\t'%s'... ", vt->m_desc.c_str());
            try {
                auto dur = run(vt);
                m_runner->output("\t\033[1;32mSUCCESS!\033[0m %lfms %s\n", dur.count() * 1000, vt->m_desc.c_str());
            } catch (VTestException &e) {
                m_runner->output("\t\033[1;31mFAIL!\033[0m %s\n", e.as_str().c_str());
            }
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> dur = end - start;
        m_runner->output("Spec %s took %lfms", m_desc.c_str(), dur.count() * 1000);
    }

};


#endif //VTEST_VEST_SPEC_H
