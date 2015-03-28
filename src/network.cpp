#include "network.h"

//Initialize network with one layer and 0 input/outputs
Network::Network(const std::vector<unsigned int>& size, unsigned int numInputs)
{
	_network.resize(size.size());
	for(unsigned int i = 0; i < size.size(); ++i)
		_network[i].resize(size[i]);

	learningRate = 0.4;

	auto psize = numInputs;
	for(unsigned int i = 0; i < _network.size(); i++) {
		for(unsigned int j = 0; j < _network[i].size(); j++) {
			Neuron n(psize);
			_network[i][j] = n;
		}
		psize = size[i];
	}
}

//Applies the inputs to the network and returns the output
std::vector<double> Network::output(const std::vector<double>& inputs)
{
	std::vector<double> output = inputs;
	for(unsigned int i = 0; i < _network.size(); i++) {
		std::vector<double> lInp(_network[i].size());
		for(unsigned int j = 0; j < _network[i].size(); j++)
			lInp[j] = _network[i][j].output(inputs);
		output = lInp;
	}
	return output;
}

//Train using back propogation
void Network::Train(const std::vector<double> &inputs,const std::vector<double> &expected) {
	//Feed forward for results
	std::vector<double> results = output(inputs);

	//Calculate output error.
	//O * (1 - O) * (A - O) = error
	for(unsigned int i = 0; i < results.size(); i++) {
		_network[_network.size() - 1][i].error = results[i] * (1 - results[i]) * (expected[i] - results[i]);
		//Update the output weights
		_network[_network.size() - 1][i].adjustForError();
	}	
	//Back propogate the error TODO DEBUG
	//decrement i to move back to the second to last layer
//	for(unsigned int i = _network.size() - 2; i >= 0; i--) {
//		for(unsigned int hid = 0; hid < _network[i].size(); hid++) {
//			double backPropVal = 0;
//			//Summation of: (W_i * Err_i)
//			for(unsigned int bpvI = 0; bpvI < _network[i+1].size(); bpvI++) {
//				backPropVal += (_network[i+1][bpvI].weights()[hid] * _network[i+1][bpvI].error);
//			}

//			//Error = O * (1 - O) * E(W_i * Err_i)
//			_network[i][hid].error = _network[i][hid].result * (1 - _network[i][hid].result) * backPropVal;

//			//Update weights for hidden layer
//			_network[i][hid].adjustForError();
//		}
//	}
}

//[Async]
//Train using back propogation without modifying the network during training.
std::vector<std::vector<double> > Network::TrainC(const std::vector<double> &inputs, const std::vector<double> &expected) const {

	//Feed forward for results
	std::vector<double> results = inputs;
	for(unsigned int i = 0; i < _network.size(); i++) {
		std::vector<double> lInp(_network[i].size());
		for(unsigned int j = 0; j < _network[i].size(); j++)
			lInp[j] = _network[i][j].output(results);
		results = lInp;
	}

	//Calculate output error.
	//O * (1 - O) * (A - O) = error
	std::vector<std::vector<double> > error(_network.size());
	for(unsigned int i = 0; i < error.size(); i++)
		error[i].resize(_network[i].size());

	for(unsigned int i = 0; i < results.size(); i++)
		error[error.size() - 1][i] = results[i] * (1 - results[i]) * (expected[i] - results[i]);

	//Back propogate the error
	//decrement i to move back to the second to last layer
	for(unsigned int i = _network.size() - 2; i >= 0; i--) {
		for(unsigned int hid = 0; hid < _network[i].size(); hid++) {
			double backPropVal = 0;
			//Summation of: (W_i * Err_i)
			for(unsigned int bpvI = 0; bpvI < _network[i+1].size(); bpvI++)
				backPropVal += (_network[i+1][bpvI].weights()[hid] * error[i+1][bpvI]);

			//Error = O * (1 - O) * E(W_i * Err_i)
			error[i][hid] = _network[i][hid].result * (1 - _network[i][hid].result) * backPropVal;
		}
	}
}

std::ostream& operator<<(std::ostream& out, Network const& n)
{
	out << "Network: [";
	const std::vector<std::vector<Neuron> > ntw = n.network();
	for(unsigned int i = 0; i < ntw.size(); i++)
	{
		for(unsigned int j = 0; j < ntw[i].size(); j++)
			out << ntw[i][j] << ";";
		out << "\n";
	}
	out << "]\n";
	return out;
}
