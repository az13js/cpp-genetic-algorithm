#ifndef GENETICALGORITHM_POPULATIONFACTORY_H
#define GENETICALGORITHM_POPULATIONFACTORY_H

#include "Population.h"

namespace GeneticAlgorithm {

    /* 工厂类，生成种群
     */
    class PopulationFactory {

    public:

        /**
         * 返回种群实体
         * @param unsigned long numberOfChromosome 种群的大小，
         * @param unsigned long lengthOfChromosome 个体染色体的长度
         * @param long double min 随机范围最小值
         * @param long double max 随机范围最大值
         * @return Population*
         */
        Population* buildRandomPopulation(unsigned long numberOfChromosome, unsigned long lengthOfChromosome, long double min, long double max);

    };

}

#endif
