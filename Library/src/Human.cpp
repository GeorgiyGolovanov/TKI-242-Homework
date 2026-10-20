#include "../include/Human.h"
#include <stdexcept>

namespace
{
    /**
     * @brief Выдать следующий свободный идентификатор
     * @return Идентификатор: 1, 2, 3...
     */
    int nextId()
    {
        static int counter = 0;
        return ++counter;
    }
}

Human::Human(const std::string& name,
             const std::string& surname,
             const int age,
             const std::string& patronymic,
             const std::string& phone,
             const std::string& mail)
    : id(nextId()),
      name(name),
      surname(surname),
      patronymic(patronymic),
      age(age),
      phone(phone),
      mail(mail)
{
    if (this->name.empty() || this->surname.empty() || age <= 0)
        throw std::invalid_argument("Поля имя, фамилия и возраст обязательны");
}

int Human::getId() const
{
    return id;
}

const std::string& Human::getName() const
{
    return name;
}

const std::string& Human::getSurname() const
{
    return surname;
}

const std::string& Human::getPatronymic() const
{
    return patronymic;
}

int Human::getAge() const
{
    return age;
}

const std::string& Human::getPhone() const
{
    return phone;
}

const std::string& Human::getMail() const
{
    return mail;
}

std::string Human::getFullName() const
{
    return surname + " " + name + (patronymic.empty() ? "" : " " + patronymic);
}

std::string Human::getFullInfo() const
{
    return "ID: " + std::to_string(id)
        + "\nКатегория: " + getRole()
        + "\nФИО: " + getFullName()
        + "\nВозраст: " + std::to_string(age)
        + "\nТелефон: " + (phone.empty() ? "не указан" : phone)
        + "\nEmail: " + (mail.empty() ? "не указан" : mail)
        + "\n";
}

bool Human::matches(const std::string& query) const
{
    return getFullName().find(query) != std::string::npos
        || phone.find(query) != std::string::npos
        || mail.find(query) != std::string::npos
        || std::to_string(id) == query;
}
