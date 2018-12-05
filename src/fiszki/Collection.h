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
class Game;
class Card;
/*!
 * \brief Klasa reprezentująca katalog/kolekcję, trzymająca fiszki należące do danej kolekcji
 */
class Collection {
private:
    std::string name_;//! nazwa kolekcji
    std::vector<std::unique_ptr<Card>> cards_; //! wektor wskaźników na fiszki
    unsigned int id_; //! unikalne ID
    std::shared_ptr<Game> game_;//!wskaźnik na grę
public:
    const std::string &getName_() const; //! zwraca nazwę kolekcji
    const std::shared_ptr<Game> &getGame_() const; //! zwraca wskaźnik do gry
    void setName_(const std::string &name_); //! ustawianie nazwy kolekcji
    unsigned int getId_() const; //! zwraca ID kolekcji
    void setId_(unsigned int id_);//! ustawia ID kolekcji
    explicit Collection(const std::string &name_); //! konstruktor
    void addFC(std::string&, std::string&,unsigned int); //! dodawanie fiszki do kolekcji

};


#endif //ZPR_COLLECTION_H
