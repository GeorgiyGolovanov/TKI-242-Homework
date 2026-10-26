#include "../include/MedicalInstitution.h"
#include <stdexcept>

MedicalInstitution::MedicalInstitution(const std::string& name, const std::string& address)
    : name(name), address(address)
{
    if (this->name.empty() || this->address.empty())
        throw std::invalid_argument("Нужны название и адрес учреждения");
}

const std::string& MedicalInstitution::getName() const
{
    return name;
}

const std::string& MedicalInstitution::getAddress() const
{
    return address;
}

const MedicalWorker& MedicalInstitution::getWorker(const int id) const
{
    for (const Doctor& doctor : doctors)
        if (doctor.getId() == id) 
            return doctor;
    for (const Nurse& nurse : nurses)
        if (nurse.getId() == id) 
            return nurse;
    throw std::invalid_argument("Медработник не найден: " + std::to_string(id));
}

const Patient& MedicalInstitution::getPatient(const int id) const
{
    for (const Patient& patient : patients)
        if (patient.getId() == id)
            return patient;

    throw std::invalid_argument("Пациент не найден: " + std::to_string(id));
}

Patient& MedicalInstitution::findPatient(const int id)
{
    for (Patient& patient : patients)
        if (patient.getId() == id)
            return patient;

    throw std::invalid_argument("Пациент не найден: " + std::to_string(id));
}

const Ward& MedicalInstitution::getWard(const int number) const
{
    for (const Ward& ward : wards)
        if (ward.getNumber() == number)
            return ward;

    throw std::invalid_argument("Палата не найдена: " + std::to_string(number));
}

Ward& MedicalInstitution::findWard(const int number)
{
    for (Ward& ward : wards)
        if (ward.getNumber() == number)
            return ward;

    throw std::invalid_argument("Палата не найдена: " + std::to_string(number));
}

int MedicalInstitution::addWorker(const Doctor& doctor)
{
    for (const Doctor& existing : doctors)
        if (existing.getId() == doctor.getId())
            throw std::invalid_argument("Медработник с этим ID уже добавлен");
    for (const Nurse& existing : nurses)
        if (existing.getId() == doctor.getId())
            throw std::invalid_argument("Медработник с этим ID уже добавлен");
    doctors.push_back(doctor);
    return doctor.getId();
}

int MedicalInstitution::addWorker(const Nurse& nurse)
{
    for (const Doctor& existing : doctors)
        if (existing.getId() == nurse.getId())
            throw std::invalid_argument("Медработник с этим ID уже добавлен");
    for (const Nurse& existing : nurses)
        if (existing.getId() == nurse.getId())
            throw std::invalid_argument("Медработник с этим ID уже добавлен");
    nurses.push_back(nurse);
    return nurse.getId();
}

int MedicalInstitution::addPatient(const Patient& patient)
{
    for (const Patient& existing : patients)
        if (existing.getId() == patient.getId())
            throw std::invalid_argument("Пациент с этим ID уже добавлен");
    for (const int workerId : patient.getWorkerIds())
        getWorker(workerId);
    patients.push_back(patient);
    return patient.getId();
}

void MedicalInstitution::addWard(const Ward& ward)
{
    if (ward.getOccupancy() != 0)
        throw std::invalid_argument("Добавлять можно только пустую палату");
    for (const Ward& existing : wards)
        if (existing.getNumber() == ward.getNumber())
            throw std::invalid_argument("Палата с таким номером уже есть");
    wards.push_back(ward);
}


const std::vector<Doctor>& MedicalInstitution::getDoctors() const
{
    return doctors;
}

const std::vector<Nurse>& MedicalInstitution::getNurses() const
{
    return nurses;
}

const std::vector<Patient>& MedicalInstitution::getPatients() const
{
    return patients;
}

const std::vector<Ward>& MedicalInstitution::getWards() const
{
    return wards;
}

MedicalInstitution::PatientList MedicalInstitution::searchPatients(const std::string& query) const
{
    PatientList result;
    for (const Patient& patient : patients)
        if (patient.matches(query))
            result.push_back(patient);
    return result;
}

std::vector<int> MedicalInstitution::searchWorkers(const std::string& query) const
{
    std::vector<int> result;
    for (const Doctor& doctor : doctors)
        if (doctor.matches(query)) result.push_back(doctor.getId());
    for (const Nurse& nurse : nurses)
        if (nurse.matches(query)) result.push_back(nurse.getId());
    return result;
}

std::vector<Doctor> MedicalInstitution::searchDoctors(const std::string& query) const
{
    std::vector<Doctor> result;
    for (const Doctor& doctor : doctors)
        if (doctor.matches(query)) result.push_back(doctor);
    return result;
}

bool MedicalInstitution::assignWorker(const int workerId, const int patientId)
{
    getWorker(workerId);
    return findPatient(patientId).addWorker(workerId);
}

bool MedicalInstitution::unassignWorker(const int workerId, const int patientId)
{
    getWorker(workerId);
    return findPatient(patientId).removeWorker(workerId);
}

std::vector<int> MedicalInstitution::getWorkersOfPatient(const int patientId) const
{
    std::vector<int> result;
    for (const int workerId : getPatient(patientId).getWorkerIds())
        result.push_back(workerId);
    return result;
}

MedicalInstitution::PatientList MedicalInstitution::getPatientsOfWorker(const int workerId) const
{
    getWorker(workerId);
    PatientList result;
    for (const Patient& patient : patients)
        if (patient.isObservedBy(workerId))
            result.push_back(patient);
    return result;
}

bool MedicalInstitution::placePatient(const int patientId, const int wardNumber)
{
    getPatient(patientId);
    Ward& target = findWard(wardNumber);
    if (target.contains(patientId))
        return false;
    target.addPatient(patientId);
    for (Ward& ward : wards)
        if (ward.getNumber() != wardNumber)
            ward.removePatient(patientId);
    return true;
}

bool MedicalInstitution::releasePatient(const int patientId)
{
    getPatient(patientId);
    for (Ward& ward : wards)
        if (ward.removePatient(patientId))
            return true;
    return false;
}

int MedicalInstitution::getWardNumberOfPatient(const int patientId) const
{
    getPatient(patientId);
    for (const Ward& ward : wards)
        if (ward.contains(patientId))
            return ward.getNumber();
    return 0;
}

MedicalInstitution::PatientList MedicalInstitution::getPatientsWithoutWard() const
{
    PatientList result;
    for (const Patient& patient : patients)
        if (getWardNumberOfPatient(patient.getId()) == 0)
            result.push_back(patient);
    return result;
}

std::string MedicalInstitution::getFullInfo() const
{
    return name + "\nАдрес: " + address
        + "\nМедработников: " + std::to_string(doctors.size() + nurses.size())
        + "\nПациентов: " + std::to_string(patients.size())
        + "\nПалат: " + std::to_string(wards.size()) + "\n";
}
