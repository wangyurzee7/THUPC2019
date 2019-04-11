
{{ self.title() }}

{{ s('description') }}

给出一棵n个结点的树，结点标号为1到n的整数。  

定义树上两点a,b间的距离d(a,b)是最小的非负整数k，使得存在结点序列$v_i$(0≤i≤k)，其中$v_0$=a,$v_k$=b，当0≤i≤k-1时$v_i$和$v_{i+1}$之间在树上有一条边相连。  

有m个询问，每个询问形如p0 d0 p1 d1，问所有满足d(p0,a)≤d0且d(p1,b)≤d1的有序点对a,b的距离d(a,b)之和。  

{{ s('input format') }}

{{ self.input_file() }}

第一行一个整数n(1≤n≤100000)，  

接下来一行n-1个整数$f_2$, $f_3$, ... ,$f_n$，表示i和$f_i$之间有一条边(2≤i≤n, 1≤$f_i$≤i-1)，  

接下来一行一个整数m(1≤m≤100000)，  

接下来m行每行四个整数p0 d0 p1 d1表示一组询问(1≤p0≤n，0≤d0≤n-1，1≤p1≤n，0≤d1≤n-1)。  

{{ s('output format') }}

{{ self.output_file() }}

共m行，对每个询问输出一行表示答案。  

{{ s('sample') }}

{{ self.sample_text() }}
