#include <bits/stdc++.h>
using namespace std;
namespace fs = std::filesystem;
using namespace std::chrono;
using namespace std::chrono_literals;
mt19937 gen((random_device())());
string all;
int utot;
int dfs(fs::path p, int fid) {
  string cstr;
  int cid = ++utot;
  // cout << cid << ' ' << fid << ' ' << p.string() << endl;
  cstr += format("<ul id=\"u{}\">\n", cid);
  if (cid == 1) {
    cstr += format("<li onclick=\"replace_ul('u{}', 'u{}')\">{}</li>\n", cid, fid, "x");
    cstr += format("<li><a href=\"/index.html?src={}?ver={}&pos=u{}\">{}</a></li>\n", "/首页.md", gen(), cid, "首页");
    int nid;
    nid = dfs(p / "算法", cid);
    cstr += format("<li onclick=\"replace_ul('u{}', 'u{}')\">{}</li>\n", cid, nid, "算法>");
    nid = dfs(p / "数据结构", cid);
    cstr += format("<li onclick=\"replace_ul('u{}', 'u{}')\">{}</li>\n", cid, nid, "数据结构>");
    nid = dfs(p / "题目", cid);
    cstr += format("<li onclick=\"replace_ul('u{}', 'u{}')\">{}</li>\n", cid, nid, "题目>");
  }
  else {
    cstr += format("<li onclick=\"replace_ul('u{}', 'u{}')\">{}</li>\n", cid, fid, "<" + p.stem().string());
    for (const auto &file : fs::directory_iterator(p)) {
      // cout << cid << ' ' << file.path() << endl;
      if (file.is_directory()) {
        // cout << cid << ' ' << file.path() << endl;
        int nid = dfs(file.path(), cid);
        cstr += format("<li onclick=\"replace_ul('u{}', 'u{}')\">{}</li>\n", cid, nid, file.path().stem().string()+">");
      }
      else if (file.is_regular_file() && file.path().extension() == ".md") {
        cstr += format("<li><a href=\"/index.html?src={}?ver={}&pos=u{}\">{}</a></li>\n", file.path().string(), gen(), cid, file.path().stem().string());
      }
    }
  }
  cstr += "</ul>\n";
  all += cstr;
  return cid;
}
int main() 
  system("chcp 65001");
  dfs("/", 1);
  cout << all << endl;
  // for (const auto& file : fs::directory_iterator("./article")) {
  //   // if (file.is_regular_file()) {
  //     auto lwt = last_write_time(file);
  //     zoned_time zt("Asia/Shanghai", file_clock::to_sys(lwt));
  //     std::cout << "Asia/Shanghai" << " - 时区时间：" << zt << ' ' << file.path() << endl;
  //   // }
  // }
//   f << R"delimiter(  </ul>
// </body>
// </html>)delimiter";
  return 0;
}