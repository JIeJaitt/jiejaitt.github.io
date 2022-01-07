    #黑白互换
    def change_color(self) :
        self.color_count = (self.color_count + 1 ) % 2
        if self.color_count == 0 :
            self.color = "black"
        elif self.color_count ==1 :
            self.color = "white"