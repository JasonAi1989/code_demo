#!/home/eaizhao/.local/bin/python3

def b_search(array, t):
    head=0
    tail=len(array)-1
    res = -1

    while(head <= tail):
        if(head == tail):
            if(array[head] == t):
                res = head
            else:
                res = -1
            break

        mid = (tail - head)//2 + head
        if(array[mid] == t):
            res = mid
            break
        elif(array[mid] < t):
            head = mid + 1
        else:
            tail = mid - 1

    return res

a=[1, 5, 22, 33, 44, 55, 66, 77, 88, 99]
print(b_search(a, 44))
print(b_search(a, 99))
print(b_search(a, 100))
print(b_search(a, -2))

