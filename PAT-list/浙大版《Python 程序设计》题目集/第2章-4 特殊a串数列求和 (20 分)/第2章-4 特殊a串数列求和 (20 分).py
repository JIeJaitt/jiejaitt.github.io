a,b=input().split()
a,b=eval(a),eval(b)
sum=0
tmp=0
for i in range(1,b+1):
	tmp=tmp*10+a
	sum+=tmp
print("s = {:d}".format(sum))