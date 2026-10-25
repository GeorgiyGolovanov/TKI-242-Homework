#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>

#include "Matrix.h"
#include "ConstantGenerator.h"
#include "ZeroGenerator.h"
#include "IStreamGenerator.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

TEST(ConstantGeneratorTests, ReturnsSpecifiedValue)
{
	const ConstantGenerator generator(7);

	EXPECT_EQ(generator.generate(), 7);
	EXPECT_EQ(generator.generate(), 7);
}

TEST(ZeroGeneratorTests, ReturnsZero)
{
	const ZeroGenerator generator;

	EXPECT_EQ(generator.generate(), 0);
}

TEST(IStreamGeneratorTests, ReadsValuesFromStream)
{
	std::istringstream input("12 -5");
	const IStreamGenerator generator(input);

	EXPECT_EQ(generator.generate(), 12);
	EXPECT_EQ(generator.generate(), -5);
}

TEST(RandomGeneratorTests, GeneratesValuesInsideRange)
{
	const RandomGenerator generator(1, 10);

	for (size_t i = 0; i < 50; i++)
	{
		const int value = generator.generate();

		EXPECT_GE(value, 1);
		EXPECT_LE(value, 10);
	}
}

TEST(MatrixTests, DefaultConstructorCreatesEmptyMatrix)
{
	const Matrix matrix;

	EXPECT_EQ(matrix.rowsCount(), static_cast<size_t>(0));
	EXPECT_EQ(matrix.columnsCount(), static_cast<size_t>(0));
}

TEST(MatrixTests, ConstructorSetsSizeAndFillsWithZeroes)
{
	const Matrix matrix(2, 3);

	EXPECT_EQ(matrix.rowsCount(), static_cast<size_t>(2));
	EXPECT_EQ(matrix.columnsCount(), static_cast<size_t>(3));
	EXPECT_EQ(matrix(0, 0), 0);
	EXPECT_EQ(matrix(1, 2), 0);
}

TEST(MatrixTests, ConstructorThrowsOnWrongSize)
{
	EXPECT_THROW(Matrix(0, 3), std::invalid_argument);
	EXPECT_THROW(Matrix(-1, 2), std::invalid_argument);
}

TEST(MatrixTests, CopyConstructorCreatesIndependentCopy)
{
	Matrix matrix(1, 2);
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;

	Matrix copy(matrix);
	copy(0, 0) = 100;

	EXPECT_EQ(matrix(0, 0), 1);
	EXPECT_EQ(copy(0, 1), 2);
}

TEST(MatrixTests, AssignmentCopiesValues)
{
	Matrix matrix(1, 2);
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;

	Matrix copy;
	copy = matrix;

	EXPECT_EQ(copy(0, 0), 1);
	EXPECT_EQ(copy(0, 1), 2);
}

TEST(MatrixTests, ComparesMatrices)
{
	Matrix left(1, 2);
	left(0, 0) = 1;
	left(0, 1) = 2;

	Matrix right(1, 2);
	right(0, 0) = 1;
	right(0, 1) = 2;

	EXPECT_TRUE(left == right);

	right(0, 1) = 3;

	EXPECT_TRUE(left != right);
}

TEST(MatrixTests, IndexOperatorThrowsWhenOutOfRange)
{
	Matrix matrix(2, 2);

	EXPECT_THROW(matrix(2, 0), std::invalid_argument);
	EXPECT_THROW(matrix(0, 2), std::invalid_argument);
}

TEST(MatrixTests, AddsMatrices)
{
	Matrix left(1, 2);
	left(0, 0) = 1;
	left(0, 1) = 2;

	Matrix right(1, 2);
	right(0, 0) = 3;
	right(0, 1) = 4;

	Matrix result = left + right;

	EXPECT_EQ(result(0, 0), 4);
	EXPECT_EQ(result(0, 1), 6);
}

TEST(MatrixTests, SubtractsMatrices)
{
	Matrix left(1, 2);
	left(0, 0) = 5;
	left(0, 1) = 7;

	Matrix right(1, 2);
	right(0, 0) = 1;
	right(0, 1) = 2;

	Matrix result = left - right;

	EXPECT_EQ(result(0, 0), 4);
	EXPECT_EQ(result(0, 1), 5);
}

TEST(MatrixTests, AdditionThrowsOnDifferentSizes)
{
	Matrix left(2, 2);
	Matrix right(2, 3);

	EXPECT_THROW(left + right, std::invalid_argument);
}

