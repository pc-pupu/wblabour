<?php
function encryption_decryption_wblabour($action, $string) {
    $output 		= false;
    $encrypt_method = "AES-256-CBC";
    
    $secret_key 	= 'wblabour';
    $secret_iv 		= 'WbAdmLb#4321';
	
    $key = hash('sha512', $secret_key);
	
    $iv = substr(hash('sha512', $secret_iv), 0, 16);

    if( $action == 'encrypt' ) {
        $output = openssl_encrypt($string, $encrypt_method, $key, 0, $iv);
        $output = base64_encode($output);
    }else if( $action == 'decrypt' ){
        $output = openssl_decrypt(base64_decode($string), $encrypt_method, $key, 0, $iv);
    }
    return $output;
}
$pass = encryption_decryption_wblabour('encrypt', $_REQUEST['pass']);
echo $pass;
exit;
?>