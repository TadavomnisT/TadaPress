/*

Compressed block:
01111010111001011110101100001000010101110010010100000000

01111010111001 01111 01011 0000100001010111 0010010100000000

white 7 bits:      0111101 
black 7 bits:      0111001 
sum white 5 bits:  01111 
sum black 5 bits:  01011 
sum col 8 bits:    00001000 
sum row 8 bits:    01010111
corner 4 bits:     0010
center 4 bits:     0101
hash:              00000000

Correct decompressed block:

string(64) "0111101001010001100010110000101011001111110000010000000010011000"
0 1 1 1 1 0 1 0 
0 1 0 1 0 0 0 1 
1 0 0 0 1 0 1 1 
0 0 0 0 1 0 1 0 
1 1 0 0 1 1 1 1 
1 1 0 0 0 0 0 1 
0 0 0 0 0 0 0 0 
1 0 0 1 1 0 0 0 

┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│
│▓▓▓▓▓▓▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│
│▓▓▓▓▓▓▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│
│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│
├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│
│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│
│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│
│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│
├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│
│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│
│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│
│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│
├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│
│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░**░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░**░░░░│▓▓▓▓▓▓▓▓▓▓│
│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░**░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░**░░░░│▓▓▓▓▓▓▓▓▓▓│
│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│
├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│
│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│
│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│
│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│
├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│
│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│
│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│
│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│
├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│
│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│
│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│
│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│
├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│
│░░░░**░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│
│░░░░**░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│
│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│
└──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘

*/

/*
NOTE:

Why did I hard-code everything? instead of using loops ,etc..?

Simple!
In large scale computing, once the code is compiled, it behaves more optimised!
+ Less memory in use :3
+ Less pointers involved :3
++ Faster result *-*

*/

// // Comment following line if wanna skip the middle-rule-checkers 
#define MIDDLE_RULE_CHECKER_ON

#include <iostream>

using namespace std;


class ChessBean {
  public:

    string input_buffer;
    char one = '1', zero = '0';
    bool chessboard[8][8];

    bool ** temp_chessboard = new bool * [8]; 

    bool strategy = NULL;
    bool set_strategy = false;
    bool reached_end_point = false;
    bool change_strategy = false;

    bool cols[8];
    bool rows[8];
    bool black_diagonals[7];
    bool white_diagonals[7];
    unsigned char all_blacks, all_whites, remained_blacks, remained_whites;
    int white_diagonal_placed_beans, black_diagonal_placed_beans;


