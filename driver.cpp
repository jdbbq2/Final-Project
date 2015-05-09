//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman      Date: 4-3-2015         //
// File: driver.cpp                     section: a                          //
// Purpose: driver to test myMatrix class and gaussian_solver functor       //
//////////////////////////////////////////////////////////////////////////////

#include "myvec.h"
#include "mymatrix.h"
#include "gaussian_solver.h"
#include "pde_solver.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double zero(double x) {return 0;};

# define PI 3.14159265358979323846264338

int main(int argc, char* argv[])
{    
  try
  {
    if (argc != 2)
    {
      // Tell the user how to run the program
      throw invalid_argument("Please pass the input filename as a command line argument.");
    }
  
    ifstream inputfile (argv[1]);
    if (!inputfile.is_open())
    {
      throw invalid_argument("Could not open input file.");
    }

    int dimentions;

    cout << endl << endl << "Creating symmetric Matrix class" << endl;
    symmetricmatrix<double> symmatrix;

    cout << "Creating B vector" << endl;
    myVec<double> b;

    cout << "Reading dimentions" << endl;
    inputfile >> dimentions;

    cout << "Setting matrix and vector dimentions" << endl;
    symmatrix.setsize(dimentions);
    b.setsize(dimentions);

    cout << "Reading symmetric matrix" << endl;
    inputfile >> symmatrix;

    cout << "Reading B vector" << endl;
    inputfile >> b;

    cout << "B vector: " << endl << b << endl;
    cout << "symmetric Matrix: " << endl << symmatrix << endl;

    cout << "Creating pde_holder" << endl;
    pde_holder<double> myholder;

    cout << "Creating pde_solver" << endl;
    pde_solver<double> mysolver;

    cout << "Initializing pde_solver" << endl;
    myholder.lower_boundary = sin;
    myholder.upper_boundary = zero;
    myholder.right_boundary = zero;
    myholder.left_boundary = sin;

    myholder.lowerbound_x = 0;
    myholder.upperbound_x = PI;
    myholder.lowerbound_y = 0;
    myholder.upperbound_y = PI;

    cout << "Creating outmatrix, outvector" << endl;
    symmetricmatrix<double> outmatrix;
    myVec<double> outvector;

    mysolver(symmatrix, b, outmatrix, outvector, myholder);

    inputfile.close();

  }

  catch (const invalid_argument& e){cout << e.what() << endl;}
  catch (const out_of_range& e){ cout << e.what() << endl;}

  return 0;
}
