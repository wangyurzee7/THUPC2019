{{ self.title() }}

{{ s('description') }}

现在有一个长度为 $N$ 的整数序列 $S$，Alice 和 Bob 在这个序列上博弈。

游戏按轮进行，每一轮中：

* Alice 给出一个长度为 $N$ 的正整数序列 $T$
* Bob 看到 Alice 给出的 $T$，然后选择 $[0, N-1]$ 里的一个整数 $x$
* 之后我们把 $S$ 转化为 $S'$，规则如下：

$$
S'[i] = S[i] + T[(i+x)\bmod N]
$$

* 以 $S'$ 作为新的 $S$，结束这一轮。

如果某一轮结束后，$S$ 中每个数都是一个给定质数 $P$ 的倍数，那么 Alice 胜利。

给定 $N$ 和初始序列 $S$，问题：Alice 是否能在有限步必胜，如果答案为是，最快可以在几轮内保证胜利。

{{ s('input format') }}

{{ self.input_file() }}

第一行两个数 $N,P$，保证 $N\le 3\times 10^5, P\le 200$ 且 $P$ 是一个质数。

接下来一行 $N$ 个空格隔开的整数，描述初始序列 $S$。

{{ s('output format') }}

{{ self.output_file() }}

输出一个整数，如果 Alice 不能在有限步必胜，输出 $-1$，否则输出一个整数 $x$ 表示 Alice 最快能在几轮内胜利。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

**这是吕老板的样例解释**

{{ s('sample', 2) }}

{{ self.sample_file() }}

上面是只提示存在第二组样例，但不渲染到题面中。

{{ s('hint') }}

**这里是一个吕老板的非常温馨的提示。**
