//
// Created by Dominika on 19.11.18.
//
#include <ctime>
#include "Card.h"
#include <memory>
void Card::updateEF(unsigned int value) {
    //TODO

}


const std::string &Card::getPl_() const {
    return pl_;
}

const std::string &Card::getEng_() const {
    return eng_;
}

Card::Card(const std::string &pl_, const std::string &eng_) :  pl_(pl_), eng_(eng_){
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

const boost::gregorian::date &Card::getTimeToRepeat_() const {
    return timeToRepeat_;
}

void Card::setTimeToRepeat_(const boost::gregorian::date &timeToRepeat_) {
    Card::timeToRepeat_ = timeToRepeat_;
}

Card::Card(unsigned int id_, const std::string &pl_, const std::string &eng_) : id_(id_), pl_(pl_), eng_(eng_) {
    EF_=3.5;
    timeToRepeat_=boost::gregorian::day_clock::local_day();
}

void Card::insertCardtoDB() {
    char *err_msg = nullptr;
    std:: string sql="INSERT INTO CARDS VALUES("+ std::to_string(this->getId_()) +",'"+this->getPl_()+"','"+this->getEng_()+"',1);";
    int src_ = sqlite3_exec(getCollection_()->getGame_()->getDb_(), sql.c_str(), nullptr, nullptr, &err_msg);
    //TODO wyjątek
}

const std::shared_ptr <Collection> &Card::getCollection_() const {
    return collection_;
}

 bool Card::checkCorrectnessW(const std::string &word) {
    //TODO
    return false;
}







