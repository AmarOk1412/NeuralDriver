#include "Neuron.h"
#include <vector>
#include <iostream>

int main() {

  Neuron n;
  std::vector<double> t;
  
  t.push_back(0);
  t.push_back(0);
  std::cout << n.calcOutput(t) << std::endl;
  t.clear();
	t.push_back(0);
	t.push_back(1);
	std::cout << n.calcOutput(t) << std::endl;
  t.clear();
  t.push_back(1);
  t.push_back(0);
  std::cout << n.calcOutput(t) << std::endl;
  t.clear();
  t.push_back(1);
  t.push_back(1);
  std::cout << n.calcOutput(t) << std::endl;
  t.clear();
  std::cout << n;
  std::cout << std::endl; 

  return 0;
}
