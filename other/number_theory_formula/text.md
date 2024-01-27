# 数论常用公式

1. $\gcd(a,b)=\gcd(a\bmod b,b)=\gcd(a,b\bmod a)$。

2. $f(n, k)=\sum_{i=1}^{n}[\gcd(i,k)=1]=\left\lfloor\frac{n}{k}\right\rfloor\varphi(k)+f(n\bmod k, k)$。

3. $g(n,k)=\sum_{i=1}^{n}\mu(i)[\gcd(i,k)=1]=\sum_{d|k}^{}\mu^2(d)g(\left\lfloor\frac{n}{d}\right\rfloor,d)$。

证明：

$$
\begin{aligned}
 g(n,k) &= \sum_{i=1}^{n}\mu(i)[\gcd(i,k)=1] \\
  &= \sum_{i=1}^{n}\mu(i)\sum_{d|i,d|k}^{}\mu(d) \\
  &= \sum_{d|k}^{}\mu(d)\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\mu(id) \\
  &= \sum_{d|k}^{}\mu(d)\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\mu(i)\mu(d)[\gcd(i,d)=1] \\
  &= \sum_{d|k}^{}\mu^2(d)\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\mu(i)[\gcd(i,d)=1] \\
  &= \sum_{d|k}^{}\mu^2(d)g(\left\lfloor\frac{n}{d}\right\rfloor,d) \\
\end{aligned}
$$


4. 辗转相减法求 $\gcd(a,b)$。

```cpp
int mygcd(int a, int b) {
  if (a == 0) return b;
  if (b == 0) return a;
  if (a % 2 == 0 && b % 2 == 0)
    return 2 * mygcd(a / 2, b / 2);
  else if (a % 2 == 0)
    return mygcd(a / 2, b);
  else if (b % 2 == 0)
    return mygcd(a, b / 2);
  return a > b ? mygcd(a - b, b) : mygcd(a, b - a);
}
```

5. $\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=1]=\sum_{d=1}^{\min(n,m)}\mu(d)\left\lfloor\frac{n}{d}\right\rfloor \left\lfloor\frac{m}{d}\right\rfloor$

证明：

$$
\begin{aligned}
 \sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=1] &= \sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d|\gcd(i,j)}^{}\mu(d) \\
  &= \sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d|i,d|j}^{}\mu(d) \\
  &= \sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d=1}^{\min(n,m)}[d|i][d|j]\mu(d) \\
  &= \sum_{d=1}^{\min(n,m)}\mu(d)\sum_{i=1}^{n}[d|i]\sum_{j=1}^{m}[d|j] \\
  &= \sum_{d=1}^{\min(n,m)}\mu(d)\sum_{id=1}^{n}[d|id]\sum_{jd=1}^{m}[d|jd] \\
  &= \sum_{d=1}^{\min(n,m)}\mu(d)\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}[d|id]\sum_{j=1}^{\left\lfloor\frac{m}{d}\right\rfloor}[d|jd] \\
  &= \sum_{d=1}^{\min(n,m)}\mu(d)\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\sum_{j=1}^{\left\lfloor\frac{m}{d}\right\rfloor}1 \\
  &= \sum_{d=1}^{\min(n,m)}\mu(d)\left\lfloor\frac{n}{d}\right\rfloor \left\lfloor\frac{m}{d}\right\rfloor \\
\end{aligned}
$$

6. $\gcd(ij,k)=1\Leftrightarrow \gcd(i,k)=1,\gcd(j,k)=1$
