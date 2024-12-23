#pragma once

#include <string>
#include <exception>

using namespace std;

class VClientError : public exception {
public:
    VClientError(const string& errorName, const string& errorMsg, const string& funcName);
    const char* what() const noexcept override;
    string getErrorName() const;
    string getErrorMsg() const;
    string getFuncName() const;

private:
    string errorName;
    string errorMsg;
    string funcName;
    mutable string fullMsg;
};
