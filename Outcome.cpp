// Outcome.cpp : 
/*
* Это наблюдатель за тратами. Предпологается что в его базу данных можно будет
* добавлять информацию о покупках: наименование товара, цену, время, место покупки,
* скидку и тд, затем по надобности извлекать эти данные и всячески работать с ними
*
* Команды для работы с приложением:
* > add                                 - команда начать добавление чека
*   > Enter                             - ввод информации
*   > Esc                               - остановить выполнение команды
* > exit                                - выйти из программы
*
* Как должен выглядеть чек после ввода:
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                       Store: N1                             *
*              Address: mun.Chisinau, bd.Dachia, 47/7         *
*              IDNO: 1004600052987                            *
*              INR N: J4030003136                             *
*       Bon # 115                                             *
*       Item Numbers: 6                                       *
*                                                             *
*  Items:                                                     *
*   Prajitura DE P                                            *
*       0.600 x 153.00= 91.80                                 *
*   Cafea NESCAFE                                             *
*       1     x 109.80= 109.80                                *
*   Ambalaj bio                                               *
*       1     x 1.50= 1.50                                    *
*   Tea MomentsC                                              *
*       1     x 45.00= 45.00                                  *
*
*               ---------------------                         *
* TOTAL LEI     416.92                                        *
* TIMESTAMP     04-03-2026 12:48:00                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*
*/

#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>
#include <conio.h>
#include <optional>

std::optional<std::string>askString(
    std::string const& prompt,
    std::optional<std::string> const& def = std::nullopt)
{
    std::cout << prompt;

    if (def)
    {
        std::cout << " [" << *def << ']';
    }

    std::cout << "\n";

    std::string Line;

    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();

            if (ch == 27) // Esc
            {
                std::cout << "Canseled" << std::endl;
                return std::nullopt;
            }
            else if (ch == '\r') // Enter
            {
                std::cout << std::endl;
                if (Line.empty() && def)
                {
                    return def;
                }
                return Line;
            }
            else if (ch == '\b') //Backspace
            {
                if (!Line.empty())
                {
                    Line.pop_back();
                    std::cout << "\b \b";
                }
            }
            else
            {
                Line.push_back(ch);
                std::cout << ch;
            }
        }
    }
    return Line;
}

class receipt
{
public:

private:
    std::string StoreName;
    std::string address;
    int IDNO;
    std::string INR;
    int bon_number;
    int items_number;
    //items
    int total;
    std::chrono::sys_seconds tmStamp;
};

class item
{
private:
    std::string name;
    //std::string alias???
    int price_unit;
    int amount;
    bool discount;
    int discounted_price;
    int discount_percent;;
};

class CLI
{
public:
    CLI() {
        commands_["add"] = &CLI::CmdAdd;
        commands_["exit"] = &CLI::CmdExit;
    }

    void run()
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
private:
    void CmdAdd()
    {

    }
    void CmdExit()
    {
        bRunning = false;
        std::cout << "< App has been closed!" << std::endl;
    }
private:
    bool bRunning;
    using CommandMethod = void(CLI::*)(void);
    std::unordered_map<std::string, CommandMethod> commands_;
};





int main()
{
    CLI cli;
    cli.run();

    return 0;
}

