from Crypto.Util.number import *
import os
flag = os.environ.get("FLAG", "fakeflag")

p, q = getPrime(1024), getPrime(1024)
N = p * q

c = pow(bytes_to_long(flag.encode()), 0x10001, N)
gifts = [min(p % i, q % i) for i in sieve_base[:400]]

print(f"{c, gifts = }")
