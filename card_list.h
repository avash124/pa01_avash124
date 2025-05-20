// card_list.h
// Author: Your name
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H
#include "card.h"

class BST{
    private: 
        struct Node{
            Card card;
            Node* left;
            Node* right;
            Node* parent;
            Node(const Card& c): card(c), left(nullptr), right(nullptr), parent (nullptr){}
        };
        Node* root;
        

    public:
        BST(): root(nullptr){}
        ~BST();
        void  clear(); 
        void clearHelper(Node* node);
        bool insert(const Card& c);
        bool remove(const Card& c);
        bool contains(const Card& c) const;
        void printDeck() const;
        Node* getNode(const Card& c) const;
        Node* getPredecessorNode(const Card& c) const;
        Node* getSuccessorNode(const Card& c) const;

        class Iterator{
            private:
                Node* current; 
                const BST* bst;
            
            public:
                Iterator(Node* node = nullptr,const BST* bst=nullptr) : current (node), bst (bst)  {}
                Iterator& operator++();
                Iterator& operator--();
                const Card& operator* () const;
                const Card* operator ->() const;
                bool operator ==(const Iterator& other) const;
                bool operator !=(const Iterator& other) const;          

        };
            Iterator begin() const;
            Iterator end() const; 
            Iterator rbegin() const;
            Iterator rend() const;
    };

    void playGame(BST& alice, BST& bob);

#endif
