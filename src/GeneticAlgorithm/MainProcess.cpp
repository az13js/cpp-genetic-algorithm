#include <random>
#include <iostream>
#include "MainProcess.h"
#include "PopulationFactory.h"
#include "Utils/GlobalCppRandomEngine.h"
#include "Chromosome.h"

namespace GeneticAlgorithm {

    MainProcess::MainProcess() {
    }

    MainProcess::~MainProcess() {
        this->freeMemory();
    }

    void MainProcess::run(
        unsigned long numberOfChromosome,
        unsigned long lengthOfChromosome,
        long double min,
        long double max,
        unsigned long maxLoop,
        long double stopFitness,
        unsigned long keep,
        long double r
    ) {
        using namespace std;
        this->freeMemory(); // 防止重复调用run()没有释放上一次的内存
        this->numberOfChromosome = numberOfChromosome;
        this->lengthOfChromosome = lengthOfChromosome;
        this->min = min;
        this->max = max;
        this->keep = keep;
        this->kill = numberOfChromosome - keep;
        this->r = r;
        this->init();
        this->sort();
        this->maxFitness = this->population->getMaxFitnessChromosome()->getFitness();

        if (this->debug) {
            cout << "代数=0, 最大适应度=" << this->maxFitness << ", 个体信息=";
            this->population->getMaxFitnessChromosome()->dump();
        }

        while (this->loopNow < maxLoop && this->maxFitness < stopFitness) {
            this->select();
            this->crossover();
            this->mutation();
            this->generated();
            this->sort();
            this->maxFitness = this->population->getMaxFitnessChromosome()->getFitness();
            this->loopNow++;
            if (this->debug) {
                cout << "代数=" << this->loopNow << ", 最大适应度=" << this->maxFitness << ", 个体信息=";
                this->population->getMaxFitnessChromosome()->dump();
            }
        }
        if (this->debug) {
            cout << "结束。" << endl;
        }
    }

    void MainProcess::runContinue(
        unsigned long maxLoop, // 这一次的最大迭代次数
        long double stopFitness, // 达到多大的适应度就立刻停止迭代
        unsigned long keep, // 每次迭代保留多少个上一代的个体
        long double r // 基因突变的概率
    ) {
        using namespace std;
        if (nullptr == this->population || nullptr == this->selectedChromosome || nullptr == this->newChromosome) {
            return;
        }
        if (this->keep != keep) { // 之前是keep=1的话，会因为优化而不会排序
            if (1 == this->keep && keep > 1) { // 之前是keep=1的话，会因为优化而不会排序
                this->keep = keep;
                this->kill = this->numberOfChromosome - keep;
                this->sort(); // 先排序避免后满淘汰掉较优解
            } else {
                this->keep = keep;
                this->kill = this->numberOfChromosome - keep;
            }
            // 尺寸发生变化，删除旧的再申请新空间
            delete[] this->selectedChromosome;
            delete[] this->newChromosome;
            this->selectedChromosome = new Chromosome*[2 * this->kill];
            this->newChromosome = new Chromosome*[this->kill];
        }
        this->r = r;
        unsigned long i = 0;
        this->maxFitness = this->population->getMaxFitnessChromosome()->getFitness();
        while (i < maxLoop && this->maxFitness < stopFitness) {
            this->select();
            this->crossover();
            this->mutation();
            this->generated();
            this->sort();
            this->maxFitness = this->population->getMaxFitnessChromosome()->getFitness();
            this->loopNow++;
            if (this->debug) {
                cout << "代数=" << this->loopNow << ", 最大适应度=" << this->maxFitness << ", 个体信息=";
                this->population->getMaxFitnessChromosome()->dump();
            }
            i++;
        }
        if (this->debug) {
            cout << "结束。" << endl;
        }
    }

    void MainProcess::setDebug(bool enableDebug) {
        this->debug = enableDebug;
    }

    unsigned long MainProcess::getLoopNumber() {
        return this->loopNow;
    }

