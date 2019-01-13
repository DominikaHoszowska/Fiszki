//
// Created by Dominika on 05.12.18.
//

#ifndef ZPR_SESSION_H
#define ZPR_SESSION_H


#include "Game.h"
#include "Card.h"
#include "CardSession.h"
class CardSession;
/*!
 * \brief Klasa będąca sesją nauki
 */
class Session {
private:
    std::vector<std::shared_ptr<CardSession>> cards_;//! karty do nauki w danej sesji
    std::shared_ptr<Collection> collection_;//! wskaźnik do aktualnie nauczanej kolekcji
    int good_;
    int medium_;
    int bad_;

public:
    enum class Answer {
        GOOD,
        MEDIUM,
        BAD
    };

    //Konstruktry:
    Session(const std::shared_ptr<Collection> &collection_);//! zaciąga karty do nauki

    //GETTERY:

    const std::shared_ptr<Collection> &getCollection_() const;
    int getGood_() const;//!używany do wyświetlania statystyk
    int getMedium_() const;//!używany do wyświetlania statystyk
    int getBad_() const;//!używany do wyświetlania statystyk
    int getAllAnswers() const;//!używany do wyświetlania statystyk
    unsigned long getNumberOfCards();//!używany aby sprawdzić czy są jakieś karty do nauki

    //OTHERS:

    void updateCardsToLearn();//!Prosi kolekcję o dodatnie kart do nauki
    std::shared_ptr<CardSession> giveNextCard();//!zwraca kolejną kartę do nauki
    void addCardToLearn(std::shared_ptr<Card> card); //!dodaje kartę do nauki do sesji,
    void takeAnswer(std::shared_ptr<CardSession>,Answer answer);
    void deleteCard(std::shared_ptr<CardSession>);

};


#endif //ZPR_SESSION_H
