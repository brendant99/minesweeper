#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;
void update(int a[], int rows, int cols);
void test(int a[], int a2[], int index);
int counter = 0;
int bnum;
int r, c;
int main()
{
	srand((unsigned)time(0));
	int randnum;
	int bnum;
	// Dimensions of the 2D array 
	int memory = 0;
	cout << "Input row size: ";
	cin >> r;
	cout << "Input column size: ";
	cin >> c;
	// int fc;
	// cout << "Input desired first cell: ";
	// cin >> fc;

	// Declare a memory block of 
	// size r*c 
	int* arr = new int[r * c];


	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {

			// Assign values to 
			// the memory block 
			*(arr + i * c + j) = memory;
		}
	}


	/*for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {

			// Print values of the 
			// memory block 
			cout << *(arr + i * c + j)
				<< " ";
		}
		cout << endl;
	}*/

	cout << "Enter number of bombs: ";
	cin >> bnum;						//enter bnum


	int urows2, ucols2;
	cout << "Enter row and column: ";
	cin >> urows2 >> ucols2;
	int ucell = (ucols2 - 1) + (c * (urows2 - 1));
	
	// debug cout << "Bomb locations: " << endl;
	int* bombs = new int[bnum];			//create array the size of #bombs

	for (int i = 0; i < bnum; i++)		//create bnum bombs, loop bnum times + duplicate errors
	{
		randnum = rand() % (r * c);		//generate bombnum for bombs[i]
		while(randnum ==  ucell || randnum == ucell + 1 || randnum == ucell - 1 
			|| randnum == ucell + c || randnum == ucell - c || randnum == ucell + c + 1 || randnum == ucell + c -1 || randnum == ucell -1 - c || randnum == ucell + 1 - c )
			randnum = rand() % (r * c);
		if (i == 0)
		{
			bombs[i] = randnum;
		}
		else
		{
			for (int j = 0; j < i; j++)				//check for duplicates
			{
				if (randnum == bombs[j])
				{
					randnum = rand() % (r * c);
					j--;
				}
				else
					bombs[i] = randnum;
			}
		}


		// debug cout << bombs[i] << ", "; 
	}




	for (int i = 0; i < (r * c); i++)				//assign bomb locations
	{
		for (int j = 0; j < bnum; j++)				// traverse bombs[]
		{
			if (i == bombs[j])
			{
				arr[i] = 9;							//assign bomb location
			}
		}
	}


	cout << "Bombs placed: " << endl;
	/*for (int i = 0; i < r; i++) {						//print bomb board
		for (int j = 0; j < c; j++) {

			// Print values of the
			// memory block
			cout << *(arr + i * c + j)
				<< " ";
		}
		cout << endl;
	}*/


	update(arr, r, c);

	cout << "Bomb counters updated: " << endl;  //print revealed game board
	/*for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {

			// Print values of the
			// memory block
			cout << *(arr + i * c + j)
				<< " ";
		}
		cout << endl;
	}*/

	int* arr2 = new int[r * c];			// create shown board (update board)

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {

			// Assign values to 
			// the memory block 
			*(arr2 + i * c + j) = -1;
		}
	}

	//test(arr, arr2, ucell); //make first move with entered cell

	cout << "Hidden board: " << endl;  //print new board
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			// Print values of the 
			// memory block 
			cout << *(arr + i * c + j)
				<< " ";
		}
		cout << endl;
	}

	test(arr, arr2, ucell); //make first move with entered cell
	
	cout << "Game board: " << endl;  //print new board
	for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {

				// Print values of the 
				// memory block 
				if ((*(arr2 + i * c + j) == (-1)))
					cout << "?" << " ";
				else
					cout << *(arr2 + i * c + j) << " ";
			}
			cout << endl;
		}
	

	/*cout << "Game board: " << endl;  //print new board
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {

			// Print values of the 
			// memory block 
			cout << "?"
				<< " ";
		}
		cout << endl;
	}*/

	int count = r * c - bnum;
	int flag = 0;
	while (flag == 0)
	{
		int guessflag = 0;
		int cell;
		//cout << count + counter << " tiles left, enter a cell #: ";
		int urows, ucols;
		cout << count + counter << " tiles left, Enter row and column: ";
		cin >> urows >> ucols;
		while (urows > r || ucols > c || urows <= 0 || ucols <= 0)
		{
			cout << "Row or column out of bounds -- " << count + counter << " tiles left, Enter row and column: ";
			cin >> urows >> ucols;
		}
		cell = (ucols - 1) + (c * (urows - 1)); // = ucols - 1
		//cin >> cell;
		arr2[cell] = arr[cell];

		if (arr[cell] == 9)
			flag = 1; // lose game, exit loop

		if (arr[cell] == 0) // floodfill 0s if we find a 0
		{
			test(arr, arr2, cell);
		}
		else
		{
			count--;
		}


		cout << "********************************" << endl;  //print new board
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {

				// Print values of the 
				// memory block 
				if ((*(arr2 + i * c + j) == (-1)))
					cout << "?" << " ";
				else
					cout << *(arr2 + i * c + j) << " ";
			}
			cout << endl;
			if (counter + count == 0)
				flag = 2; // win game, exit loop
		}
		cout << "********************************" << endl;
	}
	if (flag == 1)
		cout << "You lose!";
	else
	{
		cout << "You win!" << endl; //reveal final game board
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				// Print values of the 
				// memory block 
				if (*(arr + i * c + j) == -1)
					cout << "0 ";
				else
					cout << *(arr + i * c + j) << " ";

			}
			cout << endl;
		}
	}
	return 0;
}

