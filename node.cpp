//Thanks to Jayden for helping with the node files
#include <iostream>
#include <cstring>
#include "node.h"

Node::Node() {
    data = '\0';
    next = nullptr;
    left = nullptr;
    right = nullptr;
}

Node::Node(char newData) {
    data = newData;
    next = nullptr;
    left = nullptr;
    right = nullptr;
}

char Node::getData() {
    return data;
}

Node* Node::getNext() {
    return next;
}

Node* Node::getLeft() {
    return left;
}

Node* Node::getRight() {
    return right;
}

void Node::setData(char newData) {
    data = newData;
}

void Node::setNext(Node* newNext) {
    next = newNext;
}

void Node::setLeft(Node* newLeft) {
    left = newLeft;
}



void Node::setRight(Node* newRight) {
    right = newRight;
}
