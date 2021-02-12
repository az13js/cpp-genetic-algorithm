#include "MainProcess.h"
#include "Multithreading.h"
#include "Chromosome.h"
#include "ChromosomeFactory.h"
#include "Utils/GlobalCppRandomEngine.h"
#include <thread>
#include <random>

namespace GeneticAlgorithm {

    Multithreading::Multithreading(unsigned long threadNumber) {
        if (threadNumber < 1) {
            throw "threadNumber < 1";
        }
        this->threadNumber = threadNumber;
        this->process = new MainProcess*[threadNumber];
        for (unsigned long i = 0; i < threadNumber; i++) {
            this->process[i] = new MainProcess();
        }
    }

    Multithreading::~Multithreading() {
        for (unsigned long i = 0; i < this->threadNumber; i++) {
            delete this->process[i];
        }
        delete[] process;
    }

    void Multithreading::run(
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
        thread** threads = new thread*[this->threadNumber];
        for (unsigned long i = 0; i < this->threadNumber; i++) {
            threads[i] = new thread([](
                MainProcess* process,
                unsigned long numberOfChromosome,
                unsigned long lengthOfChromosome,
                long double min,
                long double max,
                unsigned long maxLoop,
                long double stopFitness,
                unsigned long keep,
                long double r
            ) {
                process->run(numberOfChromosome, lengthOfChromosome, min, max, maxLoop, stopFitness, keep, r);
            }, this->process[i], numberOfChromosome, lengthOfChromosome, min, max, maxLoop, stopFitness, keep, r);
        }
        for (unsigned long i = 0; i < this->threadNumber; i++) {
            threads[i]->join();
            delete threads[i];
        }
        delete[] threads;
    }

    void Multithreading::runContinue(
        unsigned long maxLoop, // 这一次的最大迭代次数
        long double stopFitness, // 达到多大的适应度就立刻停止迭代
        unsigned long keep, // 每次迭代保留多少个上一代的个体
        long double r // 基因突变的概率
    ) {
        using namespace std;
        thread** threads = new thread*[this->threadNumber];
        for (unsigned long i = 0; i < this->threadNumber; i++) {
            threads[i] = new thread([](
                MainProcess* process,
                unsigned long maxLoop,
                long double stopFitness,
                unsigned long keep,
                long double r
            ) {
                process->runContinue(maxLoop, stopFitness, keep, r);
            }, this->process[i], maxLoop, stopFitness, keep, r);
        }
        for (unsigned long i = 0; i < this->threadNumber; i++) {
            threads[i]->join();
            delete threads[i];
        }
        delete[] threads;
    }

    void Multithreading::exchange() {
        if (1 == this->threadNumber) {
            return;
        }
        ChromosomeFactory factory = ChromosomeFactory();
        Chromosome** chromosomeData = new Chromosome*[this->threadNumber];
        for (unsigned long i = 0; i < this->threadNumber; i++) {
            chromosomeData[i] = factory.buildFromChromosome(this->process[i]->getMaxFitnessChromosome());
        }
        unsigned long select;
        Chromosome* tmp;
        for (unsigned long i = 0; i < this->threadNumber - 1; i++) {
            std::uniform_int_distribution<unsigned long> ran(i, this->threadNumber - 1);
            select = ran(Utils::GlobalCppRandomEngine::engine);
            tmp = chromosomeData[select];
            chromosomeData[select] = chromosomeData[i];
            chromosomeData[i] = tmp;
        }
        for (unsigned long i = 0; i < this->threadNumber; i++) {
            this->process[i]->replaceChromosome(chromosomeData[i]);
        }
        delete[] chromosomeData;
    }

    void Multithreading::setDebug(bool enableDebug) {
        for (unsigned long i = 0; i < this->threadNumber; i++) {
            this->process[i]->setDebug(enableDebug);
        }
    }

    unsigned long Multithreading::getLoopNumber() {
        return this->process[0]->getLoopNumber();
    }

    long double Multithreading::getMaxFitness() {
        long double f = this->process[0]->getMaxFitness();
        long double tmp;
        for (unsigned long i = 1; i < this->threadNumber; i++) {
            tmp = this->process[i]->getMaxFitness();
            if (tmp > f) {
                f = tmp;
            }
        }
        return f;
    }
}
