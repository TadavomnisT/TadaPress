<?php

require_once 'chessbean.php';
$algorithm = new ChessBean ;

$algorithm -> compressFile( "../images/logo.png" , "compressed_data.tdprs" ); 

?>
