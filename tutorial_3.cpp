// Student name: Berk Tinaz
// Student ID  : 40115829

// Submission deadline: Thursday, 14 Feb 2019, 2 pm

/*
	This exercise is a continuation of Tut-02.

	1. We want to improve the compuation efficiency by using binary search to lookup countList
	   (in Tut-02, we use sequential search to lookup countList).
	   To support binary search, the countList needs to be maintained in sorted order by the word field.

	2. After obtaining the frequency counts of words, we want to determine the most
	   popular words (i.e. words with largest count value up to a given rank threshold).
	   The word ranked 1st has the highest count value.
	   In the test data, the word "Java" with count = 30 is ranked 1st.
	   The word "program" with count = 19 is ranked 2nd, and so on.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct freqCount
{
	string word;
	int count;
};

bool hasNext(const char *buffer);
string& nextWord(char*& buffer);
int wordCount(const char text[], int lenThreshold);

// ---------------------------------------------------------- functions to be implemented by you

void updateCount_binSearch(freqCount *countList, int& n, const string& word)
{
	// Records in countList are sorted by the word field in alphabetical order.

	// Lookup countList using binary search.
	// The input word is the search key.

	// Try to optimize the efficiency of your program. 
	// Comparison of 2 strings is not a constant-time operation.
	// Minimize the number of string comparison operations in your design.

	// When the given word is not found in the countList, you can deduce the 
	// 'insertion point' of the search key from the loop control variable. 
	// Insertion point means the location to store the search key if it is added to the array. 

	int left = 0;
	int right = n - 1;
	int middle = 0; //initialize

	while (left <= right) {
		middle = left + (right - left) / 2;

		if (countList[middle].word.compare(word) == 0)
		{
			countList[middle].count += 1;
			return;
		}
		else if (countList[middle].word.compare(word) < 0)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}

	for (int i = n-1; i >= left; i--)
	{
		countList[i + 1] = countList[i];
	}

	countList[left].word = word;
	countList[left].count = 1;
	n += 1;
	return;
}

void updatePopList(freqCount *popList, int& k, int rankThreshold, const freqCount& item)
{
	// The array popList[] has been created by the calling function.

	// popList[] is ordered by the count field in descending order
	// k = number of records in popList[], value of k is updated by this function.

	// Determine if the given item should be included in the popList.
	// If yes, some of the current items may be removed.
	// Only the records within the given rankThreshold are kept in the popList.

	int left = 0;
	int right = k - 1;
	int middle = 0; //initialize

	while (left <= right) {
		middle = left + (right - left) / 2; //mid point

		if (popList[middle].count == item.count)
		{	
			while (popList[middle].count == item.count)
			{
				middle += 1;
			}
			for (int i = k - 1; i >= middle; i--)
			{
				popList[i + 1] = popList[i];
			}
			popList[middle] = item;

			if (k < rankThreshold )
			{
				k++;
			}
			else //if there are larger than rankThreshold items, set k to threshold level and keep increasing until the element at threshold'th index repeats itself.
			{
				k = rankThreshold;
				while (popList[rankThreshold - 1].count == popList[k - 1].count)
				{
					k++;
				}
				k--;
			}
			return;
		}
		else if (popList[middle].count > item.count)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}
	for (int i = k - 1; i >= left; i--)
	{
		popList[i + 1] = popList[i];
	}
	popList[left] = item;

	if (k < rankThreshold)
	{
		k++;
	}
	else
	{
		k = rankThreshold;
		while (popList[rankThreshold - 1].count == popList[k - 1].count && k < 5 * rankThreshold)
		{
			k++;
		}
		k--;
	}
	return;
}

// ----------------------------------------------------------------- functions given to you

void getMostPopular(const freqCount *countList, int n, freqCount *popList, int& k, int rankThreshold)
{
	// We want to determine the words that are ranked 1 to rankThreshold by frequency count.
	// In this exercise, we don't want to sort the countList by the count field.

	// Suppose rankThreshold = 8, we want to find out the top 8 words with largest count value.

	// Words with count value equals to the count value of the 8-th ranked word are also included in the popList.
	// For example, in the test data the word ranked 8th has count = 7.
	// There are 2 more words with the same count value, hence, there are a total of 10 words in the result.

	// n = number of records in countList[]

	// popList[] has been created by the main function
	// k = number of records in popList[], value of k is updated by this function.

	k = 0;  // initialize popList[] to empty

	for (int i = 0; i < n; i++)  // for each item in countList
		updatePopList(popList, k, rankThreshold, countList[i]);
}

void wordFreqCount(char *text, freqCount*& countList, int& n, int lenThreshold)
{
	int numWord = wordCount(text, lenThreshold);
	countList = new freqCount[numWord];
	n = 0;  // no. of records in countList

	char *buffer = text;
	while (hasNext(buffer))
	{
		string& word = nextWord(buffer);
		if (word.length() >= lenThreshold)
			updateCount_binSearch(countList, n, word);
		
		delete &word;
	}
}

int wordCount(const char text[], int lenThreshold)
{
	// Return the number of words (with length >= lenThreshold) in the array text[].

	int len = 0;  
	int count = 0;
	bool done = false;

	for (int i = 0; !done; i++)
	{
		if (isspace(text[i]) || text[i] == '\0')  // end of a word
		{
			if (len >= lenThreshold)
				count++;
			len = 0;
			if (text[i] == '\0')
				done = true;
		}
		else
			len++;	
	} 
	return count;
}

bool hasNext(const char *buffer)
{
	for (int i = 0; buffer[i] != '\0'; i++)
		if (!isspace(buffer[i])) 
			return true;
	return false;
}

string& nextWord(char*& buffer)
{
	// Extract a word from the buffer. 
	// The pointer is advanced to the white-space char or '\0' that follows the extracted word.
	// A new string object for the extracted word is created, and it is returned by reference.

	// Brackets and punctuation marks that surround the word are excluded.
	// For example, if buffer[] = "(object-oriented language)",
	// calling nextWord(buffer) returns the string "object-oriented".

	int i = 0;
	while (isspace(buffer[i]))  // skip the leading white-space char
		i++;

	int start = i;
	int len = 0;
	while (!(isspace(buffer[i]) || buffer[i] == '\0'))
	{
		len++;
		i++;
	}
	while (len > 1 && (buffer[start] == '(' || buffer[start] == '"' || buffer[start] == '\''))
	{
		start++;
		len--;
	}

	int j = start + len - 1;
	while (j > start)
	{
		char c = buffer[j];
		if (c == '.' || c == ',' || c == '?' || c == '!' || c == ';' || c == '"' || c == '\'' || c == ')')	
			len--;
		else
			break;

		j--;
	}
	string *word = new string(buffer+start, len);
	buffer += i;
	return *word;
}


char* readData(string filename)
{
	// Read in the data from the file to a char array buffer[].

	ifstream infile(filename);
	if (!infile.is_open())
	{
		cout << "Error: cannot open data file" << endl;
		system("pause");
		exit(0);
	}

	infile.seekg(0, infile.end);  // move the file cursor to end of file
	int size = infile.tellg();       // get position of cursor

	cout << "file size = " << size << " bytes\n";
	char *buffer = new char[size+1]; // create a buffer of the required size
	
	infile.seekg(0, infile.beg);  // mvoe the file cursor to beginning of file

	// In Windows, \r\n are replaced by \n when the data are read into the buffer.
	// Hence, the actual length of the array may be shorter than the size of file.

	// In some other system, the \r is retained in the buffer.

	int i = 0;
	while (!infile.eof())  // not end of file
		buffer[i++] = infile.get();	

	buffer[--i] = '\0';  // replace eof delimiter (value -1) by end of string delimiter '\0'

	cout << "len of buffer = " << i << endl;
	infile.close();
	return buffer;
}


int main()
{	
	string filename = "testData.txt";
	char *text = readData(filename);

	freqCount *countList = nullptr;
	int n = 0;
	int lenThreshold = 4;
	wordFreqCount(text, countList, n, lenThreshold);

	int countThreshold = 5;
	cout << "\nWords that appear " << countThreshold << " or more times:\n\n";
	for (int i = 0; i < n; i++)
		if (countList[i].count >= countThreshold)
			cout << countList[i].word << " : " << countList[i].count << " times\n";
	cout << endl;

	// countList[] is ordered by word field in alphabetical order.

	int rankThreshold = 8;
	freqCount *popList = new freqCount[5 * rankThreshold];  // list of most popular words
	int k = 0;  // number of records in popList[]
	
	getMostPopular(countList, n, popList, k, rankThreshold);

	cout << "Top " << rankThreshold << " words with highest frequency count:\n\n";
	for (int i = 0; i < k; i++)
		cout << popList[i].word << " : " << popList[i].count << " times\n";
	cout << endl;
	// Words are printed in decending order of count value.
	// Words with same count value are printed in alphabetical order.

	delete[] countList;  // Free the memory space occupied by arrays created by dynamic memory allocation
	delete[] text;
	delete[] popList;

	system("pause");
	return 0;
}