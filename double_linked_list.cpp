#include <iostream>
#include <exception>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;

template<typename T>
class DoubleLinkedList
{
	class Node
	{
	public:
		Node* prev, * next;
		T data;
		Node(T item) : data(item) {}
	};
	Node* head, * tail;
	unsigned int size;
	Node* getNode(unsigned int index);
public:
	DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}
	~DoubleLinkedList();
	void add(T item);
	void insert(T item, unsigned int index);
	T pop(unsigned int index);
	void print();
	unsigned int getSize() { return size; }
	T& operator[](unsigned int index);
};

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	if (!size) { ; }
	else
	{
		Node* delNode = tail->prev;
		for (int i = 0; i < size - 1; ++i)
		{
			delete delNode->next;
			delNode = delNode->prev;
		}
		delete head;
	}

}

template<typename T>
typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::getNode(unsigned int index)
{
	try {
		Node* startNode;
		if (index >= size || index < 0) { throw out_of_range("Index out of range."); }
		if (index > size / 2)
		{
			startNode = tail;
			for (int i = size - 1; i > index; --i)
			{
				startNode = startNode->prev;
			}
			return startNode;
		}
		else
		{
			startNode = head;
			for (int i = 0; i < index; ++i)
			{
				startNode = startNode->next;
			}
			return startNode;
		}
	}
	catch (exception & e)
	{
		cerr << endl << e.what() << endl;
	}
}

template<typename T>
void DoubleLinkedList<T>::add(T item)
{
	if (!size)
	{
		head = new Node(item);
		tail = head;
	}
	else
	{
		tail->next = new Node(item);
		tail->next->prev = tail;
		tail = tail->next;
	}
	++size;
}

template<typename T>
void DoubleLinkedList<T>::insert(T item, unsigned int index)
{
	if (index == size) { add(item); }
	else if (index == 0)
	{
		head->prev = new Node(item);
		head->prev->next = head;
		head = head->prev;
	}
	else
	{
		Node* insNode = getNode(index);
		insNode->prev->next = new Node(item);
		insNode->prev->next->prev = insNode->prev;
		insNode->prev->next->next = insNode;
		insNode->prev = insNode->prev->next;
	}
	++size;
}

template<typename T>
T DoubleLinkedList<T>::pop(unsigned int index)
{
	Node* popNode = getNode(index);
	T retData = popNode->data;
	if (size == 1)
	{
		head = nullptr;
		tail = nullptr;
	}
	else if (popNode == head)
	{
		head->next->prev = nullptr;
		head = head->next;
		if (popNode == tail)
		{
			tail->prev->next = nullptr;
			tail = tail->prev;
		}
	}
	else if (popNode == tail)
	{
		tail->prev->next = nullptr;
		tail = tail->prev;
	}
	else if (popNode != head && popNode != tail)
	{
		popNode->prev->next = popNode->next;
		popNode->next->prev = popNode->prev;
	}
	delete popNode;
	--size;
	return retData;
}

template<typename T>
void DoubleLinkedList<T>::print()
{
	for (unsigned int i = 0; i < size; ++i)
	{
		cout << operator[](i) << ' ';
	}
	cout << endl;
}

template<typename T>
T& DoubleLinkedList<T>::operator[](unsigned int index)
{
	return getNode(index)->data;
}


