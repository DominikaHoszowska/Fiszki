//
// Created by Dominika on 19.11.18.
//

#include <memory>
#include <iostream>
#include <sqlite3/sqlite3.h>
#include <sqlite3/sqlite_orm.h>
#include "Game.h"

using namespace sqlite_orm;

void Game::addCollection(std::string name) {
    this->collections_.push_back(std::make_unique<Collection>(name));
}

unsigned long Game::numberOfCollections() {
    return (this->collections_).size();
}

Game::Game() {
    int src;
    actualCollId_=0;
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
        src = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err_msg);
        std::cout<<sql<<"!!!!";
        sqlite3_close(db_);
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
