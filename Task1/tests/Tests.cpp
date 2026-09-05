#include <gtest/gtest.h>
#include <sstream>

#include "Matrix.h"
#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "ExerciseVariant7.h"

using namespace miit::algebra;


TEST(ConstantGeneratorTests, ReturnsSpecifiedValue)
{
	ConstantGenerator generator(7);

	EXPECT_EQ(generator.generate(), 7);
}


TEST(IStreamGeneratorTests, ReadsValueFromStream)
{
	std::istringstream input("12");
	IStreamGenerator generator(input);

	EXPECT_EQ(generator.generate(), 12);
}


TEST(MatrixTests, FillsMatrixWithGenerator)
{
	Matrix matrix(2, 2);
	ConstantGenerator generator(5);

	matrix.fill(generator);

	EXPECT_EQ(matrix(0, 0), 5);
	EXPECT_EQ(matrix(0, 1), 5);
	EXPECT_EQ(matrix(1, 0), 5);
	EXPECT_EQ(matrix(1, 1), 5);
}


TEST(MatrixTests, MultipliesMatrices)
{
	Matrix left(2, 3);
	Matrix right(3, 2);

	left(0, 0) = 1;
	left(0, 1) = 2;
	left(0, 2) = 3;
	left(1, 0) = 4;
	left(1, 1) = 5;
	left(1, 2) = 6;

	right(0, 0) = 7;
	right(0, 1) = 8;
	right(1, 0) = 9;
	right(1, 1) = 10;
	right(2, 0) = 11;
	right(2, 1) = 12;

	Matrix result = left * right;

	EXPECT_EQ(result(0, 0), 58);
	EXPECT_EQ(result(0, 1), 64);
	EXPECT_EQ(result(1, 0), 139);
	EXPECT_EQ(result(1, 1), 154);
}


TEST(ExerciseVariant7Tests, TaskOneReplacesMinimumInEachRowWithZero)
{
	Matrix matrix(3, 3);

	matrix(0, 0) = -1;
	matrix(0, 1) = 7;
	matrix(0, 2) = 2;

	matrix(1, 0) = 7;
	matrix(1, 1) = 6;
	matrix(1, 2) = -4;

	matrix(2, 0) = -10;
	matrix(2, 1) = -4;
	matrix(2, 2) = 3;

	ConstantGenerator generator(0);
	ExerciseVariant7 exercise(matrix, generator);

	Matrix& result = exercise.TaskOne();

	EXPECT_EQ(result(0, 0), 0);
	EXPECT_EQ(result(0, 1), 7);
	EXPECT_EQ(result(0, 2), 2);

	EXPECT_EQ(result(1, 0), 7);
	EXPECT_EQ(result(1, 1), 6);
	EXPECT_EQ(result(1, 2), 0);

	EXPECT_EQ(result(2, 0), 0);
	EXPECT_EQ(result(2, 1), -4);
	EXPECT_EQ(result(2, 2), 3);
}


TEST(ExerciseVariant7Tests, TaskTwoRemovesColumnsWithPositiveOddValues)
{
	Matrix matrix(2, 3);

	matrix(0, 0) = 2;
	matrix(1, 0) = 4;

	matrix(0, 1) = 1;
	matrix(1, 1) = 6;

	matrix(0, 2) = -3;
	matrix(1, 2) = 8;

	ConstantGenerator generator(0);
	ExerciseVariant7 exercise(matrix, generator);

	Matrix& result = exercise.TaskTwo();

	ASSERT_EQ(result.rowsCount(), 2);
	ASSERT_EQ(result.columnsCount(), 2);

	EXPECT_EQ(result(0, 0), 2);
	EXPECT_EQ(result(1, 0), 4);
	EXPECT_EQ(result(0, 1), -3);
	EXPECT_EQ(result(1, 1), 8);
}
