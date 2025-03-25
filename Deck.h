#pragma once
#include "Node.h"

// queue built with a linked list
class Deck {
private:
  Node *head{nullptr};
  Node *tail{nullptr};
  int length{0};

public:
  Deck() = default;
  void Enqueue(int);
  int Dequeue();
  int Peek();
  int DeckSize();
};
