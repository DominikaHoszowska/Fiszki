//
// Created by Dominika on 19.11.18.
//

#ifndef ZPR_GAME_H
#define ZPR_GAME_H

#include <memory>
#include <vector>
#include <sqlite3/sqlite3.h>
#include "Collection.h"
#include "Card.h"



class Collection;
class Card;
/*!
 * \brief Klasa trzymająca wszystkie kolekcje użytkownika.
 */
class Game {
public:

    enum class Language : uint8_t {
        PL_ENG,
        ENG_PL
    };
    //GETTERS:

    Language getLanguage_() const;
    sqlite3 *getDb_() const;//! zwraca wskaźnik do bazy danych
    unsigned long numberOfCollections();//!<Zwraca ile kolekcji jest w bazie użytkownika.

    //SETTERS:

    void setLanguage(Language language);

    //OTHERS:

    Game(); //!konstruktor
    void addCollection(std::string);//!<Dodawanie kolekcji o zadanej nazwie
    void addCard(std::string,std::string);//Dodawnie karty do kolejki do późniejszego dodoania do kolekcji

private:

    std::vector<std::unique_ptr<Collection>> collections_;//!<wektor wskaźników na kolekcje użytkownika
    std::string userName_;//!<nazwa użytkownika
    unsigned int actualCollId_;//!<Największe ID kolekcji znajdującej się w bazie. Trzymamy je, żeby wiedzieć z jakim ID stworzymy kolejną
    sqlite3* db_; //! wskaźnik do bazy danych
    Language language_ =  Language::PL_ENG;//! 0-polski->angielski, 1-angielski->polski
    std::vector<std::shared_ptr<Card>>cardsToAdd_;

};


#endif //ZPR_GAME_H
