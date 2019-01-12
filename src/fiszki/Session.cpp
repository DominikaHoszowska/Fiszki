//
// Created by Dominika on 05.12.18.
//

#include "Session.h"


class CardCompare
{
public:
    bool operator() (std::shared_ptr<Card>& c1, std::shared_ptr<Card>& c2 )
    {
        return (c1->getEF_()>c2->getEF_());

    }
};

void Session::updateCardsToLearn() {
    collection_->updateCardsToLearn(this);
    std::sort(cards_.begin(),cards_.end(),CardCompare());
}

std::shared_ptr<Card> Session::giveNextCard() {
    return cards_[0];
}

const std::shared_ptr<Collection> &Session::getCollection_() const {
    return collection_;
}


void Session::addCardtoLearn(std::shared_ptr<Card> card) {
    cards_.push_back(card);
}

Session::Session(const std::shared_ptr<Collection> &collection_) : collection_(collection_) {
    updateCardsToLearn();
}

