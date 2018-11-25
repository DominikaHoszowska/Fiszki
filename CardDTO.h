//
// Created by dominika on 24.11.18.
//

#ifndef ZPR_CARDDTO_H
#define ZPR_CARDDTO_H
/*!\brief Struktura służąca do transferu do frontu.
 *
 *
 *
 */
struct CardDTO{
    unsigned int collectionID_;
    unsigned int cardID_;
    std::string pl_;
    std::string eng_;

};
#endif //ZPR_CARDDTO_H
