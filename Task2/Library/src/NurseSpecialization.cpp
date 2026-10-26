#include "../include/NurseSpecialization.h"
#include <iterator>
#include <string>
#include <stdexcept>

namespace
{
    /**
    * @brief Названия специализаций в порядке значений перечисления 
    */
    const std::string names[] =
    {
        "Общего профиля", "Палатная", "Процедурная", "Операционная", "Интенсивной терапии",
        "Скорой помощи", "Педиатрическая", "Анестезиология", "Участковая"
    };

    static_assert(std::size(names) == static_cast<std::size_t>(NurseSpecialization::Count),
                  "Таблица названий должна совпадать с перечислением");
}

std::string toString(const NurseSpecialization value)
{
    const int index = static_cast<int>(value);
    if (index < 0 || index >= static_cast<int>(NurseSpecialization::Count))
        throw std::invalid_argument("Неизвестная специализация медсестры");
    return names[index];
}
