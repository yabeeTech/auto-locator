# Maintaining Status


November 5, 2021:
* CC integration: new GUI
    * Surveillance in cameras page
    * Business logical of stop toolbar

November 4, 2021:
* CC integration: new GUI
    * Remodeling cameras page
    * connecting cameras
    * Big toolbar

November 3, 2021:
* CC integration: new GUI
    * Repository of all control bars, especially the status bar

October 5, 2021:
* CC integration: new GUI
    * add m_tracePage
    * add m_outlookBar

October 4, 2021:
* CC integration: System self-testing
    * Create a modeless dialog to display the testing infos
    * Ethernet network testing
    * CAN network testing
    * Data center connection
    * Device end testing

October 3, 2021:
* CC integration: System initialization
    * change the login button to be power up

September 4, 2021:
* CC algorithm integration: processing flow
    * stencil lb(locating bars) parameters determination and verification
    * frame lb parameters determination and verification
    * constraint CNN algorithms

September 3, 2021:
* CC integration: algorithm integration
    * locating bar searching
    * fix parameters determination

September 1, 2021:
* CC integration: real time capturing
    * FFmpeg converting: all succeeded!

August 28, 2021:
* CC: function implementing on real time capturing based on HikVision SDK
    * NOT RTP stream, start from H264 stream
    * transfer capturing image to RGB

August 27, 2021:
* CC integration: real time capturing
    * RTP stream
    * VLC direct stream, succeeded but delay is not good
    * stop exploring on new way to optimize decoding delay

August 26, 2021:
* CC integration: real time capturing
    * PS stream

August 25, 2021:
* CC integration: real time capturing
    * Set the callback to be NULL or not, in function NET_DVR_SetRealDataCallBack ( ... ), 
    to control the capturing process
    * Set the size of the capturing images in camerasConfig.ini
    * How to set the last parameter of NET_DVR_RealPlay_V30 ( ... )
        * We've currently set to be TRUE, but why?
    * set lLinkMode to be 1, that is, use UDP protocol to transfer stream data

August 24, 2021:
* CC integration: add FFmpeg, compiling succeeded
    * modify platformYabee.vcxproj to add configuration for FFmpeg
    * copy ffmpeg and FFmpegInterop to the solution folder of Yabee.sln
    * include the ffmpeg libs

August 21, 2021:
* CC: Speed up the capturing rate of the locating cameras
    * FFmpeg / FFmpegInterop configurations for VS

August 18, 2021:
* CC: Rewrite CChannel::DecCBFun ( ... ) - not write to video files
    * considering processing image in the yuv space for fast image processing

August 13, 2021:
* CC: real time image capture - 4 days to fix this problem

August 12, 2021:
* CC integration: control flow - from capturing to motor driven procedure on board
    * initialization of the CAN network

August 11, 2021:
* CC integration: Migrating to x64, compiling succeeded

August 10, 2021:
* integrate machine into CC

August 9, 2021:
* CC & CD: integration applying process
* CD: change the folder `F:\Projects\yabee\jicheng\devicesControl\testingDevices\machine`
to be a git submodule
    * remove tracked files in foler `machine` from the Git index

    ```shell
        git rm -r machine
    ```

    * now, add the submodule

    ```shell
        git submodule add https://gitee.com/jichenghu/machine.git
    ```

August 8, 2021:
* CC & CD: integration exploration

August 7, 2021:
* CC (Control Center): Testing motors
* CC: changed to win32 platform - succeed
* CD (Control Device): change to x64 platform - failed, the CANlib does NOT support x64
* CC & CD: win32 Debug OK

August 6, 2021:
* Control Center (CC): trace the monitoring procedure
* Every camera works great, some memory leaks need to be fixed

June 26, 2021:
* add `delete cDown` in ln278, MgrChannel.cpp

June 25, 2021:
* Mem leaks at MgrChannel.cpp ln218, `ini.ReadText ( ... )`

June 23rd, 2021:
* access the monitor cameras for capturing, the main capture loop is
`void CMgrChannel::loopCapture ( )`
* the above function calls `CChannel::captureJPEG ( LPJPEG_BUFFER pBuffer )`
to get JPEG images and saves the captured pix to `m_cFolderCapture`
* the above function is then calls to `CChannel::detectFrame ( )` to detect silk printing frame

June 22nd, 2021:
* Remove `#include <opencv.hpp>` from `Channel_0.cpp`
* Remove `#include "surfplus.h" from `threadNetworkService.h`
* Remove the corresponding opencv directory from the 'Additional Include Directories'
of the property of project yabeePlatform
* all the modules related to opencv is removed and the current version works well




