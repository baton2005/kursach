#pragma once

#include <cstdint>
#include <string>
#include <cstring>
#include <array>
#include <iostream>
#include <vector>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "error.h"
#include "sha224.h"

using namespace std;

class VClient
{
private:
    int sock;
    string addr;
    uint16_t port;
    array<string, 2> conf;

public:
    VClient(string addr, uint16_t port, array<string, 2> conf);
    void conn();
    void stop();
    void auth();
    vector<uint32_t> calc(vector<vector<uint32_t>> data);

    int getSock();
    string getAddr();
    uint16_t getPort();
    array<string, 2> getConf();
};