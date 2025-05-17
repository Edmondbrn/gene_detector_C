import time

liste = []
start = time.time()
for i in range(100000):
    liste.append(i)


print(time.time() - start)