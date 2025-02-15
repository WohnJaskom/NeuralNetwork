#ifndef NET_HPP
#define NET_HPP

#include <vector>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cctype>
#include <iomanip>
#include <iterator>
#include <numeric>

// Maybe change this to vector<double> at some point
// Not sure what deltaWeight is for
struct Connection {
    double weight;
    double deltaWeight;
};

class Neuron
{
public:
    Neuron(unsigned numOutputs);
    double getOutputVal();
    void setOutputVal(double newVal);

    double getBias();
    void setBias(double newBias);

    double getWeight(int index);
    void setWeight(int index, double newWeight);
    

private:
    static double randomWeight(void);
    double m_outputVal;
    double m_bias;
    std::vector<Connection> m_outputWeights;

};

typedef std::vector<Neuron> Layer;

class Net
{
public:
    Net(const std::vector<unsigned> &topology);
    void forwardProp(std::string activationFunction, int startIndex);
    void backProp(const std::vector<double> &targetVals);
    void getResults(const std::vector<double> &resultVals) const;
    void activationReLU(double weightedSum, Neuron neuron);
    void activate(int indexOfActivation, Neuron neuron, double weightedSum);
    
    std::vector<Layer> getLayers();
    void printLayers();

private:
    std::vector<Layer> m_layers; // m_layers[layerNum][neuronNum]

};

#endif
