#ifndef GENETICALGORITHM_CHROMOSOME_H
#define GENETICALGORITHM_CHROMOSOME_H

namespace GeneticAlgorithm {

    /* 染色体
     */
    class Chromosome {

    public:
        // 创建空染色体
        Chromosome(unsigned long lengthOfChromosome);
        // 删除染色体，释放内存
        ~Chromosome();

        // 设置给定位置的基因
        bool setGene(unsigned long offset, int value);
        // 获取给定位置基因
        int getGene(unsigned long offset);
        // 打印调试信息
        void dump();
        // 获取长度，也就是基因的位数
        unsigned long getLength();

        // 获取适应度
        long double getFitness();
        // 与另一个染色体交叉，返回新的染色体
        Chromosome* crossover(Chromosome* another);

    private:
        // 保存了此染色体的长度
        unsigned long lengthOfData;
        // 保存了此染色体中基因的信息
        int *dataArray;

        // 为true时表示计算Fitness后缓存了计算结果，可以不用重复算
        bool isFitnessCached = false;
        // 缓存的上一次的适应度计算结果。需要判断isFitnessCached以确定确实缓存下来了。
        long double fitnessCached;
        // 在getFitness计算的时候，解码出来的临时变量，因为在dump()时用于打印调试所以也存储了下来。
        long double v1, v2;
        // 辅助私有方法，用于将一个0-1整数数组按位转换成一个unsigned long long的整数。
        unsigned long long getSimpleInteger(int *intArray, unsigned long lengthOfIntArray);

    };

}

#endif