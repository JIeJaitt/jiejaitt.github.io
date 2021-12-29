a,b,c=input().split()
a,b,c=eval(a),eval(b),eval(c)
if(a+b<=c or a+c<=b or b+c<=a):
    print("These sides do not correspond to a valid triangle")
else:	
    s=(a+b+c)/2
    S=(s*(s-a)*(s-b)*(s-c))**0.5
    C=a+b+c
    print("area = {:.2f}; perimeter = {:.2f}".format(S,C))
