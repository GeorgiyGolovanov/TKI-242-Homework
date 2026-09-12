#pragma once

#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra
{
	/**
	 * @brief Базовый класс для заданий, выполняемых над матрицей
	 */
	class Exercise
	{
	protected:
		/**
		 * @brief Матрица, над которой выполняются задания
		 */
		Matrix& OurMatrix;

		/**
		 * @brief Генератор, используемый для заполнения матрицы
		 */
		Generator& OurGenerator;

	public:
		/**
		 * @brief Создать объект задания для указанной матрицы
		 * @param matrix Матрица, над которой будет выполняться задание
		 * @param generator Генератор для заполнения матрицы
		 */
		Exercise(Matrix& matrix, Generator& generator);

		/**
		 * @brief Уничтожить объект задания
		 */
		virtual ~Exercise() = default;

		/**
		 * @brief Заполнить матрицу с помощью выбранного генератора
		 */
		void Fill();

		/**
		 * @brief Выполнить задание
		 * @return Матрица с результатом задания
		 */
		virtual Matrix& Solve() = 0;
	};
}
