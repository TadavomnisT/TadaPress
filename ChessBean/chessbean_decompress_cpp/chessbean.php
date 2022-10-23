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
class ChessBean
{

  function __construct(  )
  {
    // maybe later...
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
  public function compressBlock( string $block )
  {
    // var_dump( $block );
    // $this->printBlockAsMatrix( $block );
    // $this->printBlockAsChessBoard( $block );


    // die;
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


    // var_dump(
    //   $whites_7_bits ,
    //   $blacks_7_bits ,
    //   $sum_whites_5_bits ,
    //   $sum_blacks_5_bits ,
    //   $sum_columns_8_bits ,
    //   $sum_rows_8_bits ,
    //   $corner_4_bits ,
    //   $center_4_bits
    // );     
    // die;       
    // var_dump ( $compressed . $this->hashBlock( $compressed ) );
    // die;
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

    if( $sum_whites_5_bits == "00000" )
    {
        if ( $whites_7_bits == "0111111" )
            $sum_whites = 32;
        else $sum_whites = 0;
    }
    else $sum_whites = bindec( $sum_whites_5_bits );

    if( $sum_blacks_5_bits == "00000" )
    {
        if ( $blacks_7_bits == "0111111" )
            $sum_blacks = 32;
        else $sum_blacks = 0;
    }
    else $sum_blacks = bindec( $sum_blacks_5_bits );


    // DEBUG: ==============================
    // DEBUG: Test block is : 1000100101010000010011100100011100001101000010100001101000001010
    $this->printBlockAsMatrix( "1000100101010000010011100100011100001101000010100001101000001010" );
    $this->printBlockAsChessBoard( "1000100101010000010011100100011100001101000010100001101000001010" );
    // =====================================

    var_dump(
      $whites_7_bits ,
      $blacks_7_bits ,
      $sum_whites_5_bits ,
      $sum_blacks_5_bits ,
      $sum_columns_8_bits ,
      $sum_rows_8_bits ,
      $corner_4_bits ,
      $center_4_bits ,
      $blockHash ,
      $sum_blacks ,
      $sum_whites
    );die;
  }
  private function strToBin ( $number )    {
      $result = '';
      for ( $i = 0; $i < strlen($number); $i++ ){
          $conv = base_convert($number[$i], 16, 2);
          $result .= str_pad($conv, 4, '0', STR_PAD_LEFT);
      }
      return $result;
  }
  private function hashBlock( string $block )
  {
    // I should implement this later, after we decompressed data successfully.
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
  private function printBlockAsChessBoard( string $block )
  {
    $chess_board_with_beans = "\n┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│\n│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│\n├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│░░░░**░░░░│▓▓▓▓**▓▓▓▓│\n│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│░░░░░░░░░░│▓▓▓▓▓▓▓▓▓▓│\n└──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘\n";
    $flag = FALSE;
    $col_counter = 0;
    $row_counter = 0;
    $matrix = str_split( $block , 8 );
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
}



?>
