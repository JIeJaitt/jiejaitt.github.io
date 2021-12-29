s=input()
m,n=input().split()
# 逆序字符串
s=s[::-1]
for i in range(0,len(s)):
	if n==s[i] or m==s[i]:
		print("{:d} {:s}".format(len(s)-i-1,s[i]))
		