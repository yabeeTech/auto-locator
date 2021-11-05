# Automatic Locating System for Flat Bed Silk Screen Printing Pipeline
For English version please [switch to the English version](readme.md)

[^_^]:
https://github.com/yabeeTech/auto-locator

[^_^]:
https://gitee.com/yabeeTech/auto-locator

[^_^]:
F:\Projects\yabee\git\auto-locator

**********************************

Yabee 平板印花流水线智能定位系统设备端资源站点

黄冈市与武汉大学2019年百校千企签约项目

维护：胡继承 博士

**当前维护状态:** 视频捕获延迟严重(近一秒)，怀疑内存池过多拷贝，考虑直接使用HK传过来的内存。
具体维护细节参见 [软件维护状态](maintaining.md)。

## 1 系统概览

The system contains the following modules:
* auto-testing tools
* device end
* control center
* data center

## 2 控制中心

The control center consists of a series of industrial computers, each of which controls a 
actuator of locating the corresponding stancil frame.

The final implementing mechanism of the system uses displacement control. Early on, 
we used CAN bus servo motors for displacement control, and in the future we considered 
industrial Ethernet to achieve the control of the actuator.

基于成本的考虑目前我们使用伺服电机配合气缸夹紧来进行位移控制，未来可考虑使用电液压伺服来替代气缸。

### 2.1 控制中心的软件架构

软件的架构强调重用性，也就是说将来很容易移植到新的机器设备的控制过程。将组成机器的部件进行抽象，
通过CDevice的对象复合成具有层次关系的CDevice对象，广泛使用模板类和模板函数提高代码的可重用性。
所有可控制的执行机构都被封装成CDevice的子类，例如CMotor与CValve都是CDevice的子类。

每一执行机构的动作按照其所归属的时间线进行管理。

### 2.2 控制的物理层次与逻辑层次

硬件装置形成的物理层次包括基础CAN网、控制电路板、执行机构等。

控制逻辑形成的逻辑层次是对控制动作的抽象，与物理层次实现隔离。

下面以分析两个转角气缸协同执行推键的动作作为例子来思考如何分离物理层次和逻辑层次。

两个转角气缸形成了一个推送机构CDevicePush，其Action包括push和reset。
这样需要建立一个同步时钟来通过时间戳同步两个子设备的动作。
在硬件上两个转角气缸可以由不同的电路板驱动，但逻辑上似乎被同时驱动。
因此整个系统必须建立一套同步时钟系统，每个电路板通过时间戳来同步动作开启的时间。

同步由硬件设备完成，因此还需要抽象出控制电路板来保持时间戳的一致。
至于伺服电机的时间戳如何设置需要详细阅读伺服电机的控制协议，形成一个全局的同步网络。
也可以考虑将伺服电机控制器抽象为控制电路板，遵从相同的逻辑同步的使能。

### 2.3 Camera Configuration


### 2.4 类 CMgrChannel

The thread handle `HANDLE m_hThreadCapture` is associated with the thread loop 
`void loopCapture ( )` when the capture thread is created in 
`void CMgrChannel::onCapture ( )`.


### 2.5 类 CthreadNetworkService













