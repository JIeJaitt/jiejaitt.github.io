a=input()
cnt=0
for i in a:
	if i.isupper() and i!="A" and i!="E" and i!="I" and i!="O" and i!="U":
		cnt+=1
print(cnt)