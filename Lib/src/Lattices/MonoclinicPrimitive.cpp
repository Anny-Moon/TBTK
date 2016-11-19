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

/** @file MonoclinicPrimitive.cpp
 *
 *  @author Kristofer Björnson
 */

#include "MonoclinicPrimitive.h"

#include <cmath>

using namespace std;

namespace TBTK{
namespace Lattices{

MonoclinicPrimitive::MonoclinicPrimitive(
	double side1Length,
	double side2Length,
	double angle12
){
	vector<vector<double>> latticeVectors;

	latticeVectors.push_back(vector<double>());
	latticeVectors.at(0).push_back(side1Length);
	latticeVectors.at(0).push_back(0.);

	latticeVectors.push_back(vector<double>());
	latticeVectors.at(1).push_back(side2Length*cos(angle12));
	latticeVectors.at(1).push_back(side2Length*sin(angle12));

	setLatticeVectors(latticeVectors);
}

MonoclinicPrimitive::~MonoclinicPrimitive(){
}

};	//End of namespace Lattices
};	//End of namespace TBTK
