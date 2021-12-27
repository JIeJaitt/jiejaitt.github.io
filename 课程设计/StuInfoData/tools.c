#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdarg.h>
#include "tools.h"

//获取文件大小（以字节计）
long getFileSize(FILE *fp){
	long fsize;
	fpos_t fpos;  //当前位置
	fgetpos(fp, &fpos);  //获取当前位置
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fsetpos(fp,&fpos);  //恢复之前的位置

	return fsize;
}

/**
 * 暂停程序
 * @param  str  程序暂停时显示的字符串，可以包含格式控制符
 * @param  ...  变长参数
**/
void pause(const char *str, ...){
	va_list vl;
	char buf[500] = {0};
	va_start(vl, str);
	vsnprintf(buf, 500, str, vl);
	va_end(vl);
	printf(buf);
	getch();
	printf("\n");
}