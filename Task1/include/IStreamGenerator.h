#pragma once

#include "Generator.h"
#include <iostream>

namespace miit::algebra
{
	/**
	 * @brief Генератор, который считывает значения из входного потока
	 */
	class IStreamGenerator : public Generator
	{
	private:
		/**
		 * @brief Поток, из которого считываются значения
		 */
		std::istream& in;

	public:
		/**
		 * @brief Создать генератор для чтения значений из потока
		 * @param in Входной поток
		 */
		IStreamGenerator(std::istream& in = std::cin);

		/**
		 * @brief Считать следующее значение из потока
		 * @return Считанное значение
		 */
		int generate() override;
	};
}
