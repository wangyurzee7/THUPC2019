{{ self.title() }}

## {{ _('Background') }}

首先我们回忆一下经典难题过河卒问题：

棋盘上$A$点有一个过河卒，需要走到目标$B$点。卒行走的规则：可以向上、或者向右。同时在棋盘上$C$点有一个对方的马，该马所在的点和所有跳跃一步可达的点称为对方马的控制点，因此称之为“马拦过河卒”。

棋盘用坐标表示，$A$点$(1,1)$、$B$点$(N,M)$，同样马的位置坐标是需要给出的。

现在要求你计算出卒从$A$点能够到达$B$点的路径的条数，假设马的位置是固定不动的，并不是卒走一步马走一步。

**请注意，上述背景内容与本题无关！**

## {{ _('Description') }}

Kiana喜欢玩象棋，尤其是喜欢用象棋玩过河卒的游戏。在传统的过河卒问题中，Kiana需要控制一个卒从起点走到终点，在路中避开一个对方的马的攻击，然后假装不会算并询问你从起点到终点的路径总数。

在今天的过河卒二游戏中，Kiana还是控制一个卒在一个$N\times M$的棋盘上移动，初始时卒位于左下方坐标为$(1,1)$位置，但为了增加难度，Kiana对游戏规则做出了一些修改。传统的过河卒每步只能向上或向右移动$1$格，Kiana规定自己的过河卒二还可以在一步中向右上方移动$1$格，即如果当前卒位于坐标$(x,y)$处，则下一步可以走到$(x+1,y)$、$(x,y+1)$或$(x+1,y+1)$中的任意一格里面去，同时Kiana认为，如果两种移动方案在某一步时卒移动的方向（右、上或右上）不同，则两种方案就是不同的，例如从$(1,1)$先走到$(1,2)$再走到$(2,2)$、从$(1,1)$先走到$(2,1)$再走到$(2,2)$和从$(1,1)$直接走到$(2,2)$是三种不同的移动方案。

其次，过河卒二的终点不再是一个特定的位置，Kiana规定卒可以从棋盘的上方或右方走出棋盘，此时就视为游戏成功。注意在走出棋盘时仍然有方向选择的不同，例如若过河卒位于$(1,M)$处，则下一步它可以向右或者向右上用两种方式走出棋盘，若过河卒位于$(N,M)$处，则下一步它可以向上、向右或者向右上用三种方式走出棋盘，以不同的方式走出棋盘仍然被算作是不同的移动方案。

此外，对方马的攻击范围不再是有规律的几个位置，而是Kiana规定好的$K$个特定坐标，并要求过河卒在移动的过程中不能走到这$K$个坐标的任何一个上，在除这些坐标以外的位置上过河卒都可以按规则自由移动。

现在Kiana想知道，过河卒二有多少种不同的移动方案可以走出棋盘，这个答案可能非常大，她只想知道方案数对$59393$取模后的结果。由于她不会算，所以希望由你来告诉她。

## {{ _('Input Format') }}

{{ self.input_file() }}

第一行包含三个整数$N$、$M$和$K$，分别表示棋盘的坐标范围与对方马的攻击格子数（即Kiana规定的不能经过的坐标数）。

接下来$K$行，第$i$行包含两个正整数$X_i$和$Y_i$，表示对方马的第$i$个攻击坐标为$(X_i,Y_i)$。

对于所有数据，保证$1\leq N\leq 10^9, 1\leq M\leq 10^5, 0\leq K\leq 20, 1\leq X_i\leq N, 1\leq Y_i\leq M$，$(1,1)$一定不会被对方马攻击，且被攻击的格子中不存在两个坐标相同的格子。

## {{ _('Output Format') }}

{{ self.output_file() }}

输出一行一个整数，表示过河卒走出棋盘的方案数对$59393$取模后的结果。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

用$\uparrow$表示过河卒向上移动了一格，用$\rightarrow$表示过河卒向右移动了一格，用$\nearrow$表示过河卒向右上移动了一格，由此可以简化样例解释的表述。

$24$种移动方案如下：$(\uparrow\uparrow\uparrow)$、$(\uparrow\uparrow\nearrow)$、$(\uparrow\uparrow\rightarrow\uparrow)$、$(\uparrow\uparrow\rightarrow\nearrow)$、$(\uparrow\uparrow\rightarrow\rightarrow\uparrow)$、$(\uparrow\uparrow\rightarrow\rightarrow\nearrow)$、$(\uparrow\uparrow\rightarrow\rightarrow\rightarrow)$、$(\uparrow\nearrow\uparrow)$、$(\uparrow\nearrow\nearrow)$、$(\uparrow\nearrow\rightarrow\uparrow)$、$(\uparrow\nearrow\rightarrow\nearrow)$、$(\uparrow\nearrow\rightarrow\rightarrow)$、$(\rightarrow\rightarrow\rightarrow)$、$(\rightarrow\rightarrow\nearrow)$、$(\rightarrow\rightarrow\uparrow\rightarrow)$、$(\rightarrow\rightarrow\uparrow\nearrow)$、$(\rightarrow\rightarrow\uparrow\uparrow\rightarrow)$、$(\rightarrow\rightarrow\uparrow\uparrow\nearrow)$、$(\rightarrow\rightarrow\uparrow\uparrow\uparrow)$、$(\rightarrow\nearrow\rightarrow)$、$(\rightarrow\nearrow\nearrow)$、$(\rightarrow\nearrow\uparrow\rightarrow)$、$(\rightarrow\nearrow\uparrow\nearrow)$、$(\rightarrow\nearrow\uparrow\uparrow)$。
