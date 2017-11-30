#!/bin/sh

export ARCH=arm64
export LIBS=-ldl
export CROSS_COMPILE="/proj/spr/toolchain/aarch64-mvista-linux/sysroots/x86_64-oesdk-linux/usr/bin/aarch64-mvista-linux"
export CC="$CROSS_COMPILE/aarch64-mvista-linux-gcc --sysroot=/proj/spr/toolchain/aarch64-mvista-linux/sysroots/aarch64-mvista-linux"
export LD="$CROSS_COMPILE/aarch64-mvista-linux-ld --sysroot=/proj/spr/toolchain/aarch64-mvista-linux/sysroots/aarch64-mvista-linux"
export RANLIB="$CROSS_COMPILE/aarch64-mvista-linux-ranlib --sysroot=/proj/spr/toolchain/aarch64-mvista-linux/sysroots/aarch64-mvista-linux"
export AR="$CROSS_COMPILE/aarch64-mvista-linux-ar"
export CCLD="$CROSS_COMPILE/aarch64-mvista-linux-ld --sysroot=/proj/spr/toolchain/aarch64-mvista-linux/sysroots/aarch64-mvista-linux"
#export CROSS_COMPILE="/proj/spr/toolchain/aarch64-mvista-linux/sysroots/x86_64-oesdk-linux/usr/bin/aarch64-mvista-linux/aarch64-mvista-linux"


#./configure --host i686 --prefix=/workspace/git/eliudai/Spitfire_Crius/IpSec/StrongSwan/install

#./configure --host=aarch64-mvista-linux --enable-eap-mschapv2 --enable-eap-tls --enable-eap-ttls --enable-eap-peap --enable-eap-md5 --enable-eap-tnc --enable-eap-dynamic --enable-eap-radius --enable-xauth-eap --enable-xauth-pam  --enable-dhcp  --enable-openssl  --enable-addrblock --enable-unity --enable-certexpire --enable-radattr --enable-openssl --disable-gmp

make
