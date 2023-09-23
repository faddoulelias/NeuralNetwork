#include <AlgebraErrors.hpp>
#include <Matrix.hpp>
#include <string>
#include <utility>
#include <cmath>

using namespace Algebra;

Matrix::Matrix(size_t M, size_t N)
{
    if (M == 0 || N == 0)
        throw AlgebraError::MatrixInvalidDimensions();

    this->_dimensions.M = M;
    this->_dimensions.N = N;
    this->_matrix = new double[M * N];
}

Matrix::Matrix(Dimensions dimensions)
{
    if (dimensions.M == 0 || dimensions.N == 0)
        throw AlgebraError::MatrixInvalidDimensions();

    this->_dimensions = dimensions;
    this->_matrix = new double[dimensions.M * dimensions.N];
}

Matrix::Matrix(const Matrix &matrix)
{
    if (matrix._dimensions.M == 0 || matrix._dimensions.N == 0)
        throw AlgebraError::MatrixInvalidDimensions();

    this->_dimensions = matrix._dimensions;
    this->_matrix = new double[this->_dimensions.M * this->_dimensions.N];

    size_t linearSize = this->_dimensions.M * this->_dimensions.N;
    std::copy(matrix._matrix, matrix._matrix + linearSize, this->_matrix);
}

Matrix &Matrix::columnVector(std::vector<double> vector)
{
    Matrix *newMatrix = new Matrix(vector.size(), 1);

    for (size_t i = 0; i < vector.size(); i++)
    {
        newMatrix->setElement(i, 0, vector[i]);
    }

    return *newMatrix;
}

Matrix &Matrix::rowVector(std::vector<double> vector)
{
    Matrix *newMatrix = new Matrix(1, vector.size());

    for (size_t i = 0; i < vector.size(); i++)
    {
        newMatrix->setElement(0, i, vector[i]);
    }

    return *newMatrix;
}

std::vector<double> Matrix::toVector() const
{
    std::vector<double> vector;
    size_t linearSize = this->_dimensions.M * this->_dimensions.N;
    for (size_t i = 0; i < linearSize; i++)
    {
        vector.push_back(this->_matrix[i]);
    }

    return vector;
}

Matrix &Matrix::identity(size_t M)
{
    Matrix *newMatrix = new Matrix(M, M);

    for (size_t i = 0; i < M; i++)
    {
        newMatrix->setElement(i, i, 1);
    }

    return *newMatrix;
}

Matrix &Matrix::zero(Dimensions dimensions)
{
    Matrix *newMatrix = new Matrix(dimensions);
    size_t linearSize = dimensions.M * dimensions.N;
    std::fill(newMatrix->_matrix, newMatrix->_matrix + linearSize, 0);

    return *newMatrix;
}

Matrix::Matrix(std::vector<std::vector<double>> matrix)
{
    for (size_t i = 0; i < matrix.size(); i++)
    {
        if (matrix[i].size() != matrix[0].size())
            throw AlgebraError::MatrixInvalidDimensions();
    }

    this->_dimensions.M = matrix.size();
    this->_dimensions.N = matrix[0].size();
    this->_matrix = new double[this->_dimensions.M * this->_dimensions.N];

    for (size_t i = 0; i < this->_dimensions.M; i++)
    {
        for (size_t j = 0; j < this->_dimensions.N; j++)
        {
            this->_matrix[(i * this->_dimensions.N) + j] = matrix[i][j];
        }
    }
}

Matrix::Matrix(Dimensions dimensions, double min, double max)
{
    if (dimensions.M == 0 || dimensions.N == 0)
        throw AlgebraError::MatrixInvalidDimensions();

    this->_dimensions = dimensions;
    this->_matrix = new double[dimensions.M * dimensions.N];

    size_t linearSize = dimensions.M * dimensions.N;
    for (size_t i = 0; i < linearSize; i++)
    {
        this->_matrix[i] = min + ((double)rand() / RAND_MAX) * (max - min);
    }
}

Matrix &Matrix::operator=(const Matrix &matrix)
{
    if (this != &matrix)
    {
        delete[] this->_matrix;
        this->_dimensions = matrix._dimensions;
        this->_matrix = new double[this->_dimensions.M * this->_dimensions.N];

        size_t linearSize = this->_dimensions.M * this->_dimensions.N;
        std::copy(matrix._matrix, matrix._matrix + linearSize, this->_matrix);
    }

    return *this;
}

bool Matrix::operator==(const Matrix &matrix) const
{
    return this->equals(matrix);
}

bool Matrix::operator!=(const Matrix &matrix) const
{
    return !this->equals(matrix);
}

bool Matrix::equals(const Matrix &matrix) const
{
    if (this->_dimensions.M != matrix._dimensions.M || this->_dimensions.N != matrix._dimensions.N)
    {
        return false;
    }

    size_t linearSize = this->_dimensions.M * this->_dimensions.N;
    for (size_t i = 0; i < linearSize; i++)
    {
        if (this->_matrix[i] != matrix._matrix[i])
        {
            return false;
        }
    }

    return true;
}

Matrix::~Matrix()
{
    delete[] this->_matrix;
}

Dimensions Matrix::getDimensions() const
{
    return this->_dimensions;
}

double Matrix::getElement(size_t i, size_t j) const
{
    return this->_matrix[(i * this->_dimensions.N) + j];
}

void Matrix::setElement(size_t i, size_t j, double value)
{
    this->_matrix[(i * this->_dimensions.N) + j] = value;
}

