
在使用 unordered_map 时应该如何避免 TLE

事件起因：使用 `unordered_map` 在[洛谷P1173](https://www.luogu.com.cn/problem/P1173)最后一个测试点 `TLE`。

测试程序：洛谷 P1173 解题代码

测试数据：洛谷 P1173 最后一个测试点（我在这里被 T 了无数次）。

测试方式：洛谷测评，本地测评

~实验结论：不使用 `clear()` 函数，而是手动删除元素。~

实验过程

# 一、重写 `unordered_map`

重写一个跟 `unordered_map` 几乎一模一样且不会 `TLE` 的 `HashTable`（一模一样到只要把 `unordered_map` 这个单词换成 `HashTable` 就能编译运行）。

目的是使用尽可能相同的内部实现方法，对比 `unordered_map` 和 `HashTable` 之间的差异，找出 `unordered_map` 会 `TLE` 的原因。

## $1.$ `unordered_map` 的常用接口

```cpp
Node::NodeIt begin(); // 返回指向首个元素的指针
Node::NodeIt end(); // 返回指向末尾的指针（最后一个元素的下一个虚拟元素的指针）
int size(); // 返回元素的个数
void clear(); // 清空容器
Node* find(key_type key); // 返回键为 key 的元素的指针，如果没找到，则返回 NULL
Node* insert(key_type key, val_type val = {}); // 插入一个键为 key，值为 val 的元素，如果键已经存在，则把值替换为 val
void erase(key_type key); // 删除键为 key 的元素
val_type& operator[](key_type key); // 访问键为 key 的元素的 val
int count(key_type key); // 返回键为 key 的元素的个数（由于 unordered_map 中的键互不相同，所以返回值 只有两种 1 表示存在，0 表示不存在）
```

## $2.$ `HashTable` 的实现

### $a.$ 部分代码（不感兴趣可以跳过）

```cpp
#define MOD 1226959
#define SIZE MOD
template<class key_type, class val_type>
struct HashTable {
  struct Node {
    struct KeyVal {
      key_type key;
      val_type val;
      KeyVal(key_type key = {}, val_type val = {}) {
        this->key = key, this->val = val;
      }
    };
    struct NodeIt {
      Node *it;
      NodeIt(Node *it = NULL) { this->it = it; }
      operator Node*() { return it; }
      NodeIt& operator++() { //前置++运算符
        it = it->ri;
        return *this;
      }
      KeyVal& operator*() { return it->kv; }
    };
    KeyVal kv;
    Node *nx, *le, *ri;
    Node(key_type key = {}, val_type val = {}, Node *nx = NULL, Node *le = NULL, Node *ri = NULL) {
      this->kv = KeyVal(key, val), this->nx = nx, this->le = le, this->ri = ri;
    }
  };
  struct MyQueue {
    Node* data[SIZE];
    int l, r, sz;
    MyQueue() = delete;
    MyQueue(Node* base) {
      for (int i = 0; i < SIZE; i++)
        data[i] = &base[i];
      l = r = sz = 0;
    }
    void push(Node* val) {
      data[r] = val;
      if (++r == SIZE) r = 0;
      sz--;
      assert(0 <= sz && sz <= SIZE);
    }
    Node* pop() {
      Node* val = data[l]; *val = {};
      if (++l == SIZE) l = 0;
      sz++;
      assert(0 <= sz && sz <= SIZE);
      return val;
    }
    int size() { return sz; }
  };
  Node *bk[MOD];
  Node dt[SIZE];
  MyQueue dtQue;
  Node *hd, *tl;
  HashTable() : dtQue(dt) { hd = tl = dtQue.pop(); }
  // int hash(key_type key);
  int hash(pii key) {
    return ((key.first << 32 | key.second) % MOD + MOD) % MOD;
  }
  Node::NodeIt begin() { return hd; }
  Node::NodeIt end() { return tl; }
  int size() { return dtQue.size(); }
  void clear() {
    while (hd != tl) {
      bk[hash(hd->kv.key)] = NULL;
      hd->ri->le = NULL;
      dtQue.push(hd);
      hd = hd->ri;
    }
  }
  Node* find(key_type key) {
    int h = hash(key);
    for (Node *i = bk[h]; i != NULL; i = i->nx)
      if (key == i->kv.key)
        return i;
    return NULL;
  }
  void link(Node *p1, Node *p2) { p1->ri = p2, p2->le = p1; }
  void unlink(Node *p1, Node *p2) { p1->ri = p2->le = NULL; }
  void insert(Node *pos, Node *node) {
    if (pos->le == NULL)
      link(node, pos), hd = node;
    else
      link(pos->le, node), link(node, pos);
  }
  Node* insert(key_type key, val_type val = {}) {
    Node *i = find(key);
    if (i)
      i->kv.val = val;
    else {
      int h = hash(key);
      i = dtQue.pop();
      i->kv.key = key, i->kv.val = val;
      i->nx = bk[h], bk[h] = i;
      insert(tl, i);
    }
    return i;
  }
  void erase(Node *pos) {
    if (pos->le == NULL)
      hd = pos->ri, unlink(pos, pos->ri);
    else
      link(pos->le, pos->ri);
    dtQue.push(pos);
  }
  void erase(key_type key) {
    int h = hash(key);
    if (bk[h]->kv.key == key) {
      Node *i = bk[h];
      bk[h] = i->nx;
      erase(i);
    }
    else {
      for (Node *j = bk[h]; j->nx != NULL; j = j->nx) {
        Node *i = j->nx;
        if (key == i->kv.key) {
          j->nx = i->nx;
          erase(i);
          return;
        }
      }
    }
  }
  val_type& operator[](key_type key) {
    Node *i = find(key);
    if (i == NULL) {
      int h = hash(key);
      i = dtQue.pop();
      i->kv.key = key, i->kv.val = {};
      i->nx = bk[h], bk[h] = i;
      insert(tl, i);
    }
    return i->kv.val;
  }
  int count(key_type key) { return find(key) != NULL; }
};
```

### $b.$ 运行耗时

洛谷测评：[耗时 512ms](https://www.luogu.com.cn/record/143135887)

本地测评：耗时 2422ms

### $c.$ 结果评价

`HashTable` 的耗时在意料之中，没什么特别要注意的（洛谷的测评机是真的快）。

# 二、测试不同参数对 `unordered_map` 的影响

## $1.$ 原装 `unordered_map`

### $a.$ 部分代码

```cpp
// pii 原装哈希函数
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
unordered_map<pii, int> mp;
```

### $b.$ 运行耗时

洛谷测评：[耗时 TLE](https://www.luogu.com.cn/record/143138283)

本地测评：耗时 6604ms

### $c.$ 结果评价

`unordered_map` 的 `TLE` 在意料之中，在此作为对照组，给其他实验组提供参考。

## $2.$ 修改哈希函数

这是 `HashTable` 的哈希函数：

```cpp
int hash(pii key) {
  return ((key.first << 32 | key.second) % MOD + MOD) % MOD;
}
```

把 `unordered_map` 的哈希函数换成 `HashTable` 的哈希函数。

### $a.$ 部分代码

```cpp
#define MOD 1226959
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return ((p.first << 32 | p.second) % MOD + MOD) % MOD;
  }
};
unordered_map<pii, int> mp;
```

### $b.$ 运行耗时

洛谷测评：[耗时 TLE](https://www.luogu.com.cn/record/143139643)

本地测评：耗时 6537ms

### $c.$ 结果评价

跟原装的耗时基本相同，所以哈希函数对 `unordered_map` 几乎没有影响。

## $3.$ 修改内存分配器

`HashTable` 使用内存池技术分配内存，`unordered_map` 使用 `new` 和 `delete` 分配内存。

### $a.$ 内存池技术

申请长度不确定的内存会产生内存碎片，内存利用率不高。

申请长度相同的内存可以使用内存池技术，避免产生内存碎片。

原理：首先申请一块足够大的内存，把内存按固定的长度划分为连续的块，把所有块的首地址放进一个队列，需要分配内存就在队头取一个地址，解分配内存就把地址插入到队尾。

```cpp
struct MyQueue {
  Node* data[SIZE];
  int l, r, sz;
  MyQueue() = delete;
  MyQueue(Node* base) {
    for (int i = 0; i < SIZE; i++)
      data[i] = &base[i];
    l = r = sz = 0;
  }
  void push(Node* val) {
    data[r] = val;
    if (++r == SIZE) r = 0;
    sz--;
    assert(0 <= sz && sz <= SIZE);
  }
  Node* pop() {
    Node* val = data[l]; *val = {};
    if (++l == SIZE) l = 0;
    sz++;
    assert(0 <= sz && sz <= SIZE);
    return val;
  }
  int size() { return sz; }
};
```

### $b.$ 内存分配器

内存分配器决定 `STL` 容器分配内存使用的策略，下面通过自定义内存分配器记录 `unordered_map` 的内存分配过程。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
template<class T>
struct Mallocator {
  typedef T value_type;
  Mallocator () {}
  template <class U>
  constexpr Mallocator (const Mallocator <U>&) noexcept {}
  ~Mallocator () {}
  [[nodiscard]] T* allocate(size_t n) {
    auto p = static_cast<T*>(malloc(n * sizeof(T)));
    cout << format("在 {} 分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    return p;
  }
  void deallocate(T* p, size_t n) {
    cout << format("在 {} 解分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    free(p);
  }
};
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
unordered_map<pii, int, hash<pii>, equal_to<pii>, Mallocator<pair<const pii, int>>> mp;
signed main()
{
  system("chcp 65001");
  for (int i = 1; i <= 10; i++)
    mp.insert({ pii(i, i), i });
  for (int i = 1; i <= 5; i++)
    mp.erase(pii(i, i));
  mp.clear();
  return 0;
}
```

```
Active code page: 65001
在 0x1d555d81610 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1d555d81640 分配 13 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 104 个字节
在 0x1d555d816b0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1d555d816e0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1d555d81710 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1d555d81740 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1d555d81770 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1d555d817a0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1d555d817d0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1d555d81800 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1d555d81830 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1d555d81610 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1d555d816b0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1d555d816e0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1d555d81710 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1d555d81740 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1d555d81830 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1d555d81800 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1d555d817d0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1d555d817a0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1d555d81770 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1d555d81640 解分配 13 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 104 个字节
请按任意键继续. . .
```

### $c.$ `unordered_map` 内存分配规则
  
`unordered_map` 的内存由两部分组成：桶（索引表），元素（节点），跟普通的哈希差不多。

$1.$ 当插入一个元素时，`unordered_map` 会新建一个节点，如果此时一个桶也没有，就会新建一个索引表，然后把节点插入到索引表中。（初始索引表的大小是 $13$）

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
template<class T>
struct Mallocator {
  typedef T value_type;
  Mallocator () {}
  template <class U>
  constexpr Mallocator (const Mallocator <U>&) noexcept {}
  ~Mallocator () {}
  [[nodiscard]] T* allocate(size_t n) {
    auto p = static_cast<T*>(malloc(n * sizeof(T)));
    cout << format("在 {} 分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    return p;
  }
  void deallocate(T* p, size_t n) {
    cout << format("在 {} 解分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    free(p);
  }
};
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
unordered_map<pii, int, hash<pii>, equal_to<pii>, Mallocator<pair<const pii, int>>> mp;
signed main()
{
  system("chcp 65001");
  mp.insert({ pii(1, 1), 1});
  mp.insert({ pii(2, 2), 2});
  mp.insert({ pii(3, 3), 3});
  return 0;
}
```

```
Active code page: 65001
在 0x17bf8a11610 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x17bf8a11640 分配 13 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 104 个字节
在 0x17bf8a116b0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x17bf8a116e0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x17bf8a116e0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x17bf8a116b0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x17bf8a11610 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x17bf8a11640 解分配 13 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 104 个字节
请按任意键继续. . .
```

$2.$ 当元素数量达到上限时，`unordered_map` 会新建一个大小是原来两倍的索引表，然后把原来的索引表拷贝到新的索引表，最后删除原来的索引表。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
template<class T>
struct Mallocator {
  typedef T value_type;
  Mallocator () {}
  template <class U>
  constexpr Mallocator (const Mallocator <U>&) noexcept {}
  ~Mallocator () {}
  [[nodiscard]] T* allocate(size_t n) {
    auto p = static_cast<T*>(malloc(n * sizeof(T)));
    cout << format("在 {} 分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    return p;
  }
  void deallocate(T* p, size_t n) {
    cout << format("在 {} 解分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    free(p);
  }
};
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
unordered_map<pii, int, hash<pii>, equal_to<pii>, Mallocator<pair<const pii, int>>> mp;
signed main()
{
  system("chcp 65001");
  for (int i = 1; i <= 14; i++)
    mp.insert({ pii(i, i), i});
  return 0;
}
```

```
Active code page: 65001
在 0x254ed001610 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed001640 分配 13 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 104 个字节
在 0x254ed0016b0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed0016e0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed001710 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed001740 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed001770 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed0017a0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed0017d0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed001800 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed001830 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed001860 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed001890 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed0018c0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed0018f0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x254ed001920 分配 29 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 232 个字节
在 0x254ed001640 解分配 13 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 104 个字节
在 0x254ed0018f0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed001610 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed0016b0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed0016e0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed001710 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed001740 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed001770 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed0017a0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed0017d0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed001800 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed001830 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed001860 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed001890 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed0018c0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x254ed001920 解分配 29 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 232 个字节
请按任意键继续. . .
```

$3.$ 当删除一个元素时，`unordered_map` 会找到对应节点进行删除，如果没找到，什么也不会发生，删除节点后不会改变索引表的大小。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
template<class T>
struct Mallocator {
  typedef T value_type;
  Mallocator () {}
  template <class U>
  constexpr Mallocator (const Mallocator <U>&) noexcept {}
  ~Mallocator () {}
  [[nodiscard]] T* allocate(size_t n) {
    auto p = static_cast<T*>(malloc(n * sizeof(T)));
    cout << format("在 {} 分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    return p;
  }
  void deallocate(T* p, size_t n) {
    cout << format("在 {} 解分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    free(p);
  }
};
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
unordered_map<pii, int, hash<pii>, equal_to<pii>, Mallocator<pair<const pii, int>>> mp;
signed main()
{
  system("chcp 65001");
  for (int i = 1; i <= 5; i++)
    mp.insert({ pii(i, i), i});
  mp.erase(pii(6, 6));
  mp.erase(pii(2, 2));
  cout << "--------------" << endl;
  return 0;
}
```

```
Active code page: 65001
在 0x25c5f211610 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x25c5f211640 分配 13 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 104 个字节
在 0x25c5f2116b0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x25c5f2116e0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x25c5f211710 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x25c5f211740 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x25c5f2116b0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
--------------
在 0x25c5f211740 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x25c5f211710 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x25c5f2116e0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x25c5f211610 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x25c5f211640 解分配 13 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 104 个字节
请按任意键继续. . .
```

$4.$ 当清空容器时，`unordered_map` 会删除所有节点且不会改变索引表的大小。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
template<class T>
struct Mallocator {
  typedef T value_type;
  Mallocator () {}
  template <class U>
  constexpr Mallocator (const Mallocator <U>&) noexcept {}
  ~Mallocator () {}
  [[nodiscard]] T* allocate(size_t n) {
    auto p = static_cast<T*>(malloc(n * sizeof(T)));
    cout << format("在 {} 分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    return p;
  }
  void deallocate(T* p, size_t n) {
    cout << format("在 {} 解分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    free(p);
  }
};
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
unordered_map<pii, int, hash<pii>, equal_to<pii>, Mallocator<pair<const pii, int>>> mp;
signed main()
{
  system("chcp 65001");
  for (int i = 1; i <= 5; i++)
    mp.insert({ pii(i, i), i});
  cout << "clear() 前，索引表的大小为" << mp.bucket_count() << endl;
  mp.clear();
  cout << "clear() 后，索引表的大小为" << mp.bucket_count() << endl;
  cout << "--------------" << endl;
  return 0;
}
```  

```
Active code page: 65001
在 0x1dc011c1610 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1dc011c1640 分配 13 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 104 个字节
在 0x1dc011c16b0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1dc011c16e0 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1dc011c1710 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
在 0x1dc011c1740 分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32  个字节
clear() 前，索引表的大小为13
在 0x1dc011c1740 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1dc011c1710 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1dc011c16e0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1dc011c16b0 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
在 0x1dc011c1610 解分配 1 个对象，对象名为 NSt8__detail10_Hash_nodeISt4pairIKS1_IxxExELb0EEE，对象大小为 32，总共占用 32 个字节
clear() 后，索引表的大小为13
--------------
在 0x1dc011c1640 解分配 13 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 104 个字节
请按任意键继续. . .
```

### $d.$ 使用内存池技术优化内存分配器

`unordered_map` 有两种长度不同的数据类型：索引表和节点，所以我们分别给索引表开一个内存池，给节点开一个内存池。

在 `unordered_map` 新建索引表时，从索引表队列的队头取出一个索引表地址。

在 `unordered_map` 删除索引表时，把索引表地址插入到索引表队列的队尾。

在 `unordered_map` 新建节点时，从节点队列的队头取出一个节点地址。

在 `unordered_map` 删除节点时，把节点地址插入到节点队列的队尾。

### $e.$ 部分代码

```cpp
template<int COUNT, int SIZE>
struct MyQueue {
  char* data[COUNT];
  int l, r, sz;
  MyQueue(char* base) {
    for (int i = 0; i < COUNT; i++)
      data[i] = base + i * SIZE;
    l = r = sz = 0;
  }
  void push(char* val) {
    data[r] = val;
    if (++r == COUNT) r = 0;
    sz--;
    assert(0 <= sz && sz <= COUNT);
  }
  char* pop() {
    char* val = data[l];
    if (++l == COUNT) l = 0;
    sz++;
    assert(0 <= sz && sz <= COUNT);
    return val;
  }
};
const int BASE_COUNT = 8;
const int BASE_SIZE = 1e7;
const int DATA_COUNT = 5e6;
const int DATA_SIZE = sizeof(pii) + sizeof(int) + 8;
// Hash_node_baseE
char base[BASE_COUNT*BASE_SIZE];
MyQueue<BASE_COUNT, BASE_SIZE> baseQue(base);
char data1[DATA_COUNT*DATA_SIZE];
MyQueue<DATA_COUNT, DATA_SIZE> dataQue(data1);
template<class T>
struct HashTableAllocator {
  typedef T value_type;
  HashTableAllocator () = default;
  template <class U>
  constexpr HashTableAllocator (const HashTableAllocator <U>&) noexcept {}
  [[nodiscard]] T* allocate(std::size_t n) {
    T* p = 0;
    if (sizeof(T) == 8) {
      assert(n * sizeof(T) <= BASE_SIZE);
      p = (T*)baseQue.pop();
    }
    else
      p = (T*)dataQue.pop();
    return p;
  }
  void deallocate(T* p, std::size_t n) noexcept {
    if (sizeof(T) == 8)
      baseQue.push((char*)p);
    else
      dataQue.push((char*)p);
  }
};
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
unordered_map<pii, int, hash<pii>, equal_to<pii>, HashTableAllocator<pair<const pii, int>>> mp;
```

### $f.$ 运行耗时

洛谷测评：[耗时 TLE](https://www.luogu.com.cn/record/143148242)

本地测评：耗时 6140ms

### $g.$ 结果评价

比原装快了一点点，所以内存分配对 `unordered_map` 有影响，但影响不大。

## $4.$ 提前设置索引表的大小

`HashTable` 的索引表的初始大小是 `MOD`，`unordered_map` 的索引表的初始大小是 13，在元素数量达到上限时会重建索引表。

`rehash()` 函数能指定 `unordered_map` 索引表的初始大小。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
template<class T>
struct Mallocator {
  typedef T value_type;
  Mallocator () {}
  template <class U>
  constexpr Mallocator (const Mallocator <U>&) noexcept {}
  ~Mallocator () {}
  [[nodiscard]] T* allocate(size_t n) {
    auto p = static_cast<T*>(malloc(n * sizeof(T)));
    cout << format("在 {} 分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    return p;
  }
  void deallocate(T* p, size_t n) {
    cout << format("在 {} 解分配 {} 个对象，对象名为 {}，对象大小为 {}，总共占用 {} 个字节", (void*)p, n, typeid(T).name(), sizeof(T), n * sizeof(T)) << endl;
    free(p);
  }
};
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
unordered_map<pii, int, hash<pii>, equal_to<pii>, Mallocator<pair<const pii, int>>> mp;
signed main()
{
  system("chcp 65001");
  mp.rehash(100);
  cout << "clear() 前，索引表的大小为" << mp.bucket_count() << endl;
  mp.clear();
  cout << "clear() 后，索引表的大小为" << mp.bucket_count() << endl;
  cout << "--------------" << endl;
  return 0;
}
```

```
Active code page: 65001
在 0x23d25641610 分配 103 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 824 个字节
clear() 前，索引表的大小为103
clear() 后，索引表的大小为103
--------------
在 0x23d25641610 解分配 103 个对象，对象名为 PNSt8__detail15_Hash_node_baseE，对象大小为 8，总共占用 824 个字节
请按任意键继续. . .
```

### $a.$ 部分代码

```cpp
#define MOD 1226959
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
unordered_map<pii, int> mp;
mp.rehash(MOD);
```

### $b.$ 运行耗时

洛谷测评：[耗时 TLE](https://www.luogu.com.cn/record/143151110)

本地测评：耗时 80230ms = 80s

### $c.$ 结果评价

结果出乎意料的慢，理论上 `unordered_map` 提前设置索引表的大小会减少内存拷贝次数，从而消耗更少的时间，但结果消耗更多的时间，极有可能跟索引表的遍历有关，正常情况下 `unordered_map` 是不会去遍历索引表的，所以我猜测遍历发生在调用 `clear()` 函数的时候，于是就有了下一个测试。

## $5.$ 手动删除元素

### $a.$ 部分代码

```cpp
#define MOD 1226959
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
pii tmp[MOD];
void myclear(unordered_map<pii, int> &mp) {
  int len = 0;
  for (auto&& [x, y] : mp)
    tmp[++len] = x;
  for (int i = 1; i <= len; i++)
    mp.erase(tmp[i]);
}
unordered_map<pii, int> mp;
```

### $b.$ 运行耗时

洛谷测评：[耗时 1.33s](https://www.luogu.com.cn/record/143069889)

本地测评：耗时 4.51s

### $c.$ 结果评价

本地测评的耗时竟然比原装快了近 2s，并且在洛谷已经能够 `AC`（洛谷测评机就是快）。

至此，我们已经找到使用 `unordered_map` 会 `TLE` 的真正原因。

# 三、额外测试

在理解了上面的结论后，让我们来构造一组数据把 `unordered_map` 卡成 `n^2_map`（读作 `n方map` 名字是我自己取的，嘿嘿）。

首先插入 $10^6$ 个元素，然后循环执行 `插入一个元素；清空 unordered_map` $10^6$ 次。

## $a.$ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
const int N = 2e5 + 5, INF = 1e16, P = 998244353;
unordered_map<int, int> mp;
signed main() {
  cout << "start" << endl;
  for (int i = 1; i <= 1000000; i++)
    mp.insert(pii(i, i));
  for (int i = 1; i <= 1000000; i++) {
    mp.insert(pii(i, i));
    mp.clear();
  }
  cout << "end" << endl;
  return 0;
}
```

## $b.$ 运行耗时

洛谷测评：无

本地测评：耗时 > 100s

## $c.$ 结果评价

学过一点编程的都知道上面的代码的时间复杂度肯定是 $O(n)$ ，呃......结果却跟我们想的不一样，至于原因嘛，懂的都懂，不懂的也得懂。

# 四、总结

`unordered_map` 被卡成 $O(n^2)$ 这种情况是不应该出现，因为按照常规思路，`clear()` 函数时间复杂度应该只跟元素的个数有关而跟 `unordered_map` 的索引表的大小无关，但由于 `STL` 的一个小失误，导致 `unordered_map` 直接变成 `n^2_map`（`n方map`），可以说是一个小失误令无数 OIer 惨痛 `TLE`，所以我在此写下这篇文章引以为戒。

# 五、例题

[洛谷 P1173 [NOI2016] 网格](https://www.luogu.com.cn/problem/P1173)

这道题如果用原装 `unordered_map` 会在最后一个测试点 `TLE`，只要手动删除元素就能直接 `AC`。

# 六、例题的完整代码

如果想要自己测试，可以把下面的代码直接交到洛谷。

## 使用 `HashTable`

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned int
// #define pii pair<int, int>
template <typename T> using vector2 = vector<vector<T>>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define all(x) (x).begin(), (x).end()
#define endl '\n'
// #define endl " line in : " << __LINE__ << endl
struct pii {
  int first, second;
  pii(int x = 0, int y = 0) { first = x, second = y; }
  bool operator<(const pii &p) const {
    return first < p.first || (first == p.first && second < p.second);
  }
  bool operator==(const pii &p) const {
    return first == p.first && second == p.second;
  }
};

#define MOD 1226959
#define SIZE MOD
template<class key_type, class val_type>
struct HashTable {
  struct Node {
    struct KeyVal {
      key_type key;
      val_type val;
      KeyVal(key_type key = {}, val_type val = {}) {
        this->key = key, this->val = val;
      }
    };
    struct NodeIt {
      Node *it;
      NodeIt(Node *it = NULL) { this->it = it; }
      operator Node*() { return it; }
      NodeIt& operator++() { //前置++运算符
        it = it->ri;
        return *this;
      }
      KeyVal& operator*() { return it->kv; }
    };
    KeyVal kv;
    Node *nx, *le, *ri;
    Node(key_type key = {}, val_type val = {}, Node *nx = NULL, Node *le = NULL, Node *ri = NULL) {
      this->kv = KeyVal(key, val), this->nx = nx, this->le = le, this->ri = ri;
    }
  };
  struct MyQueue {
    Node* data[SIZE];
    int l, r, sz;
    MyQueue() = delete;
    MyQueue(Node* base) {
      for (int i = 0; i < SIZE; i++)
        data[i] = &base[i];
      l = r = sz = 0;
    }
    void push(Node* val) {
      data[r] = val;
      if (++r == SIZE) r = 0;
      sz--;
      assert(0 <= sz && sz <= SIZE);
    }
    Node* pop() {
      Node* val = data[l]; *val = {};
      if (++l == SIZE) l = 0;
      sz++;
      assert(0 <= sz && sz <= SIZE);
      return val;
    }
    int size() { return sz; }
  };
  Node *bk[MOD];
  Node dt[SIZE];
  MyQueue dtQue;
  Node *hd, *tl;
  HashTable() : dtQue(dt) { hd = tl = dtQue.pop(); }
  // int hash(key_type key);
  int hash(pii key) {
    return ((key.first << 32 | key.second) % MOD + MOD) % MOD;
  }
  Node::NodeIt begin() { return hd; }
  Node::NodeIt end() { return tl; }
  int size() { return dtQue.size(); }
  void clear() {
    while (hd != tl) {
      bk[hash(hd->kv.key)] = NULL;
      hd->ri->le = NULL;
      dtQue.push(hd);
      hd = hd->ri;
    }
  }
  Node* find(key_type key) {
    int h = hash(key);
    for (Node *i = bk[h]; i != NULL; i = i->nx)
      if (key == i->kv.key)
        return i;
    return NULL;
  }
  void link(Node *p1, Node *p2) { p1->ri = p2, p2->le = p1; }
  void unlink(Node *p1, Node *p2) { p1->ri = p2->le = NULL; }
  void insert(Node *pos, Node *node) {
    if (pos->le == NULL)
      link(node, pos), hd = node;
    else
      link(pos->le, node), link(node, pos);
  }
  Node* insert(key_type key, val_type val = {}) {
    Node *i = find(key);
    if (i)
      i->kv.val = val;
    else {
      int h = hash(key);
      i = dtQue.pop();
      i->kv.key = key, i->kv.val = val;
      i->nx = bk[h], bk[h] = i;
      insert(tl, i);
    }
    return i;
  }
  void erase(Node *pos) {
    if (pos->le == NULL)
      hd = pos->ri, unlink(pos, pos->ri);
    else
      link(pos->le, pos->ri);
    dtQue.push(pos);
  }
  void erase(key_type key) {
    int h = hash(key);
    if (bk[h]->kv.key == key) {
      Node *i = bk[h];
      bk[h] = i->nx;
      erase(i);
    }
    else {
      for (Node *j = bk[h]; j->nx != NULL; j = j->nx) {
        Node *i = j->nx;
        if (key == i->kv.key) {
          j->nx = i->nx;
          erase(i);
          return;
        }
      }
    }
  }
  val_type& operator[](key_type key) {
    Node *i = find(key);
    if (i == NULL) {
      int h = hash(key);
      i = dtQue.pop();
      i->kv.key = key, i->kv.val = {};
      i->nx = bk[h], bk[h] = i;
      insert(tl, i);
    }
    return i->kv.val;
  }
  int count(key_type key) { return find(key) != NULL; }
};

template<class key_type>
struct HashTableSet {
  struct Node {
    struct NodeIt {
      Node *it;
      NodeIt(Node *it = NULL) { this->it = it; }
      operator Node*() { return it; }
      NodeIt& operator++() { //前置++运算符
        it = it->ri;
        return *this;
      }
      key_type& operator*() { return it->key; }
    };
    key_type key;
    Node *nx, *le, *ri;
    Node(key_type key = {}, Node *nx = NULL, Node *le = NULL, Node *ri = NULL) {
      this->key = key, this->nx = nx, this->le = le, this->ri = ri;
    }
  };
  struct MyQueue {
    Node* data[SIZE];
    int l, r, sz;
    MyQueue() = delete;
    MyQueue(Node* base) {
      for (int i = 0; i < SIZE; i++)
        data[i] = &base[i];
      l = r = sz = 0;
    }
    void push(Node* val) {
      data[r] = val;
      if (++r == SIZE) r = 0;
      sz--;
      assert(0 <= sz && sz <= SIZE);
    }
    Node* pop() {
      Node* val = data[l]; *val = {};
      if (++l == SIZE) l = 0;
      sz++;
      assert(0 <= sz && sz <= SIZE);
      return val;
    }
    int size() { return sz; }
  };
  Node *bk[MOD];
  Node dt[SIZE];
  MyQueue dtQue;
  Node *hd, *tl;
  HashTableSet() : dtQue(dt) { hd = tl = dtQue.pop(); }
  // int hash(key_type key);
  int hash(pii key) {
    return ((key.first << 32 | key.second) % MOD + MOD) % MOD;
  }
  Node::NodeIt begin() { return hd; }
  Node::NodeIt end() { return tl; }
  int size() { return dtQue.size(); }
  void clear() {
    while (hd != tl) {
      bk[hash(hd->key)] = NULL;
      hd->ri->le = NULL;
      dtQue.push(hd);
      hd = hd->ri;
    }
  }
  Node* find(key_type key) {
    int h = hash(key);
    for (Node *i = bk[h]; i != NULL; i = i->nx)
      if (key == i->key)
        return i;
    return NULL;
  }
  void link(Node *p1, Node *p2) { p1->ri = p2, p2->le = p1; }
  void unlink(Node *p1, Node *p2) { p1->ri = p2->le = NULL; }
  void insert(Node *pos, Node *node) {
    if (pos->le == NULL)
      link(node, pos), hd = node;
    else
      link(pos->le, node), link(node, pos);
  }
  Node* insert(key_type key) {
    Node *i = find(key);
    if (i)
      ;
    else {
      int h = hash(key);
      i = dtQue.pop();
      i->key = key;
      i->nx = bk[h], bk[h] = i;
      insert(tl, i);
    }
    return i;
  }
  void erase(Node *pos) {
    if (pos->le == NULL)
      hd = pos->ri, unlink(pos, pos->ri);
    else
      link(pos->le, pos->ri);
    dtQue.push(pos);
  }
  void erase(key_type key) {
    int h = hash(key);
    if (bk[h]->key == key) {
      Node *i = bk[h];
      bk[h] = i->nx;
      erase(i);
    }
    else {
      for (Node *j = bk[h]; j->nx != NULL; j = j->nx) {
        Node *i = j->nx;
        if (key == i->key) {
          j->nx = i->nx;
          erase(i);
          return;
        }
      }
    }
  }
  int count(key_type key) { return find(key) != NULL; }
};

const int N = 15, INF = 1e16, P = 998244353;
int n, m, c;
HashTableSet<pii> p1, vis1;
HashTableSet<pii> p2, vis2;
HashTable<pii, int> dfn, low;
int dir8[] = { 0, 1, 1, -1, -1, 0, -1, 1, 0 };
int dir4[] = { 0, -1, 0, 1, 0 };
void dfs1(int x, int y, vector<pii> &ver) {
  vis1.insert(pii(x, y));
  ver.push_back(pii(x, y));
  for (int k = 0; k < 8; k++) {
    int a = x + dir8[k], b = y + dir8[k + 1];
    if (p1.count(pii(a, b)) && vis1.count(pii(a, b)) == 0)
      dfs1(a, b, ver);
  }
}
void dfs2(int x, int y) {
  vis2.insert(pii(x, y));
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) && vis2.count(pii(a, b)) == 0)
      dfs2(a, b);
  }
}
int tim;
int tarjan(int x, int y, pii fa, pii root) {
  // cout << "tj ";
  // cout << x << ' ' << y << endl;
  dfn[pii(x, y)] = low[pii(x, y)] = ++tim;
  int child = 0;
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) == 0)
      continue;
    if (dfn.count(pii(a, b)) == 0) {
      child++;
      if (tarjan(a, b, pii(x, y), root))
        return 1;
      if (pii(x, y) != root) {
        if (low[pii(a, b)] >= dfn[pii(x, y)]) {
          int ok = 1;
          for (int i = x - 1; i <= x + 1; i++)
            for (int j = y - 1; j <= y + 1; j++)
              if (1 <= i && i <= n && 1 <= j && j <= m) {
                if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
                  ok = 0;
              }

          if (ok) {
            return 1;
          }
        }
      }
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
    }
    else if (pii(a, b) != fa)
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
  }
  // cout << x << ' ' << y << ' ' << low[pii(x, y)] << ' ' << dfn[pii(x, y)] << endl;
  if (pii(x, y) == root) {
    if (child >= 2) {
      int ok = 1;
      for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
          if (1 <= i && i <= n && 1 <= j && j <= m) {
            if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
              ok = 0;
          }
      return ok;
    }
  }
  return 0;
}
void test() {
  cin >> n >> m >> c;
  p1.clear(), vis1.clear();
  vector<pii> pnt;
  for (int i = 1; i <= c; i++) {
    int x, y;
    cin >> x >> y;
    p1.insert(pii(x, y));
    pnt.push_back(pii(x, y));
  }
  /*
-1: c == n*m || c == n*m-1 || (c == n*m-2 && 两个白格相邻)
 0: 白格不连通
 1: 白格连通且存在割点
 2: 其他情况
 */
  if (c == n * m || c == n * m - 1) {
    cout << -1 << endl;
    return;
  }
  if (c == n * m - 2) {
    vector<vector<int>> a;
    a.assign(n + 5, vector<int>(m + 5));
    for (auto [x, y] : p1)
      a[x][y] = 1;
    int ok = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m - 1; j++) {
        if (a[i][j] == 0 && a[i][j + 1] == 0)
          ok = 1;
      }
    for (int i = 1; i <= n - 1; i++)
      for (int j = 1; j <= m; j++)
        if (a[i][j] == 0 && a[i + 1][j] == 0)
          ok = 1;
    cout << (ok ? -1 : 0) << endl;
    return;
  }
  if (n == 1 || m == 1) {
    if (c == 0) {
      cout << 1 << endl;
      return;
    }
    sort(all(pnt));
    auto [x1, y1] = pnt.back();
    auto [x2, y2] = pnt.front();
    if (x1 + y1 - 1 == c || x2 + y2 - 1 == n + m - 1 - c + 1)
      cout << 1 << endl;
    else
      cout << 0 << endl;
    // cout << (c == n+m-1 ? 0 : 1) << endl;
    return;
  }
  if (c == 0) {
    cout << 2 << endl;
    return;
  }
  for (auto [x, y] : p1) {
    if (vis1.count(pii(x, y)) == 0) {
      vector<pii> ver;
      dfs1(x, y, ver);
      p2.clear(), vis2.clear();
      for (auto [x, y] : ver) {
        for (int k = 0; k < 8; k++) {
          int a = x + dir8[k], b = y + dir8[k + 1];
          if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
            p2.insert(pii(a, b));
        }
      }
      auto [a, b] = *p2.begin();
      dfs2(a, b);
      if (vis2.size() != p2.size()) {
        cout << 0 << endl;
        return;
      }
    }
  }
  p2.clear();
  for (auto [x, y] : p1) {
    for (int a = x - 2; a <= x + 2; a++)
      for (int b = y - 2; b <= y + 2; b++)
        if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
          p2.insert(pii(a, b));
  }
  // for (auto [x, y] : p2) {
  //   cout << x << ' ' << y << endl;
  // }
  int ok = 0;
  dfn.clear(), low.clear(), tim = 0;
  for (auto [x, y] : p2) {
    if (dfn.count(pii(x, y)) == 0) {
      if (tarjan(x, y, pii(-1, -1), pii(x, y))) {
        ok = 1;
        break;
      }
    }
  }
  cout << (ok ? 1 : 2) << endl;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T; cin >> T; while (T--)
  test();
  // cout << clock() << "ms" << endl;
  return 0;
}
```

## 使用原装 `unordered_map`

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned int
// #define pii pair<int, int>
template <typename T> using vector2 = vector<vector<T>>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define all(x) (x).begin(), (x).end()
#define endl '\n'
// #define endl " line in : " << __LINE__ << endl
struct pii {
  int first, second;
  pii(int x = 0, int y = 0) { first = x, second = y; }
  bool operator<(const pii &p) const {
    return first < p.first || (first == p.first && second < p.second);
  }
  bool operator==(const pii &p) const {
    return first == p.first && second == p.second;
  }
};
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
const int N = 15, INF = 1e16, P = 998244353;
int n, m, c;
unordered_set<pii> p1, vis1;
unordered_set<pii> p2, vis2;
unordered_map<pii, int> dfn, low;
int dir8[] = { 0, 1, 1, -1, -1, 0, -1, 1, 0 };
int dir4[] = { 0, -1, 0, 1, 0 };
void dfs1(int x, int y, vector<pii> &ver) {
  vis1.insert(pii(x, y));
  ver.push_back(pii(x, y));
  for (int k = 0; k < 8; k++) {
    int a = x + dir8[k], b = y + dir8[k + 1];
    if (p1.count(pii(a, b)) && vis1.count(pii(a, b)) == 0)
      dfs1(a, b, ver);
  }
}
void dfs2(int x, int y) {
  vis2.insert(pii(x, y));
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) && vis2.count(pii(a, b)) == 0)
      dfs2(a, b);
  }
}
int tim;
int tarjan(int x, int y, pii fa, pii root) {
  // cout << "tj ";
  // cout << x << ' ' << y << endl;
  dfn[pii(x, y)] = low[pii(x, y)] = ++tim;
  int child = 0;
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) == 0)
      continue;
    if (dfn.count(pii(a, b)) == 0) {
      child++;
      if (tarjan(a, b, pii(x, y), root))
        return 1;
      if (pii(x, y) != root) {
        if (low[pii(a, b)] >= dfn[pii(x, y)]) {
          int ok = 1;
          for (int i = x - 1; i <= x + 1; i++)
            for (int j = y - 1; j <= y + 1; j++)
              if (1 <= i && i <= n && 1 <= j && j <= m) {
                if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
                  ok = 0;
              }

          if (ok) {
            return 1;
          }
        }
      }
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
    }
    else if (pii(a, b) != fa)
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
  }
  // cout << x << ' ' << y << ' ' << low[pii(x, y)] << ' ' << dfn[pii(x, y)] << endl;
  if (pii(x, y) == root) {
    if (child >= 2) {
      int ok = 1;
      for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
          if (1 <= i && i <= n && 1 <= j && j <= m) {
            if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
              ok = 0;
          }
      return ok;
    }
  }
  return 0;
}
void test() {
  cin >> n >> m >> c;
  p1.clear(), vis1.clear();
  vector<pii> pnt;
  for (int i = 1; i <= c; i++) {
    int x, y;
    cin >> x >> y;
    p1.insert(pii(x, y));
    pnt.push_back(pii(x, y));
  }
  /*
-1: c == n*m || c == n*m-1 || (c == n*m-2 && 两个白格相邻)
 0: 白格不连通
 1: 白格连通且存在割点
 2: 其他情况
 */
  if (c == n * m || c == n * m - 1) {
    cout << -1 << endl;
    return;
  }
  if (c == n * m - 2) {
    vector<vector<int>> a;
    a.assign(n + 5, vector<int>(m + 5));
    for (auto [x, y] : p1)
      a[x][y] = 1;
    int ok = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m - 1; j++) {
        if (a[i][j] == 0 && a[i][j + 1] == 0)
          ok = 1;
      }
    for (int i = 1; i <= n - 1; i++)
      for (int j = 1; j <= m; j++)
        if (a[i][j] == 0 && a[i + 1][j] == 0)
          ok = 1;
    cout << (ok ? -1 : 0) << endl;
    return;
  }
  if (n == 1 || m == 1) {
    if (c == 0) {
      cout << 1 << endl;
      return;
    }
    sort(all(pnt));
    auto [x1, y1] = pnt.back();
    auto [x2, y2] = pnt.front();
    if (x1 + y1 - 1 == c || x2 + y2 - 1 == n + m - 1 - c + 1)
      cout << 1 << endl;
    else
      cout << 0 << endl;
    // cout << (c == n+m-1 ? 0 : 1) << endl;
    return;
  }
  if (c == 0) {
    cout << 2 << endl;
    return;
  }
  for (auto [x, y] : p1) {
    if (vis1.count(pii(x, y)) == 0) {
      vector<pii> ver;
      dfs1(x, y, ver);
      p2.clear(), vis2.clear();
      for (auto [x, y] : ver) {
        for (int k = 0; k < 8; k++) {
          int a = x + dir8[k], b = y + dir8[k + 1];
          if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
            p2.insert(pii(a, b));
        }
      }
      auto [a, b] = *p2.begin();
      dfs2(a, b);
      if (vis2.size() != p2.size()) {
        cout << 0 << endl;
        return;
      }
    }
  }
  p2.clear();
  for (auto [x, y] : p1) {
    for (int a = x - 2; a <= x + 2; a++)
      for (int b = y - 2; b <= y + 2; b++)
        if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
          p2.insert(pii(a, b));
  }
  // for (auto [x, y] : p2) {
  //   cout << x << ' ' << y << endl;
  // }
  int ok = 0;
  dfn.clear(), low.clear(), tim = 0;
  for (auto [x, y] : p2) {
    if (dfn.count(pii(x, y)) == 0) {
      if (tarjan(x, y, pii(-1, -1), pii(x, y))) {
        ok = 1;
        break;
      }
    }
  }
  cout << (ok ? 1 : 2) << endl;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T; cin >> T; while (T--)
  test();
  // cout << clock() << "ms" << endl;
  return 0;
}
```

## 使用 `unordered_map` 并修改哈希函数

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned int
// #define pii pair<int, int>
template <typename T> using vector2 = vector<vector<T>>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define all(x) (x).begin(), (x).end()
#define endl '\n'
// #define endl " line in : " << __LINE__ << endl
struct pii {
  int first, second;
  pii(int x = 0, int y = 0) { first = x, second = y; }
  bool operator<(const pii &p) const {
    return first < p.first || (first == p.first && second < p.second);
  }
  bool operator==(const pii &p) const {
    return first == p.first && second == p.second;
  }
};
#define MOD 1226959
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return ((p.first << 32 | p.second) % MOD + MOD) % MOD;
  }
};
const int N = 15, INF = 1e16, P = 998244353;
int n, m, c;
unordered_set<pii> p1, vis1;
unordered_set<pii> p2, vis2;
unordered_map<pii, int> dfn, low;
int dir8[] = { 0, 1, 1, -1, -1, 0, -1, 1, 0 };
int dir4[] = { 0, -1, 0, 1, 0 };
void dfs1(int x, int y, vector<pii> &ver) {
  vis1.insert(pii(x, y));
  ver.push_back(pii(x, y));
  for (int k = 0; k < 8; k++) {
    int a = x + dir8[k], b = y + dir8[k + 1];
    if (p1.count(pii(a, b)) && vis1.count(pii(a, b)) == 0)
      dfs1(a, b, ver);
  }
}
void dfs2(int x, int y) {
  vis2.insert(pii(x, y));
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) && vis2.count(pii(a, b)) == 0)
      dfs2(a, b);
  }
}
int tim;
int tarjan(int x, int y, pii fa, pii root) {
  // cout << "tj ";
  // cout << x << ' ' << y << endl;
  dfn[pii(x, y)] = low[pii(x, y)] = ++tim;
  int child = 0;
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) == 0)
      continue;
    if (dfn.count(pii(a, b)) == 0) {
      child++;
      if (tarjan(a, b, pii(x, y), root))
        return 1;
      if (pii(x, y) != root) {
        if (low[pii(a, b)] >= dfn[pii(x, y)]) {
          int ok = 1;
          for (int i = x - 1; i <= x + 1; i++)
            for (int j = y - 1; j <= y + 1; j++)
              if (1 <= i && i <= n && 1 <= j && j <= m) {
                if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
                  ok = 0;
              }

          if (ok) {
            return 1;
          }
        }
      }
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
    }
    else if (pii(a, b) != fa)
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
  }
  // cout << x << ' ' << y << ' ' << low[pii(x, y)] << ' ' << dfn[pii(x, y)] << endl;
  if (pii(x, y) == root) {
    if (child >= 2) {
      int ok = 1;
      for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
          if (1 <= i && i <= n && 1 <= j && j <= m) {
            if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
              ok = 0;
          }
      return ok;
    }
  }
  return 0;
}
void test() {
  cin >> n >> m >> c;
  p1.clear(), vis1.clear();
  vector<pii> pnt;
  for (int i = 1; i <= c; i++) {
    int x, y;
    cin >> x >> y;
    p1.insert(pii(x, y));
    pnt.push_back(pii(x, y));
  }
  /*
-1: c == n*m || c == n*m-1 || (c == n*m-2 && 两个白格相邻)
 0: 白格不连通
 1: 白格连通且存在割点
 2: 其他情况
 */
  if (c == n * m || c == n * m - 1) {
    cout << -1 << endl;
    return;
  }
  if (c == n * m - 2) {
    vector<vector<int>> a;
    a.assign(n + 5, vector<int>(m + 5));
    for (auto [x, y] : p1)
      a[x][y] = 1;
    int ok = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m - 1; j++) {
        if (a[i][j] == 0 && a[i][j + 1] == 0)
          ok = 1;
      }
    for (int i = 1; i <= n - 1; i++)
      for (int j = 1; j <= m; j++)
        if (a[i][j] == 0 && a[i + 1][j] == 0)
          ok = 1;
    cout << (ok ? -1 : 0) << endl;
    return;
  }
  if (n == 1 || m == 1) {
    if (c == 0) {
      cout << 1 << endl;
      return;
    }
    sort(all(pnt));
    auto [x1, y1] = pnt.back();
    auto [x2, y2] = pnt.front();
    if (x1 + y1 - 1 == c || x2 + y2 - 1 == n + m - 1 - c + 1)
      cout << 1 << endl;
    else
      cout << 0 << endl;
    // cout << (c == n+m-1 ? 0 : 1) << endl;
    return;
  }
  if (c == 0) {
    cout << 2 << endl;
    return;
  }
  for (auto [x, y] : p1) {
    if (vis1.count(pii(x, y)) == 0) {
      vector<pii> ver;
      dfs1(x, y, ver);
      p2.clear(), vis2.clear();
      for (auto [x, y] : ver) {
        for (int k = 0; k < 8; k++) {
          int a = x + dir8[k], b = y + dir8[k + 1];
          if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
            p2.insert(pii(a, b));
        }
      }
      auto [a, b] = *p2.begin();
      dfs2(a, b);
      if (vis2.size() != p2.size()) {
        cout << 0 << endl;
        return;
      }
    }
  }
  p2.clear();
  for (auto [x, y] : p1) {
    for (int a = x - 2; a <= x + 2; a++)
      for (int b = y - 2; b <= y + 2; b++)
        if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
          p2.insert(pii(a, b));
  }
  // for (auto [x, y] : p2) {
  //   cout << x << ' ' << y << endl;
  // }
  int ok = 0;
  dfn.clear(), low.clear(), tim = 0;
  for (auto [x, y] : p2) {
    if (dfn.count(pii(x, y)) == 0) {
      if (tarjan(x, y, pii(-1, -1), pii(x, y))) {
        ok = 1;
        break;
      }
    }
  }
  cout << (ok ? 1 : 2) << endl;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T; cin >> T; while (T--)
  test();
  // cout << clock() << "ms" << endl;
  return 0;
}
```

## 使用 `unordered_map` 并修改内存分配器

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned int
// #define pii pair<int, int>
template <typename T> using vector2 = vector<vector<T>>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define all(x) (x).begin(), (x).end()
// #define endl '\n'
// #define endl " line in : " << __LINE__ << endl
struct pii {
  int first, second;
  pii(int x = 0, int y = 0) { first = x, second = y; }
  bool operator<(const pii &p) const {
    return first < p.first || (first == p.first && second < p.second);
  }
  bool operator==(const pii &p) const {
    return first == p.first && second == p.second;
  }
};
template<int COUNT, int SIZE>
struct MyQueue {
  char* data[COUNT];
  int l, r, sz;
  MyQueue(char* base) {
    for (int i = 0; i < COUNT; i++)
      data[i] = base + i * SIZE;
    l = r = sz = 0;
  }
  void push(char* val) {
    data[r] = val;
    if (++r == COUNT) r = 0;
    sz--;
    assert(0 <= sz && sz <= COUNT);
  }
  char* pop() {
    char* val = data[l];
    if (++l == COUNT) l = 0;
    sz++;
    assert(0 <= sz && sz <= COUNT);
    return val;
  }
};
const int BASE_COUNT = 8;
const int BASE_SIZE = 1e7;
const int DATA_COUNT = 5e6;
const int DATA_SIZE = sizeof(pii) + sizeof(int) + 8;
// Hash_node_baseE
char base[BASE_COUNT*BASE_SIZE];
MyQueue<BASE_COUNT, BASE_SIZE> baseQue(base);
char data1[DATA_COUNT*DATA_SIZE];
MyQueue<DATA_COUNT, DATA_SIZE> dataQue(data1);
template<class T>
struct HashTableAllocator {
  typedef T value_type;
  HashTableAllocator () = default;
  template <class U>
  constexpr HashTableAllocator (const HashTableAllocator <U>&) noexcept {}
  [[nodiscard]] T* allocate(std::size_t n) {
    T* p = 0;
    if (sizeof(T) == 8) {
      assert(n * sizeof(T) <= BASE_SIZE);
      p = (T*)baseQue.pop();
    }
    else
      p = (T*)dataQue.pop();
    return p;
  }
  void deallocate(T* p, std::size_t n) noexcept {
    if (sizeof(T) == 8)
      baseQue.push((char*)p);
    else
      dataQue.push((char*)p);
  }
};
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
const int N = 15, INF = 1e16, P = 998244353;
int n, m, c;
unordered_set<pii, hash<pii>, equal_to<pii>, HashTableAllocator<pii>> p1, vis1;
unordered_set<pii, hash<pii>, equal_to<pii>, HashTableAllocator<pii>> p2, vis2;
unordered_map<pii, int, hash<pii>, equal_to<pii>, HashTableAllocator<pair<const pii, int>>> dfn, low;
int dir8[] = { 0, 1, 1, -1, -1, 0, -1, 1, 0 };
int dir4[] = { 0, -1, 0, 1, 0 };
void dfs1(int x, int y, vector<pii> &ver) {
  vis1.insert(pii(x, y));
  ver.push_back(pii(x, y));
  for (int k = 0; k < 8; k++) {
    int a = x + dir8[k], b = y + dir8[k + 1];
    if (p1.count(pii(a, b)) && vis1.count(pii(a, b)) == 0)
      dfs1(a, b, ver);
  }
}
void dfs2(int x, int y) {
  vis2.insert(pii(x, y));
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) && vis2.count(pii(a, b)) == 0)
      dfs2(a, b);
  }
}
int tim;
int tarjan(int x, int y, pii fa, pii root) {
  // cout << "tj ";
  // cout << x << ' ' << y << endl;
  dfn[pii(x, y)] = low[pii(x, y)] = ++tim;
  int child = 0;
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) == 0)
      continue;
    if (dfn.count(pii(a, b)) == 0) {
      child++;
      if (tarjan(a, b, pii(x, y), root))
        return 1;
      if (pii(x, y) != root) {
        if (low[pii(a, b)] >= dfn[pii(x, y)]) {
          int ok = 1;
          for (int i = x - 1; i <= x + 1; i++)
            for (int j = y - 1; j <= y + 1; j++)
              if (1 <= i && i <= n && 1 <= j && j <= m) {
                if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
                  ok = 0;
              }

          if (ok) {
            return 1;
          }
        }
      }
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
    }
    else if (pii(a, b) != fa)
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
  }
  // cout << x << ' ' << y << ' ' << low[pii(x, y)] << ' ' << dfn[pii(x, y)] << endl;
  if (pii(x, y) == root) {
    if (child >= 2) {
      int ok = 1;
      for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
          if (1 <= i && i <= n && 1 <= j && j <= m) {
            if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
              ok = 0;
          }
      return ok;
    }
  }
  return 0;
}
void test() {
  cin >> n >> m >> c;
  p1.clear(), vis1.clear();
  vector<pii> pnt;
  for (int i = 1; i <= c; i++) {
    int x, y;
    cin >> x >> y;
    p1.insert(pii(x, y));
    pnt.push_back(pii(x, y));
  }
  /*
-1: c == n*m || c == n*m-1 || (c == n*m-2 && 两个白格相邻)
 0: 白格不连通
 1: 白格连通且存在割点
 2: 其他情况
 */
  if (c == n * m || c == n * m - 1) {
    cout << -1 << endl;
    return;
  }
  if (c == n * m - 2) {
    vector<vector<int>> a;
    a.assign(n + 5, vector<int>(m + 5));
    for (auto [x, y] : p1)
      a[x][y] = 1;
    int ok = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m - 1; j++) {
        if (a[i][j] == 0 && a[i][j + 1] == 0)
          ok = 1;
      }
    for (int i = 1; i <= n - 1; i++)
      for (int j = 1; j <= m; j++)
        if (a[i][j] == 0 && a[i + 1][j] == 0)
          ok = 1;
    cout << (ok ? -1 : 0) << endl;
    return;
  }
  if (n == 1 || m == 1) {
    if (c == 0) {
      cout << 1 << endl;
      return;
    }
    sort(all(pnt));
    auto [x1, y1] = pnt.back();
    auto [x2, y2] = pnt.front();
    if (x1 + y1 - 1 == c || x2 + y2 - 1 == n + m - 1 - c + 1)
      cout << 1 << endl;
    else
      cout << 0 << endl;
    // cout << (c == n+m-1 ? 0 : 1) << endl;
    return;
  }
  if (c == 0) {
    cout << 2 << endl;
    return;
  }
  for (auto [x, y] : p1) {
    if (vis1.count(pii(x, y)) == 0) {
      vector<pii> ver;
      dfs1(x, y, ver);
      p2.clear(), vis2.clear();
      for (auto [x, y] : ver) {
        for (int k = 0; k < 8; k++) {
          int a = x + dir8[k], b = y + dir8[k + 1];
          if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
            p2.insert(pii(a, b));
        }
      }
      auto [a, b] = *p2.begin();
      dfs2(a, b);
      if (vis2.size() != p2.size()) {
        cout << 0 << endl;
        return;
      }
    }
  }
  p2.clear();
  for (auto [x, y] : p1) {
    for (int a = x - 2; a <= x + 2; a++)
      for (int b = y - 2; b <= y + 2; b++)
        if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
          p2.insert(pii(a, b));
  }
  // for (auto [x, y] : p2) {
  //   cout << x << ' ' << y << endl;
  // }
  int ok = 0;
  dfn.clear(), low.clear(), tim = 0;
  for (auto [x, y] : p2) {
    if (dfn.count(pii(x, y)) == 0) {
      if (tarjan(x, y, pii(-1, -1), pii(x, y))) {
        ok = 1;
        break;
      }
    }
  }
  cout << (ok ? 1 : 2) << endl;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T; cin >> T; while (T--)
  test();
  // cout << clock() << "ms" << endl;
  return 0;
}
```

## 使用 `unordered_map` 并提前设置索引表的大小

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned int
// #define pii pair<int, int>
template <typename T> using vector2 = vector<vector<T>>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define all(x) (x).begin(), (x).end()
// #define endl '\n'
// #define endl " line in : " << __LINE__ << endl
struct pii {
  int first, second;
  pii(int x = 0, int y = 0) { first = x, second = y; }
  bool operator<(const pii &p) const {
    return first < p.first || (first == p.first && second < p.second);
  }
  bool operator==(const pii &p) const {
    return first == p.first && second == p.second;
  }
};
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return p.first << 32 | p.second;
  }
};
const int N = 15, INF = 1e16, P = 998244353;
int n, m, c;
unordered_set<pii> p1, vis1;
unordered_set<pii> p2, vis2;
unordered_map<pii, int> dfn, low;
int dir8[] = { 0, 1, 1, -1, -1, 0, -1, 1, 0 };
int dir4[] = { 0, -1, 0, 1, 0 };
void dfs1(int x, int y, vector<pii> &ver) {
  vis1.insert(pii(x, y));
  ver.push_back(pii(x, y));
  for (int k = 0; k < 8; k++) {
    int a = x + dir8[k], b = y + dir8[k + 1];
    if (p1.count(pii(a, b)) && vis1.count(pii(a, b)) == 0)
      dfs1(a, b, ver);
  }
}
void dfs2(int x, int y) {
  vis2.insert(pii(x, y));
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) && vis2.count(pii(a, b)) == 0)
      dfs2(a, b);
  }
}
int tim;
int tarjan(int x, int y, pii fa, pii root) {
  // cout << "tj ";
  // cout << x << ' ' << y << endl;
  dfn[pii(x, y)] = low[pii(x, y)] = ++tim;
  int child = 0;
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) == 0)
      continue;
    if (dfn.count(pii(a, b)) == 0) {
      child++;
      if (tarjan(a, b, pii(x, y), root))
        return 1;
      if (pii(x, y) != root) {
        if (low[pii(a, b)] >= dfn[pii(x, y)]) {
          int ok = 1;
          for (int i = x - 1; i <= x + 1; i++)
            for (int j = y - 1; j <= y + 1; j++)
              if (1 <= i && i <= n && 1 <= j && j <= m) {
                if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
                  ok = 0;
              }

          if (ok) {
            return 1;
          }
        }
      }
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
    }
    else if (pii(a, b) != fa)
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
  }
  // cout << x << ' ' << y << ' ' << low[pii(x, y)] << ' ' << dfn[pii(x, y)] << endl;
  if (pii(x, y) == root) {
    if (child >= 2) {
      int ok = 1;
      for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
          if (1 <= i && i <= n && 1 <= j && j <= m) {
            if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
              ok = 0;
          }
      return ok;
    }
  }
  return 0;
}
void test() {
  cin >> n >> m >> c;
  p1.clear(), vis1.clear();
  vector<pii> pnt;
  for (int i = 1; i <= c; i++) {
    int x, y;
    cin >> x >> y;
    p1.insert(pii(x, y));
    pnt.push_back(pii(x, y));
  }
  /*
-1: c == n*m || c == n*m-1 || (c == n*m-2 && 两个白格相邻)
 0: 白格不连通
 1: 白格连通且存在割点
 2: 其他情况
 */
  if (c == n * m || c == n * m - 1) {
    cout << -1 << endl;
    return;
  }
  if (c == n * m - 2) {
    vector<vector<int>> a;
    a.assign(n + 5, vector<int>(m + 5));
    for (auto [x, y] : p1)
      a[x][y] = 1;
    int ok = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m - 1; j++) {
        if (a[i][j] == 0 && a[i][j + 1] == 0)
          ok = 1;
      }
    for (int i = 1; i <= n - 1; i++)
      for (int j = 1; j <= m; j++)
        if (a[i][j] == 0 && a[i + 1][j] == 0)
          ok = 1;
    cout << (ok ? -1 : 0) << endl;
    return;
  }
  if (n == 1 || m == 1) {
    if (c == 0) {
      cout << 1 << endl;
      return;
    }
    sort(all(pnt));
    auto [x1, y1] = pnt.back();
    auto [x2, y2] = pnt.front();
    if (x1 + y1 - 1 == c || x2 + y2 - 1 == n + m - 1 - c + 1)
      cout << 1 << endl;
    else
      cout << 0 << endl;
    // cout << (c == n+m-1 ? 0 : 1) << endl;
    return;
  }
  if (c == 0) {
    cout << 2 << endl;
    return;
  }
  for (auto [x, y] : p1) {
    if (vis1.count(pii(x, y)) == 0) {
      vector<pii> ver;
      dfs1(x, y, ver);
      p2.clear(), vis2.clear();
      for (auto [x, y] : ver) {
        for (int k = 0; k < 8; k++) {
          int a = x + dir8[k], b = y + dir8[k + 1];
          if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
            p2.insert(pii(a, b));
        }
      }
      auto [a, b] = *p2.begin();
      dfs2(a, b);
      if (vis2.size() != p2.size()) {
        cout << 0 << endl;
        return;
      }
    }
  }
  p2.clear();
  for (auto [x, y] : p1) {
    for (int a = x - 2; a <= x + 2; a++)
      for (int b = y - 2; b <= y + 2; b++)
        if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
          p2.insert(pii(a, b));
  }
  // for (auto [x, y] : p2) {
  //   cout << x << ' ' << y << endl;
  // }
  int ok = 0;
  dfn.clear(), low.clear(), tim = 0;
  for (auto [x, y] : p2) {
    if (dfn.count(pii(x, y)) == 0) {
      if (tarjan(x, y, pii(-1, -1), pii(x, y))) {
        ok = 1;
        break;
      }
    }
  }
  cout << (ok ? 1 : 2) << endl;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#define MOD 1226959
  p1.rehash(MOD);
  vis1.rehash(MOD);
  p2.rehash(MOD);
  vis2.rehash(MOD);
  dfn.rehash(MOD);
  low.rehash(MOD);
  int T; cin >> T; while (T--)
  test();
  // cout << clock() << "ms" << endl;
  return 0;
}
```

