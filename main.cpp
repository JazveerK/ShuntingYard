// Jazveer Kaler
// 03/07/24
// Shunting Yard Algorithm with help from Tejas Pandit, Taaha Khan, and Jayden Huang
/* Used some random sources: 
    https://www.youtube.com/watch?v=kKjYSBeDpFA
    https://www.youtube.com/watch?v=A3ZUpyrnCbM
    https://www.geeksforgeeks.org/stack-set-4-evaluation-postfix-expression/
    https://rosettacode.org/wiki/Parsing/Shunting-yard_algorithm
    https://www.geeksforgeeks.org/binary-tree-set-1-introduction/
    https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
    https://www.geeksforgeeks.org/convert-infix-prefix-notation/
 */

#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

//Functions
void push(Node* &top, Node* newNode);
Node* pop(Node* &top);
Node* peek(Node* top);
void enqueue(Node* &front, Node* &rear, Node* newNode);
Node* dequeue(Node* &front);
bool isOperator(char c);
int precedence(char c);
void shuntingYard(const char* input, char* postfixExpression);
Node* buildExpressionTree(const char* postfixExpression);
void printInfix(Node* root);
void printPrefix(Node* root);
void printPostfix(Node* root);

int main() {
    char input[100];
    Node* root = nullptr;
    Node* stackTop = nullptr;
    Node* queueFront = nullptr;
    Node* queueRear = nullptr;
    bool running = true;
    char command[10];

    cout << endl << "Welcome to Shunting Yard" << endl;
    
    while (running) {
        //asking user to run program
        cout << endl << "Enter a command: " << endl;
        cout << "Calculate" << endl;
        cout << "Quit" << endl << endl;
        
        
        cin.get(command, 10);
        cin.clear();
        cin.ignore(100, '\n');
        
        if (strcmp(command, "Quit") == 0) {
            running = false;
        }
        
        else if (strcmp(command, "Calculate") == 0) {
            
            //Inputt
            cout << "Enter equation in infix notation: ";
            cin.getline(input, 100);
            
            char postfixExpression[100];
            shuntingYard(input, postfixExpression);

            root = buildExpressionTree(postfixExpression);
            
            //Output
            cout << "Postfix Expression: " << postfixExpression << endl;
            cout << "Infix Notation: ";
            printInfix(root);
            cout << endl;
            cout << "Prefix Notation: ";
            printPrefix(root);
            cout << endl;
            cout << "Postfix Notation: ";
            printPostfix(root);
            cout << endl;
        }
    }
    return 0;
}

//Stack functons
void push(Node* &top, Node* newNode) {
    newNode->setNext(top);
    top = newNode;
}

Node* pop(Node* &top) {
    if (top == nullptr) {
        cerr << "Stack underflow\n";
        return nullptr;
    }
    Node* data = top;
    top = top->getNext();
    return data;
}

Node* peek(Node* top) {
    if (top == nullptr) {
        cerr << "Stack is empty\n";
        return nullptr;
    }
    return top;
}

//Queue
void enqueue(Node* &front, Node* &rear, Node* newNode) {
    if (front == nullptr) {
        front = rear = newNode;
    } else {
        rear->setNext(newNode);
        rear = newNode;
    }
}

Node* dequeue(Node* &front) {
    if (front == nullptr) {
        cerr << "Queue is empty\n";
        return nullptr;
    }
    Node* data = front;
    front = front->getNext();
    return data;
    
    //    else if (front == rear) {
    //front == NULL;
    //rear == NULL;
//}
//else {
    //Node* temp = front;
    //front = front->getNext();
    //temp->setNext(NULL);
// }
    
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

//Precedence with carrots and parenthesis now
int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    //ADDED CARROTS AND PARENTHESIS
    else if (c == '^')
        return 3;
    else if (c == '(' || c == ')')
        return 0;
    return 0;
}


// The Actual Shunting Yard Algorithim
void shuntingYard(const char* input, char* postfixExpression) {
    Node* operatorStack = nullptr;
    Node* outputQueueFront = nullptr;
    Node* outputQueueRear = nullptr;
    int i = 0;

    while (input[i] != '\0') {
        char token = input[i];
        if (token == '(')
            push(operatorStack, new Node(token));
        else if (isdigit(token))
            enqueue(outputQueueFront, outputQueueRear, new Node(token));
        
        else if (token == ')') {
            while (operatorStack != nullptr && peek(operatorStack)->getData() != '(')
                enqueue(outputQueueFront, outputQueueRear, pop(operatorStack));
            pop(operatorStack);
        } 
        
        else if (isOperator(token)) {
            while (operatorStack != nullptr && precedence(peek(operatorStack)->getData()) >= precedence(token) && peek(operatorStack)->getData() != '(')
                enqueue(outputQueueFront, outputQueueRear, pop(operatorStack));
            push(operatorStack, new Node(token));
        }
        i++;
    }

    while (operatorStack != nullptr)
        enqueue(outputQueueFront, outputQueueRear, pop(operatorStack));

    // queue into postfixExpression
    Node* current = outputQueueFront;
    int j = 0;
    while (current != nullptr) {
        postfixExpression[j++] = current->getData();
        current = current->getNext();
    }
    postfixExpression[j] = '\0';
}

Node* buildExpressionTree(const char* postfixExpression) {
    Node* nodeStack = nullptr;
    int i = 0;

    while (postfixExpression[i] != '\0') {
        char token = postfixExpression[i];
        Node* newNode = new Node(token);
        if (!isOperator(token)) {
            newNode->setLeft(nullptr);
            newNode->setRight(nullptr);
        } 
        
        else {
            Node* right = pop(nodeStack);
            Node* left = pop(nodeStack);
            newNode->setLeft(left);
            newNode->setRight(right);
        }
        push(nodeStack, newNode);
        i++;
    }
    return pop(nodeStack);
}

void printInfix(Node* root) {
    if (root) {
        if (isOperator(root->getData()) && root->getData() != '(')
            cout << "(";
        printInfix(root->getLeft());
        cout << root->getData();
        printInfix(root->getRight());
        if (isOperator(root->getData()) && root->getData() != ')')
            cout << ")";
    }
}

void printPrefix(Node* root) {
    if (root) {
        cout << root->getData();
        printPrefix(root->getLeft());
        printPrefix(root->getRight());
    }
}

void printPostfix(Node* root) {
    if (root) {
        printPostfix(root->getLeft());
        printPostfix(root->getRight());
        cout << root->getData();
    }
}
