#pragma once

#include <string>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;

string salt();
string sha224(string &data);
