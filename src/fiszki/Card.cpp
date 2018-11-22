//
// Created by dominika on 19.11.18.
//
#define day 86400
#include <ctime>
#include "Card.h"

void Card::updateEF(unsigned int value) {
    //TODO

}


const std::string &Card::getPl_() const {
    return pl_;
}

const std::string &Card::getEng_() const {
    return eng_;
}

Card::Card(unsigned int id_, const std::string &pl_, const std::string &eng_) : id_(id_), pl_(pl_), eng_(eng_){
    EF_=3.5;
    setTimeToRepeat(0);
}

void Card::setTimeToRepeat(unsigned int n) {//n-number of days
    this->timeToRepeat_=time(NULL)-(time(NULL)%day)+n*day;
}



