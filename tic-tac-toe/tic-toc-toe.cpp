#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Глобальные константы
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

// Прототипы функций
void instructions();
char askYesNo(string question);
int askNumper(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(const vector<char>& board, char computer);
void annonceWinner(char winner, char computer, char human);

