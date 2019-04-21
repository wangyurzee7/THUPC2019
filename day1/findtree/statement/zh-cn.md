{{ self.title() }}

{{ s('description') }}

定义 $\otimes_1, \otimes_2, \otimes_3$ 分别为按位与、按位或、按位异或运算，记 $a_i$ 表示 $a$ 的第 $i$ 个二进制位。定义一个作用在 $w$ 位二进制数上的新运算 $\oplus$，满足 $(a\oplus b)_i = a_i \otimes_{o_i} b_i$。不难验证 $\oplus$ 运算满足结合律和交换律。

给出一张 $n$ 个点 $m$ 条边的无向图，每一条边的权值是一个 $w$ 位二进制数。请你找一棵原图的生成树。设你找出的生成树中的边边权分别为 $w_1,\cdots,w_{n-1}$，请你最大化 $w_1\oplus w_2\oplus\cdots\oplus w_n$。

{{ s('input format') }}

{{ self.input_file() }}

第一行 $n,m$；

第二行一个长度为 $w$ 的串，串中的每个字符为 `&`、`|`、`^`  中的一个（分别代表与、或和异或），表示每一个 $\otimes_i$。

接下来 $m$ 行，每一行 $x,y,v$，表示一条连接 $x$ 和 $y$ 权值为 $v$ 的边，保证 $0\le v < 2^w$。

保证 $n\le 70$，$w\le 12$。

{{ s('output format') }}

{{ self.output_file() }}

<<<<<<< HEAD
输出一行一个数，表示答案。如果图不连通，输出 `-1`。
=======
这是 cjk 的输出格式
>>>>>>> ca6ae20fd442764dc8a94f1d0c93a6c3ac5825a0

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

<<<<<<< HEAD
{{ s('subtasks') }}

$n\le 70$，$w\le 12$，$m\le 5000$。
=======
这是 cjk 的样例解释
>>>>>>> ca6ae20fd442764dc8a94f1d0c93a6c3ac5825a0
