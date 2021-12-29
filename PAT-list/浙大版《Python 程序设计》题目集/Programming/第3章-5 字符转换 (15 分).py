a = input()
b=[]
for i in a:
	if i.isdigit():
		b.append(i)
# Python join() 方法用于将序列中的元素以指定的字符连接生成一个新的字符串
print(int("".join(b)))