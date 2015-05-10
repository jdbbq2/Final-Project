//////////////////////////////////////////////////////////////////////////////
// Programmer: Joshua Brewer and Dakota Ewigman           Date: 5-8-2015    //
// File: pde_holder.h                    section: a                         //
// Purpose: Contains struct to hold information relating to a pde           //
//////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
// Class: pde_solver                                          //
// Purpose: Description of class goes here                    //
////////////////////////////////////////////////////////////////

template <typename T>
struct pde_holder
{
  T lowerbound_x;
  T upperbound_x;
  T lowerbound_y;
  T upperbound_y;
  T(*left_boundary)(T);
  T(*upper_boundary)(T);
  T(*lower_boundary)(T);
  T(*right_boundary)(T);
  T(*forcing_funct)(T);
};