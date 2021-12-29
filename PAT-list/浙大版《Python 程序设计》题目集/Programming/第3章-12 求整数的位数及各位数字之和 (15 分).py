a=input()
sum=0
for i in range(len(a)):
	sum+=int(a[i])
print("{:d} {:d}".format(len(a),sum))