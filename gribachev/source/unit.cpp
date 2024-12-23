#include "error.h"
#include "vclient.h"
#include "rw.h"
#include "cmd.h"
#include "sha224.h"

#include "UnitTest++/UnitTest++.h"
#include <fstream>
#include <cstdio> // для функции remove

// Тесты для CMDParser
TEST(CMDParser_DefaultValues)
{
    CMDParser parser;
    CHECK_EQUAL("./in.txt", parser.getIn());
    CHECK_EQUAL("./out.txt", parser.getOut());
    CHECK_EQUAL("./cfg.txt", parser.getCfg());
    CHECK_EQUAL("127.0.0.1", parser.getAddr());
    CHECK_EQUAL(33333, parser.getPort());
}

TEST(CMDParser_ParseArgs)
{
    CMDParser parser;
    const char *argv[] = {"program", "-i", "input.txt", "-o", "output.txt", "-c", "config.txt", "-a", "192.168.0.1", "-p", "12345"};
    parser.parse(11, const_cast<char **>(argv));
    CHECK_EQUAL("input.txt", parser.getIn());
    CHECK_EQUAL("output.txt", parser.getOut());
    CHECK_EQUAL("config.txt", parser.getCfg());
    CHECK_EQUAL("192.168.0.1", parser.getAddr());
    CHECK_EQUAL(12345, parser.getPort());
}

TEST(CMDParser_InvalidArgs)
{
    CMDParser parser;
    const char *argv[] = {"program", "--in"};
    CHECK_THROW(parser.parse(2, const_cast<char **>(argv)), VClientError);
}

// Тесты для ReadWrite
TEST(ReadWrite_Initialization)
{
    string inVec = "input.txt";
    string outVec = "output.txt";
    string cfg = "config.txt";
    ReadWrite rw(inVec, outVec, cfg);
    CHECK_EQUAL("input.txt", rw.getIn());
    CHECK_EQUAL("output.txt", rw.getOut());
    CHECK_EQUAL("config.txt", rw.getCfg());
}

TEST(ReadWrite_WriteVec)
{
    string inVec = "input.txt";
    string outVec = "output.txt";
    string cfg = "config.txt";
    ReadWrite rw(inVec, outVec, cfg);

    vector<uint32_t> data = {1, 2, 3, 4};
    rw.writeVec(data);

    // Чтение файла и проверка его содержимого
    ifstream infile(outVec);
    CHECK(infile.is_open());

    uint32_t vec_size;
    infile >> vec_size;
    CHECK_EQUAL(data.size(), vec_size);

    vector<uint32_t> read_data(vec_size);
    for (size_t i = 0; i < vec_size; ++i)
    {
        infile >> read_data[i];
    }
    CHECK_ARRAY_EQUAL(data, read_data, vec_size);

    infile.close();

    // Удаление файла после теста
    remove(outVec.c_str());
}

TEST(ReadWrite_WriteVec_FileError)
{
    string inVec = "input.txt";
    string outVec = "/invalid/path/output.txt"; // Неверный путь
    string cfg = "config.txt";
    ReadWrite rw(inVec, outVec, cfg);

    vector<uint32_t> data = {1, 2, 3, 4};
    CHECK_THROW(rw.writeVec(data), VClientError);
}

TEST(ReadWrite_ReadVec)
{
    string inVec = "input.txt";
    string outVec = "output.txt";
    string cfg = "config.txt";

    // Запись тестовых данных в файл
    ofstream outfile(inVec);
    outfile << "2\n";
    outfile << "3\n1 2 3\n";
    outfile << "2\n4 5\n";
    outfile.close();

    ReadWrite rw(inVec, outVec, cfg);
    vector<vector<uint32_t>> vectors = rw.readVec();

    CHECK_EQUAL(2, vectors.size());
    CHECK_ARRAY_EQUAL(vector<uint32_t>({1, 2, 3}), vectors[0], 3);
    CHECK_ARRAY_EQUAL(vector<uint32_t>({4, 5}), vectors[1], 2);

    // Удаление файла после теста
    remove(inVec.c_str());
}

