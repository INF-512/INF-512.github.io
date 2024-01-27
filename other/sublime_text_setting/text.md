如何把 Sublime Text 打造成最炫酷的代码编辑器

# 前言

`Sublime Text` 做到了真正的自定义，哪里不顺眼就改哪里，没有你做不到的，只有你想不到的。

# 最终效果

![](https://inf-512.github.io/other/sublime_text_setting/p1.png)

# 相关资源

`sublime_text_build_4169_x64_setup.exe`

链接：`https://pan.baidu.com/s/1h7pSQMR-xhlPYLAL9eNvdw `

提取码：`7rxg`

`Sublime Text Background Image.7z`

链接：`https://pan.baidu.com/s/1afw3nMLADxHciEi5SPKHEQ `

提取码：`l9e4`

# 安装 `Sublime Text`

下载并运行 `sublime_text_build_4169_x64_setup.exe`，安装路径这里我选择 `C:\Sublime Text`，大家可以根据需要修改。

安装完后在 `C:\Sublime Text` 目录下新建一个名为 `Data` 的文件夹。

![](https://inf-512.github.io/other/sublime_text_setting/p2.png)

# 注册

如果不注册，`Sublime Text` 的标题会显示 `(UNREGISTERED)`，而且时不时有弹窗提醒你付费，非常不美观。

将 `C:\Sublime Text\sublime_text.exe` 拷贝一份新的副本并重命名为 `sublime_text4.exe`。

打开 `sublime_text.exe`，然后把 `sublime_text4.exe` 拖进来。

按下 `Ctrl+H`，然后把下面代码复制到 `Find` 中，

```
c980 7805 000f
94c1
```

把下面代码复制到 `Replace` 中，

```
c9c6 4005 0148
85c9
```

![](https://inf-512.github.io/other/sublime_text_setting/p3.png)

点击 `Replace`，然后保存，退出。

这时再打开 `sublime_text4.exe` 就已经注册好了。

# 安装 `Package Control`

按下 `Ctrl+Shift+P`，输入 install，选中 `Install Package Control`，然后回车，等待安装。

![](https://inf-512.github.io/other/sublime_text_setting/p4.png)

弹出窗口 `Package Control was successfully installed` 表示安装成功。

![](https://inf-512.github.io/other/sublime_text_setting/p5.png)

# 用户配置文件

按下 `Ctrl+Shift+P`，输入 `setting`，选中 `Preferences: Settings` ，然后回车，把下面的内容复制到右侧的窗口中。

\begin{md}
```
// Settings in here override those in "Default/Preferences.sublime-settings",
// and are overridden in turn by syntax-specific settings.
{
  // 代码字体。
  "font_face": "Cascadia Code",
  // tab 大小。
  "tab_size": 2,
  // 开启 tab 转空格。
  "translate_tabs_to_spaces": true,
  // 关闭自动修剪空格。
  // 如果打开这个，那么连续回车两下，上次回车产生的 tab 会莫名消失。
  "trim_automatic_white_space": false,
  
  // 关闭自动补全，这个自动补全出现的选项大多没什么用。
  "auto_complete": false,
  // 关闭括号补全，可以根据需要打开。
  "auto_match_enabled": false,
  // 允许在选中的文本中 Find 和 Replace。
  "auto_find_in_selection": true,
  
  // 开启自动换行。
  "word_wrap": true,
  // 关闭更新检查。
  "update_check": false,
  // 下面这两个关闭后，防止鼠标移动到函数上的时候出现一些没用的提示。
  "index_files": false,
  "show_definitions": false,
  // 文件失去焦点时自动保存。
  "save_on_focus_lost": true,
  // 加入中文单词分割符，在使用Ctrl+方向键的时候不会跳过头。
  "word_separators": "./\\()\"'-:,.;<>~!@#$%^&*|+=[]{}`~?，。（）；、？“”‘’：！【】",
  // 侧边栏不显示后缀是 dll 和 exe 的文件。
  "file_exclude_patterns": [
    "*.dll",
    "*.exe",
  ],
  // 和上面同理。
  "folder_exclude_patterns": [
    
  ],
}
```
\end{md}

# 安装插件

按下 `Ctrl+Shift+P`，输入 `install`，选中 `Package Control: Install Package`，然后回车，等到出现搜索框，然后输入插件的名称回车进行安装。

![](https://inf-512.github.io/other/sublime_text_setting/p7.png)

## 常用插件

A File Icon：给侧边栏换上好看的文件图标。

SideBarTools：在侧边栏中右键点击文件出现更多选项。（SideBarEnhancements 插件的功能类似，不过出现选项有点过多）

SnippetMaker：更加简单地生成代码片段。

Material Theme：一款经典的主题和配色。

Theme - Darkmatter：一款深蓝色的主题和配色。

Colorsublime：里面有好多好看的配色。

PackageResourceViewer：能够修改插件内部文件，例如，主题文件和配色文件。

Transparency：设置背景透明度。

上述插件建议全部安装，安装完后如下图。

![](https://inf-512.github.io/other/sublime_text_setting/p8.png)

# 更换主题和配色

主题（Theme）包括标题栏，覆盖面板，侧边栏，选项卡，状态栏，小部件面板，滚动条等等。

配色（Color Scheme）包括代码颜色，代码背景色等等。

## 更换主题

按下 `Ctrl+Shift+P`，输入 `ui theme`，选中 `UI: Select Theme`，回车，选择你喜欢的主题，回车（这里我选的是 `Material-Theme`）。

## 更换配色

按下 `Ctrl+Shift+P`，输入 'ui color'，选中 `UI: Select Color Scheme`，回车，选择你喜欢的配色，回车（这里我选的是 `Darkmatter`）。

![](https://inf-512.github.io/other/sublime_text_setting/p9.png)

一般情况下主题和配色是成套的，例如上面的 `Material-Theme` 主题和 `Material-Theme` 配色，`Darkmatter` 主题和 `Darkmatter` 配色。

## 安装新的配色

按下 `Ctrl+Shift+P`，输入 `install theme`，选中 `Colorsublime: Install Theme`，回车，选择你喜欢的配色，回车。

![](https://inf-512.github.io/other/sublime_text_setting/p10.png)

如果不满意可以自行安装别的 `Sublime Text` 主题。

# 自定义主题

如果使用了不是成套的主题和配色，主题的颜色和配色的颜色不搭，需要用 `PackageResourceViewer` 插件修改主题文件。

这里拿 `Material-Theme` 主题和 `Darkmatter` 配色为例，绿色的主题背景色和深蓝色的代码背景色不搭，需要把绿色改为深蓝色。

![](https://inf-512.github.io/other/sublime_text_setting/p37.png)

按下 `Ctrl+Shift+P`，输入 `prvor`，选中 `PackageResourceViewer: Open Resource`，回车，输入 `material`，选中 `Material Theme` 回车，输入 `sublime-theme`，选中 `Material-Theme.sublime-theme`，回车。

`.sublime-theme` 是 `Sublime Text` 的主题配置文件。

我们需要把所有可能的背景色都改为深蓝色，为了避免改错了不小心把窗口关掉导致无法撤销，建议先备份一下。

## 单词翻译

TITLE BAR：标题栏（在界面最顶部）。

OVERLAY PANELS：覆盖面板（`Ctrl+Shift+P` 弹出）。

SIDEBAR：侧边栏（打开文件夹后 `Ctrl+K+B` 弹出）。

TABS：选项卡（在标题栏下面）。

STATUS BAR：状态栏（在界面最底部）。

WIDGET PANEL：小部件面板（`Ctrl+F` 以及类似的面板）。

SCROLLBARS：滚动条。

![](https://inf-512.github.io/other/sublime_text_setting/p12.png)

如果不知道代码是什么意思，可以直接删掉，保存，然后看看界面的变化。

`Material-Theme.sublime-theme` 文件改动信息如下：

```
@@ -13,7 +13,7 @@
// 标题栏背景色
   {
     "class": "title_bar",
     "settings": ["themed_title_bar"],
-    "bg": [38, 50, 56],
+    "bg": [20, 25, 31],
     "fg": [176, 190, 197, 255],
     "style": "system"
   },
@@ -24,7 +24,7 @@
// ??背景色
     {
       "class": "sheet_container_control",
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0
     },
   
@@ -35,7 +35,7 @@
// 边框颜色
     {
       "class": "grid_layout_control",
       "border_size": 1,
-      "border_color": [34, 45, 51]
+      "border_color": [20, 25, 31]
     },
   
   
@@ -52,13 +52,13 @@
// ??背景色
     {
       "class": "dialog",
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0
     },
   
// ??背景色
     {
       "class": "progress_bar_control",
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0,
     },
   
@@ -123,7 +123,7 @@
// ??背景色
     {
       "class": "table_row",
-      "layer0.tint": [84, 110, 122],
+      "layer0.tint": [51, 64, 79],
       "layer0.opacity": 0.0,
     },
   
@@ -159,10 +159,12 @@
// 覆盖面板背景色
     // Command Panel
      {
         "class": "overlay_control",
-        "layer0.texture": "Material Theme/assets/default/overlay-bg.png",
+        "layer0.tint": [20, 25, 31],
+        "layer1.tint": [20, 25, 31],
+        // "layer0.texture": "Material Theme/assets/default/overlay-bg.png",
         "layer0.inner_margin": [24, 4, 24, 33],
         "layer0.opacity": 1.0,
-        "layer1.texture": "Material Theme/assets/commons/quick-panel-background.png",
+        // "layer1.texture": "Material Theme/assets/commons/quick-panel-background.png",
         "layer1.inner_margin": [16, 0, 16, 25],
         "layer1.opacity": 1.0,
         "content_margin": [13, 13, 13, 33]
@@ -172,7 +174,7 @@
// 覆盖面板背景色
     {
       "class": "mini_quick_panel_row",
-      "layer0.tint": [38, 50, 56, 0],
+      "layer0.tint": [20, 25, 31],
       "layer0.inner_margin": [2, 2, 2, 2],
       "layer0.opacity": 1.0
     },
@@ -182,7 +184,7 @@
// 覆盖面板背景色
     {
       "class": "mini_quick_panel_row",
       "attributes": ["selected"],
-      "layer0.tint": [84, 110, 122],
+      "layer0.tint": [51, 64, 79],
       "layer0.opacity": 0.3
     },
   
@@ -191,7 +193,7 @@
// 覆盖面板背景色
     {
       "class": "quick_panel",
       "row_padding": [32, 12],
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0
     },
   
@@ -199,7 +201,7 @@
// 覆盖面板背景色
     {
       "class": "quick_panel_row",
-      "layer0.tint": [38, 50, 56, 0],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0
     },
   
@@ -208,7 +210,7 @@
// 覆盖面板背景色
     {
       "class": "quick_panel_row",
       "parents": [{"class": "overlay_control"}],
-      "layer0.tint": [38, 50, 56, 0],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0
     },
   
@@ -218,7 +220,7 @@
// 覆盖面板背景色
       "class": "quick_panel",
       "parents": [{"class": "overlay_control"}],
       "row_padding": [32, 12],
-      "layer0.tint": [38, 50, 56, 0],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0
     },
   
@@ -227,7 +229,7 @@
// 覆盖面板背景色
     {
       "class": "quick_panel_row",
       "attributes": ["selected"],
-      "layer0.tint": [84, 110, 122],
+      "layer0.tint": [51, 64, 79],
       "layer0.opacity": 0.3,
       "layer1.opacity": 0.0
     },
@@ -279,7 +281,7 @@
// 选项卡背景色和选项卡高度
     {
       "class": "tabset_control",
       "layer0.opacity": 1.0,
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "tint_index": 1,
       "layer0.inner_margin": [2, 6],
       "layer0.opacity": 1.0,
@@ -287,7 +289,7 @@
       "tab_overlap": 0,
       "tab_width": 180,
       "tab_min_width": 64,
-      "tab_height": 54,
+      "tab_height": 45,
       "mouse_wheel_switch": false
     },
     {
@@ -301,41 +303,44 @@
// 选项卡背景色
     {
       "class": "tab_control",
   
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.inner_margin": [24, 0],
       "layer0.opacity": 1.0,
       "tint_index": 0,
   
-      "layer1.texture": "Material Theme/assets/default/tab_current.png",
+      "layer1.tint": [20, 25, 31],
+      // "layer1.texture": "Material Theme/assets/default/tab_current.png",
       "layer1.inner_margin": [0, 0],
       "layer1.opacity": 0.0,
   
-      "layer2.tint": [128, 203, 196, 0],
+      // "layer2.tint": [128, 203, 196, 0],
+      "layer2.tint": [20, 25, 31],
       "layer2.inner_margin": [0, 0],
       "layer2.opacity": { "target": 0.0, "speed": 3.0, "interpolation": "smoothstep" },
   
       "layer3.inner_margin": [0, 0],
       "layer3.opacity": { "target": 1.0, "speed": 2.0, "interpolation": "smoothstep" },
-      "layer3.texture": {
-              "keyframes":
-              [
-                "Material Theme/assets/default/tab_animation1.png",
-                "Material Theme/assets/default/tab_animation2.png",
-                "Material Theme/assets/default/tab_animation3.png",
-                "Material Theme/assets/default/tab_animation4.png",
-                "Material Theme/assets/default/tab_animation5.png",
-                "Material Theme/assets/default/tab_animation6.png",
-                "Material Theme/assets/default/tab_animation7.png",
-                "Material Theme/assets/default/tab_animation8.png",
-                "Material Theme/assets/default/tab_animation9.png",
-                "Material Theme/assets/default/tab_animation10.png",
-                "Material Theme/assets/default/tab_animation11.png",
-                "Material Theme/assets/default/tab_animation12.png",
-                "Material Theme/assets/default/tab_animation13.png"
-              ],
-              "loop": false,
-              "frame_time": 0.015,
-      },
+      "layer3.tint": [31, 39, 48],
+      // "layer3.texture": {
+      //         "keyframes":
+      //         [
+      //           "Material Theme/assets/default/tab_animation1.png",
+      //           "Material Theme/assets/default/tab_animation2.png",
+      //           "Material Theme/assets/default/tab_animation3.png",
+      //           "Material Theme/assets/default/tab_animation4.png",
+      //           "Material Theme/assets/default/tab_animation5.png",
+      //           "Material Theme/assets/default/tab_animation6.png",
+      //           "Material Theme/assets/default/tab_animation7.png",
+      //           "Material Theme/assets/default/tab_animation8.png",
+      //           "Material Theme/assets/default/tab_animation9.png",
+      //           "Material Theme/assets/default/tab_animation10.png",
+      //           "Material Theme/assets/default/tab_animation11.png",
+      //           "Material Theme/assets/default/tab_animation12.png",
+      //           "Material Theme/assets/default/tab_animation13.png"
+      //         ],
+      //         "loop": false,
+      //         "frame_time": 0.015,
+      // },
   
       "content_margin": [16, 0, 8, 0],
       "max_margin_trim": 0,
@@ -543,7 +548,7 @@
// 侧边栏背景色
     {
       "class": "sidebar_container",
       "content_margin": [0, 12, 0, 0],
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0,
       "layer0.draw_center": false,
       "layer0.inner_margin": [0, 24, 12, 24],
@@ -552,11 +557,11 @@
     },
// 侧边栏背景色
     {
       "class": "sidebar_tree",
-      "row_padding": [24, 8],
+      "row_padding": [24, 6],
       "indent": 16,
       "indent_offset": 0,
       "indent_top_level": false,
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0,
       "layer1.tint": [0,0,0],
       "layer1.opacity": 0.0
@@ -698,7 +703,7 @@
// 侧边栏背景色
     {
       "class": "icon_folder",
       "content_margin": [11, 7],
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 0,
       "layer1.texture": "Material Theme/assets/default/folder.png",
       "layer1.opacity": 1.0,
@@ -875,7 +880,7 @@
   
// 侧边栏背景色
     {
       "class": "tree_row",
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 0.0,
       "layer0.inner_margin": [1, 1]
     },
@@ -940,10 +945,11 @@
   
// 滚动条背景色
     {
       "class": "scroll_bar_control",
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.inner_margin": [0, 6],
       "layer0.opacity": 1.0,
-      "layer1.texture": "Material Theme/assets/default/normal_bar_vertical.png",
+      "layer1.tint": [20, 25, 31],
+      // "layer1.texture": "Material Theme/assets/default/normal_bar_vertical.png",
       "layer1.opacity": 1.0,
       "layer1.inner_margin": [0, 6],
       "blur": false
@@ -965,10 +971,11 @@
// 滚动条背景色
     {
       "class": "scroll_bar_control",
       "attributes": ["horizontal"],
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.inner_margin": [0, 6],
       "layer0.opacity": 1.0,
-      "layer1.texture": "Material Theme/assets/default/normal_bar_horizontal.png",
+      "layer1.tint": [20, 25, 31],
+      // "layer1.texture": "Material Theme/assets/default/normal_bar_horizontal.png",
       "layer1.opacity": 1.0,
       "layer1.inner_margin": [6, 0],
       "blur": false
@@ -990,7 +997,8 @@
// 滚动条背景色
     {
       "class": "scroll_corner_control",
-      "layer0.texture": "Material Theme/assets/default/normal_bar_corner.png",
+      "layer0.tint": [20, 25, 31],
+      // "layer0.texture": "Material Theme/assets/default/normal_bar_corner.png",
       "layer0.opacity": 1.0,
       "layer0.inner_margin": [1, 1]
     },
@@ -1071,7 +1079,7 @@
   
// 滚动条背景色
     {
       "class": "puck_control",
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 0.0,
       "layer0.inner_margin": [1, 8, 1, 8],
       "layer1.texture": "Material Theme/assets/default/thumb_vertical.png",
@@ -1083,7 +1091,7 @@
// 滚动条背景色
     {
       "class": "puck_control",
       "attributes": ["horizontal"],
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 0.0,
       "layer0.inner_margin": [8, 1, 8, 1],
       "layer1.texture": "Material Theme/assets/default/thumb_horizontal.png",
@@ -1150,7 +1158,7 @@
       "content_margin": [8, 0, 0, 0],
   
       // Layer 0 base
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0,
       "layer0.inner_margin": [2, 2],
   
@@ -1161,12 +1169,12 @@
// 状态栏背景色
     {
       "class": "status_container",
-      "content_margin": [24, 12, 24, 12],
+      "content_margin": [10, 5, 24, 5],
     },
   
// 状态栏背景色
     {
       "class": "status_button",
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0,
       "layer0.draw_center": false,
       "layer0.inner_margin": [1, 0, 0, 0],
@@ -1176,7 +1184,7 @@
   
// 状态栏背景色
     {
       "class": "status_button",
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0,
       "layer0.draw_center": false,
       "layer0.inner_margin": [1, 0, 0, 0],
@@ -1207,10 +1215,10 @@
// 状态栏背景色
     // Status bar panel
     {
       "class": "panel_control",
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.inner_margin": [2, 2, 2, 2],
       "layer0.opacity": 1.0,
-      "layer1.tint": [38, 50, 56],
+      "layer1.tint": [20, 25, 31],
       "layer1.inner_margin": [2, 2, 2, 2],
       "layer1.opacity": 1.0,
       "content_margin": [6, 14, 6, 8],
@@ -1238,11 +1246,11 @@
   
// 文本输入框背景色
     {
       "class": "text_line_control",
-      "layer0.texture": "Material Theme/assets/default/input_field_border.png",
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0,
-      "layer0.inner_margin": [20, 5, 20, 5],
+      "layer0.inner_margin": [20, 0, 20, 0],
       "tint_index": 1,
-      "content_margin": [10, 8, 16, 8]
+      "content_margin": [0, 8, 0, 8]
     },
   
   
@@ -1251,7 +1259,8 @@
// 文本输入框背景色
     {
       "class": "text_line_control",
       "parents": [{"class": "overlay_control"}],
-      "layer0.texture": "Material Theme/assets/default/input_field_border--short.png",
+      // "layer0.texture": "Material Theme/assets/default/input_field_border--short.png",
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 1.0,
       "layer0.inner_margin": [32, 0, 32, 2],
       "layer0.draw_center": true,
@@ -1302,7 +1311,7 @@
       "class": "button_control",
       "content_margin": [6, 12, 6, 12],
       "min_size": [75, 0],
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.opacity": 0.0,
       "layer0.inner_margin": [6, 6],
       "layer1.texture": "Material Theme/assets/commons/full_button_indented.png",
@@ -1332,7 +1341,7 @@
     // Small Icon Buttons
     {
       "class": "icon_button_control",
-      "layer0.tint": [38, 50, 56],
+      "layer0.tint": [20, 25, 31],
       "layer0.inner_margin": [6, 6],
       "layer0.opacity": 0.0,
       "layer2.tint": [255, 255, 255],
@@ -8266,7 +8275,7 @@
       "settings": ["material_theme_titlebar"],
       "platforms": ["osx"],
       "fg": [96, 125, 139],
-      "bg": [38, 50, 56]
+      "bg": [20, 25, 31]
     },
   
     {
```

## 修改前后效果

![](https://inf-512.github.io/other/sublime_text_setting/p13.png)

![](https://inf-512.github.io/other/sublime_text_setting/p14.png)

这里有一个小 bug，如果你覆盖面板的文本输入框背景色还是绿色的，那么你可以这么做：

在 `C:\Sublime Text\Data\Packages\User` 目录下新建一个名为 `mytheme.sublime-theme` 的文件，将 `Material-Theme.sublime-theme` 的内容拷贝进去，然后把主题换成 `mytheme`。

# 自定义配色

如果对代码颜色不满意，可以用 `PackageResourceViewer` 插件修改配色文件，这里以 `Darkmatter` 配色为例。

按下 `Ctrl+Shift+P`，输入 `prvor`，选中 `PackageResourceViewer: Open Resource`，回车，输入 `dark`，选中 `Theme - Darkmatter` 回车，输入 `tmtheme`，选中 `Darkmatter.tmTheme`，回车，这个文件不大，建议读一读。

如果想改某个单词的颜色，但不知道这个单词是什么，可以选中这个单词，然后按下 `Ctrl+Shift+Alt+P`，会弹出提示框，给你一个大概的提示。

例如我们需要改代码背景色，很容易找到下面的语句，

```
<key>background</key>
<string>#14191f</string>
```

接下来把 `#14191f` 改为你喜欢的颜色就好了。

我们还需要改关键字的颜色，同样很容易找到下面的语句，

```
<dict>
  <key>name</key>
  <string>Keyword</string>
  <key>scope</key>
  <string>keyword</string>
  <key>settings</key>
  <dict>
    <key>foreground</key>
    <string>#748aa6</string>
  </dict>
</dict>
```

接下来把 `#748aa6` 改为你喜欢的颜色就好了，这比改主题颜色简单多了。

# 自定义中英文混合字体

`Sublime Text` 的 `font_face` 属性只能设置一种字体，设置了英文就没办法设置中文，同理，设置了中文就没办法设置英文，我们需要使用 `FontForge` 混合中英两种字体。

我们需要到[官网](https://fontforge.org/en-US/)下载并安装 `FontForge`。

安装完后，打开 `FontForge` 的根目录，用 `Sublime Text` 打开 `fontforge.bat`，将第 9 行替换为 `set LANGUAGE=zh_CN`，然后保存退出。

![](https://inf-512.github.io/other/sublime_text_setting/p15.png)

准备好一种中文字体和一种英文字体，这里以新宋体和 `Courier New` 为例。

![](https://inf-512.github.io/other/sublime_text_setting/p16.png)

用 `FontForge` 打开 `cour.ttf`。

![](https://inf-512.github.io/other/sublime_text_setting/p17.png)

依次点击 `元素(L)`，`字体信息(F)`，把字体名，字族名，人类可读名称都改为你喜欢的名字，这里以 `myfont` 为例。

![](https://inf-512.github.io/other/sublime_text_setting/p18.png)

点开 `通用`，把 `M全字大小(E)` 改为 2048。

![](https://inf-512.github.io/other/sublime_text_setting/p19.png)

点开 `OS/2`，`特征`，把全部特征都改为任何。

![](https://inf-512.github.io/other/sublime_text_setting/p20.png)

点击确定和更改。

![](https://inf-512.github.io/other/sublime_text_setting/p21.png)

先不要关闭上面的窗口，现在用 `FontForge` 打开 `simsun.ttc`。

依次点击 `元素(L)`，`字体信息(F)`，`通用`，把 `M全字大小(E)` 改为 2048。

点击 `OS/2`，`特征`，把全部特征改为任何，然后连续点击两次确定。

点击 `文件(F)`，`另存为(A)`，将文件另存到上面的文件夹中，然后关闭当前窗口。

![](https://inf-512.github.io/other/sublime_text_setting/p22.png)

回到打开 `cour.ttf` 文件的窗口，点击 `元素(L)`，`合并字体(M)`，选中刚刚另存好的 `NSimSun.sfd`。

![](https://inf-512.github.io/other/sublime_text_setting/p23.png)

连续确定两次，然后点击 `文件(F)`，`生成字体(G)`，按照下面的图片进行配置。

![](https://inf-512.github.io/other/sublime_text_setting/p24.png)

最后，点击 `Generate` 生成字体。

双击 `myfont.ttf`，然后点击安装。

![](https://inf-512.github.io/other/sublime_text_setting/p25.png)

安装完毕后，重启计算机，打开 `Sublime Text`，然后按下 `Ctrl+Shift+P`，输入 `settings`，选中 `Preferences: Settings`，回车，将 `"font_face": "Cascadia Code",`，替换成 `"font_face": "myfont",`，大功告成。

![](https://inf-512.github.io/other/sublime_text_setting/p26.png)

# 设置背景透明度

打开 `SublimeTextTrans` 的配置文件。

![](https://inf-512.github.io/other/sublime_text_setting/p27.png)

调整透明度的快捷键是 `Ctrl+Shift+1` 到 `Ctrl+Shift+6`，数字越小越透明，大家根据需要调整。

# 自定义代码片段

这里以用 `sum` 生成 `\sum_{}^{}` 为例。

首先选中 `\sum_{}^{}`，按下 `Ctrl+Shift+P`，输入 `smms`，选中 `SnippetMaker: Make Snippet`，回车，然后在 `Trigger(触发单词)` 中输入 `sum`，在 `Description(描述)` 中输入 `latex sum 符号`，`Scope(生效区域)` 这个可以改也可以不改，这里我不改直接回车，最后是文件名，这里我也是直接回车。

![](https://inf-512.github.io/other/sublime_text_setting/p28.png)

然后出现下面这个文件。

![](https://inf-512.github.io/other/sublime_text_setting/p29.png)

## 光标移动

\begin{md}
我们希望光标停在第 `1` 对花括号内，然后按下 `Tab` 后，光标移动到第 `2` 对花括号内，再按下 `tab` 后，光标移动到末尾，我们可以在第 `1` 对花括号内插入 `$1`，然后在第 `2` 对花括号内插入 `$2`，末尾的 `$3` 可以省略不写，完成后，输入 `sum` 然后按 `Tab` 就会出现 `\sum_{}^{}`。
\end{md}

![](https://inf-512.github.io/other/sublime_text_setting/p30.png)

# C++ 运行环境配置

假设你已经安装好 MinGW 并配置好环境变量。

首先按下 `Ctrl+Shift+P`，输入 `prvor`，选中 `PackageResourceViewer: Open Resource`，回车，然后输入 `C++` 回车，再输入 `c++ build`，选中 `C++ Single File.sublime-build`，回车，将文件内容改为如下：

\begin{md}
```
{
  "shell_cmd": "g++ \"${file}\" -o \"${file_path}/${file_base_name}\"",
  "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
  "working_dir": "${file_path}",
  "selector": "source.c++",

  "variants":
  [
    {
      "name": "Run",
      "shell_cmd": "g++ \"${file}\" -o \"${file_path}/${file_base_name}\" && start cmd /c \"\"${file_path}/${file_base_name}\" & pause\""
    }
  ]
}
```
\end{md}

# 自定义快捷键

我们需要按 `f7` 编译，按 `Ctrl+f5` 编译运行。

首先按下 Ctrl+\` 打开控制台，输入 `sublime.log_commands(True)`，回车，表示记录命令信息。

然后按下 `Ctrl+Shift+B`，选中 `C++ Single File`，回车，再打开控制台，找到下面这条语句，这就是刚才的编译命令。

```
command: build {"build_system": "Packages/C++/C++ Single File.sublime-build", "choice_build_system": true, "choice_variant": true, "variant": ""}
```

按下 `Ctrl+Shift+P`，输入 `key bind`，选中 `Preferences: Key Bindings`，回车，在右边的窗口中加入下面这条语句。

```
{ "keys": ["f7"], "command": "build", "args": {"build_system": "Packages/C++/C++ Single File.sublime-build", "choice_build_system": true, "choice_variant": true, "variant": ""} },
```

对比一下，快捷键执行的编译命令跟控制台输出的编译命令基本类似。

使用类似的方法得到编译运行命令，

```
command: build {"build_system": "Packages/C++/C++ Single File.sublime-build", "choice_build_system": true, "choice_variant": true, "variant": "Run"}
```

然后在快捷键窗口中加入下面这条语句，

```
{ "keys": ["Ctrl+f5"], "command": "build", "args": {"build_system": "Packages/C++/C++ Single File.sublime-build", "choice_build_system": true, "choice_variant": true, "variant": "Run"} },
```

然后就搞定了。

![](https://inf-512.github.io/other/sublime_text_setting/p31.png)

# 常用快捷键

Ctrl+K+B：可以打开/关闭侧边栏

Ctrl+\`：打开控制台

Ctrl+G：跳转到第几行

Ctrl+W：关闭当前打开文件

Ctrl+Shift+W：关闭所有打开文件

Ctrl+Shift+V：粘贴并格式化

Ctrl+D：选择单词

Ctrl+Shift+D：复制光标所在整行，插入到下一行

Ctrl+L：选择行

Ctrl+Enter：在下一行前插入新行

Ctrl+Shift+Enter：在当前行前插入新行

Ctrl+X：删除当前行

Ctrl+M：跳转到对应括号

Ctrl+鼠标拖动：多光标选择

Ctrl+F：查找内容

Ctrl+H：替换内容

Ctrl+N：新建窗口

Ctrl+/：注释

Ctrl+Shift+K：删除整行

Tab：向右缩进

Shift+Tab：向左缩进

Ctrl+Z：撤销

Ctrl+Y：恢复撤销

Ctrl+Tab：按文件浏览过的顺序，切换当前窗口的标签页

alt+-：退回上一个光标的位置

alt+shift+-：前进下一个光标的位置

Ctrl+P：搜索框

输入当前项目中的文件名，快速搜索文件

输入 `@` 和关键字，查找文件中函数名

输入 `:` 和数字，跳转到文件中该行代码

输入 `#` 和关键字，查找变量名

# 设置背景图片

我们先下载 `Sublime Text Background Image.7z` 并解压。

在 `Sublime Text Background Image` 目录下打开 `cmd`，输入 `gcc -v`，查看 `gcc` 版本号，请确保你的 `gcc` 版本在 `13.0.0` 以上。

![](https://inf-512.github.io/other/sublime_text_setting/p32.png)

输入 `make`，回车，等待编译完成。

![](https://inf-512.github.io/other/sublime_text_setting/p33.png)

然后运行 `test.exe`。

![](https://inf-512.github.io/other/sublime_text_setting/p34.png)

成功设置好背景图片。

如果你的图片错位了，可以把 test.cpp 第 21 行的 1.5 改为 1.0，然后重新编译。

这里的 1.5 跟系统>屏幕>缩放和布局的缩放有关，例如这里我的电脑的缩放是 150%。

![](https://inf-512.github.io/other/sublime_text_setting/p36.png)

## 小提示

1. 程序只需要启动一次，除非闪退才需要重启。

2. 可以往 `imgs` 文件夹内加入新的图片，注意图片路径不能有中文。 

3. 如果图片太大，加载速度会严重变慢。

4. 左右方向键可以切换图片。

5. 如果不想看到控制台，可以在编译选项后面加上 `-mwindows`。

6. 如果发现 `bug` 请不要私信我~~（写完这篇文章，我已经累坏了）~~。

最后，送给大家一只可爱的心海。

![](https://inf-512.github.io/other/sublime_text_setting/p35.jpg)
