#include "error.h"

// Конструктор
VClientError::VClientError(const string& errorName, const string& errorMsg, const string& funcName) {
    this->errorName = errorName;
    this->errorMsg = errorMsg;
    this->funcName = funcName;
}

// Переопределение метода what() для получения сообщения об ошибке
const char* VClientError::what() const noexcept {
    this->fullMsg = "Error: " + errorName + " - " + errorMsg + " (Function: " + funcName + ")";
    return fullMsg.c_str();
}   

// Метод для получения имени ошибки
string VClientError::getErrorName() const {
    return this->errorName;
}

// Метод для получения сообщения об ошибке
string VClientError::getErrorMsg() const {
    return this->errorMsg;
}

// Метод для получения имени функции, в которой произошла ошибка
string VClientError::getFuncName() const {
    return this->funcName;
}
