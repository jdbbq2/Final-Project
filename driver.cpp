//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman      Date: 4-3-2015         //
// File: driver.cpp                     section: a                          //
// Purpose: driver to test myMatrix class and gaussian_solver functor       //
//////////////////////////////////////////////////////////////////////////////

#include "myvec.h"
#include "mymatrix.h"
#include "gaussian_solver.h"
#include <iostream>
#include <fstream>

using namespace std;

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

    cout << "Solving system using Cholesky: " << endl;
    gaussian_solver<double> solver;
    solver(symmatrix, b);

    cout << "Creating tridiagonal Matrix class" << endl;
    tridiagonalmatrix<double> trimatrix;

    cout << "Reading dimentions" << endl;
    inputfile >> dimentions;

    cout << "Setting matrix and vector dimentions" << endl;
    trimatrix.setsize(dimentions);
    b.setsize(dimentions);

    cout << "Reading in tridiagonal matrix" << endl;
    inputfile >> trimatrix;

    cout << "Reading B vector" << endl;
    inputfile >> b;
    cout << "B vector: " << endl << b << endl;
    cout << "TriDiagonal Matrix: " << endl << trimatrix << endl;

    cout << "Solving system using Thomas: " << endl;

    solver(trimatrix, b);

    inputfile.close();

  }

  catch (const invalid_argument& e){}
  catch (const out_of_range& e){}

  return 0;
}
