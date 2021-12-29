l=list(map(int,input().split()))
sum=0
for i in range(0,len(l)):
	sum+=l[i]
aver=sum/len(l)
for i in range(0,len(l)):
	if l[i]>aver:
		print("{:d}".format(l[i]),end= " ")