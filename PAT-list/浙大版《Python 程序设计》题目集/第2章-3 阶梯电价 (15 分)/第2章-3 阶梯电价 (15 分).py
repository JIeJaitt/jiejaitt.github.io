a=int(input())
if a<0:
	print("Invalid Value!")
elif a<50:
	cost=a*0.53
	print("cost = {:.2f}".format(cost))
else:
	cost=50*0.53+(a-50)*0.58
	print("cost = {:.2f}".format(cost))