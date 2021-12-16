# robot_system
Chiba Institute of Technology robot system for class

課題１のリポジトリ保管庫として使用。

# 開発環境:
Ubuntu20.04

Raspberry Pi 4
<span style="color: red; ">ラズパイ３だと動かないと思われるため注意。</span>

# 使用機器等
### OS系統
・Ubuntu20.04LTS(PC)

・Raspberry Pi 4([Ubuntu20.04マイクロSD内蔵](https://onl.tw/a45isMj)(c)Ryuich Ueda)

・LANケーブル

### 配線系統
・[抵抗240Ω×1](https://onl.tw/hu2GyUC)

・[発光ダイオード(LED)×1](https://onl.tw/kVm3vah)

・ブレットボード

・ジャンパー線


# 配線
ラズパイの２５ピンから抵抗、LED、GNDピンの順番に配線する。以下が今回使用した配線例である。


# 基本的な動作：
### ラズパイを用いたLED点灯プログラム。
 ```
make
 ```
 ```
sudo insmod myled.ko
 ```
 ```
sudo rmmod myled
 ```
 ```
sudo insmod myled.ko
 ```
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
