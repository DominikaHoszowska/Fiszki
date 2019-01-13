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

private:
    std::vector<std::shared_ptr<Collection>> collections_;//!<wektor wskaźników na kolekcje użytkownika
    unsigned int actualCollId_;//!<Największe ID kolekcji znajdującej się w bazie. Trzymamy je, żeby wiedzieć z jakim ID stworzymy kolejną
    unsigned int actualCardId_;//!największe ID karty znajdujacej sie bazie
    sqlite3* db_;    //! wskaźnik do bazy danych
    Language language_ =  Language::PL_ENG;
    std::vector<std::shared_ptr<Card>>cardsToAdd_;



public:
    //Konstruktory:
    Game(); //!konstruktor

    //Destruktor:
    virtual ~Game();

    //Gettery:

    Language getLanguage_() const;
    sqlite3 *getDb_() const;//! zwraca wskaźnik do bazy danych
    unsigned long numberOfCollections();//!<Zwraca ile kolekcji jest w bazie użytkownika.
    std::shared_ptr<Collection> getCollection(unsigned int);//!zwraca kolekcje o zadanym id
    std::shared_ptr<Collection> getCollection(std::string&);//!zwraca kolekcję o zadaniej nazwie
    std::vector<std::string> getCollections(); //!Zwraca kolekcje które są w grze
    unsigned int getActualCardId_() const;

    //Settery:

    void setLanguage(Language language);
    void setDb_(sqlite3 *db_);//! ustawia baze danych, używana w FE
    void setActualCollId();//!Sprawdza jakie jest na większe id wśród naszych kolekcji

    //Inne:

    void addCollection(unsigned int, std::string);//!<Dodawanie kolekcji o zadanej nazwie i id
    void addCollection(std::string);//!znajduje odpowidnie Id dla kolekcji i wywoluje tworzenie nowej kolekcji
    void addCard(std::string,std::string);//!Dodawnie karty do kolejki do późniejszego dodania do kolekcji
    void addCardsToCollection(std::string);//!Dodaje karty ze schowka do wybranej kolekcji
    bool ifCardsToAddIsEmpty();//!zwraca czy są jakieś karty do dodatnia
    bool ifCollectionNameUnique(std::string&);//! sprawdza czy nazwa kolekcji jest unikalana
    void clearCardsToAdd();//!Czyści karty do dodatnia w przypadku rezygnacji użytkownika
    void loadCollectionsFromDB();//!zaciąga z bazy kolekcje
    void loadActualCardId();//! zaciąga największe Id z bazy
};


#endif //ZPR_GAME_H
