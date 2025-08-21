<?php

function ssdg_webservice_services_resource() {
  $api = array(
	'createTestData' => array(
  	'operations' => array(
    	
		 'create' => array(
          'help' => 'Create a user',
          'callback' => 'create_Test_Data',
          'file' => array('type' => 'inc', 'module' => 'ssdg_webservice', 'name' => 'includes/ssdg_webservice.services'),
          'access callback' => 'user_access',
          'access arguments' => array('access content'),
          'access arguments append' => FALSE,
          'args' => array(
            array(
              'name' => 'account',
              'type' => 'array',
              'description' => 'The user object',
              'source' => 'data',
              'optional' => FALSE,
            ),
          ),
        ),
      	),
	),
	
	'userValidation' => array(
  	'operations' => array(
    	
		 'create' => array(
          'help' => 'Create a user',
          'callback' => 'user_validation',
          'file' => array('type' => 'inc', 'module' => 'ssdg_webservice', 'name' => 'includes/ssdg_webservice.services'),
          'access callback' => 'user_access',
          'access arguments' => array('access content'),
          'access arguments append' => FALSE,
          'args' => array(
            array(
              'name' => 'account',
              'type' => 'array',
              'description' => 'The user object',
              'source' => 'data',
              'optional' => FALSE,
            ),
          ),
        ),
      	),
	),
	
	'applicationStatus' => array(
		'operations' => array(
			'create' => array(
					'help' 					=> 	'Application Status',
					'callback' 				=> 	'application_status',
					'file' 					=> 	array('type' => 'inc', 'module' => 'ssdg_webservice', 'name' => 'includes/ssdg_webservice.services'),
					'access callback' 		=> 	'user_access',
					'access arguments' 		=> array('access content'),
					'access arguments append' => FALSE,
					'args' 					=> 	array(
													array(
														'name' 			=> 'account',
														'type' 			=> 'array',
														'description' 	=> 'The user object',
														'source' 		=> 'data',
														'optional' 		=> FALSE
												),
				),
			),
		),
	),
	
	'ldUserServiceInfoUpdate' => array(
		'operations' => array(
			'create' => array(
					'help' 					=> 	'Ld user Service Update',
					'callback' 				=> 	'ld_user_service_info_update',
					'file' 					=> 	array('type' => 'inc', 'module' => 'ssdg_webservice', 'name' => 'includes/ssdg_webservice.services'),
					'access callback' 		=> 	'user_access',
					'access arguments' 		=> array('access content'),
					'access arguments append' => FALSE,
					'args' 					=> 	array(
													array(
														'name' 			=> 'account',
														'type' 			=> 'array',
														'description' 	=> 'The user object',
														'source' 		=> 'data',
														'optional' 		=> FALSE
												),
				),
			),
		),
	),
	
	'centralinspectionStatus' => array(
		'operations' => array(
			'create' => array(
					'help' 					=> 	'Central Inspection Status',
					'callback' 				=> 	'central_inspection_status',
					'file' 					=> 	array('type' => 'inc', 'module' => 'ssdg_webservice', 'name' => 'includes/ssdg_webservice.services'),
					'access callback' 		=> 	'user_access',
					'access arguments' 		=> array('access content'),
					'access arguments append' => FALSE,
					'args' 					=> 	array(
													array(
														'name' 			=> 'account',
														'type' 			=> 'array',
														'description' 	=> 'The user object',
														'source' 		=> 'data',
														'optional' 		=> FALSE
												),
				),
			),
		),
	),
	
	
  );
  //print_r($api); exit;
  return $api;
}

function ld_user_service_info_update($parm_arr = NULL){
		$user_service_info_id = trim($parm_arr['user_service_info_id']);
		$service_id = trim($parm_arr['service_id']);
		$service_table_updt = array(
			'status' => 1
		);
		
		$transaction = db_transaction();		
		try {
			$query=db_update('ld_user_service_info')
			->fields($service_table_updt)
			->condition('id', $user_service_info_id)
			->condition('service_id', $service_id)
			->execute();
			return array('code'=>200, 'msg'=>'Successfully updated');
		}catch (Exception $e) {
			$transaction->rollback();
			return services_error("PDO Exception".$e,500);
		}
}

