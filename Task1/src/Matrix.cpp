#include "../include/Matrix.h"
#include <algorithm>
#include <stdexcept>

namespace miit::algebra
{
	void Matrix::ERROR(const std::string& text) const
	{
		throw std::invalid_argument(text);
	}

	void Matrix::MEMORY(int** data) const
	{
		if (data == nullptr)
		{
			ERROR("Ошибка выделения памяти");
		}

		for (size_t i = 0; i < rows; i++)
		{
			if (data[i] == nullptr)
			{
				ERROR("Ошибка выделения памяти");
			}
		}
	}

	void Matrix::allocate()
	{
		if (rows == 0 || columns == 0)
		{
			data = nullptr;
			return;
		}

		data = new int* [rows];

		for (size_t i = 0; i < rows; i++)
		{
			data[i] = new int[columns]();
		}

		MEMORY(data);
	}

	void Matrix::clear()
	{
		if (data != nullptr)
		{
			for (size_t i = 0; i < rows; i++)
			{
				delete[] data[i];
			}
			delete[] data;
		}

		data = nullptr;
		rows = 0;
		columns = 0;
	}

	Matrix::Matrix() : data(nullptr), rows(0), columns(0)
	{
	}

	Matrix::Matrix(const int rows, const int columns) : data(nullptr), rows(0), columns(0)
	{
		if (rows <= 0 || columns <= 0)
		{
			ERROR("Неверные размеры матрицы");
		}

		this->rows = static_cast<size_t>(rows);
		this->columns = static_cast<size_t>(columns);

		allocate();
	}

	Matrix::Matrix(const Matrix& elements)
		: data(nullptr), rows(elements.rows), columns(elements.columns)
	{
		allocate();

		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				data[i][j] = elements.data[i][j];
			}
		}
	}

	Matrix::Matrix(Matrix&& elements)
		: data(elements.data), rows(elements.rows), columns(elements.columns)
	{
		elements.data = nullptr;
		elements.rows = 0;
		elements.columns = 0;
	}

	Matrix::~Matrix()
	{
		clear();
	}

	bool Matrix::operator == (const Matrix& other) const
	{
		if (rows != other.rows || columns != other.columns)
		{
			return false;
		}

		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
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

	Matrix& Matrix::operator = (const Matrix& other)
	{
		if (this != &other)
		{
			clear();

			rows = other.rows;
			columns = other.columns;

			allocate();

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

		clear();

		data = other.data;
		rows = other.rows;
		columns = other.columns;

		other.data = nullptr;
		other.rows = 0;
		other.columns = 0;

		return *this;
	}

	int& Matrix::operator () (const int row, const int column)
	{
		return const_cast<int&>(static_cast<const Matrix&>(*this)(row, column));
	}

	const int& Matrix::operator () (const int row, const int column) const
	{
		int currentRow = row;
		int currentColumn = column;

		if (currentRow < 0)
		{
			currentRow += static_cast<int>(rows);
		}

		if (currentColumn < 0)
		{
			currentColumn += static_cast<int>(columns);
		}

		if (currentRow < 0 || currentRow >= static_cast<int>(rows) ||
			currentColumn < 0 || currentColumn >= static_cast<int>(columns))
		{
			ERROR("Выход за пределы матрицы");
		}

		return data[currentRow][currentColumn];
	}

	int& Matrix::minimum() const
	{
		if (rows == 0 || columns == 0)
		{
			ERROR("Матрица пустая");
		}

		size_t minRow = 0;
		size_t minColumn = 0;

		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				if (data[i][j] < data[minRow][minColumn])
				{
					minRow = i;
					minColumn = j;
				}
			}
		}

		return data[minRow][minColumn];
	}

	int& Matrix::maximum() const
	{
		if (rows == 0 || columns == 0)
		{
			ERROR("Матрица пустая");
		}

		size_t maxRow = 0;
		size_t maxColumn = 0;

		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				if (data[i][j] > data[maxRow][maxColumn])
				{
					maxRow = i;
					maxColumn = j;
				}
			}
		}

		return data[maxRow][maxColumn];
	}

	Matrix Matrix::operator + (const Matrix& other) const
	{
		if (rows != other.rows || columns != other.columns)
		{
			ERROR("Матрицы разных размерностей нельзя складывать");
		}

		Matrix result(static_cast<int>(rows), static_cast<int>(columns));

		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				result.data[i][j] = data[i][j] + other.data[i][j];
			}
		}

		return result;
	}

	Matrix Matrix::operator - (const Matrix& other) const
	{
		if (rows != other.rows || columns != other.columns)
		{
			ERROR("Матрицы разных размерностей нельзя вычитать");
		}

		Matrix result(static_cast<int>(rows), static_cast<int>(columns));

		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				result.data[i][j] = data[i][j] - other.data[i][j];
			}
		}

		return result;
	}

	Matrix Matrix::operator * (const Matrix& other) const
	{
		if (columns != other.rows)
		{
			ERROR("Не выполнено условие перемножения матриц");
		}

		Matrix result(static_cast<int>(rows), static_cast<int>(other.columns));

		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < other.columns; j++)
			{
				for (size_t k = 0; k < columns; k++)
				{
					result.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}

		return result;
	}

	size_t Matrix::rowsCount() const
	{
		return rows;
	}

	size_t Matrix::columnsCount() const
	{
		return columns;
	}

	void Matrix::fill(const Generator& generator)
	{
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				data[i][j] = generator.generate();
			}
		}
	}

	void Matrix::removeColumn(const size_t columnIndex)
	{
		if (columnIndex >= columns)
		{
			ERROR("Индекс столбца вне диапазона");
		}

		const size_t newColumns = columns - 1;

		if (newColumns == 0)
		{
			*this = Matrix();
			return;
		}

		Matrix result(static_cast<int>(rows), static_cast<int>(newColumns));

		for (size_t i = 0; i < rows; i++)
		{
			size_t destinationColumn = 0;

			for (size_t j = 0; j < columns; j++)
			{
				if (j == columnIndex)
				{
					continue;
				}

				result.data[i][destinationColumn++] = data[i][j];
			}
		}

		*this = std::move(result);
	}

	std::ostream& operator << (std::ostream& output, const Matrix& matrix)
	{
		for (size_t i = 0; i < matrix.rows; i++)
		{
			for (size_t j = 0; j < matrix.columns; j++)
			{
				output << matrix.data[i][j];

				if (j + 1 < matrix.columns)
				{
					output << '\t';
				}
			}
			output << '\n';
		}

		return output;
	}

	std::istream& operator >> (std::istream& input, Matrix& matrix)
	{
		for (size_t i = 0; i < matrix.rows; i++)
		{
			for (size_t j = 0; j < matrix.columns; j++)
			{
				input >> matrix.data[i][j];
			}
		}

		return input;
	}
}
