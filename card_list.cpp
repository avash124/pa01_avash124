// card_list.cpp
// Author: Your name Aryan Vashishta
// Implementation of the classes defined in card_list.h
#include "card_list.h"
#include <iostream>

BST::~BST(){
    clear();
}

BST::Node* BST::getNode(const Card& c) const{ 
    Node* current = root;
    while(current != nullptr){
        if(current -> card == c){
            return current;
        }
        if(c < current -> card){
            current = current -> left;
        }
        else{ 
        current = current -> right;
        }
    }
    return nullptr;
}

BST:: Node* BST::getPredecessorNode(const Card& c) const{
    Node *current = getNode(c);
    if(current == nullptr){
        return nullptr;
    }
    if(current -> left != nullptr){
        Node* predecessor = current -> left;
        while(predecessor -> right != nullptr){
            predecessor = predecessor -> right;
        }
        return predecessor;
    }
    else{
        Node* parentNode = current -> parent;
        while (parentNode != nullptr && current == parentNode -> left){
            current = parentNode;
            parentNode = parentNode -> parent;
        }
        return parentNode;
    }     

}

BST:: Node* BST::getSuccessorNode(const Card& c) const{
    Node *current = getNode(c);
    if(current == nullptr){
        return nullptr;
    }
    if(current -> right != nullptr){
        Node* successor = current -> right;
        while(successor -> left != nullptr){
            successor = successor -> left;
        }
        return successor;
    }
    else{
        Node* parentNode = current -> parent;
        while (parentNode != nullptr && current == parentNode -> right){
            current = parentNode;
            parentNode = parentNode -> parent;
        }
        return parentNode;
    }
}

void BST::clear(){
    clearHelper(root);
    root = nullptr;
}

void BST::clearHelper(Node* node){
    if(node == nullptr){
        return;
    }
    clearHelper(node->left);
    clearHelper(node-> right);
    delete node;
}

bool BST::contains(const Card& c) const{
    return getNode(c) != nullptr;
}
       
bool BST::insert(const Card& c){
    if(root == nullptr){
        root = new Node(c);
        return true;
    }
    Node* current = root;
    Node* parent = nullptr;
    while(current!=nullptr){
        parent = current;
        if(current -> card == c){
            return false;
        }
        else if(current->card > c){
            current = current -> left;
        }
        else{
            current = current -> right;    
        }
    }

    Node* insert = new Node(c);
    insert -> parent = parent;
    if(parent -> card > c){
        parent -> left = insert;
    }
    else{
        parent -> right = insert;
    }

    return true;
}

bool BST::remove(const Card& c){
    Node* removeNode = getNode(c);
    if(removeNode == nullptr){
        return false;
    }
    else if(removeNode-> right == nullptr && removeNode-> left == nullptr){
        if(removeNode == root){
            delete root;
            root = nullptr;
        }
        else{
            if(removeNode->parent->right == removeNode){
                removeNode-> parent -> right = nullptr;
            }
            else{
                removeNode -> parent -> left = nullptr;
            }
            delete removeNode;
        }
    }

    else if (removeNode -> left == nullptr || removeNode -> right == nullptr){
        Node* childNode;
        if(removeNode -> left != nullptr){
            childNode = removeNode -> left;
        }
        else{
            childNode = removeNode -> right;
        }
        if(removeNode == root){
            root = childNode;
            root -> parent = nullptr;
            delete removeNode;
        }
        else{
            if (removeNode -> parent -> left == removeNode){
                removeNode -> parent -> left = childNode;
            }
            else{
            removeNode -> parent -> right = childNode;
            }

            childNode -> parent = removeNode -> parent; 
             delete removeNode;
        }
    }    
    else{
            Node* successor = getSuccessorNode(removeNode -> card);
            removeNode -> card = successor -> card;
            Node* successorChildNode = successor->right;
            if (successor->parent->left == successor) {
                successor->parent->left = successorChildNode;
            }   
            else {
                successor->parent->right = successorChildNode;
            }

            if (successorChildNode != nullptr) {
                successorChildNode->parent = successor->parent;
            }
            delete successor;
            }
            return true;
}
BST::Iterator& BST::Iterator::operator--(){
    if(current!=nullptr && bst!=nullptr){
        current = bst->getPredecessorNode(current->card);
    }
    return *this;
}

BST::Iterator& BST::Iterator::operator++(){
    if(current!=nullptr && bst!=nullptr){
        current = bst->getSuccessorNode(current->card);
    }
    return *this;
}

const Card& BST::Iterator:: operator*() const{
    return current -> card;
}

const Card* BST::Iterator::operator->() const{
    return &current-> card;
}

bool BST::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

bool BST::Iterator::operator !=(const Iterator& other) const{
    return current != other.current;
}

BST::Iterator BST::rbegin() const{
    Node* current = root;
    if(current == nullptr){
        return Iterator(nullptr,this);
    }
    while(current ->right != nullptr){
        current = current -> right;
    }

    return Iterator(current,this);
}

BST:: Iterator BST::begin()const{
     Node* current = root;
    if(current == nullptr){
        return Iterator(nullptr,this);
    }
    while(current -> left != nullptr){
        current = current -> left;
    }

    return Iterator(current,this);
}

BST::Iterator BST:: end() const{
    return Iterator(nullptr,this);
}

BST::Iterator BST:: rend() const{
    return Iterator(nullptr,this);
}

void BST::printDeck() const{
    for(Iterator it = begin(); it!=end(); ++it){
        std::cout << *it << std::endl;
    }
}

void playGame(BST& alice, BST& bob){
    bool aliceTurn = true; 
    bool gamePlay = true;
    while(gamePlay == true){
        bool pairFound = false;
        if(aliceTurn == true){
            for(BST::Iterator it = alice.begin(); it!=alice.end(); ++it){
                if(bob.contains(*it)){
                    pairFound = true;
                    std::cout<< "Alice picked matching card " << it->toString() << std::endl;
                    bob.remove(*it);
                    alice.remove(*it);
                    aliceTurn = false;
                    break;
                }
            }
        }
        else{
            for(BST::Iterator it = bob.rbegin(); it!=bob.rend(); --it){
                if(alice.contains(*it)){
                    std::cout << "Bob picked matching card " << it->toString() << std::endl;
                    pairFound = true;
                    alice.remove(*it);
                    bob.remove(*it);
                    aliceTurn = true;
                    break;
                }

            }
        }

        if(pairFound == false){
            gamePlay = false;
        }
    }
}