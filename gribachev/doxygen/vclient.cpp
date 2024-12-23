#include "vclient.h"

using namespace std;

// Конструктор
VClient::VClient(string addr, uint16_t port, array<string, 2> conf)
{
    this->addr = addr;
    this->port = port;
    this->conf = conf;
    this->sock = -1;
}

// Метод для соединения с сервером
void VClient::conn()
{
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sock < 0)
    {
        throw VClientError("SocketError", "Socket creation error", __func__);
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(this->port);

    if (inet_pton(AF_INET, this->addr.c_str(), &serv_addr.sin_addr) <= 0)
    {
        throw VClientError("AddressError", "Invalid address/ Address not supported", __func__);
    }

    if (connect(this->sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        throw VClientError("ConnectionError", "Connection failed", __func__);
    }

    cout << "Connection to " << this->addr << ":" << this->port << " established." << endl;
}

// Метод для остановки соединения
void VClient::stop()
{
    ::close(this->sock);
    this->sock = -1;
    cout << "Connection closed." << endl;
}

void VClient::auth()
{
    string salt = ::salt(); // Используем функцию salt
    string data = salt + this->conf[1];
    string hash = ::sha224(data); // Используем функцию sha224

    string auth_msg = this->conf[0] + salt + hash;
    if (send(this->sock, auth_msg.c_str(), auth_msg.size(), 0) < 0)
    {
        throw VClientError("SendError", "Failed to send authentication message", __func__);
    }

    char response[1024];
    int response_length = recv(this->sock, response, sizeof(response) - 1, 0);
    if (response_length < 0)
    {
        throw VClientError("ReceiveError", "Failed to receive authentication response", __func__);
    }

    response[response_length] = '\0';
    if (string(response) != "OK")
    {
        throw VClientError("AuthError", "Authentication failed", __func__);
    }

    cout << "log: authentication successful.\n";
}

vector<uint32_t> VClient::calc(vector<vector<uint32_t>> data)
{
    // Передача количества векторов
    uint32_t num_vectors = data.size();
    if (send(this->sock, &num_vectors, sizeof(num_vectors), 0) < 0)
    {
        throw VClientError("SendError", "Failed to send number of vectors", __func__);
    }

    // Передача каждого вектора
    for (const auto &vec : data)
    {
        uint32_t vec_size = vec.size();
        if (send(this->sock, &vec_size, sizeof(vec_size), 0) < 0)
        {
            throw VClientError("SendError", "Failed to send vector size", __func__);
        }
        if (send(this->sock, vec.data(), vec_size * sizeof(uint32_t), 0) < 0)
        {
            throw VClientError("SendError", "Failed to send vector data", __func__);
        }
    }

    // Получение результатов
    vector<uint32_t> results(num_vectors);
    for (uint32_t i = 0; i < num_vectors; ++i)
    {
        if (recv(this->sock, &results[i], sizeof(uint32_t), 0) < 0)
        {
            throw VClientError("ReceiveError", "Failed to receive result", __func__);
        }
    }

    return results;
}

int VClient::getSock()
{
    return this->sock;
}

string VClient::getAddr()
{
    return this->addr;
}

uint16_t VClient::getPort()
{
    return this->port;
}

array<string, 2> VClient::getConf()
{
    return this->conf;
}
