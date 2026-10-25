#include "../Library/include/Doctor.h"
#include "../Library/include/MedicalInstitution.h"
#include "../Library/include/Nurse.h"
#include "../Library/include/Patient.h"
#include "../Library/include/Ward.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

/** 
* @brief Пустое имя или неположительный возраст отклоняются 
*/
TEST(HumanTests, Constructor_InvalidData_Throws)
{
    EXPECT_THROW(Patient("", "Иванов", 30), std::invalid_argument);
    EXPECT_THROW(Patient("Иван", "Иванов", 0), std::invalid_argument);
}

/** 
* @brief Каждый новый человек получает свой ID 
*/
TEST(HumanTests, Id_DifferentPeople_AreUnique)
{
    const Patient first("Иван", "Иванов", 30);
    const Patient second("Иван", "Иванов", 30);
    EXPECT_NE(first.getId(), second.getId());
}

/**
* @brief Обход коллекции базового класса вызывает методы наследников 
*/
TEST(HumanTests, Polymorphism_CollectionOfBase_UsesDerivedMethods)
{
    const Doctor doctor("Анна", "Иванова", 38,
        DoctorSpecialization::Cardiologist, "Кардиология", 12);
    const Nurse nurse("Мария", "Смирнова", 28,
        NurseSpecialization::Ward, "Кардиология", 5);
    const Patient patient("Иван", "Кузнецов", 50, "Стенокардия");

    EXPECT_EQ("Врач", doctor.getRole());
    EXPECT_EQ("Медсестра / медбрат", nurse.getRole());
    EXPECT_EQ("Пациент", patient.getRole());
    EXPECT_NE(std::string::npos, doctor.getFullInfo().find("Кардиолог"));
    EXPECT_NE(std::string::npos, patient.getFullInfo().find("Стенокардия"));
}

/** 
* @brief Врач возвращает свою специализацию и признак врача 
*/
TEST(MedicalWorkerTests, Doctor_Specialization_IsReturned)
{
    const Doctor doctor("Олег", "Петров", 45, DoctorSpecialization::Surgeon, "Хирургия", 20);
    EXPECT_EQ(DoctorSpecialization::Surgeon, doctor.getSpecialization());
    EXPECT_EQ("Хирург", doctor.getSpecializationName());
    EXPECT_EQ("Хирургия", doctor.getDepartment());
    EXPECT_EQ(20, doctor.getExperience());
    EXPECT_TRUE(doctor.isDoctor());
}

/** 
* @brief Медсестра не является врачом 
*/
TEST(MedicalWorkerTests, Nurse_IsNotDoctor)
{
    const Nurse nurse("Мария", "Смирнова", 28, NurseSpecialization::Procedural, "Терапия", 3);
    EXPECT_EQ("Процедурная", nurse.getSpecializationName());
    EXPECT_FALSE(nurse.isDoctor());
}

/** 
* @brief Стаж больше возраста и пустое отделение отклоняются
*/
TEST(MedicalWorkerTests, Constructor_InvalidWorkData_Throws)
{
    EXPECT_THROW(Doctor("Олег", "Петров", 30, DoctorSpecialization::Surgeon, "Хирургия", 31),
                 std::invalid_argument);
    EXPECT_THROW(Nurse("Мария", "Смирнова", 28, NurseSpecialization::Ward, "", 1),
                 std::invalid_argument);
}

/** 
* @brief Поиск работает по отделению и специализации 
*/
TEST(MedicalWorkerTests, Matches_DepartmentAndSpecialization)
{
    const Doctor doctor("Анна", "Иванова", 38, DoctorSpecialization::Cardiologist, "Кардиология", 12);
    EXPECT_TRUE(doctor.matches("Кардиолог"));
    EXPECT_TRUE(doctor.matches("Кардиология"));
    EXPECT_FALSE(doctor.matches("хирург"));
}

/** 
* @brief Значение Count не является специализацией 
*/
TEST(MedicalWorkerTests, ToString_Count_Throws)
{
    EXPECT_THROW(toString(DoctorSpecialization::Count), std::invalid_argument);
    EXPECT_THROW(toString(NurseSpecialization::Count), std::invalid_argument);
}

