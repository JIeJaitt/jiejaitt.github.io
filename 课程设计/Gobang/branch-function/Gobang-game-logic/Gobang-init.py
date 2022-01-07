    def __init__(self) :
        self.board = chessBoard()
        self.game_print = StringVar()
        self.game_print.set("")
        
        # 16*16的二维列表，保证不会out of index
        self.db = [([2] * 16) for i in range(16)]
        # 悔棋用的顺序列表
        self.order = []
        # 棋子颜色
        self.color_count = 0 
        self.color = 'black'
        # 清空与赢的初始化，已赢为1，已清空为1
        self.flag_win = 1
        self.flag_empty = 1
        self.options()