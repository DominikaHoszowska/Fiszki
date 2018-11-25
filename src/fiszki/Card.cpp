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
//    setTimeToRepeat(0);
}

void Card::setNewTimeToRepeat(unsigned int n) {//n-number of days
//    this->timeToRepeat_=time(NULL)-(time(NULL)%day)+n*day;
}

unsigned int Card::getId_() const {
    return id_;
}

void Card::setId_(unsigned int id_) {
    Card::id_ = id_;
}

void Card::setPl_(const std::string &pl_) {
    Card::pl_ = pl_;
}

void Card::setEng_(const std::string &eng_) {
    Card::eng_ = eng_;
}

double Card::getEF_() const {
    return EF_;
}

void Card::setEF_(double EF_) {
    Card::EF_ = EF_;
}

time_t Card::getTimeToRepeat_() const {
    return timeToRepeat_;
}

void Card::setTimeToRepeat_(time_t timeToRepeat_) {
    Card::timeToRepeat_ = timeToRepeat_;
}






