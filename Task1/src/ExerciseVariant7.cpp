#include "../include/ExerciseVariant7.h"
#include <cmath>

namespace miit::algebra
{
    bool isOddPositive(int value);

    ExerciseVariant7::ExerciseVariant7(Matrix& matrix, Generator& generator): Exercise(matrix, generator)
    {
    }

    Matrix& ExerciseVariant7::TaskOne()
    {
        TaskOneResult = OurMatrix;

        for (size_t i = 0; i < TaskOneResult.rowsCount(); i++)
        {
            if (TaskOneResult.columnsCount() == 0)
            {
                continue;
            }

            int minCol = 0;
            int minValue = TaskOneResult(i, 0);

            for (size_t j = 1; j < TaskOneResult.columnsCount(); j++)
            {
                if (TaskOneResult(i, j) < minValue)
                {
                    minValue = TaskOneResult(i, j);
                    minCol = static_cast<int>(j);
                }
            }

            TaskOneResult(i, minCol) = 0;
        }

        return TaskOneResult;
    }

    Matrix& ExerciseVariant7::TaskTwo()
    {
        TaskTwoResult = OurMatrix;

        for (int j = static_cast<int>(TaskTwoResult.columnsCount()) - 1;
            j >= 0;
            j--)
        {
            bool hasOddPositive = false;

            for (int i = 0;
                i < TaskTwoResult.rowsCount() && !hasOddPositive;
                i++)
            {
                if (isOddPositive(TaskTwoResult(i, j)))
                {
                    hasOddPositive = true;
                }
            }

            if (hasOddPositive)
            {
                TaskTwoResult.removeColumn(j);
            }
        }

        return TaskTwoResult;
    }

    bool isOddPositive(int value)
    {
        long long rounded = static_cast<long long>(std::llround(value));

        return value > 0 && (rounded % 2 != 0);
    }
}
