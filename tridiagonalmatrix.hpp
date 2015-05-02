//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer            Date: 4-3-2015                      //
// File: tridiagonalmatrix.hpp             section: a                             //
// Purpose: Contains function implementation for tridiagonalmatrix class          //
//////////////////////////////////////////////////////////////////////////////

template <typename T>
tridiagonalmatrix<T>::tridiagonalmatrix()
{
  m_dimentions = 0;
  m_g.setsize(0);
  m_e.setsize(0);
  m_f.setsize(0);
  zero = 0;
}

/*-----------Destructor------------*/

template <typename T>
tridiagonalmatrix<T>::~tridiagonalmatrix()
{
}

template <typename T>
tridiagonalmatrix<T>::tridiagonalmatrix (const tridiagonalmatrix<T>& cpy)
{
  m_dimentions = cpy.getdimentions();
  setsize(m_dimentions);
  zero = 0;

  m_g = cpy.m_g;
  m_e = cpy.m_e;
  m_f = cpy.m_f;
}

// ---------------  Function to Print
// Purpose: prints an tridiagonalmatrix
template <typename T>
void tridiagonalmatrix<T>::print(ostream& out) const
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
          out << m_f[i] << ",";
        } else if (j == i+1)
        {
          out << m_g[j-1] << ",";
        } else if (i == j+1)
        {
          out << m_e[i-1] << ",";
        } else
        {
          out << "0,";
        }
      }
      out << "]" << endl;
    }
  } else
  {
    out << "[]";
  }
  return;
}

//// ---------------  Function to get input
//// Purpose: read in a matrix
template <typename T>
void tridiagonalmatrix<T>::read(istream& in)
{
  T temp;
  for (int i = 0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
        if (j==i)
        {
          in >> m_f[i];
        } else if (j == i+1)
        {
          in >> m_g[j-1];
        } else if (i == j+1)
        {
          in >> m_e[i-1];
        } else
        {
          in >> temp;
        }
    }
  }
  return;
}


template <typename T>
void tridiagonalmatrix<T>::setsize(const int size)
{
  if (size < 0)
  {
    throw length_error("Invalid setsize param");
  }
  m_dimentions = size;
  m_g.setsize(size-1); 
  m_f.setsize(size);
  m_e.setsize(size-1);

  return;
}

// assignment operator
template <typename T>  
tridiagonalmatrix<T>& tridiagonalmatrix<T>::operator=(const tridiagonalmatrix<T>& source)
{
  m_dimentions = source.getdimentions();
  setsize(m_dimentions);

  m_g = source.m_g;
  m_e = source.m_e;
  m_f = source.m_f;
  return *this;
}

template <typename T>  
tridiagonalmatrix<T> tridiagonalmatrix<T>::operator *(const T rhs) const
{
  tridiagonalmatrix<T> tmp(*this);
  tmp.m_f = tmp.m_f * rhs;
  tmp.m_g = tmp.m_g * rhs;
  tmp.m_e = tmp.m_e * rhs;

  return tmp;
}

template <typename T>  
myVec<T> tridiagonalmatrix<T>::operator *(const myVec<T>& rhs) const
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
    for (int j=0; j < m_dimentions; j++)
    {
      if (j==i)
      {
        tmp[i] = tmp[i] + rhs[i]*m_f[i];
      } else if (j == i+1)
      {
        tmp[i] = tmp[i] + rhs[j]*m_g[j-1];
      } else if (i == j+1)
      {
        tmp[i] = tmp[i] + rhs[i-1]*m_e[i-1];
      } 
    }
  }
  return tmp;
}

template <typename T>  
tridiagonalmatrix<T> tridiagonalmatrix<T>::operator *(const tridiagonalmatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  tridiagonalmatrix<T> tmp;
  tmp.setsize(m_dimentions);
  myVec<T> column_holder(m_dimentions);

  tmp.m_g = m_g*rhs.m_g;
  tmp.m_f = m_f*rhs.m_f;
  tmp.m_e = m_e*rhs.m_e;
  return tmp;
}

template <typename T>  
tridiagonalmatrix<T> tridiagonalmatrix<T>::operator +(const tridiagonalmatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  tridiagonalmatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      if (j==i)
      {
        tmp(i,i) += rhs(i,i);
      } else if (j == i+1)
      {
        tmp(i,j) += rhs(i,j);
      } else if (i == j+1)
      {
        tmp(i,j) += rhs(i,j);
      } 
    }
  } 
  return tmp;
}

template <typename T>  
denseMatrix<T> tridiagonalmatrix<T>::operator +(const myMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      if (j==i)
      {
        tmp(i,i) += rhs(i,i);
      } else if (j == i+1)
      {
        tmp(i,j) += rhs(i,j);
      } else if (i == j+1)
      {
        tmp(i,j) += rhs(i,j);
      } 
    }
  } 
  return tmp;
}


template <typename T>  
tridiagonalmatrix<T> tridiagonalmatrix<T>::operator -(const tridiagonalmatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  tridiagonalmatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      if (j==i)
      {
        tmp(i,i) += rhs(i,i);
      } else if (j == i+1)
      {
        tmp(i,j) += rhs(i,j);
      } else if (i == j+1)
      {
        tmp(i,j) += rhs(i,j);
      } 
    }
  } 
  return tmp;
}

template <typename T>  
denseMatrix<T> tridiagonalmatrix<T>::operator -(const myMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      if (j==i)
      {
        tmp(i,i) -= rhs(i,i);
      } else if (j == i+1)
      {
        tmp(i,j) -= rhs(i,j);
      } else if (i == j+1)
      {
        tmp(i,j) -= rhs(i,j);
      } 
    }
  } 
  return tmp;
}

template <typename T>
T& tridiagonalmatrix<T>::operator ()(const int row, const int column)
{
  if(row == column)
  {
    return m_f[row];
  } else if (column == row+1)
  {
    return m_g[column-1];
  } else if (row == column+1)
  {
    return m_e[row-1];
  }
  return zero;
}
template <typename T>
const T& tridiagonalmatrix<T>::operator ()(const int row, const int column) const
{
  if(row == column)
  {
    return m_f[row];
  } else if (column == row+1)
  {
    return m_g[column-1];
  } else if (row == column+1)
  {
    return m_e[row-1];
  }
  return zero;
}