Matrix &Matrix::add(const Matrix &A, const Matrix &B)
{
    if (A._dimensions.M != B._dimensions.M || A._dimensions.N != B._dimensions.N)
        throw AlgebraError::MatrixDimensionsMismatch();

    Matrix *newMatrix = new Matrix(A);
    size_t linearSize = A._dimensions.M * A._dimensions.N;

    for (size_t i = 0; i < linearSize; i++)
    {
        newMatrix->_matrix[i] = A._matrix[i] + B._matrix[i];
    }

    return *newMatrix;
}

void Matrix::apply(const MathFunction &f)
{
    size_t linearSize = this->_dimensions.M * this->_dimensions.N;
    for (size_t i = 0; i < linearSize; i++)
    {
        this->_matrix[i] = f(this->_matrix[i]);
    }
}

Matrix &Matrix::multiply(double scalar, const Matrix &matrix)
{
    Matrix *newMatrix = new Matrix(matrix);

    newMatrix->apply([&scalar](double x)
                     { return x * scalar; });

    return *newMatrix;
}

Matrix &Matrix::multiply(const Matrix &A, const Matrix &B)
{
    if (A._dimensions.N != B._dimensions.M)
        throw AlgebraError::MatrixInvalidmultiply();

    Matrix *newMatrix = new Matrix(A._dimensions.M, B._dimensions.N);

    for (size_t i = 0; i < A._dimensions.M; i++)
    {
        for (size_t j = 0; j < B._dimensions.N; j++)
        {
            double sum = 0;
            for (size_t k = 0; k < A._dimensions.N; k++)
            {
                sum += A.getElement(i, k) * B.getElement(k, j);
            }
            newMatrix->setElement(i, j, sum);
        }
    }

    return *newMatrix;
}

double Algebra::Matrix::sum() const
{
    double sum = 0;
    size_t linearSize = this->_dimensions.M * this->_dimensions.N;
    for (size_t i = 0; i < linearSize; i++)
    {
        sum += this->_matrix[i];
    }

    return sum;
}

Matrix &Matrix::transposed() const
{
    Matrix *newMatrix = new Matrix(this->_dimensions.N, this->_dimensions.M);

    for (size_t i = 0; i < this->_dimensions.M; i++)
    {
        for (size_t j = 0; j < this->_dimensions.N; j++)
        {
            newMatrix->setElement(j, i, this->getElement(i, j));
        }
    }

    return *newMatrix;
}

double Matrix::determinant()
{
    if (this->_dimensions.M != this->_dimensions.N)
        throw AlgebraError::MatrixInvalidDeterminant();

    if (this->_dimensions.M == 1)
        return this->_matrix[0];

    if (this->_dimensions.M == 2)
        return (this->_matrix[0] * this->_matrix[3]) - (this->_matrix[1] * this->_matrix[2]);

    double determinant = 0;
    for (size_t i = 0; i < this->_dimensions.M; i++)
    {
        Matrix *newMatrix = new Matrix(this->_dimensions.M - 1, this->_dimensions.N - 1);

        for (size_t j = 1; j < this->_dimensions.M; j++)
        {
            for (size_t k = 0; k < this->_dimensions.N; k++)
            {
                if (k < i)
                {
                    newMatrix->setElement(j - 1, k, this->getElement(j, k));
                }
                else if (k > i)
                {
                    newMatrix->setElement(j - 1, k - 1, this->getElement(j, k));
                }
            }
        }

        determinant += pow(-1, i) * this->_matrix[i] * newMatrix->determinant();
        delete newMatrix;
    }

    return determinant;
}

std::string Matrix::toString(int digitLimit) const
{
    std::string result = "";
    size_t linearSize = this->_dimensions.M * this->_dimensions.N;
    for (size_t i = 0; i < linearSize; i++)
    {
        if (this->_matrix[i] > pow(10, digitLimit))
        {
            result += std::string(digitLimit, '+');
        }
        else
        {
            result += std::to_string(this->_matrix[i]).substr(0, digitLimit);
        }
        result += " ";
        if ((i + 1) % this->_dimensions.N == 0)
        {
            result += "\n";
        }
    }

    return result;
}

Matrix &Matrix::operator+(const Matrix &matrix) const
{
    return Matrix::add(*this, matrix);
}

Matrix &Matrix::operator-(const Matrix &matrix) const
{
    return Matrix::add(*this, Matrix::multiply(-1, matrix));
}

Matrix &Matrix::operator*(const Matrix &matrix) const
{
    return Matrix::multiply(*this, matrix);
}

Matrix &Matrix::operator*(double scalar) const
{
    return Matrix::multiply(scalar, *this);
}

Matrix &Matrix::operator/(double scalar) const
{
    if (scalar == 0)
        throw AlgebraError::MatrixDivisionByZero();

    return Matrix::multiply(1 / scalar, *this);
}

Matrix &Matrix::operator+=(const Matrix &matrix)
{
    return *this = *this + matrix;
}

Matrix &Matrix::operator-=(const Matrix &matrix)
{
    return *this = *this - matrix;
}

Matrix &Matrix::operator*=(const Matrix &matrix)
{
    return *this = *this * matrix;
}

Matrix &Matrix::operator*=(double scalar)
{
    return *this = *this * scalar;
}

Matrix &Matrix::operator/=(double scalar)
{
    return *this = *this / scalar;
}
