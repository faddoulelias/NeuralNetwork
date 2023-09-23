#include <NeuralNetworkLayer.hpp>

using namespace Algebra;

NeuralNetworkLayer::NeuralNetworkLayer(size_t numberOfNeurons, size_t numberOfInputs, ActivationFunction activationFunction) : _numberOfNeurons(numberOfNeurons),
                                                                                                                               _numberOfInputs(numberOfInputs),
                                                                                                                               _activationFunction(activationFunction),
                                                                                                                               _weights({numberOfNeurons, numberOfInputs}, -1, 1),
                                                                                                                               _biases({numberOfNeurons, 1}, -1, 1),
                                                                                                                               _outputBuffer({numberOfNeurons, 1}, -1, 1)
{
}

size_t NeuralNetworkLayer::getNumberOfNeurons() const
{
    return _numberOfNeurons;
}

size_t NeuralNetworkLayer::getNumberOfInputs() const
{
    return _numberOfInputs;
}

Matrix const &Algebra::NeuralNetworkLayer::getOutput() const
{
    return this->_outputBuffer;
}

Matrix &NeuralNetworkLayer::getWeights()
{
    return this->_weights;
}

Matrix &NeuralNetworkLayer::getBiases()
{
    return this->_biases;
}

ActivationFunction NeuralNetworkLayer::getActivationFunction() const
{
    return this->_activationFunction;
}

void NeuralNetworkLayer::setWeights(const Matrix &weights)
{
    this->_weights = weights;
}

void NeuralNetworkLayer::setBiases(const Matrix &biases)
{
    this->_biases = biases;
}

Matrix &NeuralNetworkLayer::feed(const Matrix &inputs)
{
    this->_outputBuffer = Matrix::add(Matrix::multiply(this->_weights, inputs), this->_biases);
    this->_outputBuffer.apply(this->_activationFunction.function);

    return this->_outputBuffer;
}

double cost(const Matrix &output, const Matrix &targets)
{
    Matrix error = targets - output;
    error.apply([](double x)
                { return x * x; });

    return error.sum();
}
