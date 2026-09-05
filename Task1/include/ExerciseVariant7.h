#pragma once

#include "Exercise.h"

namespace miit::algebra
{
	/**
	 * @brief Реализация заданий для варианта 7
	 */
	class ExerciseVariant7 : public Exercise
	{
	private:
		/**
		 * @brief Матрица с результатом первого задания
		 */
		Matrix TaskOneResult;

		/**
		 * @brief Матрица с результатом второго задания
		 */
		Matrix TaskTwoResult;

	public:
		/**
		 * @brief Создать объект заданий варианта 7
		 * @param matrix Матрица, над которой будут выполняться задания
		 * @param generator Генератор для заполнения матрицы
		 */
		ExerciseVariant7(Matrix& matrix, Generator& generator);

		/**
		 * @brief Заменить минимальный элемент в каждой строке на ноль
		 * @return Матрица после выполнения первого задания
		 */
		Matrix& TaskOne() override;

		/**
		 * @brief Удалить столбцы, в которых есть положительные нечётные элементы
		 * @return Матрица после выполнения второго задания
		 */
		Matrix& TaskTwo() override;
	};
}
