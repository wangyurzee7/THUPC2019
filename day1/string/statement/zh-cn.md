{{ self.title() }}

## {{ _('Background') }}

Yazid 和 Tiffany 喜欢字符串问题。在这里，我们将给你介绍一些关于字符串的基本概念。如果你是一名熟练的算法竞赛选手，则你基本上可以忽略它们。

对于一个字符串 $S$， 我们定义 $\lvert S\rvert$ 表示 $S$ 的长度。

接着，我们定义 $S\left(i\right)$（$1\leq i\leq\lvert S\rvert$）表示 $S$ 中从左往右数第 $i$ 个字符；该串 $S\left( {L,R}\right)$ 表示由 $S$ 中从左往右数，第 $L$ 个字符到第 $R$ 个字符依次连接形成的字符串，特别地，如果 $L < 1$ 或 $R > \lvert S\rvert$ 或 $L > R$，则 $S\left( L,R\right)$ 表示空串。

我们说两个字符串相等，当且仅当它们的长度相等，且从左至右各位上的字符依次相同。

我们说一个字符串串 $T$ 是字符串 $S$ 的子串，当且仅当存在 $L,R$，使得 $S\left( L,R\right)=T$。

对于两个不相等的字符串 $S,T$，比较它们字典序大小的规则如下：

* 空串的字典序小于任意非空字符串。

* 如果两字符串均非空，且 $S\left( 1\right)\neq T\left( 1\right)$，则它们的字典序比较结果即为 $S\left( 1\right), T\left( 1\right)$ 的比较结果。

* 如果两字符串均非空，且 $S\left( 1\right) = T\left( 1\right)$，则它们的字典序比较结果即为 $S\left( 2,\lvert S\rvert\right), T\left( 2,\lvert S\rvert\right)$ 的字典序比较结果。

## {{ _('Description') }}

给定多个**模式串** $S_1,\dots,S_m$。如果一个字符串的**所有长度为 $K$ 的子串**均为**至少一个模式串的子串**，则我们说这个字符串是 $K$-Yazid 的。

举例而言：如果仅有一个模式串 `abac`，那么字符串 `babac` 就是 $2$-Yazid 的，但字符串 `abc` 并不是 $2$-Yazid 的，因为包含一个长度为 $2$ 的子串 `bc` 并不是模式串的子串。

Tiffany 希望你求出**最小的正整数** $k$，满足不存在长度超过 $\sum_{i=1}^{m} \lvert S_i\rvert$ 的 $k$-Yazid 串。

在此基础上，Tiffany 还希望你求出**长度最大**的 $k$-Yazid 串中**字典序最小**的字符串 $T$。

## {{ _('Input Format') }}

{{ self.input_file() }}

第 $1$ 行一个正整数 $m$，表示模式串的数目。

第 $2$ 行至第 $m+1$ 行，每行一个仅包含小写字母的非空字符串，其中第 $i+1$ 行的字符串为 $S_i$。

保证 $1\leq \sum_{i=1}^m \lvert S_i \rvert\leq 5\times 10^5$，这也意味着 $m\leq 5\times 10^5$。

## {{ _('Output Format') }}

{{ self.output_file() }}

第 $1$ 行一个整数 $k$，即为满足【题目描述】中要求的最小非负整数。

第 $2$ 行一个字符串 $T$，表示字典序最小的最长 $k$-Yazid 串。

{% set vars = {} -%}
{%- do vars.__setitem__('sample_id', 1) -%}
{{ self.sample_text() }}

{% do vars.__setitem__('sample_id', 2) -%}
{{ self.sample_text() }}

