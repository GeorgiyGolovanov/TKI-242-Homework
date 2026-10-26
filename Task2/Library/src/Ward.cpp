#include "../include/Ward.h"
#include <algorithm>
#include <stdexcept>

Ward::Ward(const int number, const int capacity)
    : number(number), capacity(capacity)
{
    if (number <= 0 || capacity <= 0)
        throw std::invalid_argument("Номер палаты и число мест должны быть больше 0");
}

int Ward::getNumber() const
{
    return number;
}

int Ward::getCapacity() const
{
    return capacity;
}

std::size_t Ward::getOccupancy() const
{
    return patientIds.size();
}

const std::vector<int>& Ward::getPatientIds() const
{
    return patientIds;
}

bool Ward::contains(const int patientId) const
{
    return std::find(patientIds.begin(), patientIds.end(), patientId) != patientIds.end();
}

bool Ward::isFull() const
{
    return patientIds.size() >= static_cast<std::size_t>(capacity);
}

bool Ward::addPatient(const int patientId)
{
    if (contains(patientId))
        return false;
    if (isFull())
        throw std::runtime_error("В палате " + std::to_string(number) + " нет свободных мест");
    patientIds.push_back(patientId);
    return true;
}

bool Ward::removePatient(const int patientId)
{
    const auto it = std::find(patientIds.begin(), patientIds.end(), patientId);
    if (it == patientIds.end())
        return false;
    patientIds.erase(it);
    return true;
}

std::string Ward::getFullInfo() const
{
    return "Палата " + std::to_string(number)
        + ", мест: " + std::to_string(capacity)
        + ", занято: " + std::to_string(patientIds.size());
}
