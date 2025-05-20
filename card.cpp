// card.cpp
// Author: Your name Aryan Vashishta
// Implementation of the classes defined in card.h
#include "card.h"
#include <iostream>
#include <string>


Card::Card(char s,const std::string& v) : suit(s), value(v) {}

bool Card::operator == (const Card& other) const{
    return suit == other.suit && value == other.value;
}

bool Card:: operator < (const Card& other) const{
    if(suit != other.suit){
        return rankBySuit(suit) < rankBySuit(other.suit);
    }
    return rankByValue(value) < rankByValue(other.value);
}

bool Card:: operator > (const Card& other) const{
    if(suit != other.suit){
        return rankBySuit(suit) > rankBySuit(other.suit);
    }
    return rankByValue(value) > rankByValue(other.value);
}

std::string Card::toString() const {
    return std::string(1,suit) + " " + value;
}

int Card::rankByValue(const std::string& v) const{
    if(v == "a"){
        return 1;
    }
    else if(v == "j"){
        return 11;
    }
    else if(v == "q"){
        return 12;
    }
    else if(v == "k")
        return 13;
    else{
        return std::stoi(v);
    }
} 

int Card::rankBySuit(char s) const{
    if(s == 'c'){
        return 0;
    }
    else if(s == 'd'){
        return 1;
    }
    else if(s == 's'){
        return 2;
    }
    else{
        return 3;
    }
}

std::ostream& operator<<(std::ostream& os, const Card& card){
    os<<card.toString();
    return os;
}









