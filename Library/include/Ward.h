#pragma once

#include <cstddef>
#include <string>
#include <vector>

/**
 * @brief Больничная палата: номер, число мест и размещённые пациенты
 */
class Ward
{
private:
    /** 
    * @brief Номер палаты 
    */
    int number;

    /** 
    * @brief Количество мест 
    */
    int capacity;

    /** 
    * @brief Идентификаторы размещённых пациентов 
    */
    std::vector<int> patientIds;

public:
    /**
     * @brief Создать пустую палату
     * @param number Номер палаты, больше нуля
     * @param capacity Количество мест, больше нуля
     */
    Ward(const int number, const int capacity);

    /**
     * @brief Получить номер палаты
     * @return Номер палаты
     */
    int getNumber() const;

    /**
     * @brief Получить вместимость палаты
     * @return Количество мест
     */
    int getCapacity() const;

    /**
     * @brief Получить количество занятых мест
     * @return Число размещённых пациентов
     */
    std::size_t getOccupancy() const;

    /**
     * @brief Получить идентификаторы размещённых пациентов
     * @return Ссылка на список идентификаторов
     */
    const std::vector<int>& getPatientIds() const;

    /**
     * @brief Проверить, лежит ли пациент в этой палате
     * @param patientId Идентификатор пациента
     * @return true, если пациент размещён в палате
     */
    bool contains(const int patientId) const;

    /**
     * @brief Проверить, заняты ли все места
     * @return true, если свободных мест нет
     */
    bool isFull() const;

    /**
     * @brief Разместить пациента в палате
     * @param patientId Идентификатор пациента
     * @return true, если пациент размещён; false, если он уже был в палате
     */
    bool addPatient(const int patientId);

    /**
     * @brief Освободить место пациента
     * @param patientId Идентификатор пациента
     * @return true, если место освобождено; false, если пациента в палате не было
     */
    bool removePatient(const int patientId);

    /**
     * @brief Получить краткую информацию о палате
     * @return Строка
     */
    std::string getFullInfo() const;
};
