#include "MainProcess.h"
#include <iostream>
#include "PopulationFactory.h"
#include <random>
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
        unsigned long maxLoop,
        long double stopFitness,
        unsigned long keep,
        long double r
    ) {
        using namespace std;
        this->freeMemory(); // 防止重复调用run()没有释放上一次的内存
        this->numberOfChromosome = numberOfChromosome;
        this->lengthOfChromosome = lengthOfChromosome;
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

    void MainProcess::setDebug(bool enableDebug) {
        this->debug = enableDebug;
    }

    void MainProcess::init() {
        this->population = PopulationFactory().buildRandomPopulation(this->numberOfChromosome, this->lengthOfChromosome);
        this->loopNow = 0;
        this->maxFitness = 0.0;
        this->selectedChromosome = new Chromosome*[2 * this->kill];
        this->newChromosome = new Chromosome*[this->kill];
    }

    void MainProcess::sort() {
        this->population->sort();
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
        using std::uniform_real_distribution;
        using namespace GeneticAlgorithm::Utils;
        uniform_real_distribution<long double> range(0.0, 1.0);
        for (unsigned long i = 0; i < this->kill; i++) {
            for (unsigned long j = 0; j < this->lengthOfChromosome; j++) {
                if (range(GlobalCppRandomEngine::engine) <= this->r) {
                    this->newChromosome[i]->setGene(j, 1 - this->newChromosome[i]->getGene(j));
                }
            }
        }
    }

    void MainProcess::generated() {
        for (unsigned long i = this->keep; i < this->numberOfChromosome; i++) {
            this->population->replaceChromosome(i, this->newChromosome[i - this->keep]);
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
