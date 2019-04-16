{{ self.title() }}

{{ s('description') }}

定义 $\otimes_1, \otimes_2, \otimes_3$ 分别为按位与、按位或、按位异或运算，记 $a_i$ 表示 $a$ 的第 $i$ 个二进制位。定义一个作用在 $w$ 位二进制数上的新运算 $\oplus$，满足 $(a\oplus b)_i = a_i \otimes_{o_i} b_i$。不难验证 $\oplus$ 运算满足结合律和交换律。

给出一张 $n$ 个点 $m$ 条边的无向连通图，每一条边的权值是一个 $w$ 位二进制数。请你找一棵原图的生成树。设你找出的生成树中的边边权分别为 $w_1,\cdots,w_{n-1}$，请你最大化 $w_1\oplus w_2\oplus\cdots\oplus w_n$。

{{ s('input format') }}

{{ self.input_file() }}

这是 cjk 的输入格式

保证 $n\le 100$，$w\le 10$。

{{ s('output format') }}

{{ self.output_file() }}

这是 cjk 的输出格式

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

这是 cjk 的样例解释