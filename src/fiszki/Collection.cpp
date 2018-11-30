//
// Created by dominika on 19.11.18.
//

#include "Collection.h"

Collection::Collection(const std::string &name_) : name_(name_) {}

void Collection::addFC(std::string &pl, std::string &eng, unsigned int id) {
    this->cards_.push_back(std::make_unique<Card>(id,pl,eng));
}

const std::string &Collection::getName_() const {
    return name_;
}

void Collection::setName_(const std::string &name_) {
    Collection::name_ = name_;
}

unsigned int Collection::getId_() const {
    return id_;
}

void Collection::setId_(unsigned int id_) {
    Collection::id_ = id_;
}

const std::shared_ptr<Game> &Collection::getGame_() const {
    return game_;
}
