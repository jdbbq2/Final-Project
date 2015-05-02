//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer            Date: 4-3-2015                      //
// File: symmetricmatrix.hpp             section: a                             //
// Purpose: Contains function implementation for symmetricmatrix class          //
//////////////////////////////////////////////////////////////////////////////

template <typename T>
symmetricmatrix<T>::symmetricmatrix()
{
  m_dimentions = 0;
  m_data.setsize(0);
}

/*-----------Destructor------------*/

template <typename T>
symmetricmatrix<T>::~symmetricmatrix()
{
}

template <typename T>
symmetricmatrix<T>::symmetricmatrix (const symmetricmatrix<T>& cpy)
{
  m_dimentions = cpy.getdimentions();
  setsize(m_dimentions);

  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      m_data[i][j] = cpy.m_data[i][j];
    }
  }
}

// ---------------  Function to Print
// Purpose: prints an symmetricmatrix
template <typename T>
void symmetricmatrix<T>::print(ostream& out) const
{
  if (m_dimentions != 0)
  {
    for (int i=0; i < m_dimentions; i++)
    {
      out << m_data[i] << endl;
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
void symmetricmatrix<T>::read(istream& in)
{
  for (int i = 0; i < m_dimentions; i++)
  {
    in >> m_data[i];
  }
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      if (m_data[i][j] != m_data[j][i])
      {
        throw invalid_argument("Attempted read in of non-symmetric matrix.");
      }
    }
  }
  return;
}


template <typename T>
void symmetricmatrix<T>::setsize(const int size)
{
  if (size < 0)
  {
    throw length_error("Invalid setsize param");
  }
  m_dimentions = size;
  m_data.setsize(size);

  for (int i=0; i < size; i++)
  {
    m_data[i].setsize(size);
  }
  return;
}

// assignment operator
template <typename T>  
symmetricmatrix<T>& symmetricmatrix<T>::operator=(const symmetricmatrix<T>& source)
{
  m_dimentions = source.getdimentions();
  setsize(m_dimentions);

  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      m_data[i][j] = source.m_data[i][j];
    }
  }
  return *this;
}

template <typename T>  
symmetricmatrix<T> symmetricmatrix<T>::operator *(const T rhs) const
{
  symmetricmatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      tmp.m_data[i][j] *= rhs;
    }
  } 
  return tmp;
}

template <typename T>  
myVec<T> symmetricmatrix<T>::operator *(const myVec<T>& rhs) const
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
    tmp[i] = m_data[i] * rhs;
  } 
  return tmp;
}

template <typename T>  
symmetricmatrix<T> symmetricmatrix<T>::operator *(const symmetricmatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  symmetricmatrix<T> tmp;
  tmp.setsize(m_dimentions);
  myVec<T> column_holder(m_dimentions);

  for (int i=0; i < m_dimentions; i++) //row in calling matrix
  {
    for (int k=0; k < m_dimentions; k++)// column in rhs
    {
      for (int j=0; j < m_dimentions; j++) // row in rhs
      {
        column_holder[j] = rhs[j][k];
      }
      tmp.m_data[i][k] = column_holder * m_data[i];
    }
  } 
  return tmp;
}

template <typename T>  
symmetricmatrix<T> symmetricmatrix<T>::operator +(const symmetricmatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  symmetricmatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      tmp.m_data[i][j] += rhs[i][j];
    }
  } 
  return tmp;
}

template <typename T>  
denseMatrix<T> symmetricmatrix<T>::operator +(const myMatrix<T>& rhs) const
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
      tmp.m_data[i][j] += rhs[i][j];
    }
  } 
  return tmp;
}

template <typename T>  
symmetricmatrix<T> symmetricmatrix<T>::operator -(const symmetricmatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  symmetricmatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      tmp.m_data[i][j] -= rhs[i][j];
    }
  } 
  return tmp;
}

template <typename T>  
denseMatrix<T> symmetricmatrix<T>::operator -(const myMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp;
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions-i; j++)
    {
      tmp.m_data[i][j] -= rhs[i][j];
    }
  } 
  return tmp;
}

template <typename T>
symmetricmatrix<T> symmetricmatrix<T>::transpose() const
{
  symmetricmatrix<T> temp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      temp[i][j] = m_data[j][i];
    }
  }
  return temp;
}