/* void function(arr[], arr2[], int cell)
	{
		if(arr[cell] == 0)
		{
			arr[cell]--;
			arr2[cell] = 0;

			if(in corner)
			{
				funtion (arr, arr2, cell +1)
				function(...)
				function(...)
			{
		}



	}
	*/

void test(int a[], int a2[], int cell) //dubug print
{
	if (a[cell] == 0)					//if cell value is zero, check invis board as checked
	{
		a[cell]--;
		a2[cell] = 0;
		counter--;

		if (cell == 0) // up left corner
		{
			test(a, a2, cell + 1);
			test(a, a2, cell + c);
			test(a, a2, cell + c + 1);
		}
		else if (cell == c - 1) // up right corner
		{
			test(a, a2, cell + 1);
			test(a, a2, cell + c);
			test(a, a2, cell + c - 1);
		}
		else if (cell == c * (r - 1)) // bot left corner
		{
			test(a, a2, cell + 1);
			test(a, a2, cell - c);
			test(a, a2, cell - c + 1);

		}
		else if (cell == c * (r - 1)) // bot right corner
		{
			test(a, a2, cell - 1);
			test(a, a2, cell - c);
			test(a, a2, cell - c - 1);

		}
		else if (cell < c) //top row
		{
			test(a, a2, cell - 1); //left
			test(a, a2, cell + 1); // right
			test(a, a2, cell + c);
			test(a, a2, cell + c + 1);
			test(a, a2, cell + c - 1);
		}
		else if (cell % c == 0) //first column
		{
			test(a, a2, cell + 1); //left
			test(a, a2, cell + c + 1); //up diaig
			test(a, a2, cell - c + 1); // down diag
			test(a, a2, cell + c);
			test(a, a2, cell - c);
		}

		else if ((cell + 1) % c == 0) //last column
		{
			test(a, a2, cell - 1); //left
			test(a, a2, cell + c - 1); //up diaig
			test(a, a2, cell - c - 1); // down diag
			test(a, a2, cell + c);
			test(a, a2, cell - c);
		}
		else if (cell > c * (r - 1))
		{
			test(a, a2, cell - 1);
			test(a, a2, cell + 1);
			test(a, a2, cell + c);
			test(a, a2, cell + c + 1);
			test(a, a2, cell + c - 1);
		}
		else {

			test(a, a2, cell - 1);
			test(a, a2, cell + 1);
			test(a, a2, cell + c);
			test(a, a2, cell - c);
			if(a[cell + c + 1] !=0)			// if statements added to check if a 0 is bleeding through a diagonal
				test(a, a2, cell + c + 1);
			if (a[cell + c - 1] != 0)
				test(a, a2, cell + c - 1);
			if (a[cell - c + 1] != 0)
				test(a, a2, cell - c + 1);
			if (a[cell - c - 1] != 0)
				test(a, a2, cell - c - 1);
			

		}
	}
	else if (a[cell] > 0 && a[cell] < 9)
	{
		a2[cell] = a[cell];
		a[cell] = -1;
		counter--;
	}
}

