//
// Created by Dominika on 19.11.18.
//

#ifndef ZPR_COLLECTION_H
#define ZPR_COLLECTION_H
#include <string>
#include <vector>
#include <memory>
#include "Game.h"
#include "Card.h"
#include "Session.h"

class Game;
class Card;
class Session;
/*!
 * \brief Klasa reprezentująca katalog/kolekcję, trzymająca fiszki należące do danej kolekcji
 */
class Collection {
private:
    std::string name_;//!< nazwa kolekcji
    std::vector<std::shared_ptr<Card>> cards_; //!< wektor wskaźników na fiszki
    unsigned int id_; //!< unikalne ID
    Game* game_;//!<wskaźnik na grę

public:
    //Konstruktory:
    explicit Collection(const std::string &name_, unsigned int id_, Game* game_);//!<konstruktor używany przy dodawaniu kolekcji do gry

    //Gettery:

    Game *getGame_() const;//!< zwraca wskaźnik na grę
    const std::string &getName_() const; //!< zwraca nazwę kolekcji
    unsigned int getId_() const; //!< zwraca ID kolekcji
   //Inne:

    void addNewFC(const std::string&, const std::string&, unsigned int); //!< dodawanie fiszki do kolekcji
    void loadFromDB();//!< pobiera z bazy danych karty należące do kolekcji
    static bool checkCorrectnessC(const std::string &word);//!<sprawdza czy dany string jest poprawnym słowem
    void updateCardsToLearn(Session*);//!<daje sesji karty do nauki

};




#endif //ZPR_COLLECTION_H
