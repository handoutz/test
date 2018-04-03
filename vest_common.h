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

#define HERE_LOC() location(__FILE__, __LINE__)

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

class VTestRunner {
public:
    list<VTestSpec *> m_specs;

    void output(text fmt, ...);

    ~VTestRunner() {
        for (auto vts :m_specs)
            delete vts;
    }

    std::chrono::duration<double> run(VTestCase *tcase);

    VTestSpec *new_spec(text name) {
        auto vts = new VTestSpec(name);
        m_specs.push_back(vts);
        return vts;
    }

    void run_all_specs() {
        for (auto spec:m_specs)
            spec->run_all();
    }
};



#endif //VTEST_VEST_COMMON_H
