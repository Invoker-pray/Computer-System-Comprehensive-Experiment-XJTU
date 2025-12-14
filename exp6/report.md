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

## gem5-salam 中Transformer加速器设计方法

## 加速器设计架构，原理，以及性能分析

## 心得感悟
