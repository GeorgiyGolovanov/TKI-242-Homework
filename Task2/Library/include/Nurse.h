#pragma once

#include "MedicalWorker.h"
#include "NurseSpecialization.h"

/**
 * @brief Медсестра или медбрат с выбранной специализацией
 */
class Nurse : public MedicalWorker
{
private:
    /** 
    * @brief Специализация медсестры или медбрата 
    */
    NurseSpecialization specialization;

public:
    /**
     * @brief Создать медсестру или медбрата
     * @param name Имя (непустое)
     * @param surname Фамилия (непустая)
     * @param age Возраст, больше нуля
     * @param patronymic Отчество (при наличии)
     * @param phone Номер телефона; пустая строка
     * @param mail Электронная почта; пустая строка
     * @param experience Стаж в годах, от 0 до возраста
     * @param department Отделение 
     */
    Nurse(const std::string& name,
          const std::string& surname,
          const int age,
          const NurseSpecialization specialization,
          const std::string& department,
          const int experience,
          const std::string& patronymic = "",
          const std::string& phone = "",
          const std::string& mail = "");

    /**
     * @brief Получить специализацию
     * @return Значение перечисления специализаций
     */
    NurseSpecialization getSpecialization() const;

    /**
     * @brief Получить категорию человека
     * @return «Медсестра / медбрат»
     */
    std::string getRole() const override;

    /**
     * @brief Получить название специализации
     * @return Название специализации на русском языке
     */
    std::string getSpecializationName() const override;
};
