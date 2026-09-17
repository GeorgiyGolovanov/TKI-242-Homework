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

		for (int i = 0; i < static_cast<int>(result.rowsCount()); ++i)
		{
			int minColumn = 0;

			for (int j = 1; j < static_cast<int>(result.columnsCount()); ++j)
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