function create_Test_Data($user_arr = NULL){
	//echo "hii"; exit;
	//return array('code'=>200,'content'=>array('msg'=>'Successfully added'));
	$un = trim($user_arr['userName']);
	//$email = trim($user_arr['emailId']);
	$mob = trim($user_arr['mobileNo']);
	
	/*if(chk_not_empty($un,$email,$mob)==2)
		return array('code'=>401,'content'=>array('msg'=>'Username field cannot be empty'));
	if(chk_not_empty($un,$email,$mob)==3)
		return array('code'=>401,'content'=>array('msg'=>'Email field cannot be empty'));
	if(chk_not_empty($un,$email,$mob)==4)
		return array('code'=>401,'content'=>array('msg'=>'Mobile field cannot be empty'));
	
	if(chk_email(trim($user_arr['emailId']))==2)
		return array('code'=>401,'content'=>array('msg'=>'Invalid Email'));*/
	if(chk_special_chars(trim($user_arr['userName']))==2)
		return array('code'=>401,'content'=>array('msg'=>'User Name contains special characters.'));
	/*if(chk_special_chars(trim($user_arr['applicantFirstName']))==2)
		return array('code'=>401,'content'=>array('msg'=>'First Name contains special characters.'));
	if(chk_special_chars(trim($user_arr['applicantMiddleName']))==2)
		return array('code'=>401,'content'=>array('msg'=>'Middle Name contains special characters.'));
	if(chk_special_chars(trim($user_arr['applicantLastName']))==2)
		return array('code'=>401,'content'=>array('msg'=>'Last Name contains special characters.'));*/
	/*if(chk_mobile(trim($user_arr['mobileNo'])) == 2)
		return array('code'=>401,'content'=>array('msg'=>'Invalid Mobile No.'));
	if(!empty($user_arr['applicantPincode']))
		if(chk_pin(trim($user_arr['applicantPincode'])) == 2)
			return array('code'=>401,'content'=>array('msg'=>'Invalid Appilicant Pin Code.'));
	
	if(!empty($user_arr['registeredUnitPincode']))
		if(chk_pin(trim($user_arr['registeredUnitPincode'])) == 2)
			return array('code'=>401,'content'=>array('msg'=>'Invalid Registered Unit Pin Code.'));*/
	
	
		/*$user_exist_arr = db_select('webservice_test', 'u')
							->fields('u', array('name'))
							->condition('u.name', $user_arr['userName'], '=')
							->execute()
							->fetchAssoc();

			if($user_exist_arr){
				 return services_error('Duplicate Entry',409);
			}*/							
				
		$transaction = db_transaction();
		
		try {
		
											
	$newUser 					= 	array(
												'name' 		=> trim($user_arr['userName']),
												/*'pass' 		=> 'oswicsuser@123', 
												'mail' 		=> trim($user_arr['emailId']),
												'status' 	=> 1,*/
												'phno' 		=> trim($user_arr['mobileNo']),					
											);								
											
											
			/*user_save(null, $newUser);
			$txtValue					=	trim($user_arr['userName']); 
			$fetch_info_querys 			= 	db_select('users', 'U');
			$fetch_info_querys->fields('U',  array('uid'));
			$fetch_info_querys->condition('U.name',$txtValue);
			$fetch_info_querys_result 	= 	$fetch_info_querys->execute()->fetchObject();
			$lastId						=	$fetch_info_querys_result->uid; 
			
			if(trim($user_arr['applicantGender'])=="M"){
				$gender	=	0;
			}
			if(trim($user_arr['applicantGender'])=="F"){
				$gender	=	1;
			}
			
			$userInfo 					= 	array(
												'user_id' 			=> $lastId,
												'f_name'		=> trim($user_arr['applicantFirstName']),
												'm_name'		=> trim($user_arr['applicantMiddleName']),
												'l_name'		=> trim($user_arr['applicantLastName']),
												'mobile'         => trim($user_arr['mobileNo']),
												  'gender'         =>  $gender,
												  'dist_code'         =>get_dist_id(trim($user_arr['applicantDistrict'])),
												   'pin'         =>trim($user_arr['applicantPincode']),
												   'dob'         =>  $user_arr['applicantDateOfBirth']!=''?$user_arr['applicantDateOfBirth']:'1970-01-01',
												 'address'         =>trim($user_arr['applicantAddress']),
												'organizationname'         =>trim($user_arr['organizationName']),
												  'contactpersonname'         =>trim($user_arr['contactPersonName']),
												  'contactpersondesignation'         =>trim($user_arr['contactPersonDesignation']),
													 'registeredunitname'         =>trim($user_arr['registeredUnitName']),
													 'registeredunitaddress'         =>trim($user_arr['registeredUnitAddress']),
													 'registeredunitpincode'         =>trim($user_arr['registeredUnitPincode']),
													   'oswicsapplicationid' =>trim($user_arr['oswicsApplicationId']),
												   'oswicsapplicationflag'=>1,
												   'status'	=>1,
												   'email'         => trim($user_arr['emailId'])
											);*/
										
		  $lastId =  db_insert('webservice_test')->fields($newUser)->execute();
		  /* $userRole 					= 	array(
												'uid' => $lastId,
												'rid' => 8
											);
			db_insert('users_roles')->fields($userRole)->execute();*/
			
		}catch (Exception $e) {
    $transaction->rollback();
   	return services_error("PDO Exception".$e,500);
  }
				
			//return array('id'=>$lastId);						
			return array('code'=>200, 'Last_Id'=>$lastId,'content'=>array('Username' => $user_arr['userName'], 'Mobile_No' => $user_arr['mobileNo'],'msg'=>'Successfully added'));	
	}

