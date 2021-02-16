#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(size_t perceptronCounts, size_t inputsCount)
    : perceptronCounts(perceptronCounts), inputsCount(inputsCount)
{
    for (size_t i = 0; i < perceptronCounts; i++)
        perceptrons.push_back(Matrix<double>(1,inputsCount));

    for (auto & perceptron : perceptrons)
    {
        for (size_t j = 0; j < inputsCount; j++)
            perceptron(0,j) = (double)rand() / RAND_MAX;
    }
}

void NeuralNetwork::train(const std::string &path, size_t rounds)
{
    std::ifstream in(path);

    size_t countOfExamples;

    in >> countOfExamples;


    for (size_t i = 0; i < countOfExamples; i++)
    {

        Matrix<double> example(1,inputsCount);

        for (size_t j = 0; j < inputsCount; j++)
        {
            double weight;
            in >> weight;
            example(0,j) = weight;
        }

        std::vector<double> goals(perceptronCounts);

        for (size_t i = 0; i < perceptronCounts; i++)
        {
            in >> goals[i];
        }

        for (size_t round = 0; round < rounds; round++)
        {
            double errorPerRound = 0;
            for (size_t i = 0; i < perceptronCounts; i++)
         {
             double prediction = perceptrons[i].scalarProduct(example);
             errorPerRound += pow(prediction - goals[i],2);
             gradientCorrection(perceptrons[i], prediction, goals[i], example);
         }
            errors.push_back(errorPerRound);
        }
    }
    in.close();
}

void NeuralNetwork::gradientCorrection(Matrix<double> &weigths, double prediction, double goal, Matrix<double> const & example)
{
    double error = pow(goal - prediction, 2);
    double delta = prediction - goal;
    Matrix<double> input(example);
    auto x = input * delta;
    x *= 0.1;
    weigths = weigths - x;
}

void NeuralNetwork::saveWeigths(std::string const & path)
{
    std::ofstream out(path);
    for (auto & x : perceptrons)
    {
        for (size_t i = 0; i < x.dim().first; i++)
        {
            for (size_t j = 0; j < x.dim().second; j++)
                out << x(i,j) << "\t";
            out << std::endl;
        }
        out << std::endl;
    }
}

std::vector<double> NeuralNetwork::predict(std::vector<double> input)
{
    Matrix<double> inputs(1,input.size());
    for (size_t i = 0; i < input.size(); i++)
        inputs(0,i) = input[i];

    std::vector<double> results;

    for (size_t i = 0; i < perceptronCounts; i++)
    {
        double net = perceptrons[i].scalarProduct(inputs);
        results.push_back(sigmaidal(net));
    }

    return results;
}

double NeuralNetwork::sigmaidal(double net)
{
    return 1/(1+exp(-net));
}

void NeuralNetwork::saveErrors(std::string const &path)
{
    std::ofstream out(path);
    for (auto x : errors)
        out << x << std::endl;
    out.close();
}
