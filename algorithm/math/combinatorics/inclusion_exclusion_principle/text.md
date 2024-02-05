容斥原理求解不定方程

# 前言

在阅读本文前，假设你已经掌握了组合数，集合运算。

# 容斥原理

设每个物品有 $n$ 种不同的特征，具有第 $i$ 种特征的物品构成多重集合 $S_i$，所有物品构成多重全集 $U$，多重全集 $U$ 应包含全部 $2^n$ 种物品（相当于无视全部特征），但多重全集的大小 $\left | U \right | $ 不一定等于 $2^n$，因为每种物品的具体个数是未知的。

# 常用公式

1. 至少具有一个特征（具有该特征的并集）

$$\left | \bigcup_{i=1}^{n}S_i \right | =\sum_{i}^{}\left | S_i \right | - \sum_{i < j}^{}\left | S_i \cap S_j \right | +\sum_{i< j< k}^{}\left | S_i\cap S_j\cap S_k \right | - \cdots$$

2. 至少不具有一个特征（不具有该特征的并集）等价于至少具有一个相反特征

$$\left | \bigcup_{i=1}^{n}\overline{S_i} \right | =\sum_{i}^{}\left | \overline{S_i} \right | - \sum_{i < j}^{}\left | \overline{S_i} \cap \overline{S_j} \right | +\sum_{i< j< k}^{}\left | \overline{S_i}\cap \overline{S_j}\cap \overline{S_k} \right | - \cdots$$

3. 具有全部特征（全集-至少不具有一个特征）

$$\left | \bigcap_{i=1}^{n}S_i \right | = \left | U \right | - \left | \bigcup_{i=1}^{n}\overline{S_i} \right |$$

4. 不具有任何特征（全集-至少具有一个特征）

$$\left | \bigcap_{i=1}^{n}\overline{S_i} \right | = \left | U \right | - \left | \bigcup_{i=1}^{n}S_i \right |$$

# 插板法

1. 把 $n$ 个完全相同的元素分成 $k$ 组，每组至少有一个元素的方案数。

原问题等价于将 $k-1$ 块板插入到 $n-1$ 个间隔中，方案数为：

$$\binom{n-1}{k-1}$$

2. 把 $n$ 个完全相同的元素分成 $k$ 组，每组可以为空的方案数。

我们先补 $k-1$ 个完全相同的元素，则原问题变成从 $n+k-1$ 个完全相同的元素中选 $k-1$ 个元素作为板的方案数：

$$\binom{n+k-1}{k-1}$$

# 求解不定方程

1. 给出不定方程 $\sum_{i=1}^{n}x_i=m$，其中 $m\ge n$，求正整数解的个数。

原问题等价于（插板法问题 $1$）把 $m$ 个完全相同的元素分成 $n$ 组，每组至少有一个元素的方案数，所以解的个数为：

$$\binom{m-1}{n-1}$$

2. 给出不定方程 $\sum_{i=1}^{n}x_i=m$，其中 $m\ge 0$，求非负整数解的个数。

原问题等价于（插板法问题 $2$）把 $m$ 个完全相同的元素分成 $n$ 组，每组可以为空的方案数，所以解的个数为：

$$\binom{m+n-1}{n-1}$$

3. 给出不定方程 $\sum_{i=1}^{n}x_i=m$ 和 $n$ 个限制 $x_i\ge b_i$，其中 $m\ge 0,b_i\ge 0,\sum_{i=1}^{n}b_i\le m$，求非负整数解的个数。

原问题等价于把 $m$ 个完全相同的元素分成 $n$ 组，第 $i$ 组至少有 $b_i$ 个元素的方案数。

对于所有 $1\le i\le n$，我们先给第 $i$ 组放 $b_i$ 个元素，那么问题变成（求解不定方程问题 $2$）把 $m-\sum_{i=1}^{n}b_i$ 个完全相同的元素分成 $n$ 组，每组可以为空的方案数，所以解的个数为：

$$\binom{m-\sum_{i=1}^{n}b_i+n-1}{n-1}$$

4. 给出不定方程 $\sum_{i=1}^{n}x_i=m$ 和 $n$ 个限制 $x_i\le b_i$，其中 $m\ge 0,b_i\ge 0$，求非负整数解的个数。

上面写了这么多，其实都是在给这题铺垫。

先重申一下定义，将不定方程的解视为物品，将限制视为特征，若一个不定方程的解满足第 $i$ 个限制（即 $x_i\le b_i$），我们就说一个物品具有第 $i$ 个特征。

原问题等价于求具有全部特征的物品数，我们在这里使用容斥原理第 $3$ 个公式：

$$\left | \bigcap_{i=1}^{n}S_i \right | = \left | U \right | - \left | \bigcup_{i=1}^{n}\overline{S_i} \right |$$

全集 $\left | U \right | $ 表示无视全部特征的方案数，即（求解不定方程问题 $2$）求不定方程 $\sum_{i=1}^{n}x_i=m$ 的非负整数解的个数，所以解的个数为：

$$\binom{m+n-1}{n-1}$$

$\left | \bigcup_{i=1}^{n}\overline{S_i} \right |$ 表示至少不具有一个特征的方案数等价于至少具有一个相反特征的方案数，所以问题变成：

给出不定方程 $\sum_{i=1}^{n}x_i=m$ 和 $n$ 个限制 $x_i\ge b_i + 1$（$x_i\le b_i$ 的相反限制），求至少满足一个限制的解的个数。

这里我们使用容斥原理的第 $2$ 个公式：

