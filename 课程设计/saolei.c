#include<stdio.h>
#include<time.h>
#include<windows.h>
#define ROW 11
#define COL 11
#define DEFAULT 10//设定雷区数量
//扫雷初始化，mine数组负责记录数据，show数组负责显示讲数据显示给用户
void init_board(int mine[ROW][COL], char show[ROW][COL]);
//显示扫雷结果，即将show数组中的数据显示给用户，显示过程中调用了windows API，对显示界面做了优化
void display_board(char show[ROW][COL]);
//设置雷区，没有雷的区域用数字 0 表示，有雷区域用数字 -1 表示
void set_mine(int mine[ROW][COL]);
//在扫雷游戏中，当用户点击的某个区域不是雷区时，游戏应将与此位置相邻的所有不是雷区的区域显示给用户，即实现“一点显示一片”的功能，
void mine_deal(int mine[ROW][COL], int mineDow[ROW][COL]);
//统计该位置周围雷的个数
int get_mine(int mine[ROW][COL], int x, int y);
//扫雷过程实现函数
void mine_sweep(int mine[ROW][COL], int mineDow[ROW][COL], char show[ROW][COL]);
//扫雷游戏开始入口函数
void game();
//采用递归思想，更新显示数组 show 中的数据
void show_deal(char show[ROW][COL], int mine[ROW][COL], int x, int y);
//调用windows API 给字符赋予不同颜色
void color(int m);
int main()
{
	printf("****************扫雷游戏******************\n"
		"*                                           *\n"
		"*         -----------------------           *\n"
		"*   |    Powered By c.biancheng.net    |    *\n"
		"*         -----------------------           *\n"
		"*                                           *\n"
		"*         |       游戏规则       |          *\n"
		"*                                           *\n"
		"*            输入扫雷区域的坐标             *\n"
		"*        例如第一行第一列，输入 1 1         *\n"
		"*     扫出所有非雷区的区域，即为成功！      *\n"
		"*********************************************\n");
	srand((unsigned)time(NULL));//给随机数设置种子
	color(0xE);//给以下字符赋予淡黄色
	printf("是否开始游戏：（Y/N）\n");
	while (1)
	{
		char define;
		//根据用户输入的字符，设定游戏是否开始
		if ((define = getch()) == 'y' || (define = getch()) == 'Y') {
			system("cls");//清空命令行中显示的数据
			game();//游戏开始
		}
		else {
			break;
		}
		color(0xE);
		printf("是否重新开始游戏：(Y/N)\n");
	}
	return 0;
}
void init_board(int mine[ROW][COL], char show[ROW][COL])
{
	int i;
	int j;
	//初始状态下，mine数组中全部设置为不是雷区
	for (i = 0; i < ROW - 1; i++)
	{
		for (j = 0; j < COL - 1; j++)
		{
			mine[i][j] = 0;
		}
	}
	//初始状态下，用户没有点击任何一个区域，所以，show数组中全部设为 * ，表示用户没有点击的区域
	for (i = 0; i < ROW - 1; i++)
	{
		for (j = 0; j < COL - 1; j++)
		{
			show[i][j] = '*';
		}
	}
}
void display_board(char show[ROW][COL])
{
	//在显示给用户时，为了方便用户游戏，扫雷区域外需增设一个坐标系
	int i, j;
	printf("　 ");
	color(2);//横坐标系设为淡绿色
	for (i = 1; i < COL - 1; i++) {

		printf(" %d", i);//由于扫雷游戏，显示给用户所使用的所有字符都是特殊字符，每个特殊字符占用两个普通字符的位置
	}
	printf("\n");
	for (i = 1; i < ROW - 1; i++)
	{
		//每行的纵坐标系也设置为淡绿色
		color(2);
		printf("%d　", i);
		//根据 show 数组中存储的字符的不同，分别用不同的有意义的特殊字符代替
		for (j = 1; j < COL - 1; j++)
		{
			if (show[i][j] == '*') {
				color(8);
				printf("■");
			}
			if (show[i][j] == '0') {
				color(7);
				printf("■");
			}
			if (show[i][j] == '1') {
				color(0xA);
				printf("１");
			}
			if (show[i][j] == '2') {
				color(1);
				printf("２");
			}
			if (show[i][j] == '3') {
				color(3);
				printf("３");
			}
			if (show[i][j] == '4') {
				color(3);
				printf("４");
			}
			if (show[i][j] == '5') {
				color(3);
				printf("５");
			}
			if (show[i][j] == '6') {
				color(3);
				printf("６");
			}
			if (show[i][j] == '7') {
				color(3);
				printf("７");
			}
			if (show[i][j] == '8') {
				color(3);
				printf("８");
			}
			if (show[i][j] == 'o') {
				color(6);
				printf("●");
			}

		}
		printf("\n");
	}
}
int get_mine(int mine[ROW][COL], int x, int y)
{
	//计算横坐标为 x，纵坐标为 y的位置，周围的8个区域，雷的数量
	int count = 0;
	if (mine[x - 1][y - 1] == -1)
		count++;
	if (mine[x - 1][y] == -1)
		count++;
	if (mine[x - 1][y + 1] == -1)
		count++;
	if (mine[x][y - 1] == -1)
		count++;
	if (mine[x][y + 1] == -1)
		count++;
	if (mine[x + 1][y - 1] == -1)
		count++;
	if (mine[x + 1][y] == -1)
		count++;
	if (mine[x + 1][y + 1] == -1)
		count++;
	return count;
}
//初始化 mineDow数组，用于实现扫雷游戏中"点击一下出现一片安全区域"的功能。mineDow数组中存储的是各个位置周围雷区的个数
void mine_deal(int mine[ROW][COL], int mineDow[ROW][COL]) {
	int i;
	int j;

	for (i = 1; i<ROW - 1; i++) {
		for (j = 1; j<COL - 1; j++) {
			if (mine[i][j] != -1) {
				mineDow[i][j] = get_mine(mine, i, j);
			}
			else {
				mineDow[i][j] = -1;
			}
		}
	}

}
void set_mine(int mine[ROW][COL])
{
	int x = 0;
	int y = 0;
	int count = DEFAULT;
	//用随机数想mine数组中设置数量为 count 的雷区，mine数组中，雷区用 -1 表示
	while (count)
	{
		x = rand() % (ROW - 2) + 1;
		y = rand() % (COL - 2) + 1;
		if (mine[x][y] == 0)
		{
			mine[x][y] = -1;
			count--;
		}
	}
}

