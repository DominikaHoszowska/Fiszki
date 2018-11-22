//
// Created by dominika on 19.11.18.
//

#ifndef ZPR_CARD_H
#define ZPR_CARD_H


#include <string>

class Card {
private:
    int id_;
    std::string pl_;
    std::string eng_;
    double EF_;
    struct tm* repetitionDay_;
public:

    void updateEF(unsigned int);

    const std::string &getPl_() const;

    const std::string &getEng_() const;

    Card(int id_, const std::string &pl_, const std::string &eng_);
    void setTodayDate();
};

#endif //ZPR_CARD_H
