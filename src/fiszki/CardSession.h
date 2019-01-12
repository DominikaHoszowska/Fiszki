//
// Created by dominika on 12.01.19.
//

#ifndef ZPR_CARDSESSION_H
#define ZPR_CARDSESSION_H


#include "Card.h"

class CardSession {
private:
    std::shared_ptr<Card> card_;
    std::vector<int> answer_;
public:
    CardSession(const std::shared_ptr<Card> &card_);

    const std::shared_ptr<Card> &getCard_() const;

};


#endif //ZPR_CARDSESSION_H
