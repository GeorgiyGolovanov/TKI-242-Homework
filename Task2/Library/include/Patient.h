#pragma once

#include "Human.h"
#include <vector>

/**
 * @brief Пациент больницы, его диагноз и наблюдающие медработники
 */
class Patient : public Human
{
private:
    /** 
    * @brief Диагноз
    */
    std::string diagnosis;

    /** 
    * @brief Идентификаторы медработников, закреплённые за пациентом
    */
    std::vector<int> workerIds;

public:
    /**
     * @brief Создать пациента
     * @param name Имя
     * @param surname Фамилия
     * @param age Возраст
     * @param diagnosis Диагноз (если есть)
     * @param patronymic Отчество (если есть)
     * @param phone Номер телефона
     * @param mail Электронная почта
     */
    Patient(const std::string& name,
            const std::string& surname,
            const int age,
            const std::string& diagnosis = "",
            const std::string& patronymic = "",
            const std::string& phone = "",
            const std::string& mail = "");

    /**
     * @brief Получить диагноз
     * @return Диагноз или пустая строка
     */
    const std::string& getDiagnosis() const;

    /**
     * @brief Получить идентификаторы наблюдающих медработников
     * @return Ссылка на список идентификаторов
     */
    const std::vector<int>& getWorkerIds() const;

    /**
     * @brief Проверить, наблюдает ли медработник пациента
     * @param workerId Идентификатор медработника
     * @return true, если медработник назначен пациенту
     */
    bool isObservedBy(const int workerId) const;

    /**
     * @brief Назначить медработника пациенту
     * @param workerId Идентификатор медработника
     * @return true, если назначение добавлено; false, если оно уже было
     */
    bool addWorker(const int workerId);

    /**
     * @brief Отменить назначение медработника
     * @param workerId Идентификатор медработника
     * @return true, если назначение удалено; false, если его не было
     */
    bool removeWorker(const int workerId);

    /**
     * @brief Получить категорию человека
     * @return «Пациент»
     */
    std::string getRole() const override;

    /**
     * @brief Получить полную информацию о пациенте
     * @return Данные человека и диагноз
     */
    std::string getFullInfo() const override;

    /**
     * @brief Проверить, встречается ли запрос в данных человека или в диагнозе
     * @param query Текст для поиска без учёта регистра русских и латинских букв
     * @return true, если непустой запрос найден хотя бы в одном поле
     */
    bool matches(const std::string& query) const override;
};
