s=input()
root2=open("root2","r").read()
print("length of s is ",len(s))
print("correct upto :")
for i in range(len(s)):
    if (s[i]!=root2[i]):
        print(i)
        break
else:
    print(len(s))




