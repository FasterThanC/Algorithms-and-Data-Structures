// C++ program for Knight Tour problem
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//#define N 5
int N;

int iterations = 0;
ofstream fd("protokolas.txt");

int solveKTUtil(int x, int y, int movei, int sol[10][10],
				int xMove[], int yMove[]);

/* A utility function to check if i,j are
valid indexes for N*N chessboard */
int isSafe(int x, int y, int sol[10][10], int l)
{
	if (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1)
	{
		return 1;
	}
	else if (x >= 0 && x < N && y >= 0 && y < N)
	{
		fd << "Siulas." << endl;
		return 0;
	}
	else
	{
		fd << "Uz krasto. LENTA[" << x + 1 << "," << y + 1 << "]:=" << l + 1 << endl;
		return 0;
	}
}

/* A utility function to print
solution matrix sol[N][N] */
void printSolution(int sol[10][10])
{
	cout << "  Y, V ^" << endl;
	fd << "  Y, V ^" << endl;

	for (int y = N-1; y >= 0; y--)
	{
		cout << "     " << y + 1 << " |";
		fd << "     " << y + 1 << " |";

		for (int x = 0; x < N; x++)
		{
			cout << " " << setw(2) << sol[x][y] + 1;
			fd << " " << setw(2) << sol[x][y] + 1;
		}

		cout << endl;
		fd << endl;
	}

	cout << "       -";
	fd << "       -";
	for (int i = 0; i <= N; i++)
	{
		cout << "---";
		fd << "---";
	}
	cout << "> X, U" << endl;
	fd << "> X, U" << endl;

	cout << "        ";
	fd << "        ";
	for (int i = 1; i <= N; i++)
	{
			cout << " " << setw(2) << i;
			fd << " " << setw(2) << i;
	}

}

/* This function solves the Knight Tour problem using
Backtracking. This function mainly uses solveKTUtil()
to solve the problem. It returns false if no complete
tour is possible, otherwise return true and prints the
tour.
Please note that there may be more than one solutions,
this function prints one of the feasible solutions. */
int solveKT()
{
	int sol[10][10];

	/* Initialization of solution matrix */
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			sol[x][y] = -1;

	/* xMove[] and yMove[] define next move of Knight.
	xMove[] is for next value of x coordinate
	yMove[] is for next value of y coordinate */
	int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

	// Since the Knight is initially at the first block
	sol[0][0] = 0;

	/* Start from 0,0 and explore all tours using
	solveKTUtil() */
	if (solveKTUtil(0, 0, 1, sol, xMove, yMove) == 0) {
		cout << "Sprendinys nerastas." << endl;

		fd << endl << "TRECIA DALIS. Rezultatai" << endl;
		fd << "  1) Atlikta " << iterations << " bandymu." << endl;
		fd << "  2) Apejimas nerastas." << endl;
		return 0;
	}
	else
		cout << "Atlikta " << iterations << " bandymu." << endl;
		cout << "Apejimas rastas." << endl;
		cout << "Apejimas grafiskai: " << endl << endl;

		fd << endl << "TRECIA DALIS. Rezultatai" << endl;
		fd << "  1) Atlikta " << iterations << " bandymu." << endl;
		fd << "  2) Apejimas rastas." << endl;
		fd << "  3) Apejimas grafiskai: " << endl << endl;

		printSolution(sol);

	return 1;
}

/* A recursive utility function to solve Knight Tour
problem */
int solveKTUtil(int x, int y, int movei, int sol[10][10], int xMove[8], int yMove[8]) //movei = L; next_x = U; next_Y = V; k = R1, R2...
{
	int k, next_x, next_y;
	if (movei == N * N)
		return 1;

	/* Try all next moves from
	the current coordinate x, y */
	for (k = 0; k < 8; k++) {
		iterations++;
		next_x = x + xMove[k];
		next_y = y + yMove[k];

		fd << setw(8) << iterations << ") ";
		for (int i = 1; i < movei; ++i)
        {
            fd << "-";
        }

		fd << "R" << k + 1 << ". U=" << next_x+1 << ", V=" << next_y+1 << ", L=" << movei + 1 << ". ";

		if (isSafe(next_x, next_y, sol, movei)) {
			fd << "Laisva. LENTA[" << next_x + 1 << "," << next_y + 1<< "]:=" << movei + 1 << endl;

			sol[next_x][next_y] = movei;

			if (solveKTUtil(next_x, next_y, movei + 1, sol, xMove, yMove) == 1)
			{
				return 1;
			}
			else
			{
				// backtracking
				sol[next_x][next_y] = -1;
			}
		}
	}
	return 0;
}

// Driver Code
int main()
{
	system("cls");
    cout << "Vadim Ceremisinov 4 grupe 1 pogrupis." << endl;
    cout << "Algoritmu ir Duomenu strukturu 2 uzduotis 4 variantas." << endl;
    cout << "Uzduotis - Apeiti kvadrata N*N zirgo ejimais. Vartotojas nurodo kvadrato dydi N."<<endl;
    cout << "Programa atvaizduoja kokia ejimu tvarka zirgas apeina lenta, kurios ismatavimai NxN." << endl << endl;

    cout << "Prasome ivesti lentos ismatavima N: "<<endl;
    cin >> N;
	cout << endl;

	cout << "Veiksmai atliekami su " << N << "x" << N << " lenta." <<endl;

	fd << "PIRMA DALIS. Duomenys" << endl;
	fd << "  1) Vadim Ceremisinov 4 grupe 1 pogrupis." << endl;
	fd << "  2) Uzduotis - Apeiti kvadrata N*N zirgo ejimais. Vartotojas nurodo kvadrato dydi N." << endl;
	fd << "  3) Veiksmai atliekami su " << N << "x" << N << " lenta." << endl << endl;
	fd << "ANTRA DALIS. Vykdymas" << endl;

	// Function Call
	solveKT();
	return 0;
}




