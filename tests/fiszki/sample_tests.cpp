//
// Created by dominika on 21.11.18.
//

#define BOOST_DYN_LINK
#ifdef BOOST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <fiszki/Card.h>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>

BOOST_AUTO_TEST_SUITE(sample_test_suite)


//    BOOST_AUTO_TEST_CASE(sample_unit_test) {
//        unsigned int i = 1;
//        std::string a = "pies";
//        std::string b = "dog";
//        Card *c = new Card(i, a, b);
//        BOOST_CHECK_EQUAL(c->getYear_(), 2018);
//        BOOST_CHECK_EQUAL(c->getMonth_(), 11);
//        BOOST_CHECK_EQUAL(c->getDay_(), 22);
//    }




BOOST_AUTO_TEST_SUITE_END()


#endif
