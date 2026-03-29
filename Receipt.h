#pragma once
#include <vector>
#include <chrono>
#include "Item.h"

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
    std::vector<item> items;
    int total;
    std::chrono::sys_seconds tmStamp;
};

