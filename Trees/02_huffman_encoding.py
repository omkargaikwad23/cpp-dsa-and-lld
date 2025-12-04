from heapq import *
from collections import *

class Node:
    def __init__(self,val=0,char=""):
        self.val=val
        self.char=char
        self.left=None
        self.right=None
    def __lt__(self,other): # a<b
        return self.val < other.val

class HuffmanTree:
    def encoding(self,arr): # arr=[(val,char)]
        n=len(arr)
        nodes=[Node(arr[i][0],arr[i][1]) for i in range(n)]
        
        heapify(nodes)
        while len(nodes)>1:
            x=heappop(nodes)
            y=heappop(nodes)
            curr=Node(x.val+y.val)
            curr.left=x
            curr.right=y
            heappush(nodes,curr)
        return nodes[0]
    
    def decoding(self,root):
        self.dfs(root,"")
    
    def dfs(self,root,prefix):
        if not root.left and not root.right:
            print(root.char,root.val,prefix)
            return
        if root.left:
            self.dfs(root.left,prefix+"0")
        if root.right:
            self.dfs(root.right,prefix+"1")
        
h=HuffmanTree()
text = "aaabbccccd"
d = defaultdict(int)
for i in text:
    d[i] += 1

arr=[]
for i in d.items():
    ch, freq = i
    arr.append([freq, ch])

# print(arr)

root=h.encoding(arr)
h.decoding(root)

'''
c 4 0
a 3 10
d 1 110
b 2 111
'''