<?php
function project_list($form, &$form_state){
	
	$form['form_begin'] = array(
		'#type' => 'markup',
		'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">User List</h4></div><div class="widget-main">',
	 );
	$form['user_list_details'] = array(
	  '#type' => 'markup',
	  '#markup' => get_user_list(),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
    );		
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );
	return $form;
}



function get_user_list(){
  global $user;
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');		
  $output = '';
  $header = array(
				array('data'=> 'User Name'),
				array('data'=> 'Role'),
				//array('data'=> 'Project'),
				array('data'=> 'Status'),
				array('data'=> 'Last Access'),
				array('data'=> 'Created On'),
				array('data'=> 'Action')
				//array('data'=> 'Status'),
			);
  $rows = array();
  $roles = array();
  $roles[] = 'administrator';
  $roles[] = 'cmsmanager';
  $roles[] = 'maptrackuser';
  $roles[] = 'adminmanager';
  $roles[] = 'investor';
  $roles[] = 'assetadmin';
  	
  
  //$roles = array('administrator');
  
  $query = db_select('users', 'u');
  $query->leftJoin('users_roles', 'ur', 'u.uid = ur.uid');  
  $query->leftJoin('role', 'r', 'ur.rid = r.rid'); 
  $query->leftJoin('a_user_details', 'ud', 'u.uid = ud.uid');
   
  //$query->leftJoin('project_mst', 'pm', 'pum.pid = pm.pid'); 
  /*$query->fields('pm', array('project_name')); */  
  
  //$query->fields('ur', array('uid')); 
  $query->fields('u', array('uid','name','access','created','status'));
  $query->addField('r', 'name', 'rolename');
  $query->condition('r.name', $roles, 'NOT IN');
  $query->orderBy("r.name", "ASC");
  $result = $query->execute();
  $rsData = $result->fetchAll();
  
  /*$i = 0;
  $myNewArray = array();
  for($i=0; $i<sizeof($rsData);){
	  if(!in_array($rsData[$i]->uid, $myNewArray)){
		  $myNewArray[$rsData[$i]->uid]['name'] = $rsData[$i]->name;
		  $myNewArray[$rsData[$i]->uid]['access'] = $rsData[$i]->access;
		  $myNewArray[$rsData[$i]->uid]['created'] = $rsData[$i]->created;
		  $myNewArray[$rsData[$i]->uid]['status'] = $rsData[$i]->status;
		  $myNewArray[$rsData[$i]->uid]['rolename'] = $rsData[$i]->rolename;
	  }
	 $i++; 
  }*/
  //print_r($myNewArray);
  //exit;
 	
 foreach($rsData as $record=>$val) {
	 
	/* $query_p = db_select('project_mst', 'pm');
	 $query_p->leftJoin('project_user_map', 'pum', 'pum.pid = pm.pid'); 
	 $query_p->fields('pm', array('project_name'));
	 $query_p->condition('pum.uid', $record, '=');
	 //$query_p->condition('pum.status', '1', '=');
	 $result_p = $query_p->execute();
  	 $resultProjectData = $result_p->fetchAll();
	 
	 if(!empty($resultProjectData)){
		 $project_name = '<ul style="text-align:left">';
		 foreach($resultProjectData as $p){
			$project_name .= '<li>'.$p->project_name.'</li>';
		 }
		 $project_name .='</ul>';
	 }else{
		 $project_name = 'N/A';
	 }*/
	 
	 
	 if($val->status == 1){
		 $status = 'Active';
	 }else{
		 $status = 'Blocked';
	 }
	 
	 
	 /*$user_role = '<ul style="text-align:left">';
	 foreach($val['rolename'] as $rl){
		  $user_role .= '<li>'.$rl.'</li>';
	 }
	 $user_role .='</ul>';*/
	 
	 $viewLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>','edit-user/'.$val->uid,array('html' => TRUE,'attributes'=>array('title' => 'Edit','class'=>'green'))); 
	 $delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>', 'delete-user/'.$val->uid, array('html' => TRUE,'attributes'=>array('title' => 'Delete', 'class'=>'red')));
	 
	  /*if(strtotime(format_date($record['access']))==""){
		$access = 'Never' ; 
	  }else{
		$access = format_date($record['access'], 'custom', 'd-m-Y H:i:s'); 
	  }*/
	  $rows[] = array(
					array('data' => $val->name),
					array('data' => $val->rolename),
					//array('data' => $project_name),
					array('data' => $status),
					array('data' => format_date($val->access, 'custom', 'd-m-Y H:i:s')),
					array('data' => format_date($val->created, 'custom', 'd-m-Y H:i:s')),
					array('data' => $viewLink.' '.$delLink)
		);
  }
  
  $output = theme_table(
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '',
      'colgroups' => array(),
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');

  // Returning the output
  return '<div class="formdvider viewlist">'.$output.'</div>';		

}

function project_form($form, &$form_state) {
	global $user;
	
	/*$directorate_list = getDirectorateAllList();
	$district_list = getDistrictAllList();*/
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Add New User</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
	/*$form['directorate_code'] = array(
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
	  '#required' => TRUE,
	  '#options' => $district_list,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
    );*/
	$form['fname'] = array(
		'#type' => 'textfield',
		'#title' => t('Enter Full Name'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Full Name'),
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	 );
	$form['dob'] = array(
		'#type' => 'textfield',
		'#title' => t('Date of Birth'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Birth'),
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	 );
	$form['doj'] = array(
		'#type' => 'textfield',
		'#title' => t('Date of Joining'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Joining'),
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	 );
	$form['dor'] = array(
		'#type' => 'textfield',
		'#title' => t('Date of Retirement'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Retirement'),
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	 );   
	$form['username'] = array(
	  '#type'=>'textfield',
	  '#title' => t('HRMS ID'),
	  '#default_value'=>array(0=>""),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter HRMS ID'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);
	$form['password'] = array(
	  '#type'=>'password_confirm',
	 // '#title' => t('Password'),
	  '#default_value'=>array(0=>""),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Password'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);
	 $form['mobile'] = array(
	   '#title'=>t('Mobile No'),
	   '#type' => 'textfield',
	   '#required' => TRUE,
	   '#maxlength' => 10,
	   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Mobile Number', 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-12">',
	   '#suffix' => '</div>'
	);	
	$form['email'] = array(
	  '#type'=>'textfield',
	  '#title' => t('Email'),
	  '#default_value'=>array(0=>""),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Email'),
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


function project_edit_form($form, &$form_state, $arg='') {
	global $user;
	
	//print_r($list_data);
	//$roleVal = array();
	$existingUser = user_load($arg);
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Edit User</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	
	//$all_directorate_list = getDirectorateAllList();
	//$directorate_list = getDirectorateListByRoleId($user->uid); // for login user has permission to which directorate
	//$directorate_list_selected = getDirectorateListByRoleId($arg); // for editing uid takes from arguments
	
	//$all_district_list = getDistrictAllList();
	//$district_list = getDistrictListByRoleId($user->uid); // for login user has permission to which district
	//$district_list_selected = getDistrictListByRoleId($arg); // for editing uid takes from arguments
	$resultData = getAllUidInfoFromPid($arg);
	/*$form['directorate_code'] = array(
		  '#title' => t('Select Directorate'),	
		  '#type' => 'select',
		  //'#multiple' => TRUE,
		  '#required' => TRUE,
		  '#options' => $all_directorate_list,
		  '#default_value' => !empty($directorate_list_selected) ? $directorate_list_selected : '',
		  '#attributes' => array('class'=>array('form-control')),
		  '#prefix' => '<div class="col-md-12">',
		  '#suffix' => '</div>'
    );
	
	$form['district_code'] = array(
		  '#title' => t('Select District'),	
		  '#type' => 'select',
		  //'#multiple' => TRUE,
		  '#required' => TRUE,
		  '#options' => $all_district_list,
		  '#default_value' => !empty($district_list_selected) ? $district_list_selected : '',
		  '#attributes' => array('class'=>array('form-control')),
		  '#prefix' => '<div class="col-md-12">',
		  '#suffix' => '</div>'
    );	 */
	 
	$form['user_id'] = array(
		  '#type'=>'hidden',
		  '#title' => t('UserID'),
		  '#default_value'=>$arg,
		  '#required' => TRUE,
		  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'User ID','readonly'=>'readonly'),
		  '#prefix' => '<div class="col-md-12">',
		  '#suffix' => '</div>'
	);
	$form['fname'] = array(
		'#type' => 'textfield',
		'#title' => t('Enter Full Name'),
		'#default_value' => !empty($resultData) ? $resultData['fname'] : '',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Full Name'),
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	 );
	 $form['dob'] = array(
		'#type' => 'textfield',
		'#title' => t('Date of Birth'),
		'#default_value' => !empty($resultData) ? date('d-m-Y',strtotime($resultData['dob'])) : '',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Birth'),
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	 );
	$form['doj'] = array(
		'#type' => 'textfield',
		'#title' => t('Date of Joining'),
		'#default_value' => !empty($resultData) ? date('d-m-Y',strtotime($resultData['doj'])) : '',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Joining'),
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	 );
	$form['dor'] = array(
		'#type' => 'textfield',
		'#title' => t('Date of Retirement'),
		'#default_value' => !empty($resultData) ? date('d-m-Y',strtotime($resultData['dor'])) : '',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Retirement'),
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	 );
	$form['username'] = array(
		  '#type'=>'textfield',
		  '#title' => t('HRMS ID'),
		  '#default_value'=>$existingUser->name,
		  '#required' => TRUE,
		  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'HRMS ID'),
		  '#prefix' => '<div class="col-md-12">',
		  '#suffix' => '</div>'
	);
	$form['mobile'] = array(
	   '#title'=>t('Mobile No'),
	   '#type' => 'textfield',
	   '#default_value' => !empty($resultData) ? $resultData['mobile'] : '',
	   '#required' => TRUE,
	   '#maxlength' => 10,
	   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Mobile Number', 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-12">',
	   '#suffix' => '</div>'
	);
	$form['email'] = array(
	  '#type'=>'textfield',
	  '#title' => t('Email'),
	   '#default_value' => !empty($resultData) ? $resultData['mail'] : '',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Email'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);		
	
		
	$form['submit'] = array(
	  '#type'=>'submit',
	  '#value'=> t('Update'),
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

function project_edit_form_submit($form, &$form_state) {
	
	$existingUserData = array(
		'name' => trim($form_state['values']['username']),
		'mail' => trim($form_state['values']['email']),
		/*'status' => 1,*/
		'roles' => array(8=>8),
		//'roles' => array($form_state['values']['roles']=>$form_state['values']['roles']),
		//'roles' => $form_state['values']['roles'],
	);
	@user_save((object) array('uid' => $form_state['values']['user_id']), (array) $existingUserData);
	
	$query = db_update('a_user_details');
	$query->fields(array(
		'fname' => $form_state['values']['fname'],
		'dob' => date('Y-m-d',strtotime(trim($form_state['values']['dob']))),
		'doj' => date('Y-m-d',strtotime(trim($form_state['values']['doj']))),
		'dor' => date('Y-m-d',strtotime(trim($form_state['values']['dor']))),
		'mobile' => trim($form_state['values']['mobile']),
		'email' => trim($form_state['values']['email']),
		'pass' => trim($form_state['values']['pass'])
	));
	$query->condition('uid', trim($form_state['values']['user_id']));
	$rs = $query->execute();

	/*$query = db_delete('project_user_map');
	$query->condition('uid', trim($form_state['values']['user_id']));
	$rs = $query->execute();
	if($rs){
		foreach($form_state['values']['project_id'] as $val){
			$project_user_map = array( 
				'uid' => $form_state['values']['user_id'],
				'pid' => $val,
				'status' => 1
			);
			db_insert('project_user_map')->fields($project_user_map)->execute();
		}
	}*/
	
	drupal_set_message("Your Record Updated Successfully");
	drupal_goto('user-list');
}


function project_form_submit($form, &$form_state) {

	  	$newUser = array(
			'name' => trim($form_state['values']['username']),
			'pass' => trim($form_state['values']['password']), 
			'mail' => trim($form_state['values']['email']),
			'status' => 1,
			'init' => trim($form_state['values']['email']),
			/*'roles' => array(
			  DRUPAL_AUTHENTICATED_RID => $roleVal,
			),*/
		);
		
		user_save(null, $newUser);
		$id = db_query("SELECT MAX(uid) as max_id FROM users")->fetchCol();
		
		/*foreach($form_state['values']['roles'] as $val){
			$usinfo = array( 'uid' => $id['0'],
				'rid' => $val,
			);
			db_insert('users_roles')->fields($usinfo)->execute();
		}*/
		$usinfo = array( 'uid' => $id['0'],
				'rid' => 8,
			);
		db_insert('users_roles')->fields($usinfo)->execute();
		
		
		$projectinfo = array( 'uid' => $id['0'],
            'fname' => $form_state['values']['fname'],
			'dob' => date('Y-m-d',strtotime(trim($form_state['values']['dob']))),
			'doj' => date('Y-m-d',strtotime(trim($form_state['values']['doj']))),
			'dor' => date('Y-m-d',strtotime(trim($form_state['values']['dor']))),
			'mobile' => trim($form_state['values']['mobile']),
			'email' => trim($form_state['values']['email']),
			'pass' => trim($form_state['values']['pass'])
      	);
		
		$rs = db_insert('a_user_details')->fields($projectinfo)->execute();
		if($rs){
			/*if(!empty($form_state['values']['directorate_code'])){
				foreach($form_state['values']['directorate_code'] as $val){
					$project_user_map = array( 
						'uid' => $id['0'],
						'pid' => $val,
						'status' => 1
					);
					db_insert('project_user_map')->fields($project_user_map)->execute();
				}
				drupal_set_message('User Has Been Successfully Registered');
				drupal_goto('user-list');		
			}else{*/
				drupal_set_message('User Has Been Successfully Registered');
				drupal_goto('user-list');
			//}
		}else{
			drupal_set_message('There is some problem. Please try after sometime');
			drupal_goto('add-user');
		}
}

function project_del($form, &$form_state, $uid='') {
	user_delete($uid);
	drupal_set_message('User Has Been Successfully Deleted');
	drupal_goto('user-list');
	
}

function passchng_render_user_pass_change_form($form, &$form_state) {
   global $user;

    if (!user_is_logged_in()) {
        drupal_access_denied();
    }
  $status = getUserProfileStatus($user->uid);
  if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
  }else{			
	  // Get the currently logged in user object.
	  $form['#account'] = $GLOBALS['user'];
	  
	  $form['#attributes']['class'][] = 'form-vertical';
		
	  $form['form_begin'] = array(
			'#type' => 'markup',
			'#markup' => '<div class="row">',
			'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Change Password</h4></div><div class="widget-main">',
		);
	
	  // Textfield cor current password confirmation.
	  $form['current_pass'] = array(
		'#type' => 'password',
		'#title' => t('Current password'),
		'#size' => 25,
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control')),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	  );
	
	  // Password confirm field.
	  $form['account']['pass'] = array(
		'#type' => 'password_confirm',
		'#size' => 25,
		//'#title' => t('New'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control')),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	  );
	
	  $form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
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
}

/**
 * Validate handler for change_password_form().
 */
function passchng_render_user_pass_change_form_validate(&$form, &$form_state) {  
  // Make sure the password functions are present.
  require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');

  // Make sure the provided current password is valid for this account.
  if (!user_check_password($form_state['values']['current_pass'], $form['#account'])) {
    form_set_error('current_pass', t('The current password you provided is incorrect.'));
  }
  
  if(trim($form_state['values']['current_pass'])==trim($form_state['values']['pass'])){
	  form_set_error('pass', t('The new password you provided must not be same as previous.'));
  }
  
}

 /**
 * Submit handler for change_password_form().
 */
function passchng_render_user_pass_change_form_submit(&$form, &$form_state) {
  // Set up the edit array to pass to user_save()
  $edit = array('pass' => $form_state['values']['pass']);

  // Save the account with the new password.
  user_save($form['#account'], $edit);

  // Inform the user.
  drupal_set_message(t('Your password has been changed.'));
}

/*function passchng_render_user_pass_change_form() {

    global $user;

    if (!user_is_logged_in()) {
        drupal_access_denied();
    }
	

    module_load_include('inc', 'user', 'user.pages');
    $form = drupal_get_form('user_profile_form', $user);

    $request_new = l(t('Request new password'), 'user/password', array('attributes' => array('title' => t('Request new password via e-mail.'))));
    //$current_pass_description = t('Enter your current password to change the %pass. !request_new.', array('%pass' => t('Password'), '!request_new' => $request_new));
	$current_pass_description = t('Enter your current password to change the password.');
    $form['account']['current_pass']['#description'] = $current_pass_description;    
	#krumo($form);
	
	
	
	$form['#attributes']['class'][] = 'form-vertical';
	$form['account']['current_pass']['#attributes'] = array('class'=>array('form-control'));
    unset(
      $form['account']['name'],
      $form['account']['mail'],
      $form['account']['status'],
      $form['account']['roles'],
      $form['locale'],
      $form['l10n_client'],
      $form['picture'],
      $form['overlay_control'],
      $form['contact'],
      $form['timezone'],
      $form['ckeditor'],
      $form['metatags'],
      $form['redirect'],
	  $form['user_designation']
      );

    return $form;
}*/

function employee_profile_form($form, &$form_state){
	global $user,$base_root,$base_path;
	
	$query = db_select('users', 'u');
  	$query->leftJoin('a_user_details', 'ud', 'u.uid = ud.uid');  
	$query->fields('u', array('mail'));
	$query->fields('ud', array('fname','mobile','gender','address','one_time_pass_flag'));
	$query->condition('u.uid', $user->uid, '=');
	$result = $query->execute();
	$userData = $result->fetchAssoc();
	
	
	$form['#attributes']['class'][] = 'form-vertical';
    $form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Update Profile</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	$form['fname'] = array(
		'#type' => 'textfield',
		'#title' => t('Enter Your Full Name'),
		'#required' => TRUE,
		'#default_value' => !empty($userData['fname']) ? $userData['fname'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Your Full Name'),
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	 );
	 $form['mobile'] = array(
	   '#title'=>t('Enter Your Mobile No'),
	   '#type' => 'textfield',
	   '#required' => TRUE,
	   '#default_value' => !empty($userData['mobile']) ? $userData['mobile'] : '',
	   '#maxlength' => 12,
	   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Mobile Number', 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-3">',
	   '#suffix' => '</div>'
	);
	$form['email'] = array(
	   '#title'=>t('Enter Your Email ID'),
	   '#type' => 'textfield',
	   '#required' => TRUE,
	   '#default_value' => !empty($userData['mail']) ? $userData['mail'] : '',
	   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Email', 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-3">',
	   '#suffix' => '</div>'
	);	
	$form['gender'] = array(
		'#title' => t('Gender'),
	   	'#type' => 'select',
		'#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Select Gender', 'autocomplete' => 'off'),
		'#options' => array(''=>t('Select Gender'), '1'=>t('Male'),'2'=>t('Female'),'3'=>t('3rd Gender')),
		'#default_value' => !empty($userData['gender']) ? $userData['gender'] : '',
		'#required' => TRUE,
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	  ); 
	$form['address'] = array( 
	   '#title'=>t('Enter Your Address'),
	   '#rows'=> 3,
	   '#type' => 'textarea',
	   '#required' => TRUE,
	   '#default_value'=>!empty($userData['address']) ? $userData['address'] : '',
	   '#attributes' => array('id' => 'address', 'autocomplete' => 'off', 'class'=>array('form-control'),'placeholder'=>'Address'),
	   '#prefix' => '<div class="col-md-12">',
	   '#suffix' => '</div>'
	);	
	
	if($userData['one_time_pass_flag']==0){
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
	}
	$form['submit'] = array(
    	'#type' => 'submit',
		'#value' => 'Update',
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
	
	$userDataValidate = array();
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

	}
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
 	
	$query = db_update('a_user_details');
	$query->fields(array('fname'			=> $form_state['values']['fname'],
						'mobile'			=> $form_state['values']['mobile'],
						'gender'			=> $form_state['values']['gender'],
						'address'			=> $form_state['values']['address'],
						));
	$query->condition('uid', $user->uid);
	$rs = $query->execute();
	
	if($rs){
		if($userDataSubmit['one_time_pass_flag']==0){
			$edit = array('pass' => $form_state['values']['pass'],'mail' => $form_state['values']['email']);
			user_save($form['#account'], $edit);
			
			$query = db_update('a_user_details');
			$query->fields(array('one_time_pass_flag'=> 1));
			$query->condition('uid', $user->uid);
			$query->execute();
		}
		
		drupal_set_message(t('Your profile has been updated successfully.'));
		if(in_array('asset', $user->roles)){
			drupal_goto('propertyuser-dashboard');
		}
	}else{
		drupal_set_message(t('Your profile is not updated. Please update your profile first.'));
	}
	
}

function user_details_form_entry($form, &$form_state){
	global $user;
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Add New User</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	$form['fname'] = array(
		'#type' => 'textfield',
		'#title' => t('Enter Full Name'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Full Name'),
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

function acknowledgement_received_form($form, &$form_state){
	global $user;
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Acknowledgement Received</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	$form['fname'] = array(
		'#type' => 'textfield',
		'#autocomplete_path' => 'getassetuser/autocomplete',
		'#ajax' => array('event' => 'blur',
                      'callback' => '_reload_mem_order_list',
                      //'wrapper' => 'dropdown_product_cat',
                      'effect' => 'fade',
                      'progress' => array('type' => '','message' => '',),
                   ),
		'#title' => t('Enter Full Name'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Full Name'),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	 ); 
	$form['uid'] = array(
		'#type' => 'textfield',
		'#title' => t('User Id'),
		//'#id' =>'order_no_map',
		'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('doc_name_clear','form-control'),'placeholder'=>'User Id'),
		'#prefix' => '<div id="order_no_map"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	$form['designation'] = array(
		'#type' => 'textfield',
		'#title' => t('Designation'),
		'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
		'#prefix' => '<div id="designation_map"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 ); 
	$form['district'] = array(
		'#type' => 'textfield',
		'#title' => t('District'),
		'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'District'),
		'#prefix' => '<div id="district_map"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	$form['directorate'] = array(
		'#type' => 'textfield',
		'#title' => t('Directorate'),
		'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Directorate'),
		'#prefix' => '<div id="directorate_map"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );    
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	return $form; 
}
function get_asset_user($string=''){
	
	$matches = array();
	$query = db_select('users', 'u');
	$query->leftJoin('users_roles', 'ur', 'u.uid = ur.uid');  
	$query->leftJoin('role', 'r', 'ur.rid = r.rid'); 
	$query->leftJoin('a_user_details', 'ud', 'u.uid = ud.uid');
	
	$query->leftJoin('a_user_details_service', 'us', 'u.uid = us.uid'); 
	$query->fields('us', array('designation','district_code','directorate_code')); 
	
	//$query->fields('ur', array('uid')); 
	$query->fields('u', array('uid','name','access','created','status'));
	$query->fields('ud', array('fname'));
	$query->addField('r', 'name', 'rolename');
	$query->condition('ud.fname', '%' . trim($string) . '%', 'LIKE');
	$query->orderBy("r.name", "ASC");
	$result = $query->execute();
	//$rsData = $result->fetchAll();
	

    // save the query to matches
    foreach ($result as $row) {
	  $matches[$row->fname."-".$row->uid] = check_plain($row->fname."-".$row->designation);
    }
	
    // Return the result to the form in json
    drupal_json_output($matches);
}

function getUserInfoByUid($uid){
	$query = db_select('users', 'u');
	//$query->leftJoin('users_roles', 'ur', 'u.uid = ur.uid');  
	//$query->leftJoin('role', 'r', 'ur.rid = r.rid'); 
	$query->leftJoin('a_user_details', 'ud', 'u.uid = ud.uid');
	
	$query->leftJoin('a_user_details_service', 'us', 'u.uid = us.uid'); 
	$query->fields('us', array('designation','district_code','directorate_code'));
	
	$query->leftJoin('a_directorate_mst', 'd', 'd.directorate_code = us.directorate_code'); 
	$query->fields('d', array('directorate_name')); 
	
	$query->leftJoin('district_master', 'dis', 'dis.district_code = us.district_code'); 
	$query->fields('dis', array('district_name')); 
	
	//$query->fields('ur', array('uid')); 
	$query->fields('u', array('uid','name','access','created','status'));
	$query->fields('ud', array('fname'));
	//$query->addField('r', 'name', 'rolename');
	$query->condition('u.uid', $uid, '=');
	$result = $query->execute();
	$userData = $result->fetchAssoc();
	return $userData;
}

function _reload_mem_order_list($form, $form_state) {
 $commands   = array();
 //echo $form_state['values']['fname']; exit;
 $user_arr = explode('-',$form_state['values']['fname']);
 $mydata = getUserInfoByUid($user_arr[1]);
 //print_r($mydata);
 
 $form['uid']['#value'] = $user_arr[1];
 $form['designation']['#value'] = $mydata['designation'];
 $form['directorate']['#value'] = $mydata['directorate_code'];
 $form['district']['#value'] = $mydata['district_code'];
  
 //$commands[] = ajax_command_invoke('.doc_name_clear', 'val', array($form['values']['fname']));
 $commands[] = ajax_command_replace('#order_no_map', '<div id="order_no_map">'.drupal_render($form['uid']).'</div>');
 $commands[] = ajax_command_replace('#designation_map', '<div id="designation_map">'.drupal_render($form['designation']).'</div>');
 $commands[] = ajax_command_replace('#directorate_map', '<div id="directorate_map">'.drupal_render($form['directorate']).'</div>');
 $commands[] = ajax_command_replace('#district_map', '<div id="district_map">'.drupal_render($form['district']).'</div>');
//print_r($commands);
 return array('#type' => 'ajax', '#commands' => $commands);
}