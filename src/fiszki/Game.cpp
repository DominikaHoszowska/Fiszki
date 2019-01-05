//
// Created by Dominika on 19.11.18.
//

#include <memory>
#include <iostream>
#include <sqlite3/sqlite3.h>
#include <sqlite3/sqlite_orm.h>
#include "Game.h"


using namespace sqlite_orm;



unsigned long Game::numberOfCollections() {
    return (this->collections_).size();
}

Game::Game() {
    int src;
    char *err_msg = nullptr;
    setlocale( LC_ALL, "" );
    src=sqlite3_open("baza.db", &db_);
    if(src){
        std::cout<<"Nie mogę otworzyć bazy";}
    else {
        std::string sql = "CREATE TABLE COLLECTIONS("\
        "ID INT PRIMARY KEY NOT NULL,"\
        "NAME TEXT NOT NULL);"\
        "CREATE TABLE CARDS("\
        "ID INT PRIMARY KEY NOT NULL ,"\
        "PL TEXT NOT NULL,"\
        "ENG TEXT NOT NULL,"\
        "COLLECTION_ID INT,"\
        "FOREIGN KEY (COLLECTION_ID) REFERENCES COLLECTIONS(ID));";
        src = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err_msg);

    }

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

std::vector<std::string> Game::getCollections() {
    std::vector<std::string> collections;
    std::vector<std::shared_ptr<Collection>>:: iterator i;
    for(i=collections_.begin();i!=collections_.end();++i)
    {
        collections.push_back((i->get()->getName_()));
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




void Game::loadCollectionsFromDB() {

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

    //TODO

}

void Game::addCollection(unsigned int id, std::string name) {

    std::shared_ptr<Collection> c=std::make_shared<Collection>(name,id,this);

    this->collections_.push_back(c);


}

void Game::addCollection(std::string name) {

    int src;
    char *err_msg = nullptr;
    std::string sql="INSERT INTO COLLECTIONS VALUES("+ std::to_string(actualCollId_+1) +",'"+name+"');";
    src = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err_msg);
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

std::shared_ptr<Collection> Game::getCollection(std::string& name) {
    std::vector<std::shared_ptr<Collection>>:: iterator i;
    for(i=collections_.begin();i!=collections_.end();++i)
    {
        if(!i->get()->getName_().compare(name))
            return *i;
    }
    return nullptr;
}

void Game::addCardsToCollection(std::string collectionName) {
    std::shared_ptr<Collection> c=getCollection(collectionName);
    c->loadFromDB();
    std::vector<std::shared_ptr<Card>>:: iterator i;
    for(i=cardsToAdd_.begin();i!=cardsToAdd_.end();++i)
    {
        c->addFC(i->get()->getPl_(),i->get()->getEng_(),actualCardId_+1);
        ++actualCardId_;
    }
    cardsToAdd_.clear();
}

Game::~Game() {
    sqlite3_close(db_);


}

bool Game::ifCardsToAddIsEmpty() {
    return cardsToAdd_.empty();
}

bool Game::ifCollectionNameUnique(std::string& name) {
    for(auto i:collections_)
    {
        if(!name.compare(i->getName_()))
            return 0;
    }
    return 1;
}
