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
#include <iostream>

using namespace std;

// bool check_rules_cols(bool[8][8], bool[8]);
// bool check_rules_cols_demo(bool[8][8], bool[8]);
// bool check_rules_rows(bool[8][8], bool[8]);
// bool check_rules_rows_demo(bool[8][8], bool[8]);
// bool check_rules_sum_whites(bool[8][8], unsigned char);
// bool check_rules_remained_whites(bool[8][8], unsigned char);
// bool check_rules_remained_whites_demo(bool[8][8], unsigned char);
// bool check_rules_sum_blacks(bool[8][8], unsigned char);
// bool check_rules_remained_blacks(bool[8][8], unsigned char);
// bool check_rules_remained_blacks_demo(bool[8][8], unsigned char);
// void copy_chessboard(bool[8][8], bool **);

// bool check_rules_cols(bool **, bool[8]);
// bool check_rules_cols_demo(bool **, bool[8]);
// bool check_rules_rows(bool **, bool[8]);
// bool check_rules_rows_demo(bool **, bool[8]);
// bool check_rules_sum_whites(bool **, unsigned char);
// bool check_rules_remained_whites(bool **, unsigned char);
// bool check_rules_remained_whites_demo(bool **, unsigned char);
// bool check_rules_sum_blacks(bool **, unsigned char);
// bool check_rules_remained_blacks(bool **, unsigned char);
// bool check_rules_remained_blacks_demo(bool **, unsigned char);
// void copy_chessboard(bool **, bool[8][8]);

// void print_chessboard(bool[8][8]);
// void print_chessboard(bool **);

class ChessBean {
  public:

    string input_buffer;
    char one = '1', zero = '0';
    bool chessboard[8][8];

    // bool temp_chessboard[8][8]; 
    bool ** temp_chessboard = new bool * [8]; 


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
        sum += (int) chessboard[i][j];
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
        sum += (int) chessboard[j][i];
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

  void copy_chessboard(bool chessboard[8][8], bool ** temp_chessboard) {
    for (size_t i = 0; i < 8; i++)
      for (size_t j = 0; j < 8; j++)
        temp_chessboard[i][j] = chessboard[i][j];
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
        sum += (int) chessboard[i][j];
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
        sum += (int) chessboard[j][i];
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

  void copy_chessboard(bool ** chessboard, bool temp_chessboard[8][8]) {
    for (size_t i = 0; i < 8; i++)
      for (size_t j = 0; j < 8; j++)
        temp_chessboard[i][j] = chessboard[i][j];
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

void white_diagonal(bool temp_chessboard[8][8] , bool white_diagonals[7] , bool rows[8] , bool cols[8] ) {
  int white_diagonal_placed_beans = (int)
  (temp_chessboard[0][0] +
    temp_chessboard[3][3] +
    temp_chessboard[4][4] +
    temp_chessboard[7][7]
  );
  // for black diagonal
  if (white_diagonal_placed_beans == 0) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        temp_chessboard[1][1] = diagonal_1_3[i][0];
        temp_chessboard[2][2] = diagonal_1_3[i][1];
        temp_chessboard[5][5] = diagonal_1_3[i][2];
        temp_chessboard[6][6] = diagonal_1_3[i][3];
        if (this->check_rules_cols_demo(temp_chessboard, cols) &&
          this->check_rules_rows_demo(temp_chessboard, rows) &&
          this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
          this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
        ) {
          // code

          this->print_chessboard(temp_chessboard);
          cout << endl;
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    }
  } else if (white_diagonal_placed_beans == 1) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    }
  } else if (white_diagonal_placed_beans == 2) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    }
  } else if (white_diagonal_placed_beans == 3) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    }
  } else if (white_diagonal_placed_beans == 4) {
    if (white_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_1_3[i][0];
          temp_chessboard[2][2] = diagonal_1_3[i][1];
          temp_chessboard[5][5] = diagonal_1_3[i][2];
          temp_chessboard[6][6] = diagonal_1_3[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = diagonal_0_2_4[i][0];
          temp_chessboard[2][2] = diagonal_0_2_4[i][1];
          temp_chessboard[5][5] = diagonal_0_2_4[i][2];
          temp_chessboard[6][6] = diagonal_0_2_4[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    }
  }
}


void black_diagonal(bool temp_chessboard[8][8]  , bool black_diagonals[7] , bool rows[8] , bool cols[8] ) {
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
        if (this->check_rules_cols_demo(temp_chessboard, cols) &&
          this->check_rules_rows_demo(temp_chessboard, rows) &&
          this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
          this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
        ) {
          // code

          this->print_chessboard(temp_chessboard);
          cout << endl;
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    }
  } else if (black_diagonal_placed_beans == 1) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    }
  } else if (black_diagonal_placed_beans == 2) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    }
  } else if (black_diagonal_placed_beans == 3) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    }
  } else if (black_diagonal_placed_beans == 4) {
    if (black_diagonals[0]) {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_1_3[i][0];
          temp_chessboard[2][5] = diagonal_1_3[i][1];
          temp_chessboard[5][2] = diagonal_1_3[i][2];
          temp_chessboard[6][1] = diagonal_1_3[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = diagonal_0_2_4[i][0];
          temp_chessboard[2][5] = diagonal_0_2_4[i][1];
          temp_chessboard[5][2] = diagonal_0_2_4[i][2];
          temp_chessboard[6][1] = diagonal_0_2_4[i][3];
          if (this->check_rules_cols_demo(temp_chessboard, cols) &&
            this->check_rules_rows_demo(temp_chessboard, rows) &&
            this->check_rules_remained_blacks_demo(temp_chessboard, remained_blacks) &&
            this->check_rules_remained_whites_demo(temp_chessboard, remained_whites)
          ) {
            // code

            this->print_chessboard(temp_chessboard);
            cout << endl;
          }
        }
      }
    }
  }
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

  this->copy_chessboard(chessboard, temp_chessboard);

  // Step #9
  
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