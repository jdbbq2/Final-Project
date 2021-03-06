//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman   Date: 4-3-2015            //
// File: denseMatrix.h               section: a                             //
// Purpose: Contains function implementation for denseMatrix class          //
//////////////////////////////////////////////////////////////////////////////

#include "myvec.h"

#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

////////////////////////////////////////////////////////////////
// Class: denseMatrix                                          //
// Purpose: The denseMatrix class models a mathematical matrix.//
//          Matrix multiplication, multiplication by a scalar,//
//          and multiplication by a vector are all supported. //
//          Addition and subtraction between matrices is also //
//          available. The matrix can be solved using the     //
//          gaussian_solver functor. This matrix specifically //
//          represents a filled or nearly filled matrix,      //
//          hence dense. It takes no shortcuts and is less    //
//          efficient than an upper or lower matrix.          //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//Function:     denseMatrix();                                //
//              denseMatrix(const denseMatrix& cpy);          // 
//Precondition: cpy must be square matrix (NxN)               //
//Postcondition: an object of type denseMatrix is created     //
//               default size of 0 for dimentions             //
//Description: constructors for denseMatrix, copy constructor //
//             performs a deep cpy and calls setsize          //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//Function: ~denseMatrix()                                    // 
//Precondition: none                                          //
//Postcondition: the object is destroyed and the memory is    //
//               deallocated                                  //
//Description: destructor for denseMatrix                     //
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//Function:    denseMatrix<T>& operator =(const denseMatrix<T>& source);      //
//                                                                            //
//Precondition: source must be an nxn matrix                                  //
//Postcondition: the sizes and data are copied from source to the new matrix  //
//               a deep copy is performed for the dynamically allocated memory//
//Description: the normal assignment operator                                 //
//             empty source matrix (size 0) works without memory leaks        //
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Function:   denseMatrix<T> operator +(const denseMatrix<T>& rhs) const;    //
//            denseMatrix<T> operator +(const upperMatrix<T>& rhs) const;    //
//            denseMatrix<T> operator +(const lowerMatrix<T>& rhs) const;    //
//                                                                           //
//            denseMatrix<T> operator -(const denseMatrix<T>& rhs) const;    //
//            denseMatrix<T> operator -(const denseMatrix<T>& rhs) const;    //
//            denseMatrix<T> operator -(const upperMatrix<T>& rhs) const;    //
//            denseMatrix<T> operator -(const lowerMatrix<T>& rhs) const;    //
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
//Function:      denseMatrix<T> operator *(const T rhs) const;             //
//               myVec<T> operator *(const myVec<T>& rhs) const;           //
//               denseMatrix<T> operator *(const denseMatrix<T>& rhs) const;//
//                                                                         //
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

////////////////////////////////////////////////////////////////////////////////////
//Function:         myVec<T>& operator [](const int index);                       //
//      const myVec<T>& operator [] (const int index)const;                       //
//Precondition: The index used to access the elements are                         //
//               greater than -1, less than m_dimentions (inside matrix)          //
//Postcondition: A reference to the indexed vector is returned                    //
//               Note: this allows for [][] accessing individual elements by using//
//                     the vector bracket operator                                //
//Description: The normal index operator for retrieving vectors from a matrix     //
////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
//Function:     virtual T& operator ()(const int row, const int column);            //
//              virtual const T& operator ()(const int row, const int column)const; //
//Precondition: Same as above                                                       //
//Description: Same as above                                                        //
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

///////////////////////////////////////////////////////////////////
//Function:   void swap_rows(const int row1, const int row2);    //
//Precondition: row1 and row2 are inside the matrix (exception)  //
//Postcondition: the rows with the indices passed are swapped in //
//               the calling object                              //
//Description: the indices ascend as you go down the matrix and  //
//             start at 0, not 1                                 //
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//Function:     denseMatrix<T> transpose() const;                //
//Precondition: calling object should be nxn where n=m_dimentions//
//Postcondition: a temporary matrix is returned for which the    //
//               rows are the columns of the calling object and  //
//               vice versa                                      //
//Description: The transpose of the matrix is returned and the   //
//             calling object is not modified. The copy          //
//             is called passing the calling object.             //
///////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
//Functions: virtual void read(istream& in);                      //
//           virtual void print(ostream& out) const;              //
//Precondition: none                                              //
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
class denseMatrix;                       

template <typename T>
class upperMatrix;                       

template <typename T>
class lowerMatrix;                       


template <typename T>
class denseMatrix : public myMatrix<T>
{
  public:
    denseMatrix();
    denseMatrix(const denseMatrix& cpy);
    virtual ~denseMatrix();

    denseMatrix<T>& operator =(const denseMatrix<T>& rhs);

    denseMatrix<T> operator +(const denseMatrix<T>& rhs) const;
    denseMatrix<T> operator +(const upperMatrix<T>& rhs) const;
    denseMatrix<T> operator +(const lowerMatrix<T>& rhs) const;

    denseMatrix<T> operator -(const denseMatrix<T>& rhs) const;
    denseMatrix<T> operator -(const upperMatrix<T>& rhs) const;
    denseMatrix<T> operator -(const lowerMatrix<T>& rhs) const;

    denseMatrix<T> operator *(const T rhs) const;
    virtual myVec<T> operator *(const myVec<T>& rhs) const;

    denseMatrix<T> operator *(const denseMatrix<T>& rhs) const;

    myVec<T>& operator [](const int index){return m_data[index];};
    const myVec<T>& operator [] (const int index)const{return m_data[index];};

    virtual T& operator ()(const int row, const int column){return m_data[row][column];};
    virtual const T& operator ()(const int row, const int column)const{return m_data[row][column];};


    denseMatrix<T> transpose() const;

    virtual void setsize(const int size);
    virtual int getdimentions()const{return m_dimentions;};
    virtual void swap_rows(const int row1, const int row2);


  protected:
      virtual void read(istream& in);
      virtual void print(ostream& out) const;

  private:
    int m_dimentions;
    myVec<myVec<T> > m_data;
};

#include "densematrix.hpp"

#endif
