**启发思路**

- 缩小问题规模：逐步缩小，首尾同时缩短，第一步动作分割，最后一步动作分割
- 外加约束条件：如字符串问题，以子串长度为外加约束条件进行遍历，然后再对约束条件进行放缩，约束条件作为一个纬度起到分割问题的作用
- 操作过程逆向思考
- DP 应用范围非常广泛

**数据规模逆向分析**

- `O(N)` 对抗分析：桶排序，丢弃一半子问题的高等排序（退治法），DP
- `O(X Log N)` 对抗分析：各类分治算法
- `1M+` 数值在任何位置出现几乎不可能为 IO 规模或数据规模，通常是步骤次数 
    - 数值规模 -> 数学公式（如排列组合游戏）
    - 操作次数 -> 带结合律的连续运算（如矩阵乘法） -> 高次幂算法

**String match problem**

- hash map is enough for most OJ questions.
- if pattern length is constant, use hash map with rolling hash.
- if just search one time, use kmp. (so kmp is not so useful.)
- suffix tree for match any substring with any length.
