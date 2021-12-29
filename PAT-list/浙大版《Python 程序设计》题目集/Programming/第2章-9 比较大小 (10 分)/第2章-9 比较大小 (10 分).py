# print(*sorted(map(int,input().split())),sep()="->")

l=list(map(int,input().split()))
l.sort()
l=[str(i) for i in l]
print('->'.join(l))