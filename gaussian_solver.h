//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer            Date: 4-3-2015                      //
// File: gaussian_solver.h                         section: a               //
// Purpose: Contains the class gaussian_solver and the prototype for the    //
//          member function                                                 //
//////////////////////////////////////////////////////////////////////////////

#ifndef GAUSSIAN_SOLVER_H
#define GAUSSIAN_SOLVER_H

#include "mymatrix.h"
#include "myvec.h"
#include <cmath>

//////////////////////////////////////////////////////////////////
// Class: gaussian_solver                                       //
// Purpose: This is a functor class whose sole purpose is to    //
//          use the () operator to solve the system of equations//
//          represented by the parameter matrix and vector using//
//          gaussian elimination with partial pivoting. If the  //
//          parameters are invalid an exception is thrown.      //
//////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
//Function:void   void operator() (const denseMatrix<V> matrix, const myVec<V> soln_vec);//
//                void operator() (const upperMatrix<V> matrix, const myVec<V> soln_vec);//
//                void operator() (const lowerMatrix<V> matrix, const myVec<V> soln_vec);////////
//                void operator() (const symmetricmatrix<V> matrix, const myVec<V> soln_vec);  //
//                void operator() (const diagonalmatrix<V> matrix, const myVec<V> soln_vec);   //
//                void operator() (const tridiagonalmatrix<V> matrix, const myVec<V> soln_vec);//
//Precondition: The passed matrix must be nxn and the vector of size n         //////////////////
//              * must be defined for T, the vector class is heavily used in   //
//              this algorithm so preconditions regarding the myVec class      //
//              must be followed (element wise divide, vector subtraction, etc)//
//Postcondition: The result of the algorithm is output,                        //
//               The results include:                                          //
//                   either no solution (if the system has no solution)        //
//                   the b vector and the x vector in Ax=b                     //
//Description: the computation involves solving a system of equations          //
//             represented by the passed matrix and vector. This process is    //
//             complex and lengthy (around O(n^3) time). If the matrix is unique////
//             (like diagonal, tridiagonal, or symmetric) then the process is much//
//              faster and algorithms have been implemented for them.          /////
//              Tridiagonal-Thomas algorithm                                   //
//              symmetric- Cholesky                                            //
/////////////////////////////////////////////////////////////////////////////////
template <typename V>                 
class gaussian_solver
{
  public:
    void operator() (const denseMatrix<V> matrix, const myVec<V> soln_vec);
    void operator() (const upperMatrix<V> matrix, const myVec<V> soln_vec);
    void operator() (const lowerMatrix<V> matrix, const myVec<V> soln_vec);
    void operator() (const symmetricmatrix<V> matrix, const myVec<V> soln_vec);
    void operator() (const diagonalmatrix<V> matrix, const myVec<V> soln_vec);
    void operator() (const tridiagonalmatrix<V> matrix, const myVec<V> soln_vec);

};

# include "gaussian_solver.hpp"

#endif