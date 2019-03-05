usage:
 ./lem-in < "test_name_file"
4
3 2 2
##start
start 4 0
##end
end 4 6
4 0 4
1 4 2
2 4 4
5 3 4
6 8 4
start-1
3-4
2-4
1-5
6-5
1-2
3-start
start-end

L1-end [0m
L2-end [0m
L3-end [0m
L4-end [0m

If you want colorful output, enter '-c' after name of file
If you want to see all possible ways, enter '-w' after name of file
If you want to see amount of lines in output, enter '-l' after name of file
Process:         lem-in [9619]
Path:            /Users/ychufist/lem-in 6.14.32 PM/lem-in
Load Address:    0x10680b000
Identifier:      lem-in
Version:         0
Code Type:       X86-64
Parent Process:  zsh [2297]

Date/Time:       2019-03-05 16:31:08.422 +0200
Launch Time:     2019-03-05 16:31:08.174 +0200
OS Version:      Mac OS X 10.13.3 (17D47)
Report Version:  7
Analysis Tool:   /Applications/Xcode.app/Contents/Developer/usr/bin/leaks
Analysis Tool Version:  Xcode 9.2 (9C40b)
----

leaks Report Version:  2.0
Process 9619: 194 nodes malloced for 14 KB
Process 9619: 0 leaks for 0 total leaked bytes.
