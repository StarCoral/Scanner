# Scanner
編譯程式課程期末專題 ★ scanner for compiler is developed in c++ by StarCoral

---

## 輸出輸入規定
+ 輸入為一般 .txt 文字檔，可於執行時輸入檔名  
+ 讀入文字檔，切出各 token，判斷各token 長度及類別  
+ 輸出 .txt 文字檔，若輸入檔名為test.txt，輸出檔名為scanner_test.txt  
+ 計算 token 總數及各類別token 個數，列於輸出檔最後端  
+ 找出無法分類的 token，並從下一行開始再次scan  


## Token 類別
```
+ Reserved word  

  include main char int float if else elseif 
  for while do return switch case printf scanf 
  允許各式大小寫組合

+ Library name
  <xxx.h>  

+ Comment  
  /* … */ // …

+ Identifier  
  char/int/float 有定義的變數，允許底線及數字，限定英文字母開頭 (否則視為錯誤)
  
+ Constant  
  整數/浮點數/負數
  負數可以表示成 -3 或 (-3)，算1 個token
  
+ Operator
  + - * / % ^ ++ -- & | =
  
+ Comparator
  = = < > <= >= !=
  
+ Bracket
  ( ) [ ] { }
  
+ Format specifier
  %d %f %c \*
  
+ Pointer
  *identifier 中的 * 符號
  *identifier 算1 個token
  
+ Address
  &identifier 中的 & 符號
  &identifier 算1 個token (identifier 必須已定義)
  
+ Punctuation
, ; : # “ ‘

+ Printed token
```

## Example
```
#include<stdio.h>
int i, k, m, *id;
for (i = 1; i < 10; i++) {
k = k + i;
m = 100 – m;
}
printf(“xxx yyy %d\n”, k); // This is a comment
/* This is also a comment. */
------------------------------------------------------------------
Total: 53 tokens
Reserved word: 4
include
int
for
printf
Library name: 1
<stdio.h>
Comment: 2
// This is a comment
/* This is also a comment. */
Identifier: 12
i (x5)
k (x4)
m (x3)
Constant: 3
1
10
100
Operator: 6
= (x3)
++
+
–
Comparator: 1
<
Bracket: 6
( (x2)
) (x2)
{
}
Format specifier: 2
%d
\n
Pointer: 1
*id
Punctuation: 13
#
, (x4)
; (x6)
“ (x2)
Printed token: 2
xxx
yyy
```
開發環境: Visual Studio Code
