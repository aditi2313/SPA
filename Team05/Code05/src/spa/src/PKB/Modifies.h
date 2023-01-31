#include <iostream>
#include <vector>

using namespace std;

#ifndef SPA_MODIFIES_H
#define SPA_MODIFIES_H

namespace pkb {
    class Modifies {
    public:
        int line;
        vector<string> variable;
    };

#endif //SPA_MODIFIES_H
}