## 使用 `unordered_map` 并手动删除元素

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
const int N = 15, INF = 1e16, P = 998244353;
int n, m, c;
#define MOD 1226959
template<>
struct std::hash<pii> {
  size_t operator()(const pii& p) const noexcept {
    return (((p.first << 32 | p.second) % MOD) + MOD) % MOD;
  }
};
unordered_set<pii> p1, vis1;
unordered_set<pii> p2, vis2;
unordered_map<pii, int> dfn, low;
int dir8[] = { 0, 1, 1, -1, -1, 0, -1, 1, 0 };
int dir4[] = { 0, -1, 0, 1, 0 };
void dfs1(int x, int y, vector<pii> &ver) {
  vis1.insert(pii(x, y));
  ver.push_back(pii(x, y));
  for (int k = 0; k < 8; k++) {
    int a = x + dir8[k], b = y + dir8[k + 1];
    if (p1.count(pii(a, b)) && vis1.count(pii(a, b)) == 0)
      dfs1(a, b, ver);
  }
}
void dfs2(int x, int y) {
  vis2.insert(pii(x, y));
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) && vis2.count(pii(a, b)) == 0)
      dfs2(a, b);
  }
}
int tim;
int tarjan(int x, int y, pii fa, pii root) {
  // cout << "tj ";
  // cout << x << ' ' << y << endl;
  dfn[pii(x, y)] = low[pii(x, y)] = ++tim;
  int child = 0;
  for (int k = 0; k < 4; k++) {
    int a = x + dir4[k], b = y + dir4[k + 1];
    if (p2.count(pii(a, b)) == 0)
      continue;
    if (dfn.count(pii(a, b)) == 0) {
      child++;
      if (tarjan(a, b, pii(x, y), root))
        return 1;
      if (pii(x, y) != root) {
        if (low[pii(a, b)] >= dfn[pii(x, y)]) {
          int ok = 1;
          for (int i = x - 1; i <= x + 1; i++)
            for (int j = y - 1; j <= y + 1; j++)
              if (1 <= i && i <= n && 1 <= j && j <= m) {
                if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
                  ok = 0;
              }

          if (ok) {
            return 1;
          }
        }
      }
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
    }
    else if (pii(a, b) != fa)
      low[pii(x, y)] = min(low[pii(x, y)], low[pii(a, b)]);
  }
  // cout << x << ' ' << y << ' ' << low[pii(x, y)] << ' ' << dfn[pii(x, y)] << endl;
  if (pii(x, y) == root) {
    // if (child >= 2)
    //   cout << "case 2" << endl;
    if (child >= 2) {
      int ok = 1;
      for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
          if (1 <= i && i <= n && 1 <= j && j <= m) {
            if (p1.count(pii(i, j)) == 0 && p2.count(pii(i, j)) == 0)
              ok = 0;
          }
      return ok;
    }
  }
  return 0;
}
pii tmp[MOD];
void myclear(unordered_set<pii> &st) {
  // vector<pii> tmp;
  int len = 0;
  for (auto&& x : st)
    tmp[++len] = x;
  for (int i = 1; i <= len; i++)
    st.erase(tmp[i]);
}
void myclear(unordered_map<pii, int> &mp) {
  int len = 0;
  for (auto&& [x, y] : mp)
    tmp[++len] = x;
  for (int i = 1; i <= len; i++)
    mp.erase(tmp[i]);
}
void test() {
  cin >> n >> m >> c;
  // p1.clear(), vis1.clear();
  myclear(p1), myclear(vis1);
  vector<pii> pnt;
  for (int i = 1; i <= c; i++) {
    int x, y;
    cin >> x >> y;
    p1.insert(pii(x, y));
    pnt.push_back({ x, y });
  }
  /*
-1: c == n*m || c == n*m-1 || (c == n*m-2 && 两个白格相邻)
 0: 白格不连通
 1: 白格连通且存在割点
 2: 其他情况
 */
  if (c == n * m || c == n * m - 1) {
    cout << -1 << endl;
    return;
  }
  if (c == n * m - 2) {
    vector<vector<int>> a;
    a.assign(n + 5, vector<int>(m + 5));
    for (auto [x, y] : p1)
      a[x][y] = 1;
    int ok = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m - 1; j++) {
        if (a[i][j] == 0 && a[i][j + 1] == 0)
          ok = 1;
      }
    for (int i = 1; i <= n - 1; i++)
      for (int j = 1; j <= m; j++)
        if (a[i][j] == 0 && a[i + 1][j] == 0)
          ok = 1;
    cout << (ok ? -1 : 0) << endl;
    return;
  }
  if (n == 1 || m == 1) {
    if (c == 0) {
      cout << 1 << endl;
      return;
    }
    sort(all(pnt));
    auto [x1, y1] = pnt.back();
    auto [x2, y2] = pnt.front();
    if (x1 + y1 - 1 == c || x2 + y2 - 1 == n + m - 1 - c + 1)
      cout << 1 << endl;
    else
      cout << 0 << endl;
    // cout << (c == n+m-1 ? 0 : 1) << endl;
    return;
  }
  if (c == 0) {
    cout << 2 << endl;
    return;
  }
  for (auto [x, y] : p1) {
    if (vis1.count(pii(x, y)) == 0) {
      vector<pii> ver;
      dfs1(x, y, ver);
      // p2.clear(), vis2.clear();
      myclear(p2), myclear(vis2);
      for (auto [x, y] : ver) {
        for (int k = 0; k < 8; k++) {
          int a = x + dir8[k], b = y + dir8[k + 1];
          if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
            p2.insert(pii(a, b));
        }
      }
      dfs2(p2.begin()->first, p2.begin()->second);
      if (vis2.size() != p2.size()) {
        cout << 0 << endl;
        return;
      }
    }
  }
  // p2.clear();
  myclear(p2);
  for (auto [x, y] : p1) {
    for (int a = x - 2; a <= x + 2; a++)
      for (int b = y - 2; b <= y + 2; b++)
        if (1 <= a && a <= n && 1 <= b && b <= m && p1.count(pii(a, b)) == 0)
          p2.insert(pii(a, b));
  }
  // for (auto [x, y] : p2) {
  //   cout << x << ' ' << y << endl;
  // }
  int ok = 0;
  myclear(dfn), myclear(low), tim = 0;
  // dfn.clear(), low.clear(), tim = 0;
  for (auto [x, y] : p2) {
    if (dfn.count(pii(x, y)) == 0) {
      if (tarjan(x, y, pii(-1, -1), pii(x, y))) {
        ok = 1;
        break;
      }
    }
  }
  cout << (ok ? 1 : 2) << endl;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T; cin >> T; while (T--)
  test();
  // cout << clock() << "ms" << endl;
  return 0;
}
```

最后，送给大家一只可爱的芙芙

![可爱的芙芙](./可爱的芙芙.jpg)

芙芙这么可爱，不点个赞再走吗......
