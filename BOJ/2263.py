import sys
input = sys.stdin.readline
sys.setrecursionlimit(10 ** 5)

n = int(input())
inorder_input = list(map(int, input().split()))
inorder = {}
for i in range(len(inorder_input)):
    inorder[inorder_input[i]] = i
postorder_input = list(map(int, input().split()))
postorder = {}
for i in range(len(postorder_input)):
    postorder[postorder_input[i]] = i

def solution(arr1, arr2):
    if arr1[0] == arr1[1] and arr2[0] == arr2[1]:
        print(inorder_input[arr1[0]], end = ' ')
        return
    inorder_root = inorder[postorder_input[arr2[1]]]
    print(postorder_input[arr2[1]], end = ' ')
    if arr1[0] != inorder_root:
        arr1_left = [arr1[0], inorder_root - 1]
        arr2_left = [arr2[0], arr2[0] + inorder_root - 1 - arr1[0]]
        solution(arr1_left, arr2_left)
    if arr1[1] != inorder_root:
        arr1_right = [inorder_root + 1, arr1[1]]
        arr2_right = [arr2[0] + inorder_root - arr1[0], arr2[1] - 1]
        solution(arr1_right, arr2_right)
solution([0, n - 1], [0, n - 1])

# 딕셔너리로 값을 저장한다.
# 입력된 값에 대하여
# inorder_input : index -> 값
# inorder : 값 -> index
# arr은 index를 저장