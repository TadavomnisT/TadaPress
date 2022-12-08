<?php

dump_php_var_definition(
    "put_0_in_4" ,
    array_merge(
        p_binary_combination( 4 , 0 )
    ),
);

die;
dump_php_var_definition(
    "put_1_2_3_4_in_4" ,
    array_merge(
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 3 ),
        p_binary_combination( 4 , 4 )
    ),
);

die;
dump_php_var_definition(
    "put_0_1_in_4" ,
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 )
    ),
);

die;
dump_php_var_definition(
    "put_2_3_4_in_4" ,
    array_merge(
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 3 ),
        p_binary_combination( 4 , 4 )
    ),
);

die;
dump_php_var_definition(
    "put_0_1_2_in_4" ,
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 2 )
    ),
);

die;
dump_php_var_definition(
    "put_3_4_in_4" ,
    array_merge(
        p_binary_combination( 4 , 3 ),
        p_binary_combination( 4 , 4 )
    ),
);

die;
dump_php_var_definition(
    "put_0_1_2_3_in_4" ,
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 3 )
    ),
);


die;
dump_php_var_definition(
    "put_4_in_4" ,
    array_merge(
        p_binary_combination( 4 , 4 )
    ),
);


die;
dump_php_var_definition(
    "put_0_1_2_3_4_in_4" ,
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 3 ),
        p_binary_combination( 4 , 4 )
    ),
);



die;
// ========================================================================

dump_php_var_definition(
    "put_0_2_4_in_4" ,
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 4 )
    ),
    "All possible values for putting 0 or 2 or 4 in 4."
);


dump_php_var_definition(
    "put_1_3_in_4" ,
    array_merge(
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 3 )
    ),
    "All possible values for putting 1 or 3 in 4."
);

dump_php_var_definition(
    "put_1_in_2" ,
    array_merge(
        p_binary_combination( 2 , 1 )
    ),
    "All possible values for putting 1 in 2."
);

dump_php_var_definition(
    "put_0_2_in_2" ,
    array_merge(
        p_binary_combination( 2 , 0 ),
        p_binary_combination( 2 , 2 )
    ),
    "All possible values for putting 0 or 2 in 2."
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

function dump_php_var_definition( string $name, array $values, string $comment = NULL )
{
    if( $comment !== NULL )
    echo "/*" . $comment . "*/" . PHP_EOL;
    echo "\$" . $name . " = [" . PHP_EOL;
    foreach ($values as $key => $value) {
        echo "    [" . implode( ',' , strToArray( $value ) ) . ']' . (( $key != count( $values ) - 1 ) ? ',' . PHP_EOL : PHP_EOL) ;
    }
    echo "];" . PHP_EOL;
}


function get_php_var_definition( string $name, array $values, string $comment = NULL )
{
    ob_start();
    dump_cpp_var_definition( $name , $values );
    return ob_get_clean();
}

function dump_cpp_var_definition( string $name, array $values, string $comment = NULL )
{
    if( $comment !== NULL )
    echo "/*" . $comment . "*/" . PHP_EOL;
    echo "bool " . $name . "[" . count( $values ) . "][" . strlen( $values[0] ) . "] = {" . PHP_EOL;
    foreach ($values as $key => $value) {
        echo '{' . implode( ',' , strToArray( $value ) ) . '}' . (( $key != count( $values ) - 1 ) ? ',' . PHP_EOL : PHP_EOL) ;
    }
    echo "};" . PHP_EOL;
}


function get_cpp_var_definition( string $name, array $values, string $comment = NULL )
{
    ob_start();
    dump_cpp_var_definition( $name , $values );
    return ob_get_clean();
}

function strToArray($str, $l = 0)
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


?>