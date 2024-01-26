// function getParameterByName(name, url) {
//   if (!url) url = window.location.href;
//   name = name.replace(/[\[\]]/g, "\\$&");
//   var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
//       results = regex.exec(url);
//   if (!results) {
//     if (name == "src") return "/home";
//     return null;
//   }
//   return decodeURIComponent(results[2].replace(/\+/g, " "));
// }
function replace_ul(u1, u2) {
  document.getElementById(u1).style.display="none";
  document.getElementById(u2).style.display="block";
}
function loadMarkdownFile(filename) {
  fetch(filename)
  .then(response => response.text())
  .then(data => {
    var markdown_text = document.getElementById("markdown_text");
    markdown_text.innerHTML = data;
    console.log(markdown_text.innerHTML);
    texme.renderPage();
    hljs.highlightAll();
  })
  .catch(error => {
    console.error("读取文件时发生错误", error);
  });
}
function loadGlobalUl(filename) {
  fetch(filename)
  .then(response => response.text())
  .then(data => {
    document.getElementById("sidebar").innerHTML = data;
    console.log(data);
    var s = (new URL(window.location.href)).pathname;
    s = s.split('/').slice(0, -2).join('/');
    s = "u" + s.replace(/\//g, "-") + "-";
    console.log(s);
    document.getElementById(s).style.display = 'block';
  })
  .catch(error => {
    console.error("读取文件时发生错误", error);
  });
}
// loadMarkdownFile("./text.md" + "?ver=" + Math.floor(Math.random() * 1000000000));
// loadGlobalUl("/global.ul");
