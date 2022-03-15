from functools import cmp_to_key

def cmp(A, N, M):
    value = (A[1] - N[1]) * M[0] + (N[0] - A[0]) * M[1] + (A[0] * N[1] - N[0] * A[1])
    if value > 0:
        return 1
    if value < 0:
        return -1
    return 0

def make(points): #
    
    base = min(points)
    del points[points.index(base)]
    
    points = sorted(points, key = cmp_to_key(lambda x, y: cmp(base, y, x)))
    points = [base] + points
    
    stack = [points[0], points[1]]
    
    for i in range(2, len(points)):
        while cmp(stack[-2], stack[-1], points[i]) < 0:
            stack.pop()
        stack.append(points[i])
    
    return stack
