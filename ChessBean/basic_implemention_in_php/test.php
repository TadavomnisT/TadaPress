<?php

require_once 'chessbean.php';
$algorithm = new ChessBean ;

$algorithm -> compressFile( "../images/logo.png" , "compressed_data.tdprs" );
$algorithm -> DEBUG_print_file_first_block( "../images/logo.png");
$algorithm -> decompressFile( "compressed_data.tdprs" , "decompressed_data.tdprs" ); 

?>
