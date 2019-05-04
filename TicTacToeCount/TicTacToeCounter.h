#pragma once
#include <map>
#include <set>
const int X = 1;
const int O = 2;
const int onlyWins = 1;
const int exactMoves = 2;
using namespace std;
class TicTacToeCounter
{
private:
	int _amountOfComb;
	int _amountOfDraws;
	set<map<int, int>> _comb;
	int _amountOfUniqDraws;
	int _currFlag;
	int _lastStep;
	bool SortedByExactMoves(map<int, int> currCollocation, int currDepth);
	void SetSignByNumberOfMove(int numberOfMove, int& where);
	bool SortedByWinsOnly(int currDepth, map<int, int> currCollocation);
	void PrintCombination(map<int, int> tmp);
	void RecursiveCount(int currDepth, map<int, int> currCollocation, int flag);
public:
	void PrintAllInformation();
	void PrintCombinations();
	set<map<int, int>> getUniqComb() { return _comb; };
	int getAmountOfUniqDraws() { return _amountOfUniqDraws; };
	int getAmountOfDraws() { return _amountOfDraws; };
	int getAmountOfUniqComb() { return (int)_comb.size(); };
	void CountCombinations(int lastStep, int flag);
	void Reset();
	void CountUniqDraws();
	bool HorizontalIsWinning(map<int, int>& t, int i);
	bool VerticalIsWinning(map<int, int>& t, int i);
	bool DiagonalIsWinning(map<int, int>& t);
	bool ThisCollocIsWinning(map<int, int>& t);
	TicTacToeCounter();
	~TicTacToeCounter();
};

