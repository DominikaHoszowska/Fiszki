//
// Created by dominika on 19.11.18.
//

#ifndef ZPR_CARD_H
#define ZPR_CARD_H
#include <string>
#include <ctime>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "Collection.h"
#include <memory>
class Collection;
class Card {
private:
    unsigned int id_;
    std::string pl_;
    std::string eng_;
    double EF_;
    boost::gregorian::date timeToRepeat_;
    std::shared_ptr<Collection> collection_;

public:
    unsigned int getId_() const;

    void setId_(unsigned int id_);

    void setPl_(const std::string &pl_);

    void setEng_(const std::string &eng_);

    double getEF_() const;

    Card(unsigned int id_, const std::string &pl_, const std::string &eng_);

    void setEF_(double EF_);

    void updateEF(unsigned int);

    const std::string &getPl_() const;

    const std::string &getEng_() const;

    Card(const std::string &pl_, const std::string &eng_);
    void setNewTimeToRepeat(unsigned int);

    const boost::gregorian::date &getTimeToRepeat_() const;

    void setTimeToRepeat_(const boost::gregorian::date &timeToRepeat_);
    void insertCardtoDB();

    const std::shared_ptr <Collection> &getCollection_() const;
};

#endif //ZPR_CARD_H
