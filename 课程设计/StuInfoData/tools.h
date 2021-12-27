#ifndef _TOOLS_H
#define _TOOLS_H

#include "common.h"

extern long getFileSize(FILE *fp);  //获取文件大小（以字节计）
extern void pause(const char *str, ...);  //暂停程序

#endif