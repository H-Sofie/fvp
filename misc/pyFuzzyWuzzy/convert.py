f1 = open("merge2.txt", "r", encoding="utf8")
f2 = open("merge2c.txt", "a", encoding="utf8")
cnt = 0
for line in f1.readlines():
    if cnt == 0:
        s1 = line.strip()
        s1.encode('utf8')
        f2.write(s1 + "\n")
        cnt = 1
    else:
        s2 = line.strip()
        f2.write(s2 + "\n")
        cnt = 0
f1.close()

