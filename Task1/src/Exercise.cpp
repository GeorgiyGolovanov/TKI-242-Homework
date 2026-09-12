#include "../include/Exercise.h"

namespace miit::algebra
{
	Exercise::Exercise(Matrix& matrix, Generator& generator)
		: OurMatrix(matrix), OurGenerator(generator)
	{
	}

	void Exercise::Fill()
	{
		OurMatrix.fill(OurGenerator);
	}
}
