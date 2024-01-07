#include <bits/stdc++.h>
using namespace std;
namespace fs = std::filesystem;
using namespace std::chrono;
using namespace std::chrono_literals;

int main() {
  system("chcp 65001");
  ofstream f("index.html");
  f << R"delimiter(<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>INF_512的博客</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      max-width:800px;
      margin: 0 auto;
    }
    .article-list {
      list-style: none;
      padding: 0;
    }
    .article-list li {
      margin-bottom: 10px;
    }
    a { text-decoration:none; }
    a:link { color: #0E90D2; }
    a:active { color: #0E90D2; }
    a:visited { color:#0E90D2; }
    a:hover { color: #095F8A; }
  </style>
</head>
<body>
  <h1>文章列表</h1>
  <hr>
  <ul class="article-list" id="articleList">
)delimiter";
  
  vector<pair<local_time<days>, string>> a;
  for (const auto& file : fs::directory_iterator("./article")) {
    if (file.is_regular_file()) {
      auto lwt = last_write_time(file);
      zoned_time zt("Asia/Shanghai", file_clock::to_sys(lwt));
      a.push_back(make_pair(time_point_cast<days>(zt.get_local_time()), file.path().stem().string()));
      // std::cout << "Asia/Shanghai" << " - 时区时间：" << zt << endl;
    }
  }
  sort(a.begin(), a.end(), greater<pair<local_time<days>, string>>());
  for (auto [t, s] : a) {
    std::cout << t << " : " << s << endl;
    f << "<li>" << t << " <a href=\"./article/" << s << ".html\">" << s << "</a></li>" << endl;
  }
  f << R"delimiter(  </ul>
</body>
</html>)delimiter";
  f.close();
  return 0;
}