//
// Created by Dominika on 19.11.18.
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
    Collection* collection_; //! wskaźnik na kolekcję
    unsigned int i_;//! przerwy między kolejnymi powtórkami

public:
    //Konstrukory:
    Card(unsigned int id_, const std::string &pl_, const std::string &eng_, double EF_,
         const boost::gregorian::date &timeToRepeat_, Collection* collection_, unsigned int i_);//!konstruktor używany przy zaciąganiu kart z DB
    Card(unsigned int id_, const std::string &pl_, const std::string &eng_);//! konstruktor używany przy tworzeniu nowej karty
    Card(const std::string &pl_, const std::string &eng_);//! konstruktor używany przy dodawaniu do gry

    //Gettery
    double getEF_() const;//! zwraca wskaźnik nauki fiszki
    unsigned int getI_() const;
    const std::string &getPl_() const; //! zwraca polskie znaczenie
    const std::string &getEng_() const;//! zwraca angielskie znaczenie
    const boost::gregorian::date &getTimeToRepeat_() const; //! funkcja zwracająca datę kolejnej powtórki fiszki
    Collection* getCollection_() const;

    //UpdateCard:
    void updateCard(double);
    void updateEF( double); //! aktulizuje wskaźnik uczenia
    void updateI();
    void updateTimeToRepeat();
    void updateCardDB();

    //Inne:

    static bool checkCorrectnessW(const std::string &word);//!sprawdza czy dany string jest poprawnym słowem
};
#endif //ZPR_CARD_H
