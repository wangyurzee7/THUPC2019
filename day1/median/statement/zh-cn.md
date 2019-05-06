{{ self.title() }}

{{ s('description') }}

Yazid 和 Tiffany 喜欢中位数。对于一个长度为 $n$ 的序列 $A_1,A_2,\dots,A_n$ 而言，其中位数指的是：该序列在升序排序后 $A_{\lfloor\frac{n+1}{2}\rfloor}$ 的值（$\lfloor x\rfloor$ 表示不超过 $x$ 的最大整数）。

Tiffany 有 $m$ 个序列，其中长度为 $n_i$ 的第 $i$ 个（$1\leq i\leq m$）序列为 $A_{i,1},A_{i,2},\dots A_{i,n_i}$。

记 $f\left( u,v\right)$ 表示第 $u$ 个序列和第 $v$ 个序列合并得到的序列（即由两个序列的共 $n_u +n_v$ 个元素组成的新序列）的中位数。Yazid 想求出所有 $f\left( u,v\right)$，但为了节省你的输出时间，你只需要对所有 $1\leq u\leq m$ 求出：

* $R\left(u\right)=\mathop{\mathrm{xor}}\limits_{v=1}^{n} {\left(f\left(u,v\right)+u+v\right)}$（$\mathrm{xor}$ 指异或运算，在 C++ 语言中对应 `^` 运算符）。

{{ s('input format') }}

{{ self.input_file() }}

第一行一个正整数 $m$，表示序列数目。

接下来 $m$ 行，每行若干个用单个空格隔开的整数描述一个序列：这部分的第 $i$ 行的第一个正整数为 $n_i$，表示第 $i$ 个序列的长度；接下来 $n_i$ 个非负整数 $A_{i,1},A_{i,2},\dots A_{i,n_i}$ 描述第 $i$ 个序列。

保证 $m\leq 10000$，$n_i\leq 500$，$0\leq A_{i,j}\leq 10^9$。

{{ s('output format') }}

{{ self.output_file() }}

输出 $n$ 行，每行一个整数，其中第 $i$ 行的整数为 $R\left(i\right)$。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

$R\left(1\right)=\left(f\left(1,1\right)+1+1\right)+\left(f\left(1,2\right)+1+2\right)+\left(f\left(1,3\right)+1+3\right)=4\mathrm{\space xor\space }6\mathrm{ \space xor\space }6=4$

$R\left(2\right)=\left(f\left(2,1\right)+2+1\right)+\left(f\left(2,2\right)+2+2\right)+\left(f\left(2,3\right)+2+3\right)=6\mathrm{\space xor\space }8\mathrm{ \space xor\space }9=7$

$R\left(3\right)=\left(f\left(3,1\right)+3+1\right)+\left(f\left(3,2\right)+3+2\right)+\left(f\left(3,3\right)+3+3\right)=6\mathrm{\space xor\space }9\mathrm{ \space xor\space }8=7$
