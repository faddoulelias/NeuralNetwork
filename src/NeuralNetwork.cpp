#include "NeuralNetwork.hpp"
#include <iostream>

using namespace Algebra;

Algebra::NeuralNetwork::NeuralNetwork(std::vector<double> topology, ActivationFunction activationFunction)
{
    for (size_t i = 0; i < topology.size() - 1; i++)
    {
        _layers.push_back(NeuralNetworkLayer(topology[i + 1], topology[i], activationFunction));
    }

    _inputSize = topology[0];
    _outputSize = topology[topology.size() - 1];
}

std::vector<double> Algebra::NeuralNetwork::feedForward(std::vector<double> inputs)
{
    Matrix input = Matrix::columnVector(inputs);

    for (size_t i = 0; i < _layers.size(); i++)
    {
        input = _layers[i].feed(input);
    }

    return input.toVector();
}

void NeuralNetwork::backPropagation(std::vector<double> inputs, std::vector<double> targets, double learningRate)
{
}