<?php

require_once 'chessbean.php';
$algorithm = new ChessBean ;

$result = $algorithm -> compressBlock( $argv[1] );

echo $result;

// $algorithm -> decompressFile( "compressed_data.tdprs" , "decompressed_data.tdprs" ); 

?>
