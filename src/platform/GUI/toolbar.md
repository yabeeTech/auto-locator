# Toolbar


## 1 Buttons on the toolbar

### 1.1 工具条分组

### 1.2 预热、启动与停止


- 预热按钮的 ID 为 ID_SERVER_PRESTART, 响应函数 OnServerPreStart
- 启动按钮的 ID 为 ID_SERVER_START, 响应函数 OnServerStart
- 停止按钮的 ID 为 ID_SERVER_STOP, 响应函数 OnServerStop

### 1.3 视频流相关


## 2 Business Logic

预热的功能目标
- 以太网连接正常, 能顺利登录访问各视频摄像头
- CAN 网工作正常（目前这一部分业务逻辑需要验证）

启动的功能目标
- 按照控制顺序逐一检测各 device 的状态
- 需要检讨上电顺序


## 3 GUI enhancement

