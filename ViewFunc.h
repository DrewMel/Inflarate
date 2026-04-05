#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <conio.h>
#include "StrParser.h"

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

std::string Money2String(int iprice)
{
    int ifract = iprice % 100;
    int iwhole = iprice / 100;

    std::string strFract{ "" };
    if (ifract < 10)
    {
        strFract = '0';
    }

    return std::string(std::to_string(iwhole) + '.' + strFract + std::to_string(ifract));
}