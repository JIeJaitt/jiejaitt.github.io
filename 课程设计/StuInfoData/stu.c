#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "common.h"
#include "stu.h"

//初始化
void init(){
	STU stu;
	NODE *preNode = NULL, *thisNode = NULL;

	//打开文件
	if( (fp=fopen(FILENAME, "rb+")) == NULL && (fp=fopen(FILENAME, "wb+")) == NULL ){
		pause("Error on open %s file!", FILENAME);
		exit(EXIT_FAILURE);
	}

	if(getFileSize(fp)){  //如果文件中有数据，那么创建链表
		while(fread(&stu, 1, sizeof(STU), fp)){
			thisNode = (NODE*)malloc(sizeof(NODE));
			thisNode->data = stu;
			thisNode->next = NULL;
			if(preNode==NULL){  //链表第一个节点
				header.link = thisNode;
			}else{  //不是第一个节点
				preNode->next = thisNode;
			}
			preNode = thisNode;
			header.num++;
		}
	}else{  //如果文件中没有数据，那么链表为空
		header.num = 0;
		header.link = NULL;
	}
}

//显示所有学生信息
void showAllStu(){
	STU thisStu;
	NODE *thisNode;
	float mathTotal = 0, cnTotal = 0, enTotal = 0, ageTotal = 0, oneTotal = 0, allTotal = 0;
	int manTotal = 0, womanTotal = 0, n = header.num;

	if(!header.num){
		pause("还未添加任何学生信息，按任意键返回...");
		return;
	}
	system("cls");
	printf("-----------------------------------------------------------------------\n");
	printf("  学号  |  姓名  |  性别  |  年龄  |  数学  |  语文  |  英语  | 总成绩\n");
	printf("--------+--------+--------+--------+--------+--------+--------+--------\n");

	for(thisNode=header.link; thisNode!=NULL; thisNode=thisNode->next){
		thisStu = thisNode->data;
		oneTotal = thisStu.math + thisStu.cn + thisStu.en;
		allTotal += oneTotal;
		mathTotal += thisStu.math;
		cnTotal += thisStu.cn;
		enTotal += thisStu.en;
		ageTotal += thisStu.age;
		if(strcmp(thisStu.sex, "男")){
			womanTotal++;
		}else{
			manTotal++;
		}
		printf("   %.2d   | %-6s |   %-3s  |   %-3d  | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", thisStu.id, thisStu.name, thisStu.sex, thisStu.age, thisStu.math, thisStu.cn, thisStu.en, oneTotal);
	}
	printf("--------+--------+--------+--------+--------+--------+--------+--------\n");
	printf("   --   |   --   | %2d/%-2d  | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", manTotal, womanTotal, ageTotal/n, mathTotal/n, cnTotal/n, enTotal/n, allTotal/n);
	printf("-----------------------------------------------------------------------\n");
	pause("\n共有%d条学生信息，按任意键返回...", n);
}

//添加学生信息
void addStuInfo(){
	STU stu;
	int id, isStuExist = 0;
	NODE *thisNode, *pnode = (NODE*)malloc(sizeof(NODE));
	getStuID(&stu.id);
	id = stu.id;

	if(header.num == 0){  //如果链表为空，直接插入
		header.link = pnode;
		pnode->next = NULL;
	}else{  //如果链表不为空，需要遍历链表确定插入位置
		for(thisNode=header.link; thisNode!=NULL; thisNode=thisNode->next){
			if(thisNode->data.id == id){  //该学生信息存在
				free(pnode);
				isStuExist = 1;
			}

			if(thisNode==header.link && thisNode->data.id>id){  //如果需要在链表开头插入（也就是在头结点和第一个节点之间插入）
				header.link = pnode;
				pnode->next = thisNode;
				break;
			}else if(thisNode->next==NULL && thisNode->data.id<id){  //如果需要在链表末尾插入
				thisNode->next = pnode;
				pnode->next = NULL;
				break;
			}else if(thisNode->data.id<id && thisNode->next->data.id>id ){  //在链表中间插入
				pnode->next = thisNode->next;
				thisNode->next = pnode;
				break;
			}
		}
	}

	if(isStuExist){  //该学生存在
		pause("错误：该学生信息已存在，无需重复添加！按任意键返回...");
	}else{  //该学生不存在
		getStuName(stu.name);
		getStuSex(stu.sex);
		getStuAge(&stu.age);
		getStuMath(&stu.math);
		getStuCN(&stu.cn);
		getStuEN(&stu.en);
		pnode->data = stu;
		updateFile();
		header.num++;
		pause("提示：添加成功！按任意键返回...");
	}
}

