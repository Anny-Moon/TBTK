/** @package TBTKcalc
 *  @file PropertyExtractorChebyshev.h
 *  @brief Extracts physical properties from the ChebyshevSolver
 *
 *  @author Kristofer Björnson
 */

#ifndef COM_DAFER45_TBTK_PROPERTY_EXTRACTOR_CHEBYSHEV
#define COM_DAFER45_TBTK_PROPERTY_EXTRACTOR_CHEBYSHEV

#include "ChebyshevSolver.h"

/** Experimental class for extracting properties from a ChebyshevSolver. */
class PropertyExtractorChebyshev{
public:
	/** Constructor. */
	PropertyExtractorChebyshev(ChebyshevSolver *cSolver,
					int numCoefficients,
					int energyResolution,
					bool useGPUToCalculateCoefficients,
					bool useGPUToGenerateGreensFunctions,
					bool useLookupTable = true);

	/** Destructor. */
	~PropertyExtractorChebyshev();

	/** Calculate Green's function. */
	std::complex<double>* calculateGreensFunction(Index to, Index from);

	/** Calculate Green's function for a range of 'to'-indices. */
	std::complex<double>* calculateGreensFunctions(std::vector<Index> &to, Index from);

	/** !!!Not tested!!!. Calculate local density of states. */
	double *calculateLDOS(Index pattern, Index ranges);
private:
	/** ChebyshevSolver to work on. */
	ChebyshevSolver *cSolver;

	/** Number of Chebyshev coefficients used in the expansion. */
	int numCoefficients;

	/** Energy resolution of the Green's function. */
	int energyResolution;

	/** Flag indicating whether a lookup table is used or not. */
	bool useLookupTable;

	/** Flag indicating whether the GPU should be used to calculate
	 *  Chebyshev coefficients. */
	bool useGPUToCalculateCoefficients;

	/** Flag indicating whether the GPU should be used to generate Green's
	 *  functions. */
	bool useGPUToGenerateGreensFunctions;

	/** Loops over range indices and calls the appropriate callback
	 *  function to calculate the correct quantity. */
	void calculate(void (*callback)(PropertyExtractorChebyshev *cb_this, void *memory, const Index &index, int offset),
			void *memory, Index pattern, const Index &ranges, int currentOffset, int offsetMultiplier);

	/** !!!Not tested!!! Callback for calculating local density of states.
	 *  Used by calculateLDOS. */
	static void calculateLDOSCallback(PropertyExtractorChebyshev *cb_this, void *ldos, const Index &index, int offset);

	/** Hint used to pass information between calculate[Property] and
	 * calculate[Property]Callback. */
	void *hint;
};

#endif
