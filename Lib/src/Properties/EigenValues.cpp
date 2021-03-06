/* Copyright 2016 Kristofer Björnson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @file EigenValues.cpp
 *
 *  @author Kristofer Björnson
*/

#include "EigenValues.h"

namespace TBTK{
namespace Property{

EigenValues::EigenValues(int size){
	this->size = size;
	data = new double[size];
}

EigenValues::EigenValues(int size, const double *data){
	this->size = size;
	this->data = new double[size];
	for(int n = 0; n < size; n++)
		this->data[n] = data[n];
}

EigenValues::~EigenValues(){
	delete [] data;
}

};	//End of namespace Property
};	//End of namespace TBTK
