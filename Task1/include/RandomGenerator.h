#pragma once

#include "../include/Generator.h"
#include <random>

namespace miit::algebra
{
	/**
	 * @brief Генератор случайных целых чисел в заданном диапазоне
	 */
	class RandomGenerator : public Generator
	{
	private:
		/**
		 * @brief Равномерное распределение случайных целых чисел
		 */
		std::uniform_int_distribution<int> distribution;

		/**
		 * @brief Генератор псевдослучайных чисел
		 */
		std::mt19937 generator;

	public:
		/**
		 * @brief Создать генератор случайных чисел в заданном диапазоне
		 * @param min Минимальное значение диапазона
		 * @param max Максимальное значение диапазона
		 */
		RandomGenerator(const int min, const int max);

		/**
		 * @brief Сгенерировать случайное число из диапазона [min; max]
		 * @return Случайное число из заданного диапазона
		 */
		int generate() override;
	};
}
