# GUI of control center

We've added a pop up menu in the system tray. The corresponding class is CSystemTray.

## 1 Property pages in the main window

### 1.1 Steps to add a property page in the main window

1. 定义页面类例如相机参数页面 `CCamerasPage : public CDialogResize`
2. 在 `CControlCenterDlg` 头文件中
   * 包含前述页面类的头文件
   * 增加一个页面类的对象 `CCamerasPage m_camerasPage;`
3. 在 `CControlCenterDlg` 的实现中
   * 在 `CControlCenterDlg::ActivatePage(int nIndex)` 中增加相应页面的显示或隐藏
4. 

### 1.2 Add a page to show connecting status of transmitter wires

Actuator must be connected and operated exactly according to the operation instruction.


## 2 Outlook bar

定义的位置：
```cpp
CListCtrl CControlCenterDlg::m_OutlookBar;
```

### 2.1 问题: Outlook bar 无法获取输入消息 NM_CLICK

将 CListCtrl 控件之外的其它控件全部移动到 CCamerasPage 对应的对话框资源中后，
NM_CLICK 消息能够准确被捕获。后面将逐步追踪造成无法捕获消息的具体原因。


### 2.2 Click item to change property page

转换页面后，`m_OutlookBar`被遮挡无法显示，因此需要重写界面元素重排函数：
`MoveAll
`

### 2.3 Outlook bar 造成的 `m_arrData` 内存泄露

这个是类 `CDialogResiz`e 未处理 `CArray<AfxResizeData, AfxResizeData&> m_arrData` 
在对话框 OnDestroy 时未清理容器造成的。在 `CControlCenterDlg::OnDestroy()`中加上
`m_arrData.RemoveAll()` 后该处内存泄露被清理。


## 3 重新规划摄像头监控界面

将 CControlCenterDlg 中的摄像头监控窗口转移到 CCamerasPage 中

### 3.1 Rewrite CCamerasPage




