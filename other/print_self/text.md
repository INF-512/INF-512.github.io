如何写一个程序打印自己的源代码

# 前言

在上课的时候，突然想起很久以前的一个有趣的问题。

# 题目描述

写一个程序打印自己的源代码。

假设程序的源代码是：

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main() {
  cout << "Hello World" << endl;
  return 0;
}
```

那么你的答案应该打印：

```
#include <bits/stdc++.h>
using namespace std;
signed main() {
  cout << "Hello World" << endl;
  return 0;
}
```

~~在查看答案前，建议先自行思考。~~

## 解法

直接读取程序的源代码文件，然后打印源代码即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
char s[N];
signed main() {
  ifstream f("test.cpp");
  while (f.getline(s, N))
    cout << s << endl;
  return 0;
}
```

但是这种方法太low了，于是就有了加强版。

# 加强版

写一个程序打印自己的源代码，且禁止读写文件。

## 解法

这个题目最大的难点在于使用 `cout` 打印一个语句后，又产生一条新的语句，导致需要打印无尽的语句。

例如，

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main() {
  cout << "#include <bits/stdc++.h>" << endl;
  cout << "using namespace std;" << endl;
  cout << "signed main() {" << endl;
  cout << "  cout << \"#include <bits/stdc++.h>\" << endl;" << endl;
  cout << "  cout << \"using namespace std;\" << endl;" << endl;
  cout << "  cout << \"signed main() {\" << endl;" << endl;
  return 0;
}
```

如果我们有这样一个函数 $f(s)$，可以同时打印 $s$ 语句和调用它的语句就好了。

例如，

调用 `f("#include <bits/stdc++.h>")` 同时在恰当的位置打印 `#include <bits/stdc++.h>` 和 `f("#include <bits/stdc++.h>")`。

## f 的实现

```cpp
void f(string s, int x, int y) {
  ans[x] = s;
  ans[y] += ' ';
  ans[y] += ' ';
  ans[y] += 'f';
  ans[y] += '(';
  ans[y] += (char)34;
  ans[y] += s;
  ans[y] += (char)34;
  ans[y] += ',';
  ans[y] += ' ';
  ans[y] += to_string(x);
  ans[y] += ',';
  ans[y] += ' ';
  ans[y] += to_string(y);
  ans[y] += ')';
  ans[y] += ';';
}
```

在调用 $f$ 后，在第 $x$ 行打印 $s$ 语句，在第 $y$ 行打印调用它的语句。

注意在打印双引号的时候如果直接使用 `"` 会产生嵌套，要使用 `(char)34` 替代。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
string ans[55];
void f(string s, int x, int y) {
  ans[x] = s;
  ans[y] += ' ';
  ans[y] += ' ';
  ans[y] += 'f';
  ans[y] += '(';
  ans[y] += (char)34;
  ans[y] += s;
  ans[y] += (char)34;
  ans[y] += ',';
  ans[y] += ' ';
  ans[y] += to_string(x);
  ans[y] += ',';
  ans[y] += ' ';
  ans[y] += to_string(y);
  ans[y] += ')';
  ans[y] += ';';
}
signed main() {
  f("#include <bits/stdc++.h>", 1, 23);
  f("using namespace std;", 2, 24);
  f("string ans[55];", 3, 25);
  f("void f(string s, int x, int y) {", 4, 26);
  f("  ans[x] = s;", 5, 27);
  f("  ans[y] += ' ';", 6, 28);
  f("  ans[y] += ' ';", 7, 29);
  f("  ans[y] += 'f';", 8, 30);
  f("  ans[y] += '(';", 9, 31);
  f("  ans[y] += (char)34;", 10, 32);
  f("  ans[y] += s;", 11, 33);
  f("  ans[y] += (char)34;", 12, 34);
  f("  ans[y] += ',';", 13, 35);
  f("  ans[y] += ' ';", 14, 36);
  f("  ans[y] += to_string(x);", 15, 37);
  f("  ans[y] += ',';", 16, 38);
  f("  ans[y] += ' ';", 17, 39);
  f("  ans[y] += to_string(y);", 18, 40);
  f("  ans[y] += ')';", 19, 41);
  f("  ans[y] += ';';", 20, 42);
  f("}", 21, 43);
  f("signed main() {", 22, 44);
  f("  for (int i = 1; i <= 52; i++)", 49, 45);
  f("    cout << ans[i] << endl;", 50, 46);
  f("  return 0;", 51, 47);
  f("}", 52, 48);
  for (int i = 1; i <= 52; i++)
    cout << ans[i] << endl;
  return 0;
}
```

如果有其他更好的做法，欢迎在评论区提出，感谢你的阅读。
