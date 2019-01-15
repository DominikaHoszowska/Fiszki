//
// Created by Dominika on 21.11.18.
//

#define BOOST_DYN_LINK
#ifdef BOOST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <fiszki/Card.h>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include <fiszki/Game.h>
#include <fiszki/Card.h>
#include <memory>
#include <boost/date_time/gregorian_calendar.hpp>

struct F1
{
    std::unique_ptr<Game>game_;

    F1(){
        std::string db="baza.db";
        sqlite3* base;
        int src = sqlite3_open(db.c_str(), &base);

        if (src)
        {
              std::cout << "Nie mogę otworzyć bazy";

        }
        else {
            char *err_msg = nullptr;
            std::string sql = "DROP TABLE CARDS; "
                              "DROP TABLE COLLECTIONS;";
            sqlite3_exec(base, sql.c_str(), nullptr, nullptr, &err_msg);
            sqlite3_close(base);

            game_ = std::make_unique<Game>(db);
            }
    }

};
BOOST_AUTO_TEST_SUITE(withF1)

    BOOST_FIXTURE_TEST_CASE(createGameAndSetLanguage,F1) {
        game_->setLanguage(Game::Language::PL_ENG);
        BOOST_CHECK(game_->getLanguage_() == Game::Language::PL_ENG);

    }
    BOOST_FIXTURE_TEST_CASE(addCollection,F1) {
        std::string collectionName("rodzina");
        game_->addCollection(collectionName);
        BOOST_CHECK_EQUAL(game_->ifCollectionNameUnique(collectionName), 0);
    }

    BOOST_FIXTURE_TEST_CASE(addCardsToGame,F1) {
        game_->addCard("mama", "mother");
        BOOST_CHECK_EQUAL(game_->ifCardsToAddIsEmpty(), 0);
    }

    BOOST_FIXTURE_TEST_CASE(clearCardsToAdd,F1) {
            game_->addCard("tata", "father");
            game_->clearCardsToAdd();
            BOOST_CHECK_EQUAL(game_->ifCardsToAddIsEmpty(), 1);
        }
BOOST_AUTO_TEST_SUITE_END()

struct F2
{
    std::unique_ptr<Game>game_;

