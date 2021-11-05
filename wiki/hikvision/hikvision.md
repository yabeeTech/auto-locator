# Dev Memoire for HikVision

Please read:
<https://headendinfo.com/ts-transport-stream-mpts-spts/>

************************

## 1 Wiki

### 1.1 Transport Stream

Abbreviated as TS, transport stream is an audio, video and data communications 
transmission protocol that is specified in MPEG-2 Part 1, Systems (ISO/IEC standard 
13818-1). Its design goal is to allow multiplexing of digital video and audio and to 
synchronize the output. Transport stream offers features for error correction for 
transportation over unreliable media, and is used in broadcast applications such as
 DVB and ATSC. The transport stream allows 
for multiplexing of the digital video and audio, which means the data is combined into 
a single synchronous transmission bit stream, for transmission over a variety of 
standard mediums such as DSL, IP, IPv, Ethernet, Cable TV networks, and more. The 
transport stream is designed to address only the delivery. Storage applications use the 
[program stream](#program-stream).

#### 1.1.1 Some Important Elements of a Transport Stream

##### Packet
A packet is the basic unit of data in a transport stream. It consists of a sync byte, 
whose value is 0x47, followed by three one-bit flags and a 13-bit PID. This is followed 
by a 4-bit continuity counter, which usually increments with each subsequent packet of a 
frame, and can be used to detect missing packets. Additional optional transport fields, 
whose presence may be signalled in the optional adaptation field, may follow. The rest 
of the packet consists of payload. Packets are most often 188 bytes in length, but some 
transport streams consist of 204-byte packets which end in 16 bytes of Reed-Solomon 
error correction data. The 188-byte packet size was originally chosen for compatibility 
with ATM systems.

##### PID
Each table or elementary stream in a transport stream is identified by a 13-bit PID. A 
demultiplexer extracts elementary streams from the transport stream in part by looking 
for packets identified by the same PID. In most applications, Time-division multiplexing 
will be used to decide how often a particular PID appears in the transport stream.

##### Programs
Transport stream has a concept of programs, which are groups of one or more PIDs that are 
related to each other. For instance, a transport stream used in digital television might 
contain three programs, to represent three television channels. Suppose each channel 
consists of one video stream, one or two audio streams, and any necessary metadata. A 
receiver wishing to tune to a particular "channel" merely has to decode the payload of 
the PIDs associated with its program. It can discard the contents of all other PIDs.

##### PAT
PAT stands for Program Association Table. The PAT lists PIDs for all PMTs in the stream. 
Packets containing PAT information always have PID 0x0.

##### PMT
Program Map Tables, or PMTs, contain information about programs. For each program, there 
is a PMT, with the PMT for each program appearing on its own PID. The PMTs describe which 
PIDs contain data relevant to the program. PMTs also provide metadata about the streams 
in their constituent PIDs. For example, if a program contains an MPEG-2 video stream, the 
PMT will list this PID, describe it as a video stream, and provide the type of video that 
it contains (in this case, MPEG-2). The PMT may also contain additional descriptors 
providing data about its constituent streams.

##### PCR
To assist the decoder in presenting programs on time, at the right speed, and with 
synchronization, programs usually periodically provide a Program Clock Reference, or 
PCR, on one of the PIDs in the program.

##### Null Packets
Some transmission schemes, such as those in ATSC and DVB, impose strict constant bitrate 
requirements on the transport stream. In order to ensure that the stream maintains a 
constant bitrate, a multiplexer may need to insert some additional packets. The PID 
0x1FFF is reserved for this purpose. The payload of null packets may contain any data 
at all, and the receiver is expected to ignore its contents. As it happens, most 
multiplexers place all 0's or all F's in these packets, but a few have been seen to 
insert secret messages for the enjoyment of bored engineers.

### 1.2 Program Stream

Abbreviated as PS, program stream is a container format for storage applications 
specified in MPEG-1 Systems and MPEG-2 Part 1. A program stream contains only one 
content channel and is suited to authoring and storage not broadcasting. Contrast 
with [transport stream](#transport-stream), which is designed to address the delivery 
of the content.

To parse PS data stream, the most important part is to extract the PS header:
`00 00 00 ba`, the next is the system header `00 00 00 bb`, and then the `Program Stream map`
packet `00 00 00 bc`, and the H264 data `00 00 00 e0`. For details please see the 
source header file [MediaPsAnaly.h](MediaPsAnaly.h) and the cpp file 
[MediaPsAnaly.cpp](MediaPsAnaly.cpp).

## 2 Realtime Surveillance

NET_DVR_RealPlay_V40: real time surveillance

NET_DVR_StopRealPlay: stop surveillance

NET_DVR_SetRealDataCallBack: Register callback function to access realtime data flow

We have two ways to capture an image:
* using realtime surveillance: NET_DVR_RealPlay_V40
* using `NET_DVR_CaptureJPEGPicture_NEW`, which is not for realtime app

Functions needed to be compared:
* decoding and displaying: PlayM4_SetDecCallBackEx
* decoding but not displaying: PlayM4_SetDecCallBack

PlayM4_InputData 的作用是什么？是不是软解？

### 2.1 Current 2021 implementation


### 2.2 Future optimizing steps

#### 2.2.1 How to direct RTP stream

[VLC](https://www.videolan.org/vlc/) is a free and open source cross-platform multimedia 
player and framework that plays most multimedia files as well as DVDs, Audio CDs, VCDs, 
and various streaming protocols.

We can use VLC to direct RTP stream. We test and succeed, but the result does not look
what we expected. The delay is quite a bit more, much slow than we employ Hik sdk functions.

**或许是VLC的播放缓冲策略导致大延时，将来自己写解码部分再看看是否能有提高。**

```batch
rtsp://[username]:[password]@[ip]:[port]/[codec]/[channel]/[subtype]/av_stream

# main stream
rtsp://admin:123456@192.168.2.231:554/h264/ch1/main/av_stream
# which is equivlent to:
rtsp://admin:123456@192.168.2.231

# sub-stream
rtsp://admin:123456@192.168.2.231:554/h264/ch1/sub/av_stream
```

* port:
default value is 554
* codec:
h264/MPEG-4/mpeg4
* channel: 
channel number, start from 1，起始为1. 如通道1则为ch1.
subtype
码流类型. 主码流为main，辅码流为sub.

You can find the source code in [gitee mirror of VLC media player](https://gitee.com/mirrors/vlc-media-player)

## SDK memoire

### NET_DVR_SetPlayerBufNumber

```cpp
    ///
    /// 设置播放器帧缓冲区的个数
    ///    说明
    ///        设置网络延时和流畅度可以通过此函数来进行调节，如果dwBufNum 值越大，播放的流畅性越好，相应的延时比较大，dwBufNum 值越小，
    ///        播放的延时很小，但是当网络不太顺畅的时候，会有丢帧现象，感觉播放不会很流畅。一般设置的帧缓冲大于等于6帧时，
    ///        音频预览才会正常，如果不需要音频预览，只需要视频实时性则这个值可以设置的更小。此函数要紧跟在NET_DVR_RealPlay后使用，
    ///        在图像播放之后设置则不起作用！硬解码时则通过相应的硬解码的函数来调整延时和流畅程度。
    ///    NET_DVR_API BOOL __stdcall NET_DVR_SetPlayerBufNumber(LONG lRealHandle,DWORD dwBufNum);
    ///
    /// [in] NET_DVR_RealPlay或者NET_DVR_RealPlay_V30的返回值
    /// [in]播放器帧缓冲区缓存的最大帧数，取值为（1－50），缓冲区越大，播放越流畅；缓冲区越小，实时性越好。若是复合流建议最小值设置成6
    ///
    [DllImport("HCNetSDK.dll")]
    public static extern bool NET_DVR_SetPlayerBufNumber(int lRealHandle, uint dwBufNum);
```

## refs

<https://blog.csdn.net/duopuledemao/article/details/98225471>

<https://blog.csdn.net/yaoyutian/article/details/96346257>

<https://www.cnblogs.com/zhumengke/articles/11656360.html>

<https://blog.csdn.net/chen495810242/article/details/39207305>

<https://www.jianshu.com/p/75aac9258637>

<https://blog.csdn.net/qq_26602023/article/details/101024815>

<https://blog.yasking.org/a/hikvision-rtp-ps-stream-parser.html>

<https://blog.csdn.net/u010868213/article/details/102484175>

<https://blog.csdn.net/wwyyxx26/article/details/15224879#>

<https://www.cnblogs.com/codenow/p/4871704.html>

<https://blog.csdn.net/weixin_30640769/article/details/95496633>

<https://www.cnblogs.com/zhumengke/articles/11681668.html>

<https://blog.csdn.net/xswy1/article/details/81609427>

<https://www.icode9.com/content-4-897139.html>

<https://www.pianshen.com/article/2084455049/>





