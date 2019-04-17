{{ self.title() }}

{{ s('background') }}

这样的子标题会被程序自动处理，可以方便翻译和提取每个部分等。如果你想自己定义子标签（尽管我们一般**不推荐**自己定义 s 标签），或者不需要国际化的话，你可将这些子标题直接写成这样：

```
{{ s('如何使用交互库') }}
### 对于使用C/C++的选手
```

If you want an English statement file, just copy this file as *en.md* and replace any Chinese text into English.

更加详细的题目书写文档在[这里](https://git.thusaac.org/publish/tuack/wikis/%E9%A2%98%E9%9D%A2%E7%9A%84%E4%B9%A6%E5%86%99)。

如果你不需要某些章节，可以直接删除。比如这一段是“题目背景”，很多题目其实并不需要这一段。

子标题请**不要**自己手动加方括号 `【】` 。

{{ s('description') }}

**要强调的东西**这么写。一般只有 *file_name* 使用斜体，不用斜体表强调。

行内的公式：$\sin \left(a x + b \right)$。注意使用规范的公式书写方式，例如一些常见错误的正确写法为：

```
\sin	#有斜杠
\log
\max
\bmod	#最常用的取模是bmod
a~\mathrm{xor}~b	#不存在的算符可以这么造
O\left(\frac{nm}{w}\right)
#用left和right把括号变高以括住比较高的式子
#不要用*和/表示乘除号，而用省略乘号、\times、\cdot和\div、分数表示
d\left(a_i, b_j\right)	#多用括号和下标表示下标和参数，尽量不用方括号
```

行间的公式：
$$
\frac{-b\pm\sqrt{b^2-4ac} }{2a}
$$

1. 第一点
2. 第二点

* 第一点
* 第二点

字符串或代码 `This is a string`，文件名是斜体，代码是字符串。注意英文、字符串、公式和中文之间要**加一个空格**，和标点符号之间不加空格。注意按照《[标点符号用法](http://www.moe.gov.cn/ewebeditor/uploadfile/2015/01/13/20150113091548267.pdf)》（教育部国标 GB/T 15834-2011）使用标点符号，注意不要有**错别字**、**语病**。

成块的代码、数据这么写：

```
int main(int argc, char** argv);
```

除公式内可以使用 tex 的部分语法外，不要直接使用任何 html 语法和 tex 语法。替代方案如下：

不要用 markdown 自带的语法插入图片（因为目前支持不好），用下列语法插入图片：

{{ img('sample.png', size = 0.5, align = 'middle', inline = False, caption='图片样例', label='fig:sample') }}

其中 `inline` 为 `False` 表示这是一个独占一行的图片，此时支持 `align`，选项为 `left`，`middle` 或 `right`。后面这些参数可以不写。如果添加了 `caption` 字段，则对于 tex 的渲染结果，会在图片下方出现类似于“图1：图片样例”字样。

图片需要保存在试题目录的 `resources` 子目录下。

如果有本工具不能提供的功能，需要直接使用 tex 或 html 代码的，请使用下列方式以免另外一种格式下出错。（注意代码不要放在```中）

```python
{{ render(json.dumps('\\clearpage'), 'tuoi') }}
{{ render(json.dumps('<a href="http://oj.thusaac.org">TUOJ</a>'), 'html') }}
```

上述第一个例子是为了排版好看强行加入一个分页符的意思，其中 `tuoi` 表示只在生成 TUOI 风格题面的时候使用这个；第二个例子是在生成任何 html 格式题目的时候加入一个广告（雾）。

可选的参数有 `html`，`md`，`tex`，`noi`，`uoj`，`ccpc`，`ccc`，`tuoj`，`ccc-tex`，`ccc-md`，`tuoi`，`tupc`。参数可以有多个，写成一个数组即可，例如 `['tuoi', 'noi']`。

**不要在题面里直接写tex或html代码！**

{{ s('input format') }}

{{ self.input_file() }}

上面会根据具体的评测环境说明输入是文件还是标准输入等。

输入的第一行包含一个正整数 $n$，保证 $n \le {{ tl.hn(args['n']) }}$。←这是引用 *conf.yaml* 中的 `args` 的 `n` 项，然后用“好看”的格式输出。“好看”的格式如 `10^9`，`1,000,000,007`。

引用 *conf.yaml* 的方法是使用变量 `prob`，例如可以写成 `prob.args['n']`，还可以写成 `prob['args']['n']`。引用 `args` 项、`data` 项、`samples` 项和 `pre` 项可以简写成例如 `args['n']` 或 `args.n`。在下文的表格中也一样。

输入的第二行包含一个正整数 $m$，保证 $m \le {{ tl.hn(aargs.max('m')) }}$。

↑`aargs.min` 是取出 `data` 项、`samples` 项和 `pre` 项中的所有同名变量的最小值，类似的函数还有 `max` 和 `sum`。形如 `aargs['m']` 可以取出所有同名变量的迭代器。和 python 的 `dict` 类似，还可以用形如 `aargs.get('m', 0)` 指定“如果没有某项用什么对象补空”，`sum`、`min` 和 `max` 类似。如果只取出 `data` 项、`samples` 项或 `pre` 项中的同名函数，使用 `dargs`、`sargs` 或 `pargs`。

`tl` 是 `tools` 的简写，是一组工具。除 `hn` 外，还包括内建函数如 `tl.int`，`math` 中的对象或函数如 `tl.sin`，`datetime` 中的对象或函数如 `tl.time` 类，`num2chinese` 函数（可以把数字转化成中文）。

{{ s('output format') }}

{{ self.output_file() }}

输出一个字符串 `Yes`。出题人在写题面的时候注意**不要**写成 `“Yes”（不包含引号）`。

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