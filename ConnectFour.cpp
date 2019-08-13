#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;

const int BASE_WEIGHT = 1;
const int COMBO_WEIGHT = 4;
const int DEFENSIVE_WEIGHT = 6;
const char PLAYER = 15;
const char CPU = 254;

void repaint(char[][7]);
bool isWin(int, int, char [][7]);
bool gameOver(int, int, bool, char [][7]);
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
			while (!takeTurn(row, col, cpuTurn, board));
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

bool isWin(int r, int c, char board[][7]) {
	int vertical = 1;
	int horizontal = 1;
	int diagonal1 = 1;
	int diagonal2 = 1;
	int i;
	int ii;
	for (i = r + 1; i <= 5 && board[i][c] == board[r][c]; i++, vertical++);
	for (i = r - 1; board[i][c] == board[r][c] && i >= 0; i--, vertical++);
	if (vertical >= 4)
		return true;
	for (ii = c - 1; ii >= 0 && board[r][ii] == board[r][c]; ii--, horizontal++);
	for (ii = c + 1; ii <= 6 && board[r][ii] == board[r][c]; ii++, horizontal++);
	if (horizontal >= 4)
		return true;
	for (i = r - 1, ii = c - 1; i >= 0 && ii >= 0 && board[i][ii] == board[r][c]; diagonal1++, i--, ii--);
	for (i = r + 1, ii = c + 1; i <= 5 && ii <= 6 && board[i][ii] == board[r][c]; diagonal1++, i++, ii++);
	if (diagonal1 >= 4)
		return true;
	for (i = r - 1, ii = c + 1; i >= 0 && ii <= 6 && board[i][ii] == board[r][c]; diagonal2++, i--, ii++);
	for (i = r + 1, ii = c - 1; i <= 5 && ii >= 0 && board[i][ii] == board[r][c]; diagonal2++, i++, ii--);
	if (diagonal2 >= 4)
		return true;
	return false;
}

bool gameOver(int r, int c, bool cpuTurn, char board[][7]) {
    if(isWin(r, c, board)){
		if (cpuTurn) {
			cout << "You lost.\n";
            return true;
		}
		else {
			cout << "You won!\n";
            return true;
		}
    }
	return false;
}

