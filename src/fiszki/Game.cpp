//
// Created by Dominika on 19.11.18.
//

#include <memory>
#include <iostream>
#include <sqlite3/sqlite3.h>
#include <sqlite3/sqlite_orm.h>
#include "Game.h"


using namespace sqlite_orm;
//Konstruktory:
Game::Game(std::string& dbname) {
    int src;
    char *err_msg = nullptr;
    setlocale(LC_ALL, "polish");
    src = sqlite3_open(dbname.c_str(), &db_);
    if (src) {
        std::cout << "Nie mogę otworzyć bazy";
    } else {
        std::string sql = "CREATE TABLE COLLECTIONS("\
        "ID INT PRIMARY KEY NOT NULL,"\
        "NAME TEXT NOT NULL);"\
        "CREATE TABLE CARDS("\
        "ID INT PRIMARY KEY NOT NULL ,"\
        "PL TEXT NOT NULL,"\
        "ENG TEXT NOT NULL,"\
        "EF DOUBLE,"\
        "TIME_TO_REPEAT DATE,"\
        "COLLECTION_ID INT,"\
        "I INT,"\
        "FOREIGN KEY (COLLECTION_ID) REFERENCES COLLECTIONS(ID));";
        src = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err_msg);

    }
    this->loadActualCardId();
    this->loadCollectionsFromDB();
    this->setActualCollId();
}

//Destruktor:

Game::~Game() {
    sqlite3_close(db_);
}
//Gettery:

Game::Language Game::getLanguage_() const {
    return language_;
}

sqlite3 *Game::getDb_() const {
    return db_;
}


unsigned long Game::numberOfCollections() {
    return (this->collections_).size();
}


std::shared_ptr<Collection> Game::getCollection(unsigned int id) {

    for (auto& i : collections_)
        if (i->getId_() == id) return i;

    return nullptr;

}

std::shared_ptr<Collection> Game::getCollection(std::string &name) {
    for (auto i :collections_) {
        if (!i->getName_().compare(name))
            return i;
    }
    return nullptr;
}

std::vector<std::string> Game::getCollections() {
    std::vector<std::string> collections;
    std::vector<std::shared_ptr<Collection>>::iterator i;
    for (i = collections_.begin(); i != collections_.end(); ++i) {
        collections.push_back((i->get()->getName_()));
    }
    return collections;
}

unsigned int Game::getActualCardId_() const {
    return actualCardId_;
}

//Settery:

void Game::setLanguage(Game::Language language) {
    language_ = language;
}

void Game::setActualCollId() {
    std::vector<std::shared_ptr<Collection>>::iterator i;
    actualCollId_ = 0;

    for (i = collections_.begin(); i != collections_.end(); ++i) {
        if (i->get()->getId_() > actualCollId_) {
            actualCollId_ = i->get()->getId_();
        }
    }

}

//Inne:

void Game::addCollection(unsigned int id, std::string name) {

    std::shared_ptr<Collection> c = std::make_shared<Collection>(name, id, this);

    this->collections_.push_back(c);


}
void Game::addCollection(std::string name) {
    if(ifCollectionNameUnique(name)) {
        int src;
        char *err_msg = nullptr;
        std::string sql = "INSERT INTO COLLECTIONS VALUES(" + std::to_string(actualCollId_ + 1) + ",'" + name + "');";
        src = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err_msg);
        this->addCollection(actualCollId_ + 1, name);
        actualCollId_ += 1;
    }

}


void Game::addCard(std::string pl, std::string eng) {
    std::shared_ptr<Card> card(new Card(pl, eng));
    this->cardsToAdd_.push_back(card);
}


void Game::addCardsToCollection(std::string collectionName) {
    std::shared_ptr<Collection> c = getCollection(collectionName);
    if(c) {
        c->loadFromDB();
        std::vector<std::shared_ptr<Card>>::iterator i;
        for (i = cardsToAdd_.begin(); i != cardsToAdd_.end(); ++i) {
            c->addNewFC(i->get()->getPl_(), i->get()->getEng_(), actualCardId_ + 1);
            ++actualCardId_;
        }
        cardsToAdd_.clear();
    }
}

bool Game::ifCardsToAddIsEmpty() {
    return cardsToAdd_.empty();
}

bool Game::ifCollectionNameUnique(std::string &name) {
    for (auto i:collections_) {
        if (!name.compare(i->getName_()))
            return 0;
    }
    return 1;
}

void Game::clearCardsToAdd() {
    cardsToAdd_.clear();
}




void Game::loadCollectionsFromDB() {

    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Collections";
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cout<<"error: "<<sqlite3_errmsg(db_);

        return;
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        std::string name2 = reinterpret_cast<const char *>(name);
        this->addCollection(id, name2);

    }
    if (rc != SQLITE_DONE) {
        std::cout<<"error: "<< sqlite3_errmsg(db_);
    }
    sqlite3_finalize(stmt);


}


void Game::loadActualCardId() {

    sqlite3_stmt *stmt;
    const char *sql = "SELECT MAX(ID) FROM Cards";
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cout<<"error: "<<sqlite3_errmsg(db_);
        return;
    }
    rc = sqlite3_step(stmt);
    actualCardId_ = sqlite3_column_int(stmt, 0);


    if (rc != SQLITE_DONE) {
        std::cout<<"error: "<< sqlite3_errmsg(db_);
    }
    sqlite3_finalize(stmt);
}

