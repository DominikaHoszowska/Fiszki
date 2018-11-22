#include <iostream>
#include "fiszki/Card.h"

int main() {
    std::string a="pies";
    std::string b="dog";
    Card* c= new Card(1,a,b);
    return 0;
}