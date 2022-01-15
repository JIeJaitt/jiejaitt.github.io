a=int(input())
sum=0
x=-1
for i in range(1,a+1):
	x+=2
	sum+=1/x
print("sum = {:.6f}".format(sum))