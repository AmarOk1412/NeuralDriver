#ifndef J_NEURAL_NETWORK_H
#define J_NEURAL_NETWORK_H

#include "neuron.h"

class Network
{
	public:
		Network(const std::vector<unsigned int>& size, unsigned int numInputs);

		std::vector<double> output(const std::vector<double>& inputs);
		void Train(const std::vector<double> &inputs,const std::vector<double> &expected);
		std::vector<std::vector<double> > TrainC(const std::vector<double> &inputs,const std::vector<double> &expected) const;

		const std::vector<std::vector<Neuron> >& network() const { return _network; }
	private:
		std::vector<std::vector<Neuron> > _network;
		double learningRate;
};

std::ostream& operator<<(std::ostream& out, Network const& n);
#endif 
