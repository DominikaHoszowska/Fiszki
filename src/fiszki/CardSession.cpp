//
// Created by dominika on 12.01.19.
//

#include "CardSession.h"

CardSession::CardSession(const std::shared_ptr<Card> &card_) : card_(card_) {}

const std::shared_ptr<Card> &CardSession::getCard_() const {
    return card_;
}
