a,b=input().split()
a,b=eval(a),eval(b)
sum=0
for i in range(a,b+1):
    sum=sum+i*i+1/i
print("sum = {:.6f}".format(sum))

# 使用列表推导式
# m, n = map(int,input().split())
# print("sum = %.6f"% sum([m*m+1/m for m in range(m,n+1)]))
