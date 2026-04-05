#pragma once
#include <string>
#include <charconv>

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
        else if (dot)
        {
            fractal_dig++;
        }

        ipr = ipr * 10 + c - '0';

    }

    if (fractal_dig < 2)
    {
        for (int i = 0; i < (2 - fractal_dig); i++)
            ipr *= 10;
    }

    value = ipr;

    return true;
}

