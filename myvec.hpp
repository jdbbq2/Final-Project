///////////////////////////////////////////////////////////////////////////////
// Programmer: JOSHUA BREWER         date: 4-3-2015                          //
// File: myVec.hpp               section: c                                  //
// Purpose: Contains the function definitions for myVec.h                    //
///////////////////////////////////////////////////////////////////////////////

# include <iostream>

using namespace std;


/*-----------Initialization Constructor------------*/

template <typename T>
myVec<T>::myVec(const int size)
{
  m_data = new T[size];
  m_size = size;
}

/*----------Copy Constructor-------------------*/

template <typename T>
myVec<T>::myVec (const myVec<T>& cpy)
{
  m_size = cpy.m_size;
  m_data = new T[m_size];

  for (int i=0; i < m_size; i++)
    m_data[i] = cpy.m_data[i];
}

/*-----------Destructor------------*/

template <typename T>
myVec<T>::~myVec()
{
  delete [] m_data; 
}

// ---------------  Friend Function to Print
// Purpose: prints an myVec
template <typename T>                 
std::ostream& operator<< (std::ostream& out, const myVec<T>& vec)
{
  if (vec.m_size != 0)
  {
    out << "[ ";
    for (int i=0; i < vec.m_size; i++)
    {
      if (i != vec.m_size-1) // at end of vector
      {
        out << vec.m_data[i] << ", ";
      }else
      {
        out << vec.m_data[i] << "]";
      }
    } 
  }else
  {
    cout << "[]";
  }
  return out;
}

// ---------------  Friend Function to get input
// Purpose: read in a line of data
template <typename T>                 
std::istream& operator>> (std::istream& in, myVec<T>& vec)
{
  for (int i = 0; i < vec.m_size; i++)
  {
    in >> vec.m_data[i];
  }
  return in;
}

// Read/Write accessor
template <typename T>  
T& myVec<T>:: operator[] (int i)
{
  if (i > -1 && i < m_size)
  {
    return m_data[i];
  }else
  {
    throw out_of_range("Out of bounds!");
  }
}

// Read-only accessor
template <typename T>  
const T& myVec<T>:: operator[] (const int i) const
{
  if (i > -1 && i <= m_size)
  {
    return m_data[i];
  }else
  {
    throw out_of_range("Out of bounds!");
  }
}

// assignment operator
template <typename T>  
myVec<T>& myVec<T>::operator=(const myVec<T>& source)
{
// alias test
  if (this != &source)
  {
    m_size = source.m_size;
    delete[] m_data;

    m_data = new T[m_size];
    
    for (int k=0; k < m_size; k++)
    {
      m_data[k] = source.m_data[k];
    }
  }
  return *this;
}


template <typename T>
void myVec<T>::setsize(const int size)
{
  int to_read = m_size;
  if (size == 0) // reset to zero
  {
    delete [] m_data;
    m_size = 0;
    m_data = NULL;
  }else if (size == m_size) // do nothing
  {
    return;
  }else
  {
    if (size < m_size) //only read necessary data
      to_read = size;

    T* tmp = new T[size];

    for (int i=0; i < to_read; i++) // read into temp
    {
      tmp[i]=m_data[i];
    }

    delete [] m_data;
    m_data = new T[size]; // resize

    for (int i=0; i < to_read; i++) // read from temp
    {
      m_data[i] = tmp[i];
    }

    m_size = size;
    delete [] tmp; // free memory
  }
}

//+= for T must be defined
template <typename T>
myVec<T> myVec<T>::operator +(const myVec<T>& rhs) const
{
  myVec<T> tmp(rhs);
  if (rhs.getsize() != m_size)
  {
    throw invalid_argument("Invalid addition of two different sized vectors.");
  }
  for (int i=0; i < m_size; i++)
  {
    tmp.m_data[i] += m_data[i];
  }
  return tmp;
}

//+= for T must be defined
template <typename T>
myVec<T> myVec<T>::operator -(const myVec<T>& rhs) const
{
  myVec<T> tmp(rhs);
  if (rhs.getsize() != m_size)
  {
    throw invalid_argument("Invalid subtraction of two different sized vectors.");
  }
  for (int i=0; i < m_size; i++)
  {
    tmp.m_data[i] = m_data[i] - rhs.m_data[i];
  }
  return tmp;
}

template <typename T>
myVec<T> myVec<T>::operator -() const
{
  myVec<T> tmp(*this);
  for (int i=0; i < m_size; i++)
  {
    tmp.m_data[i] = -tmp.m_data[i];
  }
  return tmp;
}

//only makes sense if T is numberic (could change this)
template <typename T>
T myVec<T>::operator *(const myVec<T>& rhs) const
{
  T tmp = 0;
  if (rhs.getsize() != m_size)
  {
    throw invalid_argument("Invalid dot product of two different sized vectors.");
  }
  for (int i=0; i < m_size; i++)
  {
    tmp += rhs.m_data[i]*m_data[i];
  }
  return tmp;
}

template <typename T>
myVec<T> myVec<T>::operator /(const myVec<T>& rhs) const
{
  myVec<T> tmp(rhs);
  if (rhs.getsize() != m_size)
  {
    throw invalid_argument("Invalid division of two different sized vectors.");
  }
  for (int i=0; i < m_size; i++)
  {
    tmp.m_data[i] = m_data[i]/rhs.m_data[i];
  }
  return tmp;
}

template <typename T>
myVec<T> myVec<T>::operator /(const T& rhs) const
{
  myVec<T> tmp(*this);
  for (int i=0; i < m_size; i++)
  {
    tmp.m_data[i] = tmp.m_data[i]/rhs;
  }

  return tmp;
}

template <typename T>
myVec<T> myVec<T>::operator *(const T& rhs) const
{
  myVec<T> tmp(*this);
  for (int i=0; i < m_size; i++)
  {
    tmp.m_data[i] = tmp.m_data[i]*rhs;
  }
  return tmp;
}

template <typename T>
bool myVec<T>::operator ==(const myVec<T>& rhs) const
{
  bool is_equal = true;
  if (rhs.getsize() != m_size)
  {
    return false;
  }
  for (int i=0; i < m_size; i++)
  {
    if (m_data[i] != rhs.m_data[i])
    {
      is_equal = false;
    }
  }
  return is_equal;
}