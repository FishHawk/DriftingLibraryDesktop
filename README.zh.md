# 漂流图书馆桌面端

一个用于管理你的漫画库的软件。

## 如何使用

库目录下的一个子文件夹就是一部漫画，包括漫画图片和相关信息。文件夹名是漫画的标题。漫画文件夹中的结构如下所示（漫画图片文件未列出）：

```
BLAME!
├── content.json
├── tags.json
├── thumb.jpg
├── 单行本
│   ├── 第10卷
│   ├── 第1卷
│   ├── 第2卷
│   ├── 第3卷
│   ├── 第4卷
│   ├── 第5卷
│   ├── 第6卷
│   ├── 第7卷
│   ├── 第8卷
│   └── 第9卷
└── 画集
    └── BLAME! and so on

```

`content.json`和`tags.json`是自动生成的。可以直接编辑`content.json`来调整漫画章节的顺序，编辑`tags.json`来管理漫画的meta信息。`thumb.jpg`是漫画在库中显示的封面。

`tags.json`的格式如下，其中颜色名称参见[color QML Basic Type](https://doc.qt.io/qt-5/qml-color.html)：

```json
{
    "tags": [
        {
            "key": "artist",
            "value": ["弐瓶勉"],
            "color": "deepskyblue"
        },
        {
            "key": "status",
            "value": ["已完结"],
            "color": "orange"
        }
    ]
}
```