//删除学生信息
void deleteStuInfo(){
	STU stu;
	NODE *thisNode, *preNode;
	getStuID(&stu.id);

	for(thisNode=header.link, preNode=NULL; thisNode!=NULL; preNode=thisNode, thisNode=thisNode->next){
		if(thisNode->data.id == stu.id){
			if(preNode == NULL){  //如果是第一个节点
				header.link = thisNode->next;
			}else{  //如果不是第一个节点
				preNode->next = thisNode->next;
			}
			free(thisNode);
			updateFile();
			header.num--;
			pause("提示：删除成功，按任意键返回...");
			return;
		}else if(thisNode->data.id > stu.id){
			break;
		}
	}

	pause("错误：该学生信息不存在，删除失败！按任意键返回...");	
}

//修改学生信息
void alterStuInfo(){
	STU stu;
	NODE *thisNode;
	getStuID(&stu.id);

	for(thisNode=header.link; thisNode!=NULL; thisNode=thisNode->next){
		if(thisNode->data.id == stu.id){
			getStuName(stu.name);
			getStuSex(stu.sex);
			getStuAge(&stu.age);
			getStuMath(&stu.math);
			getStuCN(&stu.cn);
			getStuEN(&stu.en);
			thisNode->data = stu;
			updateFile();
			pause("提示：修改成功，按任意键返回...");
			return;
		}else if(thisNode->data.id > stu.id){
			break;
		}
	}

	pause("错误：该学生信息不存在，修改失败！按任意键返回...");	
}

//根据学号查询
void findStuByID(){
	STU stu;
	NODE *thisNode, *pnode = NULL;
	float total = 0;
	getStuID(&stu.id);

	for(thisNode=header.link; thisNode!=NULL; thisNode=thisNode->next){
		if(thisNode->data.id == stu.id){
			pnode = thisNode;
			break;
		}else if(thisNode->data.id > stu.id){
			break;
		}
	}

	if(pnode==NULL){
		pause("错误：该学生信息不存在，查询失败！按任意键返回...");
	}else{
		stu = pnode->data;
		total = stu.math + stu.cn + stu.en;
		printf("-----------------------------------------------------------------------\n");
		printf("  学号  |  姓名  |  性别  |  年龄  |  数学  |  语文  |  英语  | 总成绩\n");
		printf("--------+--------+--------+--------+--------+--------+--------+--------\n");
		printf("   %.2d   | %-6s |   %-3s  |   %-3d  | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", stu.id, stu.name, stu.sex, stu.age, stu.math, stu.cn, stu.en, total);
		printf("-----------------------------------------------------------------------\n");
		pause("\n按任意键返回...");
	}
}

//根据姓名查询学生信息
void findStuByName(){
	STU stu;
	NODE *thisNode = NULL;
	int n = 0;  //匹配到几条学生记录
	float total;
	char name[20];
	getStuName(name);

	for(thisNode=header.link; thisNode!=NULL; thisNode=thisNode->next){
		stu = thisNode->data;
		if(strstr(stu.name, name)){
			n++;
			total = stu.math + stu.cn + stu.en;
			if(n==1){
				printf("-----------------------------------------------------------------------\n");
				printf("  学号  |  姓名  |  性别  |  年龄  |  数学  |  语文  |  英语  | 总成绩\n");
				printf("--------+--------+--------+--------+--------+--------+--------+--------\n");
			}
			printf("   %.2d   | %-6s |   %-3s  |   %-3d  | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", stu.id, stu.name, stu.sex, stu.age, stu.math, stu.cn, stu.en, total);
		}
	}

	if(n>0){
		printf("-----------------------------------------------------------------------\n");
		pause("\n共查询到%d条记录。按任意键返回...", n);
	}else{
		pause("错误：没有查询到相关记录！按任意键返回...");
	}
}

//根据成绩查询学生信息
void findStuByScores(int flag){
	STU stu;
	int n = 0;  //匹配到几条学生记录
	float *scores = NULL;  //当前学生的成绩
	float min = 0, max = 0;  //用户输入的最高分和最低分
	int MAX = 0;  //common.h 中指定的成绩最高分
	char *courseName = NULL;  //科目名称
	float total = 0;  //当前学生总分
	NODE *thisNode = NULL;

	if(flag == FIND_BY_MATH){
		courseName = "数学成绩";
		MAX = MAX_STU_MATH;
		scores = &stu.math;
	}else if(flag == FIND_BY_CN){
		courseName = "语文成绩";
		MAX = MAX_STU_CN;
		scores = &stu.cn;
	}else if(flag == FIND_BY_EN){
		courseName = "英语成绩";
		MAX = MAX_STU_EN;
		scores = &stu.en;
	}else if(flag == FIND_BY_TOTAL){
		courseName = "总成绩";
		MAX = MAX_STU_MATH + MAX_STU_CN + MAX_STU_EN;
		scores = &total;
	}else{
		return;
	}

	while(1){
		printf("要查询的%s的范围：", courseName);
		fflush(stdin);
		scanf("%f %f", &min, &max);
		if(min<0 || min>MAX || max<0 || max>MAX){
			pause("错误：%s的取值范围为0~%d！按任意键重新输入...", courseName, MAX);
			continue;
		}
		if(min>max){
			pause("错误：最高分要高于最低分！按任意键重新输入...");
			continue;
		}
		break;
	}

	for(thisNode=header.link; thisNode!=NULL; thisNode=thisNode->next){
		stu = thisNode->data;
		total = stu.math + stu.cn + stu.en;
		if(min <= *scores && *scores <= max){
			n++;
			if(n==1){
				printf("-----------------------------------------------------------------------\n");
				printf("  学号  |  姓名  |  性别  |  年龄  |  数学  |  语文  |  英语  | 总成绩\n");
				printf("--------+--------+--------+--------+--------+--------+--------+--------\n");
			}
			printf("   %.2d   | %-6s |   %-3s  |   %-3d  | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", stu.id, stu.name, stu.sex, stu.age, stu.math, stu.cn, stu.en, total);
		}
	}

	if(n>0){
		printf("-----------------------------------------------------------------------\n");
		pause("\n共查询到%d条记录。按任意键返回...", n);
	}else{
		pause("错误：没有查询到相关记录！按任意键返回...");
	}
}

