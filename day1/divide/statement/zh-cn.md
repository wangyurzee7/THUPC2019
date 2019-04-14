{{ self.title() }}

{{ s('background') }}

这是张鸽鸽的背景

{{ s('description') }}

这是张鸽鸽的问题描述

{{ s('input format') }}

{{ self.input_file() }}

这是张鸽鸽的输入格式

{{ s('output format') }}

{{ self.output_file() }}

这是张鸽鸽的输出格式

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

这是张鸽鸽的样例解释

{{ s('sample', 2) }}

{{ self.sample_file() }}

上面是只提示存在第二组样例，但不渲染到题面中。

{{ s('hint') }}

这是张鸽鸽的温馨提示