function application_status($user_arr = NULL){
	
	$e_name 				= trim($user_arr['e_name']);
	$user_id				= trim($user_arr['user_id']);
	$act_id 				= trim($user_arr['act_id']);
	$final_submit_status 	= trim($user_arr['final_submit_status']);
	$status					= trim($user_arr['status']);
	$application_date 		= trim($user_arr['application_date']);
	$ld_uid 				= trim($user_arr['ld_uid']);
	
	
	$transaction = db_transaction();
		
	try {
		$applicationStatus 	= 	array(
									'establishment_name' 	=> $e_name,
									'lc_uid' 				=> $user_id, 
									'act_id' 				=> $act_id,
									'final_submit_status' 	=> $final_submit_status,
									'status' 				=> $status,
									'application_date' 		=> format_date(strtotime($application_date), 'custom', 'Y-m-d'),
									'ld_uid '				=> $ld_uid 					
								);								
											
											
		db_insert('ld_lc_application_status')->fields($applicationStatus)->execute();
		
	}catch (Exception $e) {
    	$transaction->rollback();
   		return services_error("PDO Exception".$e,500);
	}
	return array('code'=>200,'content'=>array('establishmentName'=>$e_name,'msg'=>'Successfully added'));
}

function chk_email($str){
	if (!filter_var($str, FILTER_VALIDATE_EMAIL)) {
		return 2;
	}
}
function chk_special_chars($str){
	if(preg_match("/[^a-zA-Z0-9\,\.\_\-\:\s\/]+/", "$str")){
		return 2;
	}
}
function chk_pin($str){
	if(!preg_match("/^([7])([0-9]){5}$/", "$str")){
		return 2;
	}
}

function chk_mobile($str){
	if(!preg_match("/^([7-9])([0-9]){9}$/", "$str")){
		return 2;
	}	
}

function chk_not_empty($un = NULL,$email = NULL,$mob = NULL){
	if(empty($un) || $un == NULL)
		return 2;
	if(empty($email) || $email == NULL)
		return 3;
	if(empty($mob) || $mob == NULL)
		return 4;
}

function get_dist_id($dist_name = NULL){
	$dist_id = 0;
		switch($dist_name){
		case 'South 24 Parganas' : $dist_id = 18; break;
		case 'Purulia' : $dist_id = 14; break;
		case 'North Dinajpur' : $dist_id = 4; break;
		case 'Birbhum' : $dist_id = 8; break;
		case 'Bankura' : $dist_id = 13; break;
		case 'Bardhaman' : $dist_id = 9; break;
		case 'Darjeeling' : $dist_id = 1; break;
		case 'South Dinajpur' : $dist_id = 5; break;
		case 'Hooghly' : $dist_id = 12; break;
		case 'Howrah' : $dist_id = 16; break;
		case 'Jalpaiguri' : $dist_id = 2; break;
		case 'Cooch Behar' : $dist_id = 3; break;
		case 'Kolkata' : $dist_id = 17; break;
		case 'Maldah' : $dist_id = 6; break;
		case 'East Midnapore' : $dist_id = 19; break;
		case 'West Midnapore' : $dist_id = 15; break;
		case 'Murshidabad' : $dist_id = 7; break;
		case 'Nadia' : $dist_id = 10; break;
		case 'North 24 Parganas' : $dist_id = 11; break;
		case 'Not Applicable' : $dist_id = 0; break;
		default : $dist_id = 0;			
	}
	return $dist_id;
}

function user_validation($user_arr = NULL){
	
	$username=$user_arr['username'];
	$authkey=$user_arr['authkey'];
	$transaction = db_transaction();
	try{
		
	/*$app_reg_det = db_select('ld_users_details', 'lud');
	$app_reg_det ->fields('lud', array());
	$app_reg_det->condition('lud.uid',trim($user->uid),'=');
	$result_det = $app_reg_det->execute();
	if($result_det->rowCount() > 0){
		$reg_det 	= 	$result_det->fetchAssoc();	*/
		
		
	$prof_det = db_select('users','lcam');
		$prof_det->fields('lcam', array());
		$prof_det->condition('lcam.name', trim($username), '=');
		$result_1 = $prof_det->execute();
		if($result_1->rowCount()>0){
			$lc_data_1 	= $result_1->fetchAssoc();
			$user_id 	= $lc_data_1['uid'];
		}
		
	$prof_det2 = db_select('sessions','lcam');
		$prof_det2->fields('lcam', array());
		$prof_det2->condition('lcam.uid', trim($user_id), '=');
		$prof_det2->condition('lcam.sid', trim($authkey), '=');
		$result_1 = $prof_det2->execute();
		if($result_1->rowCount()>0){
			$chk_stat="200";
			$chk_val="logged in";
			
		}
		else
		{
			$chk_stat="500";
			$chk_val="Not a Valid User";
		}
	}
	catch (Exception $e) {
			
			
    $transaction->rollback();
	return array('content'=>"PDO Exception".$e,'code'=>500);
  }
			
	return array('code'=>$chk_stat,'status'=>$chk_val);
	
}

function central_inspection_status($user_arr = NULL){
	print_r($user_arr);
	exit;
}