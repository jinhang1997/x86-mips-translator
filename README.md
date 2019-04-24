# x86-mips 二进制翻译器

## 欢迎合作

- 若您对本项目有兴趣，欢迎给我们加星星；如果您很希望提出建议，可以在 `issue` 里面告诉我们
- 若您发现本项目的不足，欢迎 fork 我们的项目并参与开发

## 项目介绍

- x86-MIPS 二进制翻译器
- 用 MIPS 指令表出 x86 指令
- 目前支持的程序结构
  - 分支、循环
  - 函数调用（用户函数、库函数）
  - 函数递归调用

## 开发团队

南京航空航天大学计算机科学与技术学院

金航、王山岳、秦瑞哲、蔡益武

指导教师：冯爱民老师

## Git Commit 格式

```bash
git commit -m "type: descriptions"
```
type 有以下种类：

  * feat：新功能（feature）
  * fix：修补bug
  * docs：文档（documentation）
  * style： 格式（不影响代码运行的变动）
  * refactor：重构（即不是新增功能，也不是修改bug的代码变动）
  * test：增加测试
  * chore：构建过程或辅助工具的变动

例如：

```bash
git commit -m "feat: generate converted mov instructions"
```
