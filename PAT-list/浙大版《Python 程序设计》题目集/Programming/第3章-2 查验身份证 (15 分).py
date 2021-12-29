def judge(mlist,jlist,flist):
	sum=0
	x=0
	lnum=mlist[-1]
	mlist=mlist[:17]
	
	for i in mlist:
		if i>='0' and i<='9':
			sum+=int(i) * flist[x]
		else:
			return False
	re=sum%11
	if jlist[re]==lnum:
		return True
	else:
		return False

# mlist 输入的身份证 jlist 判断字符 flist 权重列表
num=int(input())
cnt=0
jlist = ['1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2']
flist = [7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2]
for i in range(num):
	mlist = input()
	if judge(mlist,jlist,flist)==False:
		print(mlist)
	else:
		cnt+=1
if cnt==num:
	print("All passed")