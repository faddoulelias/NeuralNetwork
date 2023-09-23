#pragma once
#include <string>
#include <functional>

namespace Algebra
{
    typedef std::function<double(double)> MathFunction;

    struct Dimensions
    {
    public:
        size_t M; /*Number of Rows*/
        size_t N; /*Number of Columns*/
    };

    class Matrix
    {
    private:
        double *_matrix;
        Dimensions _dimensions;

    public:
        Matrix(size_t M, size_t N);
        Matrix(Dimensions dimensions);
        Matrix(std::vector<std::vector<double>> matrix);
        Matrix(Dimensions dimensions, double min, double max);
        Matrix(const Matrix &matrix);

        Matrix &Identity(size_t M);
        Matrix &Zero(Dimensions dimensions);

        static Matrix &columnVector(std::vector<double> vector);
        static Matrix &rowVector(std::vector<double> vector);
        std::vector<double> toVector() const;
        std::vector<std::vector<double>> to2DVector() const;
        std::vector<double> getRow(size_t i) const;
        std::vector<double> getColumn(size_t j) const;

        static Matrix &identity(size_t M);
        static Matrix &zero(Dimensions dimensions);

        Matrix &operator=(const Matrix &);
        bool operator==(const Matrix &matrix) const;
        bool operator!=(const Matrix &matrix) const;
        bool equals(const Matrix &matrix) const;
        ~Matrix();

        Dimensions getDimensions() const;
        double getElement(size_t i, size_t j) const;
        void setElement(size_t i, size_t j, double value);
        void apply(const MathFunction &f);
        static Matrix &add(const Matrix &A, const Matrix &B);
        static Matrix &multiply(double scalar, const Matrix &matrix);
        static Matrix &multiply(const Matrix &A, const Matrix &B);
        static Matrix &hadamard(const Matrix &A, const Matrix &B);
        double sum() const;
        Matrix &transposed() const;

        double determinant();
        std::string toString(int digitLimit = 5) const;

        Matrix &operator+(const Matrix &matrix) const;
        Matrix &operator-(const Matrix &matrix) const;
        Matrix &operator*(const Matrix &matrix) const;
        Matrix &operator*(double scalar) const;
        Matrix &operator/(double scalar) const;

        Matrix &operator+=(const Matrix &matrix);
        Matrix &operator-=(const Matrix &matrix);
        Matrix &operator*=(const Matrix &matrix);
        Matrix &operator*=(double scalar);
        Matrix &operator/=(double scalar);
    };
};
