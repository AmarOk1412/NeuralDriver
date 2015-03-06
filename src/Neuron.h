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
    double thetaTX(const std::vector<double>& input);
    void init(int length, double epsilon);
    std::vector<double> _input;
    std::vector<double> _theta;
    double _biase;
    double _learningRate;
    double _output;
};

#endif
