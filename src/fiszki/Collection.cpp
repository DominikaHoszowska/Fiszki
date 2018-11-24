//
// Created by dominika on 19.11.18.
//

#include "Collection.h"

Collection::Collection(const std::string &name_) : name_(name_) {}

void Collection::addFC(std::string &pl, std::string &eng, unsigned int id) {
    this->cards_.push_back(std::make_unique<Card>(id,pl,eng));
}
