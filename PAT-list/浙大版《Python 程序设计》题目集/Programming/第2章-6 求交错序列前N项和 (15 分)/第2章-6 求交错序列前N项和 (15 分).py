a=int(input())
sum=0
x=0
y=-1
flag=1
for i in range(1,a+1):
	x+=1
	y+=2
	sum+=x/y*flag
	flag=-flag
print("{:.3f}".format(sum))