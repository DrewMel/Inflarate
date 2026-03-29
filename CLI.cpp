#include <iostream>
#include <string>
#include "CLI.h"




CLI::CLI() {
    commands_["add"] = &CLI::CmdAdd;
    commands_["exit"] = &CLI::CmdExit;
}

void CLI::run()
{
    bRunning = true;
    std::string line;

    while (bRunning)
    {
        std::cout << "> ";

        if (!std::getline(std::cin, line)) break;

        auto it = commands_.find(line);
        if (it != commands_.end())
        {
            auto method = it->second;
            (this->*method)();
        }
        else
        {
            std::cout << "Unknown command: " << line << std::endl;
        }
    }
}

void CLI::CmdAdd()
{
    auto store = ask<std::string>("Store name");
    if (!store) return;

    auto product = ask<std::string>("Product name");
    if (!product) return;

    auto price = askMoney();
    if (!price) return;

    auto discount = ask<int>("Discount %", 0);

    std::cout << "\n  Added:\n";

    std::cout << '\t' << *store << "\n";
    std::cout << '\t' << *product << "\n";
    std::string strPrice = Money2String(*price);
    std::cout << '\t' << strPrice << "\n";
    std::cout << '\t' << *discount << "\n";
}
void CLI::CmdExit()
{
    bRunning = false;
    std::cout << "< App has been closed!" << std::endl;
}