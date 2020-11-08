#ifndef GENETICALGORITHM_POPULATIONFACTORY_H
#define GENETICALGORITHM_POPULATIONFACTORY_H

#include "Population.h"

namespace GeneticAlgorithm {

    /* 工厂类，生成种群
     */
    class PopulationFactory {

    public:
        // 返回种群实体，numberOfChromosome是种群的大小，lengthOfChromosome是个体染色体的长度
        Population* buildRandomPopulation(unsigned long numberOfChromosome, unsigned long lengthOfChromosome);

    };

}

#endif