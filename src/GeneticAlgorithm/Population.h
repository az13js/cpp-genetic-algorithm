#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include "Chromosome.h"

namespace GeneticAlgorithm {

    /* 种群
     */
    class Population {

    public:
        // 创建种群，空的种群
        Population(unsigned long numberOfChromosome);
        // 删除，释放内存
        ~Population();
        // 设置给定位置的个体
        bool setChromosome(unsigned long offset, Chromosome *chromosome);
        // 替换给定位置的个体
        bool replaceChromosome(unsigned long offset, Chromosome *chromosome);
        // 获取给定位置的个体
        Chromosome* getChromosome(unsigned long offset);
        // 获取种群的个体数量
        unsigned long getSize();
        // 获取Fitness最大值的Chromosome
        Chromosome* getMaxFitnessChromosome();
        // 对种群中个体按照从大到小的顺序排序
        void sort();

    private:
        // 染色体数量
        unsigned long numberOfChromosome;
        // 存储所有染色体
        Chromosome** chromosomeArray;
        // 是否有效缓存了当前种群中最大的适应度个体的适应度
        bool isMaxFitnessChromosomeCache = false;
        // 缓存的当前种群最大适应度个体的适应度
        Chromosome* maxFitnessChromosomeCache;
        // 最大适应度个体的偏移位置
        unsigned long maxFitnessChromosomeOffset;

    };

}

#endif