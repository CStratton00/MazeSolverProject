//
// Created by Collin Stratton on 10/22/20.
//

#ifndef MAZESOLVER_STACK_H
#define MAZESOLVER_STACK_H

/*
 * Template Node class
 * Creates nodes used in the stack
 */
template<class T>
struct Node {
    T data;
    Node(T newData) {
        data = newData;
        next = nullptr;
    }
    struct Node* next;
};

/*
 * Template stack class
 * creates the basic functions of a stack
 */
template<class T>
class Stack {
private:
    Node<T> *head;
    Node<T> *tail;

    int length;

public:
    Stack() : head(nullptr), tail(nullptr), length(0) {}

    virtual void insert(T);
    virtual void pop();

    virtual bool empty() const { return length == 0; }
    virtual int size() const { return length; }

    virtual T &top() { return head->data; }
};

/*
 * Stack insert
 * pushes values into the top of the stack
 * adds one to length
 */
template<class T>
void Stack<T>::insert(T val) {
    Node<T> *n_node = new Node<T>(val);

    n_node->next = head;
    head = n_node;
    Node<T> *temp = head;

    while (temp->next != nullptr) { temp = temp->next; }
    tail = temp;

    length++;
}

/*
 * Stack pop
 * removes the top of the stack
 * removes one from the length
 */
template<class T>
void Stack<T>::pop() {
    if (empty()) return;

    Node<T> *temp = head;
    head = temp->next == nullptr ? nullptr : temp->next;

    if (tail == temp) { tail = head; };
    delete temp;

    length--;
};

#endif //MAZESOLVER_STACK_H
