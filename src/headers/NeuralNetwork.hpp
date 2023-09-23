#pragma once
#include "NeuralNetworkLayer.hpp"

namespace Algebra
{
    class NeuralNetwork
    {
    private:
        std::vector<NeuralNetworkLayer> _layers;
        size_t _inputSize;
        size_t _outputSize;
        ActivationFunction _activationFunction;

    public:
        NeuralNetwork(std::vector<double> topology, ActivationFunction activationFunction);

        std::vector<double> feedForward(std::vector<double> inputs);
        void backPropagation(std::vector<double> inputs, std::vector<double> targets, double learningRate = 0.1);
    };
}