/* 
    These functions are compulsory for search algorithms but they are specific
    to problems. More clearly, you must must update their blocks but do not change
    their input and output parameters.
    
    Also, you can add new functions at the end of file by declaring them in GRAPH_SEARCH.h
*/

#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern int BOARD_SIZE; // veya 16 veya 32
int **blocked;

int is_valid_position(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}


void initialize_blocked_matrix() {
    blocked = (int **)malloc(BOARD_SIZE * sizeof(int *));
    for (int i = 0; i < BOARD_SIZE; i++) {
        blocked[i] = (int *)malloc(BOARD_SIZE * sizeof(int));
        for (int j = 0; j < BOARD_SIZE; j++) {
            blocked[i][j] = 0; // varsayılan olarak bloklanmamış
        }
    }
}

void free_blocked_matrix() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        free(blocked[i]);
    }
    free(blocked);
}



//int blocked[BOARD_SIZE][BOARD_SIZE] = {0}; // 0 = boş, 1 = engelli

// Knight’ın hareketleri (x, y)
const int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

//______________________________________________________________________________
State* Create_State()
{
	State *state = (State*)malloc(sizeof(State));
    if(state==NULL) Warning_Memory_Allocation(); 

    do {
        printf("Enter x (row) and y (col) [0-%d]: ", BOARD_SIZE - 1);
        scanf("%d %d", &state->x, &state->y);

        if (!is_valid_position(state->x, state->y)) {
            printf("Invalid position! Please enter values within the board.\n");
        }
    } while (!is_valid_position(state->x, state->y));

    // Engelli hücreleri kontrol et
    if (blocked[state->x][state->y] == 1) {
        printf("The selected position is blocked! Please choose another position.\n");
        free(state);
        return Create_State(); // Recursive call to create a new state
    }

   	// printf("Enter x (row) and y (col) [0-%d]: ", BOARD_SIZE - 1);
    // scanf("%d %d", &state->x, &state->y);

    state->h_n = 0;
	       
    return state;    
}

//______________________________________________________________________________
void Print_State(const State *const state)
{
    printf("(%d, %d)", state->x, state->y);
}

//______________________________________________________________________________
void Print_Action(const enum ACTIONS action)
{
   const char* action_names[] = {
        "MOVE_UL", "MOVE_UR", "MOVE_RU", "MOVE_RD",
        "MOVE_DR", "MOVE_DL", "MOVE_LD", "MOVE_LU", "NO_ACTION"
    };
    printf("%s", action_names[action]);
}

//______________________________________________________________________________
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model)
{
    State new_state;
    new_state.x = parent_state->x + dx[action];
    new_state.y = parent_state->y + dy[action];
	// Tahta sınırlarını ve engelleri kontrol et
    if (new_state.x < 0 || new_state.x >= BOARD_SIZE || new_state.y < 0 || new_state.y >= BOARD_SIZE)
        return FALSE;
    if (blocked[new_state.x][new_state.y] == 1)
        return FALSE;

    new_state.h_n = 0;
    trans_model->new_state = new_state;
    trans_model->step_cost = 1; // Tüm hamleler eşit maliyetli

    return TRUE;                              
}

//______________________________________________________________________________
float Compute_Heuristic_Function(const State *const state, const State *const goal)
{
      return (float)(abs(state->x - goal->x) + abs(state->y - goal->y)) / 3.0;
}

//_______________ Update if your goal state is not determined initially ___________________________________
int Goal_Test(const State *const state, const State *const goal_state)
{
	return (state->x == goal_state->x && state->y == goal_state->y);
}

// ==================== WRITE YOUR OPTIONAL FUNCTIONS (IF REQUIRED) ==========================
void Set_Blocked_Cells()
{
    blocked[2][4] = 1; // E3
    blocked[5][0] = 1; // A6
    blocked[1][1] = 1; // B2
};