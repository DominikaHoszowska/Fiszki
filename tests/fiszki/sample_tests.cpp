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

BOOST_AUTO_TEST_SUITE(sample_test_suite)


    BOOST_AUTO_TEST_CASE(sample_unit_test) {
        std::unique_ptr<Game> g=std::make_unique<Game>();
        g->addCollection("czlowiek");
        BOOST_CHECK_EQUAL(g->numberOfCollections(),1);
    }





BOOST_AUTO_TEST_SUITE_END()


#endif
