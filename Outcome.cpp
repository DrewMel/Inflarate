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
#include <conio.h>
#include <optional>
#include <charconv>
#include "CLI.h"

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
    bool dot = false;
    int fractal_dig = 0;

    for (char c : s)
    {
        if (c == '.')
        {
            if (!dot)
            {
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
        else if(dot)
        {
            fractal_dig++;
        }

        ipr = ipr * 10 + c - '0';
        
    }

    if (fractal_dig < 2)
    {
        for(int i = 0; i < (2 - fractal_dig); i++)
            ipr *= 10;
    }
        
    value = ipr;

    return true;
}

std::string Money2String(int iprice)
{
    int ifract = iprice % 100;
    int iwhole = iprice / 100;

    return std::string(std::to_string(iwhole) + '.' + std::to_string(ifract));
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

std::optional<int>askMoney()
{
    auto s = askString("Price");
    if (!s)
        return std::nullopt;

    int vPrice = 0;

    if (parseMoney(*s, vPrice))
        return vPrice;

    std::cout << "Invalid value. Try again.\n";

    return std::nullopt;
}

int main()
{
    CLI cli;
    cli.run();

    return 0;
}

