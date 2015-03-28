#ifndef J_NEURON_H
#define J_NEURON_H

#include <vector>
#include <iostream>

class Neuron
{
	public:
		Neuron(int numInputs = 0, double epsilon = 1., double learn = 0.3);
		double sigmoid(double val) const;
		double output(std::vector<double> inputs) const;

		void updateWeights(std::vector<double> inp, double expect);
		void adjustForError();
		void resetWeights(double epsilon = 1.);
		
		const std::vector<double>& weights() const { return _weights; }
		const double biase() const { return _biase; }
		double error;
		double result;

	private:
		double _biase;
		std::vector<double> _weights;
		double _learningRate;

		std::vector<double> _lastInp;
};

std::ostream& operator<<(std::ostream& out, Neuron const& n);

#endif