TEST(ReadWrite_ReadVec_FileError)
{
    string inVec = "/invalid/path/input.txt"; // Неверный путь
    string outVec = "output.txt";
    string cfg = "config.txt";
    ReadWrite rw(inVec, outVec, cfg);

    CHECK_THROW(rw.readVec(), VClientError);
}

TEST(ReadWrite_ReadCfg) {
    string inVec = "input.txt";
    string outVec = "output.txt";
    string cfg = "config.txt";

    // Запись тестовых данных в файл конфигурации
    ofstream cfgfile(cfg);
    cfgfile << "user:password\n";
    cfgfile.close();

    ReadWrite rw(inVec, outVec, cfg);
    array<string, 2> configArray = rw.readCfg();

    CHECK_EQUAL("user", configArray[0]);
    CHECK_EQUAL("password", configArray[1]);

    // Удаление файла после теста
    remove(cfg.c_str());
}

TEST(ReadWrite_ReadCfg_ThrowOnInvalidFormat) {
    string inVec = "input.txt";
    string outVec = "output.txt";
    string cfg = "config_invalid.txt";

    // Запись неправильных данных в файл конфигурации (без символа ':')
    ofstream cfgfile(cfg);
    cfgfile << "userpassword\n";
    cfgfile.close();

    ReadWrite rw(inVec, outVec, cfg);
    CHECK_THROW(rw.readCfg(), VClientError);
    // Удаление файла после теста
    remove(cfg.c_str());
}

TEST(ReadWrite_ReadCfg_FileError)
{
    string inVec = "input.txt";
    string outVec = "output.txt";
    string cfg = "/invalid/path/config.txt"; // Неверный путь
    ReadWrite rw(inVec, outVec, cfg);

    CHECK_THROW(rw.readCfg(), VClientError);
}

// Тесты для функций генерации соли
TEST(GetSalt)
{
    CHECK(salt() != salt());
}

// Тесты для функций хеширования
TEST(SHA224_Hashing)
{
    string data = "hello";
    string hash = sha224(data);
    CHECK_EQUAL("EA09AE9CC6768C50FCEE903ED054556E5BFC8347907F12598AA24193", hash);
}
// Тесты для функций хеширования
TEST(SHA224_EmptyString)
{
    string data = "";
    string hash = sha224(data);
    CHECK_EQUAL("D14A028C2A3A2BC9476102BB288234C415A2B01F828EA62AC5B3E42F", hash);
}

TEST(SHA224_LongString)
{
    string data = "The quick brown fox jumps over the lazy dog";
    string hash = sha224(data);
    CHECK_EQUAL("730E109BD7A8A32B1CB9D9A09AA2325D2430587DDBC0C38BAD911525", hash);
}

TEST(SHA224_SpecialCharacters)
{
    string data = "!@#$%^&*()_+-=";
    string hash = sha224(data);
    CHECK_EQUAL("56F6D3A6923FECA387FDA82DC2BD1BA3534C609936A266F0D1600388", hash);
}

TEST(SHA224_NumericString)
{
    string data = "1234567890";
    string hash = sha224(data);
    CHECK_EQUAL("B564E8A5CF20A254EB34E1AE98C3D957C351CE854491CCBEAEB220EA", hash);
}

TEST(SHA224_SameInputDifferentCase)
{
    string data1 = "HelloWorld";   
    string data2 = "helloworld";
    string hash1 = sha224(data1);
    string hash2 = sha224(data2);
    CHECK(hash1 != hash2);
}

TEST(SHA224_LargeInput)
{
    string data(1000, 'a'); // строка из 1000 символов 'a'
    string hash = sha224(data);
    CHECK_EQUAL("4E8F0CE90B64661A2B5E84BE6D93A7D9B76871062F1814433D04A03D", hash);
}

// Тесты для VClient
TEST(VClient_Initialization)
{
    array<string, 2> conf = {"user", "password"};
    VClient client("127.0.0.1", 33333, conf);
    CHECK_EQUAL("127.0.0.1", client.getAddr());
    CHECK_EQUAL(33333, client.getPort());
    CHECK(conf[0] == "user");
    CHECK(conf[1] == "password");
}

int main(int argc, char *argv[])
{
    return UnitTest::RunAllTests();
}
