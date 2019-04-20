{{ self.title() }}

作者，版权声明等

## 题目简述

可以把题目的要点再说一遍。

## 子任务设计

如果有的话，也许需要解释一下部分分都是怎么设计的。

## 算法1：暴力

$$
f(x)=\sum_{i=1}^{k}\lvert a_ix+b_i\rvert\\
c_i=-\frac{b_i}{a_i}\\
c_i<c_j\Rightarrow a_jb_i>a_ib_j\\
A =-\sum \lvert a_i \rvert
$$

$$
A+2\sum_{c_i\le x}\lvert a_i\rvert\ge0
$$

