There are n machines and m jobs. Each work consists of si stages.
A stage is characterized by a pair of (k, t) numbers, where k is the machine number,
and t is the duration of the stage. For each work, the order of stages is strictly specified. 
Any stage can be paused at any moment and continued later from the same moment. At any given time, 
any job can only be performed on one machine, and any machine can only perform one job. 
It is necessary to make a schedule so that all the work is done in the minimum time.


`Input:`

On the first line write the numbers n and m separated by a space. The next m lines first contain number si, followed by si pairs (k, t) of integers (1 ≤ k ≤ m, 1 ≤ t ≤ 109).

`Output:`

Output the minimal execution time.

# Example
`input.txt:`
```
4 2
3 1 1 2 1 3 3
4 1 1 2 3 4 1 3 1
```
`output.txt:`
```
7
```
