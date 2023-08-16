/*********************************
 * Reviewer: Shani  
 * Author: Sigal Tal
 * File Name: knight_tour.c
 * ******************************/

#include <stddef.h>	/* size_t */
#include <assert.h>	/* assert */
#include "knight_tour.h"
#include "bit_array.h"

#define BOARD_SIZE 8

static int CalculatPosition(position_t position);
static int IsAvailable(bit_array_t board, position_t position);
int KnightTourRec(bit_array_t board, position_t position, int step_num ,int *path, int *x_move, int *y_move);
static int CountMoves(bit_array_t board, position_t position, int *x_move, int *y_move);
int KnightTourHeurRec(bit_array_t board, position_t position, int step_num ,int *path, int *x_move, int *y_move);




void KnightTour(position_t position, int *path)
{
    bit_array_t board=0;
    int step_num=0;

    int x_move[8]={2, 1, -1, -2, -2, -1, 1, 2};
    int y_move[8]={1, 2, 2, 1, -1, -2, -2,- 1};

    KnightTourRec(board, position, step_num ,path, x_move, y_move);

    /*KnightTourHeurRec(board, position, step_num ,path, x_move, y_move);*/
}

int KnightTourRec(bit_array_t board, position_t position, int step_num ,int *path, int *x_move, int *y_move)
{
    int k=0, pos_index;
    position_t next_step={0,0};

    if(BOARD_SIZE*BOARD_SIZE==step_num)
    {
        return 0;
    }

    if(!IsAvailable(board, position))
    {
        return 1;
    }

    pos_index=CalculatPosition(position);

    board = BitArraySetOn(board,pos_index);
    path[step_num]=pos_index;

    for(k=0; k<8; ++k)
    {
        next_step.x=position.x+x_move[k];
        next_step.y=position.y+y_move[k];

        if(!KnightTourRec(board, next_step, step_num+1 ,path, x_move, y_move))
        {
            return 0;
        }   
    }

    return 1;
}

static int IsAvailable(bit_array_t board, position_t position)
{
    int pos_index=CalculatPosition(position);

    return (position.x<BOARD_SIZE && position.x>=0 
            && position.y<BOARD_SIZE && position.y>=0
            && !BitArrayGetVal(board, pos_index));
}

static int CalculatPosition(position_t position)
{
    return position.x*BOARD_SIZE+position.y;
}

int KnightTourHeurRec(bit_array_t board, position_t position, int step_num ,int *path, int *x_move, int *y_move)
{
    int k=0, pos_index=0, option_step_num_moves=0, min_moves=BOARD_SIZE+1;
    position_t option_step={0,0}, next_step={0,0};

    if(BOARD_SIZE*BOARD_SIZE==step_num)
    {
        return 0;
    }

    pos_index=CalculatPosition(position);

    board = BitArraySetOn(board,pos_index);
    path[step_num]=pos_index;

    for(k=0; k<BOARD_SIZE; ++k)
    {
        option_step.x=position.x+x_move[k];
        option_step.y=position.y+y_move[k];
        option_step_num_moves=CountMoves(board, option_step, x_move, y_move);

        if(IsAvailable(board, option_step) && option_step_num_moves<min_moves)
        {
            min_moves=option_step_num_moves;
            next_step=option_step;
        }
    }

    return KnightTourHeurRec(board, next_step, step_num+1 ,path ,x_move ,y_move);
}

static int CountMoves(bit_array_t board, position_t position, int *x_move, int *y_move)
{
    int num_moves = 0, i=0;
    position_t next={0,0};

    for(i=0;i<BOARD_SIZE;++i)
    {
        next.x=position.x+x_move[i];
        next.y=position.y+y_move[i];

        if(IsAvailable(board,next))
        {
            ++num_moves;
        }
    }

    return num_moves;
}





