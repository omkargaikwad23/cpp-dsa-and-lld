/*
https://leetcode.com/discuss/post/3526286/google-telephonic-interview-question-by-lpwxa/

https://leetcode.com/discuss/post/762690/google-telephone-interview-coding-questi-wn25/

CityA and CityB where CityA(i) -> is earnings of consultant on day i, see what path consultant should take to get maximum earningas.

if Consultant is travelling from city A to city B -> earnings =0
you can start from either CityA or CityB

exam:
CityA : [23,4,5,10}
CityB : [21,1,10,100]

answer: "ATBB"  

Use Dijkstra's algo
*/