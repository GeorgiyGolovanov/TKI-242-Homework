#pragma once

#include "MedicalWorker.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"
#include "Ward.h"
#include <functional>
#include <string>
#include <vector>

/**
 * @brief Больница: медработники, пациенты, палаты и назначения
 */
class MedicalInstitution
{
private:
    /** 
    * @brief Название учреждения 
    */
    std::string name;

    /** 
    * @brief Адрес учреждения 
    */
    std::string address;

    /** 
    * @brief Врачи
    */
    std::vector<Doctor> doctors;

    /** 
    * @brief Медсёстры
    */
    std::vector<Nurse> nurses;

    /** 
    * @brief Пациенты 
    */
    std::vector<Patient> patients;

    /** 
    * @brief Палаты 
    */
    std::vector<Ward> wards;

    /**
     * @brief Найти пациента для изменения
     * @param id Идентификатор пациента
     * @return Ссылка на пациента
     */
    Patient& findPatient(const int id);

    /**
     * @brief Найти палату для изменения
     * @param number Номер палаты
     * @return Ссылка на палату
     */
    Ward& findWard(const int number);

public:
    /**
     * @brief Создать учреждение
     * @param name Название 
     * @param address Адрес 
     */
    MedicalInstitution(const std::string& name, const std::string& address);

    /**
     * @brief Получить название
     * @return Название учреждения
     */
    const std::string& getName() const;

    /**
     * @brief Получить адрес
     * @return Адрес учреждения
     */
    const std::string& getAddress() const;

    /**
     * @brief Добавить медработника
     * @param worker Врач или медсестра; владение передаётся учреждению
     * @return Идентификатор добавленного медработника
     */
    int addWorker(const Doctor& doctor);
    int addWorker(const Nurse& nurse);

    /**
     * @brief Добавить пациента (сохраняется копия)
     * @param patient Пациент
     * @return Идентификатор добавленного пациента
     */
    int addPatient(const Patient& patient);

    /**
     * @brief Добавить пустую палату
     * @param ward Палата
     */
    void addWard(const Ward& ward);

    /**
    * @brief Список медработников
    */
    const std::vector<Doctor>& getDoctors() const;
    const std::vector<Nurse>& getNurses() const;

    /**
    * @brief Список пациентов
    */
    using PatientList = std::vector<std::reference_wrapper<const Patient>>;

    /**
     * @brief Получить всех пациентов
     * @return Ссылка на список пациентов (действительна до следующего addPatient)
     */
    const std::vector<Patient>& getPatients() const;

    /**
     * @brief Получить все палаты
     * @return Ссылка на список палат (действительна до следующего addWard)
     */
    const std::vector<Ward>& getWards() const;

    /**
     * @brief Найти медработника по идентификатору
     * @param id Идентификатор медработника
     * @return Ссылка на медработника
     */
    const MedicalWorker& getWorker(const int id) const;

    /**
     * @brief Найти пациента по идентификатору
     * @param id Идентификатор пациента
     * @return Ссылка на пациента
     */
    const Patient& getPatient(const int id) const;

    /**
     * @brief Найти палату по номеру
     * @param number Номер палаты
     * @return Ссылка на палату
     */
    const Ward& getWard(const int number) const;

    /**
     * @brief Найти пациентов по ФИО, ID, контактам или диагнозу
     * @param query Текст для поиска без учёта регистра
     * @return Найденные пациенты
     */
    PatientList searchPatients(const std::string& query) const;

    /**
     * @brief Найти ID медработников по ФИО, ID, контактам, отделению или специализации
     * @param query Текст для поиска без учёта регистра
     * @return ID найденных медработников
     */
    std::vector<int> searchWorkers(const std::string& query) const;

    /**
     * @brief Найти врачей по тем же полям, что и searchWorkers()
     * @param query Текст для поиска без учёта регистра
     * @return Найденные врачи
     */
    std::vector<Doctor> searchDoctors(const std::string& query) const;

    /**
     * @brief Назначить медработника пациенту
     * @param workerId Идентификатор медработника
     * @param patientId Идентификатор пациента
     * @return true, если назначение добавлено; false, если оно уже было
     */
    bool assignWorker(const int workerId, const int patientId);

    /**
     * @brief Отменить назначение медработника пациенту
     * @param workerId Идентификатор медработника
     * @param patientId Идентификатор пациента
     * @return true, если назначение удалено; false, если его не было
     */
    bool unassignWorker(const int workerId, const int patientId);

    /**
     * @brief Получить медработников, наблюдающих пациента
     * @param patientId Идентификатор пациента
     * @return Список назначенных медработников
     */
    std::vector<int> getWorkersOfPatient(const int patientId) const;

    /**
     * @brief Получить пациентов, которых наблюдает медработник
     * @param workerId Идентификатор медработника
     * @return Список пациентов медработника
     */
    PatientList getPatientsOfWorker(const int workerId) const;

    /**
     * @brief Разместить пациента в палате или перевести в другую
     * @param patientId Идентификатор пациента
     * @param wardNumber Номер палаты
     * @return true, если палата изменена; false, если пациент уже в этой палате
     */
    bool placePatient(const int patientId, const int wardNumber);

    /**
     * @brief Освободить место пациента в палате
     * @param patientId Идентификатор пациента
     * @return true, если место освобождено; false, если пациент не был размещён
     */
    bool releasePatient(const int patientId);

    /**
     * @brief Узнать палату пациента
     * @param patientId Идентификатор пациента
     * @return Номер палаты или 0, если пациент не размещён
     */
    int getWardNumberOfPatient(const int patientId) const;

    /**
     * @brief Получить пациентов, не размещённых ни в одной палате
     * @return Список пациентов без палаты
     */
    PatientList getPatientsWithoutWard() const;

    /**
     * @brief Получить краткую сводку об учреждении
     * @return Название, адрес и количество медработников, пациентов и палат
     */
    std::string getFullInfo() const;
};
