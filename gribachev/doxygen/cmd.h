#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "error.h"

using namespace std;

/**
 * @class CMDParser
 * @brief Класс для анализа командной строки и получения значений аргументов.
 */
class CMDParser {
private:
    string in = "./in.txt"; ///< Путь к входному файлу (по умолчанию: "./in.txt").
    string out = "./out.txt"; ///< Путь к выходному файлу (по умолчанию: "./out.txt").
    string cfg = "./cfg.txt"; ///< Путь к файлу конфигурации (по умолчанию: "./cfg.txt").
    string addr = "127.0.0.1"; ///< Адрес сервера (по умолчанию: "127.0.0.1").
    uint16_t port = 33333; ///< Порт сервера (по умолчанию: 33333).

public:
    /**
     * @brief Конструктор по умолчанию.
     */
    CMDParser() = default;

    /**
     * @brief Получить путь к входному файлу.
     * @return Путь к входному файлу.
     */
    string getIn() const;

    /**
     * @brief Получить путь к выходному файлу.
     * @return Путь к выходному файлу.
     */
    string getOut() const;

    /**
     * @brief Получить путь к файлу конфигурации.
     * @return Путь к файлу конфигурации.
     */
    string getCfg() const;

    /**
     * @brief Получить адрес сервера.
     * @return Адрес сервера.
     */
    string getAddr() const;

    /**
     * @brief Получить порт сервера.
     * @return Порт сервера.
     */
    uint16_t getPort() const;

    /**
     * @brief Разобрать аргументы командной строки и задать соответствующие значения.
     * @param argc Количество аргументов.
     * @param argv Массив аргументов.
     * @throws VClientError В случае неверного аргумента.
     */
    void parse(int argc, char* argv[]);

    /**
     * @brief Показать сообщение о помощи.
     */
    void showHelp() const;
};