    long double MainProcess::getMaxFitness() {
        return this->maxFitness;
    }

    Chromosome* MainProcess::getMaxFitnessChromosome() {
        return this->population->getMaxFitnessChromosome();
    }

    void MainProcess::replaceChromosome(Chromosome* chromosome) {
        Chromosome* maxChromosome = this->population->getMaxFitnessChromosome();
        for (unsigned long offset = this->numberOfChromosome - 1; offset + 2 > 1; offset--) {
            if ((void*)this->population->getChromosome(offset) != (void*)maxChromosome) {
                this->population->replaceChromosome(offset, chromosome);
                return;
            }
        }
    }

    void MainProcess::init() {
        this->population = PopulationFactory().buildRandomPopulation(this->numberOfChromosome, this->lengthOfChromosome, this->min, this->max);
        this->loopNow = 0;
        this->maxFitness = 0.0;
        this->selectedChromosome = new Chromosome*[2 * this->kill];
        this->newChromosome = new Chromosome*[this->kill];
    }

    void MainProcess::sort() {
        if (1 != this->keep) { // 为了优化流程，只保留一个的时候不必排序
            this->population->sort();
        }
    }

    // 锦标赛选择算法，执行速度比轮盘赌的快
    void MainProcess::select() {
        using namespace GeneticAlgorithm::Utils;
        using namespace std;
        Chromosome* selectChromosome1;
        Chromosome* selectChromosome2;
        unsigned long generate = 2 * this->kill;
        uniform_int_distribution<unsigned long> range(0, this->numberOfChromosome - 1);
        // 运行 generate 次选择
        for (unsigned long i = 0; i < generate; i++) {
            selectChromosome1 = this->population->getChromosome(range(GlobalCppRandomEngine::engine));
            selectChromosome2 = this->population->getChromosome(range(GlobalCppRandomEngine::engine));
            if (selectChromosome1->getFitness() > selectChromosome2->getFitness()) {
                this->selectedChromosome[i] = selectChromosome1;
            } else {
                this->selectedChromosome[i] = selectChromosome2;
            }
        }
    }

    void MainProcess::crossover() {
        for (unsigned long i = 0; i < this->kill; i++) {
            this->newChromosome[i] = this->selectedChromosome[2 * i]->crossover(this->selectedChromosome[1 + 2 * i]);
        }
    }

    void MainProcess::mutation() {
        if (0 >= this->r) {
            return;
        }
        for (unsigned long i = 0; i < this->kill; i++) {
            this->newChromosome[i]->mutation(this->r);
        }
    }

    void MainProcess::generated() {
        if (1 != this->keep) {
            for (unsigned long i = this->keep; i < this->numberOfChromosome; i++) {
                this->population->replaceChromosome(i, this->newChromosome[i - this->keep]);
            }
        } else {
            unsigned long replaceOffset = 0, newChromosomePoolOffset = 0;
            Chromosome* maxFitnessChromosome = this->population->getMaxFitnessChromosome();
            for (unsigned long i = 0; i < this->numberOfChromosome; i++) {
                if ((void*)(this->population->getChromosome(replaceOffset)) != (void*)maxFitnessChromosome) {
                    this->population->replaceChromosome(replaceOffset, this->newChromosome[newChromosomePoolOffset]);
                    newChromosomePoolOffset++;
                }
                replaceOffset++;
            }
        }
    }

    void MainProcess::freeMemory() {
        if (nullptr != this->population) {
            delete this->population;
            this->population = nullptr;
        }
        // selectedChromosome 指向 Population 实例里面的染色体，Population 会删除不需要在这里单独删染色体
        if (nullptr != this->selectedChromosome) {
            delete[] this->selectedChromosome;
            this->selectedChromosome = nullptr;
        }
        // 这些染色体会替换 Population 里面的，Population 会在替换时自己删掉，不需要在这里单独删染色体
        if (nullptr != this->newChromosome) {
            delete[] this->newChromosome;
            this->newChromosome = nullptr;
        }
    }
}
