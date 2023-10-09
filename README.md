# README

## 组件工具PLUS

### 项目介绍

一款桌面多功能的组件工具，主要包含天气预报系统、游戏、音乐播放器、日历、行程、日期、登录注册功能。天气预报系统可以搜索城市名，显示当地天气的详细信息，比如：温度、天气、湿度等等，并显示天气对应的图片。游戏功能包含多款游戏，目前只完成了扫雷游戏。音乐播放器用来播放本地音乐，实现切换音乐，播放模式等。日历功能包含添加行程，查看行程等功能（**因为Qt版本问题，QMediaPlaylist类以及QMediaPlayer类中的一些方法在Qt6中没有，所以目前音乐播放器功能实现不了**）。

### 架构设计

使用Qt开发工具，使用C++语言进行编写。首先是登录注册功能创建数据库，对数据库进行操作。之后进入主界面，显示具体组件工具。天气预报功能首先创建网络管理对象，发送请求，连接心知天气API，接收JSON数据，并解析，转化成具体的天气信息显示到界面当中。音乐播放器可以实现本地音乐文件的播放，通过QMediaPlaylist创建播放列表，通过相关方法以及自定义方法实现切换音乐，设置播放模式等功能。日历及行程功能通过创建QCalendarWidget控件，通过选择日期的槽函数以及自定义设立行程和查看行程的方法，创建数据结构Map，将行程星期和日期添加到数据结构里，进行操作。

### 使用说明

1. 点击注册按钮

   ![image-20231007202421836](C:\Users\30882\AppData\Roaming\Typora\typora-user-images\image-20231007202421836.png)

2. 注册用户名、密码，返回登录

   ![image-20231007202556423](C:\Users\30882\AppData\Roaming\Typora\typora-user-images\image-20231007202556423.png)

3. 主界面，点击不同的组件工具

   ![image-20231007202937215](C:\Users\30882\AppData\Roaming\Typora\typora-user-images\image-20231007202937215.png)

   

4. 天气预报系统输入城市名，显示天气信息

   注意：连接心知天气API接口密钥有效期为14天，过期后需要更换

   游戏点击扫雷

   ![image-20231007203100867](C:\Users\30882\AppData\Roaming\Typora\typora-user-images\image-20231007203100867.png)

   进行游戏，可以设置游戏难度以及自定义
   
   日历功能可以添加行程，查看行程