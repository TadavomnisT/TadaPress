<?php

dump_cpp_var_definition(
    "put_2_in_2",
    array_merge(
        p_binary_combination( 2 , 2 )
    ),
    "put 2 in 2"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "put_1_2_in_2",
    array_merge(
        p_binary_combination( 2 , 1 ),
        p_binary_combination( 2 , 2 )
    ),
    "put 1,2 in 2"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "put_0_1_2_in_2",
    array_merge(
        p_binary_combination( 2 , 0 ),
        p_binary_combination( 2 , 1 ),
        p_binary_combination( 2 , 2 )
    ),
    "put 0,1,2 in 2"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "put_0_1_in_2",
    array_merge(
        p_binary_combination( 2 , 0 ),
        p_binary_combination( 2 , 1 )
    ),
    "put 0,1 in 2"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "put_0_in_2",
    array_merge(
        p_binary_combination( 2 , 0 )

    ),
    "put 0 in 2"
);

die;

dump_cpp_var_definition(
    "fill_2_cells",
    array_merge(
        p_binary_combination( 2 , 0 ),
        p_binary_combination( 2 , 1 ),
        p_binary_combination( 2 , 2 )
    ),
    "fill 2 cells"
);

die;

dump_cpp_var_definition(
    "cols4_4",
    array_merge(
        p_binary_combination( 4 , 4 )
    ),
    "cols4: 4"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "cols4_4_3",
    array_merge(
        p_binary_combination( 4 , 4 ),
        p_binary_combination( 4 , 3 )
    ),
    "cols4: 4,3"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "cols4_4_3_2",
    array_merge(
        p_binary_combination( 4 , 4 ),
        p_binary_combination( 4 , 3 ),
        p_binary_combination( 4 , 2 )
    ),
    "cols4: 4,3,2"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "cols4_4_3_2_1",
    array_merge(
        p_binary_combination( 4 , 4 ),
        p_binary_combination( 4 , 3 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 1 )
    ),
    "cols4: 4,3,2,1"
);

echo PHP_EOL;

echo "//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" . PHP_EOL;

echo PHP_EOL;

dump_cpp_var_definition(
    "cols4_0_1_2_3_4",
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 3 ),
        p_binary_combination( 4 , 4 )
    ),
    "cols4: 0,1,2,3,4"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "cols4_0_1_2_3",
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 3 )
    ),
    "cols4: 0,1,2,3"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "cols4_0_1_2",
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 2 )
    ),
    "cols4: 0,1,2"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "cols4_0_1",
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 )
    ),
    "cols4: 0,1"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "cols4_0",
    array_merge(
        p_binary_combination( 4 , 0 )
    ),
    "cols4: 0"
);

echo PHP_EOL;

echo "//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" . PHP_EOL;
echo "//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" . PHP_EOL;
echo "//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" . PHP_EOL;

echo PHP_EOL;

dump_cpp_var_definition(
    "rows4_0_1_2_3",
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 3 )
    ),
    "rows4: 0,1,2,3"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "rows4_0_1_2",
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 2 )
    ),
    "rows4: 0,1,2"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "rows4_0_1",
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 1 )
    ),
    "rows4: 0,1"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "rows4_0",
    array_merge(
        p_binary_combination( 4 , 0 )
    ),
    "rows4: 0"
);

echo PHP_EOL;

echo "//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" . PHP_EOL;

echo PHP_EOL;

dump_cpp_var_definition(
    "rows4_4",
    array_merge(
        p_binary_combination( 4 , 4 )
    ),
    "rows4: 4"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "rows4_4_3",
    array_merge(
        p_binary_combination( 4 , 4 ),
        p_binary_combination( 4 , 3 )
    ),
    "rows4: 4,3"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "rows4_4_3_2",
    array_merge(
        p_binary_combination( 4 , 4 ),
        p_binary_combination( 4 , 3 ),
        p_binary_combination( 4 , 2 )
    ),
    "rows4: 4,3,2"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "rows4_4_3_2_1",
    array_merge(
        p_binary_combination( 4 , 4 ),
        p_binary_combination( 4 , 3 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 1 )
    ),
    "rows4: 4,3,2,1"
);

echo PHP_EOL;

dump_cpp_var_definition(
    "rows4_4_3_2_1_0",
    array_merge(
        p_binary_combination( 4 , 4 ),
        p_binary_combination( 4 , 3 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 0 ),
    ),
    "rows4: 4,3,2,1,0"
);

die;

var_dump(
    p_binary_combination( 4 , 3 )
);

die;

// four_lil_diagonals
var_dump( 
    array_merge(
        p_binary_combination( 3 , 0 ),
        p_binary_combination( 3 , 2 )
    ),
    array_merge(
        p_binary_combination( 3 , 1 ),
        p_binary_combination( 3 , 3 )
    )
);die;


$counter = 0;
for ($i=0; $i < 8; $i++) { 
    for ($j=0; $j < 8 ; $j++) { 
        if( !(($counter + !($i % 2) ) % 2) )
        echo "chessboard[$i][$j] +" . PHP_EOL;
        ++$counter;
    }
}

dump_cpp_var_definition(
    "diagonal_1_3" ,
    array_merge(
        p_binary_combination( 4 , 1 ),
        p_binary_combination( 4 , 3 )
    ),
    "All possible values for a diagonal with 1 or 3 combination."
);

echo PHP_EOL;

dump_cpp_var_definition(
    "diagonal_0_2_4" ,
    array_merge(
        p_binary_combination( 4 , 0 ),
        p_binary_combination( 4 , 2 ),
        p_binary_combination( 4 , 4 )
    ),
    "All possible values for a diagonal with 0 or 2 or 4 combination."
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