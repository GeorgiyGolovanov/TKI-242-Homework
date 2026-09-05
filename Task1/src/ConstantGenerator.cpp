#include "../include/ConstantGenerator.h"

miit::algebra::ConstantGenerator::ConstantGenerator(const int value)
{
    this->value = value;
}

int miit::algebra::ConstantGenerator::generate()
{
    return this->value;
}
