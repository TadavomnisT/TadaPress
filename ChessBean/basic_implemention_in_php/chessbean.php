<?php


/**
 * The main class that implements ChessBean algorithm.
 *
 * NOTICE:
 *
 * THIS IS NOT A DESCENT IMPLEMENTATION!!!
 *
 * why?
 *
 * Why PHP might not be the best candidate :
 *
 * https://thephp.website/en/issue/bitwise-php/ :
 *
 * ================================================================================
 * Look. I love PHP, ok? Don't get me wrong.
 * And I'm sure it will handle gracefully many more cases than you can imagine.
 * But in cases where you need to be very efficient while handling binary data, PHP simply won't do the job.
 * Just to be clear: I'm not talking about how an application might consume 5 or 10mb more,
 * I'm talking about allocating the exact amount of memory necessary to hold a certain data type.
 * According to the official documentation on integers , PHP represents decimals as well as hexadecimals, octals and binaries with the type integer.
 * So it doesn't really matter what data you put in there, it will always be an integer.
 *================================================================================
 *
 * But since these are just beginning tests,
 * we are going to use PHP ,
 * and we are going to cast bits into strings ! :/
 * I know how stupid the idea is,
 * but optimised tests will come later (probably with C++)
 *
 */

// DEBUG
require_once "reliability_testing.php";

class ChessBean
{
  // DEBUG
  private $_DEBUG_rt;
  private $_DEBUG_rt_block;

