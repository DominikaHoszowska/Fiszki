//
// Created by dominika on 19.11.18.
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
public:
    sqlite3 *getDb_() const;

private:
    std::vector<std::unique_ptr<Collection>> collections_;//!<wektor wskaźników na kolekcje użytkownika
    std::string userName_;//!<nazwa użytkownika
    unsigned int actualFCId_;//!<Największe ID fiszki znajdującej się w bazie. Trzymamy je, żeby wiedzieć z jakim ID stworzymy kolejną
    sqlite3* storage_;
    sqlite3* db_;
    int src_;
public:
    int getSrc_() const;

public:
    Game();
    void addCollection(std::string);//!<Dodawanie kolekcji o zadanej nazwie
    unsigned long numberOfCollections();//!<Zwraca ile kolekcji jest w bazie użytkownika.
    void updateFCId();
};


#endif //ZPR_GAME_H
