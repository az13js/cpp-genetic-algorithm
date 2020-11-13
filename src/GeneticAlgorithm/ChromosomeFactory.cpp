#include "ChromosomeFactory.h"
#include "Chromosome.h"
#include <random>
#include "Utils/GlobalCppRandomEngine.h"

namespace GeneticAlgorithm {

    Chromosome* ChromosomeFactory::buildFromArray(long double data[], unsigned long lengthOfData) {
        Chromosome* buildChromosome = this->buildEmpty(lengthOfData);
        for (unsigned long i = 0; i < lengthOfData; i++) {
            if (!buildChromosome->setGene(i, data[i])) {
                throw "Error, \"Chromosome::setGene\" return false. Exception throw in method \"ChromosomeFactory::buildFromArray\".";
            }
        }
        return buildChromosome;
    }

    Chromosome* ChromosomeFactory::buildRandomChromosome(unsigned long lengthOfData, long double min, long double max) {
        using namespace GeneticAlgorithm::Utils;
        long double *data = new long double[lengthOfData];
        std::uniform_real_distribution<long double> formateRandomNumberRange(min, max);
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
