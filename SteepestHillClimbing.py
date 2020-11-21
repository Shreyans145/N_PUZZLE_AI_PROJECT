import random
import time

tag = False

def sol_steepestHillClimbing(arr):
    x = 100
    c = 0

    while True:
        c += 1
        collision_number = get_Manhattan_Distance(arr)
        # print c, collision_number
        if collision_number == 0:
            return arr

        arr = steepest_HillClimbing(arr)
        
        global tag
        
        if tag:
            return arr
        
        if(c >= x):
            tag = True
            return arr


def steepest_HillClimbing(arr):
    
    for i in range(len(arr)):
        if arr[i] == 0:
            break
    
    distance_Board = dict()
    
    if i >= 3:
        up_board = list(arr)
        up_board[i] = arr[i-3]
        up_board[i-3] = 0
        distance_Board[i-3] = get_Manhattan_Distance(up_board)
    
    if i%3 != 0:
        left_board = list(arr)
        left_board[i] = arr[i-1]
        left_board[i-1] = 0
        distance_Board[i-1] = get_Manhattan_Distance(left_board)
    
    if (i+1)%3 != 0:
        right_board = list(arr)
        right_board[i] = arr[i+1]
        right_board[i+1] = 0
        distance_Board[i+1] = get_Manhattan_Distance(right_board)

    if i < 6:
        down_board = list(arr)
        down_board[i] = arr[i+3]
        down_board[i+3] = 0
        distance_Board[i+3] = get_Manhattan_Distance(down_board)
    
    d = get_Manhattan_Distance(arr)
    
    for j in distance_Board.items():
        if j[1] <= d:
            d = j[1]
    
    shortest_DistancePoints = list()

    for j in distance_Board.items():
        if j[1] == d:
            shortest_DistancePoints.append(j[0])
    
    if len(shortest_DistancePoints) == 0:
        global tag
        tag = True
        return arr
    
    random.shuffle(shortest_DistancePoints)
    arr[i] = arr[shortest_DistancePoints[0]]
    arr[shortest_DistancePoints[0]]= 0
    return arr

def get_Manhattan_Distance(arr):
    val = 0

    for i in range(len(arr)):
        val +=  abs(i%3 - arr[i]%3) + abs(i/3 - arr[i]/3)
    
    return val
    
def main():
    name = "N_Puzzle_steepestHillClimbing"
    initial_Time = time.process_time()
    total_Case = 0
    success_Case = 0
    
    res = name + " result:\n\n"

    with open("N_Puzzle_Test.txt", "r") as y:
        for line in y:
            print("case: ", total_Case)
            global tag
            tag = False
            total_Case += 1
            
            arr = list()
            
            for c in line.split():
                arr.append(int(c))
            
            arr = sol_steepestHillClimbing(arr)
            
            if tag:
                res += "Failed!"
            else:
                success_Case += 1
                for c in range(len(arr)):
                    res += str(arr[c]) + " "
            
            res += "\n"
    
    finish_Time = time.process_time()
    res += "\nTotal time: " + str(finish_Time - initial_Time) + '\n'
    res += "Total case number: " + str(total_Case) + ", Success case number: " + str(success_Case) + '\n'
    res += "Success rate: " + str(success_Case / float(total_Case)) + '\n'
    
    f = open(name + '.txt', 'w')
    f.write(res)
    f.close()
        
if __name__ == '__main__':
    main()