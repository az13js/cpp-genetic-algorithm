# C++ Genetic Algorithm

这是使用 C++ 实现的遗传算法，遗传算法针对不同问题实现起来细节可能不一样，这里罗列一下当前的实现方式具有的特性：

- 通过锦标赛算法选择个体
- 通过从上一代中剔除低适应度个体的方式去除劣质解
- 个体由一条染色体组成，所以程序不区分个体和染色体两个概念
- 通过128位的10编码组成染色体，求解 De jong 函数 f2 在 -2.048 到 2.048 范围内的最小值
- 适应度取 1 / (0.01 + f2)
- 算法的参数可以通过修改`main.cpp`中`run`方法的输入参数来改变

另外，程序通过面向对象方式实现且类名称和文件名存在严格的对应关系，命名都采用驼峰命名法，以及虽然不多但是每个方法和成员属性都有中文注释。

## 环境需求

- `Cmake` 推荐使用版本3.10以上的，否则参考`CMakeLists.txt`中的注释修改版本。
- `GCC` 推荐使用支持 C++ 17 的 GCC 编译器，否则参考`CMakeLists.txt`中的注释修改 C++ 的版本需求。程序的源码没有使用更高级的语言特性，但是至少需要 C++ 11 才能运行起来。

*注：仓库代码在 GNU Linux 环境下能使用， C++ 源码编写时没有用到标准库以外的 API ，因此源码是支持跨平台使用的。理论上 Cmake 配置可以在 Windows 和苹果电脑上使用，但是我没有试过。*

## 使用

我只在`GNU Linux`操作系统上使用，如果需要在别的系统上使用需要自己想办法……

这是使用`Cmake`工具管理的 C++ 项目，所以按照正常使用`CMake`的方法构建就行，下面是构建示例：

    $ mkdir -p build
    $ cd build
    $ cmake ../src
    $ cmake --build .

然后在`build`目录下会产生一堆文件，包括可执行程序`GeneticAlgorithm.out`。执行程序：

    $ ./GeneticAlgorithm.out
    代数=0, 最大适应度=5.32271, 个体信息=Fitness=5.32271,v1=1.22321,v2=1.46045
    代数=1, 最大适应度=5.32271, 个体信息=Fitness=5.32271,v1=1.22321,v2=1.46045
    代数=2, 最大适应度=18.7579, 个体信息=Fitness=18.7579,v1=1.15983,v2=1.35853
    代数=3, 最大适应度=18.7579, 个体信息=Fitness=18.7579,v1=1.15983,v2=1.35853
    代数=4, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=5, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=6, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=7, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=8, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=9, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=10, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=11, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=12, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=13, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=14, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=15, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=16, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=17, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=18, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=19, 最大适应度=66.5867, 个体信息=Fitness=66.5867,v1=1.05199,v2=1.10188
    代数=20, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=21, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=22, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=23, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=24, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=25, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=26, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=27, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=28, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=29, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=30, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=31, 最大适应度=89.4192, 个体信息=Fitness=89.4192,v1=1.03354,v2=1.06744
    代数=32, 最大适应度=90.7112, 个体信息=Fitness=90.7112,v1=1.02963,v2=1.05894
    代数=33, 最大适应度=90.7112, 个体信息=Fitness=90.7112,v1=1.02963,v2=1.05894
    代数=34, 最大适应度=91.2374, 个体信息=Fitness=91.2374,v1=1.02751,v2=1.0572
    代数=35, 最大适应度=93.5033, 个体信息=Fitness=93.5033,v1=1.02444,v2=1.05047
    结束。

由于算法使用了随机数，所以可能在别的系统上得到的结果有点不一样，比如结束时的代数不一样、最大适应度不一样或者个体信息不一样，这是正常的。

## 修改源码

如果需要针对别的问题调整算法，那么需要修改源码。这里假设你知道遗传算法的原理且能使用 C++ ，那么根据需要你可能会修改下面列举的文件：

- `main.cpp` 程序入口在这里，算法参数也在这里
- `MainProcess.cpp`和`MainProcess.h` 算法整体的执行流程在这里控制
- `PopulationFactory.cpp`和`PopulationFactory.h` 需要创建种群对象时优先采用这里定义和实现的工厂类，调整种群创建方式或添加不同创建方式的话也优先考虑将逻辑放在这里面
- `Population.cpp`和`Population.h` 种群类，与种群实例互动、通信的方法在这里面
- `ChromosomeFactory.cpp`和`ChromosomeFactory.h` 染色体创建的工厂类，包含创建染色体的不同方式
- `Chromosome.cpp`和`Chromosome.h` 染色体类（一个染色体就是种群里的一个个体），实现方式不区分染色体和个体，如果需要区分染色体和个体那么得单独拆分出个体类，如果不需要区分的话，染色体和个体的对外互动、通信的方法都在这里面

另外，`GlobalCppRandomEngine.cpp`和`GlobalCppRandomEngine.h`目前只是在全局提供随机数引擎。