  function __construct(  )
  {
    // DEBUG
    $this->_DEBUG_rt = new Reliability_Testing;
  }
  public function compressFile( string $inputName , string $outputName )
  {
    if ( !file_exists( $inputName ) ) throw new \Exception("File \"$inputName\" does not exists.", 1);
    if ( file_exists( $outputName ) ) throw new \Exception("File \"$outputName\" aleady exists.", 1);
    if ( $inputName === $outputName ) throw new \Exception("Output name cannot be same as input name.", 1);

    $input = fopen( $inputName,"rb");
    $output = fopen( $outputName,"w");
    while (! feof ($input))
    {
        $chunk = fread( $input , 8 );
        $block = $this->stringToBinary( $chunk );
        if( strlen($block) === 64 )
          fwrite( $output , pack('H*', base_convert($this->compressBlock( $block ), 2, 16)) );
        else
          fwrite( $output , $chunk );
    }
  }
  public function decompressFile( string $inputName , string $outputName )
  {
    if ( !file_exists( $inputName ) ) throw new \Exception("File \"$inputName\" does not exists.", 1);
    if ( file_exists( $outputName ) ) throw new \Exception("File \"$outputName\" aleady exists.", 1);
    if ( $inputName === $outputName ) throw new \Exception("Output name cannot be same as input name.", 1);

    $input = fopen( $inputName,"rb");
    $output = fopen( $outputName,"w");
    while (! feof ($input))
    {
        $chunk = fread( $input , 7 );
        $block = $this->stringToBinary( $chunk );
        if( strlen($block) === 56 )
          fwrite( $output , pack('H*', base_convert($this->decompressBlock( $block ), 2, 16)) );
        else
          fwrite( $output , $chunk );
          // DEBUG: The above IF_ELSE has a small problem , havn't decided for it yet.
          // DEBUG: The above IF_ELSE has a small problem , havn't decided for it yet.
          // DEBUG: The above IF_ELSE has a small problem , havn't decided for it yet.
    }
  }
  public function compressData( $data )
  {
    // code...
  }
  public function decompressData( $data )
  {
    // code...
  }
  private function compressBlock( string $block )
  {
    $whites_7_bits =
    ( $block[0] + $block[9] + $block[18] + $block[27] + $block[36] + $block[45] + $block[54] + $block[63] ) % 2 .
    ( $block[2] + $block[9] + $block[16] ) % 2 .
    ( $block[4] + $block[11] + $block[18] + $block[25] + $block[32] ) % 2 .
    ( $block[6] + $block[13] + $block[20] + $block[27] + $block[34] + $block[41] + $block[48] ) % 2 .
    ( $block[15] + $block[22] + $block[29] + $block[36] + $block[43] + $block[50] + $block[57] ) % 2 .
    ( $block[31] + $block[38] + $block[45] + $block[52] + $block[59] ) % 2 .
    ( $block[47] + $block[54] + $block[61] ) % 2 ;

    $blacks_7_bits =
    ( $block[7] + $block[14] + $block[21] + $block[28] + $block[35] + $block[42] + $block[49] + $block[56] ) % 2 .
    ( $block[5] + $block[14] + $block[23] ) % 2 .
    ( $block[3] + $block[12] + $block[21] + $block[30] + $block[39] ) % 2 .
    ( $block[1] + $block[10] + $block[19] + $block[28] + $block[37] + $block[46] + $block[55] ) % 2 .
    ( $block[8] + $block[17] + $block[26] + $block[35] + $block[44] + $block[53] + $block[62] ) % 2 .
    ( $block[24] + $block[33] + $block[42] + $block[51] + $block[60] ) % 2 .
    ( $block[40] + $block[49] + $block[58] ) % 2 ;

    $sum_whites_5_bits =
    $block[0] + $block[2] + $block[4] + $block[6] +
    $block[9] + $block[11] + $block[13] + $block[15] +
    $block[16] + $block[18] + $block[20] + $block[22] +
    $block[25] + $block[27] + $block[29] + $block[31] +
    $block[32] + $block[34] + $block[36] + $block[38] +
    $block[41] + $block[43] + $block[45] + $block[47] +
    $block[48] + $block[50] + $block[52] + $block[54] +
    $block[57] + $block[59] + $block[61] + $block[63] ;
    if($sum_whites_5_bits >= 32 ) $sum_whites_5_bits = 0;
    $sum_whites_5_bits = str_repeat("0" , (5 - strlen(decbin($sum_whites_5_bits)) ) ) . decbin($sum_whites_5_bits);

    $sum_blacks_5_bits =
    $block[1] + $block[3] + $block[5] + $block[7] +
    $block[8] + $block[10] + $block[12] + $block[14] +
    $block[17] + $block[19] + $block[21] + $block[23] +
    $block[24] + $block[26] + $block[28] + $block[30] +
    $block[33] + $block[35] + $block[37] + $block[39] +
    $block[40] + $block[42] + $block[44] + $block[46] +
    $block[49] + $block[51] + $block[53] + $block[55] +
    $block[56] + $block[58] + $block[60] + $block[62] ;
    if($sum_blacks_5_bits >= 32 ) $sum_blacks_5_bits = 0;
    $sum_blacks_5_bits = str_repeat("0" , (5 - strlen(decbin($sum_blacks_5_bits)) ) ) . decbin($sum_blacks_5_bits);

    $sum_columns_8_bits =
    (int) ( ( $block[0] + $block[8] + $block[16] + $block[24] + $block[32] + $block[40] + $block[48] + $block[56] ) > 4 ) .
    (int) ( ( $block[1] + $block[9] + $block[17] + $block[25] + $block[33] + $block[41] + $block[49] + $block[57] ) > 4 ) .
    (int) ( ( $block[2] + $block[10] + $block[18] + $block[26] + $block[34] + $block[42] + $block[50] + $block[58] ) > 4 ) .
    (int) ( ( $block[3] + $block[11] + $block[19] + $block[27] + $block[35] + $block[43] + $block[51] + $block[59] ) > 4 ) .
    (int) ( ( $block[4] + $block[12] + $block[20] + $block[28] + $block[36] + $block[44] + $block[52] + $block[60] ) > 4 ) .
    (int) ( ( $block[5] + $block[13] + $block[21] + $block[29] + $block[37] + $block[45] + $block[53] + $block[61] ) > 4 ) .
    (int) ( ( $block[6] + $block[14] + $block[22] + $block[30] + $block[38] + $block[46] + $block[54] + $block[62] ) > 4 ) .
    (int) ( ( $block[7] + $block[15] + $block[23] + $block[31] + $block[39] + $block[47] + $block[55] + $block[63] ) > 4 ) ;

    $sum_rows_8_bits =
    (int) ( ( $block[0] + $block[1] + $block[2] + $block[3] + $block[4] + $block[5] + $block[6] + $block[7] ) < 4 ) .
    (int) ( ( $block[8] + $block[9] + $block[10] + $block[11] + $block[12] + $block[13] + $block[14] + $block[15] ) < 4 ) .
    (int) ( ( $block[16] + $block[17] + $block[18] + $block[19] + $block[20] + $block[21] + $block[22] + $block[23] ) < 4 ) .
    (int) ( ( $block[24] + $block[25] + $block[26] + $block[27] + $block[28] + $block[29] + $block[30] + $block[31] ) < 4 ) .
    (int) ( ( $block[32] + $block[33] + $block[34] + $block[35] + $block[36] + $block[37] + $block[38] + $block[39] ) < 4 ) .
    (int) ( ( $block[40] + $block[41] + $block[42] + $block[43] + $block[44] + $block[45] + $block[46] + $block[47] ) < 4 ) .
    (int) ( ( $block[48] + $block[49] + $block[50] + $block[51] + $block[52] + $block[53] + $block[54] + $block[55] ) < 4 ) .
    (int) ( ( $block[56] + $block[57] + $block[58] + $block[59] + $block[60] + $block[61] + $block[62] + $block[63] ) < 4 ) ;

    $corner_4_bits = $block[0] . $block[7] . $block[56] . $block[63] ;

    $center_4_bits = $block[27] . $block[28] . $block[35] . $block[36] ;

    $compressed = $whites_7_bits . $blacks_7_bits . $sum_whites_5_bits .
            $sum_blacks_5_bits . $sum_columns_8_bits . $sum_rows_8_bits .
            $corner_4_bits . $center_4_bits ;

    return $compressed . $this->hashBlock( $compressed ) ;
  }
  private function decompressBlock( string $block )
  {
    // let's work on this part:
    $whites_7_bits = substr( $block , 0 , 7 );
    $blacks_7_bits = substr( $block , 7 , 7 );
    $sum_whites_5_bits = substr( $block , 14 , 5 );
    $sum_blacks_5_bits = substr( $block , 19 , 5 );
    $sum_columns_8_bits = substr( $block , 24 , 8 );
    $sum_rows_8_bits = substr( $block , 32 , 8 );
    $corner_4_bits = substr( $block , 40 , 4 );
    $center_4_bits = substr( $block , 44 , 4 );
    $blockHash = substr( $block , 48 , 8 );

    var_dump( $block );

    echo "whites_7_bits " . $whites_7_bits . PHP_EOL;
    echo "blacks_7_bits " . $blacks_7_bits . PHP_EOL;
    echo "sum_whites_5_bits " . $sum_whites_5_bits . PHP_EOL;
    echo "sum_blacks_5_bits " . $sum_blacks_5_bits . PHP_EOL;
    echo "sum_columns_8_bits " . $sum_columns_8_bits . PHP_EOL;
    echo "sum_rows_8_bits " . $sum_rows_8_bits . PHP_EOL;
    echo "corner_4_bits " . $corner_4_bits . PHP_EOL;
    echo "center_4_bits " . $center_4_bits . PHP_EOL;
    echo "blockHash " . $blockHash . PHP_EOL;

    // if( $sum_whites_5_bits == "00000" )
    // {
    //     if ( $whites_7_bits == "0111111" )
    //         $sum_whites = 32;
    //     else $sum_whites = 0;
    // }
    // else $sum_whites = bindec( $sum_whites_5_bits );

    // if( $sum_blacks_5_bits == "00000" )
    // {
    //     if ( $blacks_7_bits == "0111111" )
    //         $sum_blacks = 32;
    //     else $sum_blacks = 0;
    // }
    // else $sum_blacks = bindec( $sum_blacks_5_bits );

    $chessboard = [
      [0, 0, 0, 0, 0, 0, 0, 0], 
      [0, 0, 0, 0, 0, 0, 0, 0], 
      [0, 0, 0, 0, 0, 0, 0, 0], 
      [0, 0, 0, 0, 0, 0, 0, 0], 
      [0, 0, 0, 0, 0, 0, 0, 0], 
      [0, 0, 0, 0, 0, 0, 0, 0], 
      [0, 0, 0, 0, 0, 0, 0, 0], 
      [0, 0, 0, 0, 0, 0, 0, 0] 
    ];

    // Step #1 - Fill 4 corners:
    $chessboard[0][0] = (int) ($block[40] == '1');
    $chessboard[0][7] = (int) ($block[41] == '1');
    $chessboard[7][0] = (int) ($block[42] == '1');
    $chessboard[7][7] = (int) ($block[43] == '1');

    // $this->printBlockAsChessBoard( $chessboard );

    // Step #2 - Fill 4 centers:
    $chessboard[3][3] = (int) ($block[44] == '1');
    $chessboard[3][4] = (int) ($block[45] == '1');
    $chessboard[4][3] = (int) ($block[46] == '1');
    $chessboard[4][4] = (int) ($block[47] == '1');

    // $this->printBlockAsChessBoard( $chessboard );

    // Step #3 - calculate how many whites shall be placed:
    $all_whites =
    ($block[14] == '1') * 16 +
    ($block[15] == '1') * 8 +
    ($block[16] == '1') * 4 +
    ($block[17] == '1') * 2 +
    ($block[18] == '1') * 1;
    if ($all_whites == 0)
      $all_whites = ($block[1] == '1') ? 32 : 0;
    $remained_whites = $all_whites -
    $chessboard[0][0] -
    $chessboard[3][3] -
    $chessboard[4][4] -
    $chessboard[7][7];

    // Step #4 - calculate how many blacks shall be placed: 
    $all_blacks =
    ($block[19] == '1') * 16 +
    ($block[20] == '1') * 8 +
    ($block[21] == '1') * 4 +
    ($block[22] == '1') * 2 +
    ($block[23] == '1') * 1;
    if ($all_blacks == 0)
      $all_blacks = ($block[8] == '1') ? 32 : 0;
    $remained_blacks = $all_blacks -
    $chessboard[0][7] -
    $chessboard[3][4] -
    $chessboard[4][3] -
    $chessboard[7][0];


    $GLOBALS["all_whites"] = $all_whites;
    $GLOBALS["remained_whites"] = $remained_whites;
    $GLOBALS["all_blacks"] = $all_blacks;
    $GLOBALS["remained_blacks"] = $remained_blacks;

    var_dump(
      $all_whites,
      $remained_whites,
      $all_blacks,
      $remained_blacks
    );

    // Step #5 - extract rules for columns:
    $GLOBALS["cols"][0] = ($block[24] == '1');
    $GLOBALS["cols"][1] = ($block[25] == '1');
    $GLOBALS["cols"][2] = ($block[26] == '1');
    $GLOBALS["cols"][3] = ($block[27] == '1');
    $GLOBALS["cols"][4] = ($block[28] == '1');
    $GLOBALS["cols"][5] = ($block[29] == '1');
    $GLOBALS["cols"][6] = ($block[30] == '1');
    $GLOBALS["cols"][7] = ($block[31] == '1');

    // Step #6 - extract rules for rows:
    $GLOBALS["rows"][0] = ($block[32] == '1');
    $GLOBALS["rows"][1] = ($block[33] == '1');
    $GLOBALS["rows"][2] = ($block[34] == '1');
    $GLOBALS["rows"][3] = ($block[35] == '1');
    $GLOBALS["rows"][4] = ($block[36] == '1');
    $GLOBALS["rows"][5] = ($block[37] == '1');
    $GLOBALS["rows"][6] = ($block[38] == '1');
    $GLOBALS["rows"][7] = ($block[39] == '1');

    var_dump($GLOBALS["cols"]);  
    var_dump($GLOBALS["rows"]);
    
    // Step #7 - extract rules for white diagonal:
    $GLOBALS["white_diagonals"][0] = (int) ($block[0] == '1');
    $GLOBALS["white_diagonals"][1] = (int) ($block[1] == '1');
    $GLOBALS["white_diagonals"][2] = (int) ($block[2] == '1');
    $GLOBALS["white_diagonals"][3] = (int) ($block[3] == '1');
    $GLOBALS["white_diagonals"][4] = (int) ($block[4] == '1');
    $GLOBALS["white_diagonals"][5] = (int) ($block[5] == '1');
    $GLOBALS["white_diagonals"][6] = (int) ($block[6] == '1');

    // Step #8 - extract rules for black diagonal:
    $GLOBALS["black_diagonals"][0] = (int) ($block[7] == '1');
    $GLOBALS["black_diagonals"][1] = (int) ($block[8] == '1');
    $GLOBALS["black_diagonals"][2] = (int) ($block[9] == '1');
    $GLOBALS["black_diagonals"][3] = (int) ($block[10] == '1');
    $GLOBALS["black_diagonals"][4] = (int) ($block[11] == '1');
    $GLOBALS["black_diagonals"][5] = (int) ($block[12] == '1');
    $GLOBALS["black_diagonals"][6] = (int) ($block[13] == '1');

    var_dump(
      $GLOBALS["white_diagonals"],
      $GLOBALS["black_diagonals"],
    );  

    echo "[*]Starting nested functions." . PHP_EOL;

    $this->start_nested_functions( $chessboard );

    die; // !!!
    die; // !!!
    die; // !!!
    die; // !!!

    // // DEBUG: ==============================
    // // DEBUG: Test block is : 1000100101010000010011100100011100001101000010100001101000001010
    // $this->printBlockAsMatrix( "1000100101010000010011100100011100001101000010100001101000001010" );
    // $this->printBlockAsChessBoard( "1000100101010000010011100100011100001101000010100001101000001010" );
    // // =====================================

    // var_dump(
    //   $whites_7_bits ,
    //   $blacks_7_bits ,
    //   $sum_whites_5_bits ,
    //   $sum_blacks_5_bits ,
    //   $sum_columns_8_bits ,
    //   $sum_rows_8_bits ,
    //   $corner_4_bits ,
    //   $center_4_bits ,
    //   $blockHash ,
    //   $sum_blacks ,
    //   $sum_whites
    // );die;
  }
  private function start_nested_functions( array $chessboard )
  {
    $temp_chessboard = $chessboard;
    // $this->printBlockAsChessBoard( $temp_chessboard );
    $this->white_diagonal( $temp_chessboard );
  }
  private function white_diagonal( array $chessboard )
  {
    $temp_chessboard = $chessboard;
    echo "[*]Filling white digonal." . PHP_EOL;
    /*All possible values for putting 0 or 2 or 4 in 4.*/
    $put_0_2_4_in_4 = [
      [0,0,0,0],
      [1,1,0,0],
      [1,0,1,0],
      [1,0,0,1],
      [0,1,1,0],
      [0,1,0,1],
      [0,0,1,1],
      [1,1,1,1]
    ];
    /*All possible values for putting 1 or 3 in 4.*/
    $put_1_3_in_4 = [
      [1,0,0,0],
      [0,1,0,0],
      [0,0,1,0],
      [0,0,0,1],
      [1,1,1,0],
      [1,1,0,1],
      [1,0,1,1],
      [0,1,1,1]
    ];
    $white_diagonal_placed_beans = (int)
    ( $temp_chessboard[0][0] +
      $temp_chessboard[3][3] +
      $temp_chessboard[4][4] +
      $temp_chessboard[7][7]
    );
    if( ( $white_diagonal_placed_beans + $GLOBALS["white_diagonals"][0] ) % 2 )
      for ($i = 0; $i < 8 ; $i++) { 
        $temp_chessboard[1][1] = $put_1_3_in_4[$i][0];
        $temp_chessboard[2][2] = $put_1_3_in_4[$i][1];
        $temp_chessboard[5][5] = $put_1_3_in_4[$i][2];
        $temp_chessboard[6][6] = $put_1_3_in_4[$i][3];
        // $this->printBlockAsChessBoard( $temp_chessboard );
        $this->black_diagonal( $temp_chessboard );
      }
    else
      for ($i = 0; $i < 8 ; $i++) { 
        $temp_chessboard[1][1] = $put_0_2_4_in_4[$i][0];
        $temp_chessboard[2][2] = $put_0_2_4_in_4[$i][1];
        $temp_chessboard[5][5] = $put_0_2_4_in_4[$i][2];
        $temp_chessboard[6][6] = $put_0_2_4_in_4[$i][3];
        // $this->printBlockAsChessBoard( $temp_chessboard );
        $this->black_diagonal( $temp_chessboard );
      }
  }
  private function black_diagonal( array $chessboard )
  {
    $temp_chessboard = $chessboard;
    echo "[*]Filling black digonal." . PHP_EOL;
    /*All possible values for putting 0 or 2 or 4 in 4.*/
    $put_0_2_4_in_4 = [
      [0,0,0,0],
      [1,1,0,0],
      [1,0,1,0],
      [1,0,0,1],
      [0,1,1,0],
      [0,1,0,1],
      [0,0,1,1],
      [1,1,1,1]
    ];
    /*All possible values for putting 1 or 3 in 4.*/
    $put_1_3_in_4 = [
      [1,0,0,0],
      [0,1,0,0],
      [0,0,1,0],
      [0,0,0,1],
      [1,1,1,0],
      [1,1,0,1],
      [1,0,1,1],
      [0,1,1,1]
    ];
    $black_diagonal_placed_beans = (int)
    ( $temp_chessboard[0][7] +
      $temp_chessboard[3][4] +
      $temp_chessboard[4][3] +
      $temp_chessboard[7][0]
    );
    if( ( $black_diagonal_placed_beans + $GLOBALS["black_diagonals"][0] ) % 2 )
      for ($i = 0; $i < 8 ; $i++) { 
        $temp_chessboard[1][6] = $put_1_3_in_4[$i][0];
        $temp_chessboard[2][5] = $put_1_3_in_4[$i][1];
        $temp_chessboard[5][2] = $put_1_3_in_4[$i][2];
        $temp_chessboard[6][1] = $put_1_3_in_4[$i][3];
        // $this->printBlockAsChessBoard( $temp_chessboard );
        $this->little_diagonal_1( $temp_chessboard );
      }
    else
      for ($i = 0; $i < 8 ; $i++) { 
        $temp_chessboard[1][6] = $put_0_2_4_in_4[$i][0];
        $temp_chessboard[2][5] = $put_0_2_4_in_4[$i][1];
        $temp_chessboard[5][2] = $put_0_2_4_in_4[$i][2];
        $temp_chessboard[6][1] = $put_0_2_4_in_4[$i][3];
        // $this->printBlockAsChessBoard( $temp_chessboard );
        $this->little_diagonal_1( $temp_chessboard );
      }
  }
  private function little_diagonal_1( array $chessboard )
  {
    $temp_chessboard = $chessboard;
    /*All possible values for putting 1 in 2.*/
    $put_1_in_2 = [
      [1,0],
      [0,1]
    ];
    /*All possible values for putting 0 or 2 in 2.*/
    $put_0_2_in_2 = [
      [0,0],
      [1,1]
    ];
    if( ((int) $temp_chessboard[1][1]) ^ ((int) $GLOBALS["white_diagonals"][1]) )
      for ($i = 0; $i < 2 ; $i++) { 
        $temp_chessboard[2][0] = $put_1_in_2[$i][0];
        $temp_chessboard[0][2] = $put_1_in_2[$i][1];
        // $this->printBlockAsChessBoard( $temp_chessboard );
        $this->little_diagonal_2( $temp_chessboard );
      }
    else
      for ($i = 0; $i < 2 ; $i++) { 
        $temp_chessboard[2][0] = $put_0_2_in_2[$i][0];
        $temp_chessboard[0][2] = $put_0_2_in_2[$i][1];
        // $this->printBlockAsChessBoard( $temp_chessboard );
        $this->little_diagonal_2( $temp_chessboard );
      }
  }
  private function little_diagonal_2( array $chessboard )
  {
    $temp_chessboard = $chessboard;
    /*All possible values for putting 1 in 2.*/
    $put_1_in_2 = [
      [1,0],
      [0,1]
    ];
    /*All possible values for putting 0 or 2 in 2.*/
    $put_0_2_in_2 = [
      [0,0],
      [1,1]
    ];
    if( ((int) $temp_chessboard[1][6]) ^ ((int) $GLOBALS["black_diagonals"][1]) )
      for ($i = 0; $i < 2 ; $i++) { 
        $temp_chessboard[2][7] = $put_1_in_2[$i][0];
        $temp_chessboard[0][5] = $put_1_in_2[$i][1];
        // $this->printBlockAsChessBoard( $temp_chessboard );
        $this->little_diagonal_3( $temp_chessboard );
      }
    else
      for ($i = 0; $i < 2 ; $i++) { 
        $temp_chessboard[2][7] = $put_0_2_in_2[$i][0];
        $temp_chessboard[0][5] = $put_0_2_in_2[$i][1];
        // $this->printBlockAsChessBoard( $temp_chessboard );
        $this->little_diagonal_3( $temp_chessboard );
      }
  }
  private function little_diagonal_3( array $chessboard )
  {
    $temp_chessboard = $chessboard;
    /*All possible values for putting 1 in 2.*/
    $put_1_in_2 = [
      [1,0],
      [0,1]
    ];
    /*All possible values for putting 0 or 2 in 2.*/
    $put_0_2_in_2 = [
      [0,0],
      [1,1]
    ];
    if( ((int) $temp_chessboard[6][6]) ^ ((int) $GLOBALS["white_diagonals"][6]) )
      for ($i = 0; $i < 2 ; $i++) { 
        $temp_chessboard[7][5] = $put_1_in_2[$i][0];
        $temp_chessboard[5][7] = $put_1_in_2[$i][1];
        // $this->printBlockAsChessBoard( $temp_chessboard );
        $this->little_diagonal_4( $temp_chessboard );
      }
    else
      for ($i = 0; $i < 2 ; $i++) { 
        $temp_chessboard[7][5] = $put_0_2_in_2[$i][0];
        $temp_chessboard[5][7] = $put_0_2_in_2[$i][1];
        // $this->printBlockAsChessBoard( $temp_chessboard );
        $this->little_diagonal_4( $temp_chessboard );
      }
  }
  private function little_diagonal_4( array $chessboard )
  {
    $temp_chessboard = $chessboard;
    /*All possible values for putting 1 in 2.*/
    $put_1_in_2 = [
      [1,0],
      [0,1]
    ];
    /*All possible values for putting 0 or 2 in 2.*/
    $put_0_2_in_2 = [
      [0,0],
      [1,1]
    ];
    if( ((int) $temp_chessboard[6][1]) ^ ((int) $GLOBALS["black_diagonals"][6]) )
      for ($i = 0; $i < 2 ; $i++) { 
        $temp_chessboard[5][0] = $put_1_in_2[$i][0];
        $temp_chessboard[7][2] = $put_1_in_2[$i][1];
        // $this->printChessBoardAsBlock( $temp_chessboard );
        $this->choose_strategy( $temp_chessboard );
      }
    else
      for ($i = 0; $i < 2 ; $i++) { 
        $temp_chessboard[5][0] = $put_0_2_in_2[$i][0];
        $temp_chessboard[7][2] = $put_0_2_in_2[$i][1];
        // $this->printChessBoardAsBlock( $temp_chessboard );
        $this->choose_strategy( $temp_chessboard );
      }
  }
  private function choose_strategy( array $chessboard )
  {
    // try {
    if( !$this->middle_rule_checker($chessboard) ) return false;
    $indexes = [ 0, 2, 5, 7 ];
    // for cols:
      $col_answers = 1;  
      foreach ($indexes as $index) {
        $sum = 
        $chessboard[0][$index]+
        $chessboard[2][$index]+
        $chessboard[5][$index]+
        $chessboard[7][$index];
        switch ( (string) $sum . (int) $GLOBALS["cols"][ $index ] ) {
          case '01':
            return false;
            break;
          case '00':
            $col_answers *= 16;
            break;
          case '11':
            $col_answers *= 1;
            break;
          case '10':
            $col_answers *= 15;
            break;
          case '21':
            $col_answers *= 5;
            break;
          case '20':
            $col_answers *= 11;
            break;
          case '31':
            $col_answers *= 11;
            break;
          case '30':
            $col_answers *= 5;
            break;
          case '41':
            $col_answers *= 15;
            break;
          case '40':
            $col_answers *= 1;
            break;
          default:
            throw new Exception("[*] Undecompressable Data.");
            break;
        }
      }
    // for rows:
      $rows_answers = 1;  
      foreach ($indexes as $index) {
        $sum = 
        $chessboard[$index][0]+
        $chessboard[$index][2]+
        $chessboard[$index][5]+
        $chessboard[$index][7];
        switch ( (string) $sum . (int) $GLOBALS["rows"][ $index ] ) {
          case '01':
            $rows_answers *= 15;
            break;
          case '00':
            $rows_answers *= 1;
            break;
          case '11':
            $rows_answers *= 11;
            break;
          case '10':
            $rows_answers *= 5;
            break;
          case '21':
            $rows_answers *= 5;
            break;
          case '20':
            $rows_answers *= 11;
            break;
          case '31':
            $rows_answers *= 1;
            break;
          case '30':
            $rows_answers *= 15;
            break;
          case '41':
            return false;
            break;
          case '40':
            $rows_answers *= 16;
            break;
          default:
            throw new Exception("[*] Undecompressable Data.");
            break;
        }
      }

    var_dump( "cols:" . $col_answers . " rows:". $rows_answers );
    // } catch (\Throwable $th) {
    //   var_dump( $th );
    //   $this->printBlockAsChessBoard( $temp_chessboard );
    //   var_dump( $this->middle_rule_checker($temp_chessboard) );
    //   die;
    // }
    
    $this->perform_strategy( $chessboard , ($col_answers < $rows_answers) );
  }
  private function perform_strategy( array $chessboard , bool $strategy )
  {
    $temp_chessboard = $chessboard;
    // $this->printChessBoardAsBlock( $temp_chessboard );
    $this->perform_0( $temp_chessboard , $strategy );
  }
  private function perform_0( array $chessboard , bool $strategy )
  {
    $temp_chessboard = $chessboard;
    if( !$this->middle_rule_checker($temp_chessboard) ) return false;
    $index = 0;
    if( $strategy ) //Go with cols
    {
      $sum = 
      $temp_chessboard[0][$index]+
      $temp_chessboard[2][$index]+
      $temp_chessboard[5][$index]+
      $temp_chessboard[7][$index];
      switch ( (string) $sum . (int) $GLOBALS["cols"][ $index ] ) {
        case '01':
          return false;
          break;
        case '00':
          $put_0_1_2_3_4_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 16 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_3_4_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          $put_4_in_4 = [
            [1,1,1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_4_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          $put_0_1_2_3_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_3_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_3_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_3_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_3_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }    
          break;
        case '21':
          $put_3_4_in_4 = [
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[1][$index] = $put_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_3_4_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }  
          break;
        case '20':
          $put_0_1_2_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }       
          break;
        case '31':
          $put_2_3_4_in_4 = [
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[1][$index] = $put_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_2_3_4_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_0_1_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          $put_1_2_3_4_in_4 = [
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[1][$index] = $put_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_1_2_3_4_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '40':
          $put_0_in_4 = [
            [0,0,0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }      
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
    else //Go with rows
    {
      $sum = 
      $temp_chessboard[$index][0]+
      $temp_chessboard[$index][2]+
      $temp_chessboard[$index][5]+
      $temp_chessboard[$index][7];
      switch ( (string) $sum . (int) $GLOBALS["rows"][ $index ] ) {
        case '01':
          $put_0_1_2_3_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_3_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_3_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_3_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_3_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '00':
          $put_4_in_4 = [
            [1,1,1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_4_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          $put_0_1_2_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          $put_3_4_in_4 = [
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[$index][1] = $put_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_3_4_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '21':
          $put_0_1_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '20':
          $put_2_3_4_in_4 = [
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[$index][1] = $put_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_2_3_4_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_0_in_4 = [
            [0,0,0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_1_2_3_4_in_4 = [
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[$index][1] = $put_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_1_2_3_4_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          return false;
          break;
        case '40':
          $put_0_1_2_3_4_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 16 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_3_4_in_4[ $i ][3];
            $this->perform_2( $temp_chessboard , $strategy );
          }
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
  }
  private function perform_2( array $chessboard , bool $strategy )
  {
    $temp_chessboard = $chessboard;
    if( !$this->middle_rule_checker($temp_chessboard) ) return false;
    $index = 2;
    if( $strategy ) //Go with cols
    {
      $sum = 
      $temp_chessboard[0][$index]+
      $temp_chessboard[2][$index]+
      $temp_chessboard[5][$index]+
      $temp_chessboard[7][$index];
      switch ( (string) $sum . (int) $GLOBALS["cols"][ $index ] ) {
        case '01':
          return false;
          break;
        case '00':
          $put_0_1_2_3_4_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 16 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_3_4_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          $put_4_in_4 = [
            [1,1,1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_4_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          $put_0_1_2_3_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_3_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_3_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_3_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_3_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }    
          break;
        case '21':
          $put_3_4_in_4 = [
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[1][$index] = $put_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_3_4_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }  
          break;
        case '20':
          $put_0_1_2_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }       
          break;
        case '31':
          $put_2_3_4_in_4 = [
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[1][$index] = $put_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_2_3_4_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_0_1_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          $put_1_2_3_4_in_4 = [
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[1][$index] = $put_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_1_2_3_4_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '40':
          $put_0_in_4 = [
            [0,0,0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }      
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
    else //Go with rows
    {
      $sum = 
      $temp_chessboard[$index][0]+
      $temp_chessboard[$index][2]+
      $temp_chessboard[$index][5]+
      $temp_chessboard[$index][7];
      switch ( (string) $sum . (int) $GLOBALS["rows"][ $index ] ) {
        case '01':
          $put_0_1_2_3_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_3_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_3_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_3_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_3_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '00':
          $put_4_in_4 = [
            [1,1,1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_4_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          $put_0_1_2_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          $put_3_4_in_4 = [
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[$index][1] = $put_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_3_4_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '21':
          $put_0_1_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '20':
          $put_2_3_4_in_4 = [
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[$index][1] = $put_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_2_3_4_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_0_in_4 = [
            [0,0,0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_1_2_3_4_in_4 = [
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[$index][1] = $put_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_1_2_3_4_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          return false;
          break;
        case '40':
          $put_0_1_2_3_4_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 16 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_3_4_in_4[ $i ][3];
            $this->perform_5( $temp_chessboard , $strategy );
          }
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
  }
  private function perform_5( array $chessboard , bool $strategy )
  {
    $temp_chessboard = $chessboard;
    if( !$this->middle_rule_checker($temp_chessboard) ) return false;
    $index = 5;
    if( $strategy ) //Go with cols
    {
      $sum = 
      $temp_chessboard[0][$index]+
      $temp_chessboard[2][$index]+
      $temp_chessboard[5][$index]+
      $temp_chessboard[7][$index];
      switch ( (string) $sum . (int) $GLOBALS["cols"][ $index ] ) {
        case '01':
          return false;
          break;
        case '00':
          $put_0_1_2_3_4_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 16 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_3_4_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          $put_4_in_4 = [
            [1,1,1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_4_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          $put_0_1_2_3_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_3_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_3_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_3_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_3_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }    
          break;
        case '21':
          $put_3_4_in_4 = [
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[1][$index] = $put_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_3_4_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }  
          break;
        case '20':
          $put_0_1_2_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }       
          break;
        case '31':
          $put_2_3_4_in_4 = [
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[1][$index] = $put_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_2_3_4_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_0_1_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          $put_1_2_3_4_in_4 = [
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[1][$index] = $put_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_1_2_3_4_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '40':
          $put_0_in_4 = [
            [0,0,0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }      
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
    else //Go with rows
    {
      $sum = 
      $temp_chessboard[$index][0]+
      $temp_chessboard[$index][2]+
      $temp_chessboard[$index][5]+
      $temp_chessboard[$index][7];
      switch ( (string) $sum . (int) $GLOBALS["rows"][ $index ] ) {
        case '01':
          $put_0_1_2_3_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_3_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_3_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_3_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_3_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '00':
          $put_4_in_4 = [
            [1,1,1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_4_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          $put_0_1_2_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          $put_3_4_in_4 = [
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[$index][1] = $put_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_3_4_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '21':
          $put_0_1_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '20':
          $put_2_3_4_in_4 = [
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[$index][1] = $put_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_2_3_4_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_0_in_4 = [
            [0,0,0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_1_2_3_4_in_4 = [
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[$index][1] = $put_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_1_2_3_4_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          return false;
          break;
        case '40':
          $put_0_1_2_3_4_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 16 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_3_4_in_4[ $i ][3];
            $this->perform_7( $temp_chessboard , $strategy );
          }
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
  }
  private function perform_7( array $chessboard , bool $strategy )
  {
    $temp_chessboard = $chessboard;
    if( !$this->middle_rule_checker($temp_chessboard) ) return false;
    $index = 7;
    if( $strategy ) //Go with cols
    {
      $sum = 
      $temp_chessboard[0][$index]+
      $temp_chessboard[2][$index]+
      $temp_chessboard[5][$index]+
      $temp_chessboard[7][$index];
      switch ( (string) $sum . (int) $GLOBALS["cols"][ $index ] ) {
        case '01':
          return false;
          break;
        case '00':
          $put_0_1_2_3_4_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 16 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_3_4_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          $put_4_in_4 = [
            [1,1,1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_4_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          $put_0_1_2_3_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_3_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_3_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_3_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_3_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }    
          break;
        case '21':
          $put_3_4_in_4 = [
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[1][$index] = $put_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_3_4_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }  
          break;
        case '20':
          $put_0_1_2_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_2_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_2_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_2_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }       
          break;
        case '31':
          $put_2_3_4_in_4 = [
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[1][$index] = $put_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_2_3_4_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_0_1_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_1_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_1_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_1_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          $put_1_2_3_4_in_4 = [
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[1][$index] = $put_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_1_2_3_4_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '40':
          $put_0_in_4 = [
            [0,0,0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_in_4[ $i ][0];
            $temp_chessboard[3][$index] = $put_0_in_4[ $i ][1];
            $temp_chessboard[4][$index] = $put_0_in_4[ $i ][2];
            $temp_chessboard[6][$index] = $put_0_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }      
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
    else //Go with rows
    {
      $sum = 
      $temp_chessboard[$index][0]+
      $temp_chessboard[$index][2]+
      $temp_chessboard[$index][5]+
      $temp_chessboard[$index][7];
      switch ( (string) $sum . (int) $GLOBALS["rows"][ $index ] ) {
        case '01':
          $put_0_1_2_3_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_3_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_3_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_3_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_3_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '00':
          $put_4_in_4 = [
            [1,1,1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_4_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          $put_0_1_2_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          $put_3_4_in_4 = [
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[$index][1] = $put_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_3_4_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '21':
          $put_0_1_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1]
          ];
          for ($i=0; $i < 5 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '20':
          $put_2_3_4_in_4 = [
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 11 ; $i++) { 
            $temp_chessboard[$index][1] = $put_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_2_3_4_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_0_in_4 = [
            [0,0,0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_1_2_3_4_in_4 = [
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 15 ; $i++) { 
            $temp_chessboard[$index][1] = $put_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_1_2_3_4_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          return false;
          break;
        case '40':
          $put_0_1_2_3_4_in_4 = [
            [0,0,0,0],
            [1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1],
            [1,1,0,0],
            [1,0,1,0],
            [1,0,0,1],
            [0,1,1,0],
            [0,1,0,1],
            [0,0,1,1],
            [1,1,1,0],
            [1,1,0,1],
            [1,0,1,1],
            [0,1,1,1],
            [1,1,1,1]
          ];
          for ($i=0; $i < 16 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_3_4_in_4[ $i ][0];
            $temp_chessboard[$index][3] = $put_0_1_2_3_4_in_4[ $i ][1];
            $temp_chessboard[$index][4] = $put_0_1_2_3_4_in_4[ $i ][2];
            $temp_chessboard[$index][6] = $put_0_1_2_3_4_in_4[ $i ][3];
            $this->after_strategy_1( $temp_chessboard , $strategy );
          }
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
  }
  private function after_strategy_1( array $chessboard , bool $strategy )
  {
    $temp_chessboard = $chessboard;
    if( !$this->middle_rule_checker($temp_chessboard) ) return false;
    if ( $strategy ) {
      $index = 1;
      $sum =
      $chessboard[$index][0] +  
      $chessboard[$index][1] +  
      $chessboard[$index][2] +  
      $chessboard[$index][5] +  
      $chessboard[$index][6] +  
      $chessboard[$index][7] ;
      switch ( (string) $sum . (int) $GLOBALS["rows"][ $index ] ) {
        case '01':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '00':
          return false;
          break;
        case '11':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          return false;
          break;
        case '21':
          $put_0_1_in_2 = [
              [0,0],
              [1,0],
              [0,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '20':
          $put_2_in_2 = [
              [1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][3] = $put_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_0_in_2 = [
              [0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_1_2_in_2 = [
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[$index][3] = $put_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          return false;
          break;
        case '40':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '51':
          return false;
          break;
        case '50':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '61':
          return false;
          break;
        case '60':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
    else {
      $index = 6;
      $sum =
      $chessboard[0][$index] +  
      $chessboard[1][$index] +  
      $chessboard[2][$index] +  
      $chessboard[5][$index] +  
      $chessboard[6][$index] +  
      $chessboard[7][$index] ;
      switch ( (string) $sum . (int) $GLOBALS["cols"][ $index ] ) {
        case '01':
          return false;
          break;
        case '00':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          return false;
          break;
        case '10':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '21':
          return false;
          break;
        case '20':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_2_in_2 = [
              [1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[3][$index] = $put_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_0_1_in_2 = [
              [0,0],
              [1,0],
              [0,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          $put_1_2_in_2 = [
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[3][$index] = $put_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '40':
          $put_0_in_2 = [
              [0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '51':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '50':
          return false;
          break;
        case '61':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_2( $temp_chessboard , $strategy );
          }
          break;
        case '60':
          return false;
          break;
        default:
        throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
  }
  private function after_strategy_2( array $chessboard , bool $strategy )
  {
    $temp_chessboard = $chessboard;
    if( !$this->middle_rule_checker($temp_chessboard) ) return false;
    if ( $strategy ) {
      $index = 6;
      $sum =
      $chessboard[$index][0] +  
      $chessboard[$index][1] +  
      $chessboard[$index][2] +  
      $chessboard[$index][5] +  
      $chessboard[$index][6] +  
      $chessboard[$index][7] ;
      switch ( (string) $sum . (int) $GLOBALS["rows"][ $index ] ) {
        case '01':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '00':
          return false;
          break;
        case '11':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          return false;
          break;
        case '21':
          $put_0_1_in_2 = [
              [0,0],
              [1,0],
              [0,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '20':
          $put_2_in_2 = [
              [1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][3] = $put_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_0_in_2 = [
              [0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_1_2_in_2 = [
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[$index][3] = $put_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          return false;
          break;
        case '40':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '51':
          return false;
          break;
        case '50':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '61':
          return false;
          break;
        case '60':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][3] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][4] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
    else {
      $index = 1;
      $sum =
      $chessboard[0][$index] +  
      $chessboard[1][$index] +  
      $chessboard[2][$index] +  
      $chessboard[5][$index] +  
      $chessboard[6][$index] +  
      $chessboard[7][$index] ;
      switch ( (string) $sum . (int) $GLOBALS["cols"][ $index ] ) {
        case '01':
          return false;
          break;
        case '00':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          return false;
          break;
        case '10':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '21':
          return false;
          break;
        case '20':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_2_in_2 = [
              [1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[3][$index] = $put_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_0_1_in_2 = [
              [0,0],
              [1,0],
              [0,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          $put_1_2_in_2 = [
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[3][$index] = $put_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '40':
          $put_0_in_2 = [
              [0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '51':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '50':
          return false;
          break;
        case '61':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[3][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[4][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_3( $temp_chessboard , $strategy );
          }
          break;
        case '60':
          return false;
          break;
        default:
        throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
  }
  private function after_strategy_3( array $chessboard , bool $strategy )
  {
    $temp_chessboard = $chessboard;
    if( !$this->middle_rule_checker($temp_chessboard) ) return false;
    if ( $strategy ) {
      $index = 3;
      $sum =
      $chessboard[$index][0] +  
      $chessboard[$index][2] +  
      $chessboard[$index][3] +  
      $chessboard[$index][4] +  
      $chessboard[$index][5] +  
      $chessboard[$index][7] ;
      switch ( (string) $sum . (int) $GLOBALS["rows"][ $index ] ) {
        case '01':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '00':
          return false;
          break;
        case '11':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          return false;
          break;
        case '21':
          $put_0_1_in_2 = [
              [0,0],
              [1,0],
              [0,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '20':
          $put_2_in_2 = [
              [1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_0_in_2 = [
              [0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_1_2_in_2 = [
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[$index][1] = $put_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          return false;
          break;
        case '40':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '51':
          return false;
          break;
        case '50':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '61':
          return false;
          break;
        case '60':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
    else {
      $index = 4;
      $sum =
      $chessboard[0][$index] +  
      $chessboard[2][$index] +  
      $chessboard[3][$index] +  
      $chessboard[4][$index] +  
      $chessboard[5][$index] +  
      $chessboard[7][$index] ;
      switch ( (string) $sum . (int) $GLOBALS["cols"][ $index ] ) {
        case '01':
          return false;
          break;
        case '00':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          return false;
          break;
        case '10':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '21':
          return false;
          break;
        case '20':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_2_in_2 = [
              [1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_0_1_in_2 = [
              [0,0],
              [1,0],
              [0,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          $put_1_2_in_2 = [
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[1][$index] = $put_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '40':
          $put_0_in_2 = [
              [0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '51':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '50':
          return false;
          break;
        case '61':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->after_strategy_4( $temp_chessboard , $strategy );
          }
          break;
        case '60':
          return false;
          break;
        default:
        throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
  }
  private function after_strategy_4( array $chessboard , bool $strategy )
  {
    $temp_chessboard = $chessboard;
    if( !$this->middle_rule_checker($temp_chessboard) ) return false;
    if ( $strategy ) {
      $index = 4;
      $sum =
      $chessboard[$index][0] +  
      $chessboard[$index][2] +  
      $chessboard[$index][3] +  
      $chessboard[$index][4] +  
      $chessboard[$index][5] +  
      $chessboard[$index][7] ;
      switch ( (string) $sum . (int) $GLOBALS["rows"][ $index ] ) {
        case '01':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '00':
          return false;
          break;
        case '11':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '10':
          return false;
          break;
        case '21':
          $put_0_1_in_2 = [
              [0,0],
              [1,0],
              [0,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '20':
          $put_2_in_2 = [
              [1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_0_in_2 = [
              [0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_1_2_in_2 = [
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[$index][1] = $put_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          return false;
          break;
        case '40':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '51':
          return false;
          break;
        case '50':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '61':
          return false;
          break;
        case '60':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[$index][1] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[$index][6] = $put_0_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        default:
          throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
    else {
      $index = 3;
      $sum =
      $chessboard[0][$index] +  
      $chessboard[2][$index] +  
      $chessboard[3][$index] +  
      $chessboard[4][$index] +  
      $chessboard[5][$index] +  
      $chessboard[7][$index] ;
      switch ( (string) $sum . (int) $GLOBALS["cols"][ $index ] ) {
        case '01':
          return false;
          break;
        case '00':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '11':
          return false;
          break;
        case '10':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '21':
          return false;
          break;
        case '20':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '31':
          $put_2_in_2 = [
              [1,1]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '30':
          $put_0_1_in_2 = [
              [0,0],
              [1,0],
              [0,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '41':
          $put_1_2_in_2 = [
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 3 ; $i++) { 
            $temp_chessboard[1][$index] = $put_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '40':
          $put_0_in_2 = [
              [0,0]
          ];
          for ($i=0; $i < 1 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '51':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '50':
          return false;
          break;
        case '61':
          $put_0_1_2_in_2 = [
              [0,0],
              [1,0],
              [0,1],
              [1,1]
          ];
          for ($i=0; $i < 4 ; $i++) { 
            $temp_chessboard[1][$index] = $put_0_1_2_in_2[ $i ][0];
            $temp_chessboard[6][$index] = $put_0_1_2_in_2[ $i ][1];
            $this->fill_ones( $temp_chessboard , $strategy );
          }
          break;
        case '60':
          return false;
          break;
        default:
        throw new Exception("[*] Undecompressable Data.");
          break;
      }
    }
  }
  private function fill_ones( array $chessboard , bool $strategy )
  {
    $temp_chessboard = $chessboard;
    if( !$this->middle_rule_checker($temp_chessboard) ) return false;
    if ( $strategy )
    {
      if ((($temp_chessboard[1][3]+
            $temp_chessboard[2][2]+
            $temp_chessboard[3][1]+
            $temp_chessboard[4][0]) % 2) == $GLOBALS["white_diagonals"][2]
          ) $temp_chessboard[0][4] = 0;
      else  $temp_chessboard[0][4] = 1;
      if ((($temp_chessboard[1][4]+
            $temp_chessboard[2][5]+
            $temp_chessboard[3][6]+
            $temp_chessboard[4][7]) % 2) == $GLOBALS["black_diagonals"][2]
          ) $temp_chessboard[0][3] = 0;
      else  $temp_chessboard[0][3] = 1;
      if ((($temp_chessboard[6][4]+
            $temp_chessboard[5][5]+
            $temp_chessboard[4][6]+
            $temp_chessboard[3][7]) % 2) == $GLOBALS["white_diagonals"][5]
          ) $temp_chessboard[7][3] = 0;
      else  $temp_chessboard[7][3] = 1;
      if ((($temp_chessboard[6][3]+
            $temp_chessboard[5][2]+
            $temp_chessboard[4][1]+
            $temp_chessboard[3][0]) % 2) == $GLOBALS["black_diagonals"][5]
          ) $temp_chessboard[7][4] = 0;
      else  $temp_chessboard[7][4] = 1;
    }
    else
    {
      if ((($temp_chessboard[0][4]+
            $temp_chessboard[1][3]+
            $temp_chessboard[2][2]+
            $temp_chessboard[3][1]) % 2) == $GLOBALS["white_diagonals"][2]
          ) $temp_chessboard[4][0] = 0;
      else  $temp_chessboard[4][0] = 1;
      if ((($temp_chessboard[0][3]+
            $temp_chessboard[1][4]+
            $temp_chessboard[2][5]+
            $temp_chessboard[3][6]) % 2) == $GLOBALS["black_diagonals"][2]
          ) $temp_chessboard[4][7] = 0;
      else  $temp_chessboard[4][7] = 1;
      if ((($temp_chessboard[7][3]+
            $temp_chessboard[6][4]+
            $temp_chessboard[5][5]+
            $temp_chessboard[4][6]) % 2) == $GLOBALS["white_diagonals"][5]
          ) $temp_chessboard[3][7] = 0;
      else  $temp_chessboard[3][7] = 1;
      if ((($temp_chessboard[7][4]+
            $temp_chessboard[6][3]+
            $temp_chessboard[5][2]+
            $temp_chessboard[4][1]) % 2) == $GLOBALS["black_diagonals"][5]
          ) $temp_chessboard[3][0] = 0;
      else  $temp_chessboard[3][0] = 1;
    }
    $this->next_bloody_function( $temp_chessboard , $strategy );
  }
  private function next_bloody_function( array $chessboard , bool $strategy )
  { //EXTRA COMPUTATIONS : MUST DO STH
    $temp_chessboard = $chessboard;
    if( !$this->middle_rule_checker($temp_chessboard) ) return false;
    if( $this->_DEBUG_rt->reliability_check($chessboard , $this->_DEBUG_rt_block , 10 , $strategy) ) $this->printBlockAsChessBoard($temp_chessboard);
    // $this->after_strategy_1( $temp_chessboard , $strategy );
  }
  
  private function middle_rule_checker(array $chessboard)
  {
    $current_whites =
    $chessboard[0][0] + $chessboard[0][2] + $chessboard[0][4] + $chessboard[0][6] +
    $chessboard[1][1] + $chessboard[1][3] + $chessboard[1][5] + $chessboard[1][7] +
    $chessboard[2][0] + $chessboard[2][2] + $chessboard[2][4] + $chessboard[2][6] +
    $chessboard[3][1] + $chessboard[3][3] + $chessboard[3][5] + $chessboard[3][7] +
    $chessboard[4][0] + $chessboard[4][2] + $chessboard[4][4] + $chessboard[4][6] +
    $chessboard[5][1] + $chessboard[5][3] + $chessboard[5][5] + $chessboard[5][7] +
    $chessboard[6][0] + $chessboard[6][2] + $chessboard[6][4] + $chessboard[6][6] +
    $chessboard[7][1] + $chessboard[7][3] + $chessboard[7][5] + $chessboard[7][7] ;
    if ( $current_whites > $GLOBALS["all_whites"] ) return false;
    $current_blacks =
    $chessboard[0][1] + $chessboard[0][3] + $chessboard[0][5] + $chessboard[0][7] +
    $chessboard[1][0] + $chessboard[1][2] + $chessboard[1][4] + $chessboard[1][6] +
    $chessboard[2][1] + $chessboard[2][3] + $chessboard[2][5] + $chessboard[2][7] +
    $chessboard[3][0] + $chessboard[3][2] + $chessboard[3][4] + $chessboard[3][6] +
    $chessboard[4][1] + $chessboard[4][3] + $chessboard[4][5] + $chessboard[4][7] +
    $chessboard[5][0] + $chessboard[5][2] + $chessboard[5][4] + $chessboard[5][6] +
    $chessboard[6][1] + $chessboard[6][3] + $chessboard[6][5] + $chessboard[6][7] +
    $chessboard[7][0] + $chessboard[7][2] + $chessboard[7][4] + $chessboard[7][6] ;
    if ( $current_blacks > $GLOBALS["all_blacks"] ) return false;
    for ($i=0; $i < 8 ; $i++) {
      $sum_cols = 0;
      $sum_rows = 0; 
      for ($j=0; $j < 8 ; $j++) { 
        $sum_cols += $chessboard[$j][$i];
        $sum_rows += $chessboard[$i][$j];
      }
      if( $sum_cols > 4 && $GLOBALS["cols"][$i] == 0 ) return false;
      if( $sum_rows >= 4 && $GLOBALS["rows"][$i] == 1 ) return false;
    }
    return true;
  }
  private function strToBin ( $number ){
    $result = '';
    for ( $i = 0; $i < strlen($number); $i++ ){
        $conv = base_convert($number[$i], 16, 2);
        $result .= str_pad($conv, 4, '0', STR_PAD_LEFT);
    }
    return $result;
  }
  private function hashBlock( string $block )
  {
    return substr(
      $this->strToBin( hash("sha256" , hash( "sha256" , $block ) . $block . md5($block) )  ),
      64,
      8
    );
  }
  private function hashCompressedData( string $still_not_implemented )
  {
    // I should implement this later, after we decompressed data successfully.
    return "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
  }
  private function strToArray($str, $l = 0)
  {
      if ($l > 0) {
          $ret = array();
          $len = mb_strlen($str, "UTF-8");
          for ($i = 0; $i < $len; $i += $l) {
              $ret[] = mb_substr($str, $i, $l, "UTF-8");
          }
          return $ret;
      }
      return preg_split("//u", $str, -1, PREG_SPLIT_NO_EMPTY);
  }
  private function stringToBinary($string)
  {
      $characters = str_split($string);
      $binary = [];
      foreach ($characters as $key => $character) {
          $data = unpack('H*', $character);
          $binary[$key] = base_convert($data[1], 16, 2);
          $binary[$key] = str_repeat("0" , ( 8 - strlen($binary[$key]) ) ) . $binary[$key];
      }
      return implode('', $binary);
  }
  // DEBUG: these are debugging functions:----------------------------------------------------------------
  private function stringToBinary_bytesSeprated($string)
  {
      $characters = str_split($string);
      $binary = [];
      foreach ($characters as $key => $character) {
          $data = unpack('H*', $character);
          $binary[$key] = base_convert($data[1], 16, 2);
          $binary[$key] = str_repeat("0" , ( 8 - strlen($binary[$key]) ) ) . $binary[$key];
      }
      return implode(' ', $binary);
  }
  private function printBlockAsMatrix( string $block )
  {
    $cnt = 0;
    for ($i=0; $i < 64 ; $i++)
    {
        echo $block[$i] . " ";
        ++ $cnt;
        if ($cnt >= 8) {
            $cnt = 0;
            echo PHP_EOL;
        }
    }
    echo PHP_EOL;
  }
  private function printChessBoardAsBlock( array $chessboard )
  {
    $block = "";
    foreach ($chessboard as $row)
      $block .= implode("" , $row);
    echo $block . PHP_EOL;
  }
  private function printBlockAsChessBoard( $block )
  {
    $chess_board_with_beans = "\n┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n└──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘\n";
    $flag = FALSE;
    $col_counter = 0;
    $row_counter = 0;
    $matrix = (gettype( $block ) == "string") ? str_split( $block , 8 ) : $block ;
    $chess_board_array = $this->strToArray($chess_board_with_beans);
    foreach ( $chess_board_array as $key => $value)
    {
    	if ($value == "*" )
    	{
          if( $matrix[ $row_counter ][ (int) ($col_counter / 2) ] != "1" )
      		{
            if( $row_counter % 2 )
      			$chess_board_array[$key] = ( ((floor( $col_counter /2 ) % 2)) )? "▓" : "░" ;
            else
      			$chess_board_array[$key] = ( ((floor( $col_counter /2 ) % 2)) )? "░" : "▓" ;
      		}
      		++$col_counter;
    		  if ($col_counter > 15)
        		{
        			if ( $flag ) ++ $row_counter;
        			$col_counter = 0;
        			$flag = !$flag;
        		}
      	}
    }
    echo implode("" , $chess_board_array) . PHP_EOL;
  }
  // DEBUG FUNCTIONS:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:
  public function file_get_first_block(string $file_name , $return_in_string = false)
  {
    return ($return_in_string)? $this->stringToBinary( file_get_contents( $file_name, false, null, 0, 8 ) ) : file_get_contents( $file_name, false, null, 0, 8 );
  }
  public function DEBUG_print_file_first_block(string $file_name)
  {
    $bin_block = $this->file_get_first_block( $file_name);
    echo $this->stringToBinary_bytesSeprated($bin_block) . PHP_EOL;
    echo $block = $this->stringToBinary($bin_block) . PHP_EOL;
    $this->printBlockAsMatrix( $block );
    $this->printBlockAsChessBoard( $block );
  }
  public function DEBUG_set_rt_block(string $block)
  {
    $this->_DEBUG_rt_block = $block ;
  }
}



?>
