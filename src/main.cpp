#include <string>
#include <iostream>
#include "../include/Net.hpp"


int main() {
    srand(time(0));
    std::vector<unsigned> topology;
    // 3 layers
    topology.push_back(3); // Input Layer with 3 Neurons
    topology.push_back(2); // Hidden Layer with 2 Nuerons
    topology.push_back(1); // Output Layer with 1 Neuron

    Net myNet(topology);
    myNet.forwardProp("relu", 0);
    myNet.printLayers();
    return 0;
}
