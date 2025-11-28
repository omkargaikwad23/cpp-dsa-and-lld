/*
You have a file system represented as a Python dictionary. Each node is either a file or a directory. Directories can contain other directories or files as children. For example:
fs = { 
    1: { type=directory, name=“root", children=[2, 3] }, 
    2: { type=directory, name=“dir", children=[4, 5] }, 
    4: { type=file, name=“file1", size=100 }, 
    5: { type=file, name=“file2", size=200 }, 
    3: { type=file, name=“file3", size=300 } 
}
Tasks:
Write a function get_size() that returns the total size of for a key
How to optimise the size calculation with caching if needed
Discussion about what is expected from a typical filesystem. I could come up with the following -
No cycles: a directory cannot include itself directly or indirectly
Every file belongs to at least one directory
No two directories share the same child
No directory contains a non-existent child key

*/