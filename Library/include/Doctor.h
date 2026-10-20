#pragma once

#include "DoctorSpecialization.h"
#include "MedicalWorker.h"

/**
 * @brief Врач с выбранной специализацией
 */
class Doctor : public MedicalWorker
{
private:
    /**
    * @brief Специализация врача 
    */
    DoctorSpecialization specialization;

public:
    /**
     * @brief Создать врача
     * @param name Имя
     * @param surname Фамилия
     * @param age Возраст
     * @param specialization Специализация врача
     * @param department Отделение 
     * @param experience Стаж в годах
     * @param patronymic Отчество (при наличии)
     * @param phone Номер телефона (при наличии)
     * @param mail Электронная почта (при наличии)
     */
    Doctor(const std::string& name,
           const std::string& surname,
           const int age,
           const DoctorSpecialization specialization,
           const std::string& department,
           const int experience,
           const std::string& patronymic = "",
           const std::string& phone = "",
           const std::string& mail = "");

    /**
     * @brief Получить специализацию
     * @return Значение перечисления специализаций
     */
    DoctorSpecialization getSpecialization() const;

    /**
     * @brief Получить категорию человека
     * @return «Врач»
     */
    std::string getRole() const override;

    /**
     * @brief Проверить, является ли работник врачом
     * @return Всегда true
     */
    bool isDoctor() const override;

    /**
     * @brief Получить название специализации
     * @return Название специализации на русском языке
     */
    std::string getSpecializationName() const override;
};
