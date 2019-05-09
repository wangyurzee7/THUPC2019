{{ self.title() }}

{{ s('description') }}

Yazid 喜欢吃大碗宽面。现有 $m$ 碗宽面，其中第 $i$ 碗宽面（$1\leq i\leq m$）共包含 $n_i$ 根面条，它们的宽度分别为 $A_{i,1},A_{i,2},\dots A_{i,n_i}$。

记 $f\left( u,v\right)$ 表示若混合第 $u$ 碗宽面和第 $v$ 碗宽面，将得到的超大碗宽面的**第 $\lfloor\frac{n_u +n_v +1}{2}\rfloor$ 小**的面条宽度（$\lfloor x\rfloor$ 表示不超过 $x$ 的最大整数）。

Yazid 想求出所有 $f\left( u,v\right)$，但为了节省你的输出时间，你只需要对所有 $1\leq u\leq m$ 求出：

* $R\left(u\right)=\mathop{\mathrm{xor}}\limits_{v=1}^{m} {\left(f\left(u,v\right)+u+v\right)}$（$\mathrm{xor}$ 指异或运算，在 C++ 语言中对应 `^` 运算符）。

{{ s('input format') }}

{{ self.input_file() }}

第一行一个正整数 $m$，表示宽面碗数。

接下来 $m$ 行，每行若干个用单个空格隔开的整数描述一碗宽面：这部分的第 $i$ 行的第一个正整数为 $n_i$，表示第 $i$ 碗宽面包含的面条数；接下来 $n_i$ 个非负整数 $A_{i,1},A_{i,2},\dots A_{i,n_i}$ 描述各面条的宽度。

保证 $m\leq 10000$，$n_i\leq 500$，$0\leq A_{i,j}\leq 10^9$。

{{ s('output format') }}

{{ self.output_file() }}

输出 $n$ 行，每行一个整数，其中第 $i$ 行的整数为 $R\left(i\right)$。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

$R\left(1\right)=\left(f\left(1,1\right)+2\right)+\left(f\left(1,2\right)+3\right)+\left(f\left(1,3\right)+4\right)=4\mathrm{ \, xor\, }6\mathrm{ \, xor\, }6=4$

$R\left(2\right)=\left(f\left(2,1\right)+3\right)+\left(f\left(2,2\right)+4\right)+\left(f\left(2,3\right)+5\right)=6\mathrm{ \, xor\, }8\mathrm{ \, xor\, }9=7$

$R\left(3\right)=\left(f\left(3,1\right)+4\right)+\left(f\left(3,2\right)+5\right)+\left(f\left(3,3\right)+6\right)=6\mathrm{ \, xor\, }9\mathrm{ \, xor\, }8=7$
