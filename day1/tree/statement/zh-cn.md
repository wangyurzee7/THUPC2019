
{{ self.title() }}

{{ s('description') }}

给出一棵 $n$ 个节点的树，结点标号从 $1$ 到 $n$。

定义树上两点 $a,b$ 间的距离 $d\left( a,b\right)$ 是最小的非负整数 $k$，满足存在结点序列 $v_0,v_1,\dots ,v_k$，满足 $v_0=a$、$v_k=b$、且对于 $0\leq i\leq k-1$ 有 $v_i$ 和 $v_{i+1}$ 之间在树上有一条边相连。

有 $m$ 个询问，每个询问包含参数 $p_0,d_0,p_1,d_1$，求：

$$\sum\limits_{d\left(p_0,a\right)\leq d_0} {\sum\limits_{d\left(p_1,b\right)\leq d_1} {d(a,b)}}$$

{{ s('input format') }}

{{ self.input_file() }}

第一行一个正整数 $n$，表示树的节点数目。

接下来一行 $n-1$ 个整数 $f_2 ,f_3 ,\dots, f_n$，依次表示 $i$ 和 $f_i$（$1\leq f_i\leq i-1$） 之间有一条边。

接下来一行一个非负整数 $m$，表示询问数目。

接下来 $m$ 行依次描述所有询问：每行四个整数 $p_0,d_0,p_1,d_1$ （$1\leq p_0 ,p_1\leq n$，$0\leq d_0 ,d_1\leq n-1$）描述一组询问。

保证 $n\leq 10^5$，$m\leq 10^5$。

{{ s('output format') }}

{{ self.output_file() }}

共 $m$ 行，依次回答各组询问：每行输出一行一个整数表示这组询问的答案。

{{ s('sample') }}

{{ self.sample_text() }}
