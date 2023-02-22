#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>

#include "windows.h"

using namespace std;

//thread_local int i = 0;

thread_local  bool InvalidDomainFlag = false;

//#define max(a, b)  (((a) > (b)) ? (a) : (b)) 
//#define min(a, b)  (((a) < (b)) ? (a) : (b)) 

class BinaryTree {
public : 
	int  val;

	BinaryTree* left;
	BinaryTree* right;
	BinaryTree(int val_) : val(val_), left(nullptr), right(nullptr) {}
};

class LruCache {
private : 
	std::list<char> cache;
	int cache_capacity;
	std::map<int, int> get_key;
public : 
	LruCache(int cache_capacity_) : cache_capacity(cache_capacity_) {}
	char refer(int page_number, char ch = '\0');
	char get(int page_number, char ch);
	void display();
};

class Node {
	Node* next;
	int pg;
};

class Queue {
	Node* prev;
	Node* next;
public : 
	int cache_capacity;
	Queue();
	Queue(int cache_capacity_) : cache_capacity(cache_capacity_) {}
};

class LruCacheC {
	Node** hash_map;
	Queue* queue;
	int cache_capacity = 0;
	int page_counts = 0;
	LruCacheC(int page_counts_, int cache_capacity_);
};

// [2,3,1,1,4]

// 0, 1
int MinJumps(int p, vector<int>& nums) {

	int mini = INT_MAX;
	// 0 < 2, 1 < 4
	cout << "p = " << p << endl;
	int end = min(nums.size(), p + nums[p] + 1);
	cout << "end = " << end << endl;
	for (int i = p; i < end; ++i) {
		// 1 + 
		int tmp = 1 + MinJumps(i + 1, nums);
		mini = max(tmp, mini);
	}

	return mini;
}

int jump(vector<int>& nums) {
	int j = MinJumps(0, nums);
	return j;
}


void PrintLevel(BinaryTree* root) {

	queue<pair<int, BinaryTree*>> que;
	if (root) {
		que.push(make_pair(0, root)); 
	}

	int current_level = 0;
	while (!que.empty()) {
		std::pair<int, BinaryTree*> p = que.front();  
		que.pop();

		if (p.first == current_level) { 
			cout << p.second->val << " "; 
		} else {
			cout << endl;
			current_level = p.first; 
			cout << p.second->val << " ";
		}

		if (p.second && p.second->left) {
			que.push(make_pair(current_level + 1, p.second->left)); 
		}

		if (p.second && p.second->right) {
			que.push(make_pair(current_level + 1, p.second->right)); 
		}
	}
}
unordered_map<int, vector<int>> levels;

void PrintLevelR(BinaryTree* root, int level) {
	if (root) {
		if (levels.find(level) == levels.end()) {
			vector<int> tmp;
			tmp.push_back(root->val);
			levels[level] = tmp;
		} else {
			levels[level].push_back(root->val);
		}
	}

	if (root && root->left) {
		PrintLevelR(root->left, level + 1);
	}

	if (root && root->right) {
		PrintLevelR(root->right, level + 1);
	}
}

class SudokuSolver {

private:
	vector<vector<int>>& board;
	int boardDimensions;

	bool SolveHelper(int initialR, int initialC);
	bool AbidesRuleConstraints(int r, int c, int tryVals);
	bool FindEmptySpot(int& r, int& c);

public:
	enum STATE {
		SOLVED,
		UNSOLVED_BOARD
	};
	vector< vector<vector<int>> > board_state;
	SudokuSolver(vector<vector<int>>& board_, int boardDimensions_) : board(board_), boardDimensions(boardDimensions_) {}
	bool Solve();
	void PrintBoard(vector<vector<int>> board, STATE state);
};

class EQueens {
private:
	vector<vector<int>>& board;
	bool NoConflict(int r, int c);
	bool Place(int row);

public:
	EQueens(vector<vector<int>>& board_) : board(board_) {}
	void PrintBoard();

	bool Solve();

	void Print();
};