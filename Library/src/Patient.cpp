#include "../include/Patient.h"
#include <algorithm>

Patient::Patient(const std::string& name,
                 const std::string& surname,
                 const int age,
                 const std::string& diagnosis,
                 const std::string& patronymic,
                 const std::string& phone,
                 const std::string& mail)
    : Human(name, surname, age, patronymic, phone, mail),
      diagnosis(diagnosis)
{
}

const std::string& Patient::getDiagnosis() const
{
    return diagnosis;
}

const std::vector<int>& Patient::getWorkerIds() const
{
    return workerIds;
}

bool Patient::isObservedBy(const int workerId) const
{
    return std::find(workerIds.begin(), workerIds.end(), workerId) != workerIds.end();
}

bool Patient::addWorker(const int workerId)
{
    if (isObservedBy(workerId))
        return false;
    workerIds.push_back(workerId);
    return true;
}

bool Patient::removeWorker(const int workerId)
{
    const auto it = std::find(workerIds.begin(), workerIds.end(), workerId);
    if (it == workerIds.end())
        return false;
    workerIds.erase(it);
    return true;
}

std::string Patient::getRole() const
{
    return "Пациент";
}

std::string Patient::getFullInfo() const
{
    return Human::getFullInfo()
        + "Диагноз: " + (diagnosis.empty() ? "не указан" : diagnosis) + "\n";
}

bool Patient::matches(const std::string& query) const
{
    return Human::matches(query) || diagnosis.find(query) != std::string::npos;
}
