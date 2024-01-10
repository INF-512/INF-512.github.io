#include <bits/stdc++.h>
using namespace std;
namespace fs = std::filesystem;
using namespace std::chrono;
using namespace std::chrono_literals;
#define all(x) (x).begin(), (x).end()
mt19937 gen((random_device())());
string text;
int utot;
struct Info {
  string name, type;
  int rank;
};
template<class T>
string get_line(T &f) {
  string s;
  while (1) {
    char c = f.get();
    if (c == EOF || c == '\n')
      return s;
    s += c;
  }
}
Info get_info(fs::path p) {
  Info res = { "", "", -1 };
  ifstream f(p / "info.txt");
  if (f.is_open() == 0)
    return res;
  while (f.peek() != EOF) {
    string s = get_line(f);
    int t = s.find('=');
    if (t != string::npos) {
      string key = s.substr(0, t), val = s.substr(t + 1);
      if (key == "name")
        res.name = val;
      else if (key == "type")
        res.type = val;
      else if (key == "rank")
        res.rank = stoi(val);
    }
  }
  return res;
}
string get_uid(string s) {
  replace(all(s), '\\', '/');
  replace(all(s), '/', '-');
  return s;
}
string dfs(fs::path p) {
  string cstr;
  // cout << cid << ' ' << fid << ' ' << p.string() << endl;
  string fid = get_uid(p.parent_path().string()), cid = get_uid(p.string());
  if (cid.back() != '-') cid += '-';
  cstr += format("<ul id=\"u{}\">\n", cid);
  if (p != "/") {
    Info info = get_info(p);
    cstr += format("<li onclick=\"replace_ul('u{}', 'u{}')\">{}</li>\n", cid, fid, "&lt;" + info.name);
  }
  vector<pair<int, string>> lst;
  for (const auto &file : fs::directory_iterator(p)) {
    if (file.is_directory()) {
      cout << cid << ' ' << file.path().string() << endl;
      Info info = get_info(file.path());
      cout << info.name << ' ' << info.type << ' ' << info.rank << endl;
      if (info.rank != -1) {
        if (info.type == "directory") {
          string nid = dfs(file.path());
          lst.push_back({ info.rank, format("<li onclick=\"replace_ul('u{}', 'u{}')\">{}</li>\n", cid, nid, info.name+"&gt;") });
        }
        else if (info.type == "article") {
          lst.push_back({ info.rank, format("<li><a href=\"{}\">{}</a></li>\n", file.path().string(), info.name) });
        }
      }
    }
  }
  sort(lst.begin(), lst.end());
  for (auto [r, s] : lst) {
    replace(all(s), '\\', '/');
    cstr += s;
  }
  cstr += "</ul>\n";
  text += cstr;
  return cid;
}
int main() {
  system("chcp 65001");
  dfs("/");
  cout << text;
  ofstream f("/global.ul");
  f << text;
  f.close();
  return 0;
}