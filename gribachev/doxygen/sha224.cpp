#include "sha224.h"

string salt()
{
    const size_t size = 8;          // размер соли в байтах (64 бита = 8 байт)
    CryptoPP::byte salt[size];      // массив для соли
    AutoSeededRandomPool prng;      //
    prng.GenerateBlock(salt, size); // генерация соли
    string salt_hex;                // строка для соли
    ArraySource(salt, size, true, new HexEncoder(new StringSink(salt_hex), true));

    // Дополнение соли нулями слева до 16 символов
    while (salt_hex.size() < 16)
        salt_hex = "0" + salt_hex;

    return salt_hex;
};

string sha224(string &data)
{
    SHA224 hash_func; // создаем объект хеш-функции
    string hash_hex;

    // формирование хэша и преобразование в шестнадцатеричную строку
    StringSource(data,true,
        new HashFilter(
            hash_func,
            new HexEncoder(
                new StringSink(hash_hex),
                true // Заглавные буквы
                )));

    return hash_hex;
};