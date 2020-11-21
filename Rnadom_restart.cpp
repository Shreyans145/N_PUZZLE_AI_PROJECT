
# ifndef CLK_TCK
# define CLK_TCK CLOCKS_PER_SEC
# endif

#include<bits/stdc++.h>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;

#define TEST 1000
#define S 100
#define UP 0
#define LEFT 2
#define DOWN 1
#define RIGHT 3

struct St 
{
  int direc, manhat_diff;
  St(int i, int dis) 
  {
    this->direc = i;
    this->manhat_diff = dis;
  }

  bool operator<(const St &s) const {
    return manhat_diff > s.manhat_diff;
  }

};

  double Problem_time_ndigits;
  int Failure_count_ndigits;
  int manhat_diff_dist;

inline void swap_these(int &a, int &b) {
    a = a+b;
    b = a-b;
    a = a-b;  
}

inline bool solved(int *state) {
    
    for (int i = 0; i < 8; i++)
         if (state[i]!= (i+1))
              return  false ;
     return  true ;

 }

inline int manhat_dist ( int num, int posi) {
       int dest_x = ceil (num / 3 ), dest_y = (num - 1 )% 3 + 1 , posi_x = ceil (posi / 3 ), posi_y = ( posi - 1 )% 3 + 1 ;
    return abs(dest_x - posi_x) + abs(dest_y - posi_y);
}

  bool n_digit(int *state, int posi, int direc) {
      switch (direc) {
         case UP:
              if (posi <= 3)
                  return false;
              else {
                  manhat_diff_dist =  manhat_dist(state[posi - 4], posi - 3) - manhat_dist(state[posi - 4], posi);
                  return manhat_dist(state[posi - 4], posi - 3) > manhat_dist(state[posi - 4], posi);
              }
          case DOWN:
              if (posi >= 7)
                  return false;
              else {
                  manhat_diff_dist = manhat_dist(state[posi + 2], posi + 3) - manhat_dist(state[posi + 2], posi);
                  return manhat_dist(state[posi + 2], posi + 3) > manhat_dist(state[posi + 2], posi);
              }
          case LEFT:
              if (posi % 3 == 1)
                  return false;
              else {
                  manhat_diff_dist = manhat_dist(state[posi - 2], posi - 1) - manhat_dist(state[posi - 2], posi);
                  return manhat_dist(state[posi - 2], posi - 1) > manhat_dist(state[posi - 2], posi);
              }
         case RIGHT:
              if (posi % 3 == 0)
                 return false;
              else {
                  manhat_diff_dist =  manhat_dist(state[posi], posi + 1) - manhat_dist(state[posi], posi);
                  return manhat_dist(state[posi], posi + 1) > manhat_dist(state[posi], posi);
              }
      }
      return false;
  }

  void randm_state(int *s) {
      int state[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0}, steps, posi, direc;
      steps = S;
      posi = 9;
      while (steps--) {
         direc = rand() % 4;
          switch (direc) {
              case UP:
                  if (posi <= 3)
                      break;
                  else {
                      swap_these(state[posi - 1], state[posi - 4]), posi -= 3;
                      break;
                 }
             case DOWN:
               if (posi >= 7)
                    break;
                 else {
                     swap_these(state[posi - 1], state[posi + 2]), posi += 3;
                   break;
                 }
            case LEFT:
                 if (posi % 3 == 1)
                     break;
                 else {
                     swap_these(state[posi - 1], state[posi - 2]), posi--;
                     break;
                }
             case RIGHT:
                if (posi % 3 == 0)
                     break;
                else {
                     swap_these(state[posi - 1], state[posi]), posi++;
                     break;
                 }
         }
     }
     for (int i = 0; i < 9; i++)
         s[i] = state[i];
 }

 void One_case(int *state) {
     clock_t start_time = clock();
     int posi, i;
     bool found;
     for (i = 0; i < 9; i++)
         if (state[i] == 0) {
             posi = i + 1;
             break;
         }
    while (!solved(state)) {
        found = false;
         std::vector<St> v;
         for (i = 0; i < 4; i++) {
            if (n_digit(state, posi, i)) {
                found = true;
                 v.push_back(St(i, manhat_diff_dist));
             }
             if (i == 3 && found) {
                 std::sort(v.begin(), v.end());
                 switch (v[0].direc) {
                     case UP:
                        swap_these(state[posi - 1], state[posi - 4]), posi -= 3;
                         break;
                     case DOWN:
                       swap_these(state[posi - 1], state[posi + 2]), posi += 3;
                         break;
                     case LEFT:
                        swap_these(state[posi - 1], state[posi - 2]), posi--;
                        break;
                     case RIGHT:
                        swap_these(state[posi - 1], state[posi]), posi++;
                         break;
                }
             }
        }
         if (!found)
             randm_state(state);
    }
     Problem_time_ndigits += (double)(clock() - start_time) / CLK_TCK;
}

void Solve_Random_Restart() {

  FILE *fpointer = fopen("Test.txt", "r");
  int state_array[9];
  while (fscanf(fpointer, "%d %d %d %d %d %d %d %d %d", state_array, state_array + 1, state_array + 2, state_array + 3, state_array + 4, state_array + 5, state_array + 6, state_array + 7, state_array + 8) != EOF)
    {
      One_case(state_array);
    }
  fclose(fpointer);

}

void Show() {
    #ifndef ONLINE_JUDGE
    // for writing output from input text file
    freopen("output.txt", "w", stdout);
    #endif

  printf("N-puzzle Solved Using Random Restart Approach\n");
  printf("Average time taken to solve this: %lf\n", Problem_time_ndigits / (double)(TEST - Failure_count_ndigits));
  printf("Success rate for solving this: %lf\n", 1 - double(Failure_count_ndigits) / TEST);
}

int main() 
{
  int N;
  printf("Enter for N =");
  scanf("%d",&N);
  Problem_time_ndigits = 0;
  Failure_count_ndigits = 0;
  Solve_Random_Restart();
  Show();
  return 0;
}