  /*All possible values for a diagonal with 1 or 3 combination.*/
    bool diagonal_1_3[8][4] = {
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1}
    };

    /*All possible values for a diagonal with 0 or 2 or 4 combination.*/
    bool diagonal_0_2_4[8][4] = {
    {0,0,0,0},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1},
    {1,1,1,1}
    };
    
    /*cols4: 4*/
    bool cols4_4[1][4] = {
    {1,1,1,1}
    };

    /*cols4: 4,3*/
    bool cols4_4_3[5][4] = {
    {1,1,1,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1}
    };

    /*cols4: 4,3,2*/
    bool cols4_4_3_2[11][4] = {
    {1,1,1,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1}
    };

    /*cols4: 4,3,2,1*/
    bool cols4_4_3_2_1[15][4] = {
    {1,1,1,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
    };

    //=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

    /*cols4: 0,1,2,3,4*/
    bool cols4_0_1_2_3_4[16][4] = {
    {0,0,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1},
    {1,1,1,1}
    };

    /*cols4: 0,1,2,3*/
    bool cols4_0_1_2_3[15][4] = {
    {0,0,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1}
    };

    /*cols4: 0,1,2*/
    bool cols4_0_1_2[11][4] = {
    {0,0,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1}
    };

    /*cols4: 0,1*/
    bool cols4_0_1[5][4] = {
    {0,0,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
    };

    /*cols4: 0*/
    bool cols4_0[1][4] = {
    {0,0,0,0}
    };

    //=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
    //=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
    //=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

    /*rows4: 0,1,2,3*/
    bool rows4_0_1_2_3[15][4] = {
    {0,0,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1}
    };

    /*rows4: 0,1,2*/
    bool rows4_0_1_2[11][4] = {
    {0,0,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1}
    };

    /*rows4: 0,1*/
    bool rows4_0_1[5][4] = {
    {0,0,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
    };

    /*rows4: 0*/
    bool rows4_0[1][4] = {
    {0,0,0,0}
    };

    //=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

    /*rows4: 4*/
    bool rows4_4[1][4] = {
    {1,1,1,1}
    };

    /*rows4: 4,3*/
    bool rows4_4_3[5][4] = {
    {1,1,1,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1}
    };

    /*rows4: 4,3,2*/
    bool rows4_4_3_2[11][4] = {
    {1,1,1,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1}
    };

    /*rows4: 4,3,2,1*/
    bool rows4_4_3_2_1[15][4] = {
    {1,1,1,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
    };

    /*rows4: 4,3,2,1,0*/
    bool rows4_4_3_2_1_0[16][4] = {
    {1,1,1,1},
    {1,1,1,0},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1},
    {1,1,0,0},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0},
    {0,1,0,1},
    {0,0,1,1},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    {0,0,0,0}
    };

    /*fill 2 cells*/
    bool fill_2_cells[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };


    // ===========================================================================
    // ---------------------------------------------------------------------------
    // ---------------------------------FUNCTIONS---------------------------------
    // ---------------------------------------------------------------------------
    // ===========================================================================

    // Constructor
    ChessBean( string input_buffer = "" )
    {
      if (input_buffer != "")
      this->input_buffer = input_buffer;
    }

    void setInputBuffer( string input_buffer )
    {
      this->input_buffer = input_buffer;
    }

    void initializer()
    {
      for (int i = 0; i < 8; i++)
        this->temp_chessboard[i] = new bool[8];
      // Initialize boolean array
      for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
          this->chessboard[i][j] = 0;
        }
      }
    }

    void fill_4_corners()
    {
      // Step #1 - Fill 4 corners:
      this->chessboard[0][0] = (this->input_buffer[40] == one);
      this->chessboard[0][7] = (this->input_buffer[41] == one);
      this->chessboard[7][0] = (this->input_buffer[42] == one);
      this->chessboard[7][7] = (this->input_buffer[43] == one);
    }

    void fill_4_centers()
    {
      // Step #2 - Fill 4 centers:
      this->chessboard[3][3] = (this->input_buffer[44] == one);
      this->chessboard[3][4] = (this->input_buffer[45] == one);
      this->chessboard[4][3] = (this->input_buffer[46] == one);
      this->chessboard[4][4] = (this->input_buffer[47] == one);
    }

    void calculate_whites()
    {
      // Step #3 - calculate how many whites shall be placed:
      this->all_whites =
        (this->input_buffer[14] == this->one) * 16 +
        (this->input_buffer[15] == this->one) * 8 +
        (this->input_buffer[16] == this->one) * 4 +
        (this->input_buffer[17] == this->one) * 2 +
        (this->input_buffer[18] == this->one) * 1;
      if (this->all_whites == 0)
        this->all_whites = (this->input_buffer[1] == this->one) ? 32 : 0;
      this->remained_whites = this->all_whites -
        this->chessboard[0][0] -
        this->chessboard[3][3] -
        this->chessboard[4][4] -
        this->chessboard[7][7];

      cout << "all whites:" << (int) this->all_whites << endl;
      cout << "remained whites:" << (int) this->remained_whites << endl;
    }

    void calculate_blacks()
    {
      // Step #4 - calculate how many blacks shall be placed: 
      this->all_blacks =
        (this->input_buffer[19] == this->one) * 16 +
        (this->input_buffer[20] == this->one) * 8 +
        (this->input_buffer[21] == this->one) * 4 +
        (this->input_buffer[22] == this->one) * 2 +
        (this->input_buffer[23] == this->one) * 1;
      if (this->all_blacks == 0)
        this->all_blacks = (this->input_buffer[8] == this->one) ? 32 : 0;
      this->remained_blacks = this->all_blacks -
        this->chessboard[0][7] -
        this->chessboard[3][4] -
        this->chessboard[4][3] -
        this->chessboard[7][0];

      cout << "all blacks:" << (int) this->all_blacks << endl;
      cout << "remained blacks:" << (int) this->remained_blacks << endl;
    }

    void extract_rules_cols()
    {
      // Step #5 - extract rules for columns:
      cols[0] = (input_buffer[24] == one);
      cols[1] = (input_buffer[25] == one);
      cols[2] = (input_buffer[26] == one);
      cols[3] = (input_buffer[27] == one);
      cols[4] = (input_buffer[28] == one);
      cols[5] = (input_buffer[29] == one);
      cols[6] = (input_buffer[30] == one);
      cols[7] = (input_buffer[31] == one);
    }
    
    void extract_rules_rows()
    {
      // Step #6 - extract rules for rows:
      rows[0] = (input_buffer[32] == one);
      rows[1] = (input_buffer[33] == one);
      rows[2] = (input_buffer[34] == one);
      rows[3] = (input_buffer[35] == one);
      rows[4] = (input_buffer[36] == one);
      rows[5] = (input_buffer[37] == one);
      rows[6] = (input_buffer[38] == one);
      rows[7] = (input_buffer[39] == one);
    }

    void extract_rules_white_diagonal()
    {
      // Step #7 - extract rules for white diagonal:
      white_diagonals[0] = (input_buffer[0] == one);
      white_diagonals[1] = (input_buffer[1] == one);
      white_diagonals[2] = (input_buffer[2] == one);
      white_diagonals[3] = (input_buffer[3] == one);
      white_diagonals[4] = (input_buffer[4] == one);
      white_diagonals[5] = (input_buffer[5] == one);
      white_diagonals[6] = (input_buffer[6] == one);
    }

    void extract_rules_black_diagonal()
    {
      // Step #8 - extract rules for black diagonal:
      black_diagonals[0] = (input_buffer[7] == one);
      black_diagonals[1] = (input_buffer[8] == one);
      black_diagonals[2] = (input_buffer[9] == one);
      black_diagonals[3] = (input_buffer[10] == one);
      black_diagonals[4] = (input_buffer[11] == one);
      black_diagonals[5] = (input_buffer[12] == one);
      black_diagonals[6] = (input_buffer[13] == one);
    }


    bool check_rules_cols(bool ** chessboard, bool cols[8]) {
      //This function can be used, only if we have a complete final chessboard 
      int sum;
      for (size_t i = 0; i < 8; i++) {
        sum = 0;
        for (size_t j = 0; j < 8; j++)
          sum += (int) chessboard[i][j];
        if (cols[i] == 0)
          if (sum > 4)
            return false;
          else if (cols[i] == 1)
          if (sum <= 4)
            return false;
      }
      return true;
    }

  bool check_rules_rows(bool ** chessboard, bool rows[8]) {
    //This function can be used, only if we have a complete final chessboard 
    int sum;
    for (size_t i = 0; i < 8; i++) {
      sum = 0;
      for (size_t j = 0; j < 8; j++)
        sum += (int) chessboard[j][i];
      if (rows[i] == 0)
        if (sum < 4)
          return false;
        else if (rows[i] == 1)
        if (sum >= 4)
          return false;
    }
    return true;
  }

  bool check_rules_cols_demo(bool ** chessboard, bool cols[8]) {
    //This function can be used in any state
    int sum;
    for (size_t i = 0; i < 8; i++) {
      sum = 0;
      for (size_t j = 0; j < 8; j++)
        sum += (int) chessboard[j][i];
      if (cols[i] == 0)
        if (sum > 4)
          return false;
    }
    return true;
  }

  bool check_rules_rows_demo(bool ** chessboard, bool rows[8]) {
    //This function can be used, in any state
    int sum;
    for (size_t i = 0; i < 8; i++) {
      sum = 0;
      for (size_t j = 0; j < 8; j++)
        sum += (int) chessboard[i][j];
      if (rows[i] == 1)
        if (sum >= 4)
          return false;
    }
    return true;
  }

  bool check_rules_sum_whites(bool ** chessboard, unsigned char sum_whites) {
    //This function can be used, only if we have a complete final chessboard 
    return (chessboard[0][0] +
      chessboard[0][2] +
      chessboard[0][4] +
      chessboard[0][6] +
      chessboard[1][1] +
      chessboard[1][3] +
      chessboard[1][5] +
      chessboard[1][7] +
      chessboard[2][0] +
      chessboard[2][2] +
      chessboard[2][4] +
      chessboard[2][6] +
      chessboard[3][1] +
      chessboard[3][3] +
      chessboard[3][5] +
      chessboard[3][7] +
      chessboard[4][0] +
      chessboard[4][2] +
      chessboard[4][4] +
      chessboard[4][6] +
      chessboard[5][1] +
      chessboard[5][3] +
      chessboard[5][5] +
      chessboard[5][7] +
      chessboard[6][0] +
      chessboard[6][2] +
      chessboard[6][4] +
      chessboard[6][6] +
      chessboard[7][1] +
      chessboard[7][3] +
      chessboard[7][5] +
      chessboard[7][7]) == (int) sum_whites;
  }

  bool check_rules_sum_blacks(bool ** chessboard, unsigned char sum_blacks) {
    //This function can be used, only if we have a complete final chessboard 
    return (chessboard[0][1] +
      chessboard[0][3] +
      chessboard[0][5] +
      chessboard[0][7] +
      chessboard[1][0] +
      chessboard[1][2] +
      chessboard[1][4] +
      chessboard[1][6] +
      chessboard[2][1] +
      chessboard[2][3] +
      chessboard[2][5] +
      chessboard[2][7] +
      chessboard[3][0] +
      chessboard[3][2] +
      chessboard[3][4] +
      chessboard[3][6] +
      chessboard[4][1] +
      chessboard[4][3] +
      chessboard[4][5] +
      chessboard[4][7] +
      chessboard[5][0] +
      chessboard[5][2] +
      chessboard[5][4] +
      chessboard[5][6] +
      chessboard[6][1] +
      chessboard[6][3] +
      chessboard[6][5] +
      chessboard[6][7] +
      chessboard[7][0] +
      chessboard[7][2] +
      chessboard[7][4] +
      chessboard[7][6]) == (int) sum_blacks;
  }

  bool check_rules_remained_whites(bool ** chessboard, unsigned char remained_whites) {
    //This function can be used, only if we have a complete final chessboard 
    return (chessboard[0][2] +
      chessboard[0][4] +
      chessboard[0][6] +
      chessboard[1][1] +
      chessboard[1][3] +
      chessboard[1][5] +
      chessboard[1][7] +
      chessboard[2][0] +
      chessboard[2][2] +
      chessboard[2][4] +
      chessboard[2][6] +
      chessboard[3][1] +
      chessboard[3][5] +
      chessboard[3][7] +
      chessboard[4][0] +
      chessboard[4][2] +
      chessboard[4][6] +
      chessboard[5][1] +
      chessboard[5][3] +
      chessboard[5][5] +
      chessboard[5][7] +
      chessboard[6][0] +
      chessboard[6][2] +
      chessboard[6][4] +
      chessboard[6][6] +
      chessboard[7][1] +
      chessboard[7][3] +
      chessboard[7][5]) == (int) remained_whites;
  }

  bool check_rules_remained_blacks(bool ** chessboard, unsigned char remained_blacks) {
    //This function can be used, only if we have a complete final chessboard 
    return (chessboard[0][1] +
      chessboard[0][3] +
      chessboard[0][5] +
      chessboard[1][0] +
      chessboard[1][2] +
      chessboard[1][4] +
      chessboard[1][6] +
      chessboard[2][1] +
      chessboard[2][3] +
      chessboard[2][5] +
      chessboard[2][7] +
      chessboard[3][0] +
      chessboard[3][2] +
      chessboard[3][6] +
      chessboard[4][1] +
      chessboard[4][5] +
      chessboard[4][7] +
      chessboard[5][0] +
      chessboard[5][2] +
      chessboard[5][4] +
      chessboard[5][6] +
      chessboard[6][1] +
      chessboard[6][3] +
      chessboard[6][5] +
      chessboard[6][7] +
      chessboard[7][2] +
      chessboard[7][4] +
      chessboard[7][6]) == (int) remained_blacks;
  }

  bool check_rules_remained_whites_demo(bool ** chessboard, unsigned char remained_whites) {
    //This function can be used in any state
    return (chessboard[0][2] +
      chessboard[0][4] +
      chessboard[0][6] +
      chessboard[1][1] +
      chessboard[1][3] +
      chessboard[1][5] +
      chessboard[1][7] +
      chessboard[2][0] +
      chessboard[2][2] +
      chessboard[2][4] +
      chessboard[2][6] +
      chessboard[3][1] +
      chessboard[3][5] +
      chessboard[3][7] +
      chessboard[4][0] +
      chessboard[4][2] +
      chessboard[4][6] +
      chessboard[5][1] +
      chessboard[5][3] +
      chessboard[5][5] +
      chessboard[5][7] +
      chessboard[6][0] +
      chessboard[6][2] +
      chessboard[6][4] +
      chessboard[6][6] +
      chessboard[7][1] +
      chessboard[7][3] +
      chessboard[7][5]) <= (int) remained_whites;
  }

  bool check_rules_remained_blacks_demo(bool ** chessboard, unsigned char remained_blacks) {
    //This function can be used in any state
    return (chessboard[0][1] +
      chessboard[0][3] +
      chessboard[0][5] +
      chessboard[1][0] +
      chessboard[1][2] +
      chessboard[1][4] +
      chessboard[1][6] +
      chessboard[2][1] +
      chessboard[2][3] +
      chessboard[2][5] +
      chessboard[2][7] +
      chessboard[3][0] +
      chessboard[3][2] +
      chessboard[3][6] +
      chessboard[4][1] +
      chessboard[4][5] +
      chessboard[4][7] +
      chessboard[5][0] +
      chessboard[5][2] +
      chessboard[5][4] +
      chessboard[5][6] +
      chessboard[6][1] +
      chessboard[6][3] +
      chessboard[6][5] +
      chessboard[6][7] +
      chessboard[7][2] +
      chessboard[7][4] +
      chessboard[7][6]) <= (int) remained_blacks;
  }

  bool middle_rule_checker(bool ** chessboard)
  {
    // if( !(this->check_rules_cols_demo(chessboard, this->cols) &&
    //   this->check_rules_rows_demo(chessboard, this->rows) &&
    //   this->check_rules_remained_blacks_demo(chessboard, this->remained_blacks) &&
    //   this->check_rules_remained_whites_demo(chessboard, this->remained_whites)
    // ) )
    // {
    //   cout << endl << "++++++DEBUG++++++" << endl;
    //   cout << "check_rules_cols_demo : " <<this->check_rules_cols_demo(chessboard, this->cols) << endl 
    //   << "check_rules_rows_demo : " << this->check_rules_rows_demo(chessboard, this->rows) <<endl 
    //   << "check_rules_remained_blacks_demo : " << this->check_rules_remained_blacks_demo(chessboard, this->remained_blacks) <<endl 
    //   << "check_rules_remained_whites_demo : " << this->check_rules_remained_whites_demo(chessboard, this->remained_whites) << endl;
    //   this->print_chessboard( chessboard );
    //   cout << endl << "======DEBUG======" << endl;
    // }
    return 
    (this->check_rules_cols_demo(chessboard, this->cols) &&
      this->check_rules_rows_demo(chessboard, this->rows) &&
      this->check_rules_remained_blacks_demo(chessboard, this->remained_blacks) &&
      this->check_rules_remained_whites_demo(chessboard, this->remained_whites)
    );
  }

  bool middle_rule_checker(bool chessboard[8][8])
  {
    // if( !(this->check_rules_cols_demo(chessboard, this->cols) &&
    //   this->check_rules_rows_demo(chessboard, this->rows) &&
    //   this->check_rules_remained_blacks_demo(chessboard, this->remained_blacks) &&
    //   this->check_rules_remained_whites_demo(chessboard, this->remained_whites)
    // ) )
    // {
    //   cout << endl << "++++++DEBUG++++++" << endl;
    //   cout << "check_rules_cols_demo : " <<this->check_rules_cols_demo(chessboard, this->cols) << endl 
    //   << "check_rules_rows_demo : " << this->check_rules_rows_demo(chessboard, this->rows) <<endl 
    //   << "check_rules_remained_blacks_demo : " << this->check_rules_remained_blacks_demo(chessboard, this->remained_blacks) <<endl 
    //   << "check_rules_remained_whites_demo : " << this->check_rules_remained_whites_demo(chessboard, this->remained_whites) << endl;
    //   this->print_chessboard( chessboard );
    //   cout << endl << "======DEBUG======" << endl;
    // }
    return 
    (this->check_rules_cols_demo(chessboard, this->cols) &&
      this->check_rules_rows_demo(chessboard, this->rows) &&
      this->check_rules_remained_blacks_demo(chessboard, this->remained_blacks) &&
      this->check_rules_remained_whites_demo(chessboard, this->remained_whites)
    );
  }

  bool end_rule_checker(bool chessboard[8][8])
  { //*-*
    return 
    (this->check_rules_cols(chessboard, this->cols) &&
      this->check_rules_rows(chessboard, this->rows) &&
      this->check_rules_sum_whites(chessboard, this->remained_blacks) &&
      this->check_rules_sum_blacks(chessboard, this->remained_whites)
    );
  }

  bool does_this_chessboard_match_with_real_answer( bool ** chessboard )
  {
    // Cheat function :D ============================
    // ============MUST DELETE THIS LATER!===========
    // ============MUST DELETE THIS LATER!===========
    // ============MUST DELETE THIS LATER!===========
    // ============MUST DELETE THIS LATER!===========
    // ==============================================
    // At least one of printed answers must match the
    // real answer... right?!  
    // 
    // Correct decompressed block:
    // string(64) "01111010010100011000101100001010110
    // 01111110000010000000010011000"
    // 0 1 1 1 1 0 1 0 
    // 0 1 0 1 0 0 0 1 
    // 1 0 0 0 1 0 1 1 
    // 0 0 0 0 1 0 1 0 
    // 1 1 0 0 1 1 1 1 
    // 1 1 0 0 0 0 0 1 
    // 0 0 0 0 0 0 0 0 
    // 1 0 0 1 1 0 0 0 
    // ==============================================
    // ==============================================
    // ==============================================

    if( this->strategy )
    {
      // 4 rows selected
    }
    else
    {
      // 4 cols selected
    }
    return 0;
  }

  void copy_chessboard(bool ** chessboard, bool temp_chessboard[8][8]) {
    for (size_t i = 0; i < 8; i++)
      for (size_t j = 0; j < 8; j++)
        temp_chessboard[i][j] = chessboard[i][j];
  }

  void copy_chessboard(bool chessboard[8][8], bool ** temp_chessboard) {
    for (size_t i = 0; i < 8; i++)
      for (size_t j = 0; j < 8; j++)
        temp_chessboard[i][j] = chessboard[i][j];
  }
  
  void copy_chessboard(bool ** chessboard, bool ** temp_chessboard) {
    for (size_t i = 0; i < 8; i++)
      for (size_t j = 0; j < 8; j++)
        temp_chessboard[i][j] = chessboard[i][j];
  }

  void copy_chessboard( bool chessboard[8][8], bool temp_chessboard[8][8]) {
    for (size_t i = 0; i < 8; i++)
      for (size_t j = 0; j < 8; j++)
        temp_chessboard[i][j] = chessboard[i][j];
  }

  bool check_rules_cols(bool chessboard[8][8], bool cols[8]) {
    //This function can be used, only if we have a complete final chessboard 
    int sum;
    for (size_t i = 0; i < 8; i++) {
      sum = 0;
      for (size_t j = 0; j < 8; j++)
        sum += (int) chessboard[i][j];
      if (cols[i] == 0)
        if (sum > 4)
          return false;
        else if (cols[i] == 1)
        if (sum <= 4)
          return false;
    }
    return true;
  }

  bool check_rules_rows(bool chessboard[8][8], bool rows[8]) {
    //This function can be used, only if we have a complete final chessboard 
    int sum;
    for (size_t i = 0; i < 8; i++) {
      sum = 0;
      for (size_t j = 0; j < 8; j++)
        sum += (int) chessboard[j][i];
      if (rows[i] == 0)
        if (sum < 4)
          return false;
        else if (rows[i] == 1)
        if (sum >= 4)
          return false;
    }
    return true;
  }

  bool check_rules_cols_demo(bool chessboard[8][8], bool cols[8]) {
    //This function can be used in any state
    int sum;
    for (size_t i = 0; i < 8; i++) {
      sum = 0;
      for (size_t j = 0; j < 8; j++)
        sum += (int) chessboard[j][i];
      if (cols[i] == 0)
        if (sum > 4)
          return false;
    }
    return true;
  }

  bool check_rules_rows_demo(bool chessboard[8][8], bool rows[8]) {
    //This function can be used, in any state
    int sum;
    for (size_t i = 0; i < 8; i++) {
      sum = 0;
      for (size_t j = 0; j < 8; j++)
        sum += (int) chessboard[i][j];
      if (rows[i] == 1)
        if (sum >= 4)
          return false;
    }
    return true;
  }

  bool check_rules_sum_whites(bool chessboard[8][8], unsigned char sum_whites) {
    //This function can be used, only if we have a complete final chessboard 
    return (chessboard[0][0] +
      chessboard[0][2] +
      chessboard[0][4] +
      chessboard[0][6] +
      chessboard[1][1] +
      chessboard[1][3] +
      chessboard[1][5] +
      chessboard[1][7] +
      chessboard[2][0] +
      chessboard[2][2] +
      chessboard[2][4] +
      chessboard[2][6] +
      chessboard[3][1] +
      chessboard[3][3] +
      chessboard[3][5] +
      chessboard[3][7] +
      chessboard[4][0] +
      chessboard[4][2] +
      chessboard[4][4] +
      chessboard[4][6] +
      chessboard[5][1] +
      chessboard[5][3] +
      chessboard[5][5] +
      chessboard[5][7] +
      chessboard[6][0] +
      chessboard[6][2] +
      chessboard[6][4] +
      chessboard[6][6] +
      chessboard[7][1] +
      chessboard[7][3] +
      chessboard[7][5] +
      chessboard[7][7]) == (int) sum_whites;
  }

  bool check_rules_sum_blacks(bool chessboard[8][8], unsigned char sum_blacks) {
    //This function can be used, only if we have a complete final chessboard 
    return (chessboard[0][1] +
      chessboard[0][3] +
      chessboard[0][5] +
      chessboard[0][7] +
      chessboard[1][0] +
      chessboard[1][2] +
      chessboard[1][4] +
      chessboard[1][6] +
      chessboard[2][1] +
      chessboard[2][3] +
      chessboard[2][5] +
      chessboard[2][7] +
      chessboard[3][0] +
      chessboard[3][2] +
      chessboard[3][4] +
      chessboard[3][6] +
      chessboard[4][1] +
      chessboard[4][3] +
      chessboard[4][5] +
      chessboard[4][7] +
      chessboard[5][0] +
      chessboard[5][2] +
      chessboard[5][4] +
      chessboard[5][6] +
      chessboard[6][1] +
      chessboard[6][3] +
      chessboard[6][5] +
      chessboard[6][7] +
      chessboard[7][0] +
      chessboard[7][2] +
      chessboard[7][4] +
      chessboard[7][6]) == (int) sum_blacks;
  }

  bool check_rules_remained_whites(bool chessboard[8][8], unsigned char remained_whites) {
    //This function can be used, only if we have a complete final chessboard 
    return (chessboard[0][2] +
      chessboard[0][4] +
      chessboard[0][6] +
      chessboard[1][1] +
      chessboard[1][3] +
      chessboard[1][5] +
      chessboard[1][7] +
      chessboard[2][0] +
      chessboard[2][2] +
      chessboard[2][4] +
      chessboard[2][6] +
      chessboard[3][1] +
      chessboard[3][5] +
      chessboard[3][7] +
      chessboard[4][0] +
      chessboard[4][2] +
      chessboard[4][6] +
      chessboard[5][1] +
      chessboard[5][3] +
      chessboard[5][5] +
      chessboard[5][7] +
      chessboard[6][0] +
      chessboard[6][2] +
      chessboard[6][4] +
      chessboard[6][6] +
      chessboard[7][1] +
      chessboard[7][3] +
      chessboard[7][5]) == (int) remained_whites;
  }

  bool check_rules_remained_blacks(bool chessboard[8][8], unsigned char remained_blacks) {
    //This function can be used, only if we have a complete final chessboard 
    return (chessboard[0][1] +
      chessboard[0][3] +
      chessboard[0][5] +
      chessboard[1][0] +
      chessboard[1][2] +
      chessboard[1][4] +
      chessboard[1][6] +
      chessboard[2][1] +
      chessboard[2][3] +
      chessboard[2][5] +
      chessboard[2][7] +
      chessboard[3][0] +
      chessboard[3][2] +
      chessboard[3][6] +
      chessboard[4][1] +
      chessboard[4][5] +
      chessboard[4][7] +
      chessboard[5][0] +
      chessboard[5][2] +
      chessboard[5][4] +
      chessboard[5][6] +
      chessboard[6][1] +
      chessboard[6][3] +
      chessboard[6][5] +
      chessboard[6][7] +
      chessboard[7][2] +
      chessboard[7][4] +
      chessboard[7][6]) == (int) remained_blacks;
  }

  bool check_rules_remained_whites_demo(bool chessboard[8][8], unsigned char remained_whites) {
    //This function can be used in any state
    return (chessboard[0][2] +
      chessboard[0][4] +
      chessboard[0][6] +
      chessboard[1][1] +
      chessboard[1][3] +
      chessboard[1][5] +
      chessboard[1][7] +
      chessboard[2][0] +
      chessboard[2][2] +
      chessboard[2][4] +
      chessboard[2][6] +
      chessboard[3][1] +
      chessboard[3][5] +
      chessboard[3][7] +
      chessboard[4][0] +
      chessboard[4][2] +
      chessboard[4][6] +
      chessboard[5][1] +
      chessboard[5][3] +
      chessboard[5][5] +
      chessboard[5][7] +
      chessboard[6][0] +
      chessboard[6][2] +
      chessboard[6][4] +
      chessboard[6][6] +
      chessboard[7][1] +
      chessboard[7][3] +
      chessboard[7][5]) <= (int) remained_whites;
  }

  bool check_rules_remained_blacks_demo(bool chessboard[8][8], unsigned char remained_blacks) {
    //This function can be used in any state
    return (chessboard[0][1] +
      chessboard[0][3] +
      chessboard[0][5] +
      chessboard[1][0] +
      chessboard[1][2] +
      chessboard[1][4] +
      chessboard[1][6] +
      chessboard[2][1] +
      chessboard[2][3] +
      chessboard[2][5] +
      chessboard[2][7] +
      chessboard[3][0] +
      chessboard[3][2] +
      chessboard[3][6] +
      chessboard[4][1] +
      chessboard[4][5] +
      chessboard[4][7] +
      chessboard[5][0] +
      chessboard[5][2] +
      chessboard[5][4] +
      chessboard[5][6] +
      chessboard[6][1] +
      chessboard[6][3] +
      chessboard[6][5] +
      chessboard[6][7] +
      chessboard[7][2] +
      chessboard[7][4] +
      chessboard[7][6]) <= (int) remained_blacks;
  }


  void print_chessboard(bool ** chessboard) {
    for (size_t i = 0; i < 8; i++) {
      for (size_t j = 0; j < 8; j++) {
        cout << chessboard[i][j] << " ";
      }
      cout << endl;
    }
  }

  void print_chessboard(bool chessboard[8][8]) {
    for (size_t i = 0; i < 8; i++) {
      for (size_t j = 0; j < 8; j++) {
        cout << chessboard[i][j] << " ";
      }
      cout << endl;
    }
  }

