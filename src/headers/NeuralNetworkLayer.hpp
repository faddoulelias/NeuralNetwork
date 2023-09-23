#pragma once
#include "Matrix.hpp"

namespace Algebra
{
    struct ActivationFunction
    {
        MathFunction function;
        MathFunction derivative;
    };

    class NeuralNetworkLayer
    {
    private:
        size_t _numberOfNeurons;
        size_t _numberOfInputs;
        ActivationFunction _activationFunction;
        Matrix _weights;
        Matrix _biases;
        Matrix _outputBuffer;

    public:
        NeuralNetworkLayer(size_t numberOfNeurons, size_t numberOfInputs, ActivationFunction activationFunction);

        size_t getNumberOfNeurons() const;
        size_t getNumberOfInputs() const;
        Matrix const &getOutput() const;

        Matrix &getWeights();
        Matrix &getBiases();
        ActivationFunction getActivationFunction() const;

        void setWeights(const Matrix &weights);
        void setBiases(const Matrix &biases);

        Matrix &feed(const Matrix &inputs);
    };
}
