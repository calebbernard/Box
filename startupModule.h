#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "dataStructures.h"
#include "stringUtil.h"

using namespace std;

class Startup : public Module {
    private:
        struct twoString{
            string desc;
            string answer;
        };
        vector<twoString> warmups;
        int counter;
        bool onceBegin;
    public:
        Startup();
        string instructions();
        string begin();
        string warmup();
        string warmup(string attempt);
        string finish();
        string runCommand(vector<string> words, int arity);
};