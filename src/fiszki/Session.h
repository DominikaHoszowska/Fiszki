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
    std::vector<std::shared_ptr<Card>> cards_;//! karty do nauki w danej sesji
    std::shared_ptr<Collection> collection_;//! wskaźnik do aktualnie nauczanej kolekcji

public:

    //GETTERS:

    const std::shared_ptr<Collection> &getCollection_() const;

    Session(const std::shared_ptr<Collection> &collection_);//! zaciąga karty do nauki
    //OTHERS:

    void updateCardsToLearn();//!Prosi kolekcję o dodatnie kart do nauki
    std::shared_ptr<Card> giveNextCard();//!zwraca kolejną kartę do nauki
    void addCardtoLearn(std::shared_ptr<Card>); //!dodaje kartę do nauki do sesji,


};


#endif //ZPR_SESSION_H
