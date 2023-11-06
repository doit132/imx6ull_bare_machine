# 实验环境介绍

- 韦东山 imx6ull_pro 开发板
- 交叉编译工具链: gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabi

## 注意

- imx6ull 是不需要编写 bootloader 的, 它有自带的 bootROM , 需要去了解 imx6ull 的启动过程和启动方式
- 参考: <https://blog.csdn.net/fengyuwuzu0519/article/details/107115556> 或 教程提供的 i.MX.6ULL裸机开发手册_V1.0.pdf
