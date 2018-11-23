//
// Created by dominika on 19.11.18.
//

#ifndef ZPR_GAME_H
#define ZPR_GAME_H


#include <memory>
#include <vector>
#include "Collection.h"

class Game {
private:
    std::vector<std::unique_ptr<Collection>> collections_;
    std::string userName_;
    unsigned int actualFCId_;
public:
    Game();
    void addCollection(std::string);
    unsigned long numberOfCollections();
    void updateFCId();
};


#endif //ZPR_GAME_H
