<?php
function change_password_form($form, &$form_state) {
    drupal_add_js(drupal_get_path('module', 'asset_user') . '/crypto-js.min.js'); 
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');
	if(user_is_anonymous()){
		return $form;	
	}
	$form['#account'] = $GLOBALS['user'];
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Change Password</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 $form['current_pass'] = array(
	  '#type'=>'password',
	  '#title' => t('Current password'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Current Password'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);
	$form['new_pass'] = array(
	  '#type'=>'password',
	  '#title' => t('New Password'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'id'=>'new_pass','placeholder'=>'Enter New Password'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);	
	$form['new_pass_ct_val'] = array(
	  '#type'=>'hidden',
	  //'#title' => t('New Password'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'id'=>'new_pass_ct_val','placeholder'=>'Enter New Password'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);	
	$form['new_pass_s_val'] = array(
	  '#type'=>'hidden',
	  //'#title' => t('New Password'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'id'=>'new_pass_s_val','placeholder'=>'Enter New Password'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);	
	$form['confirm_pass'] = array(
	  '#type'=>'password',
	  '#title' => t('Confirm Password'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'id'=>'confirm_pass','placeholder'=>'Enter Confirm Password'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);
	$form['confirm_pass_ct_val'] = array(
	  '#type'=>'hidden',
	  //'#title' => t('New Password'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'id'=>'confirm_pass_ct_val','placeholder'=>'Enter New Password'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);	
	$form['confirm_pass_s_val'] = array(
	  '#type'=>'hidden',
	  //'#title' => t('New Password'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'id'=>'confirm_pass_s_val','placeholder'=>'Enter New Password'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);	
	$form['submit'] = array(
	  '#type'=>'submit',
	  '#value'=> t('Submit'),
	  '#attributes' => array('class'=>array('form-control btn btn-info'), 'id'=>'sub_click',  'onclick'=>'pass_encrypt()'),
	  //'#attributes' => array('class'=>array('form-control btn btn-info'), 'id'=>'sub_click'),
	  '#prefix' => '<div class="col-md-6"><div class="input-group">',
	  '#suffix' => '</div></div>'
	);	
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	return $form;
}

function change_password_form_validate($form, &$form_state) {
	require_once DRUPAL_ROOT .'/'. variable_get('password_inc', 'includes/password.inc');
	
	$key = "WbAdmLb#4321";
	$new_pass_ct_val = $form_state['values']['new_pass_ct_val'];
	$new_pass_s_val = $form_state['values']['new_pass_s_val'];
	$new_pass_iv = $form_state['values']['new_pass'];	
	$string = '{"ct":"'.$new_pass_ct_val.'","iv":"'.$new_pass_iv.'","s":"'.$new_pass_s_val.'"}';
	$new_pass = cryptoJsAesDecrypt($key, $string); 
	
	$confirm_pass_ct_val = $form_state['values']['confirm_pass_ct_val'];
	$confirm_pass_s_val = $form_state['values']['confirm_pass_s_val'];
	$confirm_pass_iv = $form_state['values']['confirm_pass'];	
	$string = '{"ct":"'.$confirm_pass_ct_val.'","iv":"'.$confirm_pass_iv.'","s":"'.$confirm_pass_s_val.'"}';
	$confirm_pass = cryptoJsAesDecrypt($key, $string); 
	
	if (!$form_state['values']['current_pass']) {
		form_set_error('current_pass', 'Please enter current password');   
	}
	if (!$new_pass) {
		form_set_error('new_pass', 'Please enter new password');   
	}
	if (!$confirm_pass) {
		form_set_error('confirm_pass', 'Please enter confirm password');   
	}
	if(!user_check_password($form_state['values']['current_pass'], $form['#account'])){
		form_set_error('current_pass', t('The current password you provided is incorrent'));	
	}
	if(!preg_match('/(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,20}+$/', $new_pass)) {
		form_set_error('new_pass', 'Minimum eight characters, at least one uppercase letter, one lowercase letter, one number and one special character.');
	}
	if (strlen($new_pass) > 0 || strlen($confirm_pass) > 0) {
		if (strcmp($new_pass, $confirm_pass)) {
		  form_set_error('confirm_pass', t('The specified passwords do not match.'));
		}
	}
}

function change_password_form_submit($form, &$form_state) { 
  $key = "WbAdmLb#4321";
  $new_pass_ct_val = $form_state['values']['new_pass_ct_val'];
  $new_pass_s_val = $form_state['values']['new_pass_s_val'];
  $new_pass_iv = $form_state['values']['new_pass'];	
  $string = '{"ct":"'.$new_pass_ct_val.'","iv":"'.$new_pass_iv.'","s":"'.$new_pass_s_val.'"}';
  //die($string); exit;
  $password = cryptoJsAesDecrypt($key, $string);
  
	$edit = array('pass'=>$password);
	
	user_save($form['#account'],$edit);
	
	drupal_set_message(t('Your password has been changed'));
}

function add_user_form($form, &$form_state) {
	global $user;
	
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	
	$directorate_list = getDirectorateListByRoleId($user->uid);
	
	//print_r($directorate_list); exit;
	
	//$district_list = getDistrictListByRoleId($user->uid);
	$district_list = getDistrictAllList();
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Add New User</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
	
	$form['directorate_code'] = array(
	  '#title' => t('Select Directorate'),	
	  '#type' => 'select',
	  //'#multiple' => TRUE,
	  '#required' => TRUE,
	  '#options' => $directorate_list,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
    );
	$form['district_code'] = array(
	  '#title' => t('Select District'),	
	  '#type' => 'select',
	  //'#multiple' => TRUE,
	  '#ajax'=>array(
	   			'callback'	=> 'ajax_office_callback',
				'event' 	=> 'change',
				'effect' 	=> 'fade',			
				'progress'	=>	array(
					'type'		=>'throbber',
					'message'	=>t('loading'),
			    ),
		),
	  '#required' => TRUE,
	  '#options' => $district_list,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
    );
	
	/*$form['district_code'] = array(
	  '#title' => t('Select District'),	
	  '#type' => 'select',
	  //'#multiple' => TRUE,
	  '#required' => TRUE,
	  '#options' => $district_list,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
    );*/
	//if(in_array('assetdiradmin', $user->roles)) {
		//$office_list = getOfficeListByDistrict(key($directorate_list),key($district_list));
	 if(isset($form_state['values']['district_code']) && trim($form_state['values']['district_code']) != '' && trim($form_state['values']['district_code']) != '0'){
		$form['office_id'] = array(
		  '#title' => t('Select Office'),	
		  '#type' => 'select',
		  //'#multiple' => TRUE,
		  '#required' => TRUE,
		  '#options' => getOfficeListByDistrict($form_state['values']['district_code'],$form_state['values']['directorate_code']),
		  '#attributes' => array('class'=>array('form-control')),
		  '#prefix' => '<div id="ld_idcard_replace" class="col-md-12">',
		  '#suffix' => '</div>'
		);
	 }else{
		 $form['office_id'] = array(
			'#prefix' => '<div id="ld_idcard_replace">',
			'#suffix' => '</div>'
		); 
	 }
	//}
	
	$form['username'] = array(
	  '#type'=>'textfield',
	  '#title' => t('Username'),
	  '#default_value'=>array(0=>""),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Username'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);
	$form['password'] = array(
	  //'#type'=>'password_confirm',
	  '#type'=>'password',
	  '#title' => t('Password'),
	  '#default_value'=>array(0=>""),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'), 'id'=>'new_pass','placeholder'=>'Enter Password'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);	
	// $form['new_pass_ct_val'] = array(
	//   '#type'=>'hidden',
	//   //'#title' => t('New Password'),
	//   '#required' => TRUE,
	//   '#attributes' => array('class'=>array('form-control'),'id'=>'new_pass_ct_val','placeholder'=>'Enter New Password'),
	//   '#prefix' => '<div class="col-md-12">',
	//   '#suffix' => '</div>'
	// );	
	// $form['new_pass_s_val'] = array(
	//   '#type'=>'hidden',
	//   //'#title' => t('New Password'),
	//   '#required' => TRUE,
	//   '#attributes' => array('class'=>array('form-control'),'id'=>'new_pass_s_val','placeholder'=>'Enter New Password'),
	//   '#prefix' => '<div class="col-md-12">',
	//   '#suffix' => '</div>'
	// );	
	$form['password1'] = array(
	  //'#type'=>'password_confirm',
	  '#type'=>'password',
	  '#title' => t('Confirm Password'),
	  '#default_value'=>array(0=>""),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'id'=>'confirm_pass','placeholder'=>'Enter Password'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);	
	// $form['confirm_pass_ct_val'] = array(
	//   '#type'=>'hidden',
	//   //'#title' => t('New Password'),
	//   '#required' => TRUE,
	//   '#attributes' => array('class'=>array('form-control'),'id'=>'confirm_pass_ct_val','placeholder'=>'Enter New Password'),
	//   '#prefix' => '<div class="col-md-12">',
	//   '#suffix' => '</div>'
	// );	
	// $form['confirm_pass_s_val'] = array(
	//   '#type'=>'hidden',
	//   //'#title' => t('New Password'),
	//   '#required' => TRUE,
	//   '#attributes' => array('class'=>array('form-control'),'id'=>'confirm_pass_s_val','placeholder'=>'Enter New Password'),
	//   '#prefix' => '<div class="col-md-12">',
	//   '#suffix' => '</div>'
	// );		
	$form['email'] = array(
	  '#type'=>'textfield',
	  '#title' => t('Email'),
	  '#default_value'=>array(0=>""),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Email'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);	
	
	$role_list = array();	
	$query = db_select('role', 'r');
  	$query ->fields('r', array( 'rid', 'name'));
	$query->orderBy('r.rid','ASC');
  	$result = $query->execute();
	$resultRole = $result->fetchAll();
	
	if(!empty($resultRole)){
		foreach($resultRole as $val) {
			if($val->rid != '1' && $val->rid != '2' && $val->rid != '3')
			$role_list[$val->rid]=trim($val->name);
		}
	}
	if(array_key_exists(9, $user->roles)) {
		unset($role_list[4]);
		unset($role_list[5]);
		unset($role_list[6]);
		unset($role_list[7]);
		unset($role_list[8]);
		unset($role_list[9]);
		unset($role_list[10]);
	}
	if(array_key_exists(10, $user->roles)) {
		unset($role_list[4]);
		unset($role_list[5]);
		unset($role_list[6]);
		unset($role_list[7]);
		unset($role_list[8]);
		unset($role_list[9]);
		unset($role_list[10]);
	}

	$form['roles'] = array(
	  '#type'=>'select',
	  '#title' => t('User Roles'),
	 // '#multiple' => TRUE,
	  '#options' => $role_list,
	  //'#default_value'=>array(0=>""),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Please Select'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);
	$form['submit'] = array(
	  '#type'=>'submit',
	  '#value'=> t('Add'),
	  '#attributes' => array('class'=>array('form-control btn btn-info')),
	  '#prefix' => '<div class="col-md-6"><div class="input-group">',
	  '#suffix' => '</div></div>'
	);	
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	return $form;
}

// function add_user_form_validate($form, &$form_state) {
// 	//die(trim($form_state['values']['password']));
// 	$key = "WbAdmLb#4321";
// 	$new_pass_ct_val = $form_state['values']['new_pass_ct_val'];
// 	$new_pass_s_val = $form_state['values']['new_pass_s_val'];
// 	$new_pass_iv = $form_state['values']['password'];	
// 	$string = '{"ct":"'.$new_pass_ct_val.'","iv":"'.$new_pass_iv.'","s":"'.$new_pass_s_val.'"}';
// 	$pass1 = cryptoJsAesDecrypt($key, $string); 
	
// 	$confirm_pass_ct_val = $form_state['values']['confirm_pass_ct_val'];
// 	$confirm_pass_s_val = $form_state['values']['confirm_pass_s_val'];
// 	$confirm_pass_iv = $form_state['values']['password1'];	
// 	$string = '{"ct":"'.$confirm_pass_ct_val.'","iv":"'.$confirm_pass_iv.'","s":"'.$confirm_pass_s_val.'"}';
// 	$pass2 = cryptoJsAesDecrypt($key, $string); 
	
// 	//$pass1 = trim($form_state['values']['password']);
//     //$pass2 = trim($form_state['values']['password1']);
	
// 	//echo $pass1.'-->'.$pass2; exit;
	
// 	if (!$form_state['values']['password']) {
// 		form_set_error('password', 'Password field is required.');   
// 	}
// 	if (!$form_state['values']['password1']) {
// 		form_set_error('password1', 'Confirm Password field is required.');   
// 	}
// 	//$match_pattern1 	= 	'/[A-Za-z0-9]+/';
// 	if(!preg_match('/(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,20}+$/', $pass1)) {
// 		form_set_error('password', 'Minimum eight characters, at least one uppercase letter, one lowercase letter, one number and one special character.');
// 	}
	
//   if (strlen($pass1) > 0 || strlen($pass2) > 0) {
// 	if (strcmp($pass1, $pass2)) {
// 	  form_set_error('password1', t('The specified passwords do not match.'));
// 	}
//   }
// 	//exit;
// }

// function add_user_form_submit($form, &$form_state) {
// 	global $user;
	
// 	$key = "WbAdmLb#4321";
// 	$new_pass_ct_val = $form_state['values']['new_pass_ct_val'];
// 	$new_pass_s_val = $form_state['values']['new_pass_s_val'];
// 	$new_pass_iv = $form_state['values']['password'];	
// 	$string = '{"ct":"'.$new_pass_ct_val.'","iv":"'.$new_pass_iv.'","s":"'.$new_pass_s_val.'"}';
// 	$pass1 = cryptoJsAesDecrypt($key, $string); 
	
// 	$newUser = array(
// 		'name' => trim($form_state['values']['username']),
// 		'pass' => $pass1, 
// 		'mail' => trim($form_state['values']['email']),
// 		'status' => 1,
// 		'init' => trim($form_state['values']['email']),
// 		/*'roles' => array(
// 		  DRUPAL_AUTHENTICATED_RID => $roleVal,
// 		),*/
// 	);
	
// 	user_save(null, $newUser);
// 	$id = db_query("SELECT MAX(uid) as max_id FROM users")->fetchCol();
	
// 	$usinfo = array( 'uid' => $id['0'],
// 			'rid' => $form_state['values']['roles'],
// 		);
// 	db_insert('users_roles')->fields($usinfo)->execute();
	
// 	$user_details = array( 'uid' => $id['0'],
// 		'email' => trim($form_state['values']['email']),
// 		'one_time_pass_flag' => 0,
// 		'status' => 1,
// 		'pass' => $pass1, 
// 	);
	
// 	$r = db_insert('a_user_details')->fields($user_details)->execute();
	
// 	if($form_state['values']['roles'] == 10){
// 	  $role = 'NODAL';	
// 	}elseif($form_state['values']['roles'] == 11){
// 	  $role = 'FIELD OFFICE';	
// 	}
	
// 	/*if(in_array('assetdiradmin', $user->roles)) {
// 		$office_id = $form_state['values']['office_id'];
// 	}else{
// 		$office_id = 0;
// 	}*/
// 	$user_details_service = array( 'uid' => $id['0'],
// 		'directorate_code' => $form_state['values']['directorate_code'],
// 		'district_code' => $form_state['values']['district_code'],
// 		'designation' => $form_state['values']['directorate_code']." ".$role,
// 		'office_id' => $form_state['values']['office_id']
// 	);
	
// 	$rs = db_insert('a_user_details_service')->fields($user_details_service)->execute();
// 	if($rs){
// 			drupal_set_message('User Has Been Successfully Registered');
// 			if(in_array('assetdiradmin', $user->roles)) {
// 				drupal_goto('listuserbynodal');	
// 			}else{
// 				//drupal_goto('user-list');
// 				drupal_goto('add-user');
// 			}
// 	}else{
// 		drupal_set_message('There is some problem. Please try after sometime');
// 		drupal_goto('add-user');
// 	}
// }

function add_user_form_validate($form, &$form_state) {
//die(trim($form_state['values']['password']));
// $key = "WbAdmLb#4321";
// $new_pass_ct_val = $form_state['values']['new_pass_ct_val'];
// $new_pass_s_val = $form_state['values']['new_pass_s_val'];
$new_pass_iv = $form_state['values']['password'];	
// $string = '{"ct":"'.$new_pass_ct_val.'","iv":"'.$new_pass_iv.'","s":"'.$new_pass_s_val.'"}';
// $pass1 = cryptoJsAesDecrypt($key, $string); 

// $confirm_pass_ct_val = $form_state['values']['confirm_pass_ct_val'];
// $confirm_pass_s_val = $form_state['values']['confirm_pass_s_val'];
$confirm_pass_iv = $form_state['values']['password1'];	
// $string = '{"ct":"'.$confirm_pass_ct_val.'","iv":"'.$confirm_pass_iv.'","s":"'.$confirm_pass_s_val.'"}';
// $pass2 = cryptoJsAesDecrypt($key, $string); 

//$pass1 = trim($form_state['values']['password']);
    //$pass2 = trim($form_state['values']['password1']);

//echo $pass1.'-->'.$pass2; exit;

if (!$form_state['values']['password']) {
form_set_error('password', 'Password field is required.');   
}
if (!$form_state['values']['password1']) {
form_set_error('password1', 'Confirm Password field is required.');   
}
//$match_pattern1 	= 	'/[A-Za-z0-9]+/';
// if(!preg_match('/(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,20}+$/', $new_pass_iv)) {
// 	form_set_error('password', 'Minimum eight characters, at least one uppercase letter, one lowercase letter, one number and one special character.');
// }

  if (strlen($new_pass_iv) > 0 || strlen($confirm_pass_iv) > 0) {
if (strcmp($new_pass_iv, $confirm_pass_iv)) {
  form_set_error('password1', t('The specified passwords do not match.'));
}
  }
//exit;
}

function add_user_form_submit($form, &$form_state) {
	global $user;
	
	// $key = "WbAdmLb#4321";
	// $new_pass_ct_val = $form_state['values']['new_pass_ct_val'];
	// $new_pass_s_val = $form_state['values']['new_pass_s_val'];
	$new_pass_iv = $form_state['values']['password'];	
	// $string = '{"ct":"'.$new_pass_ct_val.'","iv":"'.$new_pass_iv.'","s":"'.$new_pass_s_val.'"}';
	// $pass1 = cryptoJsAesDecrypt($key, $string); 
	
	$newUser = array(
		'name' => trim($form_state['values']['username']),
		'pass' => $new_pass_iv, 
		'mail' => trim($form_state['values']['email']),
		'status' => 1,
		'init' => trim($form_state['values']['email']),
		/*'roles' => array(
		  DRUPAL_AUTHENTICATED_RID => $roleVal,
		),*/
	);
	
	user_save(null, $newUser);
	$id = db_query("SELECT MAX(uid) as max_id FROM users")->fetchCol();
	
	$usinfo = array( 'uid' => $id['0'],
			'rid' => $form_state['values']['roles'],
		);
	db_insert('users_roles')->fields($usinfo)->execute();
	
	$user_details = array( 'uid' => $id['0'],
		'email' => trim($form_state['values']['email']),
		'one_time_pass_flag' => 0,
		'status' => 1,
		'pass' => $new_pass_iv, 
	);
	
	$r = db_insert('a_user_details')->fields($user_details)->execute();
	
	if($form_state['values']['roles'] == 10){
	  $role = 'NODAL';	
	}elseif($form_state['values']['roles'] == 11){
	  $role = 'FIELD OFFICE';	
	}
	
	/*if(in_array('assetdiradmin', $user->roles)) {
		$office_id = $form_state['values']['office_id'];
	}else{
		$office_id = 0;
	}*/
	$user_details_service = array( 'uid' => $id['0'],
		'directorate_code' => $form_state['values']['directorate_code'],
		'district_code' => $form_state['values']['district_code'],
		'designation' => $form_state['values']['directorate_code']." ".$role,
		'office_id' => $form_state['values']['office_id']
	);
	
	$rs = db_insert('a_user_details_service')->fields($user_details_service)->execute();
	if($rs){
			drupal_set_message('User Has Been Successfully Registered');
			if(in_array('assetdiradmin', $user->roles)) {
				drupal_goto('listuserbynodal');	
			}else{
				//drupal_goto('user-list');
				drupal_goto('add-user');
			}
	}else{
		drupal_set_message('There is some problem. Please try after sometime');
		drupal_goto('add-user');
	}
}

function employee_profile_form($form, &$form_state){
	global $user,$base_root,$base_path;
	
	$userData = getLoginUserDetailForAsset($user->uid);
	
	
	$form['#attributes']['class'][] = 'form-vertical';
    $form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Update Profile</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	
	if(!in_array(variable_get('field', 11), array_keys($user->roles)) && !in_array(variable_get('assetdiradmin', 10), array_keys($user->roles)) && !in_array(variable_get('assetadmin', 9), array_keys($user->roles))){
	$form['hrms_id'] = array(
		'#type' => 'textfield',
		'#title' => t('HRMS ID'),
		'#required' => TRUE,
		'#default_value' => !empty($userData['hrms_id']) ? $userData['hrms_id'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'HRMS ID','readonly'=>'readonly'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	 ); 
	 	$email_id = 'Personal Email ID';
	}else{
		$email_id = 'Official Email ID';
		
	}
	$form['fname'] = array(
		'#type' => 'textfield',
		'#title' => t('Full Name'),
		'#required' => TRUE,
		'#default_value' => !empty($userData['fname']) ? $userData['fname'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Full Name'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	 );
	 $form['mobile'] = array(
	   '#title'=>t('Mobile No'),
	   '#type' => 'textfield',
	   '#required' => TRUE,
	   '#default_value' => !empty($userData['mobile']) ? $userData['mobile'] : '',
	   '#maxlength' => 10,
	   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Mobile Number', 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-4">',
	   '#suffix' => '</div>'
	);
	$form['email'] = array(
	   '#title'=> $email_id,
	   '#type' => 'textfield',
	   '#required' => TRUE,
	   '#default_value' => !empty($userData['email']) ? $userData['email'] : '',
	   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>$email_id, 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-4">',
	   '#suffix' => '</div>'
	);	
	
	if(!in_array(variable_get('field', 11), array_keys($user->roles)) && !in_array(variable_get('assetdiradmin', 10), array_keys($user->roles)) && !in_array(variable_get('assetadmin', 9), array_keys($user->roles))){
	$form['dob'] = array(
	   '#title'=>t('Date of Birth (DD-MM-YYYY)'),
	   '#type' => 'textfield',
	   '#required' => TRUE,
	   '#default_value' => !empty($userData['dob']) ? date('d-m-Y',strtotime($userData['dob'])) : '',
	   '#attributes' => array('class'=>array('form-control','datepiker'), 'placeholder'=>'Date of Birth', 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-4">',
	   '#suffix' => '</div>'
	);
	
	$form['doj'] = array(
	   '#title'=>t('Date of Joining (DD-MM-YYYY)'),
	   '#type' => 'textfield',
	   '#required' => TRUE,
	   '#default_value' => !empty($userData['doj']) ? date('d-m-Y',strtotime($userData['doj'])) : '',
	   '#attributes' => array('class'=>array('form-control','datepiker'), 'placeholder'=>'Date of Joining', 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-4">',
	   '#suffix' => '</div>'
	);
	}
	
	/*if($userData['one_time_pass_flag']==0){
		$form['#account'] = $GLOBALS['user'];
		
		$form['current_pass'] = array(
			'#type' => 'password',
			'#title' => t('Current password'),
			'#size' => 25,
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control')),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		 );
		 $form['account']['pass'] = array(
			'#type' => 'password_confirm',
			'#size' => 25,
			//'#title' => t('New'),
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control')),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		  ); 
	}*/
	$form['submit'] = array(
    	'#type' => 'submit',
		'#value' => 'Verify & Update',
		'#attributes' => array('class'=>array('form-control btn btn-info')),
		'#prefix' => '<div class="col-md-12"><div class="input-group">',
		'#suffix' => '</div></div>'
	); 
	 
    $form['form_end'] = array(
         '#type' => 'markup',
         '#markup' => '</div>',
		 '#suffix' => '</div></div>'
    );
	
	return $form;		 
}

function employee_profile_form_validate(&$form, &$form_state) { 
	global $user;
	
  if (!$form_state['values']['fname']) {
    form_set_error('fname', 'Please enter your First Name!');   
  }
  
  $fname = $form_state['values']['fname'];
	if (!preg_match('/[A-Za-z]+$/', $fname)) {  
    form_set_error('fname', t('First Name should be text only!!'));
  }	
  
    if (!$form_state['values']['mobile']) {
    form_set_error('mobile', 'Please enter your Mobile Number!');    
  }
  
  if ($form_state['values']['mobile']!="" && (strlen($form_state['values']['mobile'])<10 || strlen($form_state['values']['mobile'])>10)) {
    form_set_error('mobile', 'Mobile Number should be of 10 digit');    
  }
  
  $mobile = $form_state['values']['mobile'];
	if (!preg_match('/^[7689][0-9]{9}$/', $mobile)) {  
    form_set_error('mobile', t('Mobile number must start with the digit 6 or 7 or 8 or 9! Please enter a valid Mobile Number'));
  }
  
  if (!$form_state['values']['email']) {
    form_set_error('email', 'Please enter your Email Id!');    
  } 
  
 $email = $form_state['values']['email'];
 if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
			form_set_error('email', t('Please enter a Valid Email Id!')); 
 }

	
	/*$userDataValidate = array();
  	$query = db_select('a_user_details', 'ud');
	$query->fields('ud', array('one_time_pass_flag'));
	$query->condition('ud.uid', $user->uid, '=');
	$result = $query->execute();
	$userDataValidate = $result->fetchAssoc();	
 	
	if($userDataValidate['one_time_pass_flag']==0){
	  // Make sure the password functions are present.
	  require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
	
	  // Make sure the provided current password is valid for this account.
	  if (!user_check_password($form_state['values']['current_pass'], $form['#account'])) {
		form_set_error('current_pass', t('The current password you provided is incorrect.'));
	  }
	  
	  if(trim($form_state['values']['current_pass'])==trim($form_state['values']['pass'])){
		  form_set_error('pass', t('The new password you provided must not be same as previous.'));
	  }

	}*/
}

function employee_profile_form_submit($form, &$form_state){
	global $user;
	
	//print_r($form_state['values']); exit;
	
	$userDataSubmit = array();
  	$query = db_select('a_user_details', 'ud');
	$query->fields('ud', array('one_time_pass_flag'));
	$query->condition('ud.uid', $user->uid, '=');
	$result = $query->execute();
	$userDataSubmit = $result->fetchAssoc();	
	
	$query_u = db_update('users');
	$query_u->fields(array('mail' => $form_state['values']['email']));
	$query_u->condition('uid', $user->uid);
	$rs_u = $query_u->execute();
 	
	if(!in_array(variable_get('field', 11), array_keys($user->roles)) && !in_array(variable_get('assetdiradmin', 10), array_keys($user->roles)) && !in_array(variable_get('assetadmin', 9), array_keys($user->roles))){
		$query = db_update('a_user_details');
		$query->fields(array('fname'			=> $form_state['values']['fname'],
							'mobile'			=> $form_state['values']['mobile'],
							'email'				=> $form_state['values']['email'],
							'dob'				=> !empty($form_state['values']['dob'])? date('Y-m-d',strtotime($form_state['values']['dob'])) : '',
							'doj'				=> !empty($form_state['values']['doj'])? date('Y-m-d',strtotime($form_state['values']['doj'])) : '',
							));
		$query->condition('uid', $user->uid);
		$rs = $query->execute();
	}else{
		$query = db_update('a_user_details');
		$query->fields(array('fname'			=> $form_state['values']['fname'],
							'mobile'			=> $form_state['values']['mobile'],
							'email'				=> $form_state['values']['email'],
							));
		$query->condition('uid', $user->uid);
		$rs = $query->execute();
	}
	
	if($rs){
		if($userDataSubmit['one_time_pass_flag']==0){
			//$edit = array('pass' => $form_state['values']['pass'],'mail' => $form_state['values']['email']);
			//user_save($form['#account'], $edit);
			
			$query = db_update('a_user_details');
			$query->fields(array('one_time_pass_flag'=> 1));
			$query->condition('uid', $user->uid);
			$query->execute();
		}
		
		drupal_set_message(t('Your profile has been updated successfully.'));
		if(in_array('asset', $user->roles)){
			drupal_goto('assetuser-dashboard');
		}
	}else{
		drupal_set_message(t('Your profile is not updated. Please update your profile first.'));
	}
}

function ajax_office_callback($form,&$form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#ld_idcard_replace', drupal_render($form['office_id']));
	return array('#type' => 'ajax', '#commands' => $commands);
 }