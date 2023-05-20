`There are n parts and m machines. For each part, the execution time on each machine and the sequence of passing through the machines for each part are known. 
It is necessary to determine the order of processing the parts, such that the last part is processed as early as possible.`

Notes:

- In the sequence of passing through the machines, no machine is encountered more than once for a part.
- It is not allowed to stop a machine before finishing the processing of the current part.
Input:
The first line contains two integers, n and m (1 ≤ n ≤ 3000, 1 ≤ m ≤ 300). 
Then n blocks follow. Each i-th block starts with a line containing the number ki of stages in the processing of the i-th part. 
Then ki lines follow, specifying the sequence of passing through the machines for the i-th part. 
Each line contains two positive integers - the machine number and the processing time. 
The processing time does not exceed 10^12.

Output:
The first line should output the completion time of the last part's processing. 
Then output m lines, each containing n numbers. 
In the i-th line, the j-th number corresponds to the time when the i-th machine
will start processing the j-th part, or it is 0 if the j-th part does not need to be processed on the i-th machine. 
The time spent should not exceed the optimal time by more than `(n + 1) / 2` times.
