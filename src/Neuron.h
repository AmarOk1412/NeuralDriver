#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Neuron
{
  public:
    Neuron();
    ~Neuron();
    Neuron( const Neuron& neuron);
    double calcOutput(const std::vector<double> input);
    void adjust(const double error);
    
  private:
    std::vector<double> input;
    std::vector<double> weights;
    double biase;
    double learningRate;
    double output;
};

#endif
