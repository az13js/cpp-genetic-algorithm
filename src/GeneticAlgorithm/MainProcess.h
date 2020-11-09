#ifndef GENETICALGORITHM_MAINPROCESS_H
#define GENETICALGORITHM_MAINPROCESS_H

#include "Population.h"
#include "Chromosome.h"

namespace GeneticAlgorithm {

    // 内存占用估计方法：y=Kx+b
    // K=0.9504 b=1764
    // x 是种群中个体的数量
    // y 是程序占用内存，单位kb
    class MainProcess {

    public:
        // 构造方法
        MainProcess();
        // 销毁对象时用于释放内存
        ~MainProcess();

        // 主流程运行
        void run(
            unsigned long numberOfChromosome, // 种群中个体数量
            unsigned long lengthOfChromosome, // 每个个体的基因长度
            unsigned long maxLoop, // 最大迭代次数
            long double stopFitness, // 达到多大的适应度就立刻停止迭代
            unsigned long keep, // 每次迭代保留多少个上一代的个体
            long double r // 基因突变的概率
        );

        // 设置debug模式，为true的时候打印调试信息
        void setDebug(bool enableDebug);
        // 获取迭代次数。如果在一开始初始化的那代种群就达到停止的条件，那么返回0
        unsigned long getLoopNumber();
        // 获取最大的适应度
        long double getMaxFitness();

    private:
        // 染色体or个体的数量
        unsigned long numberOfChromosome;
        // 染色体的长度
        unsigned long lengthOfChromosome;
        // 每次迭代从上一代保留多少个个体
        unsigned long keep;
        // 每次迭代上上一道销毁多少个个体，这个根据numberOfChromosome和lengthOfChromosome算出来的
        unsigned long kill;
        // 运行过程中保留当前迭代属于第几次迭代
        unsigned long loopNow;
        // 保留每次迭代算出来的最大适应度
        long double maxFitness;
        // 迭代时存储选中的染色体or个体
        Chromosome** selectedChromosome = nullptr;
        // 迭代时存储新生成的个体or染色体
        Chromosome** newChromosome = nullptr;
        // 变异概率
        long double r;
        // 存储一个Population实例
        Population* population = nullptr;
        // 是否开启调试
        bool debug = false;
        // 私有，初始化
        void init();
        // 私有，对种群中个体按照适应度大小排序
        void sort();
        // 私有，选择个体
        void select();
        // 私有，交叉运算
        void crossover();
        // 私有，变异
        void mutation();
        // 私有，新个体替换上一代中不需要保留的个体
        void generated();
        // 私有，把上一次run中申请的内存释放
        void freeMemory();

    };

}

#endif