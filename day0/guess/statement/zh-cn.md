{{ self.title() }}

{{ s('background') }}

听说练习赛需要 5 个题。

但负责人太懒了，所以就有了这道充数的题。

{{ s('description') }}

Tiffany 有一个数 $K$，Yazid 除了知道这是一个不超过 $2147483647$ 的非负整数外，没有别的任何信息。

即便 Yazid 不知道任何信息，Tiffany 还是要求 Yazid 判断输入的整数 $x$ 是否**小于** $K$。

不过，善良的 Tiffany 觉得只给出这些信息未免太难为 Yazid 了，因此她向 Yazid 透露，在所有测试点中，$x$ 关于测试点编号是**单调增**的。也就是说，对于任意测试点 $i,j$：第 $i$ 个测试点给出的 $x$ 小于第 $j$ 个测试点给出的 $x$ 当且仅当 $i < j$。

可惜的是，Yazid 仍不知道答案。你能帮帮愚蠢可怜的 Yazid 吗？

{{ s('input format') }}

{{ self.input_file() }}

一个整数 $x$。

保证 $0\leq x\leq 2148473647$。

{{ s('output format') }}

{{ self.output_file() }}

输出一行，如果 $x < K$，则输出 `yes`；否则输出 `no`。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('hint') }}

如果你的某次提交未能通过，OJ 将返回你**第一个**未能通过的测试点的错误信息。比如，对于所有测试点，如果你的程序的评测结果依次为：`Accepted`（通过）、`MLE`、`TLE`、`Accepted`（通过）、`WA`、……，那么 OJ 将反馈的评测结果为 `MLE`。