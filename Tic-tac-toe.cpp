#include <iostream>
#include <ctime>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;

bool checkWin(const char grid[][9], unsigned N)
{
	unsigned counterRows = 0;
	unsigned counterCols = 0;
	unsigned counterMainDiag = 0;
	unsigned counterOtherDiag = 0;

	unsigned j = 1;
	while (j <= N)
	{
		for (unsigned i = 1; i <= N - 1; i++)
		{
			if (grid[i][j] == grid[i + 1][j] && grid[i+1][j] != ' ') counterRows++;

			if (counterRows == N - 1) return true;
		}

		counterRows = 0;
		j++;
	}
	
	unsigned k = 1;
	while (k <= N)
	{
		for (unsigned i = 1; i <= N - 1; i++)
		{
			if (grid[k][i] == grid[k][i + 1] && grid[k][i + 1] != ' ') counterCols++;

			if (counterCols == N - 1) return true;
		}

		counterCols = 0;
		k++;
	}

	for (unsigned i = 1; i <= N - 1; i++)
	{
		if (grid[i][i] == grid[i + 1][i + 1] && grid[i + 1][i + 1] != ' ') counterMainDiag++;

		if (counterMainDiag == N - 1) return true;
	}

	unsigned d1 = 1, d2 = N;
	while (d1 <= N && d2 >= 1)
	{
		if (d1 + d2 == (d1 + 1) + (d2 - 1) && grid[d1][d2] == grid[d1 + 1][d2 - 1] && grid[d1 + 1][d2 - 1] != ' ') counterOtherDiag++;

		if (counterOtherDiag == N - 1) return true;
		d1++;
		d2--;
	}

return false;
}

bool gridIsFull(const char grid[][9], unsigned N)
{
	unsigned counter = 0;
	for (unsigned i = 1; i <= N; i++)
	{
		for (unsigned j = 1; j <= N; j ++)
		{
			if (grid[i][j] != ' ') counter++;
		}
	}
	
	return counter == N * N;

}

int main()
{
	unsigned answer;
	cout << "Choose game mode (1 - PvP, 2 - PvC): ";
	cin >> answer;
	unsigned N;
	do
	{
		cout << "Enter grid size (between 3 - 9): ";
		cin >> N;
	} while (N < 3 || N>9);


	char grid[9][9];
	for (unsigned i = 1; i <= N; i++)
	{
		for (unsigned j = 1; j <= N; j++)
		{
			grid[i][j] = ' ';
		}
	}

	//PvP 
	if (answer == 1)
	{
		bool flag = false;
		for (unsigned i = 1; i <= N; i++)
		{
			for (unsigned j = 1; j <= N; j++)
			{
				cout << "[ " << grid[i][j] << " ] ";
			}
			cout << endl;
		}

		do
		{
			unsigned x, y;

			do
			{
				cout << "It's player 1's turn. Enter x y coordinates (1-N): ";
				cin >> x >> y;
			} while (x<1 || x>N || y<1 || y>N || grid[x][y] != ' ');

			grid[x][y] = 'X';
			for (unsigned i = 1; i <= N; i++)
			{
				for (unsigned j = 1; j <= N; j++)
				{
					cout << "[ " << grid[i][j] << " ] ";
				}
				cout << endl;
			}

			if (checkWin(grid, N))
			{
				flag = true;
				cout << "Player 1 won! " << endl;
				break;
			}

			if (gridIsFull(grid, N))
			{
				flag = true;
				cout << "It's a tie! " << endl;
				break;
			}


			do
			{
				cout << "It's player 2's turn. Enter x y coordinates (1-N): ";
				cin >> x >> y;
			} 
			while (x<1 || x>N || y<1 || y>N || grid[x][y] != ' ');

			grid[x][y] = 'O';
			for (unsigned i = 1; i <= N; i++)
			{
				for (unsigned j = 1; j <= N; j++)
				{
					cout << "[ " << grid[i][j] << " ] ";
				}
				cout << endl;
			}

			if (checkWin(grid, N))
			{
				flag = true;
				cout << "Player 2 won! " << endl;
				break;
			}

			if (gridIsFull(grid, N))
			{
				flag = true;
				cout << "It's a tie! " << endl;
				break;
			}


		}
		  while (!flag);
	}

	//PvC
	else if (answer == 2)
	{
		bool flag = false;
		for (unsigned i = 1; i <= N; i++)
		{
			for (unsigned j = 1; j <= N; j++)
			{
				cout << "[ " << grid[i][j] << " ] ";
			}
			cout << endl;
		}

		do
		{
			unsigned x, y;

			do
			{
				cout << "It's the player's turn. Enter x y coordinates (1-N): ";
				cin >> x >> y;
			} 
			while (x<1 || x>N || y<1 || y>N || grid[x][y] != ' ');

			grid[x][y] = 'X';
			for (unsigned i = 1; i <= N; i++)
			{
				for (unsigned j = 1; j <= N; j++)
				{
					cout << "[ " << grid[i][j] << " ] ";
				}
				cout << endl;
			}

			if (checkWin(grid, N))
			{
				flag = true;
				cout << "The player won! " << endl;
				break;
			}

			if (gridIsFull(grid, N))
			{
				flag = true;
				cout << "It's a tie! " << endl;
				break;
			}


			cout << "It's the computer's turn."<<endl;
			do
			{
				srand((unsigned)time(0));
				x = rand() % N + 1;
				y = rand() % N + 1;
			} 
			while (grid[x][y] != ' ');

			grid[x][y] = 'O';
			for (unsigned i = 1; i <= N; i++)
			{
				for (unsigned j = 1; j <= N; j++)
				{
					cout << "[ " << grid[i][j] << " ] ";
				}
			cout << endl;
			}

		   if (checkWin(grid, N))
		   {
			   flag = true;
			   cout << "The computer won! " << endl;
			   break;
		   }

			if (gridIsFull(grid, N))
			{
				flag = true;
				cout << "It's a tie! " << endl;
				break;
			}
		} 
			while (!flag);
	}

	
	return 0;
}