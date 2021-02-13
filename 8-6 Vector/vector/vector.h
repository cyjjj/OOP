#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include "stdafx.h"
#include <iostream>
#include <stdexcept> // std::out_of_range

template <class T>
class Vector {
public:
	Vector();                      // creates an empty vector
	Vector(int size);              // creates a vector for holding 'size' elements
	Vector(const Vector& r);       // the copy ctor
	~Vector();                     // destructs the vector 
	T& operator[](int index);      // accesses the specified element without bounds checking
	T& at(int index);              // accesses the specified element, throws an exception of type 'std::out_of_range' when index <0 or >=m_nSize
	int size() const;		        // return the size of the container
	void push_back(const T& x);    // adds an element to the end 
	void clear();                  // clears the contents
	bool empty() const;            // checks whether the container is empty 
private:
	void inflate();                // expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
	T *m_pElements;                // pointer to the dynamically allocated storage
	int m_nSize;                   // the number of elements in the container
	int m_nCapacity;               // the number of elements that can be held in currently allocated storage
};

template<class T>
inline Vector<T>::Vector()
{
	m_pElements = nullptr;
	m_nSize = 0;
	m_nCapacity = 0;
}

template<class T>
inline Vector<T>::Vector(int size)
{
	m_pElements = new T[size];
	m_nSize = 0;
	m_nCapacity = size;
}

template<class T>
inline Vector<T>::Vector(const Vector & r)
{
	m_nSize = r.m_nSize;
	m_nCapacity = r.m_nCapacity;
	m_pElements = new T[m_nCapacity];
}

template<class T>
inline Vector<T>::~Vector()
{
	if (m_pElements != nullptr)
	{
		delete[] m_pElements;
		m_pElements = nullptr;
	}
	m_nSize = 0;
	m_nCapacity = 0;
}

template<class T>
inline T & Vector<T>::operator[](int index)
{
	// TODO: 在此处插入 return 语句
	return m_pElements[index];
}

template<class T>
inline T & Vector<T>::at(int index)
{
	// TODO: 在此处插入 return 语句
	if (index >= 0 && index < m_nSize)
		return m_pElements[index];
	else throw std::out_of_range("Vector.at():index is out of range!");//throws an exception of type 'std::out_of_range'
}

template<class T>
inline int Vector<T>::size() const
{
	return m_nSize;
}

template<class T>
inline void Vector<T>::push_back(const T & x)
{
	if (m_nSize < m_nCapacity)
	{
		m_pElements[m_nSize++] = x;
	}
	else throw exception("Vector is full!");
}

template<class T>
inline void Vector<T>::clear()
{
	m_nSize = 0;
	m_pElements = NULL;
}

template<class T>
inline bool Vector<T>::empty() const
{
	if (m_nSize == 0)
		return true;
	else return false;
}

template<class T>
inline void Vector<T>::inflate()
{
	m_nCapacity = 2 * m_nSize;
	m_pElements = new T[newSize];
}

#endif // !VECTOR_H

