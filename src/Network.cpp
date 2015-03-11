#include "Network.h"

#include <cmath>

Network::Network(std::vector<int> const sNetwork)
{
	for(auto i = 0; i < sNetwork.size()-1; ++i)
	{
	  auto nbInput = sNetwork.at(i);
	  std::vector<Neuron> l;
	  _network.push_back(l);
		for(auto j = 0; j < sNetwork.at(i); ++j)
		  _network.at(i).push_back(Neuron(nbInput));
	}
		  
	_lambda = 0.5;
}

Network::~Network()
{

}

Network::Network(const Network& network)
{
	for(auto i = 0; i < network._network.size(); ++i)
	{
	  _network.push_back(std::vector<Neuron>());
    for(auto j = 0; j < network._network.at(i).size(); ++j)
    {
    	Neuron n(network._network.at(i).at(j));
    	_network.at(i).push_back(n);
    }
  }
}

double Network::costfunction(std::vector<double> const& X, std::vector<double> const& ol, 
																													 std::vector<double> const& y)
{
  //One iteration. X -> input. ol -> output layer; y -> expected output
  //TODO test
	double J;
	auto m = X.size();
	auto K = _network.back().size();
	for(auto k=0; k<K; ++k)
	{
	  //J += y(:, k)' * (log(ol(:, k))) + (1 .- y(:, k))' * log(1.-ol(:, k));
		double termA = y.at(k)*std::log(ol.at(k));
		double termB = (1-y.at(k))*std::log(1 - ol.at(k));
	  J += termA + termB;
	}
	
	J *= -1/m;	
	
	//J += lambda/(2*m) * (sum(sum(Theta1(:, 2:end) .^ 2)) + sum(sum(Theta2(:, 2:end) .^ 2)))...;
	double regularizationTerm = 0;
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
	regularizationTerm *= _lambda/(2*m);
	J += regularizationTerm;
	
	return J;
}

std::vector<double> Network::forwardProp(std::vector<double> const& input)
{
  //TODO test
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

void backprop(std::vector<double> X, std::vector<double> y)
{
	//TODO
}
