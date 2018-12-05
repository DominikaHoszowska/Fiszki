//
// Created by Dominika on 05.12.18.
//

#include "Session.h"

void Session::updateCardsToLearn() {
    //TODO
}

std::shared_ptr<Card> Session::giveNextCard() {
    //TODO
    return nullptr;
}

const std::shared_ptr<Game> &Session::getGame_() const {
    return game_;
}

void Session::setGame_(const std::shared_ptr<Game> &game_) {
    Session::game_ = game_;
}

const std::shared_ptr<Collection> &Session::getCollection_() const {
    return collection_;
}

void Session::setCollection_(const std::shared_ptr<Collection> &collection_) {
    Session::collection_ = collection_;
}

void Session::addCardtoLearn(std::shared_ptr<Card> card) {
    cards_.push_back(card);
    //TODO sortowanie po EF
}
