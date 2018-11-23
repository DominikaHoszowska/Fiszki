//
// Created by dominika on 19.11.18.
//

#ifndef ZPR_CARD_H
#define ZPR_CARD_H


#include <string>
#include <ctime>

class Card {
private:
    unsigned int id_;
    std::string pl_;
    std::string eng_;
    double EF_;
    std::time_t timeToRepeat_;
public:

    void updateEF(unsigned int);

    const std::string &getPl_() const;

    const std::string &getEng_() const;

    Card(unsigned int id_, const std::string &pl_, const std::string &eng_);
    void setTimeToRepeat(unsigned int);

};

#endif //ZPR_CARD_H
