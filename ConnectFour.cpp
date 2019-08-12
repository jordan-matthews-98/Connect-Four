#include<iostream>
#include <string>
#include <algorithm> 

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
		repaint(board);
		do {
			do {
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
	int colVals[7] = { 0 };
	for (int col = 0; col < 7; ++col) {
		for (int row = 0; row < 6; ++row) {
			if (board[row][col] == ' ') {
				int verticalCounter = 1;
				for (int iRow = row + 1, stop = min(row + 3, 5); iRow <= stop && board[iRow][col] != 15; ++iRow)
					verticalCounter++;
				for (int iRow = row - 1, stop = max(row - 3, 0); iRow >= stop && board[iRow][col] != 15; --iRow)
					verticalCounter++;
				if (verticalCounter < 4)
					verticalCounter = 0;

				int horizontalCounter = 1;
				for (int iCol = col + 1, stop = min(col + 3, 6); iCol <= stop && board[row][iCol] != 15; ++iCol)
					horizontalCounter++;
				for (int iCol = col - 1, stop = max(col - 3, 0); iCol >= stop && board[row][iCol] != 15; --iCol)
					horizontalCounter++;
				if (horizontalCounter < 4)
					horizontalCounter = 0;

				int diagonalCounter1 = 1;
				for (int iRow = row + 1, iCol = col + 1, sCol = min(col + 3, 6), sRow = min(row + 3, 5); iCol <= sCol && iRow <= sRow && board[iRow][iCol] != 15; ++iCol, ++iRow)
					diagonalCounter1++;
				for (int iRow = row - 1, iCol = col - 1, sCol = max(col - 3, 0), sRow = max(row - 3, 0); iCol >= sCol && iRow >= sRow && board[iRow][iCol] != 15; --iCol, --iRow)
					diagonalCounter1++;
				if (diagonalCounter1 < 4)
					diagonalCounter1 = 0;

				int diagonalCounter2 = 1;
				for (int iRow = row - 1, iCol = col + 1, sCol = min(col + 3, 6), sRow = max(row - 3, 0); iCol <= sCol && iRow >= sRow && board[iRow][iCol] != 15; ++iCol, --iRow)
					diagonalCounter2++;
				for (int iRow = row + 1, iCol = col - 1, sCol = max(col - 3, 0), sRow = min(row + 3, 5); iCol >= sCol && iRow <= sRow && board[iRow][iCol] != 15; --iCol, ++iRow)
					diagonalCounter2++;
				if (diagonalCounter2 < 4)
					diagonalCounter2 = 0;

				colVals[col] = verticalCounter + horizontalCounter + diagonalCounter1 + diagonalCounter2;
				break;
			}
		}
	}
	return distance(colVals, max_element(colVals, colVals + 7));
}