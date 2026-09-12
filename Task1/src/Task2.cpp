#include "../include/Task2.h"

namespace miit::algebra
{
	Task2::Task2(Matrix& matrix, Generator& generator)
		: Exercise(matrix, generator)
	{
	}

	Matrix& Task2::Solve()
	{
		result = OurMatrix;

		std::size_t column = 0;

		while (column < result.columnsCount())
		{
			bool containsPositiveOdd = false;

			for (std::size_t row = 0; row < result.rowsCount(); ++row)
			{
				if (result(row, column) > 0 &&
					result(row, column) % 2 != 0)
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
