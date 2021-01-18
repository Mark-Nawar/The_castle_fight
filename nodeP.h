#pragma once

//#ifndef __nodeP_H_
//#define __nodeP_H_

template < typename T>
class nodeP
{
private:
	T item; // A data item( the data element of the queue Enemy for example
	int P; // the periority of an item an integer value for every nodeP 
	nodeP<T>* next; // Pointer to next nodeP
public:
	nodeP();
	nodeP(const T& r_Item,int p);	//passing by const ref.
	nodeP(const T& r_Item,int p, nodeP<T>* nextnodePPtr);
	void setItem(const T& r_Item);
	void setNext(nodeP<T>* nextnodePPtr);
	void setP(int);
	int getP();
	T getItem() const;
	nodeP<T>* getNext() const;
}; // end nodeP


template < typename T>
nodeP<T>::nodeP()
{
	next = nullptr;
}

template < typename T>
nodeP<T>::nodeP(const T& r_Item,int p)
{
	item = r_Item;
	P = p;
	next = nullptr;
}

template < typename T>
nodeP<T>::nodeP(const T& r_Item,int p, nodeP<T>* nextnodePPtr)
{
	item = r_Item;
	P = p;
	next = nextnodePPtr;
}
template < typename T>
void nodeP<T>::setItem(const T& r_Item)
{
	item = r_Item;
}
template< typename T>
void nodeP<T>::setP(int p)
{
	P = p; //set the periorty of the node by this value
}

template<typename T>
int nodeP<T>::getP()
{
	return P;
}

template < typename T>
void nodeP<T>::setNext(nodeP<T>* nextnodePPtr)
{
	next = nextnodePPtr;
}

template < typename T>
T nodeP<T>::getItem() const
{
	return item;
}

template < typename T>
nodeP<T>* nodeP<T>::getNext() const
{
	return next;
}

//#endif