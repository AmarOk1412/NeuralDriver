#include "network.h"

int main() {
	
  std::cout << "Test Neuron : " << std::endl;
  Neuron a(2);
  std::cout << a << std::endl;;
  std::vector<double> input;
  input.push_back(0.);
  input.push_back(1.);
  std::cout << "Output : " << a.output(input) << std::endl;
  a.error = 0.2;
  a.adjustForError();
  std::cout << a << std::endl;;
  std::cout << "_______________________________\n";
  
  std::cout << "Test Network : " << std::endl;
	std::vector<unsigned int> sn;
  sn.push_back(1);
	Network network(sn, 2);
	std::cout << network;
	
	std::cout << "Output : ";
	std::vector<double> output = network.output(input);
	std::cout << output.at(0) << std::endl;
	
	std::cout << "Train\n";
	std::vector<double> out;
	out.push_back(1.);
	network.Train(input, out);	
	std::cout << network;
  return 0;
}
