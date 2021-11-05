# About YUV Video

<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>

<https://docs.microsoft.com/en-us/windows/win32/medfound/about-yuv-video>

[Microsoft MPEG-2 Video Encoder](https://docs.microsoft.com/en-us/windows/win32/directshow/microsoft-mpeg-2-video-encoder)

******************************************

The three RGB values form a mathematical coordinate system, called a color space. The 
red component defines one axis of this coordinate system, blue defines the second, and 
green defines the third, as shown in the following illustration. Any valid RGB color falls 
somewhere within this color space. For example, pure magenta is 100% blue, 100% red, 
and 0% green.

![color space](pix/color-space.gif)

Although RGB is a common way to represent colors, other coordinate systems are possible. 
The term YUV refers to a family of color spaces, all of which encode brightness information 
separately from color information. Like RGB, YUV uses three values to represent any color. 
These values are termed Y', U, and V. (In fact, this use of the term "YUV" is technically 
inaccurate. In computer video, the term YUV almost always refers to one particular color 
space named Y'CbCr, discussed later. However, YUV is often used as a general term for any 
color space that works along the same principles as Y'CbCr.)

The Y' component, also called luma, represents the brightness value of the color. The prime 
symbol (') is used to differentiate luma from a closely related value, luminance, which is 
designated Y. Luminance is derived from linear RGB values, whereas luma is derived from 
non-linear (gamma-corrected) RGB values. Luminance is a closer measure of true brightness 
but luma is more practical to use for technical reasons. The prime symbol is frequently 
omitted, but YUV color spaces always use luma, not luminance.

Luma is derived from an RGB color by taking a weighted average of the red, green, and blue 
components. For standard-definition television, the following formula is used:

$$
Y' = 0.299R + 0.587G + 0.114B
$$

This formula reflects the fact that the human eye is more sensitive to certain wavelengths 
of light than others, which affects the perceived brightness of a color. Blue light appears 
dimmest, green appears brightest, and red is somewhere in between. This formula also reflects 
the physical characteristics of the phosphors used in early televisions. A newer formula, 
taking into account modern television technology, is used for high-definition television:

$$
Y' = 0.2125R + 0.7154G + 0.0721B
$$

The luma equation for standard-definition television is defined in a specification named 
ITU-R BT.601. For high-definition television, the relevant specification is ITU-R BT.709.

The U and V components, also called chroma values or color difference values, are derived 
by subtracting the Y value from the red and blue components of the original RGB color:
$$
U = B - Y'
$$
$$
V = R - Y'
$$

Together, these values contain enough information to recover the original RGB value.

## 1 Benefits of YUV

Analog television uses YUV partly for historical reasons. Analog color television signals 
were designed to be backward compatible with black-and-white televisions. The color television 
signal carries the chroma information (U and V) superimposed onto the luma signal. 
Black-and-white televisions ignore the chroma and display the combined signal as a 
grayscale image. (The signal is designed so that the chroma does not significantly interfere 
with the luma signal.) Color televisions can extract the chroma and convert the signal back 
to RGB.

YUV has another advantage that is more relevant today. The human eye is less sensitive to 
changes in hue than changes in brightness. As a result, an image can have less chroma 
information than luma information without sacrificing the perceived quality of the image. 
For example, it is common to sample the chroma values at half the horizontal resolution of 
the luma samples. In other words, for every two luma samples in a row of pixels, there is one 
U sample and one V sample. Assuming that 8 bits are used to encode each value, a total of 4 
bytes are needed for every two pixels (two Y', one U, and one V), for an average of 16 bits 
per pixel, or 30% less than the equivalent 24-bit RGB encoding.

YUV is not inherently any more compact than RGB. Unless the chroma is downsampled, a YUV 
pixel is the same size as an RGB pixel. Also, the conversion from RGB to YUV is not lossy. 
If there is no downsampling, a YUV pixel can be converted back to RGB with no loss of 
information. Downsampling makes a YUV image smaller and also loses some of the color 
information. If performed correctly, however, the loss is not perceptually significant.


## 2 YUV in Computer Video

The formulas listed previously for YUV are not the exact conversions used in digital video. 
Digital video generally uses a form of YUV called Y'CbCr. Essentially, Y'CbCr works by 
scaling the YUV components to the following ranges:

| Component	| Range |
| :-- | :-- |
| Y' | 16�C235 |
| Cb/Cr | 16�C240, with 128 representing zero |
 

These ranges assume 8 bits of precision for the Y'CbCr components. Here is the exact 
derivation of Y'CbCr, using the BT.601 definition of luma:

1. Start with RGB values in the range [0...1]. In other words, pure black is 0 and pure 
white is 1. Importantly, these are non-linear (gamma corrected) RGB values.

2. Calculate the luma. For BT.601, Y' = 0.299R + 0.587G + 0.114B, as described earlier.

3. Calculate the intermediate chroma difference values (B - Y') and (R - Y'). These values 
have a range of +/- 0.886 for (B - Y'), and +/- 0.701 for (R - Y').

4. Scale the chroma difference values as follows:

Pb = (0.5 / (1 - 0.114)) �� (B - Y')

Pr = (0.5 / (1 - 0.299)) �� (R - Y')

These scaling factors are designed to give both values the same numerical range, +/- 0.5. 
Together, they define a YUV color space named Y'PbPr. This color space is used in analog 
component video.

5. Scale the Y'PbPr values to get the final Y'CbCr values:

Y' = 16 + 219 �� Y'

Cb = 128 + 224 �� Pb

Cr = 128 + 224 �� Pr

These last scaling factors produce the range of values listed in the previous table. 
Of course, you can convert RGB directly to Y'CbCr without storing the intermediate results. 
The steps are listed separately here to show how Y'CbCr derives from the original YUV 
equations given at the beginning of this article.

The following table shows RGB and YCbCr values for various colors, again using the BT.601 
definition of luma.

| Color | R | G | B | Y' | Cb | Cr |
| :- | :- | :- | :- | :- | :- | :- |
| Black | 0 | 0 | 0 | 16 | 128 | 128 |
| Red | 255 | 0 | 0 | 81 | 90 | 240 |
| Green | 0 | 255 | 0 | 145 | 54 | 34 |
| Blue | 0 | 0 | 255 | 41 | 240 | 110 |
| Cyan | 0 | 255 | 255 | 170 | 166 | 16 |
| Magenta | 255 | 0 | 255 | 106 | 202 | 222 |
| Yellow | 255 | 255 | 0 | 210 | 16 | 146 |
| White | 255 | 255 | 255 | 235 | 128 | 128 |

As this table shows, Cb and Cr do not correspond to intuitive ideas about color. For example, 
pure white and pure black both contain neutral levels of Cb and Cr (128). The highest and 
lowest values for Cb are blue and yellow, respectively. For Cr, the highest and lowest values 
are red and cyan.

### 2.1 YUV �� RGB ��ʽ����

YUV �Ĵ洢���� RGB ��ʽ���ͬ���ڣ�RGB ��ʽÿ��������������̱�����һ��ġ��� R��G��B
��ǰ�󲻼���ı����� 2-4byte �ռ��С��� YUV ��������Ϊ�˽�Լ�ռ䣬U��V
�����ռ���С��ÿһ����� Y �����������棬������������� U��V
�����Ǳ�����һ��ģ�ͨ���˵����۲��������

### 2.2 YUV��ʽ����

YUV ��ʽ��Ϊ�������ͣ�Packed ���ͺ� Planar ���͡����У�Packed �����ǽ� YUV
����������ͬһ�������У�ÿ�����ص�� Y��U��V ����������洢�ģ�Planar �����ǽ� YUV
�����ֱ��ŵ����������������У����������洢�������ص�� Y�������Ŵ洢�������ص�� U��������������ص��V��

#### 2.2.1 YUV������ʽ

YUV �����Ĵ洢��ʽ�������ʽ������أ�Ŀǰ�����Ĳ�����ʽ���������֣�YUV444��YUV422��YUV420�����У�YUV444
������ÿһ�� Y ��Ӧһ�� UV ������ÿ������ (YUV) ռ 32 Bits��YUV422 ������ÿ���� Y
����һ�� UV ������ÿ������ռ 16bits��Y ռ 8bits��UV ����ռ 8bits����YUV420 ������ÿ�ĸ� Y
����һ�� UV ������ÿ������ (YUV) ռ 16bits ���� 12bits��ͨ����YUV A:B:C
����˼һ����ָ���� 4 ����������, ���� Y ������ A �Σ�U������ B ��, V ������ C
�Ρ������Ժڵ��ʾ���������ص��Y�������Կ���ԲȦ��ʾ���ø����ص�� UV ���������ֲ�����ʽ��ʾ����ͼ��

![sampling](pix/sampling.jpg)

a) YUV444����ʾ Y��U��V ��ռ��Ϊ 4 : 4 : 4�����ֲ�����ʽ��ɫ��ֵ UV ������ٲ�����Y��U��V
������ռһ���ֽڣ���ͬ Alpha ͨ��һ���ֽڣ�YUV444 ÿ������ռ 4 �ֽڣ�Ҳ����˵�����ʽʵ�ʾ��� 24bpp
�� RGB ��ʽ������ʾ����

    ���ԭʼ�����ĸ������ǣ�A0 Y0 U0 V0, A1 Y1 U1 V1, A2 Y2 U2 V2, A3 Y3 U3 V3 \
    ��4:4:4������������ȻΪ��A0 Y0 U0 V0, A1 Y1 U1 V1, A2 Y2 U2 V2, A3 Y3 U3 V3

b) YUV422����ʾY��U��V��ռ��Ϊ 4 : 2 : 2�����ֲ�����ʽ��ɫ��ֵ UV �����������룬�����һ�����ز���Ϊ
Y��U���ڶ������ز��� Y��V���������ơ� YUV422 ÿ������ռ 2 ���ֽڡ�����ʾ����

    ���ԭʼ�����ĸ������ǣ�Y0 U0 V0, Y1 U1 V1, Y2 U2 V2, Y3 U3 V3 \
    ����4:2:2���������ݱ�ɣ�Y0 U0, Y1 V1, Y2 U2, Y3 V3

c) YUV420��������ζû�� V ������0 ����˼�� U��V �������вŲ���һ�Σ������һ�в���Ϊ 4:2:0���ڶ��в���
4:0:2���������ơ� YUV ����(ÿ������)ռ�� 16bits �� 12bits����֮����4:4:4 
����������������ź����»�ԭ��ʾ��, �ᶪʧ���� UV ���ݣ�ֻ�������ٵ����ݲ��룬�����۶� UV
�����У��������о���ʧ����

#### 2.2.2 YUV420 ��������

���ں���ʵʱ�ɼ�����Ƶ֡��ʽΪ YV12 ���� NV21�����Ƕ����� YUV420
������ʽ�����������Ƕ����ָ�ʽ����һ���򵥵ķ�����YUV420
��ʽ�������Ĳ�����ʽΪ 4��2��0���� 4 �� Y ��������һ�� UV
����������ռ�ڴ�Ϊ 16bits/pixel��12Bits/Pixel(����)��������Ҫ�о��� YV12 �� NV21
ÿ�����ص�ռ�ڴ�Ϊ 12bit������ÿ��������һ�� YUV ���ɡ�����ɫ��ʽ����ÿ������ Y��U��V
�ֱ�ռ�ڴ��СΪ Y=8bit=1Byte��U=2bit=1/4(Byte)��V=2bit=1/4(Byte)����һ�������� Y��U��V
�ı���Ϊ 4:1:1������ԭʼ֡ͼ��Ϊ 640x480 ���أ�����ռ�õ��ڴ�ռ��СΪ��

    640*480*(Y+Y/4+Y/4) =640*480*(1+1/4+1/4)*(1 Byte) = 640*480*(3/2)�ֽ�=450KB

���У�1�� Y ����ռ�ڴ�1���ֽ�(Byte)����˾��������֪һ֡ 640x480 ���ص� YV12 �� NV21
��ͼƬ��ռ�ڴ��СΪ 450KB����Ҳ�����������ڶ� Camera �ɼ��� YV12 �� NV21
��ʽ���ݽ��б���ʱ����Ҫ����һ����СΪ`[widt*height*3/2]`���ֽ�������Ϊ�����ԭ��
�����ڴ�洢����С��λΪ�ֽڣ�Y��U��V �ֱ�ռ���ڴ�ռ�Ϊ (�� YV12 ����Ϊ��)��

    Y ������(640*480) ���ֽڣ��ڴ�洢��ΧΪ 0 ~ 640*480 �ֽ�

    V(Cr)������(640*480*(1/4)) ���ֽڣ��洢��ΧΪ 640*480 ~ (1+1/4)*640*480 �ֽ�

    U(Cb)������(640*480*(1/4)) ���ֽڣ��洢��ΧΪ 5/4*640*480 ~ 640*480*3/2 �ֽ�

#### 2.2.3 I420��YV12��NV12��NV21����

1) YUV420SP��YUV420P������ YUV420 ��ʽ���������� YUV420 ��ʽͼ�����ǵ� Y
ֵ������ȫ��ͬ����Ϊֻ�� Y ��ͼ���ǻҶ�ͼ��YUV420P �� Y��U��V
������������ƽ���ʽ����Ϊ I420(��׼YUV420��YYYYYYYYUU VV) �� YV12 ���֣�YUV420SP
�� Y ����Ϊƽ���ʽ��UV �����ʽ����Ϊ NV12 �� NV21 ���֡���Ҫע����ǣ�YUV
��ʽ�Ĵ�ŷ�ʽ��Զ����������Y������������ U �� V ��������ͬ�Ĳ���ֻ�� U �� V ���������и�ʽ��˳��ͬ��

2) YV12��I420������ YUV420P ��ʽ��ÿһ�����ص�� YUV ������ȡ��ѭ YUV420
��ʽ����ȡ��ʽ���� 4�� Y ��������һ�� UV������һ�� Plane ģʽ���� Y��U��V
�����ֶ��������� plane ���δ洢������ͼ��ʾ��I420��YV12 �� Y ֵ������ȫ��ͬ��ֻ�� U��V
ƽ���λ�ò�ͬ���洢�ռ�ṹ���£�

YV12 �����ȣ��С��У��� V���С���/4) + U���С���/4��

I420 �����ȣ��С��У��� U���С���/4) + V���С���/4��

������Y0Y1Y2Y3 U0 V0(I420)��Y0Y1Y2Y3V0U0(YV12)��

![yv12](pix/yv12.png)

![nv12](pix/nv12.png)

�ܽ᣺

I420:YYYYYYYY  UU VV    =>YUV420P(Planeģʽ)

YV12:YYYYYYYY  VV UU    =>YUV420P(Planeģʽ)

NV12:YYYYYYYY  UVUV     =>YUV420SP(2��Plannar��YΪƽ��ģʽ��UVΪ���ģʽ)

NV21:YYYYYYYY  VUVU     =>YUV420SP(2��Plannar��YΪƽ��ģʽ��UVΪ���ģʽ)








