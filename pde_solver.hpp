//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman           Date: 4-3-2015    //
// File: pde_solver.hpp                       section: a                    //
// Purpose: Contains function implementation for pde_solver class           //
//////////////////////////////////////////////////////////////////////////////

template <typename V>
void pde_solver<V>::operator() (myMatrix<V>& outmatrix, myVec<V>& outvector, const pde_holder<V>& the_pde)
{

  if(the_pde.lower_boundary == 0 ||
     the_pde.upper_boundary == 0 ||
     the_pde.left_boundary == 0  ||
     the_pde.right_boundary == 0)
  {
    throw invalid_argument("Invalid (NULL) functions");
  }

  int dimentions = outmatrix.getdimentions();
  if (dimentions == 0)
    throw invalid_argument("matrix size represents number of points");

  if(dimentions != outvector.getsize())
  {
    outvector.setsize(dimentions);
  }
//NOTE: outmatrix and outvector may be uninitialized at this point


/*--------------check for corners----------------*/

//NOTE: int comparisons are done to avoid round off problems
//      for example, 1x10^-17 not evaluated as equal to 0 when it should be
  if((int)the_pde.lower_boundary(the_pde.lowerbound_x) != (int)the_pde.left_boundary(the_pde.lowerbound_y)  ||
    (int)the_pde.upper_boundary(the_pde.lowerbound_x) != (int)the_pde.left_boundary(the_pde.upperbound_y) ||
    (int)the_pde.upper_boundary(the_pde.upperbound_x) != (int)the_pde.right_boundary(the_pde.upperbound_y) ||
    (int)the_pde.lower_boundary(the_pde.upperbound_x) != (int)the_pde.right_boundary(the_pde.lowerbound_y))
  {
    throw invalid_argument("Invalid (inconsistent) functions");
  }

/*--------------GENERATE MATRIX----------------*/
  float increment_x = the_pde.upperbound_x/(sqrt(dimentions)+1);
  float increment_y = the_pde.upperbound_y/(sqrt(dimentions)+1);
  float location_x = increment_x;
  float location_y = increment_y;
  float temp_location_x = location_x;
  float temp_location_y = location_y;

  float const weight = -0.25;

  //zero out matrix
  for (int i=0; i < dimentions; i++) //rows
  {

    for (int j=0; j < dimentions; j++) //columns
    {
      if(i==j)
      {
        outmatrix(i,j) = 1;
      }
      else
      {
        outmatrix(i,j) = 0;
      }
    }
  }
  const int mult = sqrt(dimentions);
  const int addr = mult+1;

//  cout << "increment_y" << increment_y << endl;
//  cout << "increment_x" << increment_x << endl;

  for (int i=0; i < dimentions; i++)
  {
    temp_location_x = location_x - increment_x;
//    cout << "Look at: : (" << temp_location_x << "," << location_y << ")" << endl;
    if (temp_location_x == the_pde.lowerbound_x)
    {
      outvector[i] += the_pde.left_boundary(location_y);
    }
    else
    {
//      cout << "CHANGING (" << i << "," <<((temp_location_x/increment_x) + (location_y/increment_y)-addr) << ")" << endl;
      outmatrix(i,((temp_location_x/increment_x) + mult*(location_y/increment_y))-addr) = weight;
    }

    temp_location_x = location_x + increment_x;
//    cout << "Look at: : (" << temp_location_x << "," << location_y << ")" << endl;
    if ((int)temp_location_x == (int)the_pde.upperbound_x) //int comparison for precision change
    {
      outvector[i] += the_pde.right_boundary(location_y);
    }
    else
    {
//      cout << "CHANGING (" << i << "," <<((temp_location_x/increment_x)  + mult*(location_y/increment_y)-addr) << ")" << endl;
      outmatrix(i,((temp_location_x/increment_x) + mult*(location_y/increment_y ))-addr) = weight;
    }

    temp_location_y = location_y - increment_y;
//    cout << "Look at: : (" << location_x << "," << temp_location_y << ")" << endl;
    if (temp_location_y == the_pde.lowerbound_y)
    {
      outvector[i] += the_pde.lower_boundary(location_x);
    }
    else
    {
//      cout << "CHANGING (" << i << "," <<((location_x/increment_x) + mult*(temp_location_y/increment_y)-addr) << ")" << endl;
      outmatrix(i,((location_x/increment_x) + mult*(temp_location_y/increment_y))-addr) = weight;
    }

    temp_location_y = location_y + increment_y;
//    cout << "Look at: : (" << location_x << "," << temp_location_y << ")" << endl;
//    cout << endl << endl;

    if ((int)temp_location_y == (int)the_pde.upperbound_y)
    {
      outvector[i] += the_pde.upper_boundary(location_x);
    }
    else
    {
//      cout << "CHANGING (" << i << "," <<((location_x/increment_x) + mult*(temp_location_y/increment_y)-addr) << ")" << endl;
      outmatrix(i,((location_x/increment_x) +mult*(temp_location_y/increment_y))-addr) = weight;
    }

//    cout << endl << endl << i << endl << endl;
    location_x = location_x + increment_x;
    if ((int)location_x == (int)the_pde.upperbound_x)
    {
//      cout << "TURNED " << endl;
      location_x = increment_x;
      location_y = location_y+increment_y;
    }
  }
 
  cout << "Post pde_solver matrix: " <<endl<< outmatrix << endl;
  for (int i=0; i < dimentions; i++)
  {
    outvector[i] /= 4;
    outvector[i] += ((increment_x*increment_x)/4)*the_pde.forcing_funct(increment_x);
    //forcing funct
  }
  cout << "Post pde_solver vector: " << outvector << endl;
	return;
}