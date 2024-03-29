/*
0 1 1 1 1 0 1 0 
0 1 0 1 0 0 0 1 
1 0 0 0 1 0 1 1 
0 0 0 0 1 0 1 0 
1 1 0 0 1 1 1 1 
1 1 0 0 0 0 0 1 
0 0 0 0 0 0 0 0 
1 0 0 1 1 0 0 0
*/


#include <iostream>

#ifndef NO_MIDDLE_RULE_CHECKER
#define MIDDLE_RULE_CHECKER_ON
#endif

using namespace std;

class ChessBean {
  public:

  int debug_counter = 0;

  string input_buffer;
  bool
  chessboard[8][8],
  cols[8],
  rows[8],
  black_diagonals[7],
  white_diagonals[7];
  int
  all_blacks,
  all_whites,
  remained_blacks,
  remained_whites;
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



  void debug_counter_plus_plus()
  {
    this->debug_counter++;
  }
  void print_chessboard(bool the_chessboard[8][8])
  {
    for (size_t i = 0; i < 8; i++) {
      for (size_t j = 0; j < 8; j++) {
        cout << the_chessboard[i][j] << " ";
      }
      cout << endl;
    }
  }
  void copy_chessboard( bool chessboard_1[8][8], bool chessboard_2[8][8])
  {
    for (size_t i = 0; i < 8; i++)
      for (size_t j = 0; j < 8; j++)
        chessboard_2[i][j] = chessboard_1[i][j];
  }
  void setInputBuffer( string input_buffer )
  {
    this->input_buffer = input_buffer;
  }
  void initializer()
  {
    for (size_t i = 0; i < 8; i++) {
      for (size_t j = 0; j < 8; j++) {
        this->chessboard[i][j] = 0;
      }
    }
  }
  void fill_4_corners()
  {
    this->chessboard[0][0] = (this->input_buffer[40] == '1');
    this->chessboard[0][7] = (this->input_buffer[41] == '1');
    this->chessboard[7][0] = (this->input_buffer[42] == '1');
    this->chessboard[7][7] = (this->input_buffer[43] == '1');
  }
  void fill_4_centers()
  {
    this->chessboard[3][3] = (this->input_buffer[44] == '1');
    this->chessboard[3][4] = (this->input_buffer[45] == '1');
    this->chessboard[4][3] = (this->input_buffer[46] == '1');
    this->chessboard[4][4] = (this->input_buffer[47] == '1');
  }
  void calculate_blacks_and_whites()
  {
    this->all_whites =
    (this->input_buffer[14] == '1') * 16 +
    (this->input_buffer[15] == '1') * 8 +
    (this->input_buffer[16] == '1') * 4 +
    (this->input_buffer[17] == '1') * 2 +
    (this->input_buffer[18] == '1') * 1;
    if (this->all_whites == 0)
      this->all_whites = (this->input_buffer[1] == '1') ? 32 : 0;
    this->remained_whites =
    this->all_whites -
    this->chessboard[0][0] -
    this->chessboard[3][3] -
    this->chessboard[4][4] -
    this->chessboard[7][7];
    this->all_blacks =
    (this->input_buffer[19] == '1') * 16 +
    (this->input_buffer[20] == '1') * 8 +
    (this->input_buffer[21] == '1') * 4 +
    (this->input_buffer[22] == '1') * 2 +
    (this->input_buffer[23] == '1') * 1;
    if (this->all_blacks == 0)
      this->all_blacks = (this->input_buffer[8] == '1') ? 32 : 0;
    this->remained_blacks =
    this->all_blacks -
    this->chessboard[0][7] -
    this->chessboard[3][4] -
    this->chessboard[4][3] -
    this->chessboard[7][0];

    cout << "all blacks:" << (int) this->all_blacks << endl;
    cout << "remained blacks:" << (int) this->remained_blacks << endl;
    cout << "all whites:" << (int) this->all_whites << endl;
    cout << "remained whites:" << (int) this->remained_whites << endl;
  }
  void extract_rules_cols_rows()
  {
    this->cols[0] = (this->input_buffer[24] == '1');
    this->cols[1] = (this->input_buffer[25] == '1');
    this->cols[2] = (this->input_buffer[26] == '1');
    this->cols[3] = (this->input_buffer[27] == '1');
    this->cols[4] = (this->input_buffer[28] == '1');
    this->cols[5] = (this->input_buffer[29] == '1');
    this->cols[6] = (this->input_buffer[30] == '1');
    this->cols[7] = (this->input_buffer[31] == '1');
    this->rows[0] = (this->input_buffer[32] == '1');
    this->rows[1] = (this->input_buffer[33] == '1');
    this->rows[2] = (this->input_buffer[34] == '1');
    this->rows[3] = (this->input_buffer[35] == '1');
    this->rows[4] = (this->input_buffer[36] == '1');
    this->rows[5] = (this->input_buffer[37] == '1');
    this->rows[6] = (this->input_buffer[38] == '1');
    this->rows[7] = (this->input_buffer[39] == '1');
  }
  void extract_rules_diagonals()
  {
    this->white_diagonals[0] = (this->input_buffer[0] == '1');
    this->white_diagonals[1] = (this->input_buffer[1] == '1');
    this->white_diagonals[2] = (this->input_buffer[2] == '1');
    this->white_diagonals[3] = (this->input_buffer[3] == '1');
    this->white_diagonals[4] = (this->input_buffer[4] == '1');
    this->white_diagonals[5] = (this->input_buffer[5] == '1');
    this->white_diagonals[6] = (this->input_buffer[6] == '1');
    this->black_diagonals[0] = (this->input_buffer[7] == '1');
    this->black_diagonals[1] = (this->input_buffer[8] == '1');
    this->black_diagonals[2] = (this->input_buffer[9] == '1');
    this->black_diagonals[3] = (this->input_buffer[10] == '1');
    this->black_diagonals[4] = (this->input_buffer[11] == '1');
    this->black_diagonals[5] = (this->input_buffer[12] == '1');
    this->black_diagonals[6] = (this->input_buffer[13] == '1');
  }
  void start_nested_functions( bool the_chessboard[8][8] )
  {
    bool temp_chessboard[8][8];
    this->copy_chessboard( the_chessboard , temp_chessboard );
    this->white_diagonal( temp_chessboard );
  }
  bool check_rules_cols_demo(bool the_chessboard[8][8]) {
    int sum;
    for (size_t i = 0; i < 8; i++) {
      sum = 0;
      for (size_t j = 0; j < 8; j++)
        sum += (int) the_chessboard[j][i];
      if (this->cols[i] == 0)
        if (sum > 4)
          return false;
    }
    return true;
  }
  bool check_rules_rows_demo(bool the_chessboard[8][8]) {
    int sum;
    for (size_t i = 0; i < 8; i++) {
      sum = 0;
      for (size_t j = 0; j < 8; j++)
        sum += (int) the_chessboard[i][j];
      if (this->rows[i] == 1)
        if (sum >= 4)
          return false;
    }
    return true;
  }
  bool check_rules_remained_blacks_demo(bool the_chessboard[8][8]) {
    return (
      the_chessboard[0][1] +
      the_chessboard[0][3] +
      the_chessboard[0][5] +
      the_chessboard[1][0] +
      the_chessboard[1][2] +
      the_chessboard[1][4] +
      the_chessboard[1][6] +
      the_chessboard[2][1] +
      the_chessboard[2][3] +
      the_chessboard[2][5] +
      the_chessboard[2][7] +
      the_chessboard[3][0] +
      the_chessboard[3][2] +
      the_chessboard[3][6] +
      the_chessboard[4][1] +
      the_chessboard[4][5] +
      the_chessboard[4][7] +
      the_chessboard[5][0] +
      the_chessboard[5][2] +
      the_chessboard[5][4] +
      the_chessboard[5][6] +
      the_chessboard[6][1] +
      the_chessboard[6][3] +
      the_chessboard[6][5] +
      the_chessboard[6][7] +
      the_chessboard[7][2] +
      the_chessboard[7][4] +
      the_chessboard[7][6]) <= (int) this->remained_blacks;
  }
  bool check_rules_remained_whites_demo(bool the_chessboard[8][8]) {
    return (
      the_chessboard[0][2] +
      the_chessboard[0][4] +
      the_chessboard[0][6] +
      the_chessboard[1][1] +
      the_chessboard[1][3] +
      the_chessboard[1][5] +
      the_chessboard[1][7] +
      the_chessboard[2][0] +
      the_chessboard[2][2] +
      the_chessboard[2][4] +
      the_chessboard[2][6] +
      the_chessboard[3][1] +
      the_chessboard[3][5] +
      the_chessboard[3][7] +
      the_chessboard[4][0] +
      the_chessboard[4][2] +
      the_chessboard[4][6] +
      the_chessboard[5][1] +
      the_chessboard[5][3] +
      the_chessboard[5][5] +
      the_chessboard[5][7] +
      the_chessboard[6][0] +
      the_chessboard[6][2] +
      the_chessboard[6][4] +
      the_chessboard[6][6] +
      the_chessboard[7][1] +
      the_chessboard[7][3] +
      the_chessboard[7][5]) <= (int) this->remained_whites;
  }
  bool middle_rule_checker(bool the_chessboard[8][8])
  {
    #ifdef DUMP_WHY_FAILED
    if( !(
      this->check_rules_cols_demo(the_chessboard) &&
      this->check_rules_rows_demo(the_chessboard) &&
      this->check_rules_remained_blacks_demo(the_chessboard) &&
      this->check_rules_remained_whites_demo(the_chessboard)
    ) )
    {
      cout << endl << "++++++DEBUG++++++" << endl;
      cout << "check_rules_cols_demo : " << this->check_rules_cols_demo(the_chessboard) << endl 
      << "check_rules_rows_demo : " << this->check_rules_rows_demo(the_chessboard) << endl 
      << "check_rules_remained_blacks_demo : " << this->check_rules_remained_blacks_demo(the_chessboard) << endl 
      << "check_rules_remained_whites_demo : " << this->check_rules_remained_whites_demo(the_chessboard) << endl;
      this->print_chessboard( the_chessboard );
      cout << endl << "======DEBUG======" << endl;
    }
    #endif
    return (
      this->check_rules_cols_demo(the_chessboard) &&
      this->check_rules_rows_demo(the_chessboard) &&
      this->check_rules_remained_blacks_demo(the_chessboard) &&
      this->check_rules_remained_whites_demo(the_chessboard)
    );
  }
  void white_diagonal( bool the_chessboard[8][8] )
  {
    bool temp_chessboard[8][8]; 
    this->copy_chessboard( the_chessboard , temp_chessboard );
    int white_diagonal_placed_beans = (int)
    (temp_chessboard[0][0] +
      temp_chessboard[3][3] +
      temp_chessboard[4][4] +
      temp_chessboard[7][7]
    );
    if (white_diagonal_placed_beans == 0) {
      if (white_diagonals[0]) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][1] = this->diagonal_1_3[i][0];
          temp_chessboard[2][2] = this->diagonal_1_3[i][1];
          temp_chessboard[5][5] = this->diagonal_1_3[i][2];
          temp_chessboard[6][6] = this->diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->black_diagonal(temp_chessboard);
        }
      } else {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][1] = this->diagonal_0_2_4[i][0];
            temp_chessboard[2][2] = this->diagonal_0_2_4[i][1];
            temp_chessboard[5][5] = this->diagonal_0_2_4[i][2];
            temp_chessboard[6][6] = this->diagonal_0_2_4[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->black_diagonal(temp_chessboard);
        }
      }
    } else if (white_diagonal_placed_beans == 1) {
      if (white_diagonals[0]) {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][1] = this->diagonal_0_2_4[i][0];
            temp_chessboard[2][2] = this->diagonal_0_2_4[i][1];
            temp_chessboard[5][5] = this->diagonal_0_2_4[i][2];
            temp_chessboard[6][6] = this->diagonal_0_2_4[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->black_diagonal(temp_chessboard);
        }
      } else {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][1] = this->diagonal_1_3[i][0];
            temp_chessboard[2][2] = this->diagonal_1_3[i][1];
            temp_chessboard[5][5] = this->diagonal_1_3[i][2];
            temp_chessboard[6][6] = this->diagonal_1_3[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->black_diagonal(temp_chessboard);
        }
      }
    } else if (white_diagonal_placed_beans == 2) {
      if (white_diagonals[0]) {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][1] = this->diagonal_1_3[i][0];
            temp_chessboard[2][2] = this->diagonal_1_3[i][1];
            temp_chessboard[5][5] = this->diagonal_1_3[i][2];
            temp_chessboard[6][6] = this->diagonal_1_3[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->black_diagonal(temp_chessboard);
        }
      } else {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][1] = this->diagonal_0_2_4[i][0];
            temp_chessboard[2][2] = this->diagonal_0_2_4[i][1];
            temp_chessboard[5][5] = this->diagonal_0_2_4[i][2];
            temp_chessboard[6][6] = this->diagonal_0_2_4[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->black_diagonal(temp_chessboard);

        }
      }
    } else if (white_diagonal_placed_beans == 3) {
      if (white_diagonals[0]) {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][1] = this->diagonal_0_2_4[i][0];
            temp_chessboard[2][2] = this->diagonal_0_2_4[i][1];
            temp_chessboard[5][5] = this->diagonal_0_2_4[i][2];
            temp_chessboard[6][6] = this->diagonal_0_2_4[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->black_diagonal(temp_chessboard);
        }
      } else {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][1] = this->diagonal_1_3[i][0];
            temp_chessboard[2][2] = this->diagonal_1_3[i][1];
            temp_chessboard[5][5] = this->diagonal_1_3[i][2];
            temp_chessboard[6][6] = this->diagonal_1_3[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->black_diagonal(temp_chessboard);
        }
      }
    } else if (white_diagonal_placed_beans == 4) {
      if (white_diagonals[0]) {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][1] = this->diagonal_1_3[i][0];
            temp_chessboard[2][2] = this->diagonal_1_3[i][1];
            temp_chessboard[5][5] = this->diagonal_1_3[i][2];
            temp_chessboard[6][6] = this->diagonal_1_3[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->black_diagonal(temp_chessboard);
        }
      } else {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][1] = this->diagonal_0_2_4[i][0];
            temp_chessboard[2][2] = this->diagonal_0_2_4[i][1];
            temp_chessboard[5][5] = this->diagonal_0_2_4[i][2];
            temp_chessboard[6][6] = this->diagonal_0_2_4[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->black_diagonal(temp_chessboard);
        }
      }
    }
  }
  void black_diagonal( bool the_chessboard[8][8] )
  {
    bool temp_chessboard[8][8]; 
    this->copy_chessboard( the_chessboard , temp_chessboard );
    int black_diagonal_placed_beans = (int)
    (temp_chessboard[0][7] +
      temp_chessboard[3][4] +
      temp_chessboard[4][3] +
      temp_chessboard[7][0]
    );
    if (black_diagonal_placed_beans == 0) {
      if (black_diagonals[0]) {
        for (int i = 0; i < 8; i++) {
          temp_chessboard[1][6] = this->diagonal_1_3[i][0];
          temp_chessboard[2][5] = this->diagonal_1_3[i][1];
          temp_chessboard[5][2] = this->diagonal_1_3[i][2];
          temp_chessboard[6][1] = this->diagonal_1_3[i][3];
          #ifdef MIDDLE_RULE_CHECKER_ON
          if (this->middle_rule_checker( temp_chessboard ) )
          #endif
            this->little_white_diagonal_1(temp_chessboard);
        }
      } else {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][6] = this->diagonal_0_2_4[i][0];
            temp_chessboard[2][5] = this->diagonal_0_2_4[i][1];
            temp_chessboard[5][2] = this->diagonal_0_2_4[i][2];
            temp_chessboard[6][1] = this->diagonal_0_2_4[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->little_white_diagonal_1(temp_chessboard);
        }
      }
    } else if (black_diagonal_placed_beans == 1) {
      if (black_diagonals[0]) {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][6] = this->diagonal_0_2_4[i][0];
            temp_chessboard[2][5] = this->diagonal_0_2_4[i][1];
            temp_chessboard[5][2] = this->diagonal_0_2_4[i][2];
            temp_chessboard[6][1] = this->diagonal_0_2_4[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif 
              this->little_white_diagonal_1(temp_chessboard);
        }
      } else {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][6] = this->diagonal_1_3[i][0];
            temp_chessboard[2][5] = this->diagonal_1_3[i][1];
            temp_chessboard[5][2] = this->diagonal_1_3[i][2];
            temp_chessboard[6][1] = this->diagonal_1_3[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->little_white_diagonal_1(temp_chessboard);
        }
      }
    } else if (black_diagonal_placed_beans == 2) {
      if (black_diagonals[0]) {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][6] = this->diagonal_1_3[i][0];
            temp_chessboard[2][5] = this->diagonal_1_3[i][1];
            temp_chessboard[5][2] = this->diagonal_1_3[i][2];
            temp_chessboard[6][1] = this->diagonal_1_3[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->little_white_diagonal_1(temp_chessboard);
        }
      } else {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][6] = this->diagonal_0_2_4[i][0];
            temp_chessboard[2][5] = this->diagonal_0_2_4[i][1];
            temp_chessboard[5][2] = this->diagonal_0_2_4[i][2];
            temp_chessboard[6][1] = this->diagonal_0_2_4[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->little_white_diagonal_1(temp_chessboard);
        }
      }
    } else if (black_diagonal_placed_beans == 3) {
      if (black_diagonals[0]) {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][6] = this->diagonal_0_2_4[i][0];
            temp_chessboard[2][5] = this->diagonal_0_2_4[i][1];
            temp_chessboard[5][2] = this->diagonal_0_2_4[i][2];
            temp_chessboard[6][1] = this->diagonal_0_2_4[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->little_white_diagonal_1(temp_chessboard);
        }
      } else {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][6] = this->diagonal_1_3[i][0];
            temp_chessboard[2][5] = this->diagonal_1_3[i][1];
            temp_chessboard[5][2] = this->diagonal_1_3[i][2];
            temp_chessboard[6][1] = this->diagonal_1_3[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->little_white_diagonal_1(temp_chessboard);
        }
      }
    } else if (black_diagonal_placed_beans == 4) {
      if (black_diagonals[0]) {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][6] = this->diagonal_1_3[i][0];
            temp_chessboard[2][5] = this->diagonal_1_3[i][1];
            temp_chessboard[5][2] = this->diagonal_1_3[i][2];
            temp_chessboard[6][1] = this->diagonal_1_3[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->little_white_diagonal_1(temp_chessboard);
        }
      } else {
        for (int i = 0; i < 8; i++) {
            temp_chessboard[1][6] = this->diagonal_0_2_4[i][0];
            temp_chessboard[2][5] = this->diagonal_0_2_4[i][1];
            temp_chessboard[5][2] = this->diagonal_0_2_4[i][2];
            temp_chessboard[6][1] = this->diagonal_0_2_4[i][3];
            #ifdef MIDDLE_RULE_CHECKER_ON
            if (this->middle_rule_checker( temp_chessboard ) )
            #endif
              this->little_white_diagonal_1(temp_chessboard);
        }
      }
    }
  }
  void little_white_diagonal_1( bool the_chessboard[8][8] )
  {
    bool temp_chessboard[8][8]; 
    this->copy_chessboard( the_chessboard , temp_chessboard );
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
  void little_white_diagonal_2( bool the_chessboard[8][8] )
  {
    bool temp_chessboard[8][8]; 
    this->copy_chessboard( the_chessboard , temp_chessboard );
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
  void little_black_diagonal_1( bool the_chessboard[8][8] )
  {
    bool temp_chessboard[8][8]; 
    this->copy_chessboard( the_chessboard , temp_chessboard );

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
  void little_black_diagonal_2( bool the_chessboard[8][8] )
  {
    bool temp_chessboard[8][8]; 
    this->copy_chessboard( the_chessboard , temp_chessboard );
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
  void choosing_strategy( bool the_chessboard[8][8] )
  {
    bool temp_chessboard[8][8]; 
    this->copy_chessboard( the_chessboard , temp_chessboard );
    this->complete_4_cols_1( temp_chessboard ); 
  }
  void complete_4_cols_1( bool the_chessboard[8][8] )
  {
    bool temp_chessboard[8][8]; 
    this->copy_chessboard( the_chessboard , temp_chessboard );
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
  void came_from_cols( bool the_chessboard[8][8] )
  {
    // this->print_chessboard( the_chessboard ); cout<<endl;
    debug_counter_plus_plus();
  }
  // this->print_chessboard( chessboard ); cout<<endl;
  void decompress_block( string block )
  {
    this->setInputBuffer( block );  
    this->initializer();
    this->fill_4_corners();
    this->fill_4_centers();
    this->calculate_blacks_and_whites();
    this->extract_rules_cols_rows();
    this->extract_rules_diagonals();
    this->start_nested_functions( this->chessboard );
    cout<<this->debug_counter<<endl;
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