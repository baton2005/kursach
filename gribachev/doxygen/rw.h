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

/**
 * @class ReadWrite
 * @brief Класс для работы с файлами ввода, вывода и конфигурации.
 */
class ReadWrite
{
public:
    /**
     * @brief Конструктор класса ReadWrite.
     * @param inVec Путь к файлу входных данных.
     * @param outVec Путь к файлу выходных данных.
     * @param cfg Путь к файлу конфигурации.
     */
    ReadWrite(string &inVec, string &outVec, string &cfg);

    /**
     * @brief Получить путь к файлу входных данных.
     * @return Путь к файлу входных данных.
     */
    string getIn();

    /**
     * @brief Получить путь к файлу выходных данных.
     * @return Путь к файлу выходных данных.
     */
    string getOut();

    /**
     * @brief Получить путь к файлу конфигурации.
     * @return Путь к файлу конфигурации.
     */
    string getCfg();

    /**
     * @brief Записать данные в файл выходных данных.
     * @param data Вектор данных для записи.
     */
    void writeVec(const vector<uint32_t> &data);

    /**
     * @brief Считать векторы из файла входных данных.
     * @return Вектор векторов, считанных из файла.
     */
    vector<vector<uint32_t>> readVec();

    /**
     * @brief Считать конфигурационные данные из файла конфигурации.
     * @return Массив строк, содержащий конфигурационные данные.
     */
    array<string, 2> readCfg();

private:
    string in;  ///< Путь к файлу входных данных.
    string out; ///< Путь к файлу выходных данных.
    string cfg; ///< Путь к файлу конфигурации.
};

/**
 * @brief Функция для вывода вектора uint32_t.
 * @param vec Вектор для вывода.
 */
void printVector(const vector<uint32_t> &vec);

/**
 * @brief Функция для рекурсивного вывода вложенных векторов.
 * @param vec Вектор векторов для вывода.
 */
void printVectors(const vector<vector<uint32_t>> &vec);
