#pragma once

#include <string>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;

/**
 * @brief Функция для генерации соли.
 * @return Сгенерированная соль в шестнадцатеричном формате.
 */
string salt();

/**
 * @brief Функция для вычисления SHA-224 хэша от строки данных.
 * @param data Строка данных для хэширования.
 * @return SHA-224 хэш данных в шестнадцатеричном формате.
 */
string sha224(string &data);
