# 实验六　异构加速器设计

## 实验内容　

1. 学习掌握GEM5-SALAM
2. 基于GEM5-SALAM设计一个Transformer加速器（或任选其他应用加速器，但是不能直接用已有例子）。
3. 除了2，可自选题目，完成一个综合设计实验。例如在FS模式下完成与OS相关的综合实验；或结合编译器实验，自己设计一个DSL并在GEM5运行。

实验目标：在不涉及RTL, FPGA等的前提下，通过系统级建模的方式理解异构加速器的设计方法，并且基于 gem5-SALAM 实现一个简化版Transformer 加速器，探索其硬件调度、内存访问与性能提升策略。

## 环境构建

### gem5-salam

gem5-salam(System Architecture Lab for Accelerator
Modeling)，是gem5的一个分支，面向加速器体系结构建模和教学研究。他在gem5上提供了一整套的加速器抽象层接口，通过使用gem5-salam可以避开RTL，FPGA代码，直接进行加速器本身代码的编写。

### 环境构建过程

我这里环境的构建选择使用官方文档中的docker方案，通过运行`docker　build`完成实验环境的创建。

值得注意的是，下载出来的库中的Dockerfile，有一些错误，比如`clang`　`llvm`版本错误，以及后续的make会有运行报错，需要自行适配版本。这里我选择修改Dockerfile，改为：ubuntu 20.04, clang 12, llvm 12, 同时修改之后`RUN make`的相关命令完成了环境的构建，并将生成的镜像存储为`final_exp6:latest`，以备后续使用。

镜像生成结果如下：

![docker images](docker_images.png)

## gem5-salam 文件组织架构及其分析

关于本实验过程中涉及的所有文件，这里简单的对其进行一些说明(以`/gem-SALAM`为参考目录)。

- BM_ARM_OUT:这个文件是运行仿真结果保存的路径，其中的`system.terminal`会在调试中用到，`stats.txt`保存的是仿真结果分析。

- tools/run_system.sh:这个文件是把仿真跑起来的脚本文件。

- benchmarks/sys_validations/:这个目录下我们会进行加速器设计代码编写。

这里我选择在benchmarks/sys_validations下创建名为qkv的文件夹，作为本次实验的source目录，在此目录下，我写的代码文件结构和官方提供的示例基本一致，这里也做简单介绍：

- config.yml:这个文件主要用于生成qkv_clstr_hw_defines.h，我在这个文件里开了矩阵空间，他会自动生成相应的地址，这个地址会在之后的矩阵操作用到。

- 各种defines.h: 主要是对一些常量，函数进行定义。
- hw/top.c: top.c主要进行的是DMA操作的定义。
- hw/qkv.c:包括了Transformer的（几乎）全部工作流程。
- sw/bench.h:我在这里定义了初始化需要的函数，主要是内存空间初始化和输入矩阵的随机生成。
- sw/main.cpp:主要是进行仿真流程的控制。
- sw/isr.c: 中断处理。
- sw/boot.x:仿真运行所需文件。

## gem5-salam 中Transformer加速器设计方法

完整的Transformer计算流程是比较复杂的，这里我保留了一些关键步骤。以下是设计分析：

为了简化计算，这里假设输入所有矩阵和输出结果都是行列相等的正方形矩阵。

正常的计算过程应该是：

1. Q, K,　V, 输入的处理，这里假设权重都是单位矩阵，就应该是三个输入矩阵乘单位矩阵，所以可以跳过这一步，直接拿输入矩阵当作处理过的矩阵进行下一步；

2. Q\*K^T, 这一步是计算Q矩阵乘K矩阵的转置，k转置的列其实就是转置前的行，所以计算过程就是这两个矩阵对应位置相称，其结果放到输出矩阵的对应位置。这里的寻址方式是：第i行第j列的元素

## 加速器设计架构，原理，以及性能分析

## 心得感悟
