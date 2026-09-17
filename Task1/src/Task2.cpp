#include "../include/Task2.h"

namespace miit::algebra
{
	Task2::Task2(Matrix& matrix, const Generator& generator)
		: Exercise(matrix, generator)
	{
	}

	Matrix& Task2::Solve()
	{
		result = OurMatrix;

		size_t column = 0;

		while (column < result.columnsCount())
		{
			bool containsPositiveOdd = false;

			for (int row = 0; row < static_cast<int>(result.rowsCount()); ++row)
			{
				const int value = result(row, static_cast<int>(column));

				if (value > 0 && value % 2 != 0)
				{
					containsPositiveOdd = true;
					break;
				}
			}

			if (containsPositiveOdd)
			{
				result.removeColumn(column);
			}
			else
			{
				++column;
			}
		}

		return result;
	}
}
