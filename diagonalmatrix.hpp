//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer            Date: 4-3-2015                      //
// File: diagonalmatrix.hpp             section: a                             //
// Purpose: Contains function implementation for diagonalmatrix class          //
//////////////////////////////////////////////////////////////////////////////

template <typename T>
diagonalmatrix<T>::diagonalmatrix()
{
  m_dimentions = 0;
  m_data.setsize(0);
  zero = 0;
}

/*-----------Destructor------------*/

template <typename T>
diagonalmatrix<T>::~diagonalmatrix()
{
}

template <typename T>
diagonalmatrix<T>::diagonalmatrix(const diagonalmatrix<T>& cpy)
{
  m_dimentions = cpy.getdimentions();
  setsize(m_dimentions);
  zero = 0;

  for (int i=0; i < m_dimentions; i++)
  {
    m_data[i] = cpy.m_data[i];
  }
}

// ---------------  Function to Print
// Purpose: prints an diagonalmatrix
template <typename T>
void diagonalmatrix<T>::print(ostream& out) const
{
  if (m_dimentions != 0)
  {
    for (int i = 0; i < m_dimentions; i++)
    {
      out << "[";
      for (int j=0; j < m_dimentions; j++)
      {
        if (j==i)
        {
          out << m_data[i] << ",";
        } else
        {
          out << "0,";
        }
      }
      out << "]" << endl;
    }
  }else
  {
    out << "[]";
  }
  return;
}

//// ---------------  Function to get input
//// Purpose: read in a matrix
template <typename T>
void diagonalmatrix<T>::read(istream& in)
{
  T temp;
  for (int i = 0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      if (j==i)
      {
        in >> m_data[i];
      } else
      {
        in >> temp;
      }
    }
  }
  return;
}


template <typename T>
void diagonalmatrix<T>::setsize(const int size)
{
  if (size < 0)
  {
    throw invalid_argument("Invalid setsize param");
  }
  m_dimentions = size;
  m_data.setsize(size);
  return;
}

// assignment operator
template <typename T>  
diagonalmatrix<T>& diagonalmatrix<T>::operator=(const diagonalmatrix<T>& source)
{
  m_dimentions = source.getdimentions();
  setsize(m_dimentions);

  for (int i=0; i < m_dimentions; i++)
  {
    m_data[i] = source.m_data[i];
  }
  return *this;
}

template <typename T>  
diagonalmatrix<T> diagonalmatrix<T>::operator *(const T rhs) const
{
  diagonalmatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    tmp.m_data[i] *= rhs;
  } 
  return tmp;
}

template <typename T>  
myVec<T> diagonalmatrix<T>::operator *(const myVec<T>& rhs) const
{
  if (rhs.getsize() != m_dimentions)
  {
    throw invalid_argument("Invalid dimentions");
  }
  myVec<T> tmp;
  tmp.setsize(m_dimentions);
  for (int i=0; i < m_dimentions; i++)
  {
    tmp[i] = 0;
  }
  for (int i=0; i < m_dimentions; i++)
  {
    tmp[i] = m_data[i] * rhs[i];
  } 
  return tmp;
}

template <typename T>  
diagonalmatrix<T> diagonalmatrix<T>::operator *(const diagonalmatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  diagonalmatrix<T> tmp;
  tmp.setsize(m_dimentions);

  for (int i=0; i < m_dimentions; i++)
  {
    tmp.m_data[i] = rhs.m_data[i] * m_data[i];
  } 
  return tmp;
}

template <typename T>  
diagonalmatrix<T> diagonalmatrix<T>::operator +(const diagonalmatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  diagonalmatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    tmp.m_data[i] += rhs(i,i);
  } 
  return tmp;
}

template <typename T>  
denseMatrix<T> diagonalmatrix<T>::operator +(const myMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp;
  tmp.setsize(m_dimentions);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      if (i == j)
        tmp(i,j) = rhs(i,j) + m_data[i];
      else
        tmp(i,j) = rhs(i,j);
    }
  } 
  return tmp;
}

template <typename T>  
diagonalmatrix<T> diagonalmatrix<T>::operator -(const diagonalmatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  diagonalmatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    tmp.m_data[i] -= rhs(i,i);
  } 
  return tmp;
}

template <typename T>  
denseMatrix<T> diagonalmatrix<T>::operator -(const myMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp;
  tmp.setsize(m_dimentions);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      if (i == j)
        tmp(i,j) = rhs(i,j) - m_data[i];
      else
        tmp(i,j) = rhs(i,j);
    }
  } 
  return tmp;
}


template <typename T>
T& diagonalmatrix<T>::operator ()(const int row, const int column)
{
  if(row == column)
    return m_data[row];
  return zero;
}
template <typename T>
const T& diagonalmatrix<T>::operator ()(const int row, const int column) const
{
  if(row == column)
    return m_data[row];
  return zero;
}