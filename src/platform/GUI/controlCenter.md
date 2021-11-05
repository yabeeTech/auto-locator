# GUI of control center

We've added a pop up menu in the system tray. The corresponding class is CSystemTray.

## 1 Property pages in the main window

### 1.1 Steps to add a property page in the main window

1. ����ҳ���������������ҳ�� `CCamerasPage : public CDialogResize`
2. �� `CControlCenterDlg` ͷ�ļ���
   * ����ǰ��ҳ�����ͷ�ļ�
   * ����һ��ҳ����Ķ��� `CCamerasPage m_camerasPage;`
3. �� `CControlCenterDlg` ��ʵ����
   * �� `CControlCenterDlg::ActivatePage(int nIndex)` ��������Ӧҳ�����ʾ������
4. 

### 1.2 Add a page to show connecting status of transmitter wires

Actuator must be connected and operated exactly according to the operation instruction.


## 2 Outlook bar

�����λ�ã�
```cpp
CListCtrl CControlCenterDlg::m_OutlookBar;
```

### 2.1 ����: Outlook bar �޷���ȡ������Ϣ NM_CLICK

�� CListCtrl �ؼ�֮��������ؼ�ȫ���ƶ��� CCamerasPage ��Ӧ�ĶԻ�����Դ�к�
NM_CLICK ��Ϣ�ܹ�׼ȷ�����񡣺��潫��׷������޷�������Ϣ�ľ���ԭ��


### 2.2 Click item to change property page

ת��ҳ���`m_OutlookBar`���ڵ��޷���ʾ�������Ҫ��д����Ԫ�����ź�����
`MoveAll
`

### 2.3 Outlook bar ��ɵ� `m_arrData` �ڴ�й¶

������� `CDialogResiz`e δ���� `CArray<AfxResizeData, AfxResizeData&> m_arrData` 
�ڶԻ��� OnDestroy ʱδ����������ɵġ��� `CControlCenterDlg::OnDestroy()`�м���
`m_arrData.RemoveAll()` ��ô��ڴ�й¶������


## 3 ���¹滮����ͷ��ؽ���

�� CControlCenterDlg �е�����ͷ��ش���ת�Ƶ� CCamerasPage ��

### 3.1 Rewrite CCamerasPage




