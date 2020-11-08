#ifndef GENETICALGORITHM_CHROMOSOMEFACTORY_H
#define GENETICALGORITHM_CHROMOSOMEFACTORY_H

#include "Chromosome.h"
#include <random>
#include <iostream>

namespace GeneticAlgorithm {

    /* 工厂类，用于创建Chromosome的实例
     */
    class ChromosomeFactory {

    public:
        // 从一个数组中创建染色体
        Chromosome* buildFromArray(int data[], unsigned long lengthOfData);
        // 给定长度创建随机的0-1染色体
        Chromosome* buildRandomBinrary(unsigned long lengthOfData);
        // 创建空的染色体
        Chromosome* buildEmpty(unsigned long lengthOfData);

    };

}

#endif