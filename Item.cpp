#include "Item.h"

Item::Item(std::string const & name,
    int const pricePerUnit,
    double const amount, 
    int const discount,
    int const discountPercent,
    int const totalPrice)
    : name_(name),
      pricePerUnit_(pricePerUnit),
      amount_(amount),
      discount_(discount),
      discountPercent_(discountPercent),
      Summ_(totalPrice)
{

}

std::string Item::getName() const
{
    return name_;
}

int Item::getPricePerUnit() const
{
    return pricePerUnit_;
}

int Item::getSumm() const
{
    return Summ_;
}

double Item::getAmount() const
{
    return amount_;
}