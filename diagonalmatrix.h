//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer            Date: 4-3-2015                      //
// File: diagonalmatrix.hpp             section: a                             //
// Purpose: Contains function implementation for diagonalmatrix class          //
//////////////////////////////////////////////////////////////////////////////

#include "myvec.h"

#ifndef DIAGONALMATRIX_H
#define DIAGONALMATRIX_H

////////////////////////////////////////////////////////////////
// Class: diagonalmatrix                                      //////
// Purpose: The diagonalmatrix class models a mathematical matrix.//
//          Matrix multiplication, multiplication by a scalar,//////
//          and multiplication by a vector are all supported. //
//          Addition and subtraction between matrices is also //
//          available. The matrix can be solved using the     //
//          gaussian_solver functor. This matrix specifically //
//          represents a matrix for which only the diagonal   //
//          elements have non-zero values.                    //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//Function:     diagonalmatrix();                             //
//              diagonalmatrix(const diagonalmatrix& cpy);    // 
//Precondition: cpy must be square matrix (NxN)               //
//Postcondition: an object of type diagonalmatrix is created  //
//               default size of 0 for dimentions             /////
//Description: constructors for diagonalmatrix, copy constructor //
//             performs a deep cpy and calls setsize          /////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//Function: ~diagonalmatrix()                                 // 
//Precondition: none                                          //
//Postcondition: the object is destroyed and the memory is    //
//               deallocated                                  //
//Description: destructor for diagonalmatrix                  //
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//Function:    diagonalmatrix<T>& operator =(const diagonalmatrix<T>& source);//
//                                                                            //
//Precondition: source must be an nxn matrix                                  //
//Postcondition: the sizes and data are copied from source to the new matrix  //
//               a deep copy is performed for the dynamically allocated memory//
//Description: the normal assignment operator                                 //
//             empty source matrix (size 0) works without memory leaks        //
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//Function:   diagonalmatrix<T> operator +(const diagonalmatrix<T>& rhs) const;//
//            diagonalmatrix<T> operator +(const myMatrix<T>& rhs) const;      //
//                                                                             //
//            diagonalmatrix<T> operator -(const diagonalmatrix<T>& rhs) const;//
//            diagonalmatrix<T> operator -(const myMatrix<T>& rhs) const;    ////
//                                                                           //
//Precondition: the corresponding operator MUST be defined for type T        //
//              (+=, -=), rhs must be nxn                                    //
//                                                                           //
//Postcondition: each operation is performed on all RELEVANT elements        //
//               and a temp matrix with the results is returned              //
//Description: None of these operations change the passed objects, they      //
//        return a temporary matrix containing the results.                  //
//        the operations are performed on each RELEVANT element in succession//
//        note: the copy constructor is called for the calling object        //
//              so these can only be performed on two NxN matrices           //
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//Function:      diagonalmatrix<T> operator *(const T rhs) const;          //
//               myVec<T> operator *(const myVec<T>& rhs) const;           /////////
//               diagonalmatrix<T> operator *(const diagonalmatrix<T>& rhs) const;//
//                                                                         /////////
//Precondition: *= must be defined for T                                   //
//              matrices must be square matrices of the same dimentions    //
//              vector must be of same dimention as matrix                 //
//Postcondition: Scalar multiplication: temp matrix is returned with each  //
//                  element multiplied by rhs                              //
//               Multiplication by vector: temp vector is returned that is //
//                  the standard result                                    //
//               Matrix multiplication: temp matrix is returned that is the//
//                  standard result                                        //
//Description: The matrix will always be on the LEFT hand side of these    //
//              operations. The copy constructor is called to make the     //
//              temp returned object. Vector class is used.                //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
//Function:     virtual T& operator ()(const int row, const int column);            //
//              virtual const T& operator ()(const int row, const int column)const; //
//Precondition: Indices used should be inside the array (greater than -1, less than //
//              dimentions)                                                         //
//Postcondition: A reference to the indexed value is returned                       //
//Description: Acts as expected for retrieving elements of the matrix               //
//////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////
//Functions: virtual void read(istream& in);                      //
//           virtual void print(ostream& out) const;              //
//Precondition: the matrix elements are zero outside the diagonal //
//Postcondition: these functions work similarly to insertion      //
//               and extraction operators                         //
//               they are not public                              //
//               matrix information is input/output from/to stream//
//               matrix is assigned dimentions and input values   //
//  output format - [ comma delimited elements] repeated for each //
//                  [ comma delimited elements] row in the matrix //
//  input format - int for dimentions then                        //
//                 # # # (delimiting characters between elements) //
//  Type of objects are not checked                               //
////////////////////////////////////////////////////////////////////

// --------------- Forward Declarations 
template <typename T>
class diagonalmatrix;                       

template <typename T>
class upperMatrix;                       

template <typename T>
class lowerMatrix;                       


template <typename T>
class diagonalmatrix : public myMatrix<T>
{
  public:
    diagonalmatrix();
    diagonalmatrix(const diagonalmatrix& cpy);
    virtual ~diagonalmatrix();

    diagonalmatrix<T>& operator =(const diagonalmatrix<T>& rhs);

    diagonalmatrix<T> operator +(const diagonalmatrix<T>& rhs) const;
    denseMatrix<T> operator +(const myMatrix<T>& rhs) const;

    diagonalmatrix<T> operator -(const diagonalmatrix<T>& rhs) const;
    denseMatrix<T> operator -(const myMatrix<T>& rhs) const;

    diagonalmatrix<T> operator *(const T rhs) const;
    virtual myVec<T> operator *(const myVec<T>& rhs) const;
    diagonalmatrix<T> operator *(const diagonalmatrix<T>& rhs) const;

    virtual T& operator ()(const int row, const int column);
    virtual const T& operator ()(const int row, const int column)const;

    virtual void setsize(const int size);
    virtual int getdimentions()const{return m_dimentions;};

  protected:
      virtual void read(istream& in);
      virtual void print(ostream& out) const;

  private:
    int m_dimentions;
    myVec<T> m_data;
    T zero;
};

#include "diagonalmatrix.hpp"

#endif
