/*			Mydriver.cpp
	Ben Zech ( bz19 )		9/16/2020 at 11:59pm
	Bob Myers			Assignment 1

*/
#include <iostream>
#include <string>

#include "tlist.h"

using namespace std;

template <typename T> 
void PrintList(const TList<T>& L, string label)
{
	cout << label << " size is: " << L.GetSize() << "\n"
	     << label << " = "; 
	L.Print(cout);
	cout << "\n\n";
}

int main()
{
	
	cout << "Creating a new linked list of ints using default constructor" << endl;
	TList<int> L1;
	PrintList(L1, "L1");

	cout << "Populating L1 with integer 5 using InsertBack" << endl;
	L1.InsertBack(5);
	PrintList(L1, "L1");

	cout << "Populating L1 with integer -2 using InsertFront" << endl;
	L1.InsertFront(-2);
	PrintList(L1, "L1");

	cout << "Removing from L1 using RemoveBack" << endl;
	L1.RemoveBack();
	PrintList(L1, "L1");

	cout << "Populating L1 with integer 20 using InsertBack" << endl;
	L1.InsertBack(20);
	PrintList(L1, "L1");

	cout << "Removing from L1 using RemoveFront" << endl;
	L1.RemoveFront();
	PrintList(L1, "L1");

	cout << "Running Clear() on L1" << endl;
	L1.Clear();
	PrintList(L1, "L1");

	cout << "Creating a new linked list of ints using TList(T val, int num) constructor" << endl;
	TList<int> L2(7,5);
	PrintList(L2, "L2");
	
	cout << "Creating a new linked list of ints using same constructor as before" << endl;
	TList<int> L3(-4,6);
	PrintList(L3, "L3");

	cout << "L1 will now equal L2 + L3" << endl;
	L1 = L2 + L3;
	PrintList(L2, "L2");
	PrintList(L3, "L3");
	PrintList(L1, "L1");

	cout << "Lets call print but it has a 'x' seperating each data" << endl;
	L1.Print(cout, 'x');
	cout << "\n\n";

	cout << "Lets call the copy constructor by making a new list, L4, equal to L1" << endl;
	cout << "	(L4 should now equal L1)" << endl;
	TList< int > L4 = L1;		// calls copy constructor
	PrintList(L4, "L4");

	cout << "Lets call the copy assignment by saying L4 = L2" << endl;
	cout << "	(L4 should now equal L2)" << endl;
	L4 = L2;			// calls copy assignment
	PrintList(L2, "L2");
	PrintList(L4, "L4");

	cout << "Lets add one more integer to L4 using InsertFront" << endl;
	L4.InsertFront(1000);
	PrintList(L4, "L4");


	cout << "Let's test the accessors!" << endl;
	PrintList(L4, "L4");
	if ( L4.IsEmpty() )
		cout << "According to IsEmpty(), L4 is empty" << endl;
	else
		cout << "According to IsEmpty(), L4 is not empty" << endl;
	cout << "According to GetSize(), L4 has a size of " << L4.GetSize() << endl;
	cout << "According to GetFirst(), L4's first is " << L4.GetFirst() << endl;
	cout << "According to GetLast(), L4's last is " << L4.GetLast() << endl;
	cout << endl;

	cout << "Now lets run the same accessor functions, but after we do L4.Clear()" << endl;
	L4.Clear();
	PrintList(L4, "L4");
	if ( L4.IsEmpty() )
		cout << "According to IsEmpty(), L4 is empty" << endl;
	else
		cout << "According to IsEmpty(), L4 is not empty" << endl;
	cout << "According to GetSize(), L4 has a size of " << L4.GetSize() << endl;
	cout << "According to GetFirst(), L4's first is " << L4.GetFirst() << endl;
	cout << "According to GetLast(), L4's last is " << L4.GetLast() << endl;
	
	cout << "\nCalling move constructor with new list L5 onto L2" << endl;
	PrintList(L2, "L2");
	TList< int > L5 = move(L2);	// calls move constructor
	PrintList(L5, "L5");
	
	cout << "Calling move assignment with already existing L5 onto L3" << endl;
	PrintList(L3, "L3");
	L5 = move(L3);			// calls move assignment
	PrintList(L5, "L5");
	
	cout << "Time to play around with L5 by calling various Endpoint insert/remove functions (non iterator)" << endl;
	L5.InsertFront(22);
	PrintList(L5, "L5");
	L5.RemoveBack();
	PrintList(L5, "L5");
	L5.RemoveBack();
	PrintList(L5, "L5");
	L5.InsertBack(400);
	PrintList(L5, "L5");
	L5.RemoveFront();
	PrintList(L5, "L5");
	L5.InsertBack(0);
	PrintList(L5, "L5");
	L5.RemoveFront();
	PrintList(L5, "L5");
	L5.InsertFront(99999);
	PrintList(L5, "L5");
	L5.RemoveBack();
	PrintList(L5, "L5");
	L5.InsertFront(1000);
	PrintList(L5, "L5");
	L5.InsertBack(8);
	PrintList(L5, "L5");
	L5.RemoveFront();
	PrintList(L5, "L5");
	L5.RemoveFront();
	PrintList(L5, "L5");
	L5.RemoveBack();
	PrintList(L5, "L5");
	L5.RemoveFront();
	PrintList(L5, "L5");

	cout << "Lets attempt to call remove front / back from an empty list" << endl;
	L1.Clear();
	L1.RemoveFront();
	L1.RemoveBack();
	PrintList(L1, "L1");

	cout << "Now let's do some iterator based inserts and removes" << endl;
	PrintList(L5, "L5");

	TListIterator<int> itr = L5.GetIterator();
	L5.Insert(itr, 123);				//insert
	PrintList(L5, "L5");

	itr.Next();
	itr.Next();
	L5.Insert(itr, 43110);				//insert
	PrintList(L5, "L5");

	itr.Previous();
	itr = L5.Remove(itr);				//remove
	PrintList(L5, "L5");

	itr = L5.Remove(itr);				//remove
	PrintList(L5, "L5");

	itr.Previous();
	L5.Insert(itr, 333);				//insert
	PrintList(L5, "L5");
	
	itr.Previous();
	itr.Next();
	itr = L5.Remove(itr);				//remove
	PrintList(L5, "L5");

	itr.Next();
	L5.Insert(itr, 2000);				//insert
	PrintList(L5, "L5");
	
	itr.Previous();
	itr.Previous();
	itr = L5.Remove(itr);				//remove
	PrintList(L5, "L5");
	
	L5.Insert(itr, 555);				//insert
	PrintList(L5, "L5");
	
	itr.Next();
	itr.Next();
	itr = L5.Remove(itr);				//remove
	PrintList(L5, "L5");

	itr.Next();
	L5.Insert(itr, 28395);				//insert
	PrintList(L5, "L5");

	
	cout << "Lets do some iterator functions" << endl;
	cout << "The iterator is currently pointing at " << itr.GetData() << endl;
	if ( itr.HasNext() )
		cout << "The iterator has a next" << endl;
	else
		cout << "The iterator does not have a next" << endl;
	
	if ( itr.HasPrevious() )
		cout << "The iterator has a previous" << endl;
	else
		cout << "The iterator does not have a previous" << endl;
	

	cout << "Lets create a new list, and traverse it front to back using an iterator" << endl;

	TList< int > L8;
	for (int i = 0; i < 10; i++)
		L8.InsertBack(i*3);
	
	PrintList (L8, "L8");
	TListIterator<int> FTBitr = L8.GetIterator();
	int x = 1;

	cout << "Data at spot " << x << " = " << FTBitr.GetData() << endl;
	while ( FTBitr.HasNext() )
	{
		x++;
		FTBitr.Next();
		cout << "Data at spot " << x << " = " << FTBitr.GetData() << endl;		
	}

	cout << "\n\n\n";
	cout << "Now lets do some brief testing with a list of char" << endl;

	TList<char> C1;
	PrintList(C1, "C1");

	cout << "Calling constructor with 2 parameters" << endl;
	TList<char> C2('d',10);
	PrintList(C2, "C2");
	

	cout << "Using copy assignment, lets make C1 = C2" << endl;
	C1 = C2;
	PrintList(C1, "C1");

	cout << "Lets use a mix of Insertfront, insertback, and iterator insert to populate a new list" << endl;
	TList<char> C3;
	
	C3.InsertFront('g');
	PrintList(C3, "C3");

	C3.InsertBack('o');
	PrintList(C3, "C3");

	C3.InsertFront('a');
	PrintList(C3, "C3");

	cout << "Getting an iterator to help us do insert" << endl;
	TListIterator<char> Citr = C3.GetIteratorEnd();
	C3.Insert(Citr, 'b');
	PrintList(C3, "C3");
	
	Citr.Previous();
	Citr.Previous();
	C3.Insert(Citr, 'a');
	PrintList(C3, "C3");

	C3.InsertBack('p');
	PrintList(C3, "C3");

	Citr.Next();
	Citr.Next();
	Citr.Next();
	C3.Insert(Citr, 'w');
	PrintList(C3, "C3");

	C3.InsertBack('z');
	PrintList(C3, "C3");

	C3.InsertFront('m');
	PrintList(C3, "C3");

	C3.InsertBack('k');
	PrintList(C3, "C3");
	
	Citr.Previous();
	C3.Insert(Citr, 'e');
	PrintList(C3, "C3");

	C3.InsertFront('L');
	PrintList(C3, "C3");

	Citr.Next();
	Citr.Previous();
	Citr.Next();
	Citr.Next();
	C3.Insert(Citr, 'P');
	PrintList(C3, "C3");

	C3.InsertBack('r');
	PrintList(C3, "C3");

	C3.InsertFront('T');
	PrintList(C3, "C3");
	

	cout << "Lets call a mix of removes, remove front, and remove back, along with a few inserts" << endl;
	TListIterator<char> Ditr = C3.GetIterator();
	Ditr = C3.Remove(Ditr);
	PrintList(C3, "C3");

	C3.RemoveBack();
	PrintList(C3, "C3");

	Ditr.Next();
	Ditr.Next();
	Ditr = C3.Remove(Ditr);
	PrintList(C3, "C3");	
	
	C3.RemoveFront();
	PrintList(C3, "C3");

	C3.Insert(Ditr, 'F');
	PrintList(C3, "C3");

	C3.InsertFront('G');
	PrintList(C3, "C3");
	
	C3.RemoveFront();
	PrintList(C3, "C3");
	
	Ditr.Previous();
	Ditr = C3.Remove(Ditr);
	PrintList(C3, "C3");	
		
	C3.RemoveBack();
	PrintList(C3, "C3");

	C3.RemoveBack();
	PrintList(C3, "C3");

	Ditr.Next();
	Ditr.Next();
	Ditr = C3.Remove(Ditr);
	PrintList(C3, "C3");

	C3.RemoveFront();
	PrintList(C3, "C3");

	C3.RemoveFront();
	PrintList(C3, "C3");

	C3.InsertFront('H');
	PrintList(C3, "C3");
	
	Ditr.Previous();
	Ditr.Previous();
	Ditr.Previous();
	Ditr = C3.Remove(Ditr);
	PrintList(C3, "C3");	
	
	C3.RemoveBack();
	PrintList(C3, "C3");
	
	C3.RemoveFront();
	PrintList(C3, "C3");

	C3.RemoveBack();
	PrintList(C3, "C3");

	cout << "Lets try out the accessors on the char list" << endl;
	PrintList(C3, "C3");
	if ( C3.IsEmpty() )
		cout << "According to IsEmpty(), C3 is empty" << endl;
	else
		cout << "According to IsEmpty(), C3 is not empty" << endl;
	cout << "According to GetSize(), C3 has a size of " << C3.GetSize() << endl;
	cout << "According to GetFirst(), C3's first is " << C3.GetFirst() << endl;
	cout << "According to GetLast(), C3's last is " << C3.GetLast() << endl;
	cout << endl;
	

	cout << "Lets do +operator with char lists" << endl;
	PrintList(C1, "C1");
	PrintList(C3, "C3");
	C2 = C1 + C3;
	PrintList(C2, "C2");


	cout << "Lets traverse C2 back to front using an iterator" << endl;	
	PrintList (C2, "C2");
	TListIterator<char> BTFitr = C2.GetIteratorEnd();
	
	cout << "Data going backwards: " << BTFitr.GetData() << endl;
	while ( BTFitr.HasPrevious() )
	{
		BTFitr.Previous();
		cout << "Data going backwards: " << BTFitr.GetData() << endl;
	}

	
	
	

}
