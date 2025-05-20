#include <iostream>
#include <cassert>
#include <vector>
#include "card.h"
#include "card_list.h"

void testInsert() {
    BST bst;
    assert(!bst.contains(Card('h', "5")));
    bst.insert(Card('h', "5"));
    assert(bst.contains(Card('h', "5")));
    bst.insert(Card('c', "k"));
    bst.insert(Card('d', "3"));
    bst.insert(Card('s', "q"));
    bst.insert(Card('h', "9"));
    assert(bst.contains(Card('h', "5")));
    assert(bst.contains(Card('c', "k")));
    assert(bst.contains(Card('d', "3")));
    assert(bst.contains(Card('s', "q")));
    assert(bst.contains(Card('h', "9")));
    std::cout << "testInsert passed" << std::endl;
}

void testRemove() {
    BST bst;
    bst.remove(Card('s', "7")); 
    bst.insert(Card('s', "7"));
    bst.remove(Card('s', "7"));
    assert(!bst.contains(Card('s', "7")));
    bst.insert(Card('h', "2"));
    bst.insert(Card('c', "10"));
    bst.insert(Card('d', "a"));
    bst.insert(Card('s',"8"));
    bst.remove(Card('s', "7"));
    assert(!bst.contains(Card('s', "7")));
    bst.remove(Card('c', "10"));
    assert(!bst.contains(Card('c', "10")));
    bst.remove(Card('h', "2"));
    assert(!bst.contains(Card('h', "2")));
    bst.remove(Card('s', "8"));
    assert(!bst.contains(Card('s', "8")));
    std::cout << "testRemove passed" << std::endl;
}

void testContains() {
    BST bst;
    assert(!bst.contains(Card('d', "6")));
    bst.insert(Card('d', "6"));
    assert(bst.contains(Card('d', "6")));
    bst.insert(Card('s', "4"));
    assert(bst.contains(Card('s', "4")));
    bst.remove(Card('d', "6"));
    assert(!bst.contains(Card('d', "6")));
    assert(!bst.contains(Card('h', "k")));
    std::cout << "testContains passed" << std::endl;
}

void testGetSuccessorNode() {
    BST bst;
    assert(bst.getSuccessorNode(Card('c', "3")) == nullptr);
    bst.insert(Card('c', "3"));
    assert(bst.getSuccessorNode(Card('c', "3")) == nullptr);
    bst.insert(Card('c', "7")); 
    bst.insert(Card('c', "j")); 
    auto node = bst.getSuccessorNode(Card('c', "3"));
    assert(node != nullptr);
    assert(*BST::Iterator(node) == Card('c', "7"));
    assert(bst.getSuccessorNode(Card('c', "j")) == nullptr);
    assert(bst.getSuccessorNode(Card('h', "5")) == nullptr);
    std::cout << "testGetSuccessorNode passed" << std::endl;
}


void testGetPredecessorNode() {
    BST bst;
    assert(bst.getPredecessorNode(Card('h', "8")) == nullptr);
    bst.insert(Card('h', "8"));
    assert(bst.getPredecessorNode(Card('h', "8")) == nullptr);
    bst.insert(Card('h', "q"));
    bst.insert(Card('h', "a")); 
    auto node = bst.getPredecessorNode(Card('h', "q"));
    assert(node != nullptr);
    assert(*BST::Iterator(node) == Card('h', "8"));
    assert(bst.getPredecessorNode(Card('h', "8")) == nullptr);
    assert(bst.getPredecessorNode(Card('d', "5")) == nullptr);
    std::cout << "testGetPredecessorNode passed" << std::endl;
}

void testPrintDeck() {
    BST bst;
    std::cout << "Empty bst: " << std::endl;
    bst.printDeck();
    std::cout << std::endl;
    bst.insert(Card('h', "5"));
    std::cout << "Single node: " << std::endl;
    bst.printDeck();
    std::cout << std::endl;
    bst.insert(Card('c', "3"));
    bst.insert(Card('d', "7"));
    std::cout << "Multiple nodes: " << std::endl;
    bst.printDeck();
}

void testIteratorEmpty() {
    BST bst;
    assert(bst.begin() == bst.end());
    auto it = bst.begin();
    ++it; 
    assert(it == bst.end());
    assert(bst.rbegin() == bst.rend());
    auto rit = bst.rbegin();
    ++rit; 
    assert(rit == bst.rend());
    std::cout << "testIteratorEmpty passed" << std::endl;
}

