// Student name: Berk Týnaz	
// Student ID  : 40115829

// Submission deadline: Thursday, 31 Jan 2019, 14:00

/*
	In this exercise, we want to analyze a text document to find out the
	frequency counts of words, i.e. how many times a word appear in the document.

	We shall make use of the C++ string class.
	The C++ string class offers more convenience (in particular memory management)
	compared to cstring.

	Size of a string object is 28 bytes, plus an internal char array for storing the characters.

	You can find the details about the string class in the cplusplus website
	http://www.cplusplus.com/reference/string/string/

	Arrays and string objects are created using dynamic memory allocation.
	You should be aware of memory management in your program design.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct freqCount
{
	string word;  // C++ string object
	int count;    // number of times the word is found in the document
};

bool hasNext(const char *buffer);
int wordCount(const char text[], int lenThreshold);


// --------------------------------------------- functions to be implemented by you

string& nextWord(const char*& buffer)
{
	// Precondition: buffer is not empty
	// Keyword const means that the contents of the input array buffer[] cannot be modified.
	// But the value of the pointer variable buffer can be adjusted.

	// Extract the next word from the buffer. 
	// The pointer is advanced to the white-space char or '\0' that follows the extracted word.
	// A new string object for the extracted word is created dynamically.
	// The word is returned by reference to improve computation efficiency.

	// The extracted word will be used in the analysis of frequence count.
	// 1. Bracket, single- and double-quote that appear at the beginning of the word are excluded.
	// 2. Bracket, punctuation marks, and single- and double-quote that appear at the end of the word are excluded.

	// Example 
	//    buffer[] = "(object-oriented language)"
	//    nextWord(buffer) returns the string "object-oriented"

	// Constructor of string from char*
	//    string(const char *s, unsigned len)
	// To extract a word from the char array, you need to provide the starting address
	// of the word and the length. 

	// Example: extract the word that starts at buffer[start] with length len
	//    string *word = new string(buffer+start, len);
	
	// Replace the following dummy statements by your own codes
	unsigned len = 0;
	const char *ptr = NULL;
	const char *ptr2 = NULL;

	while( isspace(*buffer) ) { // skip white spaces in the beginning if any 
		buffer++;
	}

	while ( (buffer[0] == '"') || (buffer[0] == '\'') || (buffer[0] == '(') || (buffer[0] == ')') ) // skip specified chars
	{
		buffer++;
	}

	ptr = buffer; // copy the location of the pointer

	while (!isspace(*ptr) and *ptr != '\0') // advance ptr until next white space or EOS
	{
		ptr++;
		len++;
	}

	ptr2 = ptr; // hold current location

	ptr--; //look at the last char before whitespace

	while ( ispunct(*ptr) ) // if punctuation mark skip
	{
		len--;
		ptr--;
	}

	string *word = new string(buffer, len); 
	buffer = ptr2;

	ptr = NULL; // move ptr's away from buffer address
	ptr2 = NULL;

	delete ptr; // delete ptr's
	delete ptr2;

	return *word;  
}


void wordFreqCount(const char *text, freqCount*& countList, int& n, int lenThreshold)
{
	int numWord = wordCount(text, lenThreshold); // determine the required size of countList
	countList = new freqCount[numWord];
	n = 0;  // no. of records in countList

	// Determine the frequency counts of words (with given lenThreshold) in text[].
	// Results are stored in countList[].
	// Records in countList[] are maintained in chronological order (time of insertion).

	// Case-sensitive string comparison is assumed.
	// Hence, "Object" and "object" are considered to be 2 different words.

	// Use the functions hasNext() and nextWord() in your design.
	// Take note of the efficiency in parameter passing, and memory management requirements.
	// You can define other supporting function, where appropriate.

	string *currentWord = NULL;
	bool exists = false;

	while (hasNext(text))
	{
		currentWord = &nextWord(text);

		if ((*currentWord).length() >= lenThreshold)
		{
			exists = false;

			for (int i = 0; i < n; i++)
			{
				if (countList[i].word == *currentWord)
				{
					countList[i].count++;
					exists = true;
					break;
				}
			}
			if (!exists)
			{
				countList[n].word = *currentWord;
				countList[n].count = 1;
				n++;
			}

		}
	}

	delete currentWord;
}

// --------------------------------------------- functions given to you

bool hasNext(const char *buffer)
{
	// Return true if the buffer contains non-white space char.

	for (int i = 0; buffer[i] != '\0'; i++)
		if (!isspace(buffer[i])) 
			return true;
	return false;
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
	int size = infile.tellg();    // get position of cursor

	cout << "file size = " << size << " bytes\n";
	char *buffer = new char[size+1]; // create a buffer of the required size

	infile.seekg(0, infile.beg);  // move the file cursor to beginning of file
	
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
	cout << "Words that appear " << countThreshold << " or more times:\n\n";

	for (int i = 0; i < n; i++)
		if (countList[i].count >= countThreshold)
			cout << countList[i].word << " : " << countList[i].count << " times\n";		

	cout << endl;

	delete[] countList;  // Free the memory space occupied by countList and text
	delete[] text;
	// This step is optional in this example program, but it may be required in other context.
	// The arrays are destroyed when the propgram exits.

	system("pause");
	return 0;
}