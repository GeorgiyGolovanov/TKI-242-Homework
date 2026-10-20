#pragma once

#include "Human.h"

/**
 * @brief Абстрактный базовый класс медицинского работника
 */
class MedicalWorker : public Human
{
private:
    /** 
    * @brief Отделение 
    */
    std::string department;

    /** 
    * @brief Стаж работы в годах 
    */
    int experience;

protected:
    /**
     * @brief Создать медработника 
     * @param name Имя (непустое)
     * @param surname Фамилия (непустая)
     * @param age Возраст, больше нуля
     * @param patronymic Отчество (при наличии)
     * @param phone Номер телефона; пустая строка
     * @param mail Электронная почта; пустая строка
     * @param experience Стаж в годах, от 0 до возраста
     * @param department Отделение 
     */
    MedicalWorker(const std::string& name,
                  const std::string& surname,
                  const int age,
                  const std::string& department,
                  const int experience,
                  const std::string& patronymic,
                  const std::string& phone,
                  const std::string& mail);

public:
    /**
     * @brief Получить отделение
     * @return Название отделения
     */
    const std::string& getDepartment() const;

    /**
     * @brief Получить стаж
     * @return Стаж в годах
     */
    int getExperience() const;

    /**
     * @brief Получить название специализации
     * @return Название специализации
     */
    virtual std::string getSpecializationName() const = 0;

    /**
     * @brief Проверить, является ли работник врачом
     * @return true для врача, false для остальных медработников
     */
    virtual bool isDoctor() const;

    /**
     * @brief Получить полную информацию о медработнике
     * @return Данные человека, отделение, стаж и специализация
     */
    std::string getFullInfo() const override;

    /**
     * @brief Проверить, встречается ли запрос в данных человека, отделении или специализации
     * @param query Текст для поиска без учёта регистра русских и латинских букв
     * @return true, если непустой запрос найден хотя бы в одном поле
     */
    bool matches(const std::string& query) const override;
};
