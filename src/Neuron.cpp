#include "Neuron.h"
#include <math.h>
#include <random>

#include <iostream>
#include <assert.h>

Neuron::Neuron(const int nbInput)
{
  init(nbInput, 3.4);
}

Neuron::~Neuron()
{

}

double Neuron::calcOutput(std::vector<double> const& input)
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
  std::vector<double>::iterator itThetab = _theta.begin();
  std::vector<double>::iterator itThetae = _theta.end();
  while(itThetab != itThetae)
  {
    *itThetab *= error;
    ++itThetab;
    ++itThetae;
  }
}

void Neuron::init(int length, double epsilon)
{
   std::uniform_real_distribution<double> unif(-epsilon, epsilon);
   std::random_device rand_dev;
   std::mt19937 rand_engine(rand_dev());
   for(auto i = 0; i < length; ++i)
     _theta.push_back(unif(rand_engine));
   _biase = unif(rand_engine);
}


Neuron& Neuron::operator=(const Neuron& o)
{
  //Some parameters will change (to pointer).
  _input = o._input;
  _theta = o._theta;
  _biase = o._biase;
  _learningRate = o._learningRate;
  _output = o._output;
}

const double Neuron::getBiase() const
{
  return _biase;
}
    
const std::vector<double>& Neuron::getThetas() const
{
  return _theta;
}

std::ostream& operator<<(std::ostream & out, const Neuron& n)
{
  out << '[' << n.getBiase() << ',';
  std::vector<double> thetas = n.getThetas();
  for(auto t : thetas)
    out << t << ',';
  out << ']';
}
    
