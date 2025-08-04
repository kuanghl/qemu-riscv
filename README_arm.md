### 介绍.

QEMU + vscode单步调试ARM32代码.

- [QEMU simulation with hardware boards](https://hackmd.io/@MarconiJiang/qemu_hardware): QEMU模拟ARM硬件板卡。


```sh
# 1. install/arm目录下为qemu工具链的二进制可执行文件
# 2. 调试配置为system/user目录下的.vscode
# 3. 将.vscode文件夹拷贝到根目录替换，则调试对应文件夹下的子项目
# 4. 打上断点，运行调试即可触发编译和调试
```

### 区别.

- quemu-system-arm vs qemu-arm:

| **工具**         | **模式**       | **定位**                                                                 | **典型用途**                     |
|------------------|---------------|-------------------------------------------------------------------------|----------------------------------|
| **`qemu-system-arm`** | System Mode    | 模拟完整的 ARM 计算机硬件（CPU、内存、外设等），运行完整操作系统（如 Linux） | 在 x86 主机上启动 ARM 虚拟机      |
| **`qemu-arm`**       | User Mode      | 仅模拟 ARM 指令集环境，直接运行 ARM 架构的**单个程序**（需与主机同操作系统，如 Linux） | 在 x86 Linux 上运行 ARM 可执行文件 |


| **特性**               | **`qemu-system-arm`**                  | **`qemu-arm`**                     |
|------------------------|---------------------------------------|------------------------------------|
| **多核支持**           | ✅ 支持（如 `-smp 4` 模拟 4 核）       | ❌ 仅单进程                        |
| **外设仿真**           | ✅ 网卡、USB、GPU 等完整设备树 | ❌ 无硬件交互能力                  |
| **启动完整 OS**        | ✅ 可运行 Linux、Android 等         | ❌ 仅运行用户程序                 |
| **调试支持**           | ✅ 内置 GDB 调试、QMP 管理协议 | ✅ 支持用户态调试（如 `-g` 选项） |
| **典型场景**           | - 嵌入式系统开发<br>- 多平台 CI/CD 测试<br>- 安全研究（固件模拟） | - 跨架构编译测试<br>- 单程序移植验证 |

### 编译测试.

```sh
# dependences
# for the GNU toolchain
sudo apt update
sudo apt install gcc-arm-none-eabi
sudo apt install libglib2.0-dev
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/lib/x86_64-linux-gnu/pkgconfig/

# (备选跳过)Manual install: https://learn.arm.com/install-guides/gcc/arm-gnu/
wget https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi.tar.xz
tar xJf arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi.tar.xz -C $HOME
echo 'export PATH="$PATH:$HOME/arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi/bin"' >> ~/.bashrc
source ~/.bashrc

#  https://git.qemu.org/git/qemu.git
# https://github.com/qemu/qemu.git
git clone git@github.com:qemu/qemu.git --depth=1

# configure and build qemu
cd qemu
./configure --help
./configure --target-list=arm-softmmu,arm-linux-user --prefix=$(cd ..; pwd)/install/arm32 --enable-tools --enable-debug
make -j$(nproc)
make install

# verify
export PATH=$(pwd)/install/arm32/bin:${PATH}
arm-none-eabi-gcc --version
arm-none-eabi-g++ --version
qemu-arm --version
qemu-system-arm -machine help
```