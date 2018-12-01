//
// Created by dominika on 19.11.18.
//

#ifndef ZPR_CARD_H
#define ZPR_CARD_H
#include <string>
#include <ctime>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "Collection.h"
#include <memory>
class Collection;
class Card {
private:
    unsigned int id_; //! Unikalne ID fiszki
    std::string pl_;//! Polskie znaczenie
    std::string eng_;//! Angielskie znaczenie
    double EF_; //! Wskaźnik nauki fiszki
    boost::gregorian::date timeToRepeat_; //! Data następnej powtórki
    std::shared_ptr<Collection> collection_; //! wskaźnik na kolekcję

public:
    unsigned int getId_() const;//! zwraca unikalne ID fiszki

    void setId_(unsigned int id_); //! ustawia ID

    void setPl_(const std::string &pl_); //! ustawia polskie znaczenie

    void setEng_(const std::string &eng_);//! ustawia angielskie znaczenie

    double getEF_() const;//! zwraca wskaźnik nauki fiszki

    Card(unsigned int id_, const std::string &pl_, const std::string &eng_);//! konstruktor

    void setEF_(double EF_);//! ustwia wskaźnik uczenia fiszki

    void updateEF(unsigned int); //! aktulizuje wskaźnik uczenia

    const std::string &getPl_() const; //! zwraca polskie znaczenie

    const std::string &getEng_() const;//! zwraca angielskie znaczenie

    Card(const std::string &pl_, const std::string &eng_);//! konstruktor
    void setNewTimeToRepeat(unsigned int);//! funkcja aktualizująca datę kolejnej powtórki fiszki

    const boost::gregorian::date &getTimeToRepeat_() const; //! funkcja zwracająca datę kolejnej powtórki fiszki

    void setTimeToRepeat_(const boost::gregorian::date &timeToRepeat_);//! funkcja ustawiająca datę powtórki fiszki
    void insertCardtoDB(); //! funkcja wstawiająca fiszkę do bazy danych

    const std::shared_ptr <Collection> &getCollection_() const; //! zwraca wskaźnik na kolekcję do której przypisana jest fiszka
};

#endif //ZPR_CARD_H
