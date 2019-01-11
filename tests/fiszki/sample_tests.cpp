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

BOOST_AUTO_TEST_SUITE(sample_test_suite)


    BOOST_AUTO_TEST_CASE(sample_unit_test) {

        Game game=Game();
        game.setLanguage(Game::Language::PL_ENG);
        BOOST_CHECK(game.getLanguage_() == Game::Language::PL_ENG);
        game.addCollection("rodzina");
        std::shared_ptr<Collection> c=game.getCollection(1);
        c->addNewFC("mama","mother",game.getActualCardId_()+1);



      BOOST_CHECK_EQUAL(Card::checkCorrectnessW("]]"),0);
      BOOST_CHECK_EQUAL(Card::checkCorrectnessW("bąłść"),1);



}





BOOST_AUTO_TEST_SUITE_END()


#endif
