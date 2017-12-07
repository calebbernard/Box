#pragma once

#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "../dataStructures.h"
#include "../stringUtil.h"

using namespace std;

class mabModule : public Module{
    private:
        class mab{
            private:
                int count;
                int max;
                int turnsLeft;
                int startTurns;
                int score;
                vector<int> bandit;
            public:
            mab();
            int getCount();
            int getTurns();
            int getScore();
            // For debug only
            int getChance(int x);
            int pullLever(int x);
            int getBest();
            void reset();
        };
        mab * g;
        int cheaterScore;
    public:
        mabModule();
        string toLobby();
        string reset();
        string pullLever(int lever);
        string getInfo();
        string results();
        string instructions();
        string runCommand(vector<string> words, int arity);
};