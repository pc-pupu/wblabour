<?php

function factorysarch_form($form, &$form_state) {

	$data = loadMultipleDistrictWithDonateGraph();
	echo "hi";
	print_r($data);
	exit; 

}

function loadMultipleDistrictWithDonateGraph(){
	
	$service_url 	= 	"https://wbfactories.gov.in//webservices/REST/serviceStatusSummery";
		
	$ch 			= 	curl_init();
	$headers		=	array();
	$curl_post_data = 	array(
		//"service_id" 	=> "1",
		//"district_code" => $district,
		//"sub_div_code"  => $subdivision, 
		"source" => "WBLD",      
		"from_date" 	=> "2019-01-01",
		"to_date" 		=> "2019-01-23",
		"districts"     => "BANKURA,NORTH 24-PARGANAS"
	);
	$headers[]		=	'Accept: application/json';
	$headers[]		=	'Content-Type: application/json';
	$headers[] 		= 	'charset=utf-8';
	curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($ch, CURLOPT_URL, $service_url);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0); 
	curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 0);
	curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode( $curl_post_data ) );
	curl_setopt($ch, CURLOPT_POST, true);
	$results		=	curl_exec($ch);
	$errors			=	curl_error($ch);
	curl_close($ch);
	$x				=	json_encode( $results );
	$prsecallwblc 		= 	json_decode(json_decode(trim($x)), TRUE);
	
	//$tmp= print_r(json_decode($results)); //exit;
	//print_r($tmp);
	//exit;
	return $prsecallwblc;
}