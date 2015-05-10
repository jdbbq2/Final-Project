//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman      Date: 5-9-2015         //
// File: driver.cpp                     section: a                          //
// Purpose: driver to test myMatrix class and gaussian_solver functor       //
//////////////////////////////////////////////////////////////////////////////

#include "myvec.h"
#include "mymatrix.h"
#include "gaussian_solver.h"
#include "pde_solver.h"
#include <iostream>
#include <cmath>

using namespace std;

double zero(double x) {return 0;};

# define PI 3.14159265358979323846264338

int main()
{    
  try
  {
    const int dimentions = 25;

    cout << endl << endl << "Creating symmetric Matrix class" << endl;
    symmetricmatrix<double> symmatrix;

    cout << endl << endl << "Creating dense Matrix class" << endl;
    denseMatrix<double> densematrix;

    cout << endl << endl << "Creating B vectors" << endl;
    myVec<double> b;
    myVec<double> B; //separate vectors for fairness in measuring solve time

    cout << endl << endl << "Setting matrix and vector dimentions" << endl;
    symmatrix.setsize(dimentions);
    densematrix.setsize(dimentions);
    b.setsize(dimentions);


    cout << endl << endl << "Creating pde_holder" << endl;
    pde_holder<double> myholder;

    cout << endl << endl << "Creating pde_solver" << endl;
    pde_solver<double> pdesolver;

    cout << endl << endl << "Initializing pde_solver" << endl;
    myholder.lower_boundary = sin;
    myholder.upper_boundary = zero;
    myholder.right_boundary = zero;
    myholder.left_boundary = sin;

    myholder.forcing_funct = zero;

    myholder.lowerbound_x = 0;
    myholder.upperbound_x = PI;
    myholder.lowerbound_y = 0;
    myholder.upperbound_y = PI;


    cout << endl << endl << "Creating pde matrix for symmetric" << endl;
    pdesolver(symmatrix, b, myholder);

    cout << endl << endl << "Solving pde using choelsky decomposition" << endl;
    gaussian_solver<double> system_solver;
    system_solver(symmatrix,b);


    cout << endl << endl << "Creating pde matrix for dense" << endl;
    pdesolver(densematrix, B, myholder);

    cout << endl << endl << "Solving pde using gaussian elimination" << endl;
    system_solver(densematrix,B);
  }

  catch (const invalid_argument& e){cout << e.what() << endl;}
  catch (const out_of_range& e){ cout << e.what() << endl;}

  return 0;
}