//更新文件
void updateFile(){
	NODE *thisNode;
	freopen(FILENAME, "wb+", fp );  //重新打开文件并清空文件中的数据
	for(thisNode=header.link; thisNode!=NULL; thisNode=thisNode->next){
		fwrite(&(thisNode->data), sizeof(STU), 1, fp);
	}
	fflush(fp);
}

//输入学生ID
void getStuID(int *id){
	while(1){
		printf("输入学号：");
		fflush(stdin);
		scanf("%d", id);
		if(checkStuID(*id)){
			break;
		}
	}
}

//输入学生姓名
void getStuName(char name[]){
	while(1){
		printf("输入姓名：");
		fflush(stdin);
		scanf("%s", name);
		if(checkStuName(name)){
			break;
		}
	}
}

//输入学生性别
void getStuSex(char sex[]){
	while(1){
		printf("输入性别：");
		fflush(stdin);
		scanf("%s", sex);
		if(checkStuSex(sex)){
			break;
		}
	}
}

//输入学生年龄
void getStuAge(int *age){
	while(1){
		printf("输入年龄：");
		fflush(stdin);
		scanf("%d", age);
		if(checkStuAge(*age)){
			break;
		}
	}
}

//输入数学成绩
void getStuMath(float *math){
	while(1){
		printf("数学成绩：");
		fflush(stdin);
		scanf("%f", math);
		if(checkStuMath(*math)){
			break;
		}
	}
}

//输入语文成绩
void getStuCN(float *cn){
	while(1){
		printf("语文成绩：");
		fflush(stdin);
		scanf("%f", cn);
		if(checkStuCN(*cn)){
			break;
		}
	}
}

//输入英语成绩
void getStuEN(float *en){
	while(1){
		printf("英语成绩：");
		fflush(stdin);
		scanf("%f", en);
		if(checkStuEN(*en)){
			break;
		}
	}
}

//检查学生ID是否正确
int checkStuID(int stuID){
	if(stuID <= 0 || stuID > MAX_STU_ID){
		printf("错误：学号必须是大于0且小于等于%d的整数！\n", MAX_STU_ID);
		return 0;
	}
	return 1;
}

//检查学生姓名是否正确
int checkStuName(char name[]){
	if(strlen(name) > MAX_STU_NAME){
		printf("错误：名字的最大长度不超过%d个字节！\n", MAX_STU_NAME);
		return 0;
	}
	return 1;
}

//检查学生性别是否正确
int checkStuSex(char sex[]){
	if(strcmp(sex, "男") && strcmp(sex, "女")){
		printf("错误：性别只能是男或女！\n");
		return 0;
	}else{
		return 1;
	}
}

//检查学生年龄是否正确
int checkStuAge(int age){
	if(age <=0 || age > MAX_STU_AGE){
		printf("错误：年龄的取值范围为1~%d！\n", MAX_STU_AGE);
		return 0;
	}
	return 1;
}

//检查数学成绩是否正确
int checkStuMath(float math){
	if(math < 0 || math > MAX_STU_MATH){
		printf("错误：数学成绩的取值范围为0~%d！\n", MAX_STU_MATH);
		return 0;
	}
	return 1;
}

//检查语文成绩是否正确
int checkStuCN(float cn){
	if(cn < 0 || cn > MAX_STU_CN){
		printf("错误：语文成绩的取值范围为0~%d！\n", MAX_STU_CN);
		return 0;
	}
	return 1;
}

//检查英语成绩是否正确
int checkStuEN(float en){
	if(en < 0 || en > MAX_STU_EN){
		printf("错误：英语成绩的取值范围为0~%d！\n", MAX_STU_EN);
		return 0;
	}
	return 1;
}