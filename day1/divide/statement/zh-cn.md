{{ self.title() }}

{{ s('description') }}

牛牛有一块蛋糕，他想把蛋糕分给小朋友们。

蛋糕一开始是圆形的，牛牛会在圆周上选择 $n$ （$0\le n \le64$）个点，将这几个点两两用线段连接。这些线段将会把蛋糕分成若干块。

现在，牛牛想知道，蛋糕**最多**会被分成多少块，请你告诉他答案。

{{ s('input format') }}

{{ self.input_file() }}

输入包含至多20行，每行一个整数 $n$ ，含义如上。

{{ s('output format') }}

{{ self.output_file() }}

依次回答牛牛的每个问题，对于每个问题，输出一行，包含一个整数表示答案。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

{{ img('sample.png', size = 0.5, align = 'middle', inline = False) }}