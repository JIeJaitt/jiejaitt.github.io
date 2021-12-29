s = '';lis1 = [];dic = {}
while "#" not in s:
    s += input()                    #将输入进去的字符串拼接
for i in s.split("#")[0].split():   #将整个文本进行分隔并遍历
    if "_" in i or i.isalnum():     #含"_"的单词是正常单词除此外都是分隔符
        lis1.append(i) if len(i) <= 15 else lis1.append(i[:15])
    else:
        a = [j for j in i if not j.isalnum()]       #获取分隔符
        if a[0] in i:
            lis1.extend(i[:15] if len(i) >15 else i for i in i.split(a[0]) if i != "")
for i in lis1:
    dic[i.lower()] = dic.get(i,0)+1     #用lower() 将单词转换为小写并作为键生成
lis2 = list(dic.items())
lis2.sort(key= lambda x:x[1],reverse=True)
for i in range(-1,len(dic)//10):           #获取词频最大的前10%的单词个数
    print(len(dic)) if i< 0 else print("%d : %s"%(lis2[i][1],lis2[i][0]))