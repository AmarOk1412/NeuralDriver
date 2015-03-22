#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <iostream>

#include "Neuron.h"

class Network
{
  public:
    Network(std::vector<int> const sNetwork);
    ~Network();
    double costfunction(std::vector<double> const& X, std::vector<double> const& ol, 
    																									std::vector<double> const& y);
    std::vector<double> forwardProp(std::vector<double> const& input);
    void backprop(std::vector<double> X, std::vector<double> y);
    
    void print() const;
    
    //TODO operator = & operator << add const
    
  private:
    std::vector<std::vector<Neuron>> _network;
    double _lambda;
};

#endif
