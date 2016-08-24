/** @file Dos.cpp
 *
 *  @author Kristofer Björnson
 */

#include "../include/Dos.h"

namespace TBTK{
namespace Property{

Dos::Dos(double lowerLimit, double upperLimit, int resolution){
	this->lowerLimit = lowerLimit;
	this->upperLimit = upperLimit;
	this->resolution = resolution;
	data = new double[resolution];
}

Dos::~Dos(){
	delete [] data;
}

};	//End of namespace Property
};	//End of namespace TBTK
