//--------------tlist.hpp--------------
//Ben Zech		Due: Monday, September 14th 2020
//All work below was written by Benjamin Zech. Do not steal

using namespace std;

//Private data used for Tlist
//
//	Node<T>* first;		pointer to first node in list
//	Node<T>* last;		pointer to last node in list
//	int size;		number of nodes in the list
//	static T dummy		dummy object, for empty list data returns
//				assuming type T has default construction

template < typename T >
TList< T >::TList()
// create empty linked list
{
	first = last = nullptr;
	size = 0;
}

template < typename T >
TList< T >::TList(T val, int num)
// create list with num copies of val
{
	first = last = nullptr;
	size = 0;

	for (int i = 0; i < num; i++)
	{
		InsertFront(val);
	}
}

template < typename T >
TList< T >::~TList()
// destructor
{
	Clear();
	delete first;
	delete last;
}

template < typename T >
TList< T >::TList(const TList< T >& L)
// copy constructor
{
	first = last = nullptr;
	size = 0;

	if ( !L.IsEmpty())
	{
		TListIterator< T > itr = L.GetIterator();
		InsertBack(itr.GetData());

		while( itr.HasNext() )
		{
			itr.Next();
			InsertBack(itr.GetData());
		}
	}
}

template < typename T >
TList<T>& TList< T >::operator=(const TList& L)
// copy assignment operator
{
	Clear();

	copier(L);

	return *this;
}

template < typename T >
TList< T >::TList(TList && L) : size{ L.size }, first{ L.first}, last{ L.last }
// move constructor
{
	L.size = 0;
	L.first = nullptr;
	L.last = nullptr;
}

template < typename T >
TList<T>& TList< T >::operator=(TList && L)
// move assignment operator
{
	std::swap( size, L.size );
	std::swap( first, L.first);
	std::swap( last, L.last);

	L.Clear();
	
	return *this;
}

template < typename T >
bool TList< T >::IsEmpty() const
// checks to see whether list is empty
{
	if (size == 0)
		return true;
	else
		return false;
}

template < typename T >
void TList< T >::Clear()
// clear out list, reset to empty
{
	while ( !IsEmpty())
	{
		RemoveFront();
	}
}

template < typename T >
int TList< T >::GetSize() const
// return the size of the list
{
	return size;
}

template < typename T >
void TList< T >::InsertFront(const T& d)
// insert data d as first element
{
	Node< T >* newNode = new Node< T >(d);
	
	if(IsEmpty())
		first = last = newNode;
	else
	{
		first->prev = newNode;
		newNode->next = first;
		first = newNode;
		newNode->prev = nullptr;
	}

	size++;
}

template < typename T >
void TList< T >::InsertBack(const T& d)
// insert data d as last element
{
	Node< T >* newNode = new Node< T >(d);
	
	if(IsEmpty())
		first = last = newNode;
	else
	{
		last->next = newNode;
		newNode->prev = last;
		last = newNode;
		last->next = nullptr;
	}

	size++;
}

template < typename T >
void TList< T >::RemoveFront()
// remove first element of list
{

	if (IsEmpty())
		return;	

	if (!IsEmpty())
	{
		Node< T >* tempPtr = first;
		
		if (first == last)
			first = last = nullptr;		// this case is for when theres only one node
		else
		{
			first = first->next;
			first->prev = nullptr;
		}
		
		size--;
		delete tempPtr;
	}
}

template < typename T >
void TList< T >::RemoveBack()
// remove last element of list
{
	if (IsEmpty())
		return;
	
	if (!IsEmpty())
	{
		Node< T >* tempPtr = last;

		if (first == last)
			first = last = nullptr;		//only one node = empty list after
		else
		{
			last = last->prev;
			last->next = nullptr;
		}
		
		size--;
		delete tempPtr;
	}
}

template < typename T >
T& TList< T >::GetFirst() const
// return first element of list
{
	if ( !IsEmpty() )
		return first->data;
	else
		return dummy;
}

template < typename T >
T& TList< T >::GetLast() const
// return last element of list
{
	if ( !IsEmpty() )
		return last->data;
	else
		return dummy;
}

template < typename T >
TListIterator<T> TList< T >::GetIterator() const
// return iterator to first item
{
	TListIterator< T > iterator;
	iterator.ptr = first;
	return iterator;
}

