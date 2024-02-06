from time import perf_counter as pc

from time import sleep

import numpy as np

GOAL_STATE = [[]]
GLOBAL_STATE_DICT = {}
N = 0
total_nodes = 0


class Node:
    def __init__(self, state, manhattan, zero_pos):
        self.state = state
        self.heuristic = manhattan
        self.zero_pos = zero_pos

    def __str__(self):
        return f"state=\n{self.state}\nheuristic={int(self.heuristic)}"

    def __eq__(self, other):
        return np.array_equal(self.state, other.state)

    def __repr__(self):
        return f"state=\n{self.state}\nheuristic={int(self.heuristic)}"

    def __hash__(self):
        return hash(self.state.tobytes())


def customSort(node):
    return node.heuristic


def nextnodes(node):
    global total_nodes
    
    zero = node.zero_pos

    r, c = map(int, zero)
    directions = ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1))
    nodes = []
    for direction in directions:
        if 0 <= direction[0] < N and 0 <= direction[1] < N:
            total_nodes += 1
            
            tmp = np.copy(node.state)
            goal = GLOBAL_STATE_DICT[tmp[direction]]

            tmp[direction], tmp[zero] = tmp[zero], tmp[direction]

            dir_goal_distance = manhattan_distance(direction, goal)
            goal_zero_distance = manhattan_distance(goal, (r, c))
            
            # print("dir goal dis:", dir_goal_distance)
            # print("goal zero dis:", goal_zero_distance)
            # print("node heur - dir + goal", node.heuristic - dir_goal_distance + goal_zero_distance)

            nodes.append(Node(tmp, node.heuristic - dir_goal_distance + goal_zero_distance, direction))
            
            # print("nodes len", len(nodes))
            # sleep(0.25)
    return sorted(nodes, key=customSort)


def manhattan_distance(a, b):
    return abs(b[0] - a[0]) + abs(b[1] - a[1])


def manhattan_heuristic(state):
    distance = 0
    for i in range(N):
        for j in range(N):
            num = state[i][j]
            if num != GOAL_STATE[i][j] and num != 0:
                goal = GLOBAL_STATE_DICT[num]
                distance += manhattan_distance((i, j), goal)
    return distance

t=0
def search(path, g, threshold):
    global t
    # print("\rthreshold:", threshold, t, end='')
    t+=1
    node = list(path.keys())[-1]

    f = g + node.heuristic

    if f > threshold:
        return f
    if np.array_equal(node.state, GOAL_STATE):
        return True

    minimum = float('inf')
    for n in nextnodes(node):
        if n not in path:
            path[n] = None
            # print("n is", n)
            tmp = search(path, g + 1, threshold)
            if tmp == True:
                return True
            if tmp < minimum:
                minimum = tmp
            path.popitem()

    return minimum

def solve(initial_state):
    t=0
    zero = np.where(initial_state == 0)
    initial_node = Node(initial_state, manhattan_heuristic(initial_state), zero)
    threshold = initial_node.heuristic
    # The dictionary keeps insertion order since Python 3.7 so it can be used as a queue
    path = {initial_node: None}
    while 1:
        tmp = search(path, 0, threshold)
        if tmp == True:
            print("\nGOOD!")
            return path.keys()
        elif tmp == float('inf'):
            print("\nWRONG!")
            return False
        threshold = tmp
        print("\rthreshold in solve", threshold, t, end='')
        t+=1



def define_goal_state(n):
    global GOAL_STATE
    global N
    global GLOBAL_STATE_DICT

    # m = [[0] * n for i in range(n)]
    # dx, dy = [0, 1, 0, -1], [1, 0, -1, 0]
    # x, y, c = 0, -1, 1
    # for i in range(n + n - 2):
    #     for j in range((n + n - i) // 2):
    #         x += dx[i % 4]
    #         y += dy[i % 4]
    #         m[x][y] = c
    #         c += 1
    
    m = [[1, 2, 3, 4],
         [5, 6, 7, 8],
         [9, 10, 11, 12],
         [13, 14, 15, 0]]
    
    # m = [[1, 2, 3],
    #      [4, 5, 6],
    #      [7, 8, 0]]

    GOAL_STATE = np.array(m)
    N = len(GOAL_STATE)
    GLOBAL_STATE_DICT = {m[r][c]: (r, c) for r in range(N) for c in range(N)}


tests = {#'3x3': np.array([[8, 7, 3], [4, 1, 2], [0, 5, 6]]),
        #  '4x4': np.array([[13, 2, 10, 3],
        #                         [1, 12, 8, 4],
        #                         [5, 0, 9, 6],
        #                         [15, 14, 11, 7]])
        # '4x4': np.array([[13, 2, 10, 3],
        #                 [1, 12, 8, 4],
        #                 [5, 0, 9, 6],
        #                 [15, 14, 11, 7]])}
        
        # '3x3': np.array([[1, 2, 3], [4, 6, 5], [8, 7, 0]]),}

        # '4x4': np.array([[3, 4, 11, 12],
        #                 [0, 7, 13, 14],
        #                 [9, 2, 6, 5],
        #                 [15, 1, 8, 10]])}
        
        '4x4': np.array([[10, 12, 8, 4],
                        [11, 15, 14, 13],
                        [1, 3, 5, 9],
                        [0, 2, 7, 6]])}
        



for name, puzzle in tests.items():
    define_goal_state(len(puzzle))
    print('Puzzle:\n', puzzle)
    t0 = pc()
    path = solve(puzzle)
    t1 = pc()
    
    # for i in path:
    #     print(i)
        
    print(f'{name} depth:{len(path)} runtime:{round(t1 - t0, 3)} s')
    print("total nodes:", total_nodes)
    