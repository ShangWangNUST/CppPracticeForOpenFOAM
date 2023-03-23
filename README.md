# CppPracticeForOpenFOAM
本频道主要介绍 OpenFOAM 框架下 Cpp 的基本应用：主要介绍了 OpenFOAM 的基本框架，各个模块类型的运行机制及个人定制办法，对常用一些后处理也会有所涉猎。

---
## OpenFOAM® 版本
当前所有介绍模块基于 OpenFOAM-10，OpenFOAM-8，9 部分模块也进行过一些测试可以运行。如果部分模块运行出现问题，可以根据当前版本查找对应内容解决办法。

---
## 使用方法简介
本频道中没有 step-by-step 教程，进本的使用方法与 OpenFOAM 中 Case 类似，各个模块相互独立，默认参考本频道的 OpenFOAMer 已经了解了 OpenFOAM 基本算例的运行流程。

每个模块包括：1）程序源码用以说明该模块功能；2）算例展示程序功能的具体实现。

多数模块中的编译可以通过 `wmake` 实现，模块的基本实现流程如下：
```
./wmake
cd testCase
./run
```

---
## 000_Case0 - OpenFOAM 编译框架简介

通过 OpenFOAM 实现基本的信息输出，明确 OpenFOAM 的基本程序编译过程。

---
## 001_Case1 - OpenFOAM 数据的输入输出

1. 介绍 OpenFOAM 的基本变量类型
2. 介绍 OpenFOAM 的字典文件结构
3. 如何初始化字典类对象，读取指定字典文件信息
4. 对所需信息进行输出：控制台输出、文件输出

---
## 002_Case2 - OpenFOAM Mesh

介绍 OpenFOAM 中多面体网格的基本信息，主要包括：points、faces、owner、neighbour、boundary、（pointZones、faceZones、cellZones基本用不到，暂不介绍）。

---
## 003_Case3 - OpenFOAM 基本场操作

介绍了 OpenFOAM 场相关的基本类：单元标量场（volScalarField）、单元矢量场（volVectorField）、面标量场（surfaceScalarField）、面矢量场（surfaceVectorField）。说明各类场的基本方法，如：pow、mag、gSum等。

---
## 004_Case4 - OpenFOAM main 函数参数，运行脚本

1. 介绍了 OpenFOAM 中 main 函数参数的基本实现，主要包括：基本位置参数、关键字参数等。
2. 简单介绍基本算例脚本的编写方法。

---
## 005_Case5 - OpenFOAM 并行编程基本方法介绍

以 Cavity 为基础介绍了基于 OpenFOAM 的并行编程方法的基本实现。

---
## 006_Case6 - OpenFOAM 自定义类

介绍了 OpenFOAM 中基本类方法的基本实现。

---
## 007_Case7 - OpenFOAM 自定义库

介绍了 OpenFOAM 如何自定义库，及自定义库的基本应用方法。

---
## 008_Case8 - 自定义边界

介绍了如何自定义边界类型，将定义边界应用到既定算例中。

---
## 009_Case9 - OpenFOAM 多物理场数据读取与基本插值方法

介绍了 OpenFOAM 中节点数据与体心数据的基本交互实现：插值，提供了 FEM 和 FVM 方法数据相互转换的可能。

---
# ···后续内容计划
## 010_Case10 - 输运方程

---
## 011_Case11 - 网格修改

---
## 012_Case12 - 自定义动量源

---
## 013_Case13 - 波方程

---
## 014_Case14 - SIMPLE 算法

---
## 015_Case15 - 离散方法

--- 
## 016_Case16 - Lagrangian 粒子追踪
