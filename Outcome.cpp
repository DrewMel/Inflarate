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
#include <charconv>

std::optional<std::string>askString(
    std::string const& prompt,
    std::optional<std::string> const& def = std::nullopt)
{
    std::cout << "< " << prompt << ":";

    if (def)
    {
        std::cout << " [" << *def << ']';
    }

    std::cout << "\n> ";

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

template<typename T>
bool parseValue(const std::string& s, T& value);

template<>
bool parseValue<int>(const std::string& s, int& value)
{
    auto [ptr, ec] = std::from_chars(
        s.data(),
        s.data() + s.size(),
        value);

    return ec == std::errc();
}

template<>
bool parseValue<std::string>(const std::string& s, std::string& value)
{
    value = s;
    return true;
}

bool parseMoney(const std::string& s, int& value)
{
    //60.65 // 00.50 // 1000.87 // .78 // 8.4 // 91 //
    //after . only two digits

    value = 0;
    int ipr = 0;
    int ipr_fract = 0; 
    bool dot = false;
    int fractal_dig = 0;

    for (char c : s)
    {
        if (c == '.')
        {
            if (!dot)
            {
                ipr *= 100;
                dot = true;
                continue;
            }
            else
            {
                return false;
            }
        }

        if (unsigned(c - '0') > 9)
        {
            return false;
        }

        if (fractal_dig >= 2)
        {
            return false;
        }

        if (dot)
        {
            ipr_fract = ipr_fract*10 + c - '0';
            ++fractal_dig;
        }
        else
        {
            ipr = ipr * 10 + c - '0';
        }
        
    }

    value = ipr + ipr_fract;

    return true;
}

template<typename T>
std::optional<T> ask(
    const std::string& prompt,
    std::optional<T> def = std::nullopt)
{
    while (true)
    {
        std::optional<std::string> defStr;

        if (def)
            defStr = std::to_string(*def);
        auto s = askString(prompt, defStr);

        if (!s)
            return std::nullopt;

        T value;

        if (parseValue<T>(*s, value))
            return value;

        std::cout << "Invalid value. Try again.\n";
    }
}

template<>
std::optional<std::string> ask<std::string>(
    const std::string& prompt,
    std::optional < std::string> def)
{
    return askString(prompt, def);
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
        auto store = ask<std::string>("Store name");
        if (!store) return;

        auto product = ask<std::string>("Product name");
        if (!product) return;

        auto price = ask<int>("Price");
        if (!price) return;

        auto discount = ask<int>("Discount %", 0);

        std::cout << "\nAdded\n";

        std::cout << *store << "\n";
        std::cout << *product << "\n";
        std::cout << *price << "\n";
        std::cout << *discount << "\n";
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

