/*
 * $ cd build
 * $ CXX=g++ cmake ../src
 * $ cmake --build .
 *
 */
#include <iostream>
#include "GeneticAlgorithm.h"
#include "GeneticAlgorithm/MainProcess.h"

using namespace GeneticAlgorithm;

int main()
{
    MainProcess mainProcess = MainProcess();
    mainProcess.setDebug(true);
    mainProcess.run(
        400, // 种群大小
        128, // 染色体长度
        100, // 最大迭代次数
        93.0, // 停止迭代适应度
        90, // 每次迭代保留多少个上一代的高适应度个体
        0.1 // 变异概率
    );
    return 0;
}
