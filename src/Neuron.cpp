#include "Neuron.h"
#include <math.h>

#include <iostream>
#include <assert.h>

Neuron::Neuron()
{
  _biase = -30;
  _theta.push_back(20);
  _theta.push_back(20);
}

Neuron::~Neuron()
{

}

Neuron::Neuron(const Neuron& neuron)
{

}

double Neuron::calcOutput(const std::vector<double> input)
{
  return 1/(1+exp(-thetaTX(input)));
}

double Neuron::thetaTX(const std::vector<double>& input)
{
  assert(_theta.size() == input.size());
  assert(input.size() > 0);
  
  double res = .0;
  
  std::vector<double>::const_iterator itInputb = input.cbegin();
  std::vector<double>::const_iterator itThetab = _theta.cbegin();
  std::vector<double>::const_iterator itThetae = _theta.cend();
   
  while(itThetab != itThetae)
  {
    res += (*itThetab) * (*itInputb);
    ++itInputb;
    ++itThetab;
  }
  
  return res+_biase;
}

void Neuron::adjust(const double error)
{
  //Error is a ratio
  std::vector<double>::const_iterator itThetab = _theta.cbegin();
  std::vector<double>::const_iterator itThetae = _theta.cend();
  while(itThetab != itThetae)
  {
    *itThetab *= error;
    ++itThetab;
    ++itThetae;
  }
}
