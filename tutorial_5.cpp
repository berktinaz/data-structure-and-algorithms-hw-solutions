// Student name: Berk Tinaz	
// Student ID  : 40115829

/*
	Submission deadline: Thursday, 28 Feb 2019, 2 pm.

	This exercise is on sorting.
	We shall compare the performances of bubble sort, insertion sort, and qsort
	for sorting arrays of cstring and C++ string objects.

	A template (generic) function for insertion sort is given to you.
	You need to define your own compare functions in order to use the template insertionSort function.
	We want to sort an array of string (or cstring) by length, 
	and strings of the same length are sorted by alphabetical order.

	In the second part, you need to design a template function for bubble sort.

	In the third part, you need to define the compare functions required by qsort.

	Observe the performances of the 3 algorithms, and the differences in the computation
	time for sorting arrays of cstring and string.
	You need to understand the reasons behind the differences in performances of the 3 algorithms.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
typedef char* charpointer;

// Part-1: Define your compare functions for using the template insertionSort function

template<class Type>
void insertionSort(Type *x, int n, int (*compare)(const Type&, const Type&))
{
	for (int i = 1; i < n; i++)
	{
		Type t = x[i];
		int j;
		for (j = i-1; j >= 0 && compare(x[j], t) > 0; j--)
			x[j+1] = x[j];
		x[j+1] = t;
	}
}

int compareString(const string& a, const string& b)
{
	if (a.length() < b.length())
	{
		return -1;
	}
	else if (a.length() > b.length())
	{
		return 1;
	}
	return a.compare(b);
}

int compareCstring(const charpointer& a, const charpointer& b)
{
	if (strlen(a) < strlen(b))
	{
		return -1;
	}
	else if (strlen(a) > strlen(b))
	{
		return 1;
	}
	return strcmp(a, b);
}

void test_insertionSort(char **a, string *s, int n)
{
	// Sort the list of strings by length, and 
	// strings of the same length are sorted in alphabetical order
	clock_t begin, end;
	double elapsedTime;

	cout << "Insertion sort:\n\n";
	cout << "Sort an array of char*, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array a[] using insertionSort
	insertionSort( a, n, compareCstring);

	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;	

	cout << "Sort an array of string, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array s[] using insertionSort
	insertionSort(s, n, compareString);

	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;		

	cout << "\nFirst 5 and last 5 strings in the sorted list:\n\n";
	for (int i = 0; i < 5; i++)
		cout << a[i] << " : " << s[i] << endl;
	cout << endl;
	for (int i = 5; i > 0; i--)
		cout << a[n-i] << " : " << s[n-i] << endl;
}

//-------------------------------------------------------------------------------------

// Part-2: Define your template function bubbleSort
template<class Type>
void bubbleSort(Type *x, int N, int(*compare)(const Type&, const Type&))
{
	int switched = 1;
	for (int pass = 1; pass < N && switched; pass++)
	{
		switched = 0;
		for (int j = 0; j < N - pass; j++)
			if (compare(x[j],x[j+1]) > 0) // assert: j+1 is a valid index
			{
				Type temp = x[j];
				x[j] = x[j + 1];
				x[j + 1] = temp;
				switched = 1;
			}
	}
}


void test_bubbleSort(char **a, string *s, int n)
{
	// Sort the list of strings by length, and 
	// strings of the same length are sorted in alphabetical order

	clock_t begin, end;
	double elapsedTime;

	cout << "\n------------------------------------------------------\n";
	cout << "Bubble sort:\n\n";
	cout << "Sort an array of char*, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array a[] using bubbleSort
	bubbleSort(a, n, compareCstring);

	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;	

	cout << "Sort an array of string, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array s[] using bubbleSort
	bubbleSort(s, n, compareString);

	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;		

	cout << "\nFirst 5 and last 5 strings in the sorted list:\n\n";
	for (int i = 0; i < 5; i++)
		cout << a[i] << " : " << s[i] << endl;
	cout << endl;
	for (int i = 5; i > 0; i--)
		cout << a[n-i] << " : " << s[n-i] << endl;
}

//-------------------------------------------------------------------------------------

// Part-3: Define your compare functions here for using qsort
int compareCstring2(const void *a, const void *b)
{
	char **c1 = (char **)a;
	char **c2 = (char **)b;

	if (strlen(*c1) < strlen(*c2))
	{
		return -1;
	}
	else if (strlen(*c1) > strlen(*c2))
	{
		return 1;
	}

	return strcmp(*c1, *c2);
}

int compareString2(const void *a, const void *b)
{
	string *c1 = (string*) a;
	string *c2 = (string*) b;

	if (c1->length() < c2->length())
	{
		return -1;
	}
	else if (c1->length() > c2->length())
	{
		return 1;
	}

	return c1->compare(*c2);
}

void test_qsort(char **a, string *s, int n)
{
	// Sort the list of strings by length, and 
	// strings of the same length are sorted in alphabetical order.

	clock_t begin, end;
	double elapsedTime;

	cout << "\n------------------------------------------------------\n";
	cout << "qsort:\n\n";
	cout << "Sort an array of char*, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array a[] using qsort
	qsort(a, n, sizeof(char*), compareCstring2);

	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;	

	cout << "Sort an array of string, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array s[] using qsort
	qsort(s, n, sizeof(string), compareString2);

	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;		

	cout << "\nFirst 5 and last 5 strings in the sorted list:\n\n";
	for (int i = 0; i < 5; i++)
		cout << a[i] << " : " << s[i] << endl;
	cout << endl;
	for (int i = 5; i > 0; i--)
		cout << a[n-i] << " : " << s[n-i] << endl;
	cout << endl;
}

// ---------------------------------------------- other functions given to you

void randomize(char **a, string *s, int n)
{
	for (int i = 0; i < n; i++)
	{
		int j = rand() % n;
		char *t = a[i];
		a[i] = a[j];
		a[j] = t;

		string w = s[i];
		s[i] = s[j];
		s[j] = w;
	}
}

char* gen_cstring(int len)
{
	char *t = new char[len+1];
	for (int i = 0; i < len; i++)
		t[i] = 'a' + rand() % 26;
	t[len] = '\0';
	return t;
}

int main()
{		
	srand((unsigned)time(NULL));  // set the seed of the random number generator
	
	int n = 2000;
	char **a = new char*[n];  
	string *s = new string[n];

	for (int i = 0; i < n; i++)	
	{
		int len = 5 + rand() % 15;
		a[i] = gen_cstring(len);
		s[i] = string(a[i]);
	}
	
	test_insertionSort(a, s, n);	

	randomize(a, s, n);	
	test_bubbleSort(a, s, n);
	
	randomize(a, s, n);
	test_qsort(a, s, n);

	system("pause");
	return 0;
}