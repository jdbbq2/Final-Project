//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman           Date: 4-3-2015    //
// File: pde_solver.hpp                       section: a                    //
// Purpose: Contains function implementation for pde_solver class           //
//////////////////////////////////////////////////////////////////////////////

template <typename V>
void pde_solver<V>::operator() (myMatrix<V>& outmatrix, myVec<V>& outvector, const pde_holder<V>& the_pde)
{

  /*-------------VERIFYING PASSED PARAMETERS---------------*/
  cout << "GOT HERE" << endl;
  cout << "Don't forget to set matrix sizes" << endl;
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
//      for example, 1x10^-17 != 0 when it should be
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
  const int adder = -2;

  cout << "increment_x" << increment_x << endl;
  cout << "increment_y" << increment_y << endl;

  for (int i=0; i < dimentions; i++)
  {
    temp_location_x = location_x - increment_x;
    cout << "Look at: : (" << temp_location_x << "," << location_y << ")" << endl;
    if (temp_location_x == the_pde.lowerbound_x)
    {
      outvector[i] += the_pde.left_boundary(location_y);
    }
    else
    {
      cout << "CHANGING (" << i << "," <<((temp_location_x/increment_x) +(location_y/increment_y) + 2*((location_y/increment_y) +adder)) << ")" << endl;
      outmatrix(i,((temp_location_x/increment_x) +(location_y/increment_y) + 2*((location_y/increment_y) + adder))) = weight;
    }

    temp_location_x = location_x + increment_x;
    cout << "Look at: : (" << temp_location_x << "," << location_y << ")" << endl;
    if ((float)temp_location_x == (float)the_pde.upperbound_x) //float comparison for precision change
    {
      outvector[i] += the_pde.right_boundary(location_y);
    }
    else
    {
      cout << "CHANGING (" << i << "," <<((temp_location_x/increment_x) + (location_y/increment_y) + 2*((location_y/increment_y) +adder)) << ")" << endl;
      outmatrix(i,((temp_location_x/increment_x) +(location_y/increment_y) + 2*((location_y/increment_y) + adder))) = weight;
    }

    temp_location_y = location_y - increment_y;
    cout << "Look at: : (" << location_x << "," << temp_location_y << ")" << endl;
    if (temp_location_y == the_pde.lowerbound_y)
    {
      outvector[i] += the_pde.lower_boundary(location_x);
    }
    else
    {
      cout << "CHANGING (" << i << "," <<((location_x/increment_x) + (temp_location_y/increment_y) +2*((temp_location_y/increment_y) +adder)) << ")" << endl;
      outmatrix(i,((location_x/increment_x) +(temp_location_y/increment_y) + 2*((temp_location_y/increment_y) +adder))) = weight;
    }

    temp_location_y = location_y + increment_y;
    cout << "Look at: : (" << location_x << "," << temp_location_y << ")" << endl;
    cout << endl << endl;

    if ((float)temp_location_y == (float)the_pde.upperbound_y)
    {
      outvector[i] += the_pde.upper_boundary(location_x);
    }
    else
    {
      cout << "CHANGING (" << i << "," <<((location_x/increment_x) + (temp_location_y/increment_y)+(2*((temp_location_y/increment_y) +adder))) << ")" << endl;
      outmatrix(i,((location_x/increment_x) +(temp_location_y/increment_y)+ 2*((temp_location_y/increment_y) +adder))) = weight;
    }

    //THIS IS WHERE THE FORCING FUNCTION WILL GO

    location_x = location_x + increment_x;
    if ((float)location_x == (float)the_pde.upperbound_x)
    {
      location_x = increment_x;
      location_y = location_y+increment_y;
    }
  }
 
  cout << "THE MATRIX : " <<endl<< outmatrix << endl;
  for (int i=0; i < dimentions; i++)
  {
    outvector[i] /= 4;
  }
  cout << "THE VECTOR : " << outvector << endl;
	return;
}