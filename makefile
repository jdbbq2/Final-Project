###############################################################################
## -->Makefile<--
###############################################################################

###############################################################################
##
## Instructor :  Clayton Price
## Class      :  CS328/CS5201 Spring 2015
## Assignment :  2
## Programmer :  Joshua Brewer and Dakota Ewigman
## Date       :  3-16-2015
## Filename   :  makefile
##
###############################################################################

###############################################################################
## This makefile is used to build or clean the files for assignment 1 example 2
###############################################################################

# Generic GNU g++ compiler flags
CXX = /usr/bin/g++
CXXFLAGS = -g -std=c++11

OBJECTS =  driver.o   
             
.SUFFIXES: .cpp
                                                         
.cpp.o: $<
	${CXX} -c ${CXXFLAGS} $< -o $@

default: all

all: driver

driver: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@
    
clean:
	rm -f *.o core driver > /dev/null 2>&1
                
# Dependency lists for the various source files
driver.o: driver.cpp \
					myvec.h \
					myvec.hpp \
					gaussian_solver.h \
					gaussian_solver.hpp \
					mymatrix.h \
					densematrix.h \
					densematrix.hpp \
					uppermatrix.h \
					uppermatrix.hpp \
					lowermatrix.h \
					lowermatrix.hpp \
					diagonalmatrix.h \
					diagonalmatrix.hpp \
					symmetricmatrix.h \
					symmetricmatrix.hpp \
					tridiagonalmatrix.h \
					tridiagonalmatrix.hpp\
					pde_holder.h \
					pde_solver.h\
					pde_solver.hpp\
