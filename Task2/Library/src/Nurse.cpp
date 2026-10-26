#include "../include/Nurse.h"
#include <stdexcept>

Nurse::Nurse(const std::string& name,
             const std::string& surname,
             const int age,
             const NurseSpecialization specialization,
             const std::string& department,
             const int experience,
             const std::string& patronymic,
             const std::string& phone,
             const std::string& mail)
    : MedicalWorker(name, surname, age, department, experience, patronymic, phone, mail),
      specialization(specialization)
{
    toString(specialization);
}

NurseSpecialization Nurse::getSpecialization() const
{
    return specialization;
}

std::string Nurse::getRole() const
{
    return "Медсестра / медбрат";
}

std::string Nurse::getSpecializationName() const
{
    return toString(specialization);
}
