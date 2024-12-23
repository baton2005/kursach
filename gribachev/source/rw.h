#pragma once

#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <iostream>
#include "error.h"

using namespace std;

class ReadWrite
{
public:
    ReadWrite(string &inVec, string &outVec, string &cfg);
    string getIn();
    string getOut();
    string getCfg();
    void writeVec(const vector<uint32_t> &data);
    vector<vector<uint32_t>> readVec();
    array<string, 2> readCfg();

private:
    string in;
    string out;
    string cfg;
};

void printVector(const vector<uint32_t> &vec);
void printVectors(const vector<vector<uint32_t>> &vec);
