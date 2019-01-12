//
// Created by dominika on 12.01.19.
//

#include <numeric>
#include "CardSession.h"

CardSession::CardSession(const std::shared_ptr<Card> &card_) : card_(card_) {}

const std::shared_ptr<Card> &CardSession::getCard_() const {
    return card_;
}

void CardSession::addNewScore(unsigned int q) {
    scores_.push_back(q);
}

double CardSession::getAverage() {
    return std::accumulate(scores_.begin(),scores_.end(),0.0)/scores_.size();
}

unsigned int CardSession::getNumberOfScores() {
    return scores_.size();
}

