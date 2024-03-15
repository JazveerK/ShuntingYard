//Thanks to Jayden for helping with the node files
#ifndef NODE_H
#define NODE_H

class Node {
private:
    char data;
    Node* next;
    Node* left;
    Node* right;

public:
    Node();
    Node(char newData);
    
    //Getters
    char getData();
    Node* getNext();
    Node* getLeft();
    Node* getRight();
    
    //Setters
    void setData(char newData);
    void setNext(Node* newNext);
    void setLeft(Node* newLeft);
    void setRight(Node* newRight);
};

#endif
