#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
#define loop(n) for (int _n = n; _n; _n--)
#define endl '\n'
// #define endl " line in : " << __LINE__ << endl
const int N = 2e5 + 5, INF = 1e18, P = 998244353;
#define uint unsigned int
mt19937_64 gen(time(0));
uint rand(uint l, uint r) {
  uniform_int_distribution<uint> dis(l, r);
  return dis(gen);
}
double distance(int x1, int y1, int x2, int y2) {
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
// 420 140
// 1100 850
int xmin = 420, xmax = 1100, ymin = 140, ymax = 850, d = 100;
vector<pii> p;
int check(int x, int y) {
  for (auto [a, b] : p)
    if (distance(x, y, a, b) < d)
      return 1;
  return 0;
}
void click() {
  mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
  Sleep(10);
  mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
void sol() {
  p.clear();
  loop (10) {
    int x, y;
    do {
      x = rand(xmin, xmax), y = rand(ymin, ymax);
    } while (check(x, y));
    p.push_back({ x, y });
  }
  for (auto [x, y] : p) {
    SetCursorPos(x, y);
    Sleep(100);
    click();
    Sleep(100);
  }
}
void test() {
  RegisterHotKey(NULL, 10001, 0, VK_F1);
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0) != 0) {
    if (msg.message == WM_HOTKEY) {
      cout << "WM_HOTKEY received" << endl;
      sol();
    }
  } 
  // system("pause");
  // while (1) {
  //   POINT pt;
  //   GetCursorPos(&pt);
  //   cout << pt.x << ' ' << pt.y << endl;
  //   Sleep(500);
  // }
}
signed main() {
  // ios::sync_with_stdio(0);
  // cin.tie(0);
  // int T; cin >> T; loop(T)
  test();
  return 0;
}