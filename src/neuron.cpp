#include "neuron.h"

#include <cmath>
#include <random>
#include <cassert>

Neuron::Neuron(int numInputs, double epsilon, double learn) : _learningRate(learn)
{
	_weights.resize(numInputs);
	_lastInp.resize(numInputs, 1.);
	resetWeights(epsilon);
}

double Neuron::sigmoid(double val) const 
{
	return 1/(1+std::exp(-val));
}

double Neuron::output(std::vector<double> inputs) const {
  assert(inputs.size() == _weights.size());
	auto sum = .0;
	for(unsigned int i = 0; i < inputs.size(); i++)
		sum += inputs[i] * _weights[i];
	return sigmoid(sum + _biase);
}

//Randomizes the the weights to a number between -range and range
void Neuron::resetWeights(double epsilon) {
	 std::uniform_real_distribution<double> unif(-epsilon, epsilon);
   std::random_device rand_dev;
   std::mt19937 rand_engine(rand_dev());
   for(unsigned int i = 0; i < _weights.size(); ++i)
     _weights[i] = unif(rand_engine);
   _biase = unif(rand_engine);
}

void Neuron::adjustForError(double error) {
	for(unsigned int wt = 0; wt < _weights.size(); wt++)
		_weights[wt] += _learningRate * error * _lastInp[wt];
	_biase += _learningRate * error;
}

std::ostream& operator<<(std::ostream & out, const Neuron& n)
{
	out << "Neuron: [";
	const std::vector<double> w = n.weights();
	for(unsigned int i = 0; i < w.size(); i++)
		out << w[i] << ",";
	out << n.biase() << " (biase)]\n";
	return out;
}
