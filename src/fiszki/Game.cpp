//
// Created by dominika on 19.11.18.
//

#include "Game.h"
#include "Collection.h"
#include <memory>
#include <iostream>
#include <sqlite3/sqlite3.h>
#include <sqlite3/sqlite_orm.h>

using namespace sqlite_orm;

void Game::addCollection(std::string name) {
    this->collections_.push_back(std::make_unique<Collection>(name));
}

unsigned long Game::numberOfCollections() {
    return (this->collections_).size();
}


Game::Game() {
//    actualFCId_=0;
//    char *err_msg = nullptr;
//
//    src_=sqlite3_open("baza.db", &db_);
//    if(src_){
//        std::cout<<"Nie mogę otworzyć bazy";
//    }
//    else{
//        std::string sql="CREATE TABLE COLLECTIONS("\
//        "ID INT PRIMATY KEY NOT NULL,"\
//        "NAME TEXT NOT NULL);"\
//        "CREATE TABLE CARDS("\
//        "ID INT PRIMARY KEY NOT NULL,"\
//        "PL TEXT NOT NULL,"\
//        "ENG TEXT NOT NULL,"\
//        "FOREGIN KEY(COLLRECTIONS) REFERENCES COLLECIONS(ID);"\
//        "INSERT INTO COLLECTIONS VALUES(1,'HOME');";
//        src_= sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err_msg);
//        sqlite3_close(db_);

//    }

    auto collectionsTable = make_table("Collections",
                                       make_column("id",
                                                   &Collection::setId_, //setter
                                                   &Collection::getId_, //getter,
                                                   autoincrement(),
                                                   primary_key()),
                                       make_column("name",
                                                   &Collection::setName_,
                                                   &Collection::getName_));
    auto cardTable = make_table("Cards",
                                make_column("id",
                                            &Card::setId_, //setter
                                            &Card::getId_, //getter,
                                            autoincrement(),
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


    auto storage = make_storage("dane.sqlite",
                                collectionsTable, cardTable);
}

void Game::updateFCId() {
    ++(this->actualFCId_);
}

int Game::getSrc_() const {
    return src_;
}
