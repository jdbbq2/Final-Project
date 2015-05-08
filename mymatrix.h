//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman   Date: 4-3-2015            //
// File: myMatrix.hpp             section: a                                //
// Purpose: Contains function implementation for myMatrix class             //
//////////////////////////////////////////////////////////////////////////////

#include "myvec.h"
#include <stdexcept>

#ifndef MYMATRIX_H
#define MYMATRIX_H

////////////////////////////////////////////////////////////////
// Class: myMatrix                                            //
// Purpose: The myMatrix interface base class models          //
//          a mathematical matrix.                            //
//          Derived classes include dense, upper, and lower.  //
//          Matrix multiplication, multiplication by a scalar,//
//          and multiplication by a vector are all supported. //
//          Addition and subtraction between matrices is also //
//          available. The matrix can be solved using the     //
//          gaussian_solver functor.                          //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//Function: ~myMatrix()                                       // 
//Precondition: none                                          //
//Postcondition: the object is destroyed and the memory is    //
//               deallocated                                  //
//Description: virtual destructor for myMatrix                //
////////////////////////////////////////////////////////////////

//Note Functionality forwarded (virtual): see derived classes documentation for details
////////////////////////////////////////////////////////////////////
//Function: friend ostream& operator<<                            //
//          (ostream& out, const myMatrix<T>& vec)                //
//          friend istream& operator>>                            //
//         (istream& in, myMatrix<T>& vec)                        // 
//Precondition: objects put in stream must be of type T and must  //
//              follow the format: int for dimentions followed by //
//                                 dimentions*dimentions objects  //
//                                 separated by whitespace        //
//Postcondition: matrix information is input/output from/to stream//
//               matrix is assigned dimentions and input values   //
//Description: Stream operators for myMatrix                      //
//  output format - [ comma delimited elements] repeated for each //
//                  [ comma delimited elements] row in the matrix //
//  input format - int for dimentions then                        //
//                 # # # (delimiting characters between elements) //
//  Type of objects are not checked                               //
//  These friend functions forward implementation to the type of  //
//  matrix through the pure virtual read/print functions          //
////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//Function:      myVec<T> operator *(const myVec<T>& rhs) const;           //
//                                                                         //
//Precondition: *= must be defined for T                                   //
//              vector must be same size as matrix dimentions              //
//Postcondition: vector is returned that is the product of the calling     //
//               vector*rhs                                                //
//                                                                         //
//Description: The matrix will always be on the LEFT hand side of these    //
//              operations. The copy constructor is called to make the     //
//              temp returned object. Vector class is used. (for other     //
//              multiplication operators)                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


//Note Functionality forwarded (virtual): see derived classes documentation for details
////////////////////////////////////////////////////////////////////////////////////
//Function:         myVec<T>& operator [](const int index);                       //
//      const myVec<T>& operator [] (const int index)const;                       //
//Precondition: The index used to access the elements are of type int and are     //
//               greater than -1, less than m_dimentions (inside matrix)          //
//               The object is NOT an upper or lower matrix, for accessing elemnts//
//               in upper or lower matrices use the () operator with 2 arguments  //
//Postcondition: A reference to the indexed vector is returned                    //
//               Note: this allows for [][] accessing individual elements by using//
//                     the vector bracket operator                                //
//Description: The normal index operator for retrieving vectors from a matrix     //
////////////////////////////////////////////////////////////////////////////////////

//Note Functionality forwarded (virtual): see derived classes documentation for details
//////////////////////////////////////////////////////////////////////////
//Function:   int getdimentions() const;                                //
//            void setsize(const int size);                             //
//Precondition: setsize argument is not negative                        //
//                                                                      //
//Postcondition: the dimentions of the matrix are returned              //
//               sets dimentions and resizes all vectors to size        //
//Description: getsize is a standard accessor for size of the matrix,   //
//             setsize resizes underlying arrays without memory leaks   //
//////////////////////////////////////////////////////////////////////////

//Note Functionality forwarded (virtual): see derived classes documentation for details
///////////////////////////////////////////////////////////////////
//Function:   void swap_rows(const int row1, const int row2);    //
//Precondition: row1 and row2 are inside the matrix (exception)  //
//              calling object is NOT upper or lower matrix,     //
//              swapping rows would make those matrices invalid  //
//Postcondition: the rows with the indices passed are swapped in //
//               the calling object                              //
//Description: the indices ascend as you go down the matrix and  //
//             start at 0, not 1                                 //
///////////////////////////////////////////////////////////////////

//Functions:
//      virtual void read(istream& in) = 0;
//      virtual void print(ostream& out) const = 0;

//These are helper functions to forward implementation of insertion
// and extraction operators, see <<.>> for pre,post, and details

// --------------- Forward Declarations 
template <typename T>
class myMatrix;                       

template <typename T>                 // a friend function for output
ostream& operator<< (ostream& out, const myMatrix<T>& vec);

template <typename T>                 // a friend function for input
istream& operator>> (istream& in, myMatrix<T>& vec);

template <typename T>
class myMatrix
{
  public:

    virtual ~myMatrix(){};

    virtual myVec<T> operator *(const myVec<T>& rhs) const = 0;

//    virtual myVec<T>& operator [](const int index) = 0;
//    virtual const myVec<T>& operator [] (const int index)const = 0;
    virtual T& operator ()(const int row, const int column) = 0;
    virtual const T& operator ()(const int row, const int column)const = 0;

    virtual void setsize(const int size) = 0;
    virtual int getdimentions()const = 0;
//    virtual void swap_rows(const int row1, const int row2) = 0;

            // Purpose: prints the myMatrix
      friend ostream& operator<< <> (ostream& out, 
                                       const myMatrix<T>& matrix);
        // Purpose: reads in the myMatrix
      friend istream& operator>> <> (istream& in, 
                                        myMatrix<T>& matrix);
    protected:

      virtual void read(istream& in) = 0;
      virtual void print(ostream& out) const = 0;
};

// ---------------  Friend Function to Print
// Purpose: prints an myMatrix
template <typename T>                 
ostream& operator<< (ostream& out, const myMatrix<T>& matrix)
{
  matrix.print(out);
  return out;
}

// ---------------  Friend Function to get input
// Purpose: read in a line of data
template <typename T>                 
istream& operator>> (istream& in, myMatrix<T>& matrix)
{
  matrix.read(in);
  return in;
}

#include "densematrix.h"
#include "uppermatrix.h"
#include "lowermatrix.h"
#include "diagonalmatrix.h"
#include "symmetricmatrix.h"
#include "tridiagonalmatrix.h"

#endif