template < typename T >
TListIterator<T> TList< T >::GetIteratorEnd() const
// return iterator to last item
{
	TListIterator< T > iterator;
	iterator.ptr = last;
	return iterator;
}

template < typename T >
void TList< T >::Insert(TListIterator<T> pos, const T& d)
// insert data element d just before item at pos position
{

	Node< T >* newNode = new Node< T >(d);

	if ( IsEmpty() )
		InsertFront(d);
	else if ( pos.ptr == nullptr )
		InsertBack(d);
	else if ( pos.ptr == first )
		InsertFront(d);
	else
	{
		newNode->prev = pos.ptr->prev;
		newNode->next = pos.ptr;
		
		pos.ptr->prev->next = newNode;
		pos.ptr->prev = newNode;
		
		size++;
	}
}

template < typename T >
TListIterator<T> TList< T >::Remove(TListIterator<T> pos)
// remove data item at position pos. Return iterator to the item 
// that comes after the one being deleted
{
	if ( IsEmpty() )
		return TListIterator<T>();
	else if ( GetSize() == 1 )
	{
		RemoveFront();		// dont need to do size-- because RemoveFront covers it
		pos.ptr = first;
		return pos;
	}
	else if ( pos.ptr == first )
	{
		RemoveFront();
		pos.ptr = first;
		return pos;
	}
	else if ( pos.ptr == last )
	{
		RemoveBack();
		pos.ptr = last;
		return pos;
	}
	else
	{
		Node< T >* tempPtr = pos.ptr;

		pos.ptr->prev->next = pos.ptr->next;
		pos.ptr->next->prev = pos.ptr->prev;
		pos.Next();			// sets pos to the iterator after the one removed
		delete tempPtr;			// temp is pointing to the node being deleted
	
		size--;
		return pos;
	}
}

template < typename T >
void TList< T >::Print(std::ostream& os, char delim) const
// print list contents in order, separated by given delimiter
{
	if ( IsEmpty() )
		os << "The list is empty" << endl;
	else
	{
		TListIterator< T > itr = GetIterator();
		
		os << itr.GetData();
		
		while ( itr.HasNext() )
		{
			os << delim;
			itr.Next();
			os << itr.GetData();
		}
		
		os << endl;
	}
}

template <typename T>
TList<T> operator+(const TList<T>& t1, const TList<T>& t2)
// stand-alone function for concatenating two TList objects
{
	TList<T> result = t1;		// calls copy constructor, result now holds t1

	if ( !t2.IsEmpty())
	{
		TListIterator< T > itr = t2.GetIterator();
		result.InsertBack(itr.GetData());

		while( itr.HasNext() )
		{
			itr.Next();
			result.InsertBack(itr.GetData());
		}
	}
	
	return result;
}

template < typename T >
void TList< T >::copier(const TList < T >& L)
// helper function for copying
{
	if ( !L.IsEmpty())
	{
		TListIterator< T > itr = L.GetIterator();
		InsertBack(itr.GetData());

		while( itr.HasNext() )
		{
			itr.Next();
			InsertBack(itr.GetData());
		}
	}	
}



// TListIterator functions below
//
//
//
// Private data for TListIterator:
//
//	Node<T>* ptr;		pointer to current list item
//


template <typename T>
TListIterator< T >::TListIterator()
// default constructor
{
	ptr = nullptr;
}

template <typename T>
bool TListIterator< T >::HasNext() const
// next item available?
{
	if(ptr->next != nullptr)
		return true;
	else
		return false;
}

template <typename T>
bool TListIterator< T >::HasPrevious() const
// previous item available?
{
	if (ptr->prev != nullptr)
		return true;
	else
		return false;
}

template <typename T>
TListIterator<T> TListIterator< T >::Next()
// advance to next item
{
	if (HasNext())
	{
		ptr = ptr->next;
		return *this;
	}
}

template <typename T>
TListIterator<T> TListIterator< T >::Previous()
// move to previous item
{
	if (HasPrevious())
	{
		ptr = ptr->prev;
		return *this;
	}
}

template <typename T>
T& TListIterator< T >::GetData() const
// return data element of current node
{
	if (ptr == nullptr)
		return TList<T>::dummy;
	else
		return ptr->data;
}
