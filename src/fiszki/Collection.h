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
    std::string name_;//! nazwa kolekcji
    std::vector<std::shared_ptr<Card>> cards_; //! wektor wskaźników na fiszki
    unsigned int id_; //! unikalne ID
    Game* game_;//!wskaźnik na grę
public:
    Game *getGame_() const;

public:

    const std::string &getName_() const; //! zwraca nazwę kolekcji
    unsigned int getId_() const; //! zwraca ID kolekcji
    void setId_(unsigned int id_);//! ustawia ID kolekcji
    explicit Collection(const std::string &name_, unsigned int id_, Game* game_);
    void addNewFC(const std::string&, const std::string&, unsigned int); //! dodawanie fiszki do kolekcji
    void loadFromDB();
    static bool checkCorrectnessC(const std::string &word);//!sprawdza czy dany string jest poprawnym słowem
    void updateCardsToLearn(Session*);

};




#endif //ZPR_COLLECTION_H
