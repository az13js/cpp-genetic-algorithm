#include <iostream>
#include "Chromosome.h"
#include "ChromosomeFactory.h"
#include "Utils/GlobalCppRandomEngine.h"

namespace GeneticAlgorithm {

    Chromosome::Chromosome(unsigned long lengthOfChromosome) {
        this->dataArray = new long double[lengthOfChromosome];
        this->lengthOfData = lengthOfChromosome;
    }

    Chromosome::~Chromosome() {
        delete[] this->dataArray;
    }

    bool Chromosome::setGene(unsigned long offset, long double value) {
        if (offset > this->lengthOfData - 1) {
            return false;
        }
        if (this->dataArray[offset] != value) {
            this->dataArray[offset] = value;
            this->isFitnessCached = false;
        }
        return true;
    }

    long double Chromosome::getGene(unsigned long offset) {
        if (offset > this->lengthOfData - 1) {
            throw "Error, out of range.";
        }
        return this->dataArray[offset];
    }

    void Chromosome::dump() {
        std::cout << "Fitness=" << this->getFitness() << ",v1=" << this->dataArray[0] << ",v2=" << this->dataArray[1] << std::endl;
    }

    unsigned long Chromosome::getLength() {
        return this->lengthOfData;
    }

    long double Chromosome::getFitness() {
        if (this->isFitnessCached) {
            return this->fitnessCached;
        }
        if (this->lengthOfData < 2) {
            throw "Can not less then 2.";
        }
        long double v1, v2, y;
        v1 = this->dataArray[0];
        v2 = this->dataArray[1];
        y = 100.0 * (v1 * v1 - v2) * (v1 * v1 - v2) + (1.0 - v1) * (1.0 - v1);
        // y 最小等于0，我们求最大适应度需要反过来
        this->fitnessCached = 1.0 / (y + 0.01);
        return this->fitnessCached;
    }

    Chromosome* Chromosome::crossover(Chromosome* another) {
        if (another->getLength() != this->lengthOfData) {
            throw "Length not equals!";
        }
        long double* newData = new long double[this->lengthOfData];
        for (unsigned long i = 0; i < this->lengthOfData; i++) {
            newData[i] = (this->dataArray[i] + another->getGene(i)) / 2.0;
        }
        Chromosome* newChromosome = ChromosomeFactory().buildFromArray(newData, this->lengthOfData);
        delete[] newData;
        return newChromosome;
    }

    void Chromosome::mutation(long double r) {
        if (r <= 0.0) {
            return;
        }
        using GeneticAlgorithm::Utils::GlobalCppRandomEngine;
        std::normal_distribution<long double> distribution(0, r);
        for (unsigned long i = 0; i < this->lengthOfData; i++) {
            this->dataArray[i] += distribution(GlobalCppRandomEngine::engine);
        }
    }
}
