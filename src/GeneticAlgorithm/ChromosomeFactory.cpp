#include "ChromosomeFactory.h"
#include "Chromosome.h"
#include <random>
#include "Utils/GlobalCppRandomEngine.h"

namespace GeneticAlgorithm {

    Chromosome* ChromosomeFactory::buildFromArray(int data[], unsigned long lengthOfData) {
        Chromosome* buildChromosome = this->buildEmpty(lengthOfData);
        for (unsigned long i = 0; i < lengthOfData; i++) {
            if (!buildChromosome->setGene(i, data[i])) {
                throw "Error, \"Chromosome::setGene\" return false. Exception throw in method \"ChromosomeFactory::buildFromArray\".";
            }
        }
        return buildChromosome;
    }

    Chromosome* ChromosomeFactory::buildRandomBinrary(unsigned long lengthOfData) {
        using std::uniform_int_distribution;
        using namespace GeneticAlgorithm::Utils;

        int *data = new int[lengthOfData];
        uniform_int_distribution<int> formateRandomNumberRange(0, 1);
        for (unsigned long i = 0; i < lengthOfData; i++) {
            data[i] = formateRandomNumberRange(GlobalCppRandomEngine::engine);
        }

        Chromosome* buildChromosome = this->buildFromArray(data, lengthOfData);
        delete[] data;
        return buildChromosome;
    }

    Chromosome* ChromosomeFactory::buildEmpty(unsigned long lengthOfData) {
        return new Chromosome(lengthOfData);
    }

}