{{ self.title() }}

{{ s('background') }}

时光回到2017年6月7日。午后，阳光正好。

现在的你，在考场中笔耕不辍。在刷刷声中，你填写着交给从前和未来的自己的答卷。

像无数次训练过的那样，你直接跳到了这张数学试卷的最后一道大题，二选一的题目直接选择了后者。快速地略过了题目描述，紧缩的眉头渐渐放松。

“稳了。”

你一刻也不敢停留，又向你的梦想靠近了一小步。

{{ s('description') }}

已知两个 $n$ 维实向量 $\vec{a}=(a_1,a_2,\dots,a_n),\vec{b}=(b_1,b_2,\dots,b_n)$，定义 $n$ 个定义域为 $\mathbb{R}$ 函数 $f_1,f_2,\dots,f_n$：
$$
f_k(x)=\sum_{i=1}^{k} |a_ix+b_i| \quad (k=1,2,\dots,n)
$$
对于每个 $k=1,2,\dots,n$，试求 $f_k$ 在 $\mathbb{R}$ 上的最小值。

{{ s('input format') }}

{{ self.input_file() }}

第一行一个整数 $n$，表示向量的长度及函数的个数。

接下来两行，每行 $n$ 个实数，分别描述向量 $\vec{a},\vec{b}$ 的各个分量，以空格隔开。

对于所有的输入数据，都满足 $n\le {{tl.hn(prob.args['n'])}},0\le|a_i|,|b_i|<{{tl.hn(prob.args['a'])}}$。

{{ s('output format') }}

{{ self.output_file() }}

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

{{ s('sample', 2) }}

{{ self.sample_file() }}

{{ s('subtasks') }}

{{ tbl('data') }}

{{ s('hint') }}

后来，全国三卷的考生们又回想起了被参数方程支配的恐惧。