void testIteratorSingle() {
    BST bst;
    bst.insert(Card('d', "10"));
    auto it = bst.begin();
    assert(*it == Card('d', "10"));
    ++it;
    assert(it == bst.end());
    ++it;
    assert(it == bst.end());
    auto rIt = bst.rbegin();
    assert(*rIt == Card('d', "10"));
    ++rIt;
    assert(rIt == bst.rend());
    ++rIt;
    assert(rIt == bst.rend()); 
    std::cout << "testIteratorSingle passed" << std::endl;
}

void testIteratorInorder() {
    BST bst;
    bst.insert(Card('s', "5"));
    bst.insert(Card('h', "8"));
    bst.insert(Card('c', "2"));
    std::vector<Card> values = {Card('c', "2"), Card('s', "5"), Card('h', "8")};
    auto it = bst.begin();
    for (const auto& card : values) {
        assert(it != bst.end());
        assert(*it == card);
        ++it;
    }
    assert(it == bst.end());
    ++it;
    assert(it == bst.end());
    std::cout << "testIteratorInorder passed" << std::endl;
}

void testIteratorReverse() {
    BST bst;
    bst.insert(Card('s', "5"));
    bst.insert(Card('h', "8"));
    bst.insert(Card('c', "2"));
    std::vector<Card> values = {Card('h', "8"), Card('s', "5"), Card('c', "2")};
    auto it = bst.rbegin();
    for (const auto& card : values) {
        assert(it != bst.rend());
        assert(*it == card);
        ++it;
    }
    assert(it == bst.rend());
    ++it;
    assert(it == bst.rend());
    std::cout << "testIteratorReverse passed" << std::endl;
}

void testIteratorComparison() {
    BST bst;
    bst.insert(Card('c', "7"));
    bst.insert(Card('d', "5"));
    auto it1 = bst.begin();
    auto it2 = bst.begin();
    assert(it1 == it2);
    ++it2;
    assert(it1 != it2);
    auto endIt = bst.end();
    assert(it1 != endIt);
    ++it1;
    ++it1;
    assert(it1 == endIt);
    std::cout << "testIteratorComparison passed" << std::endl;
}

void testClear() {
    BST bst;
    bst.clear();
    assert(bst.begin() == bst.end());
    bst.insert(Card('h', "5"));
    bst.insert(Card('c', "3"));
    bst.insert(Card('d', "7"));
    bst.clear();
    assert(bst.begin() == bst.end());
    assert(!bst.contains(Card('h', "5")));
    assert(!bst.contains(Card('c', "3")));
    assert(!bst.contains(Card('d', "7")));
    std::cout << "testClear passed" << std::endl;
}

void testCommonCards() {
    BST alice, bob;
    alice.insert(Card('d', "2"));
    alice.insert(Card('c', "4"));
    alice.insert(Card('s', "6"));
    bob.insert(Card('d', "2"));
    bob.insert(Card('h', "9"));
    bob.insert(Card('s', "6"));
    playGame(alice, bob);
    assert(!alice.contains(Card('d', "2")));
    assert(!bob.contains(Card('d', "2")));
    assert(!alice.contains(Card('s', "6")));
    assert(!bob.contains(Card('s', "6")));
    std::cout << "testCommonCards passed"<<std::endl;
}

void testOneEmpty() {
    BST alice;
    BST bob;
    bob.insert(Card('h', "3"));
    playGame(alice, bob);
    assert(bob.contains(Card('h', "3")));
    std::cout << "testOneEmpty passed"<< std::endl;
}

void testNoCommon() {
    BST alice;
    BST bob;
    alice.insert(Card('c', "10"));
    alice.insert(Card('s', "k"));
    bob.insert(Card('h', "7"));
    bob.insert(Card('d', "9"));
    playGame(alice,bob);
    assert(alice.contains(Card('c', "10")));
    assert(bob.contains(Card('h', "7")));
    std::cout << "testNoCommon passed" << std::endl;
}

int main() {
    testInsert();
    testRemove();
    testContains();
    testGetSuccessorNode();
    testGetPredecessorNode();
    testPrintDeck();
    testIteratorEmpty();
    testIteratorSingle();
    testIteratorInorder();
    testIteratorReverse();
    testIteratorComparison(); 
    testClear();
    testCommonCards();
    testOneEmpty();
    testNoCommon();
    std::cout << "All tests passed" << std::endl;
    return 0;
}