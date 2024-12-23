#include "rw.h"

// Конструктор
ReadWrite::ReadWrite(string &inVec, string &outVec, string &cfg)
{
    this->in = inVec;
    this->out = outVec;
    this->cfg = cfg;
}

// Метод для получения пути входного файла
string ReadWrite::getIn()
{
    return this->in;
}

// Метод для получения пути выходного файла
string ReadWrite::getOut()
{
    return this->out;
}

// Метод для получения пути файла конфигурации
string ReadWrite::getCfg()
{
    return this->cfg;
}

// Метод для записи
void ReadWrite::writeVec(const vector<uint32_t> &data)
{
    ofstream outfile(this->out);
    if (!outfile.is_open())
    {
        throw VClientError("FileError", "Unable to open output file", __func__);
    }
    uint32_t vec_size = data.size();
    outfile << vec_size << "\n";
    for (size_t i = 0; i < data.size(); ++i)
    {
        outfile << data[i];
        if (i < data.size() - 1)
        {
            outfile << " ";
        }
    }
    outfile << "\n";
    if (!outfile)
    {
        throw VClientError("FileWriteError", "Error writing to output file", __func__);
    }
    outfile.close();

    // Вывод записанных данных
    cout << "log: write vector complete.\nvec: ";
    printVector(data);
}

// Метод для чтения
vector<vector<uint32_t>> ReadWrite::readVec()
{
    ifstream infile(this->in);
    if (!infile.is_open())
    {
        throw VClientError("FileError", "Unable to open input file", __func__);
    }

    string line;
    uint32_t num_vectors;
    vector<vector<uint32_t>> vectors;

    // Чтение количества векторов
    if (getline(infile, line))
    {
        stringstream ss(line);
        ss >> num_vectors;
    }
    else
    {
        throw VClientError("FileReadError", "Error reading number of vectors", __func__);
    }

    // Чтение каждого вектора
    for (uint32_t i = 0; i < num_vectors; ++i)
    {
        vector<uint32_t> vec;
        uint32_t vec_size;

        // Чтение размера вектора
        if (getline(infile, line))
        {
            stringstream ss(line);
            ss >> vec_size;
        }
        else
        {
            throw VClientError("FileReadError", "Error reading vector size", __func__);
        }

        // Чтение значений вектора
        if (getline(infile, line))
        {
            stringstream ss(line);
            uint32_t value;
            for (uint32_t j = 0; j < vec_size; ++j)
            {
                if (!(ss >> value))
                {
                    throw VClientError("FileReadError", "Error reading vector values", __func__);
                }
                vec.push_back(value);
            }
        }
        else
        {
            throw VClientError("FileReadError", "Error reading vector values", __func__);
        }

        vectors.push_back(vec);
    }

    infile.close();

    // Вывод считанных данных
    cout << "log: read vectors comlete.\nvec: ";
    printVectors(vectors);
    return vectors;
}

// Метод для чтения конфигурации
array<string, 2> ReadWrite::readCfg()
{
    ifstream infile(this->cfg);
    if (!infile.is_open())
    {
        throw VClientError("FileError", "Unable to open config file", __func__);
    }

    array<string, 2> configArray;
    string line;

    if (getline(infile, line))
    {
        stringstream ss(line);
        if (!(getline(ss, configArray[0], ':') && getline(ss, configArray[1])))
        {
            throw VClientError("FileReadError", "Error reading config data", __func__);
        }
    }
    else
    {
        throw VClientError("FileReadError", "Error reading config file", __func__);
    }

    infile.close();
    cout << "log: read config complete.\n"
         << "cfg: " << configArray[0]
         << ":" << configArray[1] << "\n";
    return configArray;
}

// Функция для вывода вектора uint32_t
void printVector(const vector<uint32_t> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

// Функция для рекурсивного вывода вложенных векторов
void printVectors(const vector<vector<uint32_t>> &vec)
{
    cout << "[";
    if (!vec.empty()) {
        cout << endl;
        for (const auto &subVec : vec) {
            cout << "\t";
            printVector(subVec);
        }
    }
    cout << "]" << endl;
}
