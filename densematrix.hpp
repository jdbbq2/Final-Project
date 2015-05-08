//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman   Date: 4-3-2015            //
// File: denseMatrix.hpp             section: a                             //
// Purpose: Contains function implementation for denseMatrix class          //
//////////////////////////////////////////////////////////////////////////////

template <typename T>
denseMatrix<T>::denseMatrix()
{
  m_dimentions = 0;
  m_data.setsize(0);
}

/*-----------Destructor------------*/

template <typename T>
denseMatrix<T>::~denseMatrix()
{
}

template <typename T>
denseMatrix<T>::denseMatrix (const denseMatrix<T>& cpy)
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
// Purpose: prints an denseMatrix
template <typename T>
void denseMatrix<T>::print(ostream& out) const
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
void denseMatrix<T>::read(istream& in)
{
  for (int i = 0; i < m_dimentions; i++)
  {
    in >> m_data[i];
  }
  return;
}


template <typename T>
void denseMatrix<T>::setsize(const int size)
{
  if (size < 0)
  {
    throw out_of_range("Invalid setsize param");
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
denseMatrix<T>& denseMatrix<T>::operator=(const denseMatrix<T>& source)
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
denseMatrix<T> denseMatrix<T>::operator *(const T rhs) const
{
  denseMatrix<T> tmp(*this);
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
myVec<T> denseMatrix<T>::operator *(const myVec<T>& rhs) const
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
denseMatrix<T> denseMatrix<T>::operator *(const denseMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp;
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
denseMatrix<T> denseMatrix<T>::operator +(const denseMatrix<T>& rhs) const
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
denseMatrix<T> denseMatrix<T>::operator +(const upperMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions-i; j++)
    {
      tmp.m_data[i][j+i] += rhs[i][j];
    }
  } 
  return tmp;
}

template <typename T>  
denseMatrix<T> denseMatrix<T>::operator +(const lowerMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < i+1; j++)
    {
      tmp.m_data[i][j] += rhs[i][j];
    }
  } 
  return tmp;
}

template <typename T>  
denseMatrix<T> denseMatrix<T>::operator -(const denseMatrix<T>& rhs) const
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
      tmp.m_data[i][j] -= rhs[i][j];
    }
  } 
  return tmp;
}

template <typename T>  
denseMatrix<T> denseMatrix<T>::operator -(const upperMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp(*this);
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
denseMatrix<T> denseMatrix<T>::operator -(const lowerMatrix<T>& rhs) const
{  
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < i+1; j++)
    {
      tmp.m_data[i][j] -= rhs[i][j];
    }
  } 
  return tmp;

}

template <typename T>  
void denseMatrix<T>::swap_rows(const int row1, const int row2)
{
  if ((row1 > m_dimentions-1 || row2 > m_dimentions-1) ||
      (row1 < 0 || row2 < 0))
  {
    throw invalid_argument("Invalid row swap");
  }
  if (row1 != row2)
  {
    myVec<T> row_holder(m_data[row1]);
    m_data[row1] = m_data[row2];
    m_data[row2] = row_holder;
  }
  return;
}

template <typename T>
denseMatrix<T> denseMatrix<T>::transpose() const
{
  denseMatrix<T> temp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      temp[i][j] = m_data[j][i];
    }
  }
  return temp;
}
