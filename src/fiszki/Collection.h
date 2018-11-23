//
// Created by dominika on 19.11.18.
//

#ifndef ZPR_COLLECTION_H
#define ZPR_COLLECTION_H

#include <string>
#include <vector>
#include "Card.h"
#include <memory>

class Collection {
private:
    std::string name_;
    std::vector<std::unique_ptr<Card>> cards_;
public:

    Collection(const std::string &name_);


};


#endif //ZPR_COLLECTION_H