//根据mineDow数组中的数据，更新show数组。采用递归的方式，找出与（x，y）相邻的不是雷区的位置
void show_deal(char show[ROW][COL], int mine[ROW][COL], int x, int y) {
	//递归出口
	if (x == 0 || x == ROW - 1 || y == 0 || y == COL - 1) {
		return;
	}
	//如果show数组中的某个位置不是 *，说明该位置之前已经做过更新，无需再做一次。
	if (show[x][y] != '*') {
		return;
	}
	//更新show数组中的数据
	show[x][y] = mine[x][y] + '0';
	//扫雷游戏中，当遇到周围有雷区的位置时（位置上显示的为周围雷区的个数），即不再继续显示
	if (mine[x][y] != 0) {
		return;
	}
	show_deal(show, mine, x + 1, y);
	show_deal(show, mine, x - 1, y);
	show_deal(show, mine, x, y + 1);
	show_deal(show, mine, x, y - 1);
}
//判断用户是否完成游戏，采用时刻监控扫雷区域中 * 的个数，如果与设置的雷区数相等，证明用户扫雷成功
int countShow(char show[ROW][COL]) {
	int i, j,count=0;
	for (i = 1; i < ROW - 1; i++) {
		for (j = 1; j < COL - 1; j++) {
			if (show[i][j] == '*') {
				count++;
			}
		}
	}
	return count;
}
//实现扫雷的功能函数
void mine_sweep(int mine[ROW][COL],int mineDow[ROW][COL], char show[ROW][COL])
{
	int x = 0;
	int y = 0;
	int count = 0;
	//只要未知区域的个数比雷区的总数大，就继续
	while (countShow(show)> DEFAULT)
	{
		printf("请输入坐标ROW（1-9）COL（1-9）：");
		scanf("%d%d", &x, &y);
		//用户输入的x，y需在规定范围内，否则无效
		if (x >= 1 && x <= 9 && y >= 1 && y <= 9) {
			//输入的（x，y）每次都必须为位置区域。否则无效
			if (show[x][y] == '*') {
				//如果该位置为 -1，则是雷区，游戏结束
				if (mine[x][y] == -1)
				{
					//雷区在show数组中用 o 表示
					show[x][y] = 'o';
					//通过重设光标所在位置进行刷新，可有效避免屏幕闪烁
					COORD pos = { 0, 0 };
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

					display_board(show);
					printf("踩到雷了：");
					color(6);
					printf("●\n");

					return;
				}else{
					//更新数组show中的数据，看是否有相邻且不是雷区的区域。若有，全部显示给用户
					show_deal(show, mineDow, x, y);

					COORD pos = { 0, 0 };
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

					display_board(show);
				}
			}
		}
	}
	printf("扫雷成功\n");
}
void game()
{
	int  mine[ROW][COL] = { 0 };
	char show[ROW][COL] = { 0 };
	int mineDow[ROW][COL] = { 0 };
	init_board(mine, show);
	display_board(show);

	set_mine(mine);//设置地雷
	mine_deal(mine, mineDow);
	mine_sweep(mine,mineDow, show);
}
void color(int m) {
	HANDLE consolehend;
	consolehend = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consolehend, m);
}
