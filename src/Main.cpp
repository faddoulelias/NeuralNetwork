#include <iostream>
#include <Matrix.hpp>
#include <assert.h>
#include <chrono>
#include <math.h>
#include <NeuralNetwork.hpp>

using namespace Algebra;

void testMatrixCreation()
{
    Matrix a = Matrix(2, 3);
    assert(a.getDimensions().M == 2);
    assert(a.getDimensions().N == 3);

    Matrix b = Matrix({{1, 2, 3},
                       {4, 5, 6}});
    assert(b.getDimensions().M == 2);
    assert(b.getDimensions().N == 3);

    Matrix c = Matrix({{1, 2, 3},
                       {4, 5, 6},
                       {7, 8, 9}});
    assert(c.getDimensions().M == 3);
    assert(c.getDimensions().N == 3);

    assert(a == a);
    assert(b == b);
    assert(c == c);

    assert(a != b);
    assert(a != c);
    assert(b != c);

    Matrix d = Matrix({{1, 2, 3},
                       {4, 5, 6}});

    assert(b == d);
}

void testMatrixAddition()
{
    Matrix a = Matrix({{1, 2, 3},
                       {4, 5, 6}});

    Matrix b = Matrix({{1, 2, 3},
                       {4, 5, 6}});

    Matrix c = Matrix({{2, 4, 6},
                       {8, 10, 12}});

    assert(Matrix::add(a, b) == c);

    assert(a == Matrix({{1, 2, 3},
                        {4, 5, 6}}));
    assert(b == Matrix({{1, 2, 3},
                        {4, 5, 6}}));

    a = a + b;
    assert(a == c);

    a = a - b;
    assert(a == Matrix({{1, 2, 3},
                        {4, 5, 6}}));

    a += b;
    assert(a == c);

    a -= b;
    assert(a == Matrix({{1, 2, 3},
                        {4, 5, 6}}));
}

void testApply()
{
    Matrix a = Matrix({{1, 2, 3},
                       {4, 5, 6}});

    Matrix b = Matrix({{2, 4, 6},
                       {8, 10, 12}});

    a.apply([](double x)
            { return 2 * x; });

    assert(a == b);

    a.apply([](double x)
            { return x * x; });

    assert(a == Matrix({{4, 16, 36},
                        {64, 100, 144}}));
}

void testScalarMultiplication()
{
    Matrix a = Matrix({{1, 2, 3},
                       {4, 5, 6}});

    Matrix b = Matrix({{2, 4, 6},
                       {8, 10, 12}});

    assert(Matrix::multiply(2, a) == b);

    assert(a == Matrix({{1, 2, 3},
                        {4, 5, 6}}));

    a = a * 2;
    assert(a == b);

    a = a / 2;
    assert(a == Matrix({{1, 2, 3},
                        {4, 5, 6}}));

    a *= 2;
    assert(a == b);

    a /= 2;
    assert(a == Matrix({{1, 2, 3},
                        {4, 5, 6}}));
}

void testCrossProduct()
{
    Matrix a = Matrix({{1, 2, 3},
                       {4, 5, 6}});

    Matrix b = Matrix({{1, 2},
                       {3, 4},
                       {5, 6}});

    Matrix c = Matrix({{22, 28},
                       {49, 64}});

    assert(Matrix::crossProduct(a, b) == c);

    assert(a == Matrix({{1, 2, 3},
                        {4, 5, 6}}));

    assert(b == Matrix({{1, 2},
                        {3, 4},
                        {5, 6}}));

    Matrix g = a * b;
    assert(g == c);

    a *= b;
    assert(a == g);
}

void testTranspose()
{
    Matrix a = Matrix({{1, 2, 3},
                       {4, 5, 6}});

    Matrix b = Matrix({{1, 4},
                       {2, 5},
                       {3, 6}});

    a = a.transposed();

    assert(a == b);
}

void testDeterminant()
{
    Matrix a = Matrix({{1, 2, 3},
                       {4, 5, 6},
                       {7, 8, 9}});

    Matrix b = Matrix({{1, 2},
                       {3, 4}});

    Matrix c = Matrix({{1, 2, 3, 4},
                       {5, 6, 7, 8},
                       {9, 10, 11, 12},
                       {13, 14, 15, 16}});

    Matrix d = Matrix({{1, 2, 4, 5, 6},
                       {7, 8, 9, 10, 11},
                       {12, 13, 41, 15, 16},
                       {17, 18, 19, 20, 21},
                       {22, 23, 24, 25, 62}});

    assert(a.determinant() == 0);
    assert(b.determinant() == -2);
    assert(c.determinant() == 0);
    assert(d.determinant() == -9720);
}

void testVectorize()
{
    Matrix a = Matrix::columnVector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    Matrix b = Matrix::rowVector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    assert(a.getDimensions().M == 10);
    assert(a.getDimensions().N == 1);

    assert(b.getDimensions().M == 1);
    assert(b.getDimensions().N == 10);

    Matrix t_a = a.transposed();
    assert(t_a == b);
    assert(a == Matrix::columnVector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));

    a = a.transposed();
    assert(a == b);
    assert(a == t_a);

    Matrix c = Matrix({{1, 2, 3},
                       {4, 5, 6}});
    std::vector<double> d = c.toVector();
    for (size_t i = 0; i < d.size(); i++)
    {
        assert(d[i] == i + 1);
    }
}

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double sigmoidDerivative(double x)
{
    return x * (1 - x);
}

void testNeuralNetwork()
{
    srand(time(NULL));

    NeuralNetwork a = NeuralNetwork({2, 3, 2}, {sigmoid, sigmoidDerivative});

    std::vector<double> inputs = {1, 0};

    // Training
    // for (size_t i = 0; i < 10; i++)
    // {
    //     std::vector<double> targets = {1};
    //     a.backPropagation(inputs, targets, 0.1);

    //     targets = {0};
    //     a.backPropagation(inputs, targets, 0.1);
    // }

    // Testing
    std::vector<double> output = a.feedForward(inputs);
    std::cout << "Output: " << output[0] << std::endl;
    std::cout << "Output: " << output[1] << std::endl;
}

int main()
{

    Matrix a = Matrix({{1, 2, 3},
                       {4, 5, 6}});

    testMatrixCreation();
    testMatrixAddition();
    testApply();
    testScalarMultiplication();
    testCrossProduct();
    testTranspose();
    testDeterminant();
    testVectorize();

    testNeuralNetwork();
    return 0;
}
