//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer            Date: 4-3-2015                      //
// File: gaussian_solver.hpp                       section: a               //
// Purpose: Contains function implementation for gaussian_solver class      //
//////////////////////////////////////////////////////////////////////////////

template <typename V>
void gaussian_solver<V>::operator() (const denseMatrix<V> matrix, const myVec<V> soln_vec)
{
  if (matrix.getdimentions() != soln_vec.getsize())
    throw invalid_argument("matrix size does not match vector size");

  denseMatrix<V> a(matrix);
  myVec<V> b(soln_vec);
  bool zeros; // keeps track of zero rows to determine end conditions

  V temp;
  V largest = 0;
  int largeindex = 0;
  int dimentions = matrix.getdimentions();
  myVec<V> x(dimentions); 
  myVec<int> free_coeff(dimentions);

  for (int i=0; i < dimentions; i++) // initialize helper vectors
  {
    x[i] = 0;
    free_coeff[i] = -1;
  }

  for (int i=0; i < dimentions; i++)//matrix column
  {
    largest = 0;
    largeindex= i;
    for (int j=i; j < dimentions; j++)//matrix row
    {
      if (largest < abs(a[j][i]))
      {
        largest = a[j][i];
        largeindex = j;
      }
    }
    a.swap_rows(i,largeindex);
    if (i != largeindex)
    {
      temp = b[i];
      b[i] = b[largeindex];
      b[largeindex] = temp;
    }

    if (largest != 0) // make the pivot 1
    {
      a[i] = a[i]/largest;
      b[i] = b[i]/largest;
    }
    for (int k=i+1; k < dimentions; k++)
    {   
      temp = -a[k][i]; //coefficient to multiply by
      a[k] = a[k] + (a[i]* temp); // zero out zeros below pivot
      b[k] = b[k] + (b[i]* temp);
    }
  }

  for (int i=0; i < dimentions; i++) //checking for no solution condition
  {
    zeros = true;
    for (int j=0; j < dimentions; j++)
    {
      if (a[i][j] != 0)
      {
        zeros = false;
      }
    }
    if (zeros == true)
    {
      if (b[i] != 0)
      {
        cout << endl << "There is no solution for this system." << endl;
        cout << "The system is inconsistent." << endl;
        return;
      }
    }
  }
  for (int i=dimentions-1; i >= 0; i--)//for all coefficients
  {
    x[i] = b[i]; // 0 .. x = b
    for (int j=i-1; j >=0; j--)//going up the matrix from diagonal
    {
      b[j] = b[j] - (x[i]*a[j][i]); // 0 x aji b -> 0 x 0 b
    }
  }
  cout <<"b vector: " << x << endl << endl;
  cout <<"a matrix: " << endl << a << endl << endl;
  cout <<"SOLUTION: " << endl;
  for (int i=dimentions-1; i >= 0; i--)
  {
    if (x[i] == 0) // free coeff
    {
      cout << "X_" << i << " = " << "Free" << endl;
      free_coeff[i] = 1;
    } else
    {
      cout << "X_" << i << " = " << x[i];
      for (int k=0; k < dimentions; k++)
      {
        if (free_coeff[k] == 1)
        {
          cout << " - " << a[i][k] << "X_" << k;
        }
      }
      cout << endl;
    }
  }
  return;
}

template <typename V>
void gaussian_solver<V>::operator() (const upperMatrix<V> matrix, const myVec<V> soln_vec)
{
  if (matrix.getdimentions() != soln_vec.getsize())
    throw invalid_argument("matrix size does not match vector size");

  upperMatrix<V> a(matrix);
  myVec<V> b(soln_vec);
  bool zeros; // keeps track of zero rows to determine end conditions

  V temp;
  V largest = 0;
  int largeindex = 0;
  int dimentions = matrix.getdimentions();
  myVec<V> x(dimentions); 
  myVec<int> free_coeff(dimentions);

  for (int i=0; i < dimentions; i++) //checking for no solution condition
  {
    zeros = true;
    for (int j=0; j < dimentions; j++)
    {
      if (a(i,j) != 0)
      {
        zeros = false;
      }
    }
    if (zeros == true)
    {
      if (b[i] != 0)
      {
        cout << endl << "There is no solution for this system." << endl;
        cout << "The system is inconsistent." << endl;
        return;
      }
    }
  }
  for (int i=dimentions-1; i >= 0; i--)//for all coefficients
  {
    x[i] = b[i]; // 0 .. x = b
    for (int j=i-1; j >=0; j--)//going up the matrix from diagonal
    {
      b[j] = b[j] - (x[i]*a(j,i)); // 0 x aji b -> 0 x 0 b
    }
  }
  cout <<"b vector: " << x << endl << endl;
  cout <<"a matrix: " << endl << a << endl << endl;
  cout <<"SOLUTION: " << endl;
  for (int i=dimentions-1; i >= 0; i--)
  {
    if (x[i] == 0) // free coeff
    {
      cout << "X_" << i << " = " << "Free" << endl;
      free_coeff[i] = 1;
    } else
    {
      cout << "X_" << i << " = " << x[i];
      for (int k=0; k < dimentions; k++)
      {
        if (free_coeff[k] == 1)
        {
          cout << " - " << a(i,k) << "X_" << k;
        }
      }
      cout << endl;
    }
  }
  return;
}

