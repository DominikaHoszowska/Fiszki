//
// Created by Dominika on 19.11.18.
//

#ifndef ZPR_GAME_H
#define ZPR_GAME_H

#include <memory>
#include <vector>
#include <sqlite3/sqlite3.h>
#include "Collection.h"
class Collection;
/*!
 * \brief Klasa trzymająca wszystkie kolekcje użytkownika.
 */
class Game {
private:
    std::vector<std::unique_ptr<Collection>> collections_;//!<wektor wskaźników na kolekcje użytkownika
    std::string userName_;//!<nazwa użytkownika
    unsigned int actualCollId_;//!<Największe ID kolekcji znajdującej się w bazie. Trzymamy je, żeby wiedzieć z jakim ID stworzymy kolejną
    sqlite3* db_; //! wskaźnik do bazy danych
    bool gameMode_;//! tryb gry 0-samoocena, 1-wpisywanie
    bool language_;//! 0-polski->angielski, 1-angielski->polski

public:

    //GETTERS:

    bool getGameMode_() const;
    bool getLanguage_() const;
    sqlite3 *getDb_() const;//! zwraca wskaźnik do bazy danych
    unsigned long numberOfCollections();//!<Zwraca ile kolekcji jest w bazie użytkownika.

    //SETTERS:

    void setGameMode_(bool gameMode_);
    void setLanguage_(bool language_);

    //OTHERS:

    Game(); //!konstruktor
    void addCollection(std::string);//!<Dodawanie kolekcji o zadanej nazwie
};


#endif //ZPR_GAME_H
