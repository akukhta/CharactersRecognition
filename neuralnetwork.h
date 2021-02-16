#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"

class NeuralNetwork
{
public:
    NeuralNetwork(size_t perceptronCounts, size_t inputsCount);
    void train(std::string const & path, size_t rounds);
    std::vector<double> predict(std::vector<double> input);
    void saveWeigths(std::string const & path = "weights.txt");
    void saveErrors(std::string const &path = "errors.txt");

private:
    std::vector<Matrix<double>> perceptrons;
    size_t perceptronCounts, inputsCount;

    template<class T, typename std::enable_if_t<std::is_fundamental<T>::value>* = nullptr>
    T convert(std::vector<char> buffer)
    {
        return *reinterpret_cast<T*>(buffer.data(), buffer.data() + sizeof(T));
    }

    void gradientCorrection(Matrix<double> &weigths, double prediction, double goal, Matrix<double> const & example);
    double sigmaidal(double net);
    const double alpha = 0.6;
    std::vector<double> errors;
};



