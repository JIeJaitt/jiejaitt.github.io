unordered_map是C++中的哈希表，可以在任意类型与类型之间做映射。

## 基本操作
- 引用头文件(C++11)：`#include <unordered_map>`
- 定义：unordered_map<int,int>、unordered_map<string, double> ...
- 插入：例如将("ABC" -> 5.45) 插入unordered_map<string, double> hash中，hash["ABC"]=5.45
- 查询：hash["ABC"]会返回5.45
- 判断key是否存在：hash.count("ABC") != 0 或 hash.find("ABC") != hash.end()
- 遍历
