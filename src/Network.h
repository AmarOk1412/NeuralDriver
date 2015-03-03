#ifndef NETWORK_H
#define NETWORK_H

#include "Neuron.h"

class Network
{
  public:
    Network(std::vector<int> const sNetwork);
    ~Network();
    Network(const Network& network);
    void printNetwork() const;
    std::vector<double> costfunction(std::vector<double> const X);
    void backprop(std::vector<double> X, std::vector<double> y);
    
  private:
    std::vector<std::vector<Neuron>> _network;
};

#endif
