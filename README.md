<h1 align = "center" >ArduinoTest</h1>
<ul>
<li>本文件包含几个传感器测试程序如下：</li>
<li>1 红外传感器</li>
<li>2 灰度传感器</li>
<li>3 光敏传感器</li>
<li>4 加速度计传感器</li>
<li>4 舵机</li>
<li>4 电机</li>
</ul>









传感器测试工具解析文档

<h2>目录</h2>

说明	1
<h3><a href = "#ONE">第一章、红外对管传感器检测工具	1</a></h3>
第二章、灰度传感器检测工具	2
第三章、加速度计传感器检测工具	3
第四章、光敏传感器检测工具	4
第五章、舵机检测工具	5


 
说明
代码部分请参考GitHub:



<h2 align = "center" id = "ONE">第一章、红外对管传感器检测工具</h2>
<h3>First 器件清单</h3>
<ul>
<ol>豆包控制器×1</ol>  
<ol>豆包电源×1</ol> 
<ol>豆包像素舵机×1</ol>
<ol>豆包积木若干×1</ol>
<ol>按钮×1</ol>
<ol>灯×1</ol>
<ol>黑色白色硬纸片</ol>
</ul>
<h3>Second 功能介绍</h3>
<p>接通电源，将被检测传感器接到对应插线上放到积木上，按动按钮，舵机带动红外传感器转动，分别进行黑白测试，测试完成后如果LED灯发光，则传感器有效。
        测试完一个传感器，可以取下更换另一传感器，按动按钮复位继续测试。</p>


<h3>Third 制作方法</h3>

<ul>
    <p>首先，我们按照下图所示搭建好我们的结构，主体结构是舵机与一张带有黑色白色背景色的硬纸片配合，让舵机能够在活动范围内使黑白区域分别被传感器检测到。此处需要注意红外传感器具有一定的测量范围，这点需要我们注意
继续，编写程序。笔者这里程序整体如下：</p>>
1、参量包含2个，一个状态值flag，代表着我们所完成的检测工序。第二个是一个value用来储存检测到的模拟。
2、setup里面需要初始化舵机、串口、LED、按钮（采用中断方式）、模拟读取口。
3、整体思路：
1）按钮中断：当按钮被按动时调用中断，进入到中断函数，将flag标志位置1，LED熄灭，也就是复位开始检测。
2）主循环：主循环flag为1时检测一次模拟值，判断其值是否在允许范围内，如果符合要求则转动舵机到白色区域，flag置2。
当flag为2时检测一次模拟值，判断其值是否接近0，如果符合要求则将flag置3。
当flag为3时，点亮绿灯，进入死循环，等待按钮按动跳出循环。

<h3>Fouth 思路拓展</h3> 
<p>    1、本案例相对简单，上述实验只是定性的测量了传感器的好坏，那么是否可以给出定量的指标呢，其实我们可以计算两次测量结果的差值，也可以检测黑白交接渐进程度，这些有待同学们进一步思考。问题虽小，但却体现着工程学的艺术。
  </p>  

 

第二章、灰度传感器检测工具

First 器件清单
1.豆包控制器×1
2.豆包电源×1
3.豆包像素舵机×1
4.豆包积木若干×1
5.按钮×1
6.LED灯×1

Second 功能介绍

接通电源，将被检测传感器接到对应插线上放到积木上，按动按钮，舵机带动灰度传感器转动，分别进行不同积木灰度测试，测试完成后如果LED灯发光，则传感器有效。
测试完一个传感器，可以取下更换另一传感器，按动按钮复位继续测试。

Third 制作方法

首先，我们按照下图所示搭建好我们的结构，主体结构是舵机与几个灰度差值较大的积木配合，让舵机能够在活动范围内使不同灰度的积木分别被传感器检测到。然后更换不同积木看灰度值的差值，挑选出灰度差值较大的。笔者测试的是红色积木和黄色积木。差值大于60。这个也跟远近有一定关系，所以每个人的测试结果也有不同。
继续，编写程序。笔者这里程序整体如下：
1、参量包含2个，一个状态值flag，代表着我们所完成的检测工序。第二个是两个value用来储存检测的积木的灰度值，如果你检测四个积木，那么你可以三个value。
2、setup里面需要初始化舵机、串口、LED、按钮（采用中断方式）、模拟读取口。
3、整体思路：
1）按钮中断：当按钮被按动时调用中断，进入到中断函数，将flag标志位置1，LED熄灭，也就是复位开始检测。
2）主循环：主循环flag为1时检测一次灰度值，并保存，然后转动舵机到下一灰度值，flag置2。
当flag为2时检测一次灰度值，并保存。对两次flag值做对比，差值在正确范围内则将flag置3。
当flag为3时，点亮绿灯，进入死循环，等待按钮按动跳出循环。
 
Fouth 思路拓展
    1、两个积木灰度值的比较相对简单，如果三个积木块比较的话，准确度会提高，但相对算法错误率也会提高，朋友们可以尝试一下对三个灰度值的检测如何确保系统的稳定性。
    2、积木的灰度值差值不是很明显，朋友们可以思考下新的设计方法。

