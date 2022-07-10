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

bool check_rules_cols( bool[8][8] , bool[8] );
bool check_rules_cols_demo( bool[8][8] , bool[8] );
bool check_rules_rows( bool[8][8] , bool[8] );
bool check_rules_rows_demo( bool[8][8] , bool[8] );
bool check_rules_sum_whites( bool[8][8] , unsigned char );
bool check_rules_remained_whites( bool[8][8] , unsigned char );
bool check_rules_remained_whites_demo( bool[8][8] , unsigned char );
bool check_rules_sum_blacks( bool[8][8] , unsigned char );
bool check_rules_remained_blacks( bool[8][8] , unsigned char );
bool check_rules_remained_blacks_demo( bool[8][8] , unsigned char );
void copy_chessboard( bool[8][8], bool ** );

int main(int argc, char *argv[])
{

    // string input_buffer = "01111010111001011110101100001000010101110010010100000000";
    string input_buffer = argv[ 1 ];
    char  one = '1' ,  zero = '0';
    bool chessboard[8][8]; 
    
    // bool temp_chessboard[8][8]; 
    bool **temp_chessboard;
    temp_chessboard = new bool *[8];
    for(int i = 0; i <8; i++)
        temp_chessboard[i] = new bool[8];

    bool cols[8]; 
    bool rows[8]; 
    unsigned char all_blacks, all_whites, remained_blacks, remained_whites;

    // /*All possible values for a column.*/
    // unsigned char cols_possible_values[8][5] = {
    // {0,1,2,3,4},
    // {5,6,7,8}
    // };

    // /*All possible values for a row.*/
    // unsigned char rows_possible_values[8][5] = {
    // {4,5,6,7,8},
    // {0,1,2,3}
    // };

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


    // Initialize boolean array
    for(size_t i = 0; i < 8; i++){
        for(size_t j = 0; j < 8; j++){
            chessboard[i][j] = 0;
        }
    }

    // decompress part

    // Step #1 - Fill 4 corners:
    chessboard[0][0] = ( input_buffer[40] == one );
    chessboard[0][7] = ( input_buffer[41] == one );
    chessboard[7][0] = ( input_buffer[42] == one );
    chessboard[7][7] = ( input_buffer[43] == one );

    // Step #2 - Fill 4 centers:
    chessboard[3][3] = ( input_buffer[44] == one );
    chessboard[3][4] = ( input_buffer[45] == one );
    chessboard[4][3] = ( input_buffer[46] == one );
    chessboard[4][4] = ( input_buffer[47] == one );

    // Step #3 - calculate how many whites shall be placed:
    all_whites =
    ( input_buffer[14] == one ) * 16 +
    ( input_buffer[15] == one ) * 8  +
    ( input_buffer[16] == one ) * 4  +
    ( input_buffer[17] == one ) * 2  +
    ( input_buffer[18] == one ) * 1  ;
    if( all_whites == 0 )
        all_whites = ( input_buffer[1] == one )? 32 : 0 ;
    remained_whites = all_whites
    - chessboard[0][0]
    - chessboard[3][3]
    - chessboard[4][4]
    - chessboard[7][7];

    cout << "all whites:" << (int) all_whites << endl;
    cout << "remained whites:" << (int) remained_whites << endl;

    // Step #4 - calculate how many blacks shall be placed: 
    all_blacks =
    ( input_buffer[19] == one ) * 16 +
    ( input_buffer[20] == one ) * 8  +
    ( input_buffer[21] == one ) * 4  +
    ( input_buffer[22] == one ) * 2  +
    ( input_buffer[23] == one ) * 1  ;
    if( all_blacks == 0 )
        all_blacks = ( input_buffer[8] == one )? 32 : 0 ;
    remained_blacks = all_blacks
    - chessboard[0][7]
    - chessboard[3][4]
    - chessboard[4][3]
    - chessboard[7][0];

    cout << "all blacks:" << (int) all_blacks << endl;
    cout << "remained blacks:" << (int) remained_blacks << endl;

    // Step #5 - extract rules for columns:
    cols[0] = ( input_buffer[24] == one );
    cols[1] = ( input_buffer[25] == one );
    cols[2] = ( input_buffer[26] == one );
    cols[3] = ( input_buffer[27] == one );
    cols[4] = ( input_buffer[28] == one );
    cols[5] = ( input_buffer[29] == one );
    cols[6] = ( input_buffer[30] == one );
    cols[7] = ( input_buffer[31] == one );

    // Step #6 - extract rules for rows:
    rows[0] = ( input_buffer[32] == one );
    rows[1] = ( input_buffer[33] == one );
    rows[2] = ( input_buffer[34] == one );
    rows[3] = ( input_buffer[35] == one );
    rows[4] = ( input_buffer[36] == one );
    rows[5] = ( input_buffer[37] == one );
    rows[6] = ( input_buffer[38] == one );
    rows[7] = ( input_buffer[39] == one );

    // cout << check_rules_cols_demo( chessboard , cols ) << endl;
    // cout << check_rules_rows_demo( chessboard , rows ) << endl;

    // cout << check_rules_remained_whites( chessboard , remained_whites ) << endl;
    // cout << check_rules_remained_blacks( chessboard , remained_blacks ) << endl;
    // cout << check_rules_remained_whites_demo( chessboard , remained_whites ) << endl;
    // cout << check_rules_remained_blacks_demo( chessboard , remained_blacks ) << endl;


    // Actually, Let's get serious!


    copy_chessboard( chessboard , temp_chessboard );

    for(size_t i = 0; i < 8; i++){
        for(size_t j = 0; j < 8; j++){
            cout << temp_chessboard[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

// ===========================================================================
// ---------------------------------------------------------------------------
// ---------------------------------FUNCTIONS---------------------------------
// ---------------------------------------------------------------------------
// ===========================================================================



bool check_rules_cols( bool chessboard[8][8], bool cols[8]  )
{
    //This function can be used, only if we have a complete final chessboard 
    int sum;
    for(size_t i = 0; i < 8; i++){
        sum = 0;
        for(size_t j = 0; j < 8; j++)
            sum += (int) chessboard[i][j];
        if( cols[i] == 0 )
            if( sum > 4 )
                return false;
        else if( cols[i] == 1 )
            if( sum <= 4 )
                return false;
    }
    return true;
}

bool check_rules_rows( bool chessboard[8][8], bool rows[8]  )
{
    //This function can be used, only if we have a complete final chessboard 
    int sum;
    for(size_t i = 0; i < 8; i++){
        sum = 0;
        for(size_t j = 0; j < 8; j++)
            sum += (int) chessboard[j][i];
        if( rows[i] == 0 )
            if( sum < 4 )
                return false;
        else if( rows[i] == 1 )
            if( sum >= 4 )
                return false;
    }
    return true;
}

bool check_rules_cols_demo( bool chessboard[8][8], bool cols[8]  )
{
    //This function can be used in any state
    int sum;
    for(size_t i = 0; i < 8; i++){
        sum = 0;
        for(size_t j = 0; j < 8; j++)
            sum += (int) chessboard[i][j];
        if( cols[i] == 0 )
            if( sum > 4 )
                return false;
    }
    return true;
}

bool check_rules_rows_demo( bool chessboard[8][8], bool rows[8]  )
{
    //This function can be used, in any state
    int sum;
    for(size_t i = 0; i < 8; i++){
        sum = 0;
        for(size_t j = 0; j < 8; j++)
            sum += (int) chessboard[j][i];
        if( rows[i] == 1 )
            if( sum >= 4 )
                return false;
    }
    return true;
}

bool check_rules_sum_whites( bool chessboard[8][8] , unsigned char sum_whites )
{
    //This function can be used, only if we have a complete final chessboard 
    return (
    chessboard[0][0] +
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

bool check_rules_sum_blacks( bool chessboard[8][8] , unsigned char sum_blacks )
{
    //This function can be used, only if we have a complete final chessboard 
    return (
    chessboard[0][1] +
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
    chessboard[7][6] ) == (int) sum_blacks;
}

bool check_rules_remained_whites( bool chessboard[8][8] , unsigned char remained_whites )
{
    //This function can be used, only if we have a complete final chessboard 
    return (
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
    chessboard[7][5] ) == (int) remained_whites;
}

bool check_rules_remained_blacks( bool chessboard[8][8] , unsigned char remained_blacks )
{
    //This function can be used, only if we have a complete final chessboard 
    return (
    chessboard[0][1] +
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
    chessboard[7][6] ) == (int) remained_blacks;
}

bool check_rules_remained_whites_demo( bool chessboard[8][8] , unsigned char remained_whites )
{
    //This function can be used in any state
    return (
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
    chessboard[7][5] ) <= (int) remained_whites;
}

bool check_rules_remained_blacks_demo( bool chessboard[8][8] , unsigned char remained_blacks )
{
    //This function can be used in any state
    return (
    chessboard[0][1] +
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
    chessboard[7][6] ) <= (int) remained_blacks;
}

void copy_chessboard( bool chessboard[8][8], bool ** temp_chessboard )
{
    for(size_t i = 0; i < 8; i++)
        for(size_t j = 0; j < 8; j++)
            temp_chessboard[i][j] = chessboard[i][j];           
}