void update(int a[], int rows, int cols)
{
	for (int i = 0; i < rows; i++) {						//print new board
		for (int j = 0; j < cols; j++)
		{
			if (a[j + (c * i)] == 9)
				if (i == 0 && j == 0) // if in the first row, first column
				{
					if (a[1] != 9)			//update the left
						a[1]++;
					if (a[cols] != 9)	//below
						a[cols]++;
					if (a[cols + 1] != 9)	//diagonal
						a[cols + 1]++;
				}
				else if (i == 0 && j == (cols - 1)) // if in top right
				{
					if (a[cols - 2] != 9)		//update left, backdag, bottom
						a[cols - 2]++;
					if (a[rows + cols - 1] != 9)
						a[rows + cols - 1]++;
					if (a[rows + cols - 2] != 9)
						a[rows + cols - 2]++;

				}
				else if (i == (rows - 1) && j == 0) // if in bottom left
				{
					if (a[j + (cols * i) + 1] != 9)			// above, diagf, left
						a[j + (cols * i) + 1]++;
					if (a[j - cols + cols * i] != 9)
						a[j - cols + cols * i]++;
					if (a[j - cols + cols * i + 1] != 9)
						a[j - cols + cols * i + 1]++;

				}

				else if (i == (rows - 1) && j == (cols - 1))	//if in bottom right 
				{
					if (a[j + (c * i) - 1] != 9)					// above, back diag, left
						a[j + (c * i) - 1]++;
					if (a[j + (c * i) - cols] != 9)
						a[j + (c * i) - cols]++;
					if (a[j + (c * i) - cols - 1] != 9)
						a[j + (c * i) - cols - 1]++;

				}
				else if (i == 0)								// first row
				{
					if (a[j + (c * i) - 1] != 9)
						a[j + (c * i) - 1]++;
					if (a[j + (c * i) + 1] != 9)
						a[j + (c * i) + 1]++;
					if (a[j + (c * i) - 1 + cols] != 9)
						a[j + (c * i) - 1 + cols]++;
					if (a[j + (c * i) + cols] != 9)
						a[j + (c * i) + cols]++;
					if (a[j + (c * i) + 1 + cols] != 9)
						a[j + (c * i) + 1 + cols]++;

				}
				else if (j == 0) // first col
				{
					if (a[j + (c * i) - cols] != 9)
						a[j + (c * i) - cols]++;
					if (a[j + (c * i) - cols + 1] != 9)
						a[j + (c * i) - cols + 1]++;
					if (a[j + (c * i) + 1] != 9)
						a[j + (c * i) + 1]++;
					if (a[j + (c * i) + 1 + cols] != 9)
						a[j + (c * i) + 1 + cols]++;
					if (a[j + (c * i) + cols] != 9)
						a[j + (c * i) + cols]++;

				}
				else if (j == (cols - 1)) //last col
				{
					if (a[j + (c * i) - cols] != 9)
						a[j + (c * i) - cols]++;
					if (a[j + (c * i) - cols - 1] != 9)
						a[j + (c * i) - cols - 1]++;
					if (a[j + (c * i) - 1] != 9)
						a[j + (c * i) - 1]++;
					if (a[j + (c * i) - 1 + cols] != 9)
						a[j + (c * i) - 1 + cols]++;
					if (a[j + (c * i) + cols] != 9)
						a[j + (c * i) + cols]++;
				}
				else if (i == (rows - 1)) // last row
				{
					if (a[j + (c * i) - 1] != 9)
						a[j + (c * i) - 1]++;
					if (a[j + (c * i) + 1] != 9)
						a[j + (c * i) + 1]++;
					if (a[j + (c * i) - 1 - cols] != 9)
						a[j + (c * i) - 1 - cols]++;
					if (a[j + (c * i) - cols] != 9)
						a[j + (c * i) - cols]++;
					if (a[j + (c * i) + 1 - cols] != 9)
						a[j + (c * i) + 1 - cols]++;
				}
				else
				{
					if (a[j + (c * i) - 1] != 9)
						a[j + (c * i) - 1]++;
					if (a[j + (c * i) + 1] != 9)
						a[j + (c * i) + 1]++;
					if (a[j + (c * i) - 1 - cols] != 9)
						a[j + (c * i) - 1 - cols]++;
					if (a[j + (c * i) - cols] != 9)
						a[j + (c * i) - cols]++;
					if (a[j + (c * i) + 1 - cols] != 9)
						a[j + (c * i) + 1 - cols]++;
					if (a[j + (c * i) + 1 + cols] != 9)
						a[j + (c * i) + 1 + cols]++;
					if (a[j + (c * i) + cols] != 9)
						a[j + (c * i) + cols]++;
					if (a[j + (c * i) - 1 + cols] != 9)
						a[j + (c * i) - 1 + cols]++;
				}
		}
	}
}
