#include "Population.h"
#include <iostream>
#include <algorithm>

namespace GeneticAlgorithm {

    Population::Population(unsigned long numberOfChromosome) {
        this->chromosomeArray = new Chromosome*[numberOfChromosome];
        this->numberOfChromosome = numberOfChromosome;
    }

    Population::~Population() {
        for (unsigned long i = 0; i < this->numberOfChromosome; i++) {
            if (nullptr != this->chromosomeArray[i]) {
                delete this->chromosomeArray[i];
            }
        }
        delete[] this->chromosomeArray;
    }

    bool Population::setChromosome(unsigned long offset, Chromosome *chromosome) {
        if (offset < this->numberOfChromosome) {
            this->chromosomeArray[offset] = chromosome;
            this->isMaxFitnessChromosomeCache = false;
            return true;
        }
        return false;
    }

    bool Population::replaceChromosome(unsigned long offset, Chromosome *chromosome) {
        if (offset < this->numberOfChromosome) {
            delete this->chromosomeArray[offset];
            this->chromosomeArray[offset] = chromosome;
            this->isMaxFitnessChromosomeCache = false;
            return true;
        }
        return false;
    }

    Chromosome* Population::getChromosome(unsigned long offset) {
        if (offset >= this->numberOfChromosome) {
            throw "Error, offset out of range, in \"Population::getChromosome\".";
        }
        if (!this->chromosomeArray[offset]) {
            throw "Null pointer exception.";
        }
        return this->chromosomeArray[offset];
    }

    unsigned long Population::getSize() {
        return this->numberOfChromosome;
    }

    void Population::sort() {
        std::sort(
            &(this->chromosomeArray[0]),
            &(this->chromosomeArray[this->numberOfChromosome]),
            [](Chromosome* a, Chromosome* b) -> bool {
                return a->getFitness() > b->getFitness();
            }
        );
        this->isMaxFitnessChromosomeCache = true;
        this->maxFitnessChromosomeCache = this->chromosomeArray[0];
    }

    Chromosome* Population::getMaxFitnessChromosome() {
        if (this->isMaxFitnessChromosomeCache) {
            return this->maxFitnessChromosomeCache;
        }
        long double maxFitness = std::numeric_limits<long double>::min();
        unsigned long offset = 0;
        for (unsigned long i = 0; i < this->numberOfChromosome; i++) {
            if (this->chromosomeArray[i]->getFitness() > maxFitness) {
                offset = i;
                maxFitness = this->chromosomeArray[i]->getFitness();
            }
        }
        this->isMaxFitnessChromosomeCache = true;
        this->maxFitnessChromosomeCache = this->chromosomeArray[offset];
        return this->chromosomeArray[offset];
    }

}
