#include "error.h"
#include "vclient.h"
#include "rw.h"
#include "cmd.h"

/**
 * @brief Главная функция программы.
 * @param argc Количество аргументов.
 * @param argv Массив аргументов.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[])
{
    try
    {
        // Создаем объект парсера командной строки
        CMDParser cmdParser;
        cmdParser.parse(argc, argv);

        // Получаем значения из парсера
        string inFile = cmdParser.getIn();
        string outFile = cmdParser.getOut();
        string cfgFile = cmdParser.getCfg();
        string addr = cmdParser.getAddr();
        uint16_t port = cmdParser.getPort();

        // Создаем объект ReadWrite для работы с файлами
        ReadWrite rw(inFile, outFile, cfgFile);

        // Читаем конфигурацию
        array<string, 2> conf = rw.readCfg();

        // Создаем объект VClient и устанавливаем соединение
        VClient client(addr, port, conf);
        client.conn();

        // Аутентификация
        client.auth();

        // Чтение данных
        vector<vector<uint32_t>> data = rw.readVec();

        // Выполнение вычислений
        vector<uint32_t> result = client.calc(data);

        // Запись результата
        rw.writeVec(result);

        // Завершение соединения
        client.stop();
    }
    catch (const VClientError &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
