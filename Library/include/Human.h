#pragma once

#include <string>

/**
 * @brief Абстрактный базовый класс человека
 */
class Human
{
private:
    /** 
    * @brief Уникальный идентификатор, выдаётся автоматически при создании 
    */
    int id;

    /** 
    * @brief Имя 
    */
    std::string name;

    /** 
    * @brief Фамилия 
    */
    std::string surname;

    /** 
    * @brief Отчество (при наличии) 
    */
    std::string patronymic;

    /** 
    * @brief Возраст в годах 
    */
    int age;

    /** 
    * @brief Номер телефона (может быть пустым) 
    */
    std::string phone;

    /** 
    * @brief Электронная почта (может быть пустой) 
    */
    std::string mail;

public:
    /**
     * @brief Создать человека
     * @param name Имя (непустое)
     * @param surname Фамилия (непустая)
     * @param age Возраст, больше нуля
     * @param patronymic Отчество (при наличии)
     * @param phone Номер телефона; пустая строка
     * @param mail Электронная почта; пустая строка
     */
    Human(const std::string& name,
          const std::string& surname,
          const int age,
          const std::string& patronymic = "",
          const std::string& phone = "",
          const std::string& mail = "");

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Human() = default;

    /**
     * @brief Получить идентификатор
     * @return Уникальный идентификатор человека
     */
    int getId() const;

    /**
     * @brief Получить имя
     * @return Имя
     */
    const std::string& getName() const;

    /**
     * @brief Получить фамилию
     * @return Фамилия
     */
    const std::string& getSurname() const;

    /**
     * @brief Получить отчество
     * @return Отчество (при наличии) или пустая строка
     */
    const std::string& getPatronymic() const;

    /**
     * @brief Получить возраст
     * @return Возраст в годах
     */
    int getAge() const;

    /**
     * @brief Получить номер телефона
     * @return Номер телефона или пустая строка
     */
    const std::string& getPhone() const;

    /**
     * @brief Получить электронную почту
     * @return Адрес электронной почты или пустая строка
     */
    const std::string& getMail() const;

    /**
     * @brief Получить фамилию, имя и отчество одной строкой
     * @return ФИО
     */
    std::string getFullName() const;

    /**
     * @brief Получить категорию человека
     * @return Название категории («Врач», «Пациент» и т.п.)
     */
    virtual std::string getRole() const = 0;

    /**
     * @brief Получить полную информацию о человеке
     * @return Многострочный текст с данными
     */
    virtual std::string getFullInfo() const;

    /**
     * @brief Проверить, встречается ли запрос в ФИО, телефоне или почте либо совпадает с ID
     * @param query Текст для поиска без учёта регистра русских и латинских букв
     * @return true, если непустой запрос найден хотя бы в одном поле или равен ID
     */
    virtual bool matches(const std::string& query) const;
};
