// Student name: Berk Tinaz
// Student ID  : 40115829

// Submission deadline: Thursday, 21 March 2019, 2 pm.

// You need to implement 2 functions, qsort_list() and msort_list().

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct dnode  // template struct is not used in this exercise
{
	int info;
	dnode *back, *next;
};

void merge(dnode *A, dnode *B, dnode*& first, dnode*& last);
// The function merge() is used to support the merge sort algorithm.
// It is implemented for you.

// -------------------------------------- Part-1: sort a doubly-linked list with quicksort

void swap(dnode *n1, dnode *n2)
{
	int temp = n1->info;
	n1->info = n2->info;
	n2->info = temp;
}

dnode* partition(dnode *left, dnode *right)
{
	int val = left->info;
	int temp = 0;
	dnode *t1 = left->next;
	bool done = false;
	bool past = false;

	while (!done)
	{
		while ( !past && t1->info <= val) //advance t1 pointer until info is larger than val
		{
			if (t1 == right || t1 == right->next) //check if right pointer is past
			{
				past = true;
			}
			t1 = t1->next;
		}
		while (right->info > val) //advance until info is smaller or equal than val
		{
			if (t1 == right || t1 == right->next) //check if t1 pointer is past
			{
				past = true;
			}
			right = right->back;
		}

		if (t1 != right && t1 != right->next) // if t1 and right didn't pass each other swap
		{
			swap(t1, right);
		}
		else
		{
			done = true;
		}
	}
	swap(left, right); //val is in correct position now
	return right;
}

void qsort_list(dnode *first, dnode *last)
{
	// first points to the first node of the list segment to be sorted.
	// last points to the last node of the list segment to be sorted.

	// Implement this function using the quicksort algorithm.

	// Data object can be copied from one node to another node.
	// The structure (pointer) of the list is not modified.
	if (last != nullptr && first != last && first != last->next)
	{
		dnode *t = partition(first, last);
		qsort_list(first, t->back);
		qsort_list(t->next, last);
	}
	
}


// -------------------------------------- Part-2: sort a single-linked list with merge sort
dnode* getMidNode(dnode *start)
{
	if (start == nullptr)
	{
		return start;
	}
	dnode *n1 = start->next;
	dnode *n2 = start;

	while (n1 != nullptr) //advance n1 2 node, n2 1 node when possible
	{
		n1 = n1->next;
		if (n1 != nullptr)
		{
			n1 = n1->next;
			n2 = n2->next;
		}
	}
	return n2;
}

void msort_list(dnode*& first)
{
	// The back pointer in a node is not used. 
	// The linked list is treated as single-linked list.

	// The function to merge 2 sorted sublists is given to you.
	// The nodes in the linked list are rearranged. 
	// No new node is created in the sorting process.
	// Data object will not be copied from one node to another node.
	if (first == nullptr || first->next == nullptr)
	{
		return;
	}

	dnode *last = first;
	while (last->next != nullptr)
	{
		last = last->next;
	}

	dnode *mid = getMidNode(first);
	dnode *nmid = mid->next;
	mid->next = nullptr;

	msort_list(first);
	msort_list(nmid);

	merge(first, nmid, first, last);
}

// ------------------------------------- functions given to you

void merge(dnode *A, dnode *B, dnode*& first, dnode*& last)
{
	// Preconditions: Lists A and B are not empty.
	//                Lists A and B are sorted in ascending order.

	// Merge lists A and B. Nodes in A and B are put together in the merged list.
	// The merged list is sorted in ascending order.
	// Pointers first and last point to the first and last node of the merged list.

	dnode *p, *q;
	
	if (A->info <= B->info)
	{
		first = last = A;
		p = A->next;
		q = B;
	}
	else
	{
		first = last = B;
		p = A;
		q = B->next;
	}

	while (p != nullptr && q != nullptr)
	{
		dnode *r;
		if (p->info <= q->info)
		{
			r = p;
			p = p->next;
		}
		else
		{
			r = q;
			q = q->next;
		}
		
		// Append node r to the merged list
		last->next = r;		
		last = r;
	}

	if (p != nullptr)
		last->next = p;
	else if (q != nullptr)
		last->next = q;

	while (last->next != nullptr)  // move pointer last to the last node
		last = last->next;
}

void printList(const char *label, const dnode *list)
{
	cout << label << endl;
	int count = 0;
	const dnode *p = list;
	while (p != nullptr)
	{
		if (count > 0 && count % 10 == 0)  // print up to 10 numbers per line
			cout << endl;

		cout << setw(3) << p->info << ", ";
		count++;
		p = p->next;
	}
	cout << endl << endl;
}

void createList(int n, int range, dnode*& first, dnode*& last)
{
	// n = length of the linked list to be created

	if (n <= 0)
	{
		first = last = nullptr;
		return;
	}

	first = last = new dnode;
	first->info = rand() % range;
	first->back = nullptr;

	for (int i = 1; i < n; i++)
	{
		last->next = new dnode;
		last->next->back = last;
		last = last->next;
		last->info = rand() % range;
	}
	last->next = nullptr;
}

void clearList(dnode *list)
{
	dnode *p;
	while (list != nullptr)
	{
		p = list->next;
		delete list;
		list = p;
	}	
}

void test_qsort(int n, int range)
{
	cout << "\n*** Test case with n = " << n << endl;

	dnode *first, *last;
	createList(n, range, first, last);
	printList("list : ", first);

	qsort_list(first, last);

	printList("list (sorted) : ", first);
	clearList(first);
}

void change_to_single_linked(dnode *list)
{
	dnode *p = list;
	while (p != nullptr)
	{
		p->back = nullptr;
		p = p->next;
	}
}

void test_msort(int n, int range)
{
	cout << "\n*** Test case with n = " << n << endl;

	dnode *first, *last;
	createList(n, range, first, last);
	change_to_single_linked(first);

	printList("list : ", first);
	msort_list(first);
	printList("list (sorted) : ", first);
	clearList(first);
}

int main()
{	
	cout << "Sort a doubly-linked list of integers with quicksort" << endl << endl;
	
	srand((unsigned)time(NULL));  
	test_qsort(10, 97);
	test_qsort(50, 193);

	cout << "\nSort a single-linked list of integers with merge sort" << endl << endl;
	test_msort(10, 97);
	test_msort(50, 193);

	system("pause");
	return 0;
}