a=input()
b=input()

if b.find(a)!=-1:
	b=b[::-1]
	print("index = {:d}".format(len(b)-b.find(a)-1))
else:
	print("Not Found")
	
# 反向查询
# a, b = input(), input()
# print("index =", b.rfind(a)) if b.rfind(a) != -1 else print('Not Found')
	