/** 
* @brief Назначение медработника не дублируется и снимается 
*/
TEST(PatientTests, AddAndRemoveWorker)
{
    Patient patient("Иван", "Кузнецов", 50);
    EXPECT_TRUE(patient.addWorker(7));
    EXPECT_FALSE(patient.addWorker(7));
    EXPECT_TRUE(patient.isObservedBy(7));
    EXPECT_EQ(1u, patient.getWorkerIds().size());

    EXPECT_TRUE(patient.removeWorker(7));
    EXPECT_FALSE(patient.removeWorker(7));
    EXPECT_FALSE(patient.isObservedBy(7));
}

/** 
* @brief Пустой диагноз выводится как «не указан» 
*/
TEST(PatientTests, FullInfo_EmptyDiagnosis)
{
    const Patient patient("Иван", "Кузнецов", 50);
    EXPECT_EQ("", patient.getDiagnosis());
    EXPECT_NE(std::string::npos, patient.getFullInfo().find("Диагноз: не указан"));
}


/** 
* @brief Пациенты добавляются, пока есть места, затем исключение
*/
TEST(WardTests, AddPatient_UntilFull_ThenThrows)
{
    Ward ward(101, 1);
    EXPECT_TRUE(ward.addPatient(1));
    EXPECT_FALSE(ward.addPatient(1));
    EXPECT_TRUE(ward.isFull());
    EXPECT_THROW(ward.addPatient(2), std::runtime_error);
}

/** 
* @brief Освобождение места
*/
TEST(WardTests, RemovePatient_FreesPlace)
{
    Ward ward(101, 2);
    ward.addPatient(1);
    EXPECT_TRUE(ward.removePatient(1));
    EXPECT_FALSE(ward.removePatient(1));
    EXPECT_EQ(0u, ward.getOccupancy());
}

/**
* @brief Некорректные номер и вместимость отклоняются 
*/
TEST(WardTests, Constructor_InvalidData_Throws)
{
    EXPECT_THROW(Ward(0, 2), std::invalid_argument);
    EXPECT_THROW(Ward(101, 0), std::invalid_argument);
}

/** 
* @brief Краткая информация содержит номер, места и занятость 
*/
TEST(WardTests, FullInfo_Format)
{
    Ward ward(101, 2);
    ward.addPatient(5);
    EXPECT_EQ("Палата 101, мест: 2, занято: 1", ward.getFullInfo());
}

/**
 * @brief Тестовая больница
 */
class MedicalInstitutionTests : public ::testing::Test
{
protected:
    MedicalInstitution hospital{"Больница", "ул. Центральная, 10"};
    int doctorId = 0;
    int nurseId = 0;
    int ivanId = 0;
    int petrId = 0;

    void SetUp() override
    {
        doctorId = hospital.addWorker(Doctor("Анна", "Иванова", 38,
            DoctorSpecialization::Cardiologist, "Кардиология", 12));
        nurseId = hospital.addWorker(Nurse("Мария", "Смирнова", 28,
            NurseSpecialization::Ward, "Кардиология", 5));
        ivanId = hospital.addPatient(Patient("Иван", "Кузнецов", 50, "Стенокардия"));
        petrId = hospital.addPatient(Patient("Пётр", "Соколов", 42));
        hospital.addWard(Ward(101, 1));
        hospital.addWard(Ward(102, 2));
    }
};

/** 
* @brief Пустые название или адрес отклоняются 
*/
TEST(MedicalInstitutionConstructorTests, EmptyNameOrAddress_Throws)
{
    EXPECT_THROW(MedicalInstitution("", "адрес"), std::invalid_argument);
    EXPECT_THROW(MedicalInstitution("Больница", ""), std::invalid_argument);
}

/** 
* @brief Задания 1 и 3: сведения обо всех медработниках и пациентах 
*/
TEST_F(MedicalInstitutionTests, GetAll_ReturnsEveryone)
{
    EXPECT_EQ(2u, hospital.getDoctors().size() + hospital.getNurses().size());
    EXPECT_EQ(2, hospital.getPatients().size());
    EXPECT_EQ("Кузнецов Иван", hospital.getPatient(ivanId).getFullName());
    EXPECT_EQ("Врач", hospital.getWorker(doctorId).getRole());
}

