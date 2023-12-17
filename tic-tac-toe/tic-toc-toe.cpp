#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Global constants
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

// Function prototypes
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

int main() 
{
	system("chcp 1251");
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);
	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;
	displayBoard(board);
	while (winner(board) == NO_ONE) 
	{
		if (turn == human)
		{
			move = humanMove(board, human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(board);
		turn = opponent(turn);
	}
	annonceWinner(winner(board), computer, human);
}

void instructions();
{
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	cout << "--where human brains is pit agains silicon processor\n\n";
	cout << "Make your move known by entering a numper, 0 - 8. The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";
	cout << " 0 | 1 | 2\n";
	cout << " ---------\n";
	cout << " 3 | 4 | 5\n";
	cout << " ---------\n";
	cout << " 6 | 7 | 8\n\n";
	cout << "Prepare yourself, human. The battle is about to begin.\n\n";
}
// Функция задает пользователю вопрос, на который можно ответить да или нет.
char askYesNo(string question)
{
	char response;
	do
	{
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');
	return response;
}

// Функция запрашивает у пользователя число из определенного диапазона и продолжает задавать вопрос, 
// пока пользователь не введет соответствующее диапазону число
int askNumper(string question, int high, int low)
{
	int number;
	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	} while (number > high || number < low);
	return number;
}
// Спрашивает у пользхователя, хочет ли он ходить первым
char humanPiece()
{
	char go_first = askYesNo("Do you require the first move?");
	if (go_first == 'y')
	{
		cout << "\nThen take the first move. You will need it. \n";
		return X;
	}
	else
	{
		cout << "\nYour bravery will be your undoing... Iwill go first. \n";
		return O;
	}
}
// Узнает фигуру польз-ователя (Х или О) и на основании этой информации возвращает фигуру, 
// которой будет ходить соперник
char opponent(char piece)
{
	if (piece == X)
	{
		return O;
	}
	else
	{
		return X;
	}
}