    F2(){
        std::string db="baza.db";
        sqlite3* base;
        int src = sqlite3_open(db.c_str(), &base);

        if (src)
        {
            std::cout << "Nie mogę otworzyć bazy";

        }
        else {
            char *err_msg = nullptr;
            std::string sql = "DROP TABLE CARDS; "
                              "DROP TABLE COLLECTIONS;";
            sqlite3_exec(base, sql.c_str(), nullptr, nullptr, &err_msg);
            sqlite3_close(base);

            game_ = std::make_unique<Game>(db);
            std::string collectionName("rodzina");
            game_->addCollection(collectionName);
        }
    }
};
BOOST_AUTO_TEST_SUITE(withF2)

    BOOST_FIXTURE_TEST_CASE(numbersOFCollections,F2) {
        BOOST_CHECK_EQUAL(game_->numberOfCollections(),1);
    }
    BOOST_FIXTURE_TEST_CASE(getCollectionInt,F2) {
        BOOST_CHECK_EQUAL(game_->getCollection(1)->getName_(),"rodzina");
    }
    BOOST_FIXTURE_TEST_CASE(getCollectionString,F2) {
        std::string collectionName("rodzina");

        BOOST_CHECK_EQUAL(game_->getCollection(collectionName)->getId_(),1);
    }
    BOOST_FIXTURE_TEST_CASE(getCollections,F2) {
        int i=game_->getCollections().size();
        BOOST_CHECK_EQUAL(i,1);
    }
    BOOST_FIXTURE_TEST_CASE(addCardSToCollection,F2) {
        game_->addCard("mama", "mather");
        game_->addCard("tata", "father");
        std::string collectionName("rodzina");
        game_->addCardsToCollection(collectionName);
        BOOST_CHECK_EQUAL(game_->getActualCardId_(),2);
    }
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(checkCorrectness)
    BOOST_AUTO_TEST_CASE(checkCorrectnessW) {
        BOOST_CHECK_EQUAL(Card::checkCorrectnessW("]]"), 0);
        BOOST_CHECK_EQUAL(Card::checkCorrectnessW("żźóąłść"), 1);
        BOOST_CHECK_EQUAL(Card::checkCorrectnessW("AlamakotaipsairybkiiświnkęMorską"), 0);
        BOOST_CHECK_EQUAL(Card::checkCorrectnessW(","), 0);
    }

    BOOST_AUTO_TEST_CASE(checkCorrectnessC) {

        BOOST_CHECK_EQUAL(Collection::checkCorrectnessC("rodzina1234"),1);
        BOOST_CHECK_EQUAL(Collection::checkCorrectnessC("ćma1'"),1);

    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(updateCard)
    BOOST_AUTO_TEST_CASE(updateEF){
        Collection* collection;
        Card* card=new Card(1,"dom","house",2,boost::gregorian::from_string("2018-1-1"),collection,2);
        card->updateEF(2);
        BOOST_CHECK_EQUAL(card->getEF_(),1.68);
        delete card;
    }
    BOOST_AUTO_TEST_CASE(updateEF2){
        Collection* collection;
        Card* card=new Card(1,"dom","house",1.1,boost::gregorian::from_string("2018-1-1"),collection,2);
        card->updateEF(1);
        BOOST_CHECK_EQUAL(card->getEF_(),1.1);
        delete card;
    }

    BOOST_AUTO_TEST_CASE(updateI){
        Collection* collection;
        Card* card=new Card(1,"dom","house",2,boost::gregorian::from_string("2018-1-1"),collection,2);
        card->updateEF(1);
        card->updateI();
        BOOST_CHECK_EQUAL(card->getI_(),2);
        delete card;
    }

    BOOST_AUTO_TEST_CASE(updateTimeToRepeat){
        Collection* collection;
        Card* card=new Card(1,"dom","house",2,boost::gregorian::from_string("2018-1-1"),collection,2);
        card->updateTimeToRepeat();
        BOOST_CHECK_EQUAL(card->getTimeToRepeat_(), boost::gregorian::day_clock::local_day()+boost::gregorian::days(card->getI_()));
    }
BOOST_AUTO_TEST_SUITE_END()

struct F3
{
    std::unique_ptr<Game>game_;
    std::shared_ptr<Collection> collection_;
    std::unique_ptr<Session> session_;
    F3(){
        std::string db="baza.db";
        sqlite3* base;
        int src = sqlite3_open(db.c_str(), &base);

        if (src)
        {
            std::cout << "Nie mogę otworzyć bazy";

        }
        else {
            char *err_msg = nullptr;
            std::string sql = "DROP TABLE CARDS; "
                              "DROP TABLE COLLECTIONS;";
            sqlite3_exec(base, sql.c_str(), nullptr, nullptr, &err_msg);
            sqlite3_close(base);
            game_ = std::make_unique<Game>(db);
            std::string collectionName("rodzina");
            game_->addCollection(collectionName);
            game_->addCard("mama", "mather");
            game_->addCard("tata", "father");
            game_->addCardsToCollection(collectionName);
            collection_=game_->getCollection(collectionName);
            session_=std::make_unique<Session>(collection_);
        }
    }
};
BOOST_AUTO_TEST_SUITE(withF3)
    BOOST_FIXTURE_TEST_CASE(gettingCardsToLearn,F3) {
        std::shared_ptr<CardSession> cs = session_->giveNextCard();
        BOOST_CHECK_EQUAL(cs->getCard_()->getPl_(), "mama");
    }


    BOOST_FIXTURE_TEST_CASE(gettingCardsToLearn2,F3) {
        std::shared_ptr<CardSession> cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::GOOD);
        cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::GOOD);
        BOOST_CHECK_EQUAL(session_->giveNextCard(),nullptr);
    }
    BOOST_FIXTURE_TEST_CASE(statistics,F3) {
        std::shared_ptr<CardSession> cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::GOOD);
        cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::BAD);
        cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::BAD);
        cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::MEDIUM);
        BOOST_CHECK_EQUAL(session_->getAllAnswers(),4);
        BOOST_CHECK_EQUAL(session_->getBad_(),2);
        BOOST_CHECK_EQUAL(session_->getMedium_(),1);
        BOOST_CHECK_EQUAL(session_->getGood_(),1);
    }


    BOOST_FIXTURE_TEST_CASE(updateCardsToLearn,F3) {
        std::shared_ptr<CardSession> cs = session_->giveNextCard();
        cs->getCard_()->updateCard(5);
        session_->updateCardsToLearn();
        cs = session_->giveNextCard();
        session_->takeAnswer(cs,Session::Answer::GOOD);
        BOOST_CHECK_EQUAL(session_->giveNextCard(), nullptr);

    }
    BOOST_FIXTURE_TEST_CASE(deleteCardsToLearn,F3) {
    std::shared_ptr<CardSession> cs;
    while( cs = session_->giveNextCard())
    {
        session_->deleteCard(cs);
    }
        BOOST_CHECK_EQUAL(session_->cardsAreNotNull(), 0);

    }
    BOOST_FIXTURE_TEST_CASE(getAverage,F3) {
        std::shared_ptr<CardSession> cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::GOOD);
        cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::BAD);
        cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::MEDIUM);
        BOOST_CHECK_EQUAL(cs->getAverage(),2);
    }
    BOOST_FIXTURE_TEST_CASE(getNumberOfScores,F3) {
        std::shared_ptr<CardSession> cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::GOOD);
        cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::BAD);
        BOOST_CHECK_EQUAL(cs->getNumberOfScores(),1);

        cs = session_->giveNextCard();
        session_->takeAnswer(cs, Session::Answer::MEDIUM);
        BOOST_CHECK_EQUAL(cs->getNumberOfScores(),2);
    }

BOOST_AUTO_TEST_SUITE_END()



#endif
