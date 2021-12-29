a,b=input().split()
a,b=eval(a),eval(b)
cnt=0
sum=0
for i in range(a,b+1):
	print("{:>5d}".format(i),end="")
	cnt+=1
	sum+=i
	if cnt==5:
		print("\n",end="")
		cnt=0
	elif i==b:
		print("\n",end="")
print("Sum = {:d}".format(sum))