#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#include <string>
#include <iostream>
using namespace std;


template <class T>
class PriorityQueue
{
private:
	int  m_size;
	int Sort_method;
	T* m_data;

	//check legal for pop opration
	bool check() const
	{
		if (m_size == 0)
			throw (0);
	}

public:
	//ctor
	PriorityQueue(int sort_method = 1) : m_size(0),Sort_method(sort_method) {}

	//cctor
	PriorityQueue(const PriorityQueue<T>& pq)
	{
		m_size = pq.m_size;
		m_data = new T[m_size];
		for (int i = 0; i < m_size; i++)
			m_data[i] = pq.m_data[i];

	}

	//dtor
	~PriorityQueue()
	{
		if(!empty())
		delete[] m_data;
	}

	void set_sort_method(int n)
	{
		Sort_method = n;
	}

	int get_size()
	{
		return m_size;
	}

	T* get_data()
	{
		return m_data;
	}

	//insert new element to the queue
	void insert_element(T element)
	{
		m_size++;
		T* temp = new T[m_size];
		for (int i = 0; i < m_size - 1; i++)
			temp[i] = m_data[i];
		temp[m_size - 1] = element;

		delete[] m_data;
		m_data = new T[m_size];
		for (int i = 0; i < m_size; i++)
			m_data[i] = temp[i];
		delete[] temp;
	}

	//swap between elements
	void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	//sort the queue after push operation
	void sort_push(int index)
	{
		int cmp_ndx = index - 1;
		if (index > 0 && m_data[index] > m_data[cmp_ndx])
		{
			swap(m_data[index], m_data[cmp_ndx]);
			index -= 1;
			sort_push(index);
		}
	}

	//sort the queue after pop operation
	void sort_pop(int index)
	{
		int cmp_ndx = index + 1;
		if (index < m_size - 1 && m_data[index] < m_data[cmp_ndx])
		{
			swap(m_data[index], m_data[cmp_ndx]);
			index += 1;
			sort_pop(index);
		}
	}

	//pop an element from the queue
	T pop(int i)
	{
		try
		{
			check();
			swap(m_data[i], m_data[m_size - 1]);
			T value = m_data[m_size - 1];
			m_size--;
			if (m_size == 0)
				delete m_data;
			if (Sort_method==1)
			sort_pop(i);
			return value;
		}

		catch (int n)
		{
			cout << " Empty Queue" << endl;
		}
	}

	//push an element to the queue
	void push(T element)
	{
		if (empty())
		{
			m_data = new T[1];
			m_data[0] = element;
			m_size++;
		}
		else
		{
			insert_element(element);
			if (Sort_method == 1)
				sort_push(m_size - 1);
		}
	}

	//return top element
	const T& top()const
	{
		return m_data[0];
	}

	//queue is empty?
	bool empty() const
	{
		if (m_size) return false;
		else return true;
	}

	//return size of the queue
	int size() const
	{
		return m_size;
	}

	//operators:
	friend ostream& operator<<(ostream& os, const PriorityQueue<T>& pq)
	{
		for (int i = 0; i < pq.m_size; i++)
			cout << pq.m_data[i] << " ";
		return os;
	}

	T& operator[](int i)
	{
		if (i < 0 || i >= m_size)throw "illegel index";
		return m_data[i];
	}

	const T& operator[](int i) const
	{
		if (i < 0 || i >= m_size)throw "illegel index";
		return m_data[i];
	}

	PriorityQueue<T>& operator=(const PriorityQueue<T>& other) {
		if (&other == this)
			return *this;
		if (m_size != other.m_size)
		{
			delete[] m_data;
			m_size = other.m_size;

			m_data = new T[m_size];
		}
		for (int i = 0; i < m_size; i++)
			m_data[i] = other.m_data[i];
		return *this;
	}

};


//template function for reversed print
template <class T>
void print_reversed_queue(const PriorityQueue<T>& pq)
{

	PriorityQueue<T> pq_cpy(pq);
	int size = pq_cpy.size();
	T* reversed_arr = new T[size];
	for (int i = 0; i < size; i++)
	{
		reversed_arr[i] = pq_cpy.pop();
	}
	for (int i = size - 1; i >= 0; i--)
		cout << reversed_arr[i] << " ";
	cout << endl;
	delete[] reversed_arr;

}

#endif
