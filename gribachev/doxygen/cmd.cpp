#include "cmd.h"


string CMDParser::getIn() const {
    return this->in;
}

string CMDParser::getOut() const {
    return this->out;
}

string CMDParser::getCfg() const {
    return this->cfg;
}

string CMDParser::getAddr() const {
    return this->addr;
}

uint16_t CMDParser::getPort() const {
    return this->port;
}

void CMDParser::parse(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-a" && i + 1 < argc) {
            this->addr = argv[++i];
        } else if (arg == "-p" && i + 1 < argc) {
            this->port = static_cast<uint16_t>(stoi(argv[++i]));
        } else if (arg == "-i" && i + 1 < argc) {
            this->in = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            this->out = argv[++i];
        } else if (arg == "-c" && i + 1 < argc) {
            this->cfg = argv[++i];
        } else if (arg == "-h") {
            showHelp();
            exit(0);
        } else {
            throw VClientError("ArgumentError", "Invalid argument: " + arg, __func__);
        }
    }
}

void CMDParser::showHelp() const {
    cout << "Usage: program [options]\n"
         << "Options:\n"
         << "  -a <address>    Set the server address (default: 127.0.0.1)\n"
         << "  -p <port>       Set the server port (default: 33333)\n"
         << "  -i <input>      Set the input file path (default: ./in.txt)\n"
         << "  -o <output>     Set the output file path (default: ./out.txt)\n"
         << "  -c <config>     Set the config file path (default: ./cfg.txt)\n"
         << "  -h              Show this help message\n";
}
