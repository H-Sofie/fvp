from fuzzywuzzy import fuzz, process

f = open("merge2.txt", "r")
s1 = str()
s2 = str()
cnt = 0
dict1 = {}
lndict = {}
list1 = []
tote = 0
for line in f.readlines():
    if cnt == 0:
        s1 = line.strip()
        list1.append(s1)
        cnt = 1
    else:
        s2 = line.strip()
        dict1[s1] = s2
        tote = tote+1
        cnt = 0
f.close()
print("read done, total " + str(tote) + " entries")

f = open("rep2.txt", "r")
f2 = open("result2.txt", "a")
f3 = open("rep2log.txt", "a")
tot = 6984
cnum = 1
for line in f.readlines():
    if cnt == 0:
        s1 = line.strip()
        cnt = 1
    else:
        s2 = line.strip()
        tmp = process.extractOne(s2, list1)
        # f2 = open("result2.txt", "a+")
        f2.write(s1 + "\n")
        f2.write(dict1[tmp[0]] + "\n")
        # f2.close()
        ll = str(cnum) + " / " + str(tot) + " processed, line " + s1 + ", ratio " + str(tmp[1])
        ll = ll + ", text " + s2 + ", total " + str(tote) + " entries"
        print(ll)
        f3.write(ll + "\n")
        cnum = cnum+1
        cnt = 0
        if cnum >= 10:
            break
f.close()
f2.close()
f3.close()

