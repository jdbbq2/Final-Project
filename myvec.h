//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman  Date: 4-3-2015             //
// File: myVec.hpp             section: a                                   //
// Purpose: Contains function prototypes for myVec class                    //
//////////////////////////////////////////////////////////////////////////////

#ifndef MYVEC_H
#define MYVEC_H

#include <iostream>
#include <stdexcept>

////////////////////////////////////////////////////////////////
// Class: myVec                                               //
// Purpose: This is a basic vector class that uses            //
//          dynamically allocated memory to handle the        //
//          objects stored inside                             //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//Function:     myVec(const int size);                        //
//              myVec(): m_size(0), m_data(NULL) {};          //
//              myVec(const myVec& cpy);                      // 
//Precondition: none                                          //
//Postcondition: an object of type myVec is created           //
//               default size of zero with a null pointer     //
//Description: constructors for myVec, size constructor       //
//             contains junk, copy constructor performs       //
//             deep copy                                      //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//Function: ~myVec()                                          // 
//Precondition: none                                          //
//Postcondition: the object is destroyed and the memory is    //
//               deallocated                                  //
//Description: destructor for myVec                           //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
//Function: friend ostream& operator<<                            //
//          (ostream& out, const myVec<T>& vec)                   //
//          friend istream& operator>>                            //
//         (istream& in, myVec<T>& vec)                           // 
//Precondition: objects put in instream are of type T, there are  //
//               exactly the number of elements to be read in as  //
//               the size of the myVec object, and are            //
//               separated by whitespace                          //
//Postcondition: array information is input/output from/to stream //
//Description: Stream operators for myVec                         //
//  output format - [ comma delimited elements]                   //
//  input format - # # # (delimiting characters between elements) //
//  Type of objects are not checked                               //
////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//Function:     T& operator[](const int i);  read and write                //
//             const T& operator[](const int i) const;  read only version  //
//Precondition: index is not out of bounds                                 //
//Postcondition: A reference to the indexed element is returned, if the    //
//               index is out of bounds a message is sent to cerr and the  //
//               error object is returned                                  /////
//Description: The normal index operator for retrieving elements from an array//
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//Function:   int getsize() const{return m_size;};                      //
//            void setsize(const int size);                             //
//Precondition: none                                                    //
//                                                                      //
//Postcondition: the size of the myVec is returned or set               //
//               if the size set is smaller than the current size       //
//               then the lower-most elements will be preserved         //
//               setting the size larger gives junk until initialized   //
//Description: getsize is a standard accessor for size of array,        //
//             setsize resizes underlying array without memory leaks    //
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Function:    myVec<T>& operator =(const myVec<T>& source);                  //
//                                                                            //
//Precondition: not the same vector (alias test is performed but nothing is   //
//                                   done if they are the same)               //
//Postcondition: the sizes and data are copied from source to the new vector  //
//               a deep copy is performed for the dynamically allocated array //
//Description: the normal assignment operator                                 //
//             empty source vector (size 0) works without memory leaks        //
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Function:    myVec<T> operator +(const myVec<T>& rhs) const;               //
//             myVec<T> operator -(const myVec<T>& rhs) const;               //
//             myVec<T> operator -() const;                                  //
//             myVec<T> operator /(const myVec<T>& rhs) const;               //
//             bool operator ==(const myVec<T>& rhs) const;                  //
//                                                                           //
//Precondition: the corresponding operator MUST be defined for type T        //
//              (+=, -, /, etc)                                              //
//                                                                           //
//Postcondition: each operation is performed on all elements and a temp      //
//               vector with the results is returned                         //
//               (except ==, a bool is returned)                             //
//Description: None of these operations change the passed objects, they      //
//        return a temporary vector containing the results or a bool.        //
//        the operations are performed on each element in succession         //
//        note: the division operator is an element-wise divide              //
//              used to check if one vector is a multiple of the other       //
//        the dot product and multiplication by scalar are next              //
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//Function:   T operator *(const myVec<T>& rhs) const;                     //
//            myVec<T> operator *(const T& rhs) const;                     //
//                                                                         //
//Precondition: 0 MUST be a defined value for T                            //
//              * (multiplication) must be defined for two T objects       //
//              + (addition) must be defined for two T objects             //
//Postcondition: The dot product (sum of products of elements) is returned //
//               as a T object for two vectors.                            //
//               A temp vector with the results of multiplying rhs to each //
//               element is returned if rhs is of type T (not vector)      //
//Description: Invalid size dot product is handled with a message only     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

// --------------- Forward Declarations 
template <typename T>
class myVec;                       

template <typename T>                 // a friend function for output
std::ostream& operator<< (std::ostream& out, const myVec<T>& vec);

template <typename T>                 // a friend function for input
std::istream& operator>> (std::istream& in, myVec<T>& vec);

template<typename T>
class myVec
{
  public:
    myVec(const int size);
    myVec(): m_size(0), m_data(NULL) {};
    myVec(const myVec& cpy);
    ~myVec();

    /*ACCESSORS*/
    T& operator[](const int i); // read and write
    const T& operator[](const int i) const; // read only version

    int getsize() const{return m_size;};
    void setsize(const int size);

    /*OPERATORS*/
    myVec<T>& operator =(const myVec<T>& source);
    myVec<T> operator +(const myVec<T>& rhs) const;
    myVec<T> operator -(const myVec<T>& rhs) const;
    myVec<T> operator -() const;
    myVec<T> operator /(const myVec<T>& rhs) const;
    myVec<T> operator /(const T& rhs) const;
    T operator *(const myVec<T>& rhs) const;
    myVec<T> operator *(const T& rhs) const;
    bool operator ==(const myVec<T>& rhs) const;

        // Purpose: prints the myVec
    friend std::ostream& operator<< <> (std::ostream& out, 
                                        const myVec<T>& vec);
        // Purpose: reads in the myVec
    friend std::istream& operator>> <> (std::istream& in, 
                                        myVec<T>& vec);
  private:
    int m_size;
    T* m_data;
};

#include "myvec.hpp"

#endif
