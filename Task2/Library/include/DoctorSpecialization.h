#pragma once

#include <string>

/**
 * @brief Специализации врача
 */
enum class DoctorSpecialization
{
    Therapist,               // Терапевт
    Cardiologist,            // Кардиолог
    Neurologist,             // Невролог
    Neurosurgeon,            // Нейрохирург
    Surgeon,                 // Хирург
    CardiovascularSurgeon,   // Сердечно-сосудистый хирург
    Traumatologist,          // Травматолог
    Orthopedist,             // Ортопед
    Pediatrician,            // Педиатр
    Neonatologist,           // Неонатолог
    Gynecologist,            // Гинеколог
    Obstetrician,            // Акушер
    Urologist,               // Уролог
    Dermatologist,           // Дерматолог
    Ophthalmologist,         // Офтальмолог
    Otolaryngologist,        // ЛОР
    Gastroenterologist,      // Гастроэнтеролог
    Hepatologist,            // Гепатолог
    Pulmonologist,           // Пульмонолог
    Endocrinologist,         // Эндокринолог
    Nephrologist,            // Нефролог
    Rheumatologist,          // Ревматолог
    Hematologist,            // Гематолог
    Oncologist,              // Онколог
    InfectiousDiseaseDoctor, // Инфекционист
    Allergist,               // Аллерголог
    Psychiatrist,            // Психиатр
    Anesthesiologist,        // Анестезиолог
    Resuscitator,            // Реаниматолог
    EmergencyDoctor,         // Врач скорой помощи
    Dentist,                 // Стоматолог
    DentalSurgeon,           // Стоматолог-хирург
    Orthodontist,            // Ортодонт
    Pathologist,             // Патологоанатом
    Geneticist,              // Генетик
    RehabilitationDoctor,    // Врач-реабилитолог
    Epidemiologist,          // Эпидемиолог
    Count                    // Количество специализаций
};

/**
 * @brief Получить название специализации врача
 * @param value Специализация врача
 * @return Название на русском языке
 */
std::string toString(const DoctorSpecialization value);
