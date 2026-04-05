#pragma once
#include <string>

class Item
{
public:
Item(std::string const & name,
    int const pricePerUnit,
    double const amount, 
    int const discount,
    int const discountPercent,
    int const Summ);

std::string getName() const;
int getPricePerUnit() const;
int getSumm() const;      
double getAmount() const; 

private:
    std::string const name_;
    int pricePerUnit_;
    double amount_;
    int discount_;
    int discountPercent_;
    int Summ_;
};

