#include <NeuralNetworkLayer.hpp>

using namespace Algebra;

NeuralNetworkLayer::NeuralNetworkLayer(size_t numberOfNeurons, size_t numberOfInputs, ActivationFunction activationFunction) : _numberOfNeurons(numberOfNeurons),
                                                                                                                               _numberOfInputs(numberOfInputs),
                                                                                                                               _activationFunction(activationFunction),
                                                                                                                               _weights({numberOfNeurons, numberOfInputs}, -1, 1),
                                                                                                                               _biases({numberOfNeurons, 1}, -1, 1)
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

Matrix &NeuralNetworkLayer::getWeights()
{
    return this->_weights;
}

Matrix &NeuralNetworkLayer::getBiases()
{
    return this->_biases;
}

ActivationFunction Algebra::NeuralNetworkLayer::getActivationFunction() const
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

Matrix &NeuralNetworkLayer::feedForward(const Matrix &inputs)
{
    Matrix *output = new Matrix(this->_weights * inputs + this->_biases);
    output->apply(this->_activationFunction.function);

    return *output;
}

Matrix NeuralNetworkLayer::backPropagation(const Matrix &inputs, const Matrix &targets, double learningRate)
{
    Matrix output = this->feedForward(inputs);
    Matrix error = targets - output;

    Matrix gradient = output;
    gradient.apply(this->_activationFunction.derivative);
    gradient *= error;
    gradient *= learningRate;

    Matrix delta = gradient * inputs.transposed();

    this->_weights += delta;
    this->_biases += gradient;

    return this->_weights.transposed() * error;
}
