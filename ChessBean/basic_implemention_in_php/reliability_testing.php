<?php

class Reliability_Testing
{
    public function reliability_check($chessboard, $block, int $state, bool $strategy = NULL)
    {
    $array = str_split( $block , 8);
    // $state == 1 => choosing strategy step
    if ( $state == 1 )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;

      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 2 => choosing perform 0 step
    if ( $state == 2 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 2 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;

      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 3 => choosing perform 2 step
    if ( $state == 3 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 3 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;

      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 4 => choosing perform 5 step
    if ( $state == 4 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 4 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;

      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 5 => choosing perform 7 step
    if ( $state == 5 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 5 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;

      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 6 => idk what does things means that I wrote em!
    if ( $state == 6 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 6 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;

      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 7 => hmmmm
    if ( $state == 7 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 7 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;

      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 8 => awh
    if ( $state == 8 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 8 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;

      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 9 => huh:3
    if ( $state == 9 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 9 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;

      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 10 => hey mano tahdidam nakon:3
    if ( $state == 10 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 10 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 11 => Maa zadim beh simeh aakhar:3
    if ( $state == 11 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 11 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 12 => haha:3
    if ( $state == 12 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 12 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 13 => nth to say...
    if ( $state == 13 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 13 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    // $state == 14 => I am scared!
    if ( $state == 14 && $strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
    if ( $state == 14 && !$strategy )
    {
      if ( (int) $chessboard[0][0] != (int) $array[0][0] ) return false;
      if ( (int) $chessboard[0][1] != (int) $array[0][1] ) return false;
      if ( (int) $chessboard[0][2] != (int) $array[0][2] ) return false;
      if ( (int) $chessboard[0][3] != (int) $array[0][3] ) return false;
      if ( (int) $chessboard[0][4] != (int) $array[0][4] ) return false;
      if ( (int) $chessboard[0][5] != (int) $array[0][5] ) return false;
      if ( (int) $chessboard[0][6] != (int) $array[0][6] ) return false;
      if ( (int) $chessboard[0][7] != (int) $array[0][7] ) return false;

      if ( (int) $chessboard[1][0] != (int) $array[1][0] ) return false;
      if ( (int) $chessboard[1][1] != (int) $array[1][1] ) return false;
      if ( (int) $chessboard[1][2] != (int) $array[1][2] ) return false;
      if ( (int) $chessboard[1][3] != (int) $array[1][3] ) return false;
      if ( (int) $chessboard[1][4] != (int) $array[1][4] ) return false;
      if ( (int) $chessboard[1][5] != (int) $array[1][5] ) return false;
      if ( (int) $chessboard[1][6] != (int) $array[1][6] ) return false;
      if ( (int) $chessboard[1][7] != (int) $array[1][7] ) return false;

      if ( (int) $chessboard[2][0] != (int) $array[2][0] ) return false;
      if ( (int) $chessboard[2][1] != (int) $array[2][1] ) return false;
      if ( (int) $chessboard[2][2] != (int) $array[2][2] ) return false;
      if ( (int) $chessboard[2][3] != (int) $array[2][3] ) return false;
      if ( (int) $chessboard[2][4] != (int) $array[2][4] ) return false;
      if ( (int) $chessboard[2][5] != (int) $array[2][5] ) return false;
      if ( (int) $chessboard[2][6] != (int) $array[2][6] ) return false;
      if ( (int) $chessboard[2][7] != (int) $array[2][7] ) return false;

      if ( (int) $chessboard[3][0] != (int) $array[3][0] ) return false;
      if ( (int) $chessboard[3][1] != (int) $array[3][1] ) return false;
      if ( (int) $chessboard[3][2] != (int) $array[3][2] ) return false;
      if ( (int) $chessboard[3][3] != (int) $array[3][3] ) return false;
      if ( (int) $chessboard[3][4] != (int) $array[3][4] ) return false;
      if ( (int) $chessboard[3][5] != (int) $array[3][5] ) return false;
      if ( (int) $chessboard[3][6] != (int) $array[3][6] ) return false;
      if ( (int) $chessboard[3][7] != (int) $array[3][7] ) return false;

      if ( (int) $chessboard[4][0] != (int) $array[4][0] ) return false;
      if ( (int) $chessboard[4][1] != (int) $array[4][1] ) return false;
      if ( (int) $chessboard[4][2] != (int) $array[4][2] ) return false;
      if ( (int) $chessboard[4][3] != (int) $array[4][3] ) return false;
      if ( (int) $chessboard[4][4] != (int) $array[4][4] ) return false;
      if ( (int) $chessboard[4][5] != (int) $array[4][5] ) return false;
      if ( (int) $chessboard[4][6] != (int) $array[4][6] ) return false;
      if ( (int) $chessboard[4][7] != (int) $array[4][7] ) return false;

      if ( (int) $chessboard[5][0] != (int) $array[5][0] ) return false;
      if ( (int) $chessboard[5][1] != (int) $array[5][1] ) return false;
      if ( (int) $chessboard[5][2] != (int) $array[5][2] ) return false;
      if ( (int) $chessboard[5][3] != (int) $array[5][3] ) return false;
      if ( (int) $chessboard[5][4] != (int) $array[5][4] ) return false;
      if ( (int) $chessboard[5][5] != (int) $array[5][5] ) return false;
      if ( (int) $chessboard[5][6] != (int) $array[5][6] ) return false;
      if ( (int) $chessboard[5][7] != (int) $array[5][7] ) return false;

      if ( (int) $chessboard[6][0] != (int) $array[6][0] ) return false;
      if ( (int) $chessboard[6][1] != (int) $array[6][1] ) return false;
      if ( (int) $chessboard[6][2] != (int) $array[6][2] ) return false;
      if ( (int) $chessboard[6][3] != (int) $array[6][3] ) return false;
      if ( (int) $chessboard[6][4] != (int) $array[6][4] ) return false;
      if ( (int) $chessboard[6][5] != (int) $array[6][5] ) return false;
      if ( (int) $chessboard[6][6] != (int) $array[6][6] ) return false;
      if ( (int) $chessboard[6][7] != (int) $array[6][7] ) return false;

      if ( (int) $chessboard[7][0] != (int) $array[7][0] ) return false;
      if ( (int) $chessboard[7][1] != (int) $array[7][1] ) return false;
      if ( (int) $chessboard[7][2] != (int) $array[7][2] ) return false;
      if ( (int) $chessboard[7][3] != (int) $array[7][3] ) return false;
      if ( (int) $chessboard[7][4] != (int) $array[7][4] ) return false;
      if ( (int) $chessboard[7][5] != (int) $array[7][5] ) return false;
      if ( (int) $chessboard[7][6] != (int) $array[7][6] ) return false;
      if ( (int) $chessboard[7][7] != (int) $array[7][7] ) return false;

      return true;
    }
  }
}


?>
