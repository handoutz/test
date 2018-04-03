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
