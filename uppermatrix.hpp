//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman	    Date: 4-3-2015          //
// File: upperMatrix.hpp             section: a                             //
// Purpose: Contains function implementation for upperMatrix class          //
//////////////////////////////////////////////////////////////////////////////

template <typename T>
upperMatrix<T>::upperMatrix()
{
  m_dimentions = 0;
  m_data.setsize(0);
}

/*-----------Destructor------------*/

template <typename T>
upperMatrix<T>::~upperMatrix()
{
}

template <typename T>
upperMatrix<T>::upperMatrix (const upperMatrix<T>& cpy)
{
  m_dimentions = cpy.getdimentions();
  setsize(m_dimentions);

  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions-i; j++)
    {
      m_data[i][j] = cpy.m_data[i][j];
    }
  }
}

// ---------------  Function to Print
// Purpose: prints an upperMatrix
template <typename T>
void upperMatrix<T>::print(ostream& out) const
{
  if (m_dimentions != 0)
  {
    for (int i=0; i < m_dimentions; i++)
    {
      out << "[";
      for (int k=0; k < i; k++) // i 0s
      {
        out <<"0,";
      }
      for (int j=0; j < m_dimentions-i; j++)
      {
        out << m_data[i][j];
        if (j != (m_dimentions-i) - 1)
        {
          out << ",";
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
void upperMatrix<T>::read(istream& in)
{
  T temp;
  for (int i=0; i < m_dimentions; i++)
  {
    for (int k=0; k < i; k++) // ignore the first i characters
    {
      in >> temp;
    }
    for (int j=0; j < m_dimentions-i; j++)
    {
      in >> m_data[i][j];
    }
  }
  return;
}


template <typename T>
void upperMatrix<T>::setsize(const int size)
{
  if (size < 0)
  {
    throw length_error("invalid size");
  }
  m_dimentions = size;
  m_data.setsize(size);

  for (int i=0; i < size; i++)
  {
    m_data[i].setsize(size-i);
  }
  return;
}


// assignment operator
template <typename T>  
upperMatrix<T>& upperMatrix<T>::operator=(const upperMatrix<T>& source)
{
  m_dimentions = source.getdimentions();
  setsize(m_dimentions);

  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions-i; j++)
    {
      m_data[i][j] = source.m_data[i][j];
    }
  }
  return *this;
}

template <typename T>  
upperMatrix<T> upperMatrix<T>::operator *(const T rhs) const
{
  upperMatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions-i; j++)
    {
      tmp.m_data[i][j] *= rhs;
    }
  } 
  return tmp;
}

template <typename T>  
myVec<T> upperMatrix<T>::operator *(const myVec<T>& rhs) const
{
  if (rhs.getsize() != m_dimentions)
  {
    throw invalid_argument("Invalid dimentions");
  }
  myVec<T> tmp;
  T tempval;
  tmp.setsize(m_dimentions);
  for (int i=0; i < m_dimentions; i++)
  {
    tmp[i] = 0;
  }

  for (int i=0; i < m_dimentions; i++)
  {
    tempval = 0;
    for (int j=0; j < m_dimentions-i; j++)
    {
      tempval += m_data[i][j] * rhs[j];
    }
    tmp[i]=tempval;
  } 
  return tmp;
}

//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>  
upperMatrix<T> upperMatrix<T>::operator *(const upperMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  upperMatrix<T> tmp;
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

//////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>  
upperMatrix<T> upperMatrix<T>::operator +(const upperMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  upperMatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions-i; j++)
    {
      tmp[i][j] += rhs[i][j];
    }
  } 
  return tmp;
}

template <typename T>  
denseMatrix<T> upperMatrix<T>::operator +(const denseMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  return rhs+(*this);
}

template <typename T>  
denseMatrix<T> upperMatrix<T>::operator +(const lowerMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp;
  tmp.setsize(m_dimentions);
  tmp = tmp+rhs;
  tmp = tmp+(*this);
  return tmp;
}

template <typename T>  
upperMatrix<T> upperMatrix<T>::operator -(const upperMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  upperMatrix<T> tmp(*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions-i; j++)
    {
      tmp[i][j] -= rhs[i][j];
    }
  } 
  return tmp;
}

template <typename T>
denseMatrix<T> upperMatrix<T>::operator -(const denseMatrix<T>& rhs) const
{
  if (m_dimentions != rhs.getdimentions())
  {
    throw invalid_argument("Invalid dimentions");
  }
  denseMatrix<T> tmp;
  tmp.setsize(m_dimentions);

  tmp = tmp - (*this);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions-i; j++)
    {
      tmp[i][j] = -tmp.m_data[i][j];
    }
  } 
  return tmp;
}

template <typename T>
denseMatrix<T> upperMatrix<T>::operator -(const lowerMatrix<T>& rhs) const
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
      tmp[i][j] = 0;
    }
  }
  tmp = tmp + (*this);
  tmp = tmp - rhs;
  return tmp;
}

template <typename T>
denseMatrix<T> upperMatrix<T>::transpose() const
{
  denseMatrix<T> temp;
  temp.setsize(m_dimentions);
  for (int i=0; i < m_dimentions; i++)
  {
    for (int j=0; j < m_dimentions; j++)
    {
      temp[i][j] = 0;
    }
  }
  temp = temp +(*this);
  return temp.transpose();
}
