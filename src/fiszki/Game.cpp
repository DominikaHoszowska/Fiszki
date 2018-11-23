//
// Created by dominika on 19.11.18.
//

#include "Game.h"
#include "Collection.h"
#include <memory>
void Game::addCollection(const std::string name){
    this->collections_.push_back(std::make_unique<Collection>(name));
}

unsigned long  Game::sizeOfCollections() {
    return (this->collections_).size();
}
