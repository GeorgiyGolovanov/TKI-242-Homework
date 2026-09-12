#include "../include/Task1.h"

namespace miit::algebra
{
	Task1::Task1(Matrix& matrix, Generator& generator)
		: Exercise(matrix, generator)
	{
	}

	Matrix& Task1::Solve()
	{
		result = OurMatrix;

		for (std::size_t i = 0; i < result.rowsCount(); ++i)
		{
			std::size_t minColumn = 0;

			for (std::size_t j = 1; j < result.columnsCount(); ++j)
			{
				if (result(i, j) < result(i, minColumn))
				{
					minColumn = j;
				}
			}

			result(i, minColumn) = 0;
		}

		return result;
	}
}
