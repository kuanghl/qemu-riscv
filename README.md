### 介绍.

QEMU + vscode单步调试RISCV32代码.

```sh
# 1. install/rv32i目录下为riscv-gnu-toolchain/qemu工具链的二进制可执行文件
# 2. 调试配置为system/user目录下的.vscode
# 3. 将.vscode文件夹拷贝到根目录替换，则调试对应文件夹下的子项目
# 4. 打上断点，运行调试即可触发编译和调试
```

### 区别.

- quemu-system-riscv32 vs qemu-riscv32:

| 特性              | `qemu-system-riscv32` | `qemu-riscv32`       |
| --------------- | --------------------- | -------------------- |
| 模拟层级            | 系统级（CPU + 外设 + 内存）    | 用户态（仅 CPU 指令 + 系统调用） |
| 是否需内核/固件        | 是（如 Linux 或 OpenSBI）  | 否                    |
| 是否支持裸机程序        | 支持                    | 不支持                  |
| 是否支持外设          | 支持（串口、时钟、VirtIO 等）    | 不支持                  |
| 是否支持 `-machine` | 支持                    | 不支持                  |
| 是否支持 `rdcycle`  | 支持                    | 不支持（用户态不可访问 CSR）     |

### 编译测试.

```sh
# dependences
# for the GNU toolchain
sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev
# This is used by GDB so can run a dashboard script
sudo apt-get install python-dev-is-python3 # python-dev
# The following may not be necessary on 20.04.  But my tests included it.
sudo apt install ninja-build libglib2.0-dev libpixman-1-dev
pip3 install tomli sphinx sphinx_rtd_theme
sudo apt install libglib2.0-dev
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/lib/x86_64-linux-gnu/pkgconfig/

#  https://git.qemu.org/git/qemu.git
# https://github.com/qemu/qemu.git
git clone git@github.com:qemu/qemu.git --depth=1

# https://github.com/riscv-collab/riscv-gnu-toolchain.git
git clone git@github.com:riscv-collab/riscv-gnu-toolchain.git --depth=1

# configure and build gcc & friends
cd riscv-gnu-toolchain
git submodule init
git submodule update
./configure --prefix=$(cd ..; pwd)/install/rv32i --with-arch=rv32i --with-multilib-generator="rv32i-ilp32--;rv32ima-ilp32--;rv32imafd-ilp32--"
make -j$(nproc)

# configure and build qemu
cd qemu
./configure --target-list=riscv32-softmmu,riscv64-softmmu,riscv32-linux-user,riscv64-linux-user --prefix=$(cd ..; pwd)/install/rv32i --enable-tools --enable-debug
make -j$(nproc)
make install

# verify
export PATH=$(pwd)/install/rv32i/bin:${PATH}
qemu-system-riscv32 --version
qemu-system-riscv32 -machine help
riscv32-unknown-elf-as --version
riscv32-unknown-elf-gcc --version

# run in qemu system
qemu-system-riscv32 -machine virt -nographic -kernel main.elf
qemu-riscv32 main.elf
# 在终端按Ctrl-A再按X即可退出

# 更改运行频率，导出当前设备树，更改后重新编译设备树，引用新的dtb
qemu-system-riscv32 -machine virt,dumpdtb=virt.dtb -bios none -machine dumpdtb=virt.dtb
dtc -I dtb -O dts virt.dtb > virt.dts
# 更改timebase-frequency = <0x989680>; /* 10MHz */ --> timebase-frequency = <0x5f5e100>;   /* 100 MHz */
dtc -I dts -O dtb virt.dts -o virt-100m.dtb
qemu-system-riscv32 -machine virt -nographic -bios none -kernel main.elf -dtb virt-100m.dtb
```


### 性能测试.

- rdtime计算时间公式如下:

$$
t(ms)=\frac{ticks}{timebase\_CPU\_frequency}\times 1000
$$

```c
#define MTIME_ADDR  0x200BFF8
uint32_t get_time(void) 
{
    volatile uint32_t *mtime = (uint32_t*)MTIME_ADDR;
    return *mtime;
}

// eg:
// timebase_CPU_frequency = 10MHz= 10000000Hz
double ticks = (double)(get_time() - start_time);
double ms = ticks / 10000000.0 * 1000.0;
```