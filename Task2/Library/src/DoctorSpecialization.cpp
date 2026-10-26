#include "../include/DoctorSpecialization.h"
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
        "Терапевт", "Кардиолог", "Невролог", "Нейрохирург", "Хирург",
        "Сердечно-сосудистый хирург", "Травматолог", "Ортопед", "Педиатр", "Неонатолог",
        "Гинеколог", "Акушер", "Уролог", "Дерматолог", "Офтальмолог",
        "ЛОР", "Гастроэнтеролог", "Гепатолог", "Пульмонолог", "Эндокринолог",
        "Нефролог", "Ревматолог", "Гематолог", "Онколог", "Инфекционист",
        "Аллерголог", "Психиатр", "Анестезиолог", "Реаниматолог", "Врач скорой помощи",
        "Стоматолог", "Стоматолог-хирург", "Ортодонт", "Патологоанатом", "Генетик",
        "Врач-реабилитолог", "Эпидемиолог"
    };

    static_assert(std::size(names) == static_cast<std::size_t>(DoctorSpecialization::Count),
                  "Таблица названий должна совпадать с перечислением");
}

std::string toString(const DoctorSpecialization value)
{
    const int index = static_cast<int>(value);
    if (index < 0 || index >= static_cast<int>(DoctorSpecialization::Count))
        throw std::invalid_argument("Неизвестная специализация врача");
    return names[index];
}
