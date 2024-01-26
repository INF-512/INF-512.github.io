数论函数前缀和问题之杜教筛

# 前言

在阅读本文前假设你已经掌握了线性筛，数论分块，[常用数论函数和狄利克雷卷积](https://blog.csdn.net/INF_512/article/details/135797414?spm=1001.2014.3001.5501)。

# 题目描述

给定一个正整数 $n$，求 $\sum_{i=1}^{n}\varphi(i)$ 和 $\sum_{i=1}^{n}\mu(i)$，其中 $1\le n\le 10^9$。

# 推导过程

设 $S(n)=\sum_{i=1}^{n}f(i)$。

对于任意一个数论函数 $g(n)$，满足：$\sum_{i=1}^{n}(f*g)(i)=\sum_{i=1}^{n}g(i)S(\left\lfloor \frac{n}{i} \right\rfloor)$。

证明：

$$
\begin{aligned}
 \sum_{i=1}^{n}(f*g)(i) &= \sum_{i=1}^{n}\sum_{xy=i}f(x)g(y) \\
  &= \sum_{xy\le n}f(x)g(y) \\
  &= \sum_{y=1}^{n}\sum_{x=1}^{\left\lfloor \frac{n}{y} \right\rfloor}f(x)g(y) \\
  &= \sum_{y=1}^{n}g(y)\sum_{x=1}^{\left\lfloor \frac{n}{y} \right\rfloor}f(x) \\
  &= \sum_{y=1}^{n}g(y)S(\left\lfloor \frac{n}{y} \right\rfloor) \\
  &= \sum_{i=1}^{n}g(i)S(\left\lfloor \frac{n}{i} \right\rfloor)
\end{aligned}
$$

利用上式构造 $S(n)$ 关于 $\sum_{i=2}^{n}S(\left\lfloor\frac{n}{i}\right\rfloor)$ 的递推式。

$$\sum_{i=1}^{n}(f*g)(i)=g(1)S(n)+\sum_{i=2}^{n}g(i)S(\left\lfloor\frac{n}{i}\right\rfloor)$$

$$g(1)S(n)=\sum_{i=1}^{n}(f*g)(i)-\sum_{i=2}^{n}g(i)S(\left\lfloor\frac{n}{i}\right\rfloor)$$

若 $f(n)$ 是 $\varphi(n)$，我们有 $(\varphi*1)(n)=\text{id}(n)$，可以令 $g(n)$ 为 $1(n)$，所以 $(f*g)(n)=(\varphi*1)(n)=\text{id}(n)$。

$$1(n)S(n)=\sum_{i=1}^{n}\text{id}(i)-\sum_{i=2}^{n}1(i)S(\left\lfloor\frac{n}{i}\right\rfloor)$$

$$S(n)=\frac{n(n+1)}{2}-\sum_{i=2}^{n}S(\left\lfloor\frac{n}{i}\right\rfloor)$$

这里要预处理出 $n^\frac{2}{3}$ 以内的 $S(n)$，然后使用记忆化搜索和数论分块求解，时间复杂度是 $O(n^\frac{2}{3})$。

若 $f(n)$ 是 $\mu(n)$，我们同样有 $(\mu*1)(n)=\varepsilon(n)$，可以令 $g(n)$ 为 $1(n)$，所以 $(f*g)(n)=(\mu*1)(n)=\varepsilon(n)$。

$$1(n)S(n)=\sum_{i=1}^{n}\varepsilon(i)-\sum_{i=2}^{n}1(i)S(\left\lfloor\frac{n}{i}\right\rfloor)$$

$$S(n)=1-\sum_{i=2}^{n}S(\left\lfloor\frac{n}{i}\right\rfloor)$$

接下来跟上面的一样。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned int
#define pii pair<int, int>
template <typename T> using vector2 = vector<vector<T>>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define all(x) (x).begin(), (x).end()
#define endl '\n'
// #define endl " line in : " << __LINE__ << endl
const int N = 2e6 + 5, INF = 1e16, P = 998244353;
unordered_map<int, int> mp_phi, mp_mu;
int phi[N], mu[N];
vector<int> prm;
int vis[N];
int sol1(int n) {
  if (n < N) return phi[n];
  if (mp_phi.count(n))
    return mp_phi[n];
  int x = 0;
  for (int l = 2; l <= n; ) {
    int r = n / (n / l);
    x += sol1(n / l) * (r - l + 1);
    l = r + 1;
  }
  return mp_phi[n] = n * (n + 1) / 2 - x;
}
int sol2(int n) {
  if (n < N) return mu[n];
  if (mp_mu.count(n))
    return mp_mu[n];
  int x = 0;
  for (int l = 2; l <= n; ) {
    int r = n / (n / l);
    x += sol2(n / l) * (r - l + 1);
    l = r + 1;
  }
  return mp_mu[n] = 1 - x;
}
void test() {
  int n;
  cin >> n;
  cout << sol1(n) << ' ' << sol2(n) << endl;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  phi[1] = 1;
  mu[1] = 1;
  for (int i = 2; i < N; i++) {
    if (vis[i] == 0) {
      prm.push_back(i);
      phi[i] = i - 1;
      mu[i] = -1;
    }
    for (int p : prm) {
      if (i * p >= N)
        break;
      vis[i * p] = 1;
      if (i % p == 0) {
        phi[i * p] = phi[i] * p;
        mu[i * p] = 0;
        break;
      }
      phi[i * p] = phi[i] * phi[p];
      mu[i * p] = -mu[i];
    }
  }
  for (int i = 2; i < N; i++)
    phi[i] += phi[i - 1], mu[i] += mu[i - 1];
  int T; cin >> T; while (T--)
    test();
  return 0;
}
```

# 例题

[洛谷 P4213 【模板】杜教筛](https://www.luogu.com.cn/problem/P4213)

~~最后，送给大家一只。~~

文章太短了，下次再送。
