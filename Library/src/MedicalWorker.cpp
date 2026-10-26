#include "../include/MedicalWorker.h"
#include <stdexcept>

MedicalWorker::MedicalWorker(const std::string& name,
                             const std::string& surname,
                             const int age,
                             const std::string& department,
                             const int experience,
                             const std::string& patronymic,
                             const std::string& phone,
                             const std::string& mail)
    : Human(name, surname, age, patronymic, phone, mail),
      department(department),
      experience(experience)
{
    if (this->department.empty() || experience < 0 || experience > age)
        throw std::invalid_argument("Нужны отделение и стаж от 0 до возраста работника");
}

const std::string& MedicalWorker::getDepartment() const
{
    return department;
}

int MedicalWorker::getExperience() const
{
    return experience;
}

bool MedicalWorker::isDoctor() const
{
    return false;
}

std::string MedicalWorker::getFullInfo() const
{
    return Human::getFullInfo()
        + "Отделение: " + department
        + "\nСтаж: " + std::to_string(experience)
        + "\nСпециализация: " + getSpecializationName() + "\n";
}

bool MedicalWorker::matches(const std::string& query) const
{
    return Human::matches(query)
        || department.find(query) != std::string::npos
        || getSpecializationName().find(query) != std::string::npos;
}
