#ifndef GENETICALGORITHM_MULTITHREADING_H
#define GENETICALGORITHM_MULTITHREADING_H

#include "MainProcess.h"
#include "Multithreading.h"

namespace GeneticAlgorithm {

    /**
     * 多线程主流程
     */
    class Multithreading {
    public:
        // 构造方法
        Multithreading(unsigned long threadNumber);
        // 销毁对象
        ~Multithreading();

        // 主流程运行
        void run(
            unsigned long numberOfChromosome, // 种群中个体数量
            unsigned long lengthOfChromosome, // 每个个体的基因长度
            long double min, // 一开始初始种群时，随机数范围最小值
            long double max, // 一开始初始种群时，随机数范围最大值
            unsigned long maxLoop, // 最大迭代次数
            long double stopFitness, // 达到多大的适应度就立刻停止迭代
            unsigned long keep, // 每次迭代保留多少个上一代的个体
            long double r // 基因突变的概率
        );
        // 继续运行
        void runContinue(
            unsigned long maxLoop, // 这一次的最大迭代次数
            long double stopFitness, // 达到多大的适应度就立刻停止迭代
            unsigned long keep, // 每次迭代保留多少个上一代的个体
            long double r // 基因突变的概率
        );
        // 种群间最好个体随机复制性交换
        void exchange();
        // 设置debug模式，为true的时候打印调试信息
        void setDebug(bool enableDebug);
        // 获取迭代次数。如果在一开始初始化的那代种群就达到停止的条件，那么返回0
        unsigned long getLoopNumber();
        // 获取最大的适应度
        long double getMaxFitness();

    private:
        // 线程数
        unsigned long threadNumber;
        // MainProcess对象
        MainProcess** process = nullptr;
    };

}

#endif
