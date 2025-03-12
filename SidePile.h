#pragma once

const int SIZE = 5;

//stack
class SidePile {
private:
	int cardList[SIZE];
	int length;
public:
	SidePile() = default;
	void Push(int);
	int Pop();
	bool IsEmpty();
	int PileSize();
};