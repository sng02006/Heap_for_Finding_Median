# Heap_for_Finding_Median
-------------------------
## 개요
------
임의의 txt file의 첫 번째 숫자가 그 이후에 나올 숫자들의 개수를 나타내고 그 이후의 숫자들이 무작위로 설정되어있을 때, 첫 숫자를 제외한 나머지 숫자들의 중간값을 찾는 프로그램입니다.
Max Heap L과 Min Heap R을 만들고, L에 있는 모든 숫자는 R에 있는 모든 숫자보다 작으면서 이것이 유지되도록 file로부터 하나씩 넣습니다.
결국 언제든지 Root L을 뽑아내서 중간값을 찾아낼 수 있습니다.

## 주요 함수 설명
-------------
### Heap4Median_AddItem
-----------------------
새로운 item을 value
현재 heap을 구성하고 있는 원소의 개수가 짝수인 경우 Even, 홀수인 경우 Odd
heap L의 root인 L_Max, heap R의 root인 R_Min
 Condition			  |Even					|Odd
 :-------------------:|:-------------------:|:-------------------:
 L_Max = value = R_Min|input value in heap L|input value in heap R
 L_Max = value < R_Min|input value in heap L|input value in heap R
 L_Max < value = R_Min|input value in heap L|input value in heap R
 L_Max < value < R_Min|input value in heap L|input value in heap R
 value < L_Max		  |input value in heap L|move L_Max to heap R, input value in heap L
 R_Min < value		  |move R_Min to heap L, input value in heap R|input value in heap R
 
- Even일 때 1~5는 value를 L의 맨 마지막 원소 다음에 넣고, Reheap_Up_Max(L, (*numL))를 통해 다시 heap L의 root가 Max인 heap이 되도록 한다.
- Even일 때 6은 R_Min을 L의 맨 마지막 원소 다음에 넣고, value를 R의 root에 넣는다. Reheap_Up_Max(L, (*numL))를 통해 다시 heap L의 root가 Max인 heap이 되도록 하고, Reheap_Down_Min(R, 0, (*numR))를 통해 다시 heap R의 root가 Min인 heap이 되도록 한다.
- Odd일 때 1~4, 6은 value를 R의 맨 마지막 원소 다음에 넣고, Reheap_Up_Min(R, (*numR))를 통해 다시 heap R의 root가 Min인 heap이 되도록 한다.
- Odd일 때 5는 L_Max를 R의 맨 마지막 원소 다음에 넣고, value를 L의 root에 넣는다. Reheap_Up_Min(R, (*numR))를 통해 다시 heap R의 root가 Min인 heap이 되도록 하고, Reheap_Down_Max(L, 0, (*numL))를 통해 다시 heap L의 root가 Max인 heap이 되도록 한다.

![image01](https://user-images.githubusercontent.com/44752186/48952699-7311c280-ef86-11e8-8929-46355456d4e5.png)
![image02](https://user-images.githubusercontent.com/44752186/48952708-7dcc5780-ef86-11e8-9e5d-d063956b24f5.png)

- Reheap_Up_Max(int L[], int child)
child가 0이 아닐 때 parent = (child - 1) / 2를 설정하고, compare 함수를 통해 비교하여 L[child]가 L[parent]보다 큰 경우 swap 함수를 통해 값을 교환하고, 값이 바뀐 parent를 다시 Reheap_Up_Max(L, parent)로 child가 parent보다 작거나, parent가 0이 될 때까지 실행한다. child가 parent보다 작거나, parent가 0이 되면 L의 heapify가 끝나고, Reheap_Up_Max(int L[], int child)가 종료된다.

- Reheap_Up_Min(int R[], int child)
child가 0이 아닐 때 parent = (child - 1) / 2를 설정하고, compare 함수를 통해 비교하여 L[child]가 L[parent]보다 작은 경우 swap 함수를 통해 값을 교환하고, 값이 바뀐 parent를 다시 Reheap_Up_Min(R, parent)로 child가 parent보다 크거나, parent가 0이 될 때까지 실행한다. child가 parent보다 크거나, parent가 0이 되면 R의 heapify가 끝나고, Reheap_Up_Min(int R[], int child)가 종료된다.

- Reheap_Down_Max(int L[], int parent, int max)
child1 = parent * 2 + 1, child2 = parent * 2 + 2를 설정하고, L의 index인 child1과 child2가 L의 개수인 max보다 작을 때, 또는 child1이 max보다 작고 child2가 max보다 크거나 같을 때만 swap 한다.
child1과 child2가 L의 개수인 max보다 작을 때, child1이 child2와 parent보다 큰 경우 child1과 parent를 swap하고, child1에 대해서 다시 Reheap_Down_Max를 실행한다. child2가 child1보다 크거나 같고 child2가 parent보다 큰 경우 child2와 parent를 swap하고, child2에 대해서 다시 Reheap_Down_Max를 실행한다. 만약 child1과 child2 모두 parent보다 작은 경우 swap 되지 않고 Reheap_Down_Max(int L[], int parent, int max)가 종료된다.
child1이 max보다 작고 child2가 max보다 크거나 같을 때, L[child2]는 비어있는 원소이므로 고려하지 않고 child1이 parent보다 크다면 swap하고, child1에 대해 eheap_Down_Max(int L[], int parent, int max)를 실행한다. 만약 child1이 parent보다 작거나 같다면 swap 되지 않고 Reheap_Down_Max(int L[], int parent, int max)가 종료된다.

- Reheap_Down_Min(int R[], int parent, int max)
child1 = parent * 2 + 1, child2 = parent * 2 + 2를 설정하고, R의 index인 child1과 child2가 L의 개수인 max보다 작을 때, 또는 child1이 max보다 작고 child2가 max보다 크거나 같을 때만 swap 한다.
child1과 child2가 R의 개수인 max보다 작을 때, child1이 child2와 parent보다 작은 경우 child1과 parent를 swap하고, child1에 대해서 다시 Reheap_Down_Min를 실행한다. child2가 child1보다 작거나 같고 child2가 parent보다 작은 경우 child2와 parent를 swap하고, child2에 대해서 다시 Reheap_Down_Min를 실행한다. 만약 child1과 child2 모두 parent보다 큰 경우 swap 되지 않고 Reheap_Down_Min(int R[], int parent, int max)이 종료된다.
child1이 max보다 작고 child2가 max보다 크거나 같을 때, R[child2]는 비어있는 원소이므로 고려하지 않고 child1이 parent보다 작다면 swap하고, child1에 대해 Reheap_Down_Min(int R[], int parent, int max)을 실행한다. 만약 child1이 parent보다 크거나 같다면 swap 되지 않고 Reheap_Down_Min(int L[], int parent, int max)가 종료된다.

