#include "SidePile.h"

void SidePile::Push(int card) {
  if (length < 5) {
    cardList[length] = card;
    length++;
  }
}

int SidePile::Pop() {
  if (length > 0) {
    length--;
    return cardList[length];
  }
  return -1;
}

bool SidePile::IsEmpty() { return length == 0; }

int SidePile::PileSize() { return length; }
