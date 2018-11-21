//
// Created by dominika on 21.11.18.
//

#define BOOST_DYN_LINK
#ifdef BOOST_DYN_LINK

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(sample_test_suite)



BOOST_AUTO_TEST_CASE(sample_unit_test){
    BOOST_CHECK_EQUAL(true, false);

}

BOOST_AUTO_TEST_SUITE_END()


#endif
