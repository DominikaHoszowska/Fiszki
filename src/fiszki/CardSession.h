//
// Created by dominika on 12.01.19.
//

#ifndef ZPR_CARDSESSION_H
#define ZPR_CARDSESSION_H


#include "Card.h"

class CardSession {
private:
    std::shared_ptr<Card> card_;
    std::vector<int> scores_;
public:
    //Konstruktory:

    CardSession(const std::shared_ptr<Card> &card_);//!< konsturktor używany przy dodawaniu fiszki do uczenia w Session

    //Gettery:


    const std::shared_ptr<Card> &getCard_() const;
    double getAverage();
    unsigned int getNumberOfScores();


    //Inne
    void addNewScore(unsigned int);
};


#endif //ZPR_CARDSESSION_H
