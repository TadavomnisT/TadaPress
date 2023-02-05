<?php

require_once 'chessbean.php';
$algorithm = new ChessBean ;

$algorithm -> compressFile( "../images/logo.png" , "compressed_data.tdprs" );
$algorithm -> DEBUG_print_file_first_block( "../images/logo.png");
$algorithm -> DEBUG_set_rt_block(
    $algorithm -> file_get_first_block( "../images/logo.png" , true )
);
$algorithm -> decompressFile( "compressed_data.tdprs" , "decompressed_data.tdprs" ); 

// // Command:
// // dd bs=10 count=10 if=/dev/random > test_random_binary
// $algorithm -> compressFile( "test_random_binary" , "compressed_data.tdprs" );
// $algorithm -> DEBUG_print_file_first_block( "test_random_binary");
// $algorithm -> DEBUG_set_rt_block(
//     $algorithm -> file_get_first_block( "test_random_binary" , true )
// );
// $algorithm -> decompressFile( "compressed_data.tdprs" , "decompressed_data.tdprs" ); 


?>
