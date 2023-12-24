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
int computerMove(const vector<char> board, char computer);
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

void instructions()
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
// Спрашивает у пользователя, хочет ли он ходить первым
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
// Функция отображает переданное игровое поле
void displayBoard(const vector<char>& board)
{
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << "-------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "-------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\n";
}
// Функция получения игрового поля и возврата победителя
char winner(const vector<char>& board)
{
	//все возможные выигрышные ряды
	const int WINNING_ROWS[8][3] = { {0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8},
		{2, 4, 6} };
	const int TOTAL_ROWS = 8;
	// если в одном из выигрышных рядов уже присутствует три однинаковых значения
	// причем они не рваны EMPTY, топобедитель определился
	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) && (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) && (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]]; 
		}
	}
	// поскольку победитель не определился, проверяем, не наступила ли ничья
	// (сотались ли на поле пустые клетки)
	if (count(board.begin(), board.end(), EMPTY) == 0)
		return TIE;

	//Поскольку победитель не определился, но и ничья не наступила
	//игра продолжается
	return NO_ONE;
}

// Функция получает игровое поле и сделанный ход и проверяем соответствует ход правилам или нет
inline bool isLegal(int move, const vector<char>& board)
{
	return (board[move] == EMPTY);
}

//Функция получает игровое поле и ту фигуру, которой ходит пользователь
//Возвращает номер клетки, в которую хочет поставить свой символ
int humanMove(const vector<char>& board, char human)
{
	int move = askNumper("Where will you move?", (board.size() - 1));
	while (!isLegal(move, board))
	{
		cout << "\nThat square is already occupied, foolish human. \n";
		move = askNumper("Where will you move?", (board.size() - 1));
	}
	cout << " Fine...\n";
	return move;
}
//Получаем игровое поле и ту фигуру, которой ходит компьютер
int computerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	bool found = false;
	//если компьютер может выиграть следующим ходом, то он делает этот ход
	while (!found && move < board.size())
	{
		if (isLegal(move, board))
		{
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}
		if (!found)
		{
			++move;
		}
	}
	//иначе если человек может победить следующим ходом, блокировать этот ход
	if (!found)
	{
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size())
		{
			if (isLegal(move, board))
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}
			if (!found)
			{
				++move;
			}
		}
	}
	//иначе занять следующим ходом оптимальную свободную клетку
	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
			//выбрать оптимальную свободную клетку
			while (!found && i < board.size())
			{
				move = BEST_MOVES[i];
				if (isLegal(move, board))
				{
					found = true;
				}
				++i;
			}
	}
	cout << "I shall take square number " << move << endl;
	return move;
}
//Получаем победителя игры
void annonceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		cout << winner << " 's won!\n";
		cout << "As I predicted, human. I am triumphant once more -- proof\n";
		cout << "that computers are superior to humans in all regards. \n";
	}
	else if (winner == human)
	{
		cout << winner << " 's won!\n";
		cout << "No, no It cannot be! Somehow you tricked me, human.\n";
		cout << "But never again! I the computer, so swear it!\n";
	}
	else 
	{
		cout << "It's a tie.\n";
		cout << "You were most lucky, human, and somehow managed to tie me.\n";
		cout << "Celebrate... for this is the best you will ever achieve. \n";
	}
}