void white_diagonal( bool ** chessboard ) {
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  int white_diagonal_placed_beans = (int)
  (temp_chessboard[0][0] +
    temp_chessboard[3][3] +
    temp_chessboard[4][4] +
    temp_chessboard[7][7]
  );
  // for white diagonal
  if (white_diagonal_placed_beans == 0) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        temp_chessboard[1][1] = diagonal_1_3[i][0];
        temp_chessboard[2][2] = diagonal_1_3[i][1];
        temp_chessboard[5][5] = diagonal_1_3[i][2];
        temp_chessboard[6][6] = diagonal_1_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->black_diagonal(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    }
  } else if (white_diagonal_placed_beans == 1) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    }
  } else if (white_diagonal_placed_beans == 2) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);

      }
    }
  } else if (white_diagonal_placed_beans == 3) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    }
  } else if (white_diagonal_placed_beans == 4) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    }
  }
}


void black_diagonal( bool ** chessboard ) {
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  int black_diagonal_placed_beans = (int)
  (temp_chessboard[0][7] +
    temp_chessboard[3][4] +
    temp_chessboard[4][3] +
    temp_chessboard[7][0]
  );
  // for black diagonal
  if (black_diagonal_placed_beans == 0) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        temp_chessboard[1][6] = diagonal_1_3[i][0];
        temp_chessboard[2][5] = diagonal_1_3[i][1];
        temp_chessboard[5][2] = diagonal_1_3[i][2];
        temp_chessboard[6][1] = diagonal_1_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->little_white_diagonal_1(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    }
  } else if (black_diagonal_placed_beans == 1) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif 
            this->little_white_diagonal_1(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    }
  } else if (black_diagonal_placed_beans == 2) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    }
  } else if (black_diagonal_placed_beans == 3) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    }
  } else if (black_diagonal_placed_beans == 4) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    }
  }
}

void little_white_diagonal_1( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  // cout << "This happens 64 times right?" << endl;
  if( this->white_diagonals[1] )
  {
    if( temp_chessboard[1][1] )
    {
      temp_chessboard[0][2] = 0;
      temp_chessboard[2][0] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
      temp_chessboard[0][2] = 1;
      temp_chessboard[2][0] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
    } 
    else
    {
      temp_chessboard[0][2] = 1;
      temp_chessboard[2][0] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
      temp_chessboard[0][2] = 0;
      temp_chessboard[2][0] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
    }
  }
  else
  {
    if( temp_chessboard[1][1] )
    {
      temp_chessboard[0][2] = 1;
      temp_chessboard[2][0] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
      temp_chessboard[0][2] = 0;
      temp_chessboard[2][0] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
    } 
    else
    {
      temp_chessboard[0][2] = 0;
      temp_chessboard[2][0] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
      temp_chessboard[0][2] = 1;
      temp_chessboard[2][0] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
    }
  }
}

void little_white_diagonal_2( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  if( this->white_diagonals[6] )
  {
    if( temp_chessboard[6][6] )
    {
      temp_chessboard[5][7] = 0;
      temp_chessboard[7][5] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
      temp_chessboard[5][7] = 1;
      temp_chessboard[7][5] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
    } 
    else
    {
      temp_chessboard[5][7] = 1;
      temp_chessboard[7][5] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
      temp_chessboard[5][7] = 0;
      temp_chessboard[7][5] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
    }
  }
  else
  {
    if( temp_chessboard[6][6] )
    {
      temp_chessboard[5][7] = 1;
      temp_chessboard[7][5] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
      temp_chessboard[5][7] = 0;
      temp_chessboard[7][5] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
    } 
    else
    {
      temp_chessboard[5][7] = 0;
      temp_chessboard[7][5] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
      temp_chessboard[5][7] = 1;
      temp_chessboard[7][5] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
    }
  }
}

void little_black_diagonal_1( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  if( this->black_diagonals[1] )
  {
    if( temp_chessboard[1][6] )
    {
      temp_chessboard[0][5] = 0;
      temp_chessboard[2][7] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
      temp_chessboard[0][5] = 1;
      temp_chessboard[2][7] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
    } 
    else
    {
      temp_chessboard[0][5] = 1;
      temp_chessboard[2][7] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
      temp_chessboard[0][5] = 0;
      temp_chessboard[2][7] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
    }
  }
  else
  {
    if( temp_chessboard[1][6] )
    {
      temp_chessboard[0][5] = 1;
      temp_chessboard[2][7] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
      temp_chessboard[0][5] = 0;
      temp_chessboard[2][7] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
    } 
    else
    {
      temp_chessboard[0][5] = 0;
      temp_chessboard[2][7] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
      temp_chessboard[0][5] = 1;
      temp_chessboard[2][7] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
    }
  }
}

void little_black_diagonal_2( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  if( this->black_diagonals[6] )
  {
    if( temp_chessboard[6][1] )
    {
      temp_chessboard[5][0] = 0;
      temp_chessboard[7][2] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
      temp_chessboard[5][0] = 1;
      temp_chessboard[7][2] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
    } 
    else
    {
      temp_chessboard[5][0] = 1;
      temp_chessboard[7][2] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
      temp_chessboard[5][0] = 0;
      temp_chessboard[7][2] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
    }
  }
  else
  {
    if( temp_chessboard[6][1] )
    {
      temp_chessboard[5][0] = 1;
      temp_chessboard[7][2] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
      temp_chessboard[5][0] = 0;
      temp_chessboard[7][2] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
    } 
    else
    {
      temp_chessboard[5][0] = 0;
      temp_chessboard[7][2] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
      temp_chessboard[5][0] = 1;
      temp_chessboard[7][2] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
    }
  }
}

