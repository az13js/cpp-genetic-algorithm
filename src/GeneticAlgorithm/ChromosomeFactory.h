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

        /**
         * 从一个数组中创建染色体
         *
         * 实数数组，会原样拷贝给染色体用
         *
         * @param long double data[] 数组
         * @param unsigned long lengthOfData 数组的长度
         * @return Chromosome*
         */
        Chromosome* buildFromArray(long double data[], unsigned long lengthOfData);

        /**
         * 随机地创建染色体
         *
         * @param unsigned long lengthOfData 染色体中存储随机实数的个数
         * @param unsigned double min 随机实数的最小值
         * @param unsigned double max 随机实数的最大值
         * @return Chromosome*
         */
        Chromosome* buildRandomChromosome(unsigned long lengthOfData, long double min, long double max);

        /**
         * 创建空的染色体，其中实数都初始化为 0
         *
         * @param unsigned long lengthOfData 染色体中存储随机实数的个数
         * @return Chromosome*
         */
        Chromosome* buildEmpty(unsigned long lengthOfData);

    };

}

#endif
