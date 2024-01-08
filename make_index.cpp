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
  cstr += format("<li onclick=\"replace_ul('u{}', 'u{}')\">{}</li>\n", cid, fid, p.stem().string());
  for (const auto &file : fs::directory_iterator(p)) {
    // cout << cid << ' ' << file.path() << endl;
    if (file.is_directory()) {
      // cout << cid << ' ' << file.path() << endl;
      if (cid != 1 || file.path().filename() == "article") {
        int nid = dfs(file.path(), cid);
        cstr += format("<li onclick=\"replace_ul('u{}', 'u{}')\">{}</li>\n", cid, nid, file.path().stem().string());
      }
    }
    else if (file.is_regular_file() && file.path().extension() == ".md") {
      cstr += format("<li><a href=\"/test.html?src={}?ver={}&pos=u{}\">{}</a></li>\n", file.path().string(), gen(), cid, file.path().stem().string());
    }
  }
  cstr += "</ul>\n";
  all += cstr;
  return cid;
}
int main() {
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