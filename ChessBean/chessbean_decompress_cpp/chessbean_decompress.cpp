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


#include <iostream>
using namespace std;

bool check_rules_cols( bool[8][8] , bool[8] );
bool check_rules_cols_demo( bool[8][8] , bool[8] );
bool check_rules_rows( bool[8][8] , bool[8] );
bool check_rules_rows_demo( bool[8][8] , bool[8] );

int main(int argc, char *argv[])
{

    // string input_buffer = "01111010111001011110101100001000010101110010010100000000";
    string input_buffer = argv[ 1 ];
    char  one = '1' ,  zero = '0';
    bool chessboard[8][8]; 
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

    cout << check_rules_cols_demo( chessboard , cols ) <<endl;
    cout << check_rules_rows_demo( chessboard , rows ) <<endl;

    for(size_t i = 0; i < 8; i++){
        for(size_t j = 0; j < 8; j++){
            cout << chessboard[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

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