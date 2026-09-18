#include "../include/Exercise.h"

namespace miit::algebra
{
	Exercise::Exercise(Matrix& matrix, const Generator& generator)
		: OurMatrix(matrix), OurGenerator(generator)
	{
	}

	void Exercise::Fill()
	{
		OurMatrix.fill(OurGenerator);
	}
}
