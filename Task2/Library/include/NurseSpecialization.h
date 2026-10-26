#pragma once

#include <string>

/**
 * @brief Специализации медсестры
 */
enum class NurseSpecialization
{
    General,       // Общего профиля
    Ward,          // Палатная
    Procedural,    // Процедурная
    OperatingRoom, // Операционная
    IntensiveCare, // Интенсивной терапии
    Emergency,     // Скорой помощи
    Pediatric,     // Педиатрическая
    Anesthesia,    // Анестезиология
    District,      // Участковая
    Count          // Количество специализаций
};

/**
 * @brief Получить название специализации медсестры
 * @param value Специализация медсестры
 * @return Специализация медсестры
 */
std::string toString(const NurseSpecialization value);
