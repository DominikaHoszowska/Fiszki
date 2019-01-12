//
// Created by Dominika on 19.11.18.
//

#include "Collection.h"
#include <sqlite3/sqlite3.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <codecvt>


const std::string &Collection::getName_() const {
    return name_;
}


unsigned int Collection::getId_() const {
    return id_;
}

void Collection::setId_(unsigned int id_) {
    Collection::id_ = id_;
}


Collection::Collection(const std::string &name_, unsigned int id_, Game* game_) : name_(name_),
                                                                                                         id_(id_),
                                                                                                         game_(game_) {

}

Game *Collection::getGame_() const {
    return game_;
}

void Collection::addNewFC(const std::string & pl, const std::string &eng, unsigned int id) {

    std::shared_ptr<Card>c=std::make_shared<Card>(id,pl,eng);
    this->cards_.push_back(c);
    char *err_msg = nullptr;


    std::string sql="INSERT INTO CARDS VALUES(";
    sql+=std::to_string(id);
    setlocale( LC_ALL, "" );

    sql+=",'"+pl+"','"+eng+"'";
    std::locale::global(std::locale::classic());

    sql+=","+boost::lexical_cast<std::string>(c->getEF_());
    sql+=",'";
    sql+=std::to_string(c->getTimeToRepeat_().year())+"-";
    sql+=std::to_string(c->getTimeToRepeat_().month())+"-";
    sql+=std::to_string(c->getTimeToRepeat_().day())+"',";
    sql+=std::to_string(this->getId_());
    sql+=");";

    std::cout<<sql;
    sqlite3_exec(this->getGame_()->getDb_(), sql.c_str(), nullptr, nullptr, &err_msg);
    std::cout<<err_msg;
}

void Collection::loadFromDB() {
    sqlite3_stmt *stmt;
    std::string sql = "SELECT * FROM Cards WHERE Collection_ID=";
    sql+=std::to_string(this->getId_());
    int rc = sqlite3_prepare_v2(this->game_->getDb_(), sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
//        std::cout<<"error: "<<sqlite3_errmsg(db_);

        //TODO bug
        return;
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id           = sqlite3_column_int (stmt, 0);
        std::string pl= reinterpret_cast<const char* >(sqlite3_column_text(stmt, 1));
        std::string eng= reinterpret_cast<const char* >(sqlite3_column_text(stmt, 2));
        double ef= sqlite3_column_double(stmt,3);
        std::string date= reinterpret_cast<const char* >(sqlite3_column_text(stmt, 4));
        boost::gregorian::date d = boost::gregorian::from_simple_string(date);
        cards_.push_back(std::make_shared<Card>(id,pl,eng,ef,d,std::shared_ptr<Collection>(this)));

    }
}

bool Collection::checkCorrectnessC(const std::string &word) {
    if(word.empty())
        return false;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(word);
    std::locale loc( "pl_PL.utf8" );

    for(wchar_t letter:wide)
    {
        if(!((std::isalpha(letter,loc))||(std::isdigit(letter))||(letter==' ')||(letter=='\'')||(letter=='-')))
            return false;
    }
    return true;
}

void Collection::updateCardsToLearn(Session *session) {
    for(auto i:cards_)
    {
        if(i->getTimeToRepeat_()<=boost::gregorian::date(boost::gregorian::day_clock::local_day()))
        {
            session->addCardtoLearn(std::make_shared<Card>(*i));
        }
    }
}


