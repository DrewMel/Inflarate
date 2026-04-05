#pragma once
#include <vector>
#include <chrono>
#include "Item.h"

typedef long long unsigned int const cidno_t;

class Receipt
{
public:
    Receipt(std::string const & storeName,
            std::string const & address,
            cidno_t & idno,
            std::string const & inr,
            int const bonNumber,
            time_t const time,
            int const total,
            int const n);
private:
    std::string const StoreName_;
    std::string const address_;
    cidno_t IDNO_;
    std::string const INR_;
    int const bon_number_;
    int const total_;
    time_t const purchase_time;
    int const items_number_;

    std::chrono::system_clock::time_point const tmStamp;
    std::vector<Item> items_;
    int summ;

    public:
    void addItem(Item const & item);
    std::string const & getStoreName() const { return StoreName_;}
    std::string const & getAddres() const {return address_;}
    cidno_t & getIDNO() const {return IDNO_;}
    std::string const & getInr() const { return INR_;}
    int getINumber() const {return items_number_;}
    int getTotal() const {return total_;}
};

