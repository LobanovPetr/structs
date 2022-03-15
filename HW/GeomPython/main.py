from func import make

class line:
    A = 0
    B = 0
    C = 0
    def __init__(self, point1, point2):
        self.A = (point1[1] - point2[1])
        self.B = (point2[0] - point1[0])
        self.C = (point1[0] * point2[1] - point1[1] * point2[0])
    def dist(self, point):
        return (self.A * point[0] + self.B * point[1] + self.C)
    def print_line(self):
        print(self.A, self.B, self.C)


def __main__():
    point1 = [[0, 0], [1, 4], [4, 2], [6, -1], [0, 4], [2, 0], [2, 4], [3, -1], [1, -2]]
    points = []

    print("Enter number of points")

    try:
        n = int(input())
    except:
        print("Incorrect data1")
        return
        
    if (n < 3):
        print("Incorrect data2")
        return
    print("Enter the points")
    for i in range(n):
        try:
            point = list(map(int, input().split()))
            if (len(point) != 2):
                print("Incorrect data3")
                return
            points.append(point)
        except:
            print("Incorrect data3")
            return
    i = 1
    while (i < n and points[0] == points[i]):
        i += 1
    if (i == n):
        print("All points have the same coordinates")
        return
    
    l = line(points[0], points[i])
    flag = 1
    flag = 0
    for i in range(1, n):
        if l.dist(points[i]) != 0:
            flag = 1
    if flag == 0:
        print("The point lie on the one line")
        return
        
    ans = make(points)
    print(*ans)

__main__()
