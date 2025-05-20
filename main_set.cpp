// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  set<Card> Alice;
  set<Card> Bob;
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }
  
  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    char suit = line[0];
    string value = line.substr(2);
    Card card(suit,value);
    Alice.insert(card);
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    char suit = line[0];
    string value = line.substr(2);
    Card card(suit,value);
    Bob.insert(card);
  }
  cardFile2.close(); 

    bool aliceTurn = true; 
    bool gamePlay = true;
    while(gamePlay == true){
        bool pairFound = false;
        if(aliceTurn == true){
            for(auto it = Alice.begin(); it!=Alice.end(); ++it){
                if(Bob.count(*it)){
                    pairFound = true;
                    std::cout<< "Alice picked matching card " << *it << std::endl;
                    Bob.erase(*it);
                    auto removedCard = it;
                    ++it;
                    Alice.erase(removedCard);
                    aliceTurn = false;
                    break;
                }
            }
        }
        else{
            for(auto it = Bob.rbegin(); it!=Bob.rend(); ++it){
                if(Alice.count(*it)){
                    std::cout << "Bob picked matching card " << *it << std::endl;
                    pairFound = true;
                    Alice.erase(*it);
                    Bob.erase(prev(it.base()));
                    aliceTurn = true;
                    break;
                }

            }
        }

        if(pairFound == false){
            gamePlay = false;
        }
    }

    cout<<endl;
    cout<<"Alice's cards: " << endl;
    for(const auto& c: Alice){
      cout << c << endl;
    }

    cout<<endl;
    cout<<"Bob's cards: " << endl;
    for(const auto& c: Bob){
      cout << c << endl;
    }

  return 0;

}










