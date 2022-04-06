s=input()
root2=open("pi.txt","r").read()
print("length of s is ",len(s))
print("correct upto :")
# print(root2[78])
for i in range(len(s)):
    print(i)
    if (s[i]!=root2[i]):
        # print(i)
        
        print("input value at position: ",s[i])
        print("actual value at position: ",root2[i])
        break
else:
    print(len(s))




