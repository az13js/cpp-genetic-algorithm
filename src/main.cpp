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
using namespace std;

int main()
{
    MainProcess mainProcess = MainProcess();
    mainProcess.setDebug(true);
    mainProcess.run(
        240, // 种群大小
        2, // 染色体长度
        -2.048, // 初始范围
        2.048, // 初始范围
        100, // 最大迭代次数
        90.0, // 停止迭代适应度
        20, // 每次迭代保留多少个上一代的高适应度个体
        0.15 // 变异概率，随便变动范围系数
    );
    return 0;
}
