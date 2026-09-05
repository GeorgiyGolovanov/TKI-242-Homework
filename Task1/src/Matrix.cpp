#include "../include/Matrix.h"
#include <algorithm>
#include <cmath>

namespace miit::algebra
{
	void Matrix::ERROR(const std::string& text) const
	{
		throw std::invalid_argument(text);
	}

	void Matrix::MEMORY(int** data) const
	{
		for (size_t i = 0; i < rows; i++) {
			if (data[i] == nullptr)
			{
				throw std::invalid_argument("Ошибка выделения памяти");
			}
		}

		if (data == nullptr)
		{
			throw std::invalid_argument("Ошибка выделения памяти");
		}
	}

	Matrix::Matrix() : data(nullptr), rows(0), columns(0) {};

	Matrix::Matrix(const int rows, const int columns) : rows(rows), columns(columns)
	{
		if (rows <= 0 || columns <= 0)
		{
			ERROR("Неверные размеры матрицы");
		}

		data = new int* [rows];

		for (size_t i = 0; i < rows; i++)
		{
			data[i] = new int[columns]();
		}

		MEMORY(data);
	}

	Matrix::Matrix(const Matrix& elements): rows(elements.rows), columns(elements.columns), data(nullptr)
	{
		data = new int* [rows];

		for (size_t i = 0; i < rows; i++)
		{
			data[i] = new int[columns];
		}

		MEMORY(data);

		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				data[i][j] = elements.data[i][j];
			}
		}
	}

	Matrix::Matrix(Matrix&& other): data(other.data),rows(other.rows),columns(other.columns)
	{
		other.data = nullptr;
		other.rows = 0;
		other.columns = 0;
	}

	Matrix::~Matrix()
	{
		for (size_t i = 0; i < rows; i++) {
			delete[] data[i];
		}
		delete[] data;
	}

	bool Matrix::operator == (const Matrix& other) const
	{
		if (rows != other.rows || columns != other.columns)
		{
			return false;
		}
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < rows; j++)
			{
				if (data[i][j] != other.data[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	bool Matrix::operator != (const Matrix& other) const
	{
		return !(*this == other);
	}

	Matrix& Matrix::operator=(const Matrix& other)
	{
		if (this != &other)
		{
			for (size_t i = 0; i < rows; i++)
			{
				delete[] data[i];
			}
			delete[] data;

			rows = other.rows;
			columns = other.columns;

			if (rows == 0 || columns == 0)
			{
				data = nullptr;
				return *this;
			}

			data = new int* [rows];

			for (size_t i = 0; i < rows; i++)
			{
				data[i] = new int[columns];
			}

			for (size_t i = 0; i < rows; i++)
			{
				for (size_t j = 0; j < columns; j++)
				{
					data[i][j] = other.data[i][j];
				}
			}
		}

		return *this;
	}

	Matrix& Matrix::operator = (Matrix&& other) 
	{
		if (this == &other)
		{
			return *this;
		}

		for (size_t i = 0; i < rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;

		data = other.data;
		rows = other.rows;
		columns = other.columns;

		other.data = nullptr;
		other.rows = 0;
		other.columns = 0;

		return *this;
	}

	int& Matrix::operator()(int rows, int columns)
	{
		if (rows < 0)
			rows = this->rows + rows;

		if (columns < 0)
			columns = this->columns + columns;

		if (rows < 0 || rows >= this->rows ||
			columns < 0 || columns >= this->columns)
		{
			ERROR("Выход за пределы матрицы");
		}

		return data[rows][columns];
	}

	int& Matrix::minimum() const
	{
		if (rows == 0 && columns == 0)
		{
			ERROR("Матрица пустая");
		}
		int min = data[0][0];
		for (size_t i = 1; i < rows; i++)
		{
			for (size_t j = 1; j < columns; j++)
			{
				if (data[i][j] < min)
				{
					min = data[i][j];
				}
			}
		}
		return min;
	}

	int& Matrix::maximum() const
	{
		if (rows == 0 && columns == 0)
		{
			ERROR("Матрица пустая");
		}
		int max = data[0][0];
		for (size_t i = 1; i < rows; i++)
		{
			for (size_t j = 1; j < columns; j++)
			{
				if (data[i][j] > max)
				{
					max = data[i][j];
				}
			}
		}
		return max;
	}
	
	Matrix Matrix::operator + (const Matrix& other) const
	{
		if (rows != other.rows || columns != other.columns)
		{
			ERROR("Матрицы разных размерностей нельзя складывать");
		}

		Matrix result(rows, columns);

		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				result(i, j) = data[i][j] + other.data[i][j];
			}
		}

		return result;
	}

	Matrix Matrix::operator - (const Matrix& other) const
	{
		if (rows != other.rows || columns != other.columns)
		{
			ERROR("Матрицы разных размерностей нельзя складывать");
		}

		Matrix result(rows, columns);

		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				result(i, j) = data[i][j] - other.data[i][j];
			}
		}

		return result;
	}

	Matrix Matrix::operator * (Matrix& other) const
	{
		if (columns != other.rows)
		{
			ERROR("Не выполнено условие перемножения матриц");
		}
		Matrix result(rows, other.columns);

		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < other.columns; j++)
			{
				for (size_t k = 0; k < columns; k++)
				{
					result(i, j) += data[i][k] * other(k, j);
				}
			}
		}

		return result;
	}

	int Matrix::rowsCount() const
	{
		return rows;
	}

	int Matrix::columnsCount() const
	{
		return columns;
	}

	void Matrix::fill(Generator& generator)
	{
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				data[i][j] = static_cast<int>(generator.generate());
			}
		}
	}

	void Matrix::removeColumn(int columnIndex)
	{
		if (columnIndex < 0 || columnIndex >= columns)
		{
			ERROR("Индекс столбца вне диапазона");
		}

		int newColumns = columns - 1;

		if (newColumns == 0)
		{
			*this = Matrix();
			return;
		}

		Matrix result(rows, newColumns);

		for (size_t i = 0; i < rows; i++)
		{
			int destCol = 0;
			for (size_t j = 0; j < columns; j++)
			{
				if (j == columnIndex)
				{
					continue;
				}
				result(i, destCol++) = data[i][j];
			}
		}

		*this = std::move(result);
	}

	std::ostream& operator << (std::ostream& output, const Matrix& matrix)
	{
		for (size_t i = 0; i < matrix.rows; i++)
		{
			for (int j = 0; j < matrix.columns; j++)
			{
				output << matrix.data[i][j];
				if (j + 1 < matrix.columns) output << '\t';
			}
			output << '\n';
		}
		return output;
	}

	std::istream& operator >> (std::istream& input, Matrix& matrix)
	{
		for (int i = 0; i < matrix.rows; i++)
		{
			for (int j = 0; j < matrix.columns; j++)
			{
				input >> matrix.data[i][j];
			}
		}
		return input;
	}
}
