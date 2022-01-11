# robot_system
Chiba Institute of Technology robot system for class

課題１のリポジトリとして使用。

課題の基本としてmyled.cではGPIO25ピンによるLEDの点灯プログラムとなっている。  
以後このプログラムを基本プログラムとする。  

また、多色LEDを用いた信号機を模したLED点灯プログラム、myled2.cを信号プログラムとする。

# 開発環境:
Ubuntu20.04

Raspberry Pi 4  
ラズパイ３だと動かないと思われるため注意。

# 使用機器等
## OS系統
・Ubuntu20.04LTS(PC)

・Raspberry Pi 4([Ubuntu20.04マイクロSD内蔵](https://onl.tw/a45isMj)Copyright (c) 2021 Ryuich Ueda)

・LANケーブル

## 配線系統
### 基本プログラム
・[抵抗240Ω](https://onl.tw/hu2GyUC)×1

・[発光ダイオード(LED)](https://onl.tw/kVm3vah)×1

・ブレットボード

・ジャンパー線
#### 信号プログラム


# 配線
### 基本プログラム
ラズパイの２５ピンから抵抗、LED、GNDピンの順番に配線する。以下が今回使用した配線例である。

<img src="https://user-images.githubusercontent.com/79555986/146312253-9c89bbf7-3192-4e9a-b498-68832e0b7a2f.jpg" width="320px">

<img src="https://user-images.githubusercontent.com/79555986/146312261-7c2673ab-5f6a-4ce4-8418-89f8c606d8db.jpg" width="320px">

### 信号プログラム


# 基本的な動作：
### 基本プログラムの実行手順。
 ```
make myled.ko
 ```
 ```
sudo insmod myled.ko
 ```
 もしすでにあるというエラーが出た場合下のコードにより解決する。
 ```
sudo rmmod myled
 ```
 ```
sudo insmod myled.ko
 ```
 エラーが出なかった場合こちらから。
 ```
sudo chmod 666 /dev/myled0
 ```
点灯
 ```
echo 1 > /dev/myled0
 ```
 消灯
 ```
echo 0 > /dev/myled0
 ```
### 信号プログラムの実行手順。
もしすでにmyled.koなどが作成されている場合（LED点灯プログラムを行っていた場合）以下のクリーンから行ってください。

ない場合はとばして大丈夫です。

 ```
make clean
 ```
makeでも同じ動作が可能。
 ```
make myled2.ko
 ```
 ```
sudo insmod myled.ko
 ```
 もしすでにあるというエラーが出た場合下のコードにより解決する。
 ```
sudo rmmod myled
 ```
 ```
sudo insmod myled.ko
 ```
 エラーが出なかった場合こちらから。
 ```
sudo chmod 666 /dev/myled0
 ```
青信号変更
 ```
echo 1 > /dev/myled0
 ```
 赤信号変更
 ```
echo 0 > /dev/myled0
 ```
# デモ動画
### 基本プログラム

 https://youtu.be/JDr2gMlhLKQ 

### 信号プログラム


 
 # ライセンス

Copyright (c) 2021 Ryuich Ueda

> This program is free software; you can redistribute it and/or
> modify it under the terms of the GNU General Public License
> as published by the Free Software Foundation; either version 2
> of the License, or any later version.

> This program is distributed in the hope that it will be useful,
> but WITHOUT ANY WARRANTY; without even the implied warranty of
> MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
> GNU General Public License for more details.

> You should have received a copy of the GNU General Public License
> along with this program. If not, see http://www.gnu.org/licenses/.