bool takeTurn(int& row, int& col, bool& cpuTurn, char board[][7]) {
	char chip;
	if (cpuTurn) {
		chip = CPU;
		col = cpuChooseCol(board);
	}
	else {
		chip = PLAYER;
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
				int verticalCounterD = 0, verticalCounterC = 0, verticalCounter = 0, iRow, iCol, sRow, sCol;
				for (iRow = row + 1, sRow = min(row + 3, 5); iRow <= sRow && board[iRow][col] != PLAYER; ++iRow){
                    if(board[iRow][col] == CPU)
                        verticalCounterC += COMBO_WEIGHT;
					verticalCounter += BASE_WEIGHT;
				}
				for(; iRow <= sRow && board[iRow][col] == PLAYER; ++iRow){
                    verticalCounterD += DEFENSIVE_WEIGHT * (7 - (iRow - row));
				}
				for (iRow = row - 1, sRow = max(row - 3, 0); iRow >= sRow && board[iRow][col] != PLAYER; --iRow){
                    if(board[iRow][col] == CPU)
                        verticalCounterC += COMBO_WEIGHT;
					verticalCounter += BASE_WEIGHT;
				}
				for(; iRow >= sRow && board[iRow][col] == PLAYER; --iRow){
                    verticalCounterD += DEFENSIVE_WEIGHT * (7 - (row - iRow));
				}
				if (verticalCounterC >= COMBO_WEIGHT*3)
                    return col;
				if (verticalCounter < BASE_WEIGHT*3)
					verticalCounter = 0;
                else
                    verticalCounter += verticalCounterC;

				int horizontalCounterD = 0, horizontalCounterC = 0, horizontalCounter = 0;
				for (iCol = col + 1, sCol = min(col + 3, 6); iCol <= sCol && board[row][iCol] != PLAYER; ++iCol){
                    if(board[row][iCol] == CPU)
                        horizontalCounterC += COMBO_WEIGHT;
					horizontalCounter += BASE_WEIGHT;
				}
				for(; iCol <= sCol && board[row][iCol] == PLAYER; ++iCol){
                    horizontalCounterD += DEFENSIVE_WEIGHT * (7 - (iCol - col));
				}
				for (iCol = col - 1, sCol = max(col - 3, 0); iCol >= sCol && board[row][iCol] != PLAYER; --iCol){
                    if(board[row][iCol] == CPU)
                        horizontalCounterC += COMBO_WEIGHT;
					horizontalCounter += BASE_WEIGHT;
				}
				for(; iCol >= sCol && board[row][iCol] == PLAYER; --iCol){
                    horizontalCounterD += DEFENSIVE_WEIGHT * (7 - (col - iCol));
				}
				if (horizontalCounterC >= COMBO_WEIGHT*3)
                    return col;
				if (horizontalCounter < BASE_WEIGHT*3)
					horizontalCounter = 0;
                else
                    horizontalCounter += horizontalCounterC;

				int diagonalCounter1D = 0, diagonalCounter1C = 0, diagonalCounter1 = 0;
				for (iRow = row + 1, iCol = col + 1, sCol = min(col + 3, 6), sRow = min(row + 3, 5); iCol <= sCol && iRow <= sRow && board[iRow][iCol] != PLAYER; ++iCol, ++iRow){
                    if(board[iRow][iCol] == CPU)
                        diagonalCounter1C += COMBO_WEIGHT;
					diagonalCounter1 += BASE_WEIGHT;
				}
				for(; iCol <= sCol && iRow <= sRow && board[iRow][iCol] == PLAYER; ++iCol, ++iRow){
                    diagonalCounter1D += DEFENSIVE_WEIGHT * (7 - (iCol - col));
				}
				for (iRow = row - 1, iCol = col - 1, sCol = max(col - 3, 0), sRow = max(row - 3, 0); iCol >= sCol && iRow >= sRow && board[iRow][iCol] != PLAYER; --iCol, --iRow){
                    if(board[iRow][iCol] == CPU)
                        diagonalCounter1C += COMBO_WEIGHT;
					diagonalCounter1 += BASE_WEIGHT;
				}
				for(; iCol >= sCol && iRow >= sRow && board[iRow][iCol] == PLAYER; --iCol, --iRow){
                    diagonalCounter1D += DEFENSIVE_WEIGHT * (7 - (col - iCol));
				}
				if (diagonalCounter1C >= COMBO_WEIGHT*3)
                    return col;
				if (diagonalCounter1 < BASE_WEIGHT*3)
					diagonalCounter1 = 0;
                else
                    diagonalCounter1 += diagonalCounter1C;

				int diagonalCounter2D = 0, diagonalCounter2C = 0, diagonalCounter2 = 0;
				for (iRow = row - 1, iCol = col + 1, sCol = min(col + 3, 6), sRow = max(row - 3, 0); iCol <= sCol && iRow >= sRow && board[iRow][iCol] != PLAYER; ++iCol, --iRow){
                    if(board[iRow][iCol] == CPU)
                        diagonalCounter2C += COMBO_WEIGHT;
					diagonalCounter2 += BASE_WEIGHT;
				}
				for(; iCol <= sCol && iRow >= sRow && board[iRow][iCol] == PLAYER; ++iCol, --iRow){
                    diagonalCounter2D += DEFENSIVE_WEIGHT * (7 - (iCol - col));
				}
				for (iRow = row + 1, iCol = col - 1, sCol = max(col - 3, 0), sRow = min(row + 3, 5); iCol >= sCol && iRow <= sRow && board[iRow][iCol] != PLAYER; --iCol, ++iRow){
                    if(board[iRow][iCol] == CPU)
                        diagonalCounter2C += COMBO_WEIGHT;
					diagonalCounter2 += BASE_WEIGHT;
				}
				for(; iCol >= sCol && iRow <= sRow && board[iRow][iCol] == PLAYER; --iCol, ++iRow){
                    diagonalCounter2D += DEFENSIVE_WEIGHT * (7 - (col - iCol));
				}
				if (diagonalCounter2C >= COMBO_WEIGHT*3)
                    return col;
				if (diagonalCounter2 < BASE_WEIGHT*3)
					diagonalCounter2 = 0;
                else
                    diagonalCounter2 += diagonalCounter2C;

				colVals[col] = verticalCounter + horizontalCounter + diagonalCounter1 + diagonalCounter2 + max(max(max(verticalCounterD, horizontalCounterD), diagonalCounter1D), diagonalCounter2D);

				if(row < 5){
                    board[row + 1][col] = PLAYER;
                        if(isWin(row + 1, col, board))
                            colVals[col] = -1;
                    board[row + 1][col] = ' ';
				}
				break;
			}
		}
	}
	return distance(colVals, max_element(colVals, colVals + 7));
}
