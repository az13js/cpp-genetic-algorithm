#include "PopulationFactory.h"
#include "Population.h"
#include "ChromosomeFactory.h"

namespace GeneticAlgorithm {

    Population* PopulationFactory::buildRandomPopulation(unsigned long numberOfChromosome, unsigned long lengthOfChromosome) {
        ChromosomeFactory chromosomeFactory = ChromosomeFactory();
        Population* population = new Population(numberOfChromosome);
        for (unsigned long i = 0; i < numberOfChromosome; i++) {
            population->setChromosome(i, chromosomeFactory.buildRandomBinrary(lengthOfChromosome));
        }
        return population;
    }

}