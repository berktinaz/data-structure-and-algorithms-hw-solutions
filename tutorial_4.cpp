// Student name: Berk Tinaz
// Student ID  : 40115829

// Submission deadline: Thursday, 21 Feb, 2 pm

#include <iostream>
#include <iomanip>  //setw()
#include <cstdlib>
#include <ctime>

using namespace std;


struct intSet
{
	// Data structure to represent a set of integers.
	// Numbers in the array are maintained in ascending order.

	int *store;   // array store[] is created using dynamic memory allocation
	int maxSize;  // physical size of the array store[]
	int size;     // number of elements in the set
};

//----------------------------------------------- functions to be implemented by you

void setIntersection(const intSet& setA, const intSet& setB, intSet& setC)
{
	// Compute setC = setA intersect setB
	// Your algorithm should only require linear time.

	// You need to create the array store[] in setC
	if (setA.size < setB.size)
	{
		setC.maxSize = setA.size;
	}
	else
	{
		setC.maxSize = setB.size;
	}
	setC.store = new int[setC.maxSize];
	setC.size = 0;

	int index1 = 0;
	int index2 = 0;

	while (index1 < setA.size)
	{
		while (index2 < setB.size && setB.store[index2] < setA.store[index1] )
		{
			index2 += 1;
		}
		if (setB.store[index2] == setA.store[index1])
		{
			setC.store[setC.size] = setA.store[index1];
			setC.size += 1;
			index1 += 1;
			index2 += 1;
		}
		else
		{
			index1 += 1;
		}
	}
}

bool isSubset(const intSet& setA, const intSet& setB)
{
	// Determine if setA is a subset of setB.
	// Your algorithm should only require linear time.

	// get the intersection of setA and setB. If it has the same length as setA then setA is a subset of setB. setIntersection is in linear time. 
	// Therefore overall isSubset function is also linear.

	intSet temp;
	setIntersection(setA, setB, temp);
	delete[] temp.store;

	if (temp.size == setA.size)
	{
		return true;
	}
	return false;
}

void search2DArray(int **A, int row, int col, int key, int& r, int& c)
{
	/*
	Elements in A[row][col] are logically arranged in row-major order,
	and sorted in ascending order.

	Search for the key in the 2D array A[][] using binary search.
	If the key is found, determine r and c such that A[r][c] == key.
	If the key is not found, set r and c to -1.
	*/

	// logically convert it to 1D array and do a regular binary search. Complexity O(log(row*col)).

	int left = 0;
	int right = row*col - 1;
	int middle = 0; //initialize
	int n1 = 0;
	int n2 = 0;

	while (left <= right) {

		middle = left + (right - left) / 2;

		n1 = middle / col ;
		n2 = middle % col ;

		if (A[n1][n2] == key)
		{
			r = n1;
			c = n2;
			return;
		}
		else if (A[n1][n2] < key)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}
	r = c = -1;
	return;
}


//----------------------------------------------- functions prepared for you
int* gen1DArray(int n)
{
	int *A = new int[n];
	int delta = 3;
	int k = 1 + rand() % delta;
	for (int i = 0; i < n; i++)
	{
		A[i] = k;
		k += 1 + rand() % delta;
	}
	return A;
}

void printIntSet(const intSet& set)
{
   for (int i = 0; i < set.size; i++)
   {
	   if (i > 0 && i % 10 == 0)
		   cout << endl;
	   cout << setw(4) << set.store[i] << ",";
   }
   cout << endl << endl;
}

int** gen2DArray(int row, int col)
{
	// Create the array A[row][col] such that
	// 1. A[i][j] <= A[i][j+1] for 0 <= j < col-1; and
	// 2. A[i][n-1] <= A[i+1][0] for 0 <= i < row-1.

	int **A = new int*[row];
	for (int i = 0; i < row; i++)
		A[i] = new int[col];

	int k = 1 + rand() % 7;
	int delta = col / 2;

	for (int i = 0; i < row; i++)	
		for (int j = 0; j < col; j++)
		{
			A[i][j] = k;
			k += rand() % delta;
		}
	
	return A;
}

void print2DArray(int *A[], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << setw(4) << A[i][j] << ",";
		cout << endl;
	}
	cout << endl;
}


void part_1()
{
	cout << "Part-1: Integer set\n\n";

	intSet setA, setB, setC, setD;

	setA.size = setA.maxSize = 10;
	setA.store = gen1DArray(setA.size);

	setB.size = setB.maxSize = 8;
	setB.store = gen1DArray(setB.size);

	cout << "setA:\n";
	printIntSet(setA);

	cout << "setB:\n";
	printIntSet(setB);

	setIntersection(setA, setB, setC);
	cout << "setC:\n";
	printIntSet(setC);

	setD.size = 0;
	setD.maxSize = 8;
	setD.store = new int[setD.maxSize];

	cout << "setD: empty\n\n";

	cout << "setB is subset of setA : " << isSubset(setB, setA) << endl;
	cout << "setC is subset of setA : " << isSubset(setC, setA) << endl;
	cout << "setC is subset of setB : " << isSubset(setC, setB) << endl;
	cout << "setD is subset of setA : " << isSubset(setD, setA) << endl;
	cout << "setC is subset of setD : " << isSubset(setC, setD) << endl;

	/*
	delete[] setA.store;
	delete[] setB.store;
	delete[] setC.store;
	delete[] setD.store;
	*/
}

void part_2()
{
	cout << "\n-----------------------------------------------\n\n";
	cout << "Part-2: 2D array and binary search\n\n";

	int row, col;
	cout << "Enter number of rows: ";
	cin >> row;

	cout << "Enter number of cols: ";
	cin >> col;

	int **A2 = gen2DArray(row, col);
	cout << "\nA2[][]:\n";
	print2DArray(A2, row, col);

	int value;
	do
	{
		cout << "\nEnter search value (enter -1 to exit): ";
		cin >> value;
		if (value >= 0)
		{
			int r, c;
			search2DArray(A2, row, col, value, r, c);

			if (r >= 0 && c >= 0)
				cout << value << " is found at [" << r << "][" << c << "]\n";
			else
				cout << value << " is not found\n";
		}
	} while (value >= 0);

	for (int i = 0; i < row; i++)
		delete[] A2[i];
	delete[] A2;
}

int main()
{
	srand((unsigned)time(NULL));	

	part_1();
	part_2();

	system("pause");
	return 0;
}