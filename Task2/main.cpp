#include "Library/include/Doctor.h"
#include "Library/include/MedicalInstitution.h"
#include "Library/include/Nurse.h"
#include "Library/include/Patient.h"
#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    MedicalInstitution hospital("Городская больница", "ул. Центральная, 10");

    const int doctorId = hospital.addWorker(Doctor(
        "Анна", "Иванова", 38, DoctorSpecialization::Cardiologist, "Кардиология", 12));
    hospital.addWorker(Nurse(
        "Мария", "Смирнова", 28, NurseSpecialization::Ward, "Кардиология", 5));

    const int patientId = hospital.addPatient(Patient("Иван", "Кузнецов", 50, "Стенокардия"));
    hospital.addPatient(Patient("Пётр", "Соколов", 42, "Гипертония"));

    hospital.addWard(Ward(101, 1));
    hospital.addWard(Ward(102, 2));
    hospital.assignWorker(doctorId, patientId);
    hospital.placePatient(patientId, 101);

    std::cout << "=== Учреждение ===\n" << hospital.getFullInfo();
    std::cout << "\n=== Медработники ===\n";
    for (const Doctor& doctor : hospital.getDoctors())
        std::cout << doctor.getFullInfo() << '\n';
    for (const Nurse& nurse : hospital.getNurses())
        std::cout << nurse.getFullInfo() << '\n';
    std::cout << "=== Пациенты ===\n";
    for (const Patient& patient : hospital.getPatients())
        std::cout << patient.getFullInfo()
                  << "Палата: "
                  << (hospital.getWardNumberOfPatient(patient.getId()) == 0
                      ? "не назначена"
                      : std::to_string(hospital.getWardNumberOfPatient(patient.getId())))
                  << "\n\n";
    std::cout << "=== Палаты ===\n";
    for (const Ward& ward : hospital.getWards())
        std::cout << ward.getFullInfo() << '\n';

    return 0;
}
