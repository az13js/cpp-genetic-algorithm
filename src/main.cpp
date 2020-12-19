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
        0.015 // 变异概率，随便变动范围系数
    );
    return 0;
}

/* 多线程版本使用示例

int main()
{
    Multithreading mainProcess = Multithreading(4);
    mainProcess.setDebug(false);
    mainProcess.run(
        50, // 种群大小
        2, // 染色体长度
        -2.048, // 初始范围
        2.048, // 初始范围
        0, // 最大迭代次数
        99.9999, // 停止迭代适应度
        5, // 每次迭代保留多少个上一代的高适应度个体
        0.015 // 变异概率，随便变动范围系数
    );
    cout << "Max fitness=" << mainProcess.getMaxFitness() << endl;
    for (int i = 0; i < 100; i++) {
        //mainProcess.exchange();
        mainProcess.runContinue(50, 99.9999, 5, 0.015);
        cout << i << ",Max fitness=" << mainProcess.getMaxFitness() << endl;
    }
    return 0;
}

*/
