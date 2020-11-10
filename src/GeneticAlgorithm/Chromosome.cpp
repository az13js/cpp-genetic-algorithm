#include "Chromosome.h"
#include <iostream>
#include "ChromosomeFactory.h"

namespace GeneticAlgorithm {

    Chromosome::Chromosome(unsigned long lengthOfChromosome) {
        this->dataArray = new int[lengthOfChromosome];
        this->lengthOfData = lengthOfChromosome;
    }

    Chromosome::~Chromosome() {
        delete[] this->dataArray;
    }

    bool Chromosome::setGene(unsigned long offset, int value) {
        if (offset > this->lengthOfData - 1) {
            return false;
        }
        if (this->dataArray[offset] != value) {
            this->dataArray[offset] = value;
            this->isFitnessCached = false;
        }
        return true;
    }

    int Chromosome::getGene(unsigned long offset) {
        if (offset > this->lengthOfData - 1) {
            throw "Error, out of range.";
        }
        return this->dataArray[offset];
    }

    void Chromosome::dump() {
        std::cout << "Fitness=" << this->getFitness() << ",v1=" << this->v1 << ",v2=" << this->v2 << std::endl;
    }

    unsigned long Chromosome::getLength() {
        return this->lengthOfData;
    }

    Chromosome* Chromosome::crossover(Chromosome* another) {
        if (another->getLength() != this->lengthOfData) {
            throw "Length not equals!";
        }
        int *newData = new int[this->lengthOfData];
        for (unsigned long i = 0; i < this->lengthOfData; i++) {
            if (i % 2 == 0) {
                newData[i] = this->dataArray[i];
            } else {
                newData[i] = another->getGene(i);
            }
        }
        Chromosome* newChromosome = ChromosomeFactory().buildFromArray(newData, this->lengthOfData);
        delete[] newData;
        return newChromosome;
    }

    long double Chromosome::getFitness() {
        if (this->isFitnessCached) {
            return this->fitnessCached;
        }
        if (this->lengthOfData < 16) {
            throw "Can not less then 16 bit.";
        }
        unsigned int len1 = 64, len2 = 64;
        if (this->lengthOfData < 128) {
            len1 = this->lengthOfData / 2;
            len2 = this->lengthOfData - len1;
        }
        int *arr1 = new int[len1];
        int *arr2 = new int[len2];
        unsigned long long max1 = 0, max2 = 0;
        long double v1, v2;
        for (unsigned int i = 0; i < len1; i++) {
            arr1[i] = this->dataArray[i];
            max1 = (max1 << 1) | 0x01;
        }
        v1 = (long double)this->getSimpleInteger(arr1, len1) / (long double)max1 * 4.096 - 2.048;
        for (unsigned int i = 0; i < len2; i++) {
            arr2[i] = this->dataArray[len1 + i];
            max2 = (max2 << 1) | 0x01;
        }
        v2 = (long double)this->getSimpleInteger(arr2, len2) / (long double)max2 * 4.096 - 2.048;
        long double y = 100.0 * (v1 * v1 - v2) * (v1 * v1 - v2) + (1.0 - v1) * (1.0 - v1);
        // y 最小等于0，我们求最大适应度需要反过来
        this->fitnessCached = 1.0 / (y + 0.01);
        this->v1 = v1;
        this->v2 = v2;
        delete[] arr1;
        delete[] arr2;
        return this->fitnessCached;
    }

    unsigned long long Chromosome::getSimpleInteger(int *intArray, unsigned long lengthOfIntArray) {
        unsigned long long x = 0;
        for (unsigned long i = 0; i < lengthOfIntArray; i++) {
            x <<= 1;
            x |= (0x01 & intArray[i]);
        }
        return x;
    }
}
