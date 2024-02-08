import sys
input = sys.stdin.readline

S = 0
def add(x):
    global S
    S |= (1 << x)

def remove(x):
    global S
    S &= ~(1 << x)

def check(x):
    global S
    if S | (1 << x) == S:
        print(1)
    else:
        print(0)

def toggle(x):
    global S
    S ^= (1 << x)

def all():
    global S
    S = (1 << 21) - 1

def empty():
    global S
    S = 0

count = int(input())
for i in range(count):
    do = list(input().split())
    if do[0] == "add":
        add(int(do[1]))
    if do[0] == "remove":
        remove(int(do[1]))
    if do[0] == "check":
        check(int(do[1]))
    if do[0] == "toggle":
        toggle(int(do[1]))
    if do[0] == "all":
        all()
    if do[0] == "empty":
        empty()