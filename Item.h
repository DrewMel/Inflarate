#pragma once
#include <string>

class item
{
private:
    std::string name;
    int price_unit;
    int amount;
    bool discount;
    int discounted_price;
    int discount_percent;;
};