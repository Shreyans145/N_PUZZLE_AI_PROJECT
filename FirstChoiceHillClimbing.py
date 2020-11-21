import time
import random

tag = False

def sol_RandomHillClimbing(arr):
    x = 500000
    c = 0
    while True:
        distance = get_Manhattan_Distance(arr)
        if distance == 0:
            return arr
        arr = Random_HillClimbing(arr)
        c += 1
        if(c >= x):
            global tag
            tag = True
            return arr

def Random_HillClimbing(arr):
    for i in range(len(arr)):
        if arr[i] == 0:
            break
    
    while True:
        x = random.randint(0,4)
        
        if x == 0:
            if i >= 3:
                up_Board = list(arr)
                up_Board[i] = arr[i-3]
                up_Board[i-3] = 0
                return up_Board
        
        elif x == 1:
            if i < 6:
                down_Board = list(arr)
                down_Board[i] = arr[i+3]
                down_Board[i+3] = 0
                return down_Board
        
        elif x == 2:
            if i%3 != 0:
                left_Board = list(arr)
                left_Board[i] = arr[i-1]
                left_Board[i-1] = 0
                return left_Board
        else:    
            if (i+1)%3 != 0:
                right_Board = list(arr)
                right_Board[i] = arr[i+1]
                right_Board[i+1] = 0
                return right_Board
        
    return arr

def get_Manhattan_Distance(arr):
    val = 0
    for i in range(len(arr)):
        val += abs(i/3 - arr[i]/3) + abs(i%3 - arr[i]%3)
    return val
    
def main():
    name = "N_Puzzle_RandomHillClimbing"
    initial_Time = time.process_time()
    success_Case = 0
    total_Case = 0
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
            
            arr = sol_RandomHillClimbing(arr)
            
            if tag:
                res += "Failed!"
            else:
                success_Case += 1
                for c in range(len(arr)):
                    res += str(arr[c]) + " "
            res += "\n"
    
    finsh_Time = time.process_time()
    res += "\nTotal time: " + str(finsh_Time - initial_Time) + '\n'
    res += "Total case number: " + str(total_Case) + ", Success case number: " + str(success_Case) + '\n'
    res += "Success rate: " + str(success_Case / float(total_Case)) + '\n'
    print(res)
    
    f = open(name + '.txt', 'w')
    f.write(res)
    f.close()
            
if __name__ == '__main__':
    main()