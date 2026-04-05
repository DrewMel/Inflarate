#include "Receipt.h"

Receipt::Receipt(std::string const & storeName,
            std::string const & address,
            cidno_t & idno,
            std::string const & inr,
            int const bonNumber,
            time_t const time,
            int const total, int const n):
    StoreName_(storeName), address_(address),
    IDNO_(idno), INR_(inr), bon_number_(bonNumber),
    purchase_time(time), total_(total), 
    items_number_()
{

}

void Receipt::addItem(Item const & item)
{
    items_.push_back(item);
}