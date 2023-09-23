#pragma once
#include <exception>
#include <string>

namespace Algebra
{
    class AlgebraError : public std::exception
    {
    private:
        std::string _message;

    public:
        AlgebraError(std::string message);
        const char *what() const throw();

        static AlgebraError *MatrixDimensionsMismatch();
        static AlgebraError *MatrixElementOutOfBounds();
        static AlgebraError *MatrixNotSquare();
        static AlgebraError *MatrixInvalidDimensions();
        static AlgebraError *MatrixInvalidOperation();
        static AlgebraError *MatrixInvalidScalar();
        static AlgebraError *MatrixInvalidCrossProduct();
        static AlgebraError *MatrixInvalidDeterminant();
        static AlgebraError *MatrixInvalidTranspose();
        static AlgebraError *MatrixDivisionByZero();
    };
}
