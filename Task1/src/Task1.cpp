#include "../include/Task1.h"

namespace miit::algebra
{
	Task1::Task1(Matrix& matrix, const Generator& generator)
		: Exercise(matrix, generator)
	{
	}

	Matrix& Task1::Solve()
	{
		result = OurMatrix;

		for (size_t i = 0; i < static_cast<size_t>(result.rowsCount()); ++i)
		{
			size_t minColumn = 0;

			for (size_t j = 1; j < static_cast<size_t>(result.columnsCount()); ++j)
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
