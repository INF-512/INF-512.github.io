二元一次方程解的个数分析

# 前言

在阅读本文前，假设你已经掌握了裴蜀定理，扩展欧几里得算法。

# 题目描述

给定正整数 $a, b, c$，求出二元一次方程 $ax+by=c$ 满足 $0\le x < b$ 的所有解，其中 $1\le a,b,c\le 10^6$。

# 推导过程

裴蜀定理：设 $a,b$ 是不全为 $0$ 的整数，则存在整数 $x,y$ 满足 $ax+by=\gcd(a,b)$。

扩展欧几里得算法：通常用于求 $ax+by=\gcd(a,b)$ 的一组可行解。

若 $c$ 不能被 $\gcd(a,b)$ 整除，方程 $ax+by=c$ 无解。

若 $c=\gcd(a,b)$，方程 $ax+by=c$ 有 $\gcd(a, b)$ 个解。

略证：

$$
\begin{aligned}
 ax+by &= ax+\frac{ab}{\gcd(a,b)}+by-\frac{ab}{\gcd(a,b)} \\
  &= a(x+\frac{b}{\gcd(a,b)})+b(y-\frac{a}{\gcd(a,b)}) \\
\end{aligned}
$$

所以方程 $ax+by=c$ 相邻两个解 $x$ 的距离是 $\frac{b}{\gcd(a,b)}$，使用扩展欧几里得算法求出一个 $x$，$0\le x < b$ 范围内恰好有 $\gcd(a,b)$ 个解。

若 $c\neq \gcd(a,b)$ 且 $c$ 能被 $\gcd(a,b)$ 整除，方程 $ax+by=c$ 也是有 $\gcd(a, b)$ 个解。

略证：

我们已经证明了相邻两个解的距离只跟 $a,b$ 有关，这里 $a,b$ 跟上面一样，所以我们只需要证明 $ax+by=c$ 存在一组可行的解就好了。

设 $ax_1+by_1=\gcd(a,b)$，其中 $x_1,y_1$ 是一组可行的解。

方程两边同时乘上 $\frac{c}{\gcd(a,b)}$，

$$\frac{ac}{\gcd(a,b)}x_1+\frac{bc}{\gcd(a,b)}y_1=c$$

设 $x_2=\frac{c}{\gcd(a,b)}x_1$，$y_2=\frac{c}{\gcd(a,b)}y_1$，

$$ax_2+by_2=c$$

所以 $x_2,y_2$ 是 $ax+by=c$ 的一组可行解，因为方程 $ax+by=c$ 相邻两个解 $x$ 的距离还是 $\frac{b}{\gcd(a,b)}$，所以 $0\le x < b$ 范围内恰好有 $\gcd(a,b)$ 个解。

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
#define endl '\n'
// #define endl " line in : " << __LINE__ << endl
ostream& operator << (ostream &out, const pii &p) {
  return out << '{' << p.first << ',' << p.second << '}';
}
const int N = 5e5 + 5, INF = 1e17, P = 998244353;
int exgcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  int d = exgcd(b, a % b, x, y);
  int tx = x, ty = y;
  x = ty, y = tx - a / b * ty;
  return d;
}
int a, b, c;
void test() {
  cin >> a >> b >> c;
  int x, y, d = exgcd(a, b, x, y);
  if (c % d != 0) {
    cout << -1 << endl;
    return;
  }
  x = x * (c / d), y = y * (c / d);
  x = (x % (b / d) + (b / d)) % (b / d);
  y = (c - a * x) / b;
  cout << d << endl;
  for (int i = 0; i < d; i++) {
    cout << x << ' ' << y;
    x += b / d, y -= a / d;
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  // int T; cin >> T; while (T--)
  test();
  return 0;
}
```

# 例题

[洛谷 P5656 【模板】二元一次不定方程 (exgcd)](https://www.luogu.com.cn/problem/P5656)

这题需要在满足 $x\ge 1$ 且 $y \ge 1$ 的解中，分别找 $x$ 最小的解，$y$ 最小的解，$x$ 最大的解，$y$ 最大的解，需要注意的是当 $x$ 最小时，$y$ 最大；当 $y$ 最小时，$x$ 最大。

# 例题代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define all(x) (x).begin(), (x).end()
#define endl '\n'
// #define endl " line in : " << __LINE__ << endl
ostream& operator << (ostream &out, const pii &p) {
  return out << '{' << p.first << ',' << p.second << '}';
}
const int N = 5e5 + 5, INF = 1e17, P = 998244353;
int exgcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  int d = exgcd(b, a % b, x, y);
  int tx = x, ty = y;
  x = ty, y = tx - a / b * ty;
  return d;
}
int a, b, c;
void test() {
  cin >> a >> b >> c;
  int x, y, d = exgcd(a, b, x, y);
  if (c % d != 0) {
    cout << -1 << endl;
    return;
  }
  // cout << d << ' ' << x << ' ' << y << endl;
  a /= d, b /= d, c /= d;
  x *= c, y *= c;
  x = (x % b + b) % b;
  if (x == 0) x += b;
  y = (c - a * x) / b;
  int y2 = (y % a + a) % a;
  if (y2 == 0) y2 += a;
  int x2 = (c - b * y2) / a;
  // cout << x << ' ' << y << ' ' << x2 << ' ' << y2 << endl;
  if (x >= 1 && y >= 1) {
    cout << (x2 - x) / b + 1 << ' ' << x << ' ' << y2 << ' ' << x2 << ' ' << y << endl;
  }
  else {
    cout << x << ' ' << y2 << endl;
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T; cin >> T; while (T--)
  test();
  return 0;
}
```

感谢你阅读本文，请收下这只可爱的刻晴。

![](./p1.jpg)