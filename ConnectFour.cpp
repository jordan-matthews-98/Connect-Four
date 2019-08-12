#include<iostream>
#include <string>

using namespace std;

void repaint(char[][7]);
bool gameOver(int, int, bool, char board[][7]);
bool takeTurn(int&, int&, bool&, char[][7]);
bool continuePlaying();
int cpuChooseCol(char board[][7]);

int main() {
	do {
		char board[6][7];
		memset(board, ' ', sizeof(char) * 6 * 7);
		bool cpuTurn = false;
		int row, col;
		do {
			do {
				repaint(board);
			} while (!takeTurn(row, col, cpuTurn, board));
			repaint(board);
		} while (!gameOver(row, col, !cpuTurn, board));
	} while (continuePlaying());

	return 0;
}

void repaint(char board[][7]) {
	system("cls");
	cout << " 1   2   3   4   5   6   7\n";
	for (int a = 5; a >= 0; a--) {
		for (int b = 0; b <= 6; b++)
			cout << char(218) << char(196) << char(191) << " ";
		cout << '\n';

		for (int b = 0; b <= 6; b++)
			cout << char(179) << board[a][b] << char(179) << " ";
		cout << '\n';

		for (int b = 0; b <= 6; b++)
			cout << char(192) << char(196) << char(217) << " ";
		cout << '\n';
	}
}

bool gameOver(int r, int c, bool cpuTurn, char board[][7]) {
	int vertical = 1;
	int horizontal = 1;
	int diagonal1 = 1;
	int diagonal2 = 1;
	int i;
	int ii;
	for (i = r + 1; i <= 5 && board[i][c] == board[r][c]; i++, vertical++);
	for (i = r - 1; board[i][c] == board[r][c] && i >= 0; i--, vertical++);
	if (vertical >= 4) {
		if (cpuTurn) {
			cout << "You lost.\n";
		}
		else {
			cout << "You won!\n";
		}
		return true;
	}
	for (ii = c - 1; ii >= 0 && board[r][ii] == board[r][c]; ii--, horizontal++);
	for (ii = c + 1; ii <= 6 && board[r][ii] == board[r][c]; ii++, horizontal++);
	if (horizontal >= 4) {
		if (cpuTurn) {
			cout << "You lost.\n";
		}
		else {
			cout << "You won!\n";
		}
		return true;
	}
	for (i = r - 1, ii = c - 1; i >= 0 && ii >= 0 && board[i][ii] == board[r][c]; diagonal1++, i--, ii--);
	for (i = r + 1, ii = c + 1; i <= 5 && ii <= 6 && board[i][ii] == board[r][c]; diagonal1++, i++, ii++);
	if (diagonal1 >= 4) {
		if (cpuTurn) {
			cout << "You lost.\n";
		}
		else {
			cout << "You won!\n";
		}
		return true;
	}
	for (i = r - 1, ii = c + 1; i >= 0 && ii <= 6 && board[i][ii] == board[r][c]; diagonal2++, i--, ii++);
	for (i = r + 1, ii = c - 1; i <= 5 && ii >= 0 && board[i][ii] == board[r][c]; diagonal2++, i++, ii--);
	if (diagonal2 >= 4) {
		if (cpuTurn) {
			cout << "You lost.\n";
		}
		else {
			cout << "You won!\n";
		}
		return true;
	}
	return false;
}

bool takeTurn(int& row, int& col, bool& cpuTurn, char board[][7]) {
	char chip;
	if (cpuTurn) {
		chip = 254;
		col = cpuChooseCol(board);
	}
	else {
		chip = 15;
		cout << "Choose a column. (1 - 7)\n";
		cin >> col;
		--col;
	}

	for (row = 0; row < 6; ++row) {
		if (board[row][col] == ' ') {
			board[row][col] = chip;
			cpuTurn = !cpuTurn;
			return true;
		}
	}
	return false;
}

bool continuePlaying() {
	cout << "Another? (y/n)\n";
	char a;
	cin >> a;
	return a == 'y';
}

int cpuChooseCol(char board[][7]) {
	for (int col = 0; col < 7; ++col) {
		if (board[5][col] == ' ') {
			return col;
		}
	}
}