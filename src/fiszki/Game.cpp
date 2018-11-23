//
// Created by dominika on 19.11.18.
//

#include "Game.h"
#include "Collection.h"
#include <memory>
void Game::addCollection( std::string name){
    this->collections_.push_back(std::make_unique<Collection>(name));
}

unsigned long  Game::numberOfCollections() {
    return (this->collections_).size();
}

Game::Game(){
    actualFCId_=0;
}

void Game::updateFCId() {
    ++(this->actualFCId_);
}
