//
// Created by Dominika on 05.12.18.
//

#include "Session.h"


class CardCompare
{
public:
    bool operator() (std::shared_ptr<CardSession>& c1, std::shared_ptr<CardSession>& c2 )
    {
        return (c1->getCard_()->getEF_()>c2->getCard_()->getEF_());

    }
};

void Session::updateCardsToLearn() {
    collection_->updateCardsToLearn(this);
}

std::shared_ptr<CardSession> Session::giveNextCard() {
    if(cards_.empty())
        return nullptr;

    return  *std::max_element(cards_.begin(),cards_.end(),CardCompare());
}

const std::shared_ptr<Collection> &Session::getCollection_() const {
    return collection_;
}


void Session::addCardToLearn(std::shared_ptr<Card> card) {
    cards_.push_back(std::make_shared<CardSession>(card));
}

Session::Session(const std::shared_ptr<Collection> &collection_) : collection_(collection_) {
    updateCardsToLearn();
    good_=0;
    medium_=0;
    bad_=0;
}

void Session::takeAnswer(std::shared_ptr<CardSession>, Session::Answer answer) {
    switch (answer)
    {
        case Answer ::GOOD:
            ++good_;

            break;

        case Answer ::MEDIUM:
            ++medium_;
            break;
        default:
            ++bad_;
            break;

    }

}

int Session::getGood_() const {
    return good_;
}

int Session::getMedium_() const {
    return medium_;
}

int Session::getBad_() const {
    return bad_;
}

int Session::getAllAnswers() const {
    return (good_+medium_+bad_);
}

