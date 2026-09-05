#pragma once

#include "Generator.h"
#include <iostream>
#include <string>

namespace miit::algebra
{
	/**
	 * @brief Класс для работы с целочисленной матрицей
	 */
	class Matrix
	{
	private:
		/**
		 * @brief Данные матрицы
		 */
		int** data;

		/**
		 * @brief Количество строк матрицы
		 */
		int rows;

		/**
		 * @brief Количество столбцов матрицы
		 */
		int columns;

		/**
		 * @brief Выбросить исключение с указанным сообщением
		 * @param text Сообщение об ошибке
		 */
		void ERROR(const std::string& text) const;

		/**
		 * @brief Проверить корректность выделенной памяти
		 * @param data Указатель на данные матрицы
		 */
		void MEMORY(int** data) const;

	public:
		/**
		 * @brief Создать пустую матрицу
		 */
		Matrix();

		/**
		 * @brief Создать матрицу заданного размера
		 * @param rows Количество строк
		 * @param columns Количество столбцов
		 */
		Matrix(const int rows, const int columns);

		/**
		 * @brief Создать копию другой матрицы
		 * @param elements Матрица, которую нужно скопировать
		 */
		Matrix(const Matrix& elements);

		/**
		 * @brief Создать матрицу, переместив данные из другого объекта
		 * @param elements Матрица, из которой нужно переместить данные
		 */
		Matrix(Matrix&& elements);

		/**
		 * @brief Проверить матрицы на равенство
		 * @param other Матрица для сравнения
		 * @return true, если матрицы равны, иначе false
		 */
		bool operator == (const Matrix& other) const;

		/**
		 * @brief Проверить матрицы на неравенство
		 * @param other Матрица для сравнения
		 * @return true, если матрицы различаются, иначе false
		 */
		bool operator != (const Matrix& other) const;

		/**
		 * @brief Присвоить текущей матрице копию другой матрицы
		 * @param other Матрица, которую нужно скопировать
		 * @return Ссылка на текущую матрицу
		 */
		Matrix& operator = (const Matrix& other);

		/**
		 * @brief Переместить данные другой матрицы в текущую
		 * @param other Матрица, из которой нужно переместить данные
		 * @return Ссылка на текущую матрицу
		 */
		Matrix& operator = (Matrix&& other);

		/**
		 * @brief Сложить текущую матрицу с другой матрицей
		 * @param other Матрица для сложения
		 * @return Результат сложения матриц
		 */
		Matrix operator + (const Matrix& other) const;

		/**
		 * @brief Вычесть другую матрицу из текущей
		 * @param other Матрица для вычитания
		 * @return Результат вычитания матриц
		 */
		Matrix operator - (const Matrix& other) const;

		/**
		 * @brief Умножить текущую матрицу на другую матрицу
		 * @param other Матрица для умножения
		 * @return Результат умножения матриц
		 */
		Matrix operator * (Matrix& other) const;

		/**
		 * @brief Получить элемент матрицы по индексам
		 * @param row Индекс строки
		 * @param column Индекс столбца
		 * @return Ссылка на выбранный элемент матрицы
		 */
		int& operator () (int row, int column);

		/**
		 * @brief Найти минимальное значение в матрице
		 * @return Ссылка на минимальное значение
		 */
		int& minimum() const;

		/**
		 * @brief Найти максимальное значение в матрице
		 * @return Ссылка на максимальное значение
		 */
		int& maximum() const;

		/**
		 * @brief Получить количество строк матрицы
		 * @return Количество строк
		 */
		int rowsCount() const;

		/**
		 * @brief Получить количество столбцов матрицы
		 * @return Количество столбцов
		 */
		int columnsCount() const;

		/**
		 * @brief Заполнить матрицу значениями из генератора
		 * @param generator Генератор значений
		 */
		void fill(Generator& generator);

		/**
		 * @brief Удалить столбец по его индексу
		 * @param columnIndex Индекс столбца, который нужно удалить
		 */
		void removeColumn(int columnIndex);

		/**
		 * @brief Вывести матрицу в поток
		 * @param output Поток для вывода
		 * @param matrix Матрица, которую нужно вывести
		 * @return Поток после вывода матрицы
		 */
		friend std::ostream& operator << (std::ostream& output, const Matrix& matrix);

		/**
		 * @brief Считать элементы матрицы из потока
		 * @param input Поток для чтения
		 * @param matrix Матрица, которую нужно заполнить
		 * @return Поток после чтения матрицы
		 */
		friend std::istream& operator >> (std::istream& input, Matrix& matrix);

		/**
		 * @brief Освободить память, занятую матрицей
		 */
		~Matrix();
	};
}
