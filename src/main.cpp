#include "Network.h"
#include <vector>
#include <iostream>

int main() {

  std::vector<int> sn;
  sn.push_back(2);
  sn.push_back(1);
	Network network(sn);
	std::cout << "Network : " << std::endl;
	network.print();
	
	std::vector<double> input;
	input.push_back(0.);
	input.push_back(1.);
	std::cout << "Output : ";
	std::vector<double> output = network.forwardProp(input);
	std::cout << output.at(0) << std::endl;
	
	std::cout << "Cost function : ";
	std::vector<double> expected;
	expected.push_back(1.);
	expected.push_back(2.);
	expected.push_back(3.);
	std::vector<double> real;
	real.push_back(.5);
	real.push_back(1.);
	real.push_back(1.5);
	std::cout << network.costfunction(input, output, output) << std::endl;
	std::cout << network.costfunction(expected, real, expected) << std::endl;
	//TODO : test costfunction
	//TODO : implement back prop
  return 0;
}
