//
// Created by Vince Matonis on 4/2/18.
//

#ifndef VTEST_VEST_DEFS_H
#define VTEST_VEST_DEFS_H

#include <string>
#include <vector>

using text = std::string;
template<typename T>
using list = std::vector<T>;

#include <functional>

typedef std::function<void()> VTestRunnable;


#define HERE_LOC() location(__FILE__, __LINE__)

#include <sstream>

struct location {
    const text file;
    const int line;

    location(text file_name, int line_num)
            : file(file_name), line(line_num) {}

    const text as_str() const {
        std::stringstream streem;
        streem << file << ":" << line;
        return streem.str();
    }
};

class VTestException : std::runtime_error {
public:
    const text what;
    location where;

    ~VTestException() throw() {}

    VTestException(text desc, location loc)
            : what(desc), where(loc), std::runtime_error(as_str()) {
    }

    const text as_str() {
        std::stringstream stream;
        stream << "Exception '" << what << "' thrown by " << where.as_str();
        return stream.str();
    }
};

class VTestOutputter {
public:
    void output(text fmt, ...) {
        va_list l;
        va_start(l, fmt);
        vprintf(fmt.c_str(), l);
        //printf("\n");
        va_end(l);
    };
};

#endif //VTEST_VEST_DEFS_H
//
// Created by Vince Matonis on 4/2/18.
//


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
//
// Created by Vince Matonis on 4/2/18.
//

#ifndef VTEST_VEST_COMMON_H
#define VTEST_VEST_COMMON_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <sstream>


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
                    throw VTestException(e.what(), HERE_LOC());
                }
            });
    }
};


#endif //VTEST_VEST_COMMON_H
#ifndef VTEST_VEST_H
#define VTEST_VEST_H


VTestRunner vest_runner;
#define EXPECT(expr) if(!(expr)) throw VTestException("problem", HERE_LOC())
#define VEST_RUNNER vest_runner

#define SPEC(desc) {auto cur_spec = VEST_RUNNER.new_spec(desc);
#define CASE(desc, blk) cur_spec->add(desc, []()blk)
#define ENDSPEC }


#endif //VTEST_VEST_H
