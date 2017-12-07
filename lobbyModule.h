#pragma once

#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "dataStructures.h"
#include "stringUtil.h"

using namespace std;

class lobby : public Module{
    public:
        lobby();
        string start(string module);
        string start();
        string instructions();
        string runCommand(vector<string> words, int arity);
};