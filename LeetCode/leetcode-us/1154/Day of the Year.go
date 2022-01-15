func dayOfYear(date string) int {
    year,_:=strconv.Atoi(date[:4])
    month,_:=strconv.Atoi(date[5:7])
    day,_:=strconv.Atoi(date[8:])
    
    amount:=[]int{31,28,31,30,31,30,31,31,30,31,30,31}
    if year%400==0 || (year%4==0&&year%100!=0) {
        amount[1]++
    }     
    
    ans:=day
    for _,i:=range amount[:month-1] {
        ans+=i;
    }      
    return ans
}