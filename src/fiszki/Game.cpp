//
// Created by dominika on 19.11.18.
//

#include "Game.h"
#include "Collection.h"
#include <memory>
#include <iostream>
#include <sqlite3/sqlite3.h>

void Game::addCollection( std::string name){
    this->collections_.push_back(std::make_unique<Collection>(name));
}

unsigned long  Game::numberOfCollections() {
    return (this->collections_).size();
}

Game::Game(){
    actualFCId_=0;
    int src=sqlite3_open("test.db", &db_);
    if(src){
        std::cout<<"Nie mogę otworzyć bazy";
    }
    else{
        std::cout<<"Wszystko ok";
    }
}

void Game::updateFCId() {
    ++(this->actualFCId_);
}
