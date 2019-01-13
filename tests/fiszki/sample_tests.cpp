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


BOOST_AUTO_TEST_SUITE(sample_test_suite)


    BOOST_AUTO_TEST_CASE(createGameAndSetLanguage) {
        std::string base("baza.db");
        Game game(base);
        game.setLanguage(Game::Language::PL_ENG);
        BOOST_CHECK(game.getLanguage_() == Game::Language::PL_ENG);

    }

    BOOST_AUTO_TEST_CASE(addCollection) {
        std::string base("baza.db");
        Game game(base);
        game.setLanguage(Game::Language::PL_ENG);
        std::string collectionName("rodzina");
        game.addCollection(collectionName);
        BOOST_CHECK_EQUAL(game.ifCollectionNameUnique(collectionName), 0);
    }

    BOOST_AUTO_TEST_CASE(addCardsToGame) {
        std::string base("baza.db");
        Game game(base);
        game.setLanguage(Game::Language::PL_ENG);
        std::string collectionName("rodzina");
        game.addCard("mama", "mother");
        BOOST_CHECK_EQUAL(game.ifCardsToAddIsEmpty(), 0);
    }

    BOOST_AUTO_TEST_CASE(clearCardsToAdd) {
        std::string base("baza.db");
        Game game(base);
        game.setLanguage(Game::Language::PL_ENG);
        game.addCard("tata", "father");
        game.clearCardsToAdd();
        BOOST_CHECK_EQUAL(game.ifCardsToAddIsEmpty(), 1);
    }

    BOOST_AUTO_TEST_CASE(gettingCardsToLearn) {
        std::string base("baza.db");
        Game game(base);
        game.setLanguage(Game::Language::PL_ENG);
        std::string collectionName("rodzina");
        game.addCard("mama", "mother");
        game.addCardsToCollection(collectionName);
        std::shared_ptr<Collection> c = game.getCollection(collectionName);
        Session s = Session(c);
        std::shared_ptr<CardSession> cs = s.giveNextCard();
        BOOST_CHECK_EQUAL(cs->getCard_()->getPl_(), "mama");
    }

    BOOST_AUTO_TEST_CASE(gettingCardsToLearn2) {
        std::string base("baza.db");
        Game game(base);
        game.setLanguage(Game::Language::PL_ENG);
        std::string collectionName("rodzina");
        std::shared_ptr<Collection> c = game.getCollection(collectionName);
        Session s = Session(c);
        std::shared_ptr<CardSession> cs = s.giveNextCard();
        s.takeAnswer(cs, Session::Answer::GOOD);
        BOOST_CHECK_EQUAL(s.giveNextCard(), nullptr);
        BOOST_CHECK_EQUAL(s.getAllAnswers(), 1);

    }

    BOOST_AUTO_TEST_CASE(gettingCardsToLearn3) {
        std::string base("baza.db");
        Game game(base);
        game.setLanguage(Game::Language::PL_ENG);
        std::string collectionName("rodzina");
        std::shared_ptr<Collection> c = game.getCollection(collectionName);
        Session s = Session(c);
        game.addCard("tata","father");
        BOOST_CHECK_EQUAL(game.ifCardsToAddIsEmpty(),0);
        game.addCardsToCollection(collectionName);
        s.updateCardsToLearn();
        std::shared_ptr<CardSession> cs=s.giveNextCard();
        BOOST_CHECK_EQUAL(cs->getCard_()->getEng_(),"father");
        s.takeAnswer(cs,Session::Answer::BAD);
        BOOST_CHECK_EQUAL(cs->getCard_()->getPl_(),"tata");
        s.takeAnswer(cs,Session::Answer::MEDIUM);
        BOOST_CHECK_EQUAL(cs->getCard_()->getPl_(),"tata");
        s.takeAnswer(cs,Session::Answer::BAD);
        BOOST_CHECK_EQUAL(s.giveNextCard(), nullptr);
        BOOST_CHECK_EQUAL(s.getGood_(), 0);
        BOOST_CHECK_EQUAL(s.getMedium_(), 1);
        BOOST_CHECK_EQUAL(s.getBad_(), 2);
    }
    BOOST_AUTO_TEST_CASE(addingCardsToSession) {
        std::string base("baza.db");
        Game game(base);
        game.setLanguage(Game::Language::PL_ENG);
        std::string collectionName("rodzina");
        std::shared_ptr<Collection> c = game.getCollection(collectionName);
        game.addCard("kot", "cat");
        game.addCardsToCollection(collectionName);
        Session s = Session(c);
        BOOST_CHECK_EQUAL(s.cardsAreNotNull(),1);

    }

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


#endif
