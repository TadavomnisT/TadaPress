<?php


var_dump(
    p_binary_combination( 4 , 3 ),
    p_binary_combination( 3 , 2 ),
    p_binary_combination( 8 , 5 )
);


function p_binary_combination( int $n, int $r, $base_string = NULL , $original_r = NULL )
{
    if ( $original_r === NULL ) $original_r = $r;
    if( $base_string === NULL ){
        $base_string = str_repeat( "0" , $n );
        $GLOBALS[ "array" ] = [];
    } 
    global $array;
    if( $r === -1 ) return $base_string;
    if ( substr_count( $base_string , '1' ) === $original_r  )
        if ( !in_array( $base_string , $array ) )
            $array[] = $base_string;
    for ($i=0; $i < $n ; $i++) { 
        if ( $base_string[ $i ] !== '1' ) {
            $temp_string = $base_string;
            $temp_string[ $i ] = '1';
            p_binary_combination( $n, $r - 1, $temp_string , $original_r  );
        }
    }
    return $array;
    // Shitty function I know!
    // THIS is the kinda shit you write, when you lack motivation:)
    // But I'm better than this!
    // ... just not today. 
}






?>