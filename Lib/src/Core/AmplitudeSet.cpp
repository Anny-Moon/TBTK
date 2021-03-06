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

/** @file AmplitudeSet.cpp
 *
 *  @author Kristofer Björnson
 */

#include "AmplitudeSet.h"
#include "TBTKMacros.h"

using namespace std;

namespace TBTK{

AmplitudeSet::AmplitudeSet(){
	isConstructed = false;
	isSorted = false;
	numMatrixElements = -1;

	cooRowIndices = NULL;
	cooColIndices = NULL;
	cooValues = NULL;
}

AmplitudeSet::~AmplitudeSet(){
	if(cooRowIndices != NULL)
		delete [] cooRowIndices;
	if(cooColIndices != NULL)
		delete [] cooColIndices;
	if(cooValues != NULL)
		delete [] cooValues;
}

int AmplitudeSet::getNumMatrixElements() const{
	TBTKAssert(
		numMatrixElements != -1,
		"AmplitudeSet::getNumMatrixElements()",
		"COO format not constructed.",
		"Use Model::constructCOO() to construct COO format."
	);

	return numMatrixElements;
}

void AmplitudeSet::constructCOO(){
	TBTKAssert(
		isSorted,
		"AmplitudeSet::constructCOO()",
		"Amplitudes not sorted.",
		""
	);
	TBTKAssert(
		numMatrixElements == -1,
		"AmplitudeSet::constructCOO()",
		"Hamiltonain on COO format already constructed.",
		""
	);

	//Count number of matrix elements
	AmplitudeSet::Iterator it = getIterator();
	const HoppingAmplitude *ha;
	numMatrixElements = 0;
	int currentCol = -1;
	int currentRow = -1;
	while((ha = it.getHA())){
		int col = getBasisIndex(ha->fromIndex);
		int row = getBasisIndex(ha->toIndex);
		if(col > currentCol){
			currentCol = col;
			currentRow = -1;
		}
		if(row > currentRow){
			currentRow = row;
			numMatrixElements++;
		}

		it.searchNextHA();
	}

	cooRowIndices = new int[numMatrixElements];
	cooColIndices = new int[numMatrixElements];
	cooValues = new complex<double>[numMatrixElements];

	//Setup matrix on COO format
	it.reset();
	int currentMatrixElement = -1;
	currentCol = -1;
	currentRow = -1;
	while((ha = it.getHA())){
		int col = getBasisIndex(ha->fromIndex);
		int row = getBasisIndex(ha->toIndex);
		complex<double> amplitude = ha->getAmplitude();

		if(col > currentCol){
			currentCol = col;
			currentRow = -1;
		}
		if(row > currentRow){
			currentRow = row;
			currentMatrixElement++;

			//Note: The sorted AmplitudeSet is in ordered column
			//major order, while the COO format is in row major
			//order. The Hermitian conjugat eis therefore taken
			//here. (That is, conjugate and intercahnge of rows and
			// columns is intentional)
			cooRowIndices[currentMatrixElement] = col;
			cooColIndices[currentMatrixElement] = row;
			cooValues[currentMatrixElement] = conj(amplitude);
		}
		else{
			cooValues[currentMatrixElement] += conj(amplitude);
		}

		it.searchNextHA();
	}
}

void AmplitudeSet::destructCOO(){
	numMatrixElements = -1;
	if(cooRowIndices != NULL){
		delete [] cooRowIndices;
		cooRowIndices = NULL;
	}
	if(cooColIndices != NULL){
		delete [] cooColIndices;
		cooColIndices = NULL;
	}
	if(cooValues != NULL){
		delete [] cooValues;
		cooValues = NULL;
	}
}

void AmplitudeSet::reconstructCOO(){
	if(numMatrixElements != -1){
		destructCOO();
		constructCOO();
	}
}

void AmplitudeSet::print(){
	tree.print();
}

AmplitudeSet::Iterator AmplitudeSet::getIterator() const{
	return AmplitudeSet::Iterator(&tree);
}

AmplitudeSet::Iterator AmplitudeSet::getIterator(const Index &subspace) const{
	return AmplitudeSet::Iterator(tree.getSubTree(subspace));
}

AmplitudeSet::Iterator::Iterator(const TreeNode* tree){
	it = new TreeNode::Iterator(tree);
}

AmplitudeSet::Iterator::~Iterator(){
	delete it;
}

void AmplitudeSet::Iterator::reset(){
	it->reset();
}

void AmplitudeSet::Iterator::searchNextHA(){
	it->searchNextHA();
}

const HoppingAmplitude* AmplitudeSet::Iterator::getHA() const{
	return it->getHA();
}

void AmplitudeSet::tabulate(
	complex<double> **amplitudes,
	int **table,
	int *numHoppingAmplitudes,
	int *maxIndexSize
) const{
	Iterator it = getIterator();
	const HoppingAmplitude *ha;
	(*numHoppingAmplitudes) = 0;
	(*maxIndexSize) = 0;
	while((ha = it.getHA())){
		(*numHoppingAmplitudes)++;

		int indexSize = ha->fromIndex.size();
		if(indexSize > *maxIndexSize)
			(*maxIndexSize) = indexSize;

		it.searchNextHA();
	}

	int tableSize = (*numHoppingAmplitudes)*2*(*maxIndexSize);
	(*table) = new int[tableSize];
	for(int n = 0; n < tableSize; n++)
		(*table)[n] = -1;
	(*amplitudes) = new complex<double>[(*numHoppingAmplitudes)];

	it.reset();
	int counter = 0;
	while((ha = it.getHA())){
		for(unsigned int n = 0; n < ha->fromIndex.size(); n++)
			(*table)[2*(*maxIndexSize)*counter+n] = ha->fromIndex.at(n);
		for(unsigned int n = 0; n < ha->toIndex.size(); n++)
			(*table)[2*(*maxIndexSize)*counter+n+(*maxIndexSize)] = ha->toIndex.at(n);
		(*amplitudes)[counter] = ha->getAmplitude();

		it.searchNextHA();
		counter++;
	}
}

};	//End of namespace TBTK
