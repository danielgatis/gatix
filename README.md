What is Gatix?
=================
Gatix is a basic and small UNIX-like operating system.


How can I build?
---------------------
Set up environment on debian-like:
```bash
sudo apt-get install build-essential nasm git cmake xorriso qemu
```

Clone a copy of the main git repo by running:
```bash
git clone git://github.com/danielgatis/gatix.git
```

On **root directory** run:
```bash
sh scripts/build.sh
```

How can I run?
---------------------
On **root directory** run:
```bash
sh scripts/run.sh
```

How can I debug?
---------------------
On **root directory** run:
```bash
sh scripts/debug.sh
```

At other terminal session on **root directory** run:
```bash
gdb -symbols build/kernel/kernel.bin.sym
```

On **gdb**:
```
 (gdb) target remote localhost:1234
 (gdb) break <foobar>
 (gdb) continue
```