第三章、加速度计传感器检测工具

First 器件清单
1.豆包控制器×1
2.豆包电源×1
3.豆包像素舵机×1
4.豆包积木若干×1
5.按钮×1
6.LED灯×1

Second 功能介绍

接通电源，将被检测传感器接到对应插线上放到积木上，按动按钮，舵机带动加速度计传感器转动，分别进行不同方位测试，测试完成后如果LED灯发光，则传感器有效。
测试完一个传感器，可以取下更换另一传感器，按动按钮复位继续测试。

Third 制作方法

首先，我们按照下图所示搭建好我们的结构，主体结构是舵机与加速度计传感器配合，让舵机能够在活动范围内使加速度计转动不同方位。
继续，编写程序。笔者这里程序整体如下：
1、参量包含2个，一个状态值flag，代表着我们所完成的检测工序。第二个是一个value用来储存检测的加速度X方向值，如果你检测三个方向，那么你可以三个value。
2、setup里面需要初始化舵机、串口、LED、按钮（采用中断方式）、IIC读取口。
3、整体思路：
1）按钮中断：当按钮被按动时调用中断，进入到中断函数，将flag标志位置1，LED熄灭，也就是复位开始检测。
2）主循环：主循环flag为1时检测一次加速度值，如果其值大于0.8则flag置2，如果其值小于-0.8则flag置3。为什莫有两个判断，主要考虑加速度计传感器具有方向性，而不同的用户可能插入方向不一致，另外此处说明大致x正向为1，负向为-1。
当flag为2时检测一次加速度值，如果其值小于-0.8则将flag置4。
当flag为3时检测一次加速度值，如果其值大于0.8则将flag置4。
当flag为4时，点亮绿灯，进入死循环，等待按钮按动跳出循环。

 

第四章、光敏传感器检测工具

First 器件清单
1.豆包控制器×1
2.豆包电源×1
3.豆包像素舵机×1
4.豆包积木若干×1
5.按钮×1
6.LED灯×1

Second 功能介绍

接通电源，将被检测传感器接到对应插线上放到积木上，按动按钮，舵机带动积木门转动，分别进行有光无光测试，测试完成后如果LED灯发光，则传感器有效。
测试完一个传感器，可以取下更换另一传感器，按动按钮复位继续测试。

Third 制作方法

首先，我们按照下图所示搭建好我们的结构，主体结构是舵机与积木组成的门的配合，让舵机带动积木门为光敏传感器创造有光无光两种环境。
继续，编写程序。笔者这里程序整体如下：
1、参量包含2个，一个状态值flag，代表着我们所完成的检测工序。第二个是一个value用来储存检测到的模拟。
2、setup里面需要初始化舵机、串口、LED、按钮（采用中断方式）、模拟读取口。
3、整体思路：
1）按钮中断：当按钮被按动时调用中断，进入到中断函数，将flag标志位置1，LED熄灭，也就是复位开始检测。
2）主循环：主循环flag为1时检测一次模拟值，判断其值是否在允许范围内，如果符合要求则转动舵机到无光区域，flag置2。
当flag为2时检测一次模拟值，判断其值是否接近0，如果符合要求则将flag置3。
当flag为3时，点亮绿灯，进入死循环，等待按钮按动跳出循环。

 
Fouth 思路拓展
    1、本案例相对简单，上述实验只是定性的测量了传感器的好坏，那么是否可以给出定量的指标呢，其实我们可以计算两次测量结果的差值，分析其对光照的敏感程度，这些有待同学们进一步思考。问题虽小，但却体现着工程学的艺术。
2、本案例所搭建的积木门密封性不是特别好，同学们可以思考怎样可以给他创造更密封的无光效果。

第五章、舵机检测工具

First 器件清单
1.豆包控制器×1
2.豆包电源×1
3.豆包灰度传感器×2
4.豆包积木若干×1
5.按钮×1
6.LED灯×1

Second 功能介绍

接通电源，将被被测舵机接到对应插线上放到积木上，按动按钮，舵机带动木块旋转，首先到0度，在旋转至180度，在两端分别有两个灰度传感器测试，测试完成后如果LED灯发光，则传感器有效。
测试完一个传感器，可以取下更换另一传感器，按动按钮复位继续测试。

Third 制作方法

首先，我们按照下图所示搭建好我们的结构。。
继续，编写程序。笔者这里程序整体如下：
1、参量包含2个，一个状态值flag，代表着我们所完成的检测工序。第二个是一个value用来储存检测到的模拟。
2、setup里面需要初始化舵机、串口、LED、按钮（采用中断方式）、模拟读取口。
3、整体思路：
1）按钮中断：当按钮被按动时调用中断，进入到中断函数，将flag标志位置1，LED熄灭，也就是复位开始检测。
2）主循环：主循环flag为1时，舵机旋转置0度，检测一次模拟值，判断其值是否在允许范围内，如果符合要求则转动舵机到180度，flag置2。
当flag为2时检测一次模拟值，判断其是否符合要求，如果符合要求则将flag置3。
当flag为3时，点亮绿灯，进入死循环，等待按钮按动跳出循环。












