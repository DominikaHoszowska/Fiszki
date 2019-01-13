//
// Created by Dominika on 19.11.18.
//
#include <ctime>
#include "Card.h"
#include <memory>
#include <codecvt>
void Card::updateEF( double q) {
    EF_+=(0.1-(5-q)*(0.08+(5-q)*0.02));
    if(EF_<1.1)
    {
        EF_=1.1;
    }

}


const std::string &Card::getPl_() const {
    return pl_;
}

const std::string &Card::getEng_() const {
    return eng_;
}

Card::Card(const std::string &pl_, const std::string &eng_) :  pl_(pl_), eng_(eng_){
    EF_=3.5;
    timeToRepeat_=boost::gregorian::date(boost::gregorian::day_clock::local_day());
    i_=1;
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
    i_=1;
}



Collection *Card::getCollection_() const {
    return collection_;
}

 bool Card::checkCorrectnessW(const std::string &word) {
    if(word.empty())
        return false;
     std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
     std::wstring wide = converter.from_bytes(word);
     std::locale loc( "pl_PL.utf8" );

     for(wchar_t letter:wide)
    {

        if(!((std::isalpha(letter,loc))||(letter==' ')||(letter=='\'')||(letter=='-')))
                    return false;
    }

    return true;
}

Card::Card(unsigned int id_, const std::string &pl_, const std::string &eng_,
           Collection* collection_) : id_(id_), pl_(pl_), eng_(eng_), collection_(collection_) {
    EF_=3.5;
    timeToRepeat_=boost::gregorian::date(boost::gregorian::day_clock::local_day());
}

Card::Card(unsigned int id_, const std::string &pl_, const std::string &eng_, double EF_,
           const boost::gregorian::date &timeToRepeat_, Collection* collection_, unsigned int i_) : id_(id_),
                                                                                                          pl_(pl_),
                                                                                                          eng_(eng_),
                                                                                                          EF_(EF_),
                                                                                                          timeToRepeat_(
                                                                                                                  timeToRepeat_),
                                                                                                          collection_(
                                                                                                                  collection_),
                                                                                                                  i_(i_){}

unsigned int Card::getI_() const {
    return i_;
}

void Card::updateCard(double q) {
    updateEF(q);
    updateI();
    updateTimeToRepeat();
    updateCardDB();
}

void Card::updateI() {
    i_*=EF_;
    if(i_<1)
        i_=1;
    if(i_>100)
    {
        i_=100;
    }
}

void Card::updateTimeToRepeat() {
    timeToRepeat_=boost::gregorian::day_clock::local_day()+boost::gregorian::days(i_);
}

void Card::updateCardDB() {

    char *err_msg = nullptr;

    std::string sql="UPDATE CARDS SET  EF=";
    sql+=std::to_string(EF_);
    sql+=", TIME_TO_REPEAT='";
    sql+=std::to_string(getTimeToRepeat_().year())+"-";
    sql+=std::to_string(getTimeToRepeat_().month())+"-";
    sql+=std::to_string(getTimeToRepeat_().day())+"',I=";
    sql+=std::to_string(i_);
    sql+=" WHERE ID=";
    sql+=std::to_string(id_);
    sql+=";";
    sqlite3_exec(this->getCollection_()->getGame_()->getDb_(), sql.c_str(), nullptr, nullptr, &err_msg);

}






