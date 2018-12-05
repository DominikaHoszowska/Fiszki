//
// Created by Dominika on 05.12.18.
//

#ifndef ZPR_SESSION_H
#define ZPR_SESSION_H


#include "Game.h"
/*!
 * \brief Klasa będąca sesją nauki
 */
class Session {
private:
    std::vector<Card> cards_;//! karty do nauki w danej sesji
    std::shared_ptr<Game> game_;//! wskaźnik do gry
public:
   void updateCardsToLearn(std::shared_ptr<Game>);
   std::shared_ptr<Card> giveNextCard(std::shared_ptr<Game>);
};


#endif //ZPR_SESSION_H
