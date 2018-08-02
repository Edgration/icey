# bzoj-checker

本地bzoj评测软件，只兼容Linux系统。
具体评测方法是从bzoj.download下载数据然后实现本地评测。

程序截图：
[pic1](http://wx2.sinaimg.cn/mw690/0060lm7Tly1ftvb133tc6j30mn0kstas.jpg)
[pic2](http://wx2.sinaimg.cn/mw690/0060lm7Tly1ftvb1ang5uj30p50ga40g.jpg)

需要安装alex下载包
```
sudo apt install alex
``` 
或者是
```
cd [下载的位置]
sh prep.sh
```

运行程序
```
./bzoj-checker -t [题目编号] [本地代码地址]
```

提示：本程序bug很多很多，仅供娱乐。

## 很多功能缺陷：
+ 无法评测 TLE 
+ 无法评测 MLE 
+ RE 有时候会判成WA
+ More...

如果无意中侵犯了您的权益，请电邮edgration@163.com，此代码将及时删除




