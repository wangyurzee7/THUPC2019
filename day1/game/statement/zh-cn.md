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

上面是自动读入样例 `1.in/ans`（存储在 `down` 文件夹内） 然后渲染到题面中；如果只有一组样例，则去掉 `1` 或将其替换成空串，样例仍然保存成 `1.in/ans`。上面的 `1` 可以是字符串。

{{ self.title_sample_description() }}

这是第一组数据的样例说明。

{{ s('sample', 2) }}

{{ self.sample_file() }}

上面是只提示存在第二组样例，但不渲染到题面中。

{{ s('subtasks') }}

不要使用markdown原生的表格，使用下列方式渲染一个表格，其中表格存放在试题目录的 `tables` 子目录下。

{{ tbl('data') }}

{{ tbl('table', width = [1, 6]) }}

原理上用一个二维的 json 表格或 python 表格存储，`null` 表示和上一行合并，不支持横向合并。建议用 python 的格式写，如例子中的 `data.pyinc`，这样可以根据数据生成；跟数据无关的表格则可以像 `table.json` 那样存储。

{{ s('scoring') }}

这是评分方法，如果有必要的话。

{{ s('hint') }}

这里是一个非常温馨的提示。
