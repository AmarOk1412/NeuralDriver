#include "Network.h"

#include <cmath>

Network::Network(std::vector<int> const sNetwork)
{
	for(auto i = 1; i < sNetwork.size(); ++i)
	{
	  auto nbInput = sNetwork.at(i-1);
	  std::vector<Neuron> l;
	  _network.push_back(l);
		for(auto j = 0; j < sNetwork.at(i); ++j)
		  _network.at(i-1).push_back(Neuron(nbInput));
	}
		  
	_lambda = 0.5;
}

Network::~Network()
{

}

double Network::costfunction(std::vector<double> const& X, std::vector<double> const& ol, 
																													 std::vector<double> const& y)
{
  //One iteration. X -> input. ol -> output layer; y -> expected output
  //TODO test
	double J = 0.;
	auto m = X.size();
	auto K = _network.back().size();
	for(auto k=0; k<K; ++k)
	{
	  //J += y(:, k)' * (log(ol(:, k))) + (1 .- y(:, k))' * log(1.-ol(:, k));
		double termA = y.at(k)*std::log(ol.at(k));
		double termB = (1-y.at(k))*std::log(1 - ol.at(k));
	  J += termA + termB;
	}
	J /= -m; 
	
	//J += lambda/(2*m) * (sum(sum(Theta1(:, 2:end) .^ 2)) + sum(sum(Theta2(:, 2:end) .^ 2)))...;
	double regularizationTerm = 0.;
	auto LM1 = _network.size() - 1;
	for(auto l = 0; l < LM1; ++l)
	{
	  auto sl = _network.at(LM1).size();
	  for(auto s = 0; s < sl; ++s)
	  {
	    Neuron unit(_network.at(LM1).at(s));
	  	//regularizationTerm += std::pow(unit.getBiase(),2);
	  	for(auto t = 0; t < unit.getThetas().size(); ++t)
	  	  regularizationTerm += std::pow(unit.getThetas().at(t),2);
	  }
	}
	regularizationTerm *= _lambda;
	regularizationTerm /= (2*m);
	J += regularizationTerm;
	
	return J;
}

std::vector<double> Network::forwardProp(std::vector<double> const& input)
{
  std::vector<double> output;
  std::vector<double> cinput = input;
  std::vector<double> ninput;
	for(auto l = 0; l < _network.size(); ++l)
	{
		ninput.clear();
		for(auto i = 0; i < _network.at(l).size(); ++i)
	    ninput.push_back(_network.at(l).at(i).calcOutput(cinput));
	  cinput = ninput;
	}
	return ninput;
}

void Network::backprop(std::vector<double> X, std::vector<double> output, std::vector<double> y)
{
	//TODO
//	assert(output.size() == y.size());
//	std::vector<double> pdelta;
//	for(auto i = 0; i < output.size(); ++i)
//	  pdelta.push_back(output.at(i) - y.at(i)); 
//	for(auto l = _network.size()-1; l >= 0; --l)
//	{
//	  
//	}
}


double Network::sigmoidGradient(double z)
{
  double sigmoid = 1/(1+std::exp(-z));
  return sigmoid*(1-sigmoid);
}

void Network::print() const
{
  std::cout << '[';
  for(auto l = 0; l < _network.size(); ++l)
	{
		for(auto i = 0; i < _network.at(l).size(); ++i)
	    std::cout << _network.at(l).at(i);
	  std::cout << std::endl;
	}
  std::cout << ']' << std::endl;
}
