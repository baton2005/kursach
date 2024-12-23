#pragma once

#include <string>
#include <exception>

using namespace std;

/**
 * @class VClientError
 * @brief Класс для обработки ошибок клиента.
 */
class VClientError : public exception
{
public:
    /**
     * @brief Конструктор класса VClientError.
     * @param errorName Имя ошибки.
     * @param errorMsg Сообщение об ошибке.
     * @param funcName Имя функции, в которой произошла ошибка.
     */
    VClientError(const string &errorName, const string &errorMsg, const string &funcName);

    /**
     * @brief Получить полное сообщение об ошибке.
     * @return Сообщение об ошибке.
     */
    const char *what() const noexcept override;

    /**
     * @brief Получить имя ошибки.
     * @return Имя ошибки.
     */
    string getErrorName() const;

    /**
     * @brief Получить сообщение об ошибке.
     * @return Сообщение об ошибке.
     */
    string getErrorMsg() const;

    /**
     * @brief Получить имя функции, в которой произошла ошибка.
     * @return Имя функции.
     */
    string getFuncName() const;

private:
    string errorName;       ///< Имя ошибки.
    string errorMsg;        ///< Сообщение об ошибке.
    string funcName;        ///< Имя функции, в которой произошла ошибка.
    mutable string fullMsg; ///< Полное сообщение об ошибке.
};
