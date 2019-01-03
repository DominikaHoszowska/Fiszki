//
// Created by Dominika on 19.11.18.
//

#include <memory>
#include <iostream>
#include <sqlite3/sqlite3.h>
#include <sqlite3/sqlite_orm.h>
#include "Game.h"

using namespace sqlite_orm;

//void Game::addCollection(std::string name) {
//    this->collections_.push_back(std::make_shared()<Collection>(name));
//}

unsigned long Game::numberOfCollections() {
    return (this->collections_).size();
}

Game::Game() {
    int src;
    char *err_msg = nullptr;

    src=sqlite3_open("baza.db", &db_);
    if(src){
        std::cout<<"Nie mogę otworzyć bazy";}
    else {
        std::string sql = "CREATE TABLE COLLECTIONS("\
        "ID INT PRIMATY KEY NOT NULL,"\
        "NAME TEXT NOT NULL);"\
        "CREATE TABLE CARDS("\
        "ID INT PRIMARY KEY NOT NULL,"\
        "PL TEXT NOT NULL,"\
        "ENG TEXT NOT NULL,"\
        "COLLECTION_ID INT,"\
        "FOREIGN KEY (COLLECTION_ID) REFERENCES COLLECIONS(ID));";
        src = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err_msg);
//        unsigned int a=4;
//        std::string pl="kot";
//        std::string eng="car";
//        sql="INSERT INTO CARDS VALUES("+ std::to_string(a) +",'"+pl+"','"+eng+"',1);";
    }

        /*  auto cardTable = make_table("Cards",
                                      make_column("id",
                                                  &Card::getId_, //getter,
                                                  &Card::setId_, //setter
                                                  primary_key()),
                                      make_column("pl",
                                                  &Card::setPl_, //setter
                                                  &Card::getPl_ //getter,
                                      ),
                                      make_column("eng",
                                                  &Card::setEng_,
                                                  &Card::getEng_),
                                      make_column("Ef",
                                                  &Card::setEF_,
                                                  &Card::getEF_),
                                      make_column("date",
                                                  &Card::setTimeToRepeat_,
                                                  &Card::getTimeToRepeat_)
          );

          auto collectionsTable = make_table("Collections",
                                             make_column("id",
                                                         &Collection::setId_, //setter
                                                         &Collection::getId_, //getter,
                                                         autoincrement(),
                                                         primary_key()),
                                             make_column("name",
                                                         &Collection::setName_,
                                                         &Collection::getName_));

      */
//     auto storage = make_storage("dane.sqlite",
//                                 collectionsTable, cardTable);
//     Collection collection=Collection("a");
//     storage.insert(Card(1,std::string("pies"),std::string("dog")));
    this->loadCollectionsFromDB();
    this->setActualCollId();
}



sqlite3 *Game::getDb_() const {
    return db_;
}


Game::Language Game::getLanguage_() const {
    return language_;
}

void Game::setLanguage(Game::Language language) {
    language_ = language;
}

void Game::addCard(std::string pl, std::string eng) {
    std::shared_ptr<Card> card (new Card(pl, eng));
    this->cardsToAdd_.push_back(card);
}

std::vector<std::pair<int, std::string>> Game::getCollections() {
    std::vector<std::pair<int, std::string>> collections;
    std::vector<std::shared_ptr<Collection>>:: iterator i;
    for(i=collections_.begin();i!=collections_.end();++i)
    {
        collections.push_back(make_pair(i->get()->getId_(),i->get()->getName_()));
    }
    return collections;
}

std::shared_ptr<Collection> Game::getCollection(unsigned int id) {
    std::vector<std::shared_ptr<Collection>>:: iterator i;
    for(i=collections_.begin();i!=collections_.end();++i)
    {
        if(i->get()->getId_()==id)
        {
            return *i;
        }
    }
return nullptr;

}



/*
 * Arguments:
 *
 *   unused - nie używamy
 *    count - liczba kolumn
 *     data - wiersze
 *  columns - kolumny
 */
static int callbackFuctionForCollections(void *unused,int count, char** data, char **columns)
{
    int idx;
    for(idx=0;idx<count;idx++)
    {
        std::cout<<data[idx]<<std::endl;
    }
}
void Game::loadCollectionsFromDB() {
//    int src;
//    char *err_msg = nullptr;
//    std::string sql="SELECT * FROM COLLECTIONS;";
//    src = sqlite3_exec(db_, sql.c_str(), callbackFuctionForCollections, nullptr, &err_msg);
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Collections";
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
//        std::cout<<"error: "<<sqlite3_errmsg(db_);

        //TODO bug
        return;
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id           = sqlite3_column_int (stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        std::string name2= reinterpret_cast<const char*>(name);
        this->addCollection(id, name2);

    }
    if (rc != SQLITE_DONE) {
//        std::cout<<"error: "<< sqlite3_errmsg(db_);
//TODO bug
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db_);

    //TODO

}

void Game::addCollection(unsigned int id, std::string name) {
    int src;
    char *err_msg = nullptr;
    std::shared_ptr<Collection> c=std::make_shared<Collection>(name,id,this);
    this->collections_.push_back(c);
    std::string sql="INSERT INTO COLLECTIONS VALUES("+ std::to_string(id) +",'"+name+"');";
    src = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err_msg);

}

void Game::addCollection(std::string name) {
    this->addCollection(actualCollId_+1,name);
    actualCollId_+=1;

}

void Game::setActualCollId() {
    std::vector<std::shared_ptr<Collection>>:: iterator i;
        actualCollId_=0;

    for(i=collections_.begin();i!=collections_.end();++i)
    {
        if(i->get()->getId_()>actualCollId_)
        {
            actualCollId_=i->get()->getId_();
        }
    }

}

void Game::setDb_(sqlite3 *db_) {
    Game::db_ = db_;
}
