#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "error.h"

using namespace std;

class CMDParser {
private:
    string in = "./in.txt";
    string out = "./out.txt";
    string cfg = "./cfg.txt";
    string addr = "127.0.0.1";
    uint16_t port = 33333;

public:
    CMDParser() = default;

    string getIn() const;
    string getOut() const;
    string getCfg() const;
    string getAddr() const;
    uint16_t getPort() const;

    void parse(int argc, char* argv[]);
    void showHelp() const;
};
