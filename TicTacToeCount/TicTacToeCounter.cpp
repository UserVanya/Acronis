#include "TicTacToeCounter.h"
#include <iostream>
using namespace std;

void TicTacToeCounter::CountCombinations(int lastStep, int flag){
	Reset();
	_currFlag = flag;
	_lastStep = lastStep;
	map<int, int> currCollocation;
	for (int i = 1; i <= 9; i++)
		currCollocation.insert(make_pair(i, 0));
	RecursiveCount(0, currCollocation, flag);
	CountUniqDraws();
}
void TicTacToeCounter::Reset() {
	_amountOfComb = 0;
	_amountOfDraws = 0;
	_comb.clear();
	_amountOfUniqDraws = 0;
	_currFlag = 0;
}
void TicTacToeCounter::CountUniqDraws() {
	for (auto item : _comb) {
		if (!ThisCollocIsWinning(item)) {
			_amountOfUniqDraws++;
		}
	}
}
bool TicTacToeCounter::HorizontalIsWinning(map<int, int>& t, int i) {
	return (t[1 + 3 * i] == t[2 + 3 * i] && t[2 + 3 * i] == t[3 + 3 * i] && t[3 + 3 * i] != 0);
}

bool TicTacToeCounter::VerticalIsWinning(map<int, int>& t, int i) {
	return (t[1 + i] == t[4 + i] && t[4 + i] == t[7 + i] && t[7 + i] != 0);
}

bool TicTacToeCounter::DiagonalIsWinning(map<int, int>& t) {
	return ((t[1] == t[5] && t[5] == t[9] && t[9] != 0) || (t[3] == t[5] && t[5] == t[7] && t[7] != 0));
}

bool TicTacToeCounter::ThisCollocIsWinning(map<int, int>& t) {
	for (int i = 0; i < 3; i++) {
		if (HorizontalIsWinning(t, i) || VerticalIsWinning(t, i)) {
			return true;
		}
	}
	if (DiagonalIsWinning(t)) {
		return true;
	}
	return false;
}

bool TicTacToeCounter::SortedByExactMoves(map<int, int> currCollocation, int currDepth) {
	if (ThisCollocIsWinning(currCollocation)) {
		_comb.insert(currCollocation);
		_amountOfComb++;
		return true;
	}
	else if (currDepth == (_lastStep - 1)) {
		for (int i = 1; i <= 9; i++) {
			if (currCollocation[i] == 0) {
				SetSignByNumberOfMove(_lastStep, currCollocation[i]);
				if (!ThisCollocIsWinning(currCollocation)) {
					_amountOfDraws++;
				}
				_comb.insert(currCollocation);
				currCollocation[i] = 0;
			}
		}
		_amountOfComb++;
		return true;
	}
	return false;
}

inline void TicTacToeCounter::SetSignByNumberOfMove(int numberOfMove, int& where) {
	if (numberOfMove % 2 == 1)
		where = X;
	else
		where = O;
	return;
}

inline bool TicTacToeCounter::SortedByWinsOnly(int currDepth, map<int, int> currCollocation) {
	if (ThisCollocIsWinning(currCollocation) && currDepth != _lastStep)
		return false;
	if (ThisCollocIsWinning(currCollocation) && currDepth == _lastStep) {
		_comb.insert(currCollocation);
		_amountOfComb++;
		return true;
	}
	return true;
}

void TicTacToeCounter::PrintCombination(map<int, int> tmp) {
	for (int i = 1; i <= 9; i++) {
		if (tmp[i] == X) {
			cout << "x ";
		}
		if (tmp[i] == O) {
			cout << "o ";
		}
		if (tmp[i] == 0) {
			cout << "_ ";
		}
		if (i % 3 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

void TicTacToeCounter::PrintAllInformation(){
	cout << "Step " << _lastStep << ": " << endl;
	cout << "combinations = " << this->_amountOfComb << endl;
	cout << "uniq comb = " << this->getAmountOfUniqComb() << endl;
	if (_currFlag == exactMoves) {
		cout << "draws = " << this->_amountOfDraws << endl;
		cout << "uniq draws = " << this->_amountOfUniqDraws << endl;
	}
	return;
}

void TicTacToeCounter::PrintCombinations() {
	for (auto item: _comb) {
		PrintCombination(item);
	}
}

void TicTacToeCounter::RecursiveCount(int currDepth, map<int, int> currCollocation, int flag) {
	if (flag == exactMoves) {
		if (SortedByExactMoves(currCollocation, currDepth))
			return;
	}
	else {		
		if(SortedByWinsOnly(currDepth, currCollocation))
			return;
	}
	for (int i = 1; i <= 9; i++) {
		if (currCollocation[i] == 0) {
			SetSignByNumberOfMove(currDepth + 1, currCollocation[i]);
			RecursiveCount(currDepth + 1, currCollocation, flag);			
			currCollocation[i] = 0;
		}
	}
	return;
}

TicTacToeCounter::TicTacToeCounter(){
}


TicTacToeCounter::~TicTacToeCounter(){
}
