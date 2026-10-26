#include "../include/Doctor.h"
#include <stdexcept>

Doctor::Doctor(const std::string& name, const std::string& surname, const int age, const DoctorSpecialization specialization, 
    const std::string& department, const int experience, const std::string& patronymic,const std::string& phone, const std::string& mail)
    : MedicalWorker(name, surname, age, department, experience, patronymic, phone, mail), specialization(specialization) {}

DoctorSpecialization Doctor::getSpecialization() const
{
    return specialization;
}

std::string Doctor::getRole() const
{
    return "Врач";
}

bool Doctor::isDoctor() const
{
    return true;
}

std::string Doctor::getSpecializationName() const
{
    return toString(specialization);
}
