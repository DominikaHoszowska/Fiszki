//
// Created by dominika on 19.11.18.
//

#include "Card.h"

void Card::updateEF(unsigned int value) {
    //TODO

}


const std::string &Card::getPl_() const {
    return pl_;
}

const std::string &Card::getEng_() const {
    return eng_;
}

Card::Card(int id_, const std::string &pl_, const std::string &eng_) : id_(id_), pl_(pl_), eng_(eng_), EF_(3.5){}


