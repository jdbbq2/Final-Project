//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman           Date: 5-8-2015    //
// File: pde_solver.h                    section: a                         //
// Purpose: Contains header for a class that solves a pde                   //
//////////////////////////////////////////////////////////////////////////////

#include "pde_holder.h"

#ifndef PDE_SOLVER_H
#define PDE_SOLVER_H

////////////////////////////////////////////////////////////////
// Class: pde_solver                                          //
// Purpose: Description of class goes here                    //
////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//Function:void   void operator() (const myMatrix<T>& inmatrix, const myVec<T>&,                //
//                      myMatrix<T>& outmatrix, myVec<T>& outvector, const pde_holder& the_pde);//
//                                                                             ///////////////////
//Precondition: size of matrix must be a perfect square                        //
//Postcondition:                                                               //
//Description: dimentions of passed matrix represents number of points to compute//
/////////////////////////////////////////////////////////////////////////////////


template <typename T>

class pde_solver
{
  public:
    void operator() (myMatrix<T>& outmatrix, myVec<T>& outvector, const pde_holder<T>& the_pde);
};

#include "pde_solver.hpp"

#endif