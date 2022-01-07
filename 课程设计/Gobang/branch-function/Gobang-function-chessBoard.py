# 定义棋盘类
class chessBoard() :    
    def __init__(self) :
        # 定义窗口对象
        self.window = Tk()
        # 定义窗口命名
        self.window.title("五子棋课程设计答辩演示程序")
        # 定义窗口尺寸    
        self.window.geometry("660x470")
        # 定义窗口不可放缩
        self.window.resizable(0,0)
        # 定义窗口里的画布属性
        self.canvas=Canvas(self.window , bg="#EEE8AC" , width=470, height=470)
        # 画出画布内容
        self.paint_board()
        # 定义画布所在网络
        self.canvas.grid(row = 0 , column = 0)

    def paint_board(self) :
        # 画出横线
        for row in range(0,15) :
            if row == 0 or row == 14 :
                self.canvas.create_line(25 , 25+row*30 , 25+14*30 , 25+row*30 , width = 2)
            else :
                self.canvas.create_line(25 , 25+row*30 , 25+14*30 , 25+row*30 , width = 1)
        # 画出竖线
        for column in range(0,15) :
            if column == 0 or column == 14 :
                self.canvas.create_line(25+column*30 ,25, 25+column*30 , 25+14*30 ,width = 2)
            else :
                self.canvas.create_line(25+column*30 ,25, 25+column*30 , 25+14*30 , width = 1)
        # 画出圆    
        self.canvas.create_oval(112, 112, 118, 118, fill="black")
        self.canvas.create_oval(352, 112, 358, 118, fill="black")
        self.canvas.create_oval(112, 352, 118, 358, fill="black")
        self.canvas.create_oval(232, 232, 238, 238, fill="black")
        self.canvas.create_oval(352, 352, 358, 358, fill="black")