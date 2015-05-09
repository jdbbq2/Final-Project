//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman           Date: 4-3-2015    //
// File: pde_solver.hpp                       section: a                    //
// Purpose: Contains function implementation for pde_solver class           //
//////////////////////////////////////////////////////////////////////////////

template <typename V>
void pde_solver<V>::operator() (const myMatrix<V>& inmatrix, const myVec<V>& invector,
                      myMatrix<V>& outmatrix, myVec<V>& outvector, const pde_holder<V>& the_pde)
{

  /*-------------VERIFYING PASSED PARAMETERS---------------*/
  cout << "GOT HERE" << endl;
  cout << "Don't forget to set matrix sizes" << endl;
  cout << "PASSED MATRIX: " << endl << inmatrix << endl;
  cout << "PASSED VECTOR: " << endl << invector << endl;
  cout << "lower_boundary (cos(pi)): " << the_pde.lower_boundary(3.14) << endl;
  cout << "upper_boundary (cos(pi)): " << the_pde.upper_boundary(3.14) << endl;
  cout << "left_boundary (cos(pi)): " << the_pde.left_boundary(3.14) << endl;
  cout << "right_boundary (cos(pi)): " << the_pde.right_boundary(3.14) << endl;

  if(the_pde.lower_boundary == 0 ||
     the_pde.upper_boundary == 0 ||
     the_pde.left_boundary == 0  ||
     the_pde.right_boundary == 0)
  {
    throw invalid_argument("Invalid (NULL) functions");
  }

  int dimentions = inmatrix.getdimentions();
  if (dimentions != invector.getsize())
    throw invalid_argument("matrix size does not match vector size");

  if(dimentions != outmatrix.getdimentions())
  {
    outmatrix.setsize(dimentions);
  }
  if(dimentions != outvector.getsize())
  {
    outvector.setsize(dimentions);
  }
//NOTE: outmatrix and outvector are uninitialized at this point


/*--------------ROUND OFF PROBLEMS----------------*/

//  if(the_pde.lower_boundary(the_pde.lowerbound_x) != the_pde.left_boundary(the_pde.lowerbound_y)  ||
//    the_pde.upper_boundary(the_pde.lowerbound_x) != the_pde.left_boundary(the_pde.upperbound_y) ||
//    the_pde.upper_boundary(the_pde.upperbound_x) != the_pde.right_boundary(the_pde.upperbound_y) ||
//    the_pde.lower_boundary(the_pde.upperbound_x) != the_pde.right_boundary(the_pde.lowerbound_y))
//  {
//    cout << the_pde.lower_boundary(the_pde.upperbound_x) << endl;
//    cout << the_pde.right_boundary(the_pde.lowerbound_y) << endl;
//    throw invalid_argument("Invalid (inconsistent) functions");
//  }

/*--------------GENERATE MATRIX----------------*/

  for (int i=0; i < dimentions; i++)
  {
    
  }

	return;
}