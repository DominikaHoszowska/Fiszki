//
// Created by dominika on 19.11.18.
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
class Collection {
private:
    std::string name_;
public:
    const std::string &getName_() const;

    void setName_(const std::string &name_);

    unsigned int getId_() const;

    void setId_(unsigned int id_);

private:
    std::vector<std::unique_ptr<Card>> cards_;
    unsigned int id_;
    std::shared_ptr<Game> game_;
public:
    const std::shared_ptr<Game> &getGame_() const;

public:

    explicit Collection(const std::string &name_);
    void addFC(std::string&, std::string&,unsigned int);

};


#endif //ZPR_COLLECTION_H
