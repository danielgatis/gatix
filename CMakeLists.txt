cmake_minimum_required (VERSION 2.8)
PROJECT (gatix)

ADD_SUBDIRECTORY (kernel)
ADD_SUBDIRECTORY (modules)

ADD_CUSTOM_TARGET ( iso
  COMMENT "Building bootable ISO img"
  COMMAND mkdir -p iso/boot/grub
  COMMAND mkdir -p iso/modules
  COMMAND cp ../grub/grub.cfg iso/boot/grub
  COMMAND cp kernel/kernel.bin iso/boot/kernel.bin
  COMMAND cp modules/**/*.a iso/modules
  COMMAND grub-mkrescue -o gatix.iso iso >/dev/null 2>&1
)