/** 
* @brief Задания 2 и 4: назначения видны с обеих сторон 
*/
TEST_F(MedicalInstitutionTests, Assign_WorkersAndPatientsAreLinked)
{
    EXPECT_TRUE(hospital.assignWorker(doctorId, ivanId));
    EXPECT_FALSE(hospital.assignWorker(doctorId, ivanId));
    hospital.assignWorker(nurseId, ivanId);
    hospital.assignWorker(doctorId, petrId);

    EXPECT_EQ(2, hospital.getWorkersOfPatient(ivanId).size());
    EXPECT_EQ(2, hospital.getPatientsOfWorker(doctorId).size());
    EXPECT_EQ(1, hospital.getPatientsOfWorker(nurseId).size());

    EXPECT_TRUE(hospital.unassignWorker(nurseId, ivanId));
    EXPECT_EQ(0, hospital.getPatientsOfWorker(nurseId).size());
}

/** 
* @brief Неизвестный ID приводит к исключению
*/
TEST_F(MedicalInstitutionTests, UnknownId_Throws)
{
    EXPECT_THROW(hospital.getPatient(-1), std::invalid_argument);
    EXPECT_THROW(hospital.getWorker(-1), std::invalid_argument);
    EXPECT_THROW(hospital.getWard(999), std::invalid_argument);
    EXPECT_THROW(hospital.assignWorker(-1, ivanId), std::invalid_argument);
}

/** 
* @brief Задание 5: размещение, перевод и освобождение места 
*/
TEST_F(MedicalInstitutionTests, PlacePatient_MovesBetweenWards)
{
    EXPECT_TRUE(hospital.placePatient(ivanId, 101));
    EXPECT_EQ(101, hospital.getWardNumberOfPatient(ivanId));
    EXPECT_FALSE(hospital.placePatient(ivanId, 101));

    EXPECT_TRUE(hospital.placePatient(ivanId, 102));
    EXPECT_EQ(102, hospital.getWardNumberOfPatient(ivanId));
    EXPECT_EQ(0, hospital.getWard(101).getOccupancy());

    EXPECT_TRUE(hospital.releasePatient(ivanId));
    EXPECT_FALSE(hospital.releasePatient(ivanId));
    EXPECT_EQ(0, hospital.getWardNumberOfPatient(ivanId));
    EXPECT_EQ(2, hospital.getPatientsWithoutWard().size());
}

/** 
* @brief В полную палату не перевести; прежняя палата сохраняется 
*/
TEST_F(MedicalInstitutionTests, PlacePatient_FullWard_KeepsOldWard)
{
    hospital.placePatient(ivanId, 101);
    hospital.placePatient(petrId, 102);
    EXPECT_THROW(hospital.placePatient(petrId, 101), std::runtime_error);
    EXPECT_EQ(102, hospital.getWardNumberOfPatient(petrId));
}

/** 
* @brief Поиск врачей не возвращает медсестёр 
*/
TEST_F(MedicalInstitutionTests, Search_FiltersCorrectly)
{
    EXPECT_EQ(2, hospital.searchWorkers("Кардиология").size());
    EXPECT_EQ(1, hospital.searchDoctors("Кардиология").size());
    EXPECT_EQ(1, hospital.searchPatients("Стенокардия").size());
    EXPECT_EQ(0, hospital.searchPatients("Несуществующий диагноз").size());
}

/** 
* @brief Дубликаты отклоняются 
*/
TEST_F(MedicalInstitutionTests, AddDuplicate_Throws)
{
    const Patient copy = hospital.getPatient(ivanId);
    EXPECT_THROW(hospital.addPatient(copy), std::invalid_argument);
    EXPECT_THROW(hospital.addWard(Ward(101, 3)), std::invalid_argument);
    EXPECT_THROW(hospital.getWorker(-1), std::invalid_argument);
}

