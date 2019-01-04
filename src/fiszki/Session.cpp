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





const std::shared_ptr<Collection> &Session::getCollection_() const {
    return collection_;
}


void Session::addCardtoLearn(std::shared_ptr<Card> card) {
    cards_.push_back(card);
    //TODO sortowanie po EF
}

Session::Session(const std::shared_ptr<Collection> &collection_) : collection_(collection_) {}
