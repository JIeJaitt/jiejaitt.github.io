s=input()
st=""
for i in s:
    if(i=='#'):
        break
    st=st+i
t=""
flag=0
f=0
sum=0
for i in st:
    if(i=='-' and flag==0):
        f=1
    if(i>='0' and i<='9')or(i>='a' and i<='f')or(i>='A' and i<='F'):
        t=t+i
        flag=1
if(f):
    for i in t:
        if (i >= '0' and i <= '9'):
            sum = sum * 16 + ord(i) - 48
        elif (i >= 'a' and i <= 'f'):
            sum=sum * 16+ord(i)-87
        elif (i>= 'A' and i <= 'F'):
            sum=sum * 16+ord(i)-55
    print(sum*-1)
else:
    for i in t:
        if (i >= '0' and i <= '9'):
            sum = sum * 16 + ord(i) - 48
        elif (i >= 'a' and i <= 'f'):
            sum=sum * 16+ord(i)-87
        elif (i>= 'A' and i <= 'F'):
            sum=sum * 16+ord(i)-55
    print(sum)
