n=int(input())
lst=list(map(int,input().split()))

max=lst[0]
maxi=0
for i in range(1,n):
	if lst[i]>max:
		maxi=i
		max=lst[i]
print("{:d} {:d}".format(lst[maxi],maxi))

# a = int(input())
# b = list(map(int,input().split()))
# print(max(b), b.index(max(b)))