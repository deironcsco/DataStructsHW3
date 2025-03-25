#include "Deck.h"
#include <iostream>

void Deck::Enqueue(int item) {
  Node *newNode = new Node();
  newNode->cardNo = item;
  if (length == 0) {
    head = newNode;
  } else {
    tail->next = newNode;
  }
  tail = newNode;
  length++;
}

int Deck::Dequeue() {
  int item;
  if (length == 0) {
    std::cout << "The deck is empty" << std::endl;
    return -1;
  } else {
    Node *temp = head;
    head = head->next;
    item = temp->cardNo;
    delete temp;
    length--;
  }
  return item;
}

int Deck::Peek() {
  if (length == 0) {
    std::cout << "The deck is empty" << std::endl;
    return -1;
  } else {
    return head->cardNo;
  }
}

int Deck::DeckSize() { return length; }
