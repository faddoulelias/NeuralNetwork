#include <AlgebraErrors.hpp>

using namespace Algebra;

AlgebraError::AlgebraError(std::string message) : _message(message)
{
}

const char *AlgebraError::what() const throw()
{
    return this->_message.c_str();
}

AlgebraError *AlgebraError::MatrixDimensionsMismatch()
{
    return new AlgebraError("Matrix dimensions mismatch");
}

AlgebraError *AlgebraError::MatrixElementOutOfBounds()
{
    return new AlgebraError("Matrix element out of bounds");
}

AlgebraError *AlgebraError::MatrixNotSquare()
{
    return new AlgebraError("Matrix is not square");
}

AlgebraError *AlgebraError::MatrixInvalidDimensions()
{
    return new AlgebraError("Matrix has invalid dimensions");
}

AlgebraError *AlgebraError::MatrixInvalidOperation()
{
    return new AlgebraError("Matrix has invalid operation");
}

AlgebraError *AlgebraError::MatrixInvalidScalar()
{
    return new AlgebraError("Matrix has invalid scalar");
}

AlgebraError *AlgebraError::MatrixInvalidCrossProduct()
{
    return new AlgebraError("Matrix has invalid cross product");
}

AlgebraError *AlgebraError::MatrixInvalidDeterminant()
{
    return new AlgebraError("Matrix has invalid determinant");
}

AlgebraError *AlgebraError::MatrixInvalidTranspose()
{
    return new AlgebraError("Matrix has invalid transpose");
}

AlgebraError *AlgebraError::MatrixDivisionByZero()
{
    return new AlgebraError("Matrix division by zero");
}
