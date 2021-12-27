#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student
{
    char name[20];//名字
    char wm[20];//性别
    char work[100];//工作单位
    char stel[20];//手机
    char htel[20];//住宅号码
    char mail[20];//E-Mail
    char home[100];//家庭住址
    struct student *next;
}stu;
stu *head;//头指针

void screen()//主菜单
{
    printf("\n=======================================================\n");
    printf("              欢迎来到通讯录管理系统\n\n");
    printf("            1.输入数据         2.显示数据\n");
    printf("            3.插入数据         4.删除数据\n");
    printf("            5.查看数据         6.修改数据\n");
    printf("            7.保存数据         8.返回主菜单\n");
    printf("\n~~~~~~输~~~~~~入~~~~~~9~~~~~~退~~~~~~出~~~~~~程~~~~~~序\n");
}
void input()//输入数据
{
    int ans;//判断是否继续输入
    stu *p1,*p2;
    p1=(stu *)malloc(sizeof(stu));//申请内存来用
    if(p1!=NULL)
    {
        printf("========输入数据========\n");
        head=p1;
        while(1)
        {
            printf("名字:");
            scanf("%s",&p1->name);
            printf("性别:");
            scanf("%s",&p1->wm);
            printf("工作单位:");
            scanf("%s",&p1->work);
            printf("手机:");
            scanf("%s",&p1->stel);
            printf("住宅号码:");
            scanf("%s",&p1->htel);
            printf("E-Mail:");
            scanf("%s",&p1->mail);
            printf("家庭地址:");
            scanf("%s",&p1->home);
            printf("===================================\n");
            p2=p1;
            p1=(stu *)malloc(sizeof(stu));//申请下一个要用的空间
            if(p1!=NULL)
                p2->next=p1;
            printf("请选择是否继续输入:1.继续  2.退出\n请选择:");//用户选择
            scanf("%d",&ans);
            if(ans==1)//继续
                continue;
            else//退出
            {
                printf("========输入完毕========\n");
                p2->next=NULL;
                free(p1);//将申请的的无用内存释放
                break;
            }
        }
    }
}
void look(stu *p1)//显示数据
{
    printf("========显示数据========\n");
    while(p1!=NULL)
    {
        printf("名字：%s\n",p1->name);
        printf("性别：%s\t",p1->wm);
        printf("工作单位：%s\t",p1->work);
        printf("手机：%s\t",p1->stel);
        printf("住宅号码：%s\t",p1->htel);
        printf("E-Mail：%s\t",p1->mail);
        printf("家庭住址：%s\n",p1->home);
        printf("=====================================\n");
        p1=p1->next;
    }
    printf("========显示完毕========\n");
}
void insert()//插入数据
{
    int ans;//选择插入位置
    char name[20];//插入者的名字
    printf("========插入数据========\n");
    stu *p1,*p2,*p3;
    p1=head;
    p3=(stu *)malloc(sizeof(stu));//申请内存
    p3->next=NULL;
    printf("请输入插入者的数据:\n");
    printf("名字:");
    scanf("%s",&p3->name);
    printf("性别:");
    scanf("%s",&p3->wm);
    printf("工作单位:");
    scanf("%s",&p3->work);
    printf("手机:");
    scanf("%s",&p3->stel);
    printf("住宅号码:");
    scanf("%s",&p3->htel);
    printf("E-Mail:");
    scanf("%s",&p3->mail);
    printf("家庭地址:");
    scanf("%s",&p3->home);
    printf("请选择插入位置:1.首位置插入  2.尾部插入  3.插到某人前面\n请选择:");
    scanf("%d",&ans);
    switch(ans)
    {
    case 1://放到头指针
        p3->next=p1;
        head=p3;
        break;
    case 2://放到尾部
        while(p1->next!=NULL)
            p1=p1->next;
        p1->next=p3;
        break;
    case 3://放到某人前面
        printf("请输入插到谁前面名字:");
        scanf("%s",name);
        while(strcmp(name,p1->name)!=0)
        {
            p2=p1;
            p1=p1->next;
        }
        p2->next=p3;
        p3->next=p1;
        break;
    }
    printf("========插入成功========\n");
}
void deleted()//删除数据
{
    stu *p1,*p2;
    char name[20];//删除者名字
    printf("========删除数据========\n");
    printf("请输入要删除者的名字:");
    scanf("%s",name);
    p1=head;
    if(head==NULL)//通讯录已经没数据了
    {
        printf("通讯录里什么也没有了。\n");
        printf("========删除失败========\n");
        return;
    }
    if(!strcmp(name,p1->name))//头指针就是要删除的，为什么要单独拿出来，就是为了可以在删除后改变头指针
    {
        head=p1->next;
        printf("========删除成功========\n");
        return;
    }
    while(p1!=NULL&&strcmp(name,p1->name))
    {
        p2=p1;
        p1=p1->next;
    }
    if(p1==NULL)//查找完了，没找到
    {
        printf("查无此人!!!!\n");
        printf("========删除失败========\n");
        return;
    }
    if(p1->next!=NULL)//找到了，不是最后一个
    {
        p1=p1->next;
        p2->next=p1;
        printf("========删除成功========\n");
    }
    else//是最后一个
    {
        p2->next=NULL;
        printf("========删除成功========\n");
    }
}
void find(stu *p1)//查找数据
{
    char name[20];//查找的名字
    printf("========查看数据========\n");
    printf("请输入要查看人的名字：");
    scanf("%s",name);
    while(p1!=NULL)
    {
        if(!strcmp(name,p1->name))//找到了输出
        {
            printf("你要查找人的数据：\n");
            printf("名字：%s\n",p1->name);
            printf("性别：%s\t",p1->wm);
            printf("工作单位：%s\t",p1->work);
            printf("手机：%s\t",p1->stel);
            printf("住宅号码：%s\t",p1->htel);
            printf("E-Mail：%s\t",p1->mail);
            printf("家庭住址：%s\n",p1->home);
            break;
        }
        p1=p1->next;
    }
    if(p1==NULL)//找完了，没找到
        printf("您要查找的人不存在\n");
    printf("========结束查找========\n");
}
void update(stu *p1)//修改数据
{
    int n;//选择的修改内容
    char name[20];//要修改人的名字
    printf("========修改数据========\n");
    printf("请输入要修改人的姓名:");
    scanf("%s",name);
    while(p1!=NULL)
    {
        if(!strcmp(name,p1->name))//找到了
        {
            printf("要修改人的数据为:\n");
            printf("名字:%s\n",p1->name);
            printf("性别：%s\t",p1->wm);
            printf("工作单位：%s\t",p1->work);
            printf("手机：%s\t",p1->stel);
            printf("住宅号码：%s\t",p1->htel);
            printf("E-Mail：%s\t",p1->mail);
            printf("家庭住址：%s\n",p1->home);
            printf("请选择要修改的信息：");
            printf("\t1.名字\t2.性别\t3.工作单位\t4.手机\t5.住宅号码\t6.E-Mail\t7.家庭住址\n\n您的选择是（1~7）：");
            scanf("%d",&n);
            switch(n)
            {
                case 1:
                    printf("名字：");
                    scanf("%s",&p1->name);
                    break;
                case 2:
                    printf("性别：");
                    scanf("%s",&p1->wm);
                    break;
                case 3:
                    printf("工作单位：");
                    scanf("%s",&p1->work);
                    break;
                case 4:
                    printf("手机：");
                    scanf("%s",&p1->stel);
                    break;
                case 5:
                    printf("住宅号码：");
                    scanf("%s",&p1->htel);
                    break;
                case 6:
                    printf("E-Mail：");
                    scanf("%s",&p1->mail);
                    break;
                case 7:
                    printf("家庭住址：");
                    scanf("%s",&p1->home);
                    break;
            }
            printf("========修改成功========\n");
            break;
        }
        p1=p1->next;
    }
    if(p1==NULL)//找完了，没有找到
    {
        printf("没有找到该人信息\n");
        printf("========修改失败========\n");
    }
}
void save(stu *p1)//保存数据
{
    printf("========保存数据========\n");
    FILE *fp;
    char file[15];
    printf("请输入文件名：");
    scanf("%s",file);
    if((fp=fopen(file,"w"))==NULL)//打开文件，若没有此文件可以新建立
    {
        printf("cannot open this file\n");//无法建立新文件
        exit(0);//正常运行程序并退出程序
    }
    fprintf(fp,"名字\t性别\t工作单位\t手机\t住宅号码\tE-Mail\t家庭住址\n");
    while(p1!=NULL)
    {
        fprintf(fp,"%s\t",p1->name);
        fprintf(fp,"%s\t",p1->wm);
        fprintf(fp,"%s\t",p1->work);
        fprintf(fp,"%s\t",p1->stel);
        fprintf(fp,"%s\t",p1->htel);
        fprintf(fp,"%s\t",p1->mail);
        fprintf(fp,"%s\n",p1->home);
        p1=p1->next;
    }
    printf("========保存成功========\n");
    fclose(fp);//关闭文件，这个要记得
}



int main()
{
    int n;
    screen();
    while(1)
    {
        printf("请输入你的选择(1~9):");
        scanf("%d",&n);
        if(n<1||n>9)
        {
            printf("输入有误！");
            continue;
        }
        switch(n)
        {
        case 1:
            input();
            break;
        case 2:
            look(head);
            break;
        case 3:
            insert();
            break;
        case 4:
            deleted();
            break;
        case 5:
            find(head);
            break;
        case 6:
            update(head);
            break;
        case 7:
            save(head);
            break;
        case 8:
            screen();
            break;
        case 9:
            printf("===============欢迎你再次使用通讯录系统===============\n");
            // exit(1);
            exit(0);
            break;
        }
    }
}