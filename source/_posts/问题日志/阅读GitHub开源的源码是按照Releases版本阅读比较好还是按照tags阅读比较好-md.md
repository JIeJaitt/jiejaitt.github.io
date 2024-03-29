---
title: 阅读GitHub开源的源码是按照Releases版本阅读比较好还是按照tags阅读比较好.md
categories: 问题日志
abbrlink: ff24ad46
toc: true
date: 2023-06-22 13:45:25
tags:
sticky:
---

按照Releases版本阅读通常比较好。

<!-- more -->

Releases版本指的是在GitHub仓库中发布的具体版本，通过在Releases页面查看可以找到与版本相关的说明文档、修复的bug等信息。每个Releases版本都会有相应的代码文件和可执行文件供下载和使用。Tags（标签）则是用于标记特定的提交点或版本号，例如v1.0.0或1.2.3，在仓库的提交历史中可以根据Tag找到对应的代码。通常，Tags用于对特定版本进行标记和查找。



在阅读开源源码时，按照Releases版本阅读可以更方便地查看和理解软件的发布历史、变更日志，同时可以使用对应版本的稳定代码进行实验和测试。通过查看Release页面中提供的文档和说明，可以更好地理解代码的用途和设计思想。

然而，在某些情况下，如果你对特定的代码提交点或版本感兴趣，可以选择按照Tags进行阅读。这适用于你想查看或比较不同版本之间的代码差异、修复的bug等情况。

总而言之，按照Releases版本阅读对于了解软件的发布历史和使用稳定的代码较为方便。而按照Tags阅读则更适合特定版本的代码以及版本比较的需求。

## github

在github的`Settings/Security/Secrets and variables`设置中可以设置某些不方便公开在仓库内的变量值，类似vercel的环境变量，需要把这些变量设置到secrets里，然后通过`$`引用。另外正确的语法是`${{ secrets.GITHUB_TOKEN }}`，不需要在末尾添加额外的$符号。`${{ secrets.GITHUB_TOKEN }}`是 GitHub Actions 中引用 GitHub 仓库密钥（GitHub Token）的正确方式。在您的工作流配置中。