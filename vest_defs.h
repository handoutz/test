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
#endif //VTEST_VEST_DEFS_H
