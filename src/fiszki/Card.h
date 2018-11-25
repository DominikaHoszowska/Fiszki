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
public:
    unsigned int getId_() const;

    void setId_(unsigned int id_);

    void setPl_(const std::string &pl_);

    void setEng_(const std::string &eng_);

    double getEF_() const;

    void setEF_(double EF_);


private:
    std::string eng_;
    double EF_;
    std::time_t timeToRepeat_;
public:
    time_t getTimeToRepeat_() const;

    void setTimeToRepeat_(time_t timeToRepeat_);

    void updateEF(unsigned int);

    const std::string &getPl_() const;

    const std::string &getEng_() const;

    Card(unsigned int id_, const std::string &pl_, const std::string &eng_);
    void setNewTimeToRepeat(unsigned int);

};

#endif //ZPR_CARD_H
