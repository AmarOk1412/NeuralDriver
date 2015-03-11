#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>

class Neuron
{
  public:
    Neuron(const int nbInput);
    ~Neuron();
    Neuron(const Neuron& neuron);
    double calcOutput(std::vector<double> const& input);
    void adjust(const double error);
    
    const double getBiase() const;
    const std::vector<double>& getThetas() const;
    
    Neuron& operator=(const Neuron& o);
    
  private:
    double thetaTX(const std::vector<double>& input);
    void init(int length, double epsilon);
    std::vector<double> _input;
    std::vector<double> _theta;
    double _biase;
    double _learningRate;
    double _output;
};

std::ostream& operator<<(std::ostream& out, Neuron const& n);

#endif
