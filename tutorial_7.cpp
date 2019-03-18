// Student name: Berk Tinaz
// Student ID  : 40115829

/*
	Submission deadline: Wed, 13 March 2019, 10 am.

	Part_1: Implement the function retain() to process single-linked list.

	Part_2: Implement the function retain_2() to process doubly-linked list.
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

template<class Type>
struct node
{
	Type info;
	node<Type> *link;
};

template<class Type>
struct dnode
{
	Type info;
	dnode<Type> *back, *next;
};

template<class Type>
void retain(node<Type>*& listA, const node<Type> *listB)
{
	// Precondition: Elements in an input list are distinct, 
	//               and are sorted in ascending order.

	// Retain elements in listA that can be found in listB, 
	// i.e. remove elements in listA that are not in listB.
	node<Type> *p = listA;
	node<Type> *prev = p;
	Type temp = NULL;

	while (p != nullptr)
	{
		temp = p->info;

		while (listB != nullptr && listB->info < temp )
		{
			temp = p->info;
			listB = listB->link;
		}

		if (listB == nullptr)
		{
			if (prev == p) //if index is at the start
			{
				listA = nullptr;
				return;
			}
			prev->link = nullptr;
			return;
		}
		else if (listB->info == temp)
		{
			prev = p;
			p = p->link;
			listB = listB->link;
		}
		else
		{
			if (prev == p) //if at the start
			{
				listA = p->link;
				delete p;
				p = listA;
				prev = p;
			}
			else
			{
				prev->link = p->link;
				delete p;
				p = prev->link;
			}
		}
	}

}

template<class Type>
void retain_2(dnode<Type>*& listA, const dnode<Type> *listB)
{
	// Precondition: Elements in an input list are distinct, 
	//               and are sorted in ascending order.

	// Retain elements in listA that can be found in listB, 
	// i.e. remove elements in listA that are not in listB.

	dnode<Type> *p = listA;
	Type temp = NULL;

	while (p != nullptr)
	{
		temp = p->info;

		while (listB != nullptr && listB->info < temp)
		{
			temp = p->info;
			listB = listB->next;
		}

		if (listB == nullptr)
		{
			if (p->back == nullptr)
			{
				listA = nullptr;
				return;
			}
			p->back->next = nullptr;
			return;
		}
		else if (listB->info == temp)
		{
			p = p->next;
			listB = listB->next;
		}
		else
		{
			if (p->back == nullptr)
			{
				listA = p->next;
				p = p->next;
				p->back->next = nullptr;
				p->back = nullptr;
				continue;
			}
			p->back->next = p->next;

			if (p->next != nullptr)
			{
				p->next->back = p->back;
			}
			p = p->next;
		}
	}

}

// ------------------------------------ functions given to you

template<class Type>
void printList(const char *label, const node<Type> *list)
{
	cout << label << " { ";
	const node<Type> *p = list;
	while (p != nullptr)
	{
		cout << p->info;
		if (p->link != nullptr)
			cout << ", ";
		 
		p = p->link;
	}
	cout << " }" << endl;
}

node<int>* createList(const int a[], int n)
{
	if (n == 0)
		return nullptr;

	node<int> *p, *r;
	p = r = new node<int>;
	p->info = a[0];
	for (int i = 1; i < n; i++)
	{
		r->link = new node<int>;
		r = r->link;
		r->info = a[i];
	}
	r->link = nullptr;
	return p;
}

template<class Type>
void printList_2(const char *label, const dnode<Type> *list)
{
	cout << label << " { ";
	const dnode<Type> *p = list;
	while (p != nullptr)
	{
		cout << p->info;
		if (p->next != nullptr)
			cout << ", ";
		 
		p = p->next;
	}
	cout << " }" << endl;
}

template<class Type>
void printList_2_reverse(const char *label, const dnode<Type> *list)
{
	cout << label << " { ";
	const dnode<Type> *p = list;
	if (p != nullptr)
	{
		while (p->next != nullptr)
			p = p->next;
	}

	while (p != nullptr)
	{
		cout << p->info;
		if (p->back != nullptr)
			cout << ", ";
		 
		p = p->back;
	}
	cout << " }" << endl;
}

dnode<int>* createList_2(const int a[], int n)
{
	if (n == 0)
		return nullptr;

	dnode<int> *p, *r;
	p = r = new dnode<int>;
	p->info = a[0];
	p->back = nullptr;

	for (int i = 1; i < n; i++)
	{
		r->next = new dnode<int>;
		r->next->back = r;
		r = r->next;
		r->info = a[i];
	}
	r->next = nullptr;
	return p;
}

void part_1()  // single-linked list
{
	cout << "Part-1: Single-linked list" << endl << endl;

	int a1[] = {3, 4, 6, 8, 10, 11, 12, 13, 15};  
	int n1 = 9;

	int b1[] = {2, 5, 6, 8, 9, 10, 12};  
	int m1 = 7;

	node<int> *listA1 = createList(a1, n1);
	node<int> *listB1 = createList(b1, m1);

	printList("listA1 : ", listA1);
	printList("listB1 : ", listB1);

	retain(listA1, listB1);
	cout << "\nAfter calling retain(listA1, listB1)\n";
	printList("listA1 : ", listA1);
	cout << endl;

	int c1[] = {1, 9};
	int k1 = 2;

	node<int> *listC1 = createList(c1, k1);
	printList("listC1 : ", listC1);

	cout << "\nAfter calling retain(listA1, listC1)\n";
	retain(listA1, listC1);
	printList("listA1 : ", listA1);
}

void part_2()  // doubly-linked list
{
	cout << "\n--------------------------------------------\n";
	cout << "Part-2: Doubly-linked list" << endl << endl;

	int a1[] = {3, 4, 6, 8, 10, 11, 12, 13, 15};
	int n1 = 9;

	int b1[] = {2, 5, 6, 8, 9, 10, 12};
	int m1 = 7;


	dnode<int> *listA2 = createList_2(a1, n1);
	dnode<int> *listB2 = createList_2(b1, m1);

	printList_2("listA2 : ", listA2);
	printList_2("listB2 : ", listB2);

	retain_2(listA2, listB2);
	cout << "\nAfter calling retain_2(listA2, listB2)\n";
	printList_2("listA2 : ", listA2);
	printList_2_reverse("listA2 (reverse) : ", listA2);
	cout << endl;

	dnode<int> *listC2 = nullptr;
	printList_2("listC2 : ", listC2);

	cout << "\nAfter calling retain_2(listA2, listC2)\n";
	retain_2(listA2, listC2);
	printList_2("listA2 : ", listA2);
	cout << endl;
}

int main()
{	
	part_1();
	part_2();

	system("pause");
	return 0;
}