$$\left | \bigcup_{i=1}^{n}\overline{S_i} \right | =\sum_{i}^{}\left | \overline{S_i} \right | - \sum_{i < j}^{}\left | \overline{S_i} \cap \overline{S_j} \right | +\sum_{i< j< k}^{}\left | \overline{S_i}\cap \overline{S_j}\cap \overline{S_k} \right | - \cdots$$

为了求 $\left | \bigcup_{i=1}^{n}\overline{S_i} \right |$，我们需要暴力枚举所有集合，集合包含奇数个限制是正数，偶数个限制是负数。

我们从上面的公式中任意取出一项 $\left | \overline{S_i}\cap \overline{S_j}\cap \overline{S_k} \right |$，这项表示同时满足 $i,j,k$ 这 $3$ 个限制的解的数量，问题变成（求解不定方程问题 $3$）给出不定方程 $\sum_{i=1}^{n}x_i=m$ 和 $3$ 个限制 $x_i\ge b_i+1,x_j\ge b_j+1,x_k\ge b_k+1$，求满足全部限制的解的个数，其他项同理，所以方案数为：

$$\binom{m-(b_i+1)-(b_j+1)-(b_k+1)+n-1}{n-1}$$

总公式为：

$$\left | \bigcap_{i=1}^{n}S_i \right | =\binom{m+n-1}{n-1}-(\sum_{i}^{}\left | \overline{S_i} \right | - \sum_{i < j}^{}\left | \overline{S_i} \cap \overline{S_j} \right | +\sum_{i< j< k}^{}\left | \overline{S_i}\cap \overline{S_j}\cap \overline{S_k} \right | - \cdots)$$

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
#define endl '\n'
// #define endl " line in : " << __LINE__ << endl
ostream& operator << (ostream &out, const pii &p) {
  return out << '{' << p.first << ',' << p.second << '}';
}
const int N = 605, INF = 1e17, P = 998244353;
int m, n, b[N];
int ksm(int a, int b) {
  assert(0 <= a && a < P && b >= 0);
  int x = 1;
  while (b) {
    if (b & 1) x = x * a % P;
    a = a * a % P;
    b >>= 1;
  }
  return x;
}
struct {
  int n;
  vector<int> fac, inv;
  void init(int n) {
    assert(n >= 0);
    this->n = n;
    fac.assign(n + 5, 0);
    inv.assign(n + 5, 0);
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) {
      fac[i] = fac[i - 1] * i % P;
      inv[i] = inv[i - 1] * ksm(i, P - 2) % P;
    }
  }
  int operator()(int n, int m) {
    if (n < 0 || m < 0 || m > n)
      return 0;
    assert(n <= this->n && m <= this->n);
    return fac[n] * inv[m] % P * inv[n - m] % P;
  }
} C;
void test() {
  cin >> m >> n;
  for (int i = 0; i < n; i++)
    cin >> b[i];
  C.init(n + m + 5);
  int sum = 0;
  // 暴力枚举所有集合
  for (int i = 1; i < (1 << n); i++) {
    int m2 = m;
    // 去掉限制
    for (int j = 0; j < n; j++)
      if (i >> j & 1)
        m2 -= b[j] + 1;
    // 注意正负号
    sum += (popcount((uint)i) & 1 ? 1 : -1) * C(m2 + n - 1, n - 1);
  }
  cout << C(m + n - 1, n - 1) - sum << endl;
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

暂时找不到合适的例题。~（是我太懒了）~

# 对拍

这里我只能提供一份对拍代码。

## ans.cpp

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
const int N = 2e5 + 5, INF = 1e17, P = 998244353;
int m, n, b[N];
int ans;
void dfs(int x, int sum) {
  if (x == n + 1) {
    if (sum == m)
      ans++;
    return;
  }
  for (int i = 0; i <= b[x]; i++)
    dfs(x + 1, sum + i);
}
void test() {
  cin >> m >> n;
  for (int i = 1; i <= n; i++)
    cin >> b[i];
  dfs(1, 0);
  cout << ans << endl;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  // int T; cin >> T; while (T--)
  test();
  return 0;
}
```

## chk.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
// #define endl '\n'
// #define endl " line in : " << __LINE__ << endl
ostream& operator << (ostream &out, const pii &p) {
  return out << '{' << p.first << ',' << p.second << '}';
}
const int N = 2e5 + 5, INF = 1e17, P = 998244353;
mt19937_64 gen(time(0));
uint rand(uint l, uint r) {
  uniform_int_distribution<uint> dis(l, r);
  return dis(gen);
}
// 0 <= m <= 30, n = 6, 0 <= b_i <= 5
void create_input() {
  ofstream f("in.txt");
  int m = rand(0, 30), n = 6;
  f << m << ' ' << n << endl;
  for (int i = 1; i <= 6; i++)
    f << rand(0, 5) << ' ';
  f << endl;
  f.close();
}
int check() {
  ifstream ans("ans.txt"), test("test.txt");
  while (1) {
    int x = ans.get(), y = test.get();
    if (x != y) {
      ans.close(), test.close();
      return 1;
    }
    if (x == -1) {
      ans.close(), test.close();
      return 0;
    }
  }
}
void test() {
  for (int cnt = 1; ; cnt++) {
    create_input();
    system("ans.exe < in.txt > ans.txt");
    system("test.exe < in.txt > test.txt");
    if (check()) {
      cout << "WA" << endl;
      break;
    }
    if (cnt % 10 == 0)
      cout << cnt << endl;
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

感谢你阅读本文，请收下只可爱的刻晴。

![](./p1.jpg)