template <typename V>
void gaussian_solver<V>::operator() (const lowerMatrix<V> matrix, const myVec<V> soln_vec)
{
  if (matrix.getdimentions() != soln_vec.getsize())
    throw invalid_argument("matrix size does not match vector size");
  gaussian_solver<V> solverhelper;
  solverhelper(matrix.transpose(), soln_vec);
  return;
}

template <typename V>
void gaussian_solver<V>::operator() (const symmetricmatrix<V> matrix, const myVec<V> soln_vec)
{
  /*--------------------------SOLVING WITH CHOLESKY----------------------*/
  //solving Ax = b
  int size = matrix.getdimentions();
  symmetricmatrix<V> L;
  myVec<V> b(soln_vec);
  L.setsize(size);
  //set matrix elements to zeros
  for (int i=0; i < size; i++)
  {
    for (int j=0; j < size; j++)
    {
      L[i][j] = 0;
    }
  }
  //Decompose A = LL*
  if (matrix.getdimentions() != soln_vec.getsize())
    throw invalid_argument("matrix size does not match vector size");

  for (int i =0; i < size; i++)
  {
    for (int j=0; j < (i+1); j++)
    {
      V s = 0;
      for (int k=0; k < j; k++)
      {
        s += L[i][k] * L[j][k];
      }
      L[i][j] = (i == j) ? sqrt(matrix[i][i] - s) : (1.0 / L[j][j] * (matrix[i][j] - s));
    }
  }
  //Solve Ly = b for y (forward sub)
  for (int i=0; i < size; i++)
  {
    for (int j=0; j < i; j++)
    {
      b[i] = b[i] - (b[j]*L[i][j]);
    }
    b[i] = b[i]/L[i][i];
  }
  //Solve L*x = y for x (back sub)
  L = L.transpose();
  for (int i=size-1; i > -1; i--)
  {
    for (int j=size-1; j > i; j--)
    {
      b[i] = b[i] - (b[j]*L[i][j]);
    }
    b[i] = b[i]/L[i][i];
  }
  for (int i=0; i < size; i++)
  {
    cout << "X_" << i << " = " << b[i] << endl;
  }
  return;
}

template <typename V>
void gaussian_solver<V>::operator() (const diagonalmatrix<V> matrix, const myVec<V> soln_vec)
{
  int dimentions = matrix.getdimentions();
  if (matrix.getdimentions() != soln_vec.getsize())
    throw invalid_argument("matrix size does not match vector size");

  myVec<V> b(soln_vec);
  for (int i=dimentions-1; i >= 0; i--)
  {
    if (matrix[i] == 0) // free coeff
    {
      cout << "X_" << i << " = " << "Free" << endl;
      b[i] = 1;
    } else
    {
      cout << "X_" << i << " = " << matrix[i];
      for (int k=0; k < dimentions; k++)
      {
        if (b[k] == 1)
        {
          cout << " - " << matrix(i,k) << "X_" << k;
        }
      }
      cout << endl;
    }
  }
  return;
}

template <typename V>
void gaussian_solver<V>::operator() (const tridiagonalmatrix<V> matrix, const myVec<V> soln_vec)
{
  /*--------------------------SOLVING WITH THOMAS----------------------*/

  int n = matrix.getdimentions();
  myVec<V> d(soln_vec);
  myVec<V> b(matrix.getf());
  myVec<V> a(matrix.gete());
  myVec<V> c(matrix.getg());

  if (n != soln_vec.getsize())
    throw invalid_argument("matrix size does not match vector size");

  n--; // since we start from x0 (not x1)
  c[0] /= b[0];
  d[0] /= b[0];

  for (int i = 1; i < n; i++)
  {
      c[i] /= b[i] - a[i-1]*c[i-1];
  }

  for (int i=1; i <= n; i++)
  {
    d[i] = (d[i] - a[i-1]*d[i-1]) / (b[i] - a[i-1]*c[i-1]);
  }
  for (int i = n; i-- > 0;)
  {
      d[i] -= c[i]*d[i+1];
  }
  for (int i=0; i < n; i++)
  {
    cout << "X_" << i << " = " << d[i] << endl;
  }
  return;
}
