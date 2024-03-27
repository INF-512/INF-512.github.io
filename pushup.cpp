#include <bits/stdc++.h>
using namespace std;
namespace fs = std::filesystem;
#define int long long
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
#define loop(n) for (int _n = n; _n; _n--)
#define endl '\n'
// #define endl " line in : " << __LINE__ << endl
const int N = 2e5 + 5, INF = 1e18, P = 998244353;
void dfs(fs::path p) {
  for (const auto &file : fs::directory_iterator(p)) {
    if (file.is_directory()) {
      if (file.path().filename() != ".git" && file.path().filename() != "System Volume Information" && file.path().filename() != "$RECYCLE.BIN")
        dfs(file.path());
    }
    else if (file.is_regular_file()) {
      cout << file.path().string() << endl;
      system((string("git add ") + file.path().string()).c_str());
    }
  }
}
void test() {
  // you have to throw yourself into a problem for hours,
  // and try everything you can try.
  dfs("E:/");
  system("git commit -m \"updata\"");
  system("git push");
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  // int T; cin >> T; loop(T)
  test();
  return 0;
}