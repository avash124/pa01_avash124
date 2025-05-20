// card.h
// Author: Your name Aryan Vashishta
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>

class Card{

public:
    char suit;
    std::string value;

    Card(char s,const std::string& v);
    bool operator == (const Card& other) const;
    bool operator < (const Card& other) const; 
    bool operator > (const Card& other) const; 

    std::string toString() const; 
    int rankBySuit(char s) const;
    int rankByValue(const std::string& v) const;
    
};

std::ostream& operator<<(std::ostream& os, const Card& card); 

#endif