TEST(MatrixTests, MultipliesMatrices)
{
	Matrix left(2, 3);
	left(0, 0) = 1;
	left(0, 1) = 2;
	left(0, 2) = 3;
	left(1, 0) = 4;
	left(1, 1) = 5;
	left(1, 2) = 6;

	Matrix right(3, 2);
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

TEST(MatrixTests, MultiplicationThrowsOnWrongSizes)
{
	Matrix left(2, 3);
	Matrix right(2, 3);

	EXPECT_THROW(left * right, std::invalid_argument);
}

TEST(MatrixTests, FindsMinimumAndMaximum)
{
	Matrix matrix(2, 2);
	matrix(0, 0) = -7;
	matrix(0, 1) = 2;
	matrix(1, 0) = 3;
	matrix(1, 1) = 9;

	EXPECT_EQ(matrix.minimum(), -7);
	EXPECT_EQ(matrix.maximum(), 9);
}

TEST(MatrixTests, MinimumThrowsOnEmptyMatrix)
{
	const Matrix matrix;

	EXPECT_THROW(matrix.minimum(), std::invalid_argument);
	EXPECT_THROW(matrix.maximum(), std::invalid_argument);
}

TEST(MatrixTests, FillsMatrixWithGenerator)
{
	Matrix matrix(2, 2);
	const ConstantGenerator generator(5);

	matrix.fill(generator);

	EXPECT_EQ(matrix(0, 0), 5);
	EXPECT_EQ(matrix(0, 1), 5);
	EXPECT_EQ(matrix(1, 0), 5);
	EXPECT_EQ(matrix(1, 1), 5);
}

TEST(MatrixTests, RemovesColumn)
{
	Matrix matrix(1, 3);
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;
	matrix(0, 2) = 3;

	matrix.removeColumn(1);

	EXPECT_EQ(matrix.columnsCount(), static_cast<size_t>(2));
	EXPECT_EQ(matrix(0, 0), 1);
	EXPECT_EQ(matrix(0, 1), 3);
}

TEST(MatrixTests, RemoveColumnThrowsOnWrongIndex)
{
	Matrix matrix(2, 2);

	EXPECT_THROW(matrix.removeColumn(2), std::invalid_argument);
}

TEST(MatrixTests, WritesMatrixToStream)
{
	Matrix matrix(2, 2);
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;
	matrix(1, 0) = 3;
	matrix(1, 1) = 4;

	std::ostringstream output;
	output << matrix;

	EXPECT_EQ(output.str(), "1\t2\n3\t4\n");
}

TEST(MatrixTests, ReadsMatrixFromStream)
{
	Matrix matrix(1, 2);
	std::istringstream input("8 9");

	input >> matrix;

	EXPECT_EQ(matrix(0, 0), 8);
	EXPECT_EQ(matrix(0, 1), 9);
}

TEST(Task1Tests, ReplacesMinimumInEachRowWithZero)
{
	Matrix matrix(2, 3);
	matrix(0, 0) = -1;
	matrix(0, 1) = 7;
	matrix(0, 2) = 2;
	matrix(1, 0) = 7;
	matrix(1, 1) = 6;
	matrix(1, 2) = -4;

	const ConstantGenerator generator(0);
	Task1 task(matrix, generator);

	Matrix& result = task.Solve();

	EXPECT_EQ(result(0, 0), 0);
	EXPECT_EQ(result(0, 1), 7);
	EXPECT_EQ(result(0, 2), 2);
	EXPECT_EQ(result(1, 0), 7);
	EXPECT_EQ(result(1, 1), 6);
	EXPECT_EQ(result(1, 2), 0);
}

TEST(Task2Tests, RemovesColumnsWithPositiveOddValues)
{
	Matrix matrix(2, 3);
	matrix(0, 0) = 2;
	matrix(1, 0) = 4;
	matrix(0, 1) = 1;
	matrix(1, 1) = 6;
	matrix(0, 2) = -3;
	matrix(1, 2) = 8;

	const ConstantGenerator generator(0);
	Task2 task(matrix, generator);

	Matrix& result = task.Solve();

	EXPECT_EQ(result.columnsCount(), static_cast<size_t>(2));
	EXPECT_EQ(result(0, 0), 2);
	EXPECT_EQ(result(1, 0), 4);
	EXPECT_EQ(result(0, 1), -3);
	EXPECT_EQ(result(1, 1), 8);
}

TEST(ExerciseTests, FillUsesGenerator)
{
	Matrix matrix(1, 2);
	const ConstantGenerator generator(8);

	Task1 task(matrix, generator);
	task.Fill();

	EXPECT_EQ(matrix(0, 0), 8);
	EXPECT_EQ(matrix(0, 1), 8);
}