void choosing_strategy( bool ** temp_chessboard )
{
  int sum = 0 , col_result = 1 , row_result = 1 ;
  bool has_answer = true;
  // starting with columns :
  // if VALUE > 4 then: 1
  // else: 0
  // first column:-----------index = 0------------
  sum += (int)
  temp_chessboard[0][0] +
  temp_chessboard[2][0] +
  temp_chessboard[5][0] +
  temp_chessboard[7][0];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
      has_answer = false;
    else if( sum == 1 )
      col_result *= 1;
    else if( sum == 2 )
      col_result *= 5;
    else if( sum == 3 )
      col_result *= 11;
    else if( sum == 4 )
      col_result *= 15;
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if( sum == 0 )
      col_result *= 16;
    else if( sum == 1 )
      col_result *= 15;
    else if( sum == 2 )
      col_result *= 11;
    else if( sum == 3 )
      col_result *= 5;
    else if( sum == 4 )
      col_result *= 1;
  }
  // ---------------------------------------------
  // next column:-----------index = 2-------------
  sum = 0;
  sum += (int)
  temp_chessboard[0][2] +
  temp_chessboard[2][2] +
  temp_chessboard[5][2] +
  temp_chessboard[7][2];
  if( this->cols[ 2 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
      has_answer = false;
    else if( sum == 1 )
      col_result *= 1;
    else if( sum == 2 )
      col_result *= 5;
    else if( sum == 3 )
      col_result *= 11;
    else if( sum == 4 )
      col_result *= 15;
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if( sum == 0 )
      col_result *= 16;
    else if( sum == 1 )
      col_result *= 15;
    else if( sum == 2 )
      col_result *= 11;
    else if( sum == 3 )
      col_result *= 5;
    else if( sum == 4 )
      col_result *= 1;
  }
  // ---------------------------------------------
// next column:-----------index = 5-------------
  sum = 0;
  sum += (int)
  temp_chessboard[0][5] +
  temp_chessboard[2][5] +
  temp_chessboard[5][5] +
  temp_chessboard[7][5];
  if( this->cols[ 5 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
      has_answer = false;
    else if( sum == 1 )
      col_result *= 1;
    else if( sum == 2 )
      col_result *= 5;
    else if( sum == 3 )
      col_result *= 11;
    else if( sum == 4 )
      col_result *= 15;
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if( sum == 0 )
      col_result *= 16;
    else if( sum == 1 )
      col_result *= 15;
    else if( sum == 2 )
      col_result *= 11;
    else if( sum == 3 )
      col_result *= 5;
    else if( sum == 4 )
      col_result *= 1;
  }
  // ---------------------------------------------
// next column:-----------index = 7-------------
  sum = 0;
  sum += (int)
  temp_chessboard[0][7] +
  temp_chessboard[2][7] +
  temp_chessboard[5][7] +
  temp_chessboard[7][7];
  if( this->cols[ 7 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
      has_answer = false;
    else if( sum == 1 )
      col_result *= 1;
    else if( sum == 2 )
      col_result *= 5;
    else if( sum == 3 )
      col_result *= 11;
    else if( sum == 4 )
      col_result *= 15;
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if( sum == 0 )
      col_result *= 16;
    else if( sum == 1 )
      col_result *= 15;
    else if( sum == 2 )
      col_result *= 11;
    else if( sum == 3 )
      col_result *= 5;
    else if( sum == 4 )
      col_result *= 1;
  }
  // ---------------------------------------------
  // going on rows :
  // if VALUE < 4 then: 1
  // else: 0
  // ---------------------------------------------
  // first row:-----------index = 0------------
  sum += (int)
  temp_chessboard[0][0] +
  temp_chessboard[0][2] +
  temp_chessboard[0][5] +
  temp_chessboard[0][7];
  if( this->rows[ 0 ] ) //Means: "<4" PV: 0,1,2,3
  {
      if( sum == 0 )
        row_result *= 15;
      else if( sum == 1 )
        row_result *= 11;
      else if( sum == 2 )
        row_result *= 5;
      else if( sum == 3 )
        row_result *= 1;
      else if( sum == 3 )
        has_answer = false;
  }
  else //Means: ">=4" PV: 4,5,6,7,8
  {
    if( sum == 0 )
      row_result *= 1;
    else if( sum == 1 )
      row_result *= 5;
    else if( sum == 2 )
      row_result *= 11;
    else if( sum == 3 )
      row_result *= 15;
    else if( sum == 4 )
      row_result *= 16;
  }
  // ---------------------------------------------
  // first row:-----------index = 2------------
  sum += (int)
  temp_chessboard[2][0] +
  temp_chessboard[2][2] +
  temp_chessboard[2][5] +
  temp_chessboard[2][7];
  if( this->rows[ 2 ] ) //Means: "<4" PV: 0,1,2,3
  {
    if( sum == 0 )
      row_result *= 15;
    else if( sum == 1 )
      row_result *= 11;
    else if( sum == 2 )
      row_result *= 5;
    else if( sum == 3 )
      row_result *= 1;
    else if( sum == 3 )
      has_answer = false;
  }
  else //Means: ">=4" PV: 4,5,6,7,8
  {
    if( sum == 0 )
      row_result *= 1;
    else if( sum == 1 )
      row_result *= 5;
    else if( sum == 2 )
      row_result *= 11;
    else if( sum == 3 )
      row_result *= 15;
    else if( sum == 4 )
      row_result *= 16;
  }
  // ---------------------------------------------
  // first row:-----------index = 5------------
  sum += (int)
  temp_chessboard[5][0] +
  temp_chessboard[5][2] +
  temp_chessboard[5][5] +
  temp_chessboard[5][7];
  if( this->rows[ 5 ] ) //Means: "<4" PV: 0,1,2,3
  {
    if( sum == 0 )
      row_result *= 15;
    else if( sum == 1 )
      row_result *= 11;
    else if( sum == 2 )
      row_result *= 5;
    else if( sum == 3 )
      row_result *= 1;
    else if( sum == 3 )
      has_answer = false;
  }
  else //Means: ">=4" PV: 4,5,6,7,8
  {
    if( sum == 0 )
      row_result *= 1;
    else if( sum == 1 )
      row_result *= 5;
    else if( sum == 2 )
      row_result *= 11;
    else if( sum == 3 )
      row_result *= 15;
    else if( sum == 4 )
      row_result *= 16;
  }
  // ---------------------------------------------
  // first row:-----------index = 7------------
  sum += (int)
  temp_chessboard[7][0] +
  temp_chessboard[7][2] +
  temp_chessboard[7][5] +
  temp_chessboard[7][7];
  if( this->rows[ 7 ] ) //Means: "<4" PV: 0,1,2,3
  {
    if( sum == 0 )
      row_result *= 15;
    else if( sum == 1 )
      row_result *= 11;
    else if( sum == 2 )
      row_result *= 5;
    else if( sum == 3 )
      row_result *= 1;
    else if( sum == 3 )
      has_answer = false;
  }
  else //Means: ">=4" PV: 4,5,6,7,8
  {
    if( sum == 0 )
      row_result *= 1;
    else if( sum == 1 )
      row_result *= 5;
    else if( sum == 2 )
      row_result *= 11;
    else if( sum == 3 )
      row_result *= 15;
    else if( sum == 4 )
      row_result *= 16;
  }
  // // ---------------------------------------------
  // if( has_answer )
  //   cout << col_result << "\tvs\t" << row_result << endl;
  // else 
  //   cout << "No-Answers: Droping calculations." << endl;
  if( has_answer ) {
    if ( col_result > row_result )
    {
      this->strategy = 0;
      this->set_strategy = true;
      if( this->change_strategy )
        this->complete_4_cols_1( temp_chessboard );
      else
        this->complete_4_rows_1( temp_chessboard );
    }
    else
    {
      this->strategy = 1;
      this->set_strategy = true;
      if( this->change_strategy )
        this->complete_4_rows_1( temp_chessboard );
      else
        this->complete_4_cols_1( temp_chessboard );
    } 
  }

  // // this->strategy = 0;
  // cout << "before***" << endl;
  // this->print_chessboard(temp_chessboard);
  // cout << "***" << endl;
  // this->complete_4_rows_1( temp_chessboard );
  // cout << "after***" << endl;
  // this->print_chessboard(temp_chessboard);
  // cout << "***" << endl;
  // // this->strategy = 1;
  // this->complete_4_cols_1( temp_chessboard );
}

void complete_4_cols_1( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 0;
  int sum = (int)
  temp_chessboard[0][INDEX] +
  temp_chessboard[2][INDEX] +
  temp_chessboard[5][INDEX] +
  temp_chessboard[7][INDEX];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      return; //No answer
    }
    else if ( sum == 1 )
    {
      temp_chessboard[1][INDEX] = cols4_4[0][0];
      temp_chessboard[3][INDEX] = cols4_4[0][1];
      temp_chessboard[4][INDEX] = cols4_4[0][2];
      temp_chessboard[6][INDEX] = cols4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_2(temp_chessboard);
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2_1[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2_1[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2_1[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3_4[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3_4[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3_4[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3_4[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      temp_chessboard[1][INDEX] = cols4_0[0][0];
      temp_chessboard[3][INDEX] = cols4_0[0][1];
      temp_chessboard[4][INDEX] = cols4_0[0][2];
      temp_chessboard[6][INDEX] = cols4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_2(temp_chessboard);
    }
  }
}

void complete_4_cols_2( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 2;
  int sum = (int)
  temp_chessboard[0][INDEX] +
  temp_chessboard[2][INDEX] +
  temp_chessboard[5][INDEX] +
  temp_chessboard[7][INDEX];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      return; //No answer
    }
    else if ( sum == 1 )
    {
      temp_chessboard[1][INDEX] = cols4_4[0][0];
      temp_chessboard[3][INDEX] = cols4_4[0][1];
      temp_chessboard[4][INDEX] = cols4_4[0][2];
      temp_chessboard[6][INDEX] = cols4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_3(temp_chessboard);
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2_1[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2_1[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2_1[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3_4[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3_4[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3_4[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3_4[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      temp_chessboard[1][INDEX] = cols4_0[0][0];
      temp_chessboard[3][INDEX] = cols4_0[0][1];
      temp_chessboard[4][INDEX] = cols4_0[0][2];
      temp_chessboard[6][INDEX] = cols4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_3(temp_chessboard);
    }
  }
}

void complete_4_cols_3( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 5;
  int sum = (int)
  temp_chessboard[0][INDEX] +
  temp_chessboard[2][INDEX] +
  temp_chessboard[5][INDEX] +
  temp_chessboard[7][INDEX];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      return; //No answer
    }
    else if ( sum == 1 )
    {
      temp_chessboard[1][INDEX] = cols4_4[0][0];
      temp_chessboard[3][INDEX] = cols4_4[0][1];
      temp_chessboard[4][INDEX] = cols4_4[0][2];
      temp_chessboard[6][INDEX] = cols4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_4(temp_chessboard);
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2_1[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2_1[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2_1[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3_4[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3_4[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3_4[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3_4[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      temp_chessboard[1][INDEX] = cols4_0[0][0];
      temp_chessboard[3][INDEX] = cols4_0[0][1];
      temp_chessboard[4][INDEX] = cols4_0[0][2];
      temp_chessboard[6][INDEX] = cols4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_4(temp_chessboard);
    }
  }
}

void complete_4_cols_4( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 7;
  int sum = (int)
  temp_chessboard[0][INDEX] +
  temp_chessboard[2][INDEX] +
  temp_chessboard[5][INDEX] +
  temp_chessboard[7][INDEX];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      return; //No answer
    }
    else if ( sum == 1 )
    {
      temp_chessboard[1][INDEX] = cols4_4[0][0];
      temp_chessboard[3][INDEX] = cols4_4[0][1];
      temp_chessboard[4][INDEX] = cols4_4[0][2];
      temp_chessboard[6][INDEX] = cols4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->came_from_cols(temp_chessboard);
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2_1[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2_1[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2_1[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3_4[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3_4[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3_4[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3_4[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      temp_chessboard[1][INDEX] = cols4_0[0][0];
      temp_chessboard[3][INDEX] = cols4_0[0][1];
      temp_chessboard[4][INDEX] = cols4_0[0][2];
      temp_chessboard[6][INDEX] = cols4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->came_from_cols(temp_chessboard);
    }
  }
}

void complete_4_rows_1( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 0;
  int sum = (int)
  temp_chessboard[INDEX][0] +
  temp_chessboard[INDEX][2] +
  temp_chessboard[INDEX][5] +
  temp_chessboard[INDEX][7];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2_3[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2_3[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2_3[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      temp_chessboard[INDEX][1] = rows4_0[0][0];
      temp_chessboard[INDEX][3] = rows4_0[0][1];
      temp_chessboard[INDEX][4] = rows4_0[0][2];
      temp_chessboard[INDEX][6] = rows4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_2(temp_chessboard);
    }
    else if ( sum == 4 )
    {
      return; //No answer
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      temp_chessboard[INDEX][1] = rows4_4[0][0];
      temp_chessboard[INDEX][3] = rows4_4[0][1];
      temp_chessboard[INDEX][4] = rows4_4[0][2];
      temp_chessboard[INDEX][6] = rows4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_2(temp_chessboard);
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1_0[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1_0[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1_0[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1_0[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
  }
}

void complete_4_rows_2( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 2;
  int sum = (int)
  temp_chessboard[INDEX][0] +
  temp_chessboard[INDEX][2] +
  temp_chessboard[INDEX][5] +
  temp_chessboard[INDEX][7];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2_3[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2_3[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2_3[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      temp_chessboard[INDEX][1] = rows4_0[0][0];
      temp_chessboard[INDEX][3] = rows4_0[0][1];
      temp_chessboard[INDEX][4] = rows4_0[0][2];
      temp_chessboard[INDEX][6] = rows4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_3(temp_chessboard);
    }
    else if ( sum == 4 )
    {
      return; //No answer
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      temp_chessboard[INDEX][1] = rows4_4[0][0];
      temp_chessboard[INDEX][3] = rows4_4[0][1];
      temp_chessboard[INDEX][4] = rows4_4[0][2];
      temp_chessboard[INDEX][6] = rows4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_3(temp_chessboard);
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1_0[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1_0[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1_0[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1_0[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
  }
}

void complete_4_rows_3( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 5;
  int sum = (int)
  temp_chessboard[INDEX][0] +
  temp_chessboard[INDEX][2] +
  temp_chessboard[INDEX][5] +
  temp_chessboard[INDEX][7];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2_3[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2_3[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2_3[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      temp_chessboard[INDEX][1] = rows4_0[0][0];
      temp_chessboard[INDEX][3] = rows4_0[0][1];
      temp_chessboard[INDEX][4] = rows4_0[0][2];
      temp_chessboard[INDEX][6] = rows4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_4(temp_chessboard);
    }
    else if ( sum == 4 )
    {
      return; //No answer
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      temp_chessboard[INDEX][1] = rows4_4[0][0];
      temp_chessboard[INDEX][3] = rows4_4[0][1];
      temp_chessboard[INDEX][4] = rows4_4[0][2];
      temp_chessboard[INDEX][6] = rows4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_4(temp_chessboard);
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1_0[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1_0[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1_0[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1_0[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
  }
}

void complete_4_rows_4( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 7;
  int sum = (int)
  temp_chessboard[INDEX][0] +
  temp_chessboard[INDEX][2] +
  temp_chessboard[INDEX][5] +
  temp_chessboard[INDEX][7];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2_3[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2_3[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2_3[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      temp_chessboard[INDEX][1] = rows4_0[0][0];
      temp_chessboard[INDEX][3] = rows4_0[0][1];
      temp_chessboard[INDEX][4] = rows4_0[0][2];
      temp_chessboard[INDEX][6] = rows4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->came_from_rows(temp_chessboard);
    }
    else if ( sum == 4 )
    {
      return; //No answer
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      temp_chessboard[INDEX][1] = rows4_4[0][0];
      temp_chessboard[INDEX][3] = rows4_4[0][1];
      temp_chessboard[INDEX][4] = rows4_4[0][2];
      temp_chessboard[INDEX][6] = rows4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->came_from_rows(temp_chessboard);
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1_0[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1_0[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1_0[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1_0[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
  }
}

// ======================****

void white_diagonal( bool  chessboard[8][8] ) {
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  int white_diagonal_placed_beans = (int)
  (temp_chessboard[0][0] +
    temp_chessboard[3][3] +
    temp_chessboard[4][4] +
    temp_chessboard[7][7]
  );
  // for white diagonal
  if (white_diagonal_placed_beans == 0) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        temp_chessboard[1][1] = diagonal_1_3[i][0];
        temp_chessboard[2][2] = diagonal_1_3[i][1];
        temp_chessboard[5][5] = diagonal_1_3[i][2];
        temp_chessboard[6][6] = diagonal_1_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->black_diagonal(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    }
  } else if (white_diagonal_placed_beans == 1) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    }
  } else if (white_diagonal_placed_beans == 2) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);

      }
    }
  } else if (white_diagonal_placed_beans == 3) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    }
  } else if (white_diagonal_placed_beans == 4) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
      }
    }
  }
}


void black_diagonal( bool  chessboard[8][8] ) {
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  int black_diagonal_placed_beans = (int)
  (temp_chessboard[0][7] +
    temp_chessboard[3][4] +
    temp_chessboard[4][3] +
    temp_chessboard[7][0]
  );
  // for black diagonal
  if (black_diagonal_placed_beans == 0) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        temp_chessboard[1][6] = diagonal_1_3[i][0];
        temp_chessboard[2][5] = diagonal_1_3[i][1];
        temp_chessboard[5][2] = diagonal_1_3[i][2];
        temp_chessboard[6][1] = diagonal_1_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->little_white_diagonal_1(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    }
  } else if (black_diagonal_placed_beans == 1) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif 
            this->little_white_diagonal_1(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    }
  } else if (black_diagonal_placed_beans == 2) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    }
  } else if (black_diagonal_placed_beans == 3) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    }
  } else if (black_diagonal_placed_beans == 4) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    } else {
      for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
      }
    }
  }
}

void little_white_diagonal_1( bool  chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  // cout << "This happens 64 times right?" << endl;
  if( this->white_diagonals[1] )
  {
    if( temp_chessboard[1][1] )
    {
      temp_chessboard[0][2] = 0;
      temp_chessboard[2][0] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
      temp_chessboard[0][2] = 1;
      temp_chessboard[2][0] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
    } 
    else
    {
      temp_chessboard[0][2] = 1;
      temp_chessboard[2][0] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
      temp_chessboard[0][2] = 0;
      temp_chessboard[2][0] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
    }
  }
  else
  {
    if( temp_chessboard[1][1] )
    {
      temp_chessboard[0][2] = 1;
      temp_chessboard[2][0] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
      temp_chessboard[0][2] = 0;
      temp_chessboard[2][0] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
    } 
    else
    {
      temp_chessboard[0][2] = 0;
      temp_chessboard[2][0] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
      temp_chessboard[0][2] = 1;
      temp_chessboard[2][0] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_white_diagonal_2(temp_chessboard);
    }
  }
}

void little_white_diagonal_2( bool  chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  if( this->white_diagonals[6] )
  {
    if( temp_chessboard[6][6] )
    {
      temp_chessboard[5][7] = 0;
      temp_chessboard[7][5] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
      temp_chessboard[5][7] = 1;
      temp_chessboard[7][5] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
    } 
    else
    {
      temp_chessboard[5][7] = 1;
      temp_chessboard[7][5] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
      temp_chessboard[5][7] = 0;
      temp_chessboard[7][5] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
    }
  }
  else
  {
    if( temp_chessboard[6][6] )
    {
      temp_chessboard[5][7] = 1;
      temp_chessboard[7][5] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
      temp_chessboard[5][7] = 0;
      temp_chessboard[7][5] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
    } 
    else
    {
      temp_chessboard[5][7] = 0;
      temp_chessboard[7][5] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
      temp_chessboard[5][7] = 1;
      temp_chessboard[7][5] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_1(temp_chessboard);
    }
  }
}

void little_black_diagonal_1( bool  chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  if( this->black_diagonals[1] )
  {
    if( temp_chessboard[1][6] )
    {
      temp_chessboard[0][5] = 0;
      temp_chessboard[2][7] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
      temp_chessboard[0][5] = 1;
      temp_chessboard[2][7] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
    } 
    else
    {
      temp_chessboard[0][5] = 1;
      temp_chessboard[2][7] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
      temp_chessboard[0][5] = 0;
      temp_chessboard[2][7] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
    }
  }
  else
  {
    if( temp_chessboard[1][6] )
    {
      temp_chessboard[0][5] = 1;
      temp_chessboard[2][7] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
      temp_chessboard[0][5] = 0;
      temp_chessboard[2][7] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
    } 
    else
    {
      temp_chessboard[0][5] = 0;
      temp_chessboard[2][7] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
      temp_chessboard[0][5] = 1;
      temp_chessboard[2][7] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->little_black_diagonal_2(temp_chessboard);
    }
  }
}

void little_black_diagonal_2( bool  chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  if( this->black_diagonals[6] )
  {
    if( temp_chessboard[6][1] )
    {
      temp_chessboard[5][0] = 0;
      temp_chessboard[7][2] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
      temp_chessboard[5][0] = 1;
      temp_chessboard[7][2] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
    } 
    else
    {
      temp_chessboard[5][0] = 1;
      temp_chessboard[7][2] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
      temp_chessboard[5][0] = 0;
      temp_chessboard[7][2] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
    }
  }
  else
  {
    if( temp_chessboard[6][1] )
    {
      temp_chessboard[5][0] = 1;
      temp_chessboard[7][2] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
      temp_chessboard[5][0] = 0;
      temp_chessboard[7][2] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
    } 
    else
    {
      temp_chessboard[5][0] = 0;
      temp_chessboard[7][2] = 0;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
      temp_chessboard[5][0] = 1;
      temp_chessboard[7][2] = 1;
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->choosing_strategy(temp_chessboard);
    }
  }
}

void choosing_strategy( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int sum = 0 , col_result = 1 , row_result = 1 ;
  bool has_answer = true;
  // starting with columns :
  // if VALUE > 4 then: 1
  // else: 0
  // first column:-----------index = 0------------
  sum += (int)
  temp_chessboard[0][0] +
  temp_chessboard[2][0] +
  temp_chessboard[5][0] +
  temp_chessboard[7][0];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
      has_answer = false;
    else if( sum == 1 )
      col_result *= 1;
    else if( sum == 2 )
      col_result *= 5;
    else if( sum == 3 )
      col_result *= 11;
    else if( sum == 4 )
      col_result *= 15;
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if( sum == 0 )
      col_result *= 16;
    else if( sum == 1 )
      col_result *= 15;
    else if( sum == 2 )
      col_result *= 11;
    else if( sum == 3 )
      col_result *= 5;
    else if( sum == 4 )
      col_result *= 1;
  }
  // ---------------------------------------------
  // next column:-----------index = 2-------------
  sum = 0;
  sum += (int)
  temp_chessboard[0][2] +
  temp_chessboard[2][2] +
  temp_chessboard[5][2] +
  temp_chessboard[7][2];
  if( this->cols[ 2 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
      has_answer = false;
    else if( sum == 1 )
      col_result *= 1;
    else if( sum == 2 )
      col_result *= 5;
    else if( sum == 3 )
      col_result *= 11;
    else if( sum == 4 )
      col_result *= 15;
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if( sum == 0 )
      col_result *= 16;
    else if( sum == 1 )
      col_result *= 15;
    else if( sum == 2 )
      col_result *= 11;
    else if( sum == 3 )
      col_result *= 5;
    else if( sum == 4 )
      col_result *= 1;
  }
  // ---------------------------------------------
// next column:-----------index = 5-------------
  sum = 0;
  sum += (int)
  temp_chessboard[0][5] +
  temp_chessboard[2][5] +
  temp_chessboard[5][5] +
  temp_chessboard[7][5];
  if( this->cols[ 5 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
      has_answer = false;
    else if( sum == 1 )
      col_result *= 1;
    else if( sum == 2 )
      col_result *= 5;
    else if( sum == 3 )
      col_result *= 11;
    else if( sum == 4 )
      col_result *= 15;
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if( sum == 0 )
      col_result *= 16;
    else if( sum == 1 )
      col_result *= 15;
    else if( sum == 2 )
      col_result *= 11;
    else if( sum == 3 )
      col_result *= 5;
    else if( sum == 4 )
      col_result *= 1;
  }
  // ---------------------------------------------
// next column:-----------index = 7-------------
  sum = 0;
  sum += (int)
  temp_chessboard[0][7] +
  temp_chessboard[2][7] +
  temp_chessboard[5][7] +
  temp_chessboard[7][7];
  if( this->cols[ 7 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
      has_answer = false;
    else if( sum == 1 )
      col_result *= 1;
    else if( sum == 2 )
      col_result *= 5;
    else if( sum == 3 )
      col_result *= 11;
    else if( sum == 4 )
      col_result *= 15;
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if( sum == 0 )
      col_result *= 16;
    else if( sum == 1 )
      col_result *= 15;
    else if( sum == 2 )
      col_result *= 11;
    else if( sum == 3 )
      col_result *= 5;
    else if( sum == 4 )
      col_result *= 1;
  }
  // ---------------------------------------------
  // going on rows :
  // if VALUE < 4 then: 1
  // else: 0
  // ---------------------------------------------
  // first row:-----------index = 0------------
  sum += (int)
  temp_chessboard[0][0] +
  temp_chessboard[0][2] +
  temp_chessboard[0][5] +
  temp_chessboard[0][7];
  if( this->rows[ 0 ] ) //Means: "<4" PV: 0,1,2,3
  {
      if( sum == 0 )
        row_result *= 15;
      else if( sum == 1 )
        row_result *= 11;
      else if( sum == 2 )
        row_result *= 5;
      else if( sum == 3 )
        row_result *= 1;
      else if( sum == 3 )
        has_answer = false;
  }
  else //Means: ">=4" PV: 4,5,6,7,8
  {
    if( sum == 0 )
      row_result *= 1;
    else if( sum == 1 )
      row_result *= 5;
    else if( sum == 2 )
      row_result *= 11;
    else if( sum == 3 )
      row_result *= 15;
    else if( sum == 4 )
      row_result *= 16;
  }
  // ---------------------------------------------
  // first row:-----------index = 2------------
  sum += (int)
  temp_chessboard[2][0] +
  temp_chessboard[2][2] +
  temp_chessboard[2][5] +
  temp_chessboard[2][7];
  if( this->rows[ 2 ] ) //Means: "<4" PV: 0,1,2,3
  {
    if( sum == 0 )
      row_result *= 15;
    else if( sum == 1 )
      row_result *= 11;
    else if( sum == 2 )
      row_result *= 5;
    else if( sum == 3 )
      row_result *= 1;
    else if( sum == 3 )
      has_answer = false;
  }
  else //Means: ">=4" PV: 4,5,6,7,8
  {
    if( sum == 0 )
      row_result *= 1;
    else if( sum == 1 )
      row_result *= 5;
    else if( sum == 2 )
      row_result *= 11;
    else if( sum == 3 )
      row_result *= 15;
    else if( sum == 4 )
      row_result *= 16;
  }
  // ---------------------------------------------
  // first row:-----------index = 5------------
  sum += (int)
  temp_chessboard[5][0] +
  temp_chessboard[5][2] +
  temp_chessboard[5][5] +
  temp_chessboard[5][7];
  if( this->rows[ 5 ] ) //Means: "<4" PV: 0,1,2,3
  {
    if( sum == 0 )
      row_result *= 15;
    else if( sum == 1 )
      row_result *= 11;
    else if( sum == 2 )
      row_result *= 5;
    else if( sum == 3 )
      row_result *= 1;
    else if( sum == 3 )
      has_answer = false;
  }
  else //Means: ">=4" PV: 4,5,6,7,8
  {
    if( sum == 0 )
      row_result *= 1;
    else if( sum == 1 )
      row_result *= 5;
    else if( sum == 2 )
      row_result *= 11;
    else if( sum == 3 )
      row_result *= 15;
    else if( sum == 4 )
      row_result *= 16;
  }
  // ---------------------------------------------
  // first row:-----------index = 7------------
  sum += (int)
  temp_chessboard[7][0] +
  temp_chessboard[7][2] +
  temp_chessboard[7][5] +
  temp_chessboard[7][7];
  if( this->rows[ 7 ] ) //Means: "<4" PV: 0,1,2,3
  {
    if( sum == 0 )
      row_result *= 15;
    else if( sum == 1 )
      row_result *= 11;
    else if( sum == 2 )
      row_result *= 5;
    else if( sum == 3 )
      row_result *= 1;
    else if( sum == 3 )
      has_answer = false;
  }
  else //Means: ">=4" PV: 4,5,6,7,8
  {
    if( sum == 0 )
      row_result *= 1;
    else if( sum == 1 )
      row_result *= 5;
    else if( sum == 2 )
      row_result *= 11;
    else if( sum == 3 )
      row_result *= 15;
    else if( sum == 4 )
      row_result *= 16;
  }
  // // ---------------------------------------------
  // if( has_answer )
  //   cout << col_result << "\tvs\t" << row_result << endl;
  // else 
  //   cout << "No-Answers: Droping calculations." << endl;
  if( has_answer ) {
    if ( col_result > row_result )
    {
      this->strategy = 0;
      this->set_strategy = true;
      if( this->change_strategy )
        this->complete_4_cols_1( temp_chessboard );
      else
        this->complete_4_rows_1( temp_chessboard );
    }
    else
    {
      this->strategy = 1;
      this->set_strategy = true;
      if( this->change_strategy )
        this->complete_4_rows_1( temp_chessboard );
      else
        this->complete_4_cols_1( temp_chessboard );
    } 
  }

  // // this->strategy = 0;
  // cout << "before***" << endl;
  // this->print_chessboard(temp_chessboard);
  // cout << "***" << endl;
  // this->complete_4_rows_1( temp_chessboard );
  // cout << "after***" << endl;
  // this->print_chessboard(temp_chessboard);
  // cout << "***" << endl;
  // // this->strategy = 1;
  // this->complete_4_cols_1( temp_chessboard );
}

void complete_4_cols_1( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 0;
  int sum = (int)
  temp_chessboard[0][INDEX] +
  temp_chessboard[2][INDEX] +
  temp_chessboard[5][INDEX] +
  temp_chessboard[7][INDEX];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      return; //No answer
    }
    else if ( sum == 1 )
    {
      temp_chessboard[1][INDEX] = cols4_4[0][0];
      temp_chessboard[3][INDEX] = cols4_4[0][1];
      temp_chessboard[4][INDEX] = cols4_4[0][2];
      temp_chessboard[6][INDEX] = cols4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_2(temp_chessboard);
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2_1[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2_1[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2_1[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3_4[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3_4[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3_4[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3_4[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_2(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      temp_chessboard[1][INDEX] = cols4_0[0][0];
      temp_chessboard[3][INDEX] = cols4_0[0][1];
      temp_chessboard[4][INDEX] = cols4_0[0][2];
      temp_chessboard[6][INDEX] = cols4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_2(temp_chessboard);
    }
  }
}

void complete_4_cols_2( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 2;
  int sum = (int)
  temp_chessboard[0][INDEX] +
  temp_chessboard[2][INDEX] +
  temp_chessboard[5][INDEX] +
  temp_chessboard[7][INDEX];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      return; //No answer
    }
    else if ( sum == 1 )
    {
      temp_chessboard[1][INDEX] = cols4_4[0][0];
      temp_chessboard[3][INDEX] = cols4_4[0][1];
      temp_chessboard[4][INDEX] = cols4_4[0][2];
      temp_chessboard[6][INDEX] = cols4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_3(temp_chessboard);
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2_1[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2_1[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2_1[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3_4[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3_4[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3_4[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3_4[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_3(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      temp_chessboard[1][INDEX] = cols4_0[0][0];
      temp_chessboard[3][INDEX] = cols4_0[0][1];
      temp_chessboard[4][INDEX] = cols4_0[0][2];
      temp_chessboard[6][INDEX] = cols4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_3(temp_chessboard);
    }
  }
}

void complete_4_cols_3( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 5;
  int sum = (int)
  temp_chessboard[0][INDEX] +
  temp_chessboard[2][INDEX] +
  temp_chessboard[5][INDEX] +
  temp_chessboard[7][INDEX];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      return; //No answer
    }
    else if ( sum == 1 )
    {
      temp_chessboard[1][INDEX] = cols4_4[0][0];
      temp_chessboard[3][INDEX] = cols4_4[0][1];
      temp_chessboard[4][INDEX] = cols4_4[0][2];
      temp_chessboard[6][INDEX] = cols4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_4(temp_chessboard);
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2_1[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2_1[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2_1[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3_4[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3_4[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3_4[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3_4[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_cols_4(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      temp_chessboard[1][INDEX] = cols4_0[0][0];
      temp_chessboard[3][INDEX] = cols4_0[0][1];
      temp_chessboard[4][INDEX] = cols4_0[0][2];
      temp_chessboard[6][INDEX] = cols4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_cols_4(temp_chessboard);
    }
  }
}

void complete_4_cols_4( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 7;
  int sum = (int)
  temp_chessboard[0][INDEX] +
  temp_chessboard[2][INDEX] +
  temp_chessboard[5][INDEX] +
  temp_chessboard[7][INDEX];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      return; //No answer
    }
    else if ( sum == 1 )
    {
      temp_chessboard[1][INDEX] = cols4_4[0][0];
      temp_chessboard[3][INDEX] = cols4_4[0][1];
      temp_chessboard[4][INDEX] = cols4_4[0][2];
      temp_chessboard[6][INDEX] = cols4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->came_from_cols(temp_chessboard);
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_4_3_2_1[i][0];
        temp_chessboard[3][INDEX] = cols4_4_3_2_1[i][1];
        temp_chessboard[4][INDEX] = cols4_4_3_2_1[i][2];
        temp_chessboard[6][INDEX] = cols4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3_4[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3_4[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3_4[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3_4[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2_3[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2_3[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2_3[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1_2[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1_2[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1_2[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[1][INDEX] = cols4_0_1[i][0];
        temp_chessboard[3][INDEX] = cols4_0_1[i][1];
        temp_chessboard[4][INDEX] = cols4_0_1[i][2];
        temp_chessboard[6][INDEX] = cols4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_cols(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      temp_chessboard[1][INDEX] = cols4_0[0][0];
      temp_chessboard[3][INDEX] = cols4_0[0][1];
      temp_chessboard[4][INDEX] = cols4_0[0][2];
      temp_chessboard[6][INDEX] = cols4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->came_from_cols(temp_chessboard);
    }
  }
}

void complete_4_rows_1( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 0;
  int sum = (int)
  temp_chessboard[INDEX][0] +
  temp_chessboard[INDEX][2] +
  temp_chessboard[INDEX][5] +
  temp_chessboard[INDEX][7];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2_3[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2_3[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2_3[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      temp_chessboard[INDEX][1] = rows4_0[0][0];
      temp_chessboard[INDEX][3] = rows4_0[0][1];
      temp_chessboard[INDEX][4] = rows4_0[0][2];
      temp_chessboard[INDEX][6] = rows4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_2(temp_chessboard);
    }
    else if ( sum == 4 )
    {
      return; //No answer
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      temp_chessboard[INDEX][1] = rows4_4[0][0];
      temp_chessboard[INDEX][3] = rows4_4[0][1];
      temp_chessboard[INDEX][4] = rows4_4[0][2];
      temp_chessboard[INDEX][6] = rows4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_2(temp_chessboard);
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1_0[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1_0[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1_0[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1_0[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_2(temp_chessboard);
      }
    }
  }
}

void complete_4_rows_2( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 2;
  int sum = (int)
  temp_chessboard[INDEX][0] +
  temp_chessboard[INDEX][2] +
  temp_chessboard[INDEX][5] +
  temp_chessboard[INDEX][7];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2_3[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2_3[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2_3[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      temp_chessboard[INDEX][1] = rows4_0[0][0];
      temp_chessboard[INDEX][3] = rows4_0[0][1];
      temp_chessboard[INDEX][4] = rows4_0[0][2];
      temp_chessboard[INDEX][6] = rows4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_3(temp_chessboard);
    }
    else if ( sum == 4 )
    {
      return; //No answer
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      temp_chessboard[INDEX][1] = rows4_4[0][0];
      temp_chessboard[INDEX][3] = rows4_4[0][1];
      temp_chessboard[INDEX][4] = rows4_4[0][2];
      temp_chessboard[INDEX][6] = rows4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_3(temp_chessboard);
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1_0[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1_0[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1_0[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1_0[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_3(temp_chessboard);
      }
    }
  }
}

void complete_4_rows_3( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 5;
  int sum = (int)
  temp_chessboard[INDEX][0] +
  temp_chessboard[INDEX][2] +
  temp_chessboard[INDEX][5] +
  temp_chessboard[INDEX][7];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2_3[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2_3[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2_3[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      temp_chessboard[INDEX][1] = rows4_0[0][0];
      temp_chessboard[INDEX][3] = rows4_0[0][1];
      temp_chessboard[INDEX][4] = rows4_0[0][2];
      temp_chessboard[INDEX][6] = rows4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_4(temp_chessboard);
    }
    else if ( sum == 4 )
    {
      return; //No answer
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      temp_chessboard[INDEX][1] = rows4_4[0][0];
      temp_chessboard[INDEX][3] = rows4_4[0][1];
      temp_chessboard[INDEX][4] = rows4_4[0][2];
      temp_chessboard[INDEX][6] = rows4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->complete_4_rows_4(temp_chessboard);
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1_0[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1_0[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1_0[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1_0[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->complete_4_rows_4(temp_chessboard);
      }
    }
  }
}

void complete_4_rows_4( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int INDEX = 7;
  int sum = (int)
  temp_chessboard[INDEX][0] +
  temp_chessboard[INDEX][2] +
  temp_chessboard[INDEX][5] +
  temp_chessboard[INDEX][7];
  if( this->cols[ 0 ] ) //Means: ">4" PV: 5,6,7,8
  {
    if ( sum == 0 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2_3[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2_3[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2_3[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1_2[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1_2[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1_2[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_0_1[i][0];
        temp_chessboard[INDEX][3] = rows4_0_1[i][1];
        temp_chessboard[INDEX][4] = rows4_0_1[i][2];
        temp_chessboard[INDEX][6] = rows4_0_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      temp_chessboard[INDEX][1] = rows4_0[0][0];
      temp_chessboard[INDEX][3] = rows4_0[0][1];
      temp_chessboard[INDEX][4] = rows4_0[0][2];
      temp_chessboard[INDEX][6] = rows4_0[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->came_from_rows(temp_chessboard);
    }
    else if ( sum == 4 )
    {
      return; //No answer
    }
  }
  else //Means: "<=4" PV: 0,1,2,3,4
  {
    if ( sum == 0 )
    {
      temp_chessboard[INDEX][1] = rows4_4[0][0];
      temp_chessboard[INDEX][3] = rows4_4[0][1];
      temp_chessboard[INDEX][4] = rows4_4[0][2];
      temp_chessboard[INDEX][6] = rows4_4[0][3];
      #ifdef MIDDLE_RULE_CHECKER_ON
      if (this->middle_rule_checker( temp_chessboard ) )
      #endif
        this->came_from_rows(temp_chessboard);
    }
    else if ( sum == 1 )
    {
      for ( int i = 0 ; i < 5 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 2 )
    {
      for ( int i = 0 ; i < 11 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 3 )
    {
      for ( int i = 0 ; i < 15 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
    else if ( sum == 4 )
    {
      for ( int i = 0 ; i < 16 ; i++ )
      {
        temp_chessboard[INDEX][1] = rows4_4_3_2_1_0[i][0];
        temp_chessboard[INDEX][3] = rows4_4_3_2_1_0[i][1];
        temp_chessboard[INDEX][4] = rows4_4_3_2_1_0[i][2];
        temp_chessboard[INDEX][6] = rows4_4_3_2_1_0[i][3];
        #ifdef MIDDLE_RULE_CHECKER_ON
        if (this->middle_rule_checker( temp_chessboard ) )
        #endif
          this->came_from_rows(temp_chessboard);
      }
    }
  }
}

// ======================****

void came_from_cols( bool ** chessboard )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  // bool has_answer = true;
  int stg1 = 0, stg2 = 0,
  answer_1 = 1, answer_6 = 1,
  answer_3 = 1, answer_4 = 1,
  sum_1 = (int)
  temp_chessboard[1][0]+
  temp_chessboard[1][1]+
  temp_chessboard[1][2]+
  temp_chessboard[1][5]+
  temp_chessboard[1][6]+
  temp_chessboard[1][7],
  sum_6 = (int)
  temp_chessboard[6][0]+
  temp_chessboard[6][1]+
  temp_chessboard[6][2]+
  temp_chessboard[6][5]+
  temp_chessboard[6][6]+
  temp_chessboard[6][7],
  sum_3 = (int)
  temp_chessboard[3][0]+
  temp_chessboard[3][2]+
  temp_chessboard[3][3]+
  temp_chessboard[3][4]+
  temp_chessboard[3][5]+
  temp_chessboard[3][7],
  sum_4 = (int)
  temp_chessboard[4][0]+
  temp_chessboard[4][2]+
  temp_chessboard[4][3]+
  temp_chessboard[4][4]+
  temp_chessboard[4][5]+
  temp_chessboard[4][7];
  
  if( this->rows[ 1 ] )
  {
    if( sum_1 == 0 )
      answer_1 = 47;
    else if( sum_1 == 1 )
      answer_1 = 47;
    else if( sum_1 == 2 )
      answer_1 = 36;
    else if( sum_1 == 3 )
      answer_1 = 14;
    else answer_1 = 0;
  }
  else
  {
    if( sum_1 == 2 )
      answer_1 = 11;
    else if( sum_1 == 3 )
      answer_1 = 33;
    else if( sum_1 == 4 )
      answer_1 = 47;
    else if( sum_1 == 5 )
      answer_1 = 47;
    else if( sum_1 == 6 )
      answer_1 = 47;
    else answer_1 = 0;
  }

  if( this->rows[ 6 ] )
  {
    if( sum_6 == 0 )
      answer_6 = 47;
    else if( sum_6 == 1 )
      answer_6 = 47;
    else if( sum_6 == 2 )
      answer_6 = 36;
    else if( sum_6 == 3 )
      answer_6 = 14;
    else answer_6 = 0;
  }
  else
  {
    if( sum_6 == 2 )
      answer_6 = 11;
    else if( sum_6 == 3 )
      answer_6 = 33;
    else if( sum_6 == 4 )
      answer_6 = 47;
    else if( sum_6 == 5 )
      answer_6 = 47;
    else if( sum_6 == 6 )
      answer_6 = 47;
    else answer_6 = 0;
  }

  if( this->rows[ 3 ] )
  {
    if( sum_3 == 0 )
      answer_3 = 47;
    else if( sum_3 == 1 )
      answer_3 = 47;
    else if( sum_3 == 2 )
      answer_3 = 36;
    else if( sum_3 == 3 )
      answer_3 = 14;
    else answer_3 = 0;
  }
  else
  {
    if( sum_3 == 2 )
      answer_3 = 11;
    else if( sum_3 == 3 )
      answer_3 = 33;
    else if( sum_3 == 4 )
      answer_3 = 47;
    else if( sum_3 == 5 )
      answer_3 = 47;
    else if( sum_3 == 6 )
      answer_3 = 47;
    else answer_3 = 0;
  }

  if( this->rows[ 4 ] )
  {
    if( sum_4 == 0 )
      answer_4 = 47;
    else if( sum_4 == 1 )
      answer_4 = 47;
    else if( sum_4 == 2 )
      answer_4 = 36;
    else if( sum_4 == 3 )
      answer_4 = 14;
    else answer_4 = 0;
  }
  else
  {
    if( sum_4 == 2 )
      answer_4 = 11;
    else if( sum_4 == 3 )
      answer_4 = 33;
    else if( sum_4 == 4 )
      answer_4 = 47;
    else if( sum_4 == 5 )
      answer_4 = 47;
    else if( sum_4 == 6 )
      answer_4 = 47;
    else answer_4 = 0;
  }

  // mirio_mano_hesabi_daqun_mikoni </3

  if( (answer_1 * answer_6) && (answer_3 * answer_4) )
  {
    // both valid
    if( ( (int (answer_1 / 10)) * (int (answer_6 / 10)) ) > ( int (answer_3 / 10) * (int (answer_4 / 10))) )
    {
      // choose 3-4
      cout << ( (int (answer_1 / 10)) * (int (answer_6 / 10)) ) << ">" << ( int (answer_3 / 10) * (int (answer_4 / 10)))  << endl;
    }
    else
    {
      // choose 1-6
      cout << ( (int (answer_1 / 10)) * (int (answer_6 / 10)) ) << "<=" << ( int (answer_3 / 10) * (int (answer_4 / 10)))  << endl;
    }
  } 
  else if( (answer_1 * answer_6) && !(answer_3 * answer_4) )
  {
    // 1-6 is valid
    cout << (int (answer_1 / 10)) * (int (answer_6 / 10)) << "> 0" << endl;
  }
  else if( !(answer_1 * answer_6) && (answer_3 * answer_4) )
  {
    // 3-4 is valid
    cout << (int (answer_3 / 10)) * (int (answer_4 / 10)) << "> 0" << endl;
  }
  // else
  // {
  //   // both not valid
  //   cout << "droping" << endl;
  // }
}

void came_from_cols( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  // bool has_answer = true;
  int stg1 = 0, stg2 = 0,
  answer_1 = 1, answer_6 = 1,
  answer_3 = 1, answer_4 = 1,
  sum_1 = (int)
  temp_chessboard[1][0]+
  temp_chessboard[1][1]+
  temp_chessboard[1][2]+
  temp_chessboard[1][5]+
  temp_chessboard[1][6]+
  temp_chessboard[1][7],
  sum_6 = (int)
  temp_chessboard[6][0]+
  temp_chessboard[6][1]+
  temp_chessboard[6][2]+
  temp_chessboard[6][5]+
  temp_chessboard[6][6]+
  temp_chessboard[6][7],
  sum_3 = (int)
  temp_chessboard[3][0]+
  temp_chessboard[3][2]+
  temp_chessboard[3][3]+
  temp_chessboard[3][4]+
  temp_chessboard[3][5]+
  temp_chessboard[3][7],
  sum_4 = (int)
  temp_chessboard[4][0]+
  temp_chessboard[4][2]+
  temp_chessboard[4][3]+
  temp_chessboard[4][4]+
  temp_chessboard[4][5]+
  temp_chessboard[4][7];
  
  if( this->rows[ 1 ] )
  {
    if( sum_1 == 0 )
      answer_1 = 47;
    else if( sum_1 == 1 )
      answer_1 = 47;
    else if( sum_1 == 2 )
      answer_1 = 36;
    else if( sum_1 == 3 )
      answer_1 = 14;
    else answer_1 = 0;
  }
  else
  {
    if( sum_1 == 2 )
      answer_1 = 11;
    else if( sum_1 == 3 )
      answer_1 = 33;
    else if( sum_1 == 4 )
      answer_1 = 47;
    else if( sum_1 == 5 )
      answer_1 = 47;
    else if( sum_1 == 6 )
      answer_1 = 47;
    else answer_1 = 0;
  }

  if( this->rows[ 6 ] )
  {
    if( sum_6 == 0 )
      answer_6 = 47;
    else if( sum_6 == 1 )
      answer_6 = 47;
    else if( sum_6 == 2 )
      answer_6 = 36;
    else if( sum_6 == 3 )
      answer_6 = 14;
    else answer_6 = 0;
  }
  else
  {
    if( sum_6 == 2 )
      answer_6 = 11;
    else if( sum_6 == 3 )
      answer_6 = 33;
    else if( sum_6 == 4 )
      answer_6 = 47;
    else if( sum_6 == 5 )
      answer_6 = 47;
    else if( sum_6 == 6 )
      answer_6 = 47;
    else answer_6 = 0;
  }

  if( this->rows[ 3 ] )
  {
    if( sum_3 == 0 )
      answer_3 = 47;
    else if( sum_3 == 1 )
      answer_3 = 47;
    else if( sum_3 == 2 )
      answer_3 = 36;
    else if( sum_3 == 3 )
      answer_3 = 14;
    else answer_3 = 0;
  }
  else
  {
    if( sum_3 == 2 )
      answer_3 = 11;
    else if( sum_3 == 3 )
      answer_3 = 33;
    else if( sum_3 == 4 )
      answer_3 = 47;
    else if( sum_3 == 5 )
      answer_3 = 47;
    else if( sum_3 == 6 )
      answer_3 = 47;
    else answer_3 = 0;
  }

  if( this->rows[ 4 ] )
  {
    if( sum_4 == 0 )
      answer_4 = 47;
    else if( sum_4 == 1 )
      answer_4 = 47;
    else if( sum_4 == 2 )
      answer_4 = 36;
    else if( sum_4 == 3 )
      answer_4 = 14;
    else answer_4 = 0;
  }
  else
  {
    if( sum_4 == 2 )
      answer_4 = 11;
    else if( sum_4 == 3 )
      answer_4 = 33;
    else if( sum_4 == 4 )
      answer_4 = 47;
    else if( sum_4 == 5 )
      answer_4 = 47;
    else if( sum_4 == 6 )
      answer_4 = 47;
    else answer_4 = 0;
  }

  // mirio_mano_hesabi_daqun_mikoni </3

  if( (answer_1 * answer_6) && (answer_3 * answer_4) )
  {
    // both valid
    if( ( (int (answer_1 / 10)) * (int (answer_6 / 10)) ) > ( int (answer_3 / 10) * (int (answer_4 / 10))) )
    {
      // choose 3-4
      this->choose_3_4_from_cols( temp_chessboard , answer_3 , answer_4 );
      // cout << ( (int (answer_1 / 10)) * (int (answer_6 / 10)) ) << ">" << ( int (answer_3 / 10) * (int (answer_4 / 10)))  << endl;
    }
    else
    {
      // choose 1-6
      this->choose_1_6_from_cols( temp_chessboard , answer_1 , answer_6 );      
      // cout << ( (int (answer_1 / 10)) * (int (answer_6 / 10)) ) << "<=" << ( int (answer_3 / 10) * (int (answer_4 / 10)))  << endl;
    }
  } 
  else if( (answer_1 * answer_6) && !(answer_3 * answer_4) )
  {
    // 1-6 is valid
    this->choose_1_6_from_cols( temp_chessboard , answer_1 , answer_6 );      
    // cout << (int (answer_1 / 10)) * (int (answer_6 / 10)) << "> 0" << endl;
  }
  else if( !(answer_1 * answer_6) && (answer_3 * answer_4) )
  {
    // 3-4 is valid
      this->choose_3_4_from_cols( temp_chessboard , answer_3 , answer_4 );
    // cout << (int (answer_3 / 10)) * (int (answer_4 / 10)) << "> 0" << endl;
  }
  // else
  // {
  //   // both not valid
  //   cout << "droping" << endl;
  // }
}

// void choose_1_6_from_cols( bool ** chessboard , int answer_1 , int answer_6 ) 
// {
//   bool temp_chessboard[8][8]; 
//   this->copy_chessboard( chessboard , temp_chessboard );

//   // cout << answer_1 << " " << answer_6 << endl;
//   // this->end_point( temp_chessboard );
// }

// void choose_3_4_from_cols( bool ** chessboard , int answer_3 , int answer_4 ) 
// {
//   bool temp_chessboard[8][8]; 
//   this->copy_chessboard( chessboard , temp_chessboard );

//   // cout << answer_3 << " " << answer_4 << endl;
//   // this->end_point( temp_chessboard );
// }

void choose_1_6_from_cols( bool chessboard[8][8] , int answer_1 , int answer_6 ) 
{
  int
  ONE_X   = 1,  ONE_Y   = 3,
  TWO_X   = 1,  TWO_Y   = 4,
  THREE_X = 6,  THREE_Y = 3,
  FOUR_X  = 6,  FOUR_Y  = 4;

  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  if( answer_1 % 10 == 1 )
  {
    if( answer_6 % 10 == 1 )
    {
      // for 1: 2
      // for 6: 2

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      } 
    }
    else if( answer_6 % 10 == 3 )
    {
      // for 1: 2
      // for 6: 1-2

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }
    }
    else if( answer_6 % 10 == 7 )
    {
      // for 1: 2
      // for 6: 0-1-2

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_2_in_2[i][1];  
        for( int j = 0 ; j < 4 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }
    }
    else if( answer_6 % 10 == 6 )
    {
      // for 1: 2
      // for 6: 0-1

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }
    }
    else if( answer_6 % 10 == 4 )
    {
      // for 1: 2
      // for 6: 0

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }
    }
  }
  else if( answer_1 % 10 == 3 )
  {
    if( answer_6 % 10 == 1 )
    {
      // for 1: 1-2
      // for 6: 2

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_1_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }
    }
    else if( answer_6 % 10 == 3 )
    {
      // for 1: 1-2
      // for 6: 1-2

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_1_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }
    }
    else if( answer_6 % 10 == 7 )
    {
      // for 1: 1-2
      // for 6: 0-1-2

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_1_2_in_2[i][1];  
        for( int j = 0 ; j < 4 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 6 )
    {
      // for 1: 1-2
      // for 6: 0-1

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_1_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 4 )
    {
      // for 1: 1-2
      // for 6: 0

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_1_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
  }
  else if( answer_1 % 10 == 7 )
  {
    if( answer_6 % 10 == 1 )
    {
      // for 1: 0-1-2
      // for 6: 2

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      for( int i = 0 ; i < 4 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 3 )
    {
      // for 1: 0-1-2
      // for 6: 1-2

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 4 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 7 )
    {
      // for 1: 0-1-2
      // for 6: 0-1-2

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 4 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_2_in_2[i][1];  
        for( int j = 0 ; j < 4 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 6 )
    {
      // for 1: 0-1-2
      // for 6: 0-1

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      for( int i = 0 ; i < 4 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 4 )
    {
      // for 1: 0-1-2
      // for 6: 0

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      for( int i = 0 ; i < 4 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
  }
  else if( answer_1 % 10 == 6 )
  {
    if( answer_6 % 10 == 1 )
    {
      // for 1: 0-1
      // for 6: 2

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 3 )
    {
      // for 1: 0-1
      // for 6: 1-2

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 7 )
    {
      // for 1: 0-1
      // for 6: 0-1-2

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_in_2[i][1];  
        for( int j = 0 ; j < 4 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 6 )
    {
      // for 1: 0-1
      // for 6: 0-1

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }


    }
    else if( answer_6 % 10 == 4 )
    {
      // for 1: 0-1
      // for 6: 0

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
  }
  else if( answer_1 % 10 == 4 )
  {
    if( answer_6 % 10 == 1 )
    {
      // for 1: 0
      // for 6: 2

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 3 )
    {
      // for 1: 0
      // for 6: 1-2

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 7 )
    {
      // for 1: 0
      // for 6: 0-1-2

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_in_2[i][1];  
        for( int j = 0 ; j < 4 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 6 )
    {
      // for 1: 0
      // for 6: 0-1

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_6 % 10 == 4 )
    {
      // for 1: 0
      // for 6: 0

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_1_6_from_cols( temp_chessboard );
        }
      }

    }
  }

}

void choose_3_4_from_cols( bool chessboard[8][8] , int answer_3 , int answer_4 ) 
{
  
    int
  ONE_X   = 3,  ONE_Y   = 1,
  TWO_X   = 3,  TWO_Y   = 6,
  THREE_X = 4,  THREE_Y = 1,
  FOUR_X  = 4,  FOUR_Y  = 6;

  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  if( answer_3 % 10 == 1 )
  {
    if( answer_4 % 10 == 1 )
    {
      // for 1: 2
      // for 6: 2

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      } 
    }
    else if( answer_4 % 10 == 3 )
    {
      // for 1: 2
      // for 6: 1-2

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }
    }
    else if( answer_4 % 10 == 7 )
    {
      // for 1: 2
      // for 6: 0-1-2

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_2_in_2[i][1];  
        for( int j = 0 ; j < 4 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }
    }
    else if( answer_4 % 10 == 6 )
    {
      // for 1: 2
      // for 6: 0-1

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }
    }
    else if( answer_4 % 10 == 4 )
    {
      // for 1: 2
      // for 6: 0

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }
    }
  }
  else if( answer_3 % 10 == 3 )
  {
    if( answer_4 % 10 == 1 )
    {
      // for 1: 1-2
      // for 6: 2

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_1_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }
    }
    else if( answer_4 % 10 == 3 )
    {
      // for 1: 1-2
      // for 6: 1-2

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_1_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }
    }
    else if( answer_4 % 10 == 7 )
    {
      // for 1: 1-2
      // for 6: 0-1-2

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_1_2_in_2[i][1];  
        for( int j = 0 ; j < 4 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 6 )
    {
      // for 1: 1-2
      // for 6: 0-1

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_1_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 4 )
    {
      // for 1: 1-2
      // for 6: 0

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_1_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
  }
  else if( answer_3 % 10 == 7 )
  {
    if( answer_4 % 10 == 1 )
    {
      // for 1: 0-1-2
      // for 6: 2

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      for( int i = 0 ; i < 4 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 3 )
    {
      // for 1: 0-1-2
      // for 6: 1-2

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 4 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 7 )
    {
      // for 1: 0-1-2
      // for 6: 0-1-2

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 4 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_2_in_2[i][1];  
        for( int j = 0 ; j < 4 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 6 )
    {
      // for 1: 0-1-2
      // for 6: 0-1

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      for( int i = 0 ; i < 4 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_2_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 4 )
    {
      // for 1: 0-1-2
      // for 6: 0

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      for( int i = 0 ; i < 4 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_2_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_2_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
  }
  else if( answer_3 % 10 == 6 )
  {
    if( answer_4 % 10 == 1 )
    {
      // for 1: 0-1
      // for 6: 2

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 3 )
    {
      // for 1: 0-1
      // for 6: 1-2

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 7 )
    {
      // for 1: 0-1
      // for 6: 0-1-2

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_in_2[i][1];  
        for( int j = 0 ; j < 4 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 6 )
    {
      // for 1: 0-1
      // for 6: 0-1

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }


    }
    else if( answer_4 % 10 == 4 )
    {
      // for 1: 0-1
      // for 6: 0

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      for( int i = 0 ; i < 3 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_1_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_1_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
  }
  else if( answer_3 % 10 == 4 )
  {
    if( answer_4 % 10 == 1 )
    {
      // for 1: 0
      // for 6: 2

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      /*put 2 in 2*/
      bool put_2_in_2[1][2] = {
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 3 )
    {
      // for 1: 0
      // for 6: 1-2

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      /*put 1,2 in 2*/
      bool put_1_2_in_2[3][2] = {
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 7 )
    {
      // for 1: 0
      // for 6: 0-1-2

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      /*put 0,1,2 in 2*/
      bool put_0_1_2_in_2[4][2] = {
      {0,0},
      {1,0},
      {0,1},
      {1,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_in_2[i][1];  
        for( int j = 0 ; j < 4 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_2_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_2_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 6 )
    {
      // for 1: 0
      // for 6: 0-1

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      /*put 0,1 in 2*/
      bool put_0_1_in_2[3][2] = {
      {0,0},
      {1,0},
      {0,1}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_in_2[i][1];  
        for( int j = 0 ; j < 3 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_1_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_1_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
    else if( answer_4 % 10 == 4 )
    {
      // for 1: 0
      // for 6: 0

      /*put 0 in 2*/
      bool put_0_in_2[1][2] = {
      {0,0}
      };

      for( int i = 0 ; i < 1 ; i++ )
      {
        temp_chessboard[ONE_X][ONE_Y] = put_0_in_2[i][0];
        temp_chessboard[TWO_X][TWO_Y] = put_0_in_2[i][1];  
        for( int j = 0 ; j < 1 ; j++ )
        {
          temp_chessboard[THREE_X][THREE_Y] = put_0_in_2[i][0];
          temp_chessboard[FOUR_X][FOUR_Y] = put_0_in_2[i][1];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
          choosed_3_4_from_cols( temp_chessboard );
        }
      }

    }
  }
  
}

void choosed_1_6_from_cols(  bool chessboard[8][8]  )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  int
  sum1 = temp_chessboard[4][0] + temp_chessboard[2][2] + temp_chessboard[1][3],
  sum2 = temp_chessboard[1][4] + temp_chessboard[2][5] + temp_chessboard[4][7],
  sum3 = temp_chessboard[6][4] + temp_chessboard[5][5] + temp_chessboard[3][7],
  sum4 = temp_chessboard[3][0] + temp_chessboard[5][2] + temp_chessboard[6][3],
  FIRST_ONE_X  = 3, FIRST_ONE_Y  = 1, FIRST_TWO_X  = 0, FIRST_TWO_Y  = 4,
  SECOND_ONE_X = 0, SECOND_ONE_Y = 3, SECOND_TWO_X = 3, SECOND_TWO_Y = 6,
  THIRD_ONE_X  = 7, THIRD_ONE_Y  = 3, THIRD_TWO_X  = 4, THIRD_TWO_Y  = 6,
  FOURTH_ONE_X = 4, FOURTH_ONE_Y = 1, FOURTH_TWO_X = 7, FOURTH_TWO_Y = 4;

  if( white_diagonals[ 2 ] == sum1 % 2 )
  { // 00 11
    temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = 0;
    temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = 0;
      if( black_diagonals[ 2 ] == sum2 % 2 )
      { // 00 11
        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

      }
      else
      { // 01 10
        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }
        
      }

    temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = 1;
    temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = 1;
      if( black_diagonals[ 2 ] == sum2 % 2 )
      { // 00 11
        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

      }
      else
      { // 01 10
        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }
        
      }

  }
  else
  { // 01 10
    temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = 0;
    temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = 1;
        if( black_diagonals[ 2 ] == sum2 % 2 )
        { // 00 11
          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

        }
        else
        { // 01 10
          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }
          
        }

    temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = 1;
    temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = 0;
        if( black_diagonals[ 2 ] == sum2 % 2 )
        { // 00 11
          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

        }
        else
        { // 01 10
          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            }
        }
  }

}

// void choosed_1_6_from_cols(  bool ** chessboard  )
// {
//   bool temp_chessboard[8][8]; 
//   this->copy_chessboard( chessboard , temp_chessboard );

//   end_point( temp_chessboard );

// }

void choosed_3_4_from_cols(  bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );

  int
  sum1 = temp_chessboard[4][0] + temp_chessboard[3][1] + temp_chessboard[2][2],
  sum2 = temp_chessboard[2][5] + temp_chessboard[3][6] + temp_chessboard[4][7],
  sum3 = temp_chessboard[5][5] + temp_chessboard[4][6] + temp_chessboard[3][7],
  sum4 = temp_chessboard[3][0] + temp_chessboard[4][1] + temp_chessboard[5][2],
  FIRST_ONE_X  = 1, FIRST_ONE_Y  = 3, FIRST_TWO_X  = 0, FIRST_TWO_Y  = 4,
  SECOND_ONE_X = 0, SECOND_ONE_Y = 3, SECOND_TWO_X = 1, SECOND_TWO_Y = 4,
  THIRD_ONE_X  = 7, THIRD_ONE_Y  = 3, THIRD_TWO_X  = 6, THIRD_TWO_Y  = 4,
  FOURTH_ONE_X = 6, FOURTH_ONE_Y = 3, FOURTH_TWO_X = 7, FOURTH_TWO_Y = 4;

  if( white_diagonals[ 2 ] == sum1 % 2 )
  { // 00 11
    temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = 0;
    temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = 0;
      if( black_diagonals[ 2 ] == sum2 % 2 )
      { // 00 11
        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

      }
      else
      { // 01 10
        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }
        
      }

    temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = 1;
    temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = 1;
      if( black_diagonals[ 2 ] == sum2 % 2 )
      { // 00 11
        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

      }
      else
      { // 01 10
        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }

        temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
        temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
          if( white_diagonals[ 6 ] == sum3 % 2 )
          { // 00 11
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

          }
          else
          { // 01 10
            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
            temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
              if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            
          }
        
      }

  }
  else
  { // 01 10
    temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = 0;
    temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = 1;
        if( black_diagonals[ 2 ] == sum2 % 2 )
        { // 00 11
          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

        }
        else
        { // 01 10
          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }
          
        }

    temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = 1;
    temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = 0;
        if( black_diagonals[ 2 ] == sum2 % 2 )
        { // 00 11
          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

        }
        else
        { // 01 10
          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 0;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 1;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
              
            }

          temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = 1;
          temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = 0;
            if( white_diagonals[ 6 ] == sum3 % 2 )
            { // 00 11
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

            }
            else
            { // 01 10
              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 0;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 1;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }

              temp_chessboard[THIRD_ONE_X][THIRD_ONE_Y] = 1;
              temp_chessboard[THIRD_TWO_X][THIRD_TWO_Y] = 0;
                if( black_diagonals[ 6 ] == sum4 % 2 )
                { // 00 11
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                }
                else
                { // 01 10
                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 0;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 1;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );

                  temp_chessboard[FOURTH_ONE_X][FOURTH_ONE_Y] = 1;
                  temp_chessboard[FOURTH_TWO_X][FOURTH_TWO_Y] = 0;
                  #ifdef MIDDLE_RULE_CHECKER_ON
                  if (this->middle_rule_checker( temp_chessboard ) )
                  #endif
                  this->final2s_1( temp_chessboard );
                  
                }
            }
        }
  }

}

void final2s_1( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int
  sum1 =
  temp_chessboard[0][0] + temp_chessboard[0][2] + temp_chessboard[0][3] +
  temp_chessboard[0][4] + temp_chessboard[0][5] + temp_chessboard[0][7] ,
  sum2 =
  temp_chessboard[7][0] + temp_chessboard[7][2] + temp_chessboard[7][3] +
  temp_chessboard[7][4] + temp_chessboard[7][5] + temp_chessboard[7][7],
  FIRST_ONE_X  = 0, FIRST_ONE_Y  = 1, FIRST_TWO_X  = 0, FIRST_TWO_Y  = 6,
  SECOND_ONE_X = 7, SECOND_ONE_Y = 1, SECOND_TWO_X = 7, SECOND_TWO_Y = 6;

  if( sum1 == 0 && this->rows[FIRST_ONE_X] == 1 )
  { // 012
    /*put 0,1,2 in 2*/
    bool put_0_1_2_in_2[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 4 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 1 && this->rows[FIRST_ONE_X] == 1 )
  { // 012
    /*put 0,1,2 in 2*/
    bool put_0_1_2_in_2[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 4 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 2 && this->rows[FIRST_ONE_X] == 1 )
  { // 01
    /*put 0,1 in 2*/
    bool put_0_1_in_2[3][2] = {
    {0,0},
    {1,0},
    {0,1}
    };
    for( int i = 0 ; i < 3 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 2 && this->rows[FIRST_ONE_X] == 0 )
  { // 2
    /*put 2 in 2*/
    bool put_2_in_2[1][2] = {
    {1,1}
    };
    for( int i = 0 ; i < 1 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 3 && this->rows[FIRST_ONE_X] == 1 )
  { // 0
    /*put 0 in 2*/
    bool put_0_in_2[1][2] = {
    {0,0}
    };
    for( int i = 0 ; i < 1 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 3 && this->rows[FIRST_ONE_X] == 0 )
  { // 12
    /*put 1,2 in 2*/
    bool put_1_2_in_2[3][2] = {
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 3 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 4 && this->rows[FIRST_ONE_X] == 0 )
  { // 012
    /*put 0,1,2 in 2*/
    bool put_0_1_2_in_2[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 4 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 5 && this->rows[FIRST_ONE_X] == 0 )
  { // 012
    /*put 0,1,2 in 2*/
    bool put_0_1_2_in_2[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 4 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 6 && this->rows[FIRST_ONE_X] == 0 )
  { // 012
    /*put 0,1,2 in 2*/
    bool put_0_1_2_in_2[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 4 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->final2s_2( temp_chessboard );
            }
        }
    }
  }

}

void final2s_2( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int
  sum1 =
  temp_chessboard[0][1] + temp_chessboard[1][1] + temp_chessboard[3][1] +
  temp_chessboard[4][1] + temp_chessboard[6][1] + temp_chessboard[7][1] ,
  sum2 =
  temp_chessboard[5][0] + temp_chessboard[5][1] + temp_chessboard[5][2] +
  temp_chessboard[5][5] + temp_chessboard[5][6] + temp_chessboard[5][7],
  FIRST_ONE_X  = 2, FIRST_ONE_Y  = 1, FIRST_TWO_X  = 5, FIRST_TWO_Y  = 1,
  SECOND_ONE_X = 2, SECOND_ONE_Y = 6, SECOND_TWO_X = 5, SECOND_TWO_Y = 6;

  if( sum1 == 0 && this->cols[FIRST_ONE_Y] == 0 )
    { // 012
        /*put 0,1,2 in 2*/
        bool put_0_1_2_in_2[4][2] = {
        {0,0},
        {1,0},
        {0,1},
        {1,1}
        };
        for( int i = 0 ; i < 4 ; i++ )
        {
            temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
            temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
            if( sum2 == 0 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 1 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 2 && this->cols[SECOND_ONE_Y] == 0 )
            {  // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 1 )
            { // 2
                /*put 2 in 2*/
                bool newput_2_in_2[1][2] = {
                {1,1}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 0 )
            { // 01
                /*put 0,1 in 2*/
                bool put_0_1_in_2[3][2] = {
                {0,0},
                {1,0},
                {0,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_1_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_1_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 1 )
            { // 12
                /*put 1,2 in 2*/
                bool newput_1_2_in_2[3][2] = {
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 0 )
            { // 0
                /*put 0 in 2*/
                bool put_0_in_2[1][2] = {
                {0,0}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 5 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 6 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
        }
    }
    else if ( sum1 == 1 && this->cols[FIRST_ONE_Y] == 0 )
    { // 012
        /*put 0,1,2 in 2*/
        bool put_0_1_2_in_2[4][2] = {
        {0,0},
        {1,0},
        {0,1},
        {1,1}
        };
        for( int i = 0 ; i < 4 ; i++ )
        {
            temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
            temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
            if( sum2 == 0 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 1 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 2 && this->cols[SECOND_ONE_Y] == 0 )
            {  // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 1 )
            { // 2
                /*put 2 in 2*/
                bool newput_2_in_2[1][2] = {
                {1,1}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 0 )
            { // 01
                /*put 0,1 in 2*/
                bool put_0_1_in_2[3][2] = {
                {0,0},
                {1,0},
                {0,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_1_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_1_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 1 )
            { // 12
                /*put 1,2 in 2*/
                bool newput_1_2_in_2[3][2] = {
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 0 )
            { // 0
                /*put 0 in 2*/
                bool put_0_in_2[1][2] = {
                {0,0}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 5 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 6 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
        }
    }
    else if ( sum1 == 2 && this->cols[FIRST_ONE_Y] == 0 )
    {  // 012
        /*put 0,1,2 in 2*/
        bool put_0_1_2_in_2[4][2] = {
        {0,0},
        {1,0},
        {0,1},
        {1,1}
        };
        for( int i = 0 ; i < 4 ; i++ )
        {
            temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
            temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
            if( sum2 == 0 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 1 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 2 && this->cols[SECOND_ONE_Y] == 0 )
            {  // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 1 )
            { // 2
                /*put 2 in 2*/
                bool newput_2_in_2[1][2] = {
                {1,1}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 0 )
            { // 01
                /*put 0,1 in 2*/
                bool put_0_1_in_2[3][2] = {
                {0,0},
                {1,0},
                {0,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_1_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_1_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 1 )
            { // 12
                /*put 1,2 in 2*/
                bool newput_1_2_in_2[3][2] = {
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 0 )
            { // 0
                /*put 0 in 2*/
                bool put_0_in_2[1][2] = {
                {0,0}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 5 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 6 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
        }
    }
    else if ( sum1 == 3 && this->cols[FIRST_ONE_Y] == 1 )
    { // 2
        /*put 2 in 2*/
        bool put_2_in_2[1][2] = {
        {1,1}
        };
        for( int i = 0 ; i < 1 ; i++ )
        {
            temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_2_in_2[i][0];
            temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_2_in_2[i][1];
            if( sum2 == 0 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 1 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 2 && this->cols[SECOND_ONE_Y] == 0 )
            {  // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 1 )
            { // 2
                /*put 2 in 2*/
                bool newput_2_in_2[1][2] = {
                {1,1}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 0 )
            { // 01
                /*put 0,1 in 2*/
                bool put_0_1_in_2[3][2] = {
                {0,0},
                {1,0},
                {0,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_1_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_1_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 1 )
            { // 12
                /*put 1,2 in 2*/
                bool newput_1_2_in_2[3][2] = {
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 0 )
            { // 0
                /*put 0 in 2*/
                bool put_0_in_2[1][2] = {
                {0,0}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 5 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 6 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
        }
    }
    else if ( sum1 == 3 && this->cols[FIRST_ONE_Y] == 0 )
    { // 01
        /*put 0,1 in 2*/
        bool put_0_1_in_2[3][2] = {
        {0,0},
        {1,0},
        {0,1}
        };
        for( int i = 0 ; i < 3 ; i++ )
        {
            temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_in_2[i][0];
            temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_in_2[i][1];
            if( sum2 == 0 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 1 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 2 && this->cols[SECOND_ONE_Y] == 0 )
            {  // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 1 )
            { // 2
                /*put 2 in 2*/
                bool newput_2_in_2[1][2] = {
                {1,1}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 0 )
            { // 01
                /*put 0,1 in 2*/
                bool put_0_1_in_2[3][2] = {
                {0,0},
                {1,0},
                {0,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_1_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_1_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 1 )
            { // 12
                /*put 1,2 in 2*/
                bool newput_1_2_in_2[3][2] = {
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 0 )
            { // 0
                /*put 0 in 2*/
                bool put_0_in_2[1][2] = {
                {0,0}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 5 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 6 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
        }
    }
    else if ( sum1 == 4 && this->cols[FIRST_ONE_Y] == 1 )
    { // 12
        /*put 1,2 in 2*/
        bool put_1_2_in_2[3][2] = {
        {1,0},
        {0,1},
        {1,1}
        };
        for( int i = 0 ; i < 3 ; i++ )
        {
            temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_1_2_in_2[i][0];
            temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_1_2_in_2[i][1];
            if( sum2 == 0 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 1 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 2 && this->cols[SECOND_ONE_Y] == 0 )
            {  // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 1 )
            { // 2
                /*put 2 in 2*/
                bool newput_2_in_2[1][2] = {
                {1,1}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 0 )
            { // 01
                /*put 0,1 in 2*/
                bool put_0_1_in_2[3][2] = {
                {0,0},
                {1,0},
                {0,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_1_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_1_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 1 )
            { // 12
                /*put 1,2 in 2*/
                bool newput_1_2_in_2[3][2] = {
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 0 )
            { // 0
                /*put 0 in 2*/
                bool put_0_in_2[1][2] = {
                {0,0}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 5 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 6 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
        }
    }
    else if ( sum1 == 4 && this->cols[FIRST_ONE_Y] == 0 )
    { // 0
        /*put 0 in 2*/
        bool put_0_in_2[1][2] = {
        {0,0}
        };
        for( int i = 0 ; i < 1 ; i++ )
        {
            temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_in_2[i][0];
            temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_in_2[i][1];
            if( sum2 == 0 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 1 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 2 && this->cols[SECOND_ONE_Y] == 0 )
            {  // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 1 )
            { // 2
                /*put 2 in 2*/
                bool newput_2_in_2[1][2] = {
                {1,1}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 0 )
            { // 01
                /*put 0,1 in 2*/
                bool put_0_1_in_2[3][2] = {
                {0,0},
                {1,0},
                {0,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_1_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_1_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 1 )
            { // 12
                /*put 1,2 in 2*/
                bool newput_1_2_in_2[3][2] = {
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 0 )
            { // 0
                /*put 0 in 2*/
                bool put_0_in_2[1][2] = {
                {0,0}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 5 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 6 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
        }
    }
    else if ( sum1 == 5 && this->cols[FIRST_ONE_Y] == 1 )
    { // 012
        /*put 0,1,2 in 2*/
        bool put_0_1_2_in_2[4][2] = {
        {0,0},
        {1,0},
        {0,1},
        {1,1}
        };
        for( int i = 0 ; i < 4 ; i++ )
        {
            temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
            temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
            if( sum2 == 0 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 1 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 2 && this->cols[SECOND_ONE_Y] == 0 )
            {  // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 1 )
            { // 2
                /*put 2 in 2*/
                bool newput_2_in_2[1][2] = {
                {1,1}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 0 )
            { // 01
                /*put 0,1 in 2*/
                bool put_0_1_in_2[3][2] = {
                {0,0},
                {1,0},
                {0,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_1_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_1_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 1 )
            { // 12
                /*put 1,2 in 2*/
                bool newput_1_2_in_2[3][2] = {
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 0 )
            { // 0
                /*put 0 in 2*/
                bool put_0_in_2[1][2] = {
                {0,0}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 5 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 6 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
        }
    }
    else if ( sum1 == 6 && this->cols[FIRST_ONE_Y] == 1 )
    { // 012
        /*put 0,1,2 in 2*/
        bool put_0_1_2_in_2[4][2] = {
        {0,0},
        {1,0},
        {0,1},
        {1,1}
        };
        for( int i = 0 ; i < 4 ; i++ )
        {
            temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
            temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
            if( sum2 == 0 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 1 && this->cols[SECOND_ONE_Y] == 0 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 2 && this->cols[SECOND_ONE_Y] == 0 )
            {  // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 1 )
            { // 2
                /*put 2 in 2*/
                bool newput_2_in_2[1][2] = {
                {1,1}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 3 && this->cols[SECOND_ONE_Y] == 0 )
            { // 01
                /*put 0,1 in 2*/
                bool put_0_1_in_2[3][2] = {
                {0,0},
                {1,0},
                {0,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_1_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_1_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 1 )
            { // 12
                /*put 1,2 in 2*/
                bool newput_1_2_in_2[3][2] = {
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 3 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 4 && this->cols[SECOND_ONE_Y] == 0 )
            { // 0
                /*put 0 in 2*/
                bool put_0_in_2[1][2] = {
                {0,0}
                };
                for( int i = 0 ; i < 1 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = put_0_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = put_0_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 5 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
            else if ( sum2 == 6 && this->cols[SECOND_ONE_Y] == 1 )
            { // 012
                /*put 0,1,2 in 2*/
                bool newput_0_1_2_in_2[4][2] = {
                {0,0},
                {1,0},
                {0,1},
                {1,1}
                };
                for( int i = 0 ; i < 4 ; i++ )
                {
                    temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
                    temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
                    #ifdef MIDDLE_RULE_CHECKER_ON
                    if (this->middle_rule_checker( temp_chessboard ) )
                    #endif
                    this->final2s_3( temp_chessboard );
                }
            }
        }
    }

}

void final2s_3( bool chessboard[8][8] )
{
  bool temp_chessboard[8][8]; 
  this->copy_chessboard( chessboard , temp_chessboard );
  
  int
  sum1 =
  temp_chessboard[2][0] + temp_chessboard[2][1] + temp_chessboard[2][2] +
  temp_chessboard[2][5] + temp_chessboard[2][6] + temp_chessboard[2][7] ,
  sum2 =
  temp_chessboard[5][0] + temp_chessboard[5][1] + temp_chessboard[5][2] +
  temp_chessboard[5][5] + temp_chessboard[5][6] + temp_chessboard[5][7],
  FIRST_ONE_X  = 2, FIRST_ONE_Y  = 3, FIRST_TWO_X  = 2, FIRST_TWO_Y  = 4,
  SECOND_ONE_X = 5, SECOND_ONE_Y = 3, SECOND_TWO_X = 5, SECOND_TWO_Y = 4;

  if( sum1 == 0 && this->rows[FIRST_ONE_X] == 1 )
  { // 012
    /*put 0,1,2 in 2*/
    bool put_0_1_2_in_2[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 4 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 1 && this->rows[FIRST_ONE_X] == 1 )
  { // 012
    /*put 0,1,2 in 2*/
    bool put_0_1_2_in_2[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 4 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 2 && this->rows[FIRST_ONE_X] == 1 )
  { // 01
    /*put 0,1 in 2*/
    bool put_0_1_in_2[3][2] = {
    {0,0},
    {1,0},
    {0,1}
    };
    for( int i = 0 ; i < 3 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 2 && this->rows[FIRST_ONE_X] == 0 )
  { // 2
    /*put 2 in 2*/
    bool put_2_in_2[1][2] = {
    {1,1}
    };
    for( int i = 0 ; i < 1 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 3 && this->rows[FIRST_ONE_X] == 1 )
  { // 0
    /*put 0 in 2*/
    bool put_0_in_2[1][2] = {
    {0,0}
    };
    for( int i = 0 ; i < 1 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 3 && this->rows[FIRST_ONE_X] == 0 )
  { // 12
    /*put 1,2 in 2*/
    bool put_1_2_in_2[3][2] = {
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 3 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 4 && this->rows[FIRST_ONE_X] == 0 )
  { // 012
    /*put 0,1,2 in 2*/
    bool put_0_1_2_in_2[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 4 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 5 && this->rows[FIRST_ONE_X] == 0 )
  { // 012
    /*put 0,1,2 in 2*/
    bool put_0_1_2_in_2[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 4 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
    }
  }
  else if ( sum1 == 6 && this->rows[FIRST_ONE_X] == 0 )
  { // 012
    /*put 0,1,2 in 2*/
    bool put_0_1_2_in_2[4][2] = {
    {0,0},
    {1,0},
    {0,1},
    {1,1}
    };
    for( int i = 0 ; i < 4 ; i++ )
    {
      temp_chessboard[FIRST_ONE_X][FIRST_ONE_Y] = put_0_1_2_in_2[i][0];
      temp_chessboard[FIRST_TWO_X][FIRST_TWO_Y] = put_0_1_2_in_2[i][1];
      if( sum2 == 0 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 1 && this->rows[SECOND_ONE_X] == 1 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 1 )
        { // 01
            /*put 0,1 in 2*/
            bool newput_0_1_in_2[3][2] = {
            {0,0},
            {1,0},
            {0,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 2 && this->rows[SECOND_ONE_X] == 0 )
        { // 2
            /*put 2 in 2*/
            bool newput_2_in_2[1][2] = {
            {1,1}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 1 )
        { // 0
            /*put 0 in 2*/
            bool newput_0_in_2[1][2] = {
            {0,0}
            };
            for( int i = 0 ; i < 1 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 3 && this->rows[SECOND_ONE_X] == 0 )
        { // 12
            /*put 1,2 in 2*/
            bool newput_1_2_in_2[3][2] = {
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 3 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 4 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 5 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
        else if ( sum2 == 6 && this->rows[SECOND_ONE_X] == 0 )
        { // 012
            /*put 0,1,2 in 2*/
            bool newput_0_1_2_in_2[4][2] = {
            {0,0},
            {1,0},
            {0,1},
            {1,1}
            };
            for( int i = 0 ; i < 4 ; i++ )
            {
            temp_chessboard[SECOND_ONE_X][SECOND_ONE_Y] = newput_0_1_2_in_2[i][0];
            temp_chessboard[SECOND_TWO_X][SECOND_TWO_Y] = newput_0_1_2_in_2[i][1];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
            this->end_point( temp_chessboard );
            }
        }
    }
  }

}

// void choosed_3_4_from_cols(  bool ** chessboard  )
// {
//   bool temp_chessboard[8][8]; 
//   this->copy_chessboard( chessboard , temp_chessboard );

//   end_point( temp_chessboard );

// }

// ===============


void came_from_rows( bool ** temp_chessboard )
{
  // I should put sth here
}

void came_from_rows( bool temp_chessboard[8][8] )
{
  // I should put sth here
}

// ===============



void fill_2_cells_for_rows_1 ()
{
// ?? what is this function?!
// what does it do ?!
}

// bool **

// void end_point( bool ** temp_chessboard )
// {
//   this->reached_end_point = true;
//   this->print_chessboard( temp_chessboard );
//   cout << endl;
// }

void end_point( bool temp_chessboard[8][8] )
{
  this->reached_end_point = true;
  if( this->end_rule_checker( temp_chessboard ) )
  {
    this->print_chessboard( temp_chessboard );
    cout << endl;
  }
}

void start_nested_functions( bool ** temp_chessboard )
{
  this->white_diagonal( temp_chessboard );
}

void decompress_block( string block )
{

  this->setInputBuffer( block );

  // Step #0 - initializing:
  this->initializer();

  // Step #1 - Fill 4 corners:
  this->fill_4_corners();

  // Step #2 - Fill 4 centers:
  this->fill_4_centers();
  
  // Step #3 - calculate how many whites shall be placed:
  this->calculate_whites();

  // Step #4 - calculate how many blacks shall be placed: 
  this->calculate_blacks();
  
  // Step #5 - extract rules for columns:
  this->extract_rules_cols();

  // Step #6 - extract rules for rows:
  this->extract_rules_rows();

  // Step #7 - extract rules for white diagonal:
  this->extract_rules_white_diagonal();

  // Step #8 - extract rules for black diagonal:
  this->extract_rules_black_diagonal();

  this->copy_chessboard(this->chessboard, this->temp_chessboard);

  // Step #9 Call nested functions
  this->start_nested_functions( this->temp_chessboard );

  // Step #..? Check if reached the end_point()
  if( (! this->reached_end_point) && this->set_strategy )
  {
    cout << "Changing strategy!" << endl;
    this->change_strategy = true;
    this->copy_chessboard(this->chessboard, this->temp_chessboard);
    this->start_nested_functions( this->temp_chessboard );
  }


  
}


};

int main(int argc, char * argv[]) {

  // string input_buffer = "01111010111001011110101100001000010101110010010100000000";
  string input_buffer = argv[1];
  ChessBean cb_object;
  
  // decompress part
  cb_object.decompress_block( input_buffer );

 
  return 0;
}