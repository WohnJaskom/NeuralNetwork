#include "../include/Net.hpp"
#include "../include/boost/algorithm/string/case_conv.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

string activationFunctions[] = 
{
    "relu"
};


// Class Neuron
Neuron::Neuron(unsigned numOutputs)
{
    for (unsigned c = 0; c < numOutputs; ++c) {
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
        m_bias = randomWeight();
        m_outputVal = randomWeight();
    }
}

// Getters
double Neuron::getOutputVal()
{
    return m_outputVal;
}

double Neuron::getBias()
{
    return m_bias;
}

double Neuron::getWeight(int index) 
{
    return m_outputWeights[index].weight;
}


// Setters
void Neuron::setOutputVal(double newVal)
{
    this->m_outputVal = newVal;
}

void Neuron::setBias(double newBias)
{
    this->m_bias = newBias;
}

void Neuron::setWeight(int index, double newWeight)
{
    this->m_outputWeights[index].weight = newWeight;
}

double Neuron::randomWeight(void)
{
    return rand() / double(RAND_MAX);
}







// Class Net
Net::Net(const vector<unsigned> &topology)
{
    unsigned numLayers = topology.size();
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
        m_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        // Made a new Layer, now fill it with neurons
        for (unsigned neuronNum = 0; neuronNum < topology[layerNum]; neuronNum++) {
            m_layers.back().push_back(Neuron(numOutputs));
        }
    }
}

// Forward propogation
void Net::forwardProp(string activationFunction, int startIndex)
{
    vector<Layer> layers = this->getLayers();
    vector<Neuron> InputLayer = layers[startIndex];
    vector<Neuron> NextLayer = layers[++startIndex];

    int numNeuronsPrev = InputLayer.size();
    int numNeuronsCurr = NextLayer.size();

    for (int neuronNumCurr = 0; neuronNumCurr < numNeuronsCurr; neuronNumCurr++) {
        // Create a vector of sums so that repeated operations are not required
        // Each Neuron in NextLayer will have it's own sums vector
        vector<double> sums;
        for (int neuronNumPrev = 0; neuronNumPrev < numNeuronsPrev; neuronNumPrev++) {
            sums.push_back((InputLayer[neuronNumPrev].getWeight(neuronNumCurr) + InputLayer[neuronNumPrev].getOutputVal()));
        }
        double weightedSum = 0.0;
        for (int i = 0; i < sums.size(); i++) {
            weightedSum += sums[i];
        }
        weightedSum += NextLayer[neuronNumCurr].getBias();

        // Verify that the given activationFunction is supported by the library
        boost::algorithm::to_lower(activationFunction);
        string *location = find(begin(activationFunctions), end(activationFunctions), activationFunction);
        int indexOfActivation;
        assert(location != end(activationFunctions));

        // Perform activation function provided
        indexOfActivation = distance(activationFunctions, location);
        
        activate(indexOfActivation, NextLayer[neuronNumCurr], weightedSum);

    }

    if (startIndex < layers.size() - 1) {
        this->forwardProp(activationFunction, startIndex);
    }
}

void Net::backProp(const vector<double> &targetVals) 
{

}

void Net::getResults(const vector<double> &resultVals) const
{

}


// Activation Functions
void Net::activationReLU(double weightedSum, Neuron neuron)
{
    double output = max(0.0, weightedSum);
    neuron.setOutputVal(output);
}


void Net::activate(int indexOfActivation, Neuron neuron, double weightedSum)
{
    switch(indexOfActivation) 
    {
        case 0: // ReLU
            activationReLU(weightedSum, neuron);
    }
}



vector<Layer> Net::getLayers()
{
    return this->m_layers;
}

void Net::printLayers()
{
    vector<Layer> layers = this->getLayers();
    int count = 0;
    for (vector<Neuron> layer: layers) {
        cout << "Layer: " << count++ << "\n";
        int neuronNum = 1;
        cout << setw(20) << "Neuron #" << setw(20) << "Bias" << setw(20) << "OutputValue" << setw(20) << "Weights" << setw(50) << "\n";

        for (Neuron neuron: layer) {
            cout << setw(20) << neuronNum++ << setw(20) << neuron.getBias() << setw(20) << neuron.getOutputVal() << setw(20);
            for (int i = 0; i < layers[count].size(); i++) {
                cout << neuron.getWeight(i) << "\t";
            }
            cout << "\n";
        }
    }
    cout << endl;
}
