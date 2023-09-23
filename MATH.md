# Neural Network in C++

## Introduction to Neural Networks
In computer science, a neural network is a class of models inspired by biological neural networks (the central nervous systems of animals, in particular the brain) which are used to estimate or approximate functions that can depend on a large number of inputs and are generally unknown. Artificial neural networks are generally presented as systems of interconnected "neurons" which exchange messages between each other. The connections have numeric weights that can be tuned based on experience, making neural nets adaptive to inputs and capable of learning.

## Neural Network Neurons (Nodes)
### What is a neuron?
A neuron is the basic unit of a neural network. The neuron receives input from some other nodes, or from an external source and computes an output. We differentiate three types of neurons:
* Input Neurons
* Hidden Neurons
* Output Neurons

### Input Neurons
Input neurons are neurons that take inputs from the outside world (for exemple, the pixels of an image). They are connected to the hidden neurons. The number of input neurons is equal to the number of inputs of the neural network.

### Hidden Neurons
Hidden neurons are neurons that are not directly connected to the outside world. They are connected to the input neurons and to the output neurons. The number of hidden neurons is a parameter of the neural network. Inputs neurons are grouped into layer, each layer process the output of the previous layer.

We note $a^{(L-1)}_i$ the output of the $i^{th}$ neuron of the $(L-1)^{th}$ layer. The output of the $j^{th}$ neuron of the $L^{th}$ layer is given by the following formula:

$$a^{(L)}_j = \sigma \left(\right)$$

Where $n^{(L-1)}$ is the number of neurons in the $(L-1)^{th}$ layer, $w^{(L)}_{ij}$ is the weight of the connection between the $i^{th}$ neuron of the $(L-1)^{th}$ layer and the $j^{th}$ neuron of the $L^{th}$ layer and $b^{(L)}_j$ is the bias of the $j^{th}$ neuron of the $L^{th}$ layer.

To simplify the notation, we define the following $z^{(L)}_j$, the weighted sum of the inputs of the $j^{th}$ neuron of the $L^{th}$ layer before the activation function is applied:

$$z^{(L)}_j = \sum_{i=1}^{n^{(L-1)}} w^{(L)}_{ij} a^{(L-1)}_i + b^{(L)}_j$$

The output of the $j^{th}$ neuron of the $L^{th}$ layer is then given by:

$$a^{(L)}_j = \sigma\left(z^{(L)}_j\right)$$

### Output Neurons
Output neurons are neurons that are not directly connected to the outside world. They are connected to the hidden neurons. The number of output neurons is equal to the number of outputs of the neural network.

## Matrix Representation of a Neural Network
For any given hidden neuron in our network, we previously defined $z^{(L)}_j$ as the weighted sum of the inputs of the $j^{th}$ neuron of the $L^{th}$ layer before the activation function is applied. 

We now define $a^{(L)}$ as the vector of the outputs of the $L^{th}$ layer. We also define $w^{(L)}$ as the matrix of the weights of the connections between the $(L-1)^{th}$ layer and the $L^{th}$ layer. Finally, we define $b^{(L)}$ as the vector of the biases of the $L^{th}$ layer.

$$
\begin{pmatrix}
w_{0,0} & \cdots & w_{0,m-1}\\ 
\vdots  & \ddots & \vdots\\ 
w_{n-1,0} & \cdots & w_{n-1,m-1}\\ 
\end{pmatrix}
$$

<!-- This Document is not finished yet-->