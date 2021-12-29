a,b=input().split(",")
# Python strip() 方法用于移除字符串头尾指定的字符（默认为空格或换行符）或字符序列
# str.strip([chars])  chars -- 移除字符串头尾指定的字符序列
# 返回移除字符串头尾指定的字符生成的新字符串
# 目的是为了去除题目中的空格字符
c,d=a.strip(),b.strip()
print(c,d)
f=int(d)
n=int(c[0]*f)
print(n)