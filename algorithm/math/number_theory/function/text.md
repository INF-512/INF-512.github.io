数论函数学习笔记

# 前言

狄利克雷卷积是个非常神奇的东西，它能将一些看似无关的数论函数联系起来。

# 数论函数

数论函数是一种将正整数映射到实数的函数。

# 常用数论函数

单位元函数：$\varepsilon(n)=[n=1]$。

幂函数：$\text{id}_k(n)=n^k$，$\text{id}_1(n)$ 通常记作 $\text{id}(n)$。

恒等函数：$\text{id}(n)=n$。

常数函数：$1(n)=1$。

除数函数：$\sigma_k(n)=\sum_{d|n}d^k$，$\sigma_0$ 通常记作 $d(n)$ 或 $\tau(n)$，$\sigma_1(n)$ 通常记作 $\sigma(n)$。

欧拉函数：$\varphi(n)=\sum_{i=1}^n[\text{gcd}(i,n)=1]$。

莫比乌斯函数：$\mu(n)=
\begin{cases}
 1 & n=1 \\
 0 & n 含有平方因子 \\
 (-1)^k & k 为 n 的本质不同质因子个数
\end{cases}$。

# 积性函数

若函数 $f(n)$ 满足 $f(1)=1$ 且对于任意两个互质的数 $a, b$ 都有 $f(a)f(b)=f(ab)$，则 $f(n)$ 是积性函数。

# 狄利克雷卷积

对于两个数论函数 $f(n)$ 和 $g(n)$，它们的狄利克雷卷积定义为 $(f*g)(n) = \sum_{xy=n}f(x)g(y) = \sum_{d|n}f(d)g(\frac{n}{d})$，简记为 $f*g$。

# 常用公式

$1.$ $(f*\varepsilon)(n)=f(n)$

证明：

$$
\begin{aligned}
 (f*\varepsilon)(n) & =\sum_{d|n}f(d)\varepsilon(\frac{n}{d})\\
  & =\sum_{d|n}f(d)[\frac{n}{d}=1] \\
  & =\sum_{d|n}f(d)[d=n] \\
  & =f(n)
\end{aligned}
$$

$2.$ $(f*1)(n)=\sum_{d|n}f(d)$

证明：

$$
\begin{aligned}
 (f*1)(n) & =\sum_{d|n}f(d)1(\frac{n}{d}) \\
  & =\sum_{d|n}f(d)
\end{aligned}
$$

$3.$ $(\text{id}_k*1)(n)=\sigma_k(n)$

证明：

$$
\begin{aligned}
 (\text{id}_k*1)(n) & =\sum_{d|n}\text{id}_k(n) \\
  & =\sum_{d|n}n^k \\
  & =\sigma_k(n)
\end{aligned}
$$

$4.$ $(\varphi*1)(n)=\text{id}(n)$

证明：

我们先证 $(\varphi*1)(p^m)=\text{id}(p^m)$，$p$ 是质数，且 $m\ge 1$。

$$
\begin{aligned}
 (\varphi*1)(p^m) & =\sum_{d|p^m}\varphi(d)1(\frac{p^m}{d}) \\
  & =\sum_{d|p^m}\varphi(d) \\
  & =\sum_{i=0}^{m}\varphi(p^i) \\
  & =\varphi(1)+\sum_{i=1}^{m}\varphi(p^i) \\
  & =1+\sum_{i=1}^{m}p^i-p^{i-1} \\
  & =p^m \\
  & =\text{id}(p^m)
\end{aligned}
$$

对于任意正整数 $n$，由唯一分解定理得 $n=\prod_{i=1}^{s}p_i^{k_i}$，$p_i$ 是质数。

$$
\begin{aligned}
 (\varphi*1)(n) & =(\varphi*1)(\prod_{i=1}^{s}p_i^{k_i}) \\
  & =\prod_{i=1}^{s}(\varphi*1)(p_i^{k_i}) \\
  & =\prod_{i=1}^{s}\text{id}(p_i^{k_i}) \\
  & =\text{id}(\prod_{i=1}^{s}p_i^{k_i}) \\
  & =\text{id}(n)
\end{aligned}
$$

第 $2$ 个等号成立是因为 $(\varphi*1)(n)$ 是积性函数，第 $4$ 个等号成立是因为 $\text{id}(n)$ 是积性函数。

$5.$ $(\mu*1)(n)=\varepsilon(n)$

证明：

设 $n$ 为任意正整数，由唯一分解定理得 $n=\prod_{i=1}^{s}p_i^{k_i}$，$p_i$ 是质数，设 $n'=\prod_{i=1}^{s}p_i$。

$$
\begin{aligned}
 (\mu*1)(n) & = (\mu*1)(n') \\
  & =\sum_{d|n'}\mu(d) \\
  & =\sum_{i=0}^{s}\binom{s}{i}(-1)^i \\
  & =(1-1)^s \\
  & =[s=0] \\
  & =[n=1] \\
  & =\varepsilon(n)
\end{aligned}
$$

第 $1$ 个等号成立是因为若 $d$ 含有平方因子，则 $\mu(d)=0$。

第 $3$ 个等号成立是根据莫比乌斯函数的定义，枚举 $d$ 的质因子个数。

# 莫比乌斯反演

已知 $g(n)=\sum_{d|n}f(n)$，则 $f(n)=\sum_{d|n}\mu(d)g(\frac{n}{d})$。

证明：

$$g(n)=\sum_{d|n}f(n)=(f*1)(n)$$

方程两边同时乘上 $\mu(n)$，

$$
\begin{aligned}
 (g*\mu)(n) & =(f*\mu*1)(n) \\
  & =(f*\varepsilon)(n) \\
  & =f(n)
\end{aligned}
$$

$$f(n)=(g*\mu)(n)=\sum_{d|n}\mu(d)g(\frac{n}{d})$$

# 常用推论

$1.$ $\text{gcd}(i, j)=\sum_{d|\text{gcd}(i, j)}\varphi(d)$

证明：

$$n=\text{id}(n)=(\varphi*1)(n)=\sum_{d|n}\varphi(d)$$

所以，

$$n=\sum_{d|n}\varphi(d)$$

$$\text{gcd}(i, j)=\sum_{d|\text{gcd}(i, j)}\varphi(d)$$

$2.$ $[\text{gcd}(i, j)=1]=\sum_{d|\text{gcd}(i, j)}\mu(d)$

证明：

$$[n=1]=\varepsilon(n)=(\mu*1)(n)=\sum_{d|n}\mu(d)$$

所以，

$$[n=1]=\sum_{d|n}\mu(d)$$

$$[\text{gcd}(i, j)=1]=\sum_{d|\text{gcd}(i, j)}\mu(d)$$

# 例题

[洛谷 P2522 [HAOI2011] Problem b](https://www.luogu.com.cn/problem/P2522)

最后，送给大家一只可爱的胡桃。

![可爱的胡桃](./hutao.jpg)