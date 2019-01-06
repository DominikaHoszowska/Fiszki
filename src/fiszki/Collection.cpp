//
// Created by Dominika on 19.11.18.
//

#include "Collection.h"
#include <sqlite3/sqlite3.h>


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

void Collection::addFC(const std::string & pl, const std::string &eng, unsigned int id) {

    std::shared_ptr<Card>c=std::make_shared<Card>(id,pl,eng);
    this->cards_.push_back(c);
    char *err_msg = nullptr;


    std::string sql="INSERT INTO CARDS VALUES(";
    sql+=std::to_string(id);
    sql+=",'"+pl+"','"+eng+"'";
    sql+=",";
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
        cards_.push_back(std::make_shared<Card>(id,pl,eng,std::shared_ptr<Collection>(this)));

    }
}

bool Collection::checkCorrectnessC(const std::string &word) {
    if(word.empty())
        return false;
    for(char32_t letter:word)
    {
        if(!((std::isalpha(letter)||std::isdigit(letter)||(letter==32)||(letter==45)||(letter==39))))
            if(!(letter==206||letter==210||letter==230||letter==242||letter==245||letter==251||letter==253||letter==276||letter==344))
                return false;
    }
    return true;
}

//Collection::Collection(const std::string &name_) : name_(name_) {}
int returnFunction(void *unused, int count, char **data, char **columns)
{
    std::string s(data[0]);
    return std::stoi(s);
}
int returnFunction2(void *unused, int count, char **data, char **columns)
{
    std::string s(data[0]);
    return std::stoi(s);
}



