#pragma once

#include "Exercise.h"

namespace miit::algebra
{
	/**
	 * @brief Реализация второго задания варианта 7
	 */
	class Task2 : public Exercise
	{
	private:
		/**
		 * @brief Матрица с результатом второго задания
		 */
		Matrix result;

	public:
		/**
		 * @brief Создать объект второго задания варианта 7
		 * @param matrix Матрица, над которой будет выполняться задание
		 * @param generator Генератор для заполнения матрицы
		 */
		Task2(Matrix& matrix, Generator& generator);

		/**
		 * @brief Удалить столбцы, в которых есть положительные нечётные элементы
		 * @return Матрица после выполнения второго задания
		 */
		Matrix& Solve() override;
	};
}
