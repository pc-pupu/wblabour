<?php
function user_list_by_nodal(){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	$user_info = getAllUidInfoFromPid($user->uid);
	//print_r($user_info); exit;
	
	
	$output = '';
	$header = array(
				array('data'=> 'HRMS ID'),
				array('data'=> 'Name'),
				array('data'=> 'Role'),
				array('data'=> 'Office Name'),
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
	$roles[] = 'assetadmin';
	$roles[] = 'nodal';
	
	
	
	
	$query = db_select('users', 'u');
	$query->leftJoin('users_roles', 'ur', 'u.uid = ur.uid');  
	$query->leftJoin('role', 'r', 'ur.rid = r.rid'); 
	$query->leftJoin('a_user_details', 'ud', 'u.uid = ud.uid');
	$query->leftJoin('a_user_details_service', 'us', 'u.uid = us.uid');
	$query->leftJoin('a_office_master', 'o', 'us.office_id = o.office_id');
	$query->fields('u', array('uid','name','access','created','status'));
	$query->fields('o', array('office_name'));
	$query->fields('ud', array('fname'));
  	$query->addField('r', 'name', 'rolename');
	$query->condition('us.directorate_code', $user_info['directorate_code'], '=');
	//$query->condition('us.district_code', $user_info['district_code'], '=');
	$query->condition('us.office_id', '0', '!=');
	$query->condition('r.name', $roles, 'NOT IN');
	
  	$query->orderBy("r.name", "ASC");
  	$result = $query->execute();
  	$rsData = $result->fetchAll();
	
	//print_r($rsData); exit;
	
	foreach($rsData as $record=>$val) {
		
		$userEdit = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/edit.png">'), 'profile-edit/edit/'
		       .$val->uid, array('html' => TRUE,'attributes'=>array('title' => 'Edit')));
			   
		if($val->status == 1){
			 $status = 'Active';
		 }else{
			 $status = 'Blocked';
		 }
		$rows[] = array(
					array('data' => $val->name),
					array('data' => $val->fname),
					array('data' => $val->rolename),
					array('data' => $val->office_name),
					array('data' => $status),
					array('data' => format_date($val->access, 'custom', 'd-m-Y H:i:s')),
					array('data' => format_date($val->created, 'custom', 'd-m-Y H:i:s')),
					array('data' => $userEdit ), 
		);
  }
  
   $output .= theme('datatable', array(
        'header' => $header,
        'rows' => $rows,
        'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
        'sticky' => true,
        'caption' => '<h3>List of User </h3>',
        'colgroups' => array(),
        'empty' => t("No data found!") // The message to be displayed if table is empty
      )
    ).theme('pager');
  
/*  $output = theme_table(
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '<h3>List of User</h3>',
      'colgroups' => array(),
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
*/
  // Returning the output
  return '<div class="formdvider viewlist">'.$output.'</div>';		
}

function profile_edit_by_nodal($form, &$form_state, $args='') {
	
	global $user,$base_root,$base_path;
		
	$query = db_select('a_user_details', 'aud');
	$query->leftJoin('a_user_details_service', 'auds', 'aud.uid = auds.uid');  
	$query->fields('aud', array('uid','hrms_id','fname','mobile','email'));
	$query->fields('auds', array('designation','district_code','office_id','subdivision','service_status'));
	$query->condition('service_status',1,'=');
	$query->condition('aud.uid',$args,'=');
  	$result1 = $query->execute();
  	$result = $result1->fetchAssoc();
	
	$form['#attributes']['class'][] = 'form-vertical';
    $form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Update Profile By Nodal Officer</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
	 $form['uid'] = array(
		'#type' => 'hidden',
		'#title' => t('UID'),
		'#required' => TRUE,
		'#default_value' => isset($result['uid']) ? $result['uid'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'UID','readonly'=>'readonly'),
		/*'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'*/
	 );
	 
	$form['hrms_id'] = array(
		'#type' => 'textfield',
		'#title' => t('HRMS ID'),
		'#required' => TRUE,
		'#default_value' => isset($result['hrms_id']) ? $result['hrms_id'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'HRMS ID','readonly'=>'readonly'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	 ); 
	 
	 $form['fname'] = array(
		'#type' => 'textfield',
		'#title' => t('Full Name'),
		'#required' => TRUE,
		'#default_value' => isset($result['fname']) ? $result['fname'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Full Name','readonly'=>'readonly'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	 );
	 
	 $form['mobile'] = array(
	   '#title'=>t('Mobile No'),
	   '#type' => 'textfield',
	   '#required' => TRUE,
	   '#default_value' => isset($result['mobile']) ? $result['mobile'] : '',
	   '#maxlength' => 10,
	   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Mobile Number', 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-4">',
	   '#suffix' => '</div>'
	);
	
	 $form['email'] = array(
	   '#title'=>t('Email Id'),
	   '#type' => 'textfield',
	   '#required' => TRUE,
	   '#default_value' => isset($result['email']) ? $result['email'] : '',
	   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Email Id', 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-4">',
	   '#suffix' => '</div>'
	);
	
	 $form['designation'] = array(
	   '#title'=>t('Designation'),
	   '#type' => 'textfield',
	   '#required' => TRUE,
	   '#default_value' => isset($result['designation']) ? $result['designation'] : '',
	   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Designation', 'autocomplete' => 'off'),
	   '#prefix' => '<div class="col-md-4">',
	   '#suffix' => '</div>'
	);
	
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
 
function profile_edit_by_nodal_submit($form, &$form_state) {
	
	global $user,$base_root,$base_path;
	
	    $query = db_update('a_user_details');
		$query->fields(array('mobile' => $form_state['values']['mobile'],
							 'email'  => $form_state['values']['email'],
							));
		$query->condition('uid', $form_state['values']['uid']);
		$rs = $query->execute();
		
		$query = db_update('a_user_details_service');
		$query->fields(array('designation' => $form_state['values']['designation'],
							 
							));
		$query->condition('uid', $form_state['values']['uid']);
		$rs = $query->execute();
		
		send_sms($form_state['values']['mobile'],'Dear, '.$form_state['values']['fname'].' your mobile number has been updated successfully in Labour Department\'s Declaration of Asset Management System');
		send_sms($form_state['values']['email'],'Dear, '.$form_state['values']['fname'].' your email id has been updated successfully in Labour Department\'s Declaration of Asset Management System');
		send_sms($form_state['values']['designation'],'Dear, '.$form_state['values']['fname'].' your designation has been updated successfully in Labour Department\'s Declaration of Asset Management System');
		
		drupal_set_message(t('Your profile has been updated successfully.'));
		drupal_goto('listuserbynodal');
		
		
}

 
function asset_office_list(){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');	
	
	$user_info = getAllUidInfoFromPid($user->uid);
	
	$query = db_select('a_office_master','o');
	$query->fields('o', array('office_id','office_name','directorate_code','district_code')); 
	$query->condition('o.directorate_code', $user_info['directorate_code'], '=');
	$query->condition('o.district_code', $user_info['district_code'], '=');
	// $query->orderBy('dm.id','ASC');
	$result = $query->execute();
	$rsData = $result->fetchAll();
	
	$header = array();
	$rows   = array();
	$output = '';
	
	
	
	$header = array(  
	  array('data' => t('<b>Sl No </b>')),	
	  array('data' => t('<b>Office Name </b>')),	
	  //array('data' => t('<b>Office Address  </b>')),
	);
	 $i=1;
	  foreach($rsData as $data){
		//$i++;
		
		
		$rows[] = array( 
		  $i++,	
		  array('data' => t($data->office_name)),	
		  //array('data' => t($data->office_address)),
		);
	  }
	
	
	 $output = theme_table(
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '<h3>Office List </h3>',
      'colgroups' => array(),
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');

 return '<div class="formdvider viewlist">'.$output.'</div>';	
}

function add_office($form, &$form_state){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	$directorate_list = getDirectorateListByRoleId($user->uid);
	$district_list = getDistrictListByRoleId($user->uid);
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Add Field Office</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 $form['directorate_code'] = array(
	  '#title' => t('Select Directorate'),	
	  '#type' => 'select',
	  '#required' => TRUE,
	  '#options' => $directorate_list,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
    );
	$form['district_code'] = array(
	  '#title' => t('Select District'),	
	  '#type' => 'select',
	  '#required' => TRUE,
	  '#options' => $district_list,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
    );
	$form['office_name'] = array(
	  '#type'=>'textfield',
	  '#title' => t('Office Name'),
	  '#default_value'=>array(0=>""),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Office Name'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);
	/*$form['office_address'] = array(
	  '#type'=>'textarea',
	  '#title' => t('Office Address'),
	  '#default_value'=>array(0=>""),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Office Address'),
	  '#prefix' => '<div class="col-md-12">',
	  '#suffix' => '</div>'
	);*/
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

function add_office_submit($form, &$form_state){
	$officerInfo		=	array(		
										'office_name'			=>  $form_state['values']['office_name'],
										'directorate_code'		=> 	$form_state['values']['directorate_code'],
										'district_code'			=>  $form_state['values']['district_code'],
										//'office_address'		=>	trim($form_state['values']['office_address']),
								);
   $id = db_insert('a_office_master')->fields($officerInfo)->execute();
   if($id){
		drupal_set_message('Office has been successfully created');
		drupal_goto('office-list');
	}else{
		drupal_set_message('There is some problem. Please try after sometime');
		drupal_goto('add-office');
	}
}




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
				//array('data'=> 'Action')
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
	 
	 if($val->access == 0){
		$access = 'Never' ; 
	  }else{
		$access = format_date($val->access, 'custom', 'd-m-Y H:i:s'); 
	  }
	  
	  $rows[] = array(
					array('data' => $val->name),
					array('data' => $val->rolename),
					//array('data' => $project_name),
					array('data' => $status),
					array('data' => $access),
					array('data' => format_date($val->created, 'custom', 'd-m-Y H:i:s')),
					//array('data' => $viewLink.' '.$delLink)
		);
  }
  
   $output .= theme('datatable', array(
        'header' => $header,
        'rows' => $rows,
        'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
        'sticky' => true,
        'caption' => '',
        'colgroups' => array(),
        'empty' => t("No data found!") // The message to be displayed if table is empty
      )
    ).theme('pager');
  
 /* $output = theme_table(
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '',
      'colgroups' => array(),
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');*/

  // Returning the output
  return '<div class="formdvider viewlist">'.$output.'</div>';		

}


function acknowledgement_received_form($form, &$form_state){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Receive Asset Declaration</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	$form['decission'] = array(
		'#type' => 'hidden',
		'#title' => t('Decission'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Decission'),
		'#prefix' => '<div id="decission_map"><div class="col-md-3">',
		'#suffix' => '</div></div>'
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
		'#title' => t('Enter Officers Name'),
		'#description'=>t('Please type and select auto fetch data from mouse click, Do not use tab key from keyboard'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Officers Name'),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	 ); 
	$form['uid'] = array(
		'#type' => 'hidden',
		'#title' => t('User Id'),
		//'#id' =>'order_no_map',
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('doc_name_clear','form-control'),'placeholder'=>'User Id'),
		'#prefix' => '<div id="order_no_map"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	$form['designation'] = array(
		'#type' => 'hidden',
		'#title' => t('Designation'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
		'#prefix' => '<div id="designation_map"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 ); 
	$form['district'] = array(
		'#type' => 'hidden',
		'#title' => t('District'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'District'),
		'#prefix' => '<div id="district_map"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	$form['directorate'] = array(
		'#type' => 'hidden',
		'#title' => t('Directorate'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Directorate'),
		'#prefix' => '<div id="directorate_map"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );  
	 $form['fetch_data'] = array(
		'#prefix' => '<div id="fetch_data_map"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );
	 
	 /*$form['submit_btn'] = array(
		'#prefix' => '<div id="fetch_data_map_submit"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );*/
	  $form['submit'] = array (
        '#type' => 'submit',
        '#value' => 'Accept',
		//'#attributes' => array('class'=>array('btn btn-primary')),
		/*'#prefix' => '<div class="col-md-12">',  
        '#suffix' => '</div>',*/
		//'#attributes' => array('class'=>array('btn btn-success pull-left'),'onclick' => 'this.form.target="_blank";return true;'),
		'#attributes' => array('class'=>array('btn btn-success pull-left')),
		'#prefix' => '<div id="frmbtn" style="display:none"><div class="col-md-3">',
  		'#suffix' => '</div></div>',
     ); 
	 
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	return $form; 
}

function getUserData($userinfoarr){
	$user_arr = explode('-',$form_state['values']['fname']);
 	$mydata = getUserInfoByUid($user_arr[1]);
	return $mydata['directorate_code'];
}

function acknowledgement_received_form_submit($form, &$form_state){ 
	global $user;
	if(trim($form_state['values']['decission']=='INSERT')){
	$officerInfo		=	array(
										'uid'						=> 	$form_state['values']['uid'],
										'declaration_yr'			=>	date('Y'),
										'designation'				=>  $form_state['values']['designation'],
										'directorate_code'			=>  $form_state['values']['directorate'],
										'district_code'				=>	!empty($form_state['values']['district'])?trim($form_state['values']['district']):'',
										'document_no'  				=>  '',
										'created_date' 			 	=>  date('Y-m-d H:i:s'), 
										'status'  					=>  '1',
										'operator_uid'  			=>  $user->uid,
								);
   

   db_insert('a_asset_mst')->fields($officerInfo)->execute();
	}else if(trim($form_state['values']['decission']=='UPDATE')){
		
		$query = db_update('a_asset_mst');
		$query->fields(array('created_date' =>  date('Y-m-d H:i:s'), 'status'  =>  '1', 'operator_uid'  =>  $user->uid));
		$query->condition('uid', trim($form_state['values']['uid']), '=');
		$query->condition('declaration_yr', date('Y'), '=');
		$rs = $query->execute();
	}
   
   $user_info = getLoginUserDetailForAsset($form_state['values']['uid']);
   
  	if($form_state['values']['directorate'] == 'DB'){
		$directorate_name = 'Directorate of Boilers';
	}elseif($form_state['values']['directorate'] == 'LC'){
		$directorate_name = 'Labour Commissionerate';
	}elseif($form_state['values']['directorate'] == 'DE'){
		$directorate_name = 'Directorate of Employment';
	}elseif($form_state['values']['directorate'] == 'DF'){
		$directorate_name = 'Directorate of Factories';
	}elseif($form_state['values']['directorate'] == 'ESI'){
		$directorate_name = 'Directorate of ESI (MB) Scheme';
	}elseif($form_state['values']['directorate'] == 'LWB'){
		$directorate_name = 'Labour Welfare Board';
	}elseif($form_state['values']['directorate'] == 'DEC'){
		$directorate_name = 'Directorate of Employees Compensation';
	}elseif($form_state['values']['directorate'] == 'DIT'){
		$directorate_name = 'Directorate of Industrial Tribunal';
	}elseif($form_state['values']['directorate'] == 'LD'){
		$directorate_name = 'Labour Department';
	}
   
   send_sms($user_info['mobile'],'Your Asset Statement for the year '.date('Y').' has been received by the '.$directorate_name.'. To check your status and download the asset acknowledgement please login into your account https://wblabour.gov.in/assetlogin');
   
   drupal_set_message('Application for officer '.$form_state['values']['fname'].' has been successfully accepted. '.l('<strong> Print Acknowlwdgement</strong>','acknowledgement-print/'.$form_state['values']['uid'].'/'.date('Y'), array('html' => TRUE,'attributes'=>array('target'=>'_blank'))));
   //drupal_goto('acknowledgement-print');
}

function get_asset_user_backlog($string=''){
	
	global $user;
	
	$direc_code = getLoginUserDetailForAsset($user->uid);  
	
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
	if($user->uid != 1486){
		$query->condition('us.directorate_code',$direc_code['directorate_code'],'=');
	}
	
	if(in_array(variable_get('field', 11), array_keys($user->roles))){
		$query->condition('us.emp_group','A','!=');
		$query->condition('us.office_id',$direc_code['office_id'],'=');
	}
	
	$query->condition('ud.status',0,'=');
	$query->orderBy("r.name", "ASC");
	$query->range(0,10);
	$result = $query->execute();
	//$rsData = $result->fetchAll();
	

    // save the query to matches
    foreach ($result as $row) {
	  $matches[$row->fname."-".$row->uid] = check_plain($row->fname."-".$row->designation);
    }
	
    // Return the result to the form in json
    drupal_json_output($matches);
}



function get_asset_user($string=''){
	
	global $user;
	
	$direc_code = getLoginUserDetailForAsset($user->uid);  
	
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
	$query->condition('us.directorate_code',$direc_code['directorate_code'],'=');
	
	if(in_array(variable_get('field', 11), array_keys($user->roles))){
		$query->condition('us.emp_group','A','!=');
		$query->condition('us.office_id',$direc_code['office_id'],'=');
	}
	
	$query->condition('ud.status',0,'=');
	$query->orderBy("r.name", "ASC");
	$query->range(0,10);
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
	$query->fields('ud', array('fname','hrms_id'));
	//$query->addField('r', 'name', 'rolename');
	$query->condition('u.uid', $uid, '=');
	$result = $query->execute();
	$userData = $result->fetchAssoc();
	return $userData;
}

function getVerifyByUidYear($uid,$currentYear){
  $rsData = array();	
  $query = db_select('a_asset_mst','am');
  $query->fields('am', array('uid','declaration_yr','designation','directorate_code','status','created_date'));
  $query->condition('am.uid', $uid, '=');
  $query->condition('am.declaration_yr', $currentYear, '=');
  $result = $query->execute();
  $rsData = $result->fetchAssoc();
  return $rsData;
}

function _reload_mem_order_list($form, $form_state) {
 drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
 $commands   = array();
 //echo $form_state['values']['fname']; exit;
 $user_arr = explode('-',$form_state['values']['fname']);
 
 $verify = getVerifyByUidYear($user_arr[1],date('Y'));
 
	$header = array();
	$rows   = array();
	
	$header = array(  
	  array('data' => t('Employee Information'),'colspan' => 5),  
	);
 
 if(!empty($verify) && $verify['status']==1){
	 
	 $rows[] = array( 
	  array('data' => t('You have already submitted asset for this year'),'colspan' => 5),
	);
	 
	 $rows[] = array( 
	  array('data' => l('<strong class="btn btn-danger print-btn"> Print Acknowlwdgement</strong>','acknowledgement-print/'.$user_arr[1].'/'.$verify['declaration_yr'], array('html' => TRUE,'attributes'=>array('target'=>'_blank'))) ,'colspan' => 5),
	);
	 
	
 }else{
	 $mydata = array();
	 $mydata = getUserInfoByUid($user_arr[1]);
 
	 $form['uid']['#value'] = $user_arr[1];
	 $form['designation']['#value'] = $mydata['designation'];
	 $form['directorate']['#value'] = $mydata['directorate_code'];
	 $form['district']['#value'] = $mydata['district_code'];
	 if(!empty($verify) && $verify['status']==0){
		 $form['decission']['#value'] = 'UPDATE';
	 }else{
		 $form['decission']['#value'] = 'INSERT';
	 }
	 
	 
	 
		
	
	$rows[] = array(  
	  array('data' => t('<b>HRMS ID  </b>')),
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	  array('data' => t('<b>Directorate Name  </b>')),
	  array('data' => t('<b>District Name  </b>')),
	);
	if($mydata['hrms_id']!=""){
		$rows[] = array( 
		  array('data' => t($mydata['hrms_id'])),	
		  array('data' => t($mydata['fname'])),
		  array('data' => t($mydata['designation'])), 	 
		  array('data' => t($mydata['directorate_name'])), 
		  array('data' => t($mydata['district_name'])),
		);
	}else{
		$rows[] = array( 
		  array('data' => t('No Data Found'), 'colspan'=>5),	
		);
	}
 }
	
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => ' ',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
 //$commands[] = ajax_command_invoke('.doc_name_clear', 'val', array($form['values']['fname']));
 $commands[] = ajax_command_replace('#order_no_map', '<div id="order_no_map">'.drupal_render($form['uid']).'</div>');
 $commands[] = ajax_command_replace('#designation_map', '<div id="designation_map">'.drupal_render($form['designation']).'</div>');
 $commands[] = ajax_command_replace('#directorate_map', '<div id="directorate_map">'.drupal_render($form['directorate']).'</div>');
 $commands[] = ajax_command_replace('#district_map', '<div id="district_map">'.drupal_render($form['district']).'</div>');
 $commands[] = ajax_command_replace('#fetch_data_map', '<div id="fetch_data_map"><div class="col-md-12">'.$output.'</div></div>');
 $commands[] = ajax_command_replace('#decission_map', '<div id="decission_map">'.drupal_render($form['decission']).'</div>');
//print_r($commands);
 if(!empty($verify) && $verify['status']==1){
	$commands[] = ajax_command_invoke('#frmbtn', 'hide');
 }elseif($mydata['hrms_id']==""){
	$commands[] = ajax_command_invoke('#frmbtn', 'hide'); 
 }else{
 	$commands[] = ajax_command_invoke('#frmbtn', 'show');
 }
 
 return array('#type' => 'ajax', '#commands' => $commands);
}

function asset_received_list(){
  global $user;
  $status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
  	
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');

	
 $direc_code = getLoginUserDetailForAsset($user->uid);  
	
  $query = db_select('a_asset_mst','am');
  $query->leftJoin('users', 'u', 'u.uid = am.uid');  
  $query->leftJoin('a_user_details', 'ud', 'ud.uid = am.uid');  
  $query->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code');  
  $query->leftJoin('a_user_details_service', 'us', 'am.uid = us.uid'); 
  $query->fields('am', array('uid','declaration_yr','designation','directorate_code','status','created_date'));
  $query->fields('u', array('name','access','created'));
  $query->fields('ud', array('fname','status'));
  $query->fields('dm', array('id','directorate_name'));
  $query->fields('us', array('designation','district_code','directorate_code')); 
  if(in_array(variable_get('field', 11), array_keys($user->roles))){
		$query->condition('us.emp_group','A','!=');
		$query->condition('us.office_id',$direc_code['office_id'],'=');
	}
  $query->condition('am.status',1,'=');
  $query->condition('us.directorate_code',$direc_code['directorate_code'],'=');
  $query->condition('ud.status',0,'=');
 // $query->orderBy('dm.id','ASC');
  //$query1 = $query->extend('TableSort')->extend('PagerDefault')->limit(20);
  //$result = $query1->execute();
  $result = $query->execute();
  $rsData = $result->fetchAll();
	
	$header = array();
	$rows   = array();
	$output = '';
	
	
	
	$header = array(  
	  array('data' => t('<b>Sl No. </b>')),		
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	  //array('data' => t('<b>Directorate Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	);
	 $i=0;
	  foreach($rsData as $data){
		$i++;
		if($data->status == 1){
			$status = "Submitted";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		
		
		
		$rows[] = array( 
		  $i,	
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t($data->designation)), 	 
		  //array('data' => t($data->directorate_name)), 
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }
	  
   $output .= theme('datatable', array(
							  'header' => $header,
							  'rows' => $rows,
							  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
							  'sticky' => true,
							  'caption' => '<h3>DoA Received List </h3>',
							  'colgroups' => array(),
							  'empty' => t("No data found!") // The message to be displayed if table is empty
							)
						  ).theme('pager');	  
	
	
	/* $output = theme_table(
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '<h3>DoA Received List </h3>',
      'colgroups' => array(),
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');*/

 return '<div class="formdvider viewlist">'.$output.'</div>';	
	  
 }
 
 
 
 function asset_pending_list(){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}  
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
  
	
  $direc_code = getLoginUserDetailForAsset($user->uid);
  /*$q1 = db_select('a_asset_mst','am');
  $q1->fields('am', array('uid'));
  $q1->condition('am.status','1','=');*/
  
  $querypending = db_select('a_user_details','ud');
  $querypending->leftJoin('a_asset_mst', 'am', 'am.uid = ud.uid');   
  $querypending->leftJoin('users', 'u', 'u.uid = ud.uid');  
  $querypending->leftJoin('a_user_details_service', 'uds', 'uds.uid = ud.uid');  
  $querypending->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = uds.directorate_code');  
  $querypending->fields('ud', array('fname','uid'));
  $querypending->fields('u', array('name','access','created'));
  $querypending->fields('am', array('uid','declaration_yr','directorate_code','status','created_date'));
  $querypending->fields('uds', array('designation'));
  $querypending->fields('dm', array('id','directorate_name'));
  if(in_array(variable_get('field', 11), array_keys($user->roles))){
		$querypending->condition('uds.emp_group','A','!=');
		$querypending->condition('uds.office_id',$direc_code['office_id'],'=');
	}
  $querypending->condition('am.status',0,'=');
  $querypending->condition('uds.directorate_code',$direc_code['directorate_code'],'=');
  //$querypending->condition('ud.uid',$q1,'NOT IN');
  $querypending->orderBy('dm.id','ASC');
  //$queryfinal = $querypending->extend('TableSort')->extend('PagerDefault')->limit(20);
  //$result1 = $queryfinal->execute();
  $result1 = $querypending->execute();
  $pendingData = $result1->fetchAll(); 
  
	$header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Sl No. </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	 // array('data' => t('<b>Directorate Name </b>')),
	  //array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  //array('data' => t('<b>View </b>')),
	);
	 $i=0;
	  foreach($pendingData as $data){
		$i++;
		if($data->status == 1){
			$status = "Submitted";
			//$link = l('ACKNOWLEDGEMENT','acknowledgement-print/'.$data->uid, array('html' => TRUE,'attributes'=>array('target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			//$link = "";
		}
		
		$rows[] = array( 
		  $i,	
		  array('data' => t($data->fname)),
		  array('data' => t($data->designation)), 	 
		  //array('data' => t($data->directorate_name)), 
		  //array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		 // array('data' => t($link)),
		);
	  }
	  
	  
   $output .= theme('datatable', array(
							  'header' => $header,
							  'rows' => $rows,
							  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
							  'sticky' => true,
							  'caption' => '<h3>DoA Pending List </h3>',
							  'colgroups' => array(),
							  'empty' => t("No data found!") // The message to be displayed if table is empty
							)
						  ).theme('pager');	  
	
	
	/* $output = theme_table(
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '<h3>DoA Pending List </h3>',
      'colgroups' => array(),
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');*/

 return '<div class="formdvider viewlist">'.$output.'</div>';	
	  
 }
 
 function nodal_officer_list() {
  global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}	
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  $direc_code = getLoginUserDetailForAsset($user->uid);
	 
  /*$querynodal = db_select('a_asset_mst','am');
  $querynodal->leftJoin('users', 'u', 'u.uid = am.uid');  
  $querynodal->leftJoin('a_user_details', 'ud', 'ud.uid = am.uid');  
  $querynodal->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code');  
  $querynodal->leftJoin('a_user_details_service', 'uds', 'am.uid = uds.uid');  
  $querynodal->fields('am', array('uid','declaration_yr','designation','directorate_code','status','created_date'));
  $querynodal->fields('u', array('name','access','created'));
  $querynodal->fields('ud', array('fname'));
  $querynodal->fields('dm', array('id','directorate_name'));
   if(in_array(variable_get('field', 11), array_keys($user->roles))){
		$querynodal->condition('uds.emp_group','A','!=');
		$querynodal->condition('uds.office_id',$direc_code['office_id'],'=');
	}
  $querynodal->condition('uds.directorate_code',$direc_code['directorate_code'],'=');
 // $query->orderBy('dm.id','ASC');
  //$querynodal = $query->extend('TableSort')->extend('PagerDefault')->limit(20);
  $result1 = $querynodal->execute();
  $querynodalfinal = $result1->fetchAll();*/
  
  $querynodal = db_select('a_user_details','ud');
	$querynodal->leftJoin('a_user_details_service', 'us', 'ud.uid = us.uid');
	$querynodal->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = us.directorate_code'); 
	$querynodal->fields('ud', array('uid','fname','status'));
	$querynodal->fields('dm', array('id','directorate_name'));
	$querynodal->fields('us', array('designation','directorate_code','district_code','service_status','emp_group','office_id'));
	$querynodal->condition('ud.status',0,'=');
	$querynodal->condition('us.service_status',1,'=');
	//$query->condition('us.directorate_code',$direc_code['directorate_code'],'=');
	//$query->condition('us.office_id',$fdata->office_id,'=');
	//$query->condition('us.emp_group',array('B','C'),'IN');
	if(in_array(variable_get('field', 11), array_keys($user->roles))){
		$querynodal->condition('us.emp_group','A','!=');
		$querynodal->condition('us.office_id',$direc_code['office_id'],'=');
	}
	$querynodal->condition('us.directorate_code',$direc_code['directorate_code'],'=');
	$result1 = $querynodal->execute();
	$querynodalfinal = $result1->fetchAll();
  
	/*$querynodal = db_select('a_user_details','ud');
	$querynodal->leftJoin('a_user_details_service', 'us', 'ud.uid = us.uid');
	$querynodal->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = us.directorate_code'); 
	$querynodal->fields('ud', array('uid','fname','status'));
	$querynodal->fields('dm', array('id','directorate_name'));
	$querynodal->fields('us', array('designation','directorate_code','district_code','service_status','emp_group','office_id'));
	$querynodal->condition('ud.status',0,'=');
	$querynodal->condition('us.service_status',1,'=');
	//$query->condition('us.directorate_code',$direc_code['directorate_code'],'=');
	//$query->condition('us.office_id',$fdata->office_id,'=');
	//$query->condition('us.emp_group',array('B','C'),'IN');
	if(in_array(variable_get('field', 11), array_keys($user->roles))){
		$querynodal->condition('us.emp_group','A','!=');
		$querynodal->condition('us.office_id',$direc_code['office_id'],'=');
	}
	$querynodal->condition('us.directorate_code',$direc_code['directorate_code'],'=');
	$result1 = $querynodal->execute();
	$querynodalfinal = $result1->fetchAll();*/
	
	//print_r($querynodalfinal); exit;
	 
	$header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Sl No.  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	  //array('data' => t('<b>Directorate Name  </b>')),
	  array('data' => t('<b>'.date('Y').'</b>')),
	  array('data' => t('<b>'.(date('Y')-1).'</b>')),
	  array('data' => t('<b>'.(date('Y')-2).'</b>')),
	  array('data' => t('<b>'.(date('Y')-3).'</b>')),
	  array('data' => t('<b>'.(date('Y')-4).'</b>')),
	  array('data' => t('<b>'.(date('Y')-5).'</b>')),
	  array('data' => t('<b>'.(date('Y')-6).'</b>')),
	  array('data' => t('<b>'.(date('Y')-7).'</b>')),
	  array('data' => t('<b>'.(date('Y')-8).'</b>')),
	  array('data' => t('<b>'.(date('Y')-9).'</b>')),
	  array('data' => t('<b>'.(date('Y')-10).'</b>')),
	);
	
	/*$years = array(
	  '2018' => t('2018'),
	  '2017' => t('2017'), 
	  '2016' => t('2016'),
	  '2015' => t('2015'),
	  '2014' => t('2014'),
	  '2013' => t('2013'),
	  '2012' => t('2012'),
	  '2011' => t('2011'),
	  '2010' => t('2010'),
	  '2009' => t('2009'),
	);*/
	$years = array_combine(range(date('Y'),date('Y')-10), range(date('Y'),date('Y')-10));
	 $i=0;
	 foreach($querynodalfinal as $data){
		$i++;
		$submitted_yr = array();
		$rs = array();
		$rs = yearWiseIndividualUserDataSubmitted(array($years),$data->uid);
		
		if(!empty($rs)){
			foreach($rs as $v){
				if($data->uid == $v->uid){
					$submitted_yr[] = $v->declaration_yr;
				}
			}
		}
		
		if(in_array(date('Y'),$submitted_yr)){
			$link19 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link19 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		} 
		if(in_array(date('Y')-1,$submitted_yr)){
			$link18 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link18 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		} 
		if(in_array(date('Y')-2,$submitted_yr)){
			$link17 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link17 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		}
		if(in_array(date('Y')-3,$submitted_yr)){
			$link16 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link16 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		}
		if(in_array(date('Y')-4,$submitted_yr)){
			$link15 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link15 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		}
		if(in_array(date('Y')-5,$submitted_yr)){
			$link14 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link14 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		}
		if(in_array(date('Y')-6,$submitted_yr)){
			$link13 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link13 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		}
		if(in_array(date('Y')-7,$submitted_yr)){
			$link12 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link12 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		}
		if(in_array(date('Y')-8,$submitted_yr)){
			$link11 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link11 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		}
		if(in_array(date('Y')-9,$submitted_yr)){
			$link10 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link10 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		}
		if(in_array(date('Y')-10,$submitted_yr)){
			$link09 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link09 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		}
		/*if($data->declaration_yr == 2019 && $data->status==1){
			$link19 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
		}else{
			$link19 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		} 
		
		 if ($data->declaration_yr == 2018 && $data->status==1) {
			$link18 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
	  	}
		else {
			$link18 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
		    }
		
		if ($data->declaration_yr == 2017 && $data->status==1) {
			$link17 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
	  	}
		else {
			$link17 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
			 }
		
		if ($data->declaration_yr == 2016 && $data->status==1) {
			$link16 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
	  	}
		else {
			$link16 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
			 }
		
		if ($data->declaration_yr == 2015 && $data->status==1) {
			$link15 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Submitted')));
	  	}
		else {
			$link15 = l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">'), 
						 '', array('html' => TRUE,'attributes'=>array('title' => 'Not Submitted')));
			 }*/
		
		
		$rows[] = array( 
		  $i,
		  array('data' => t($data->fname)),
		  array('data' => t($data->designation)), 	 
		 // array('data' => t($data->directorate_name)), 
		  array('data' => t($link19)),
		  array('data' => t($link18)),
		  array('data' => t($link17)),
		  array('data' => t($link16)),
		  array('data' => t($link15)),
		  array('data' => t($link14)),
		  array('data' => t($link13)),
		  array('data' => t($link12)),
		  array('data' => t($link11)),
		  array('data' => t($link10)),
		  array('data' => t($link09)),
		);
	  }
	//print_r($rs); exit;
	
  $output .= theme('datatable', array(
							  'header' => $header,
							  'rows' => $rows,
							  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
							  'sticky' => true,
							  'caption' => '<h3>DoA Yearly Received </h3>',
							  'colgroups' => array(),
							  'empty' => t("No data found!") // The message to be displayed if table is empty
							)
						  ).theme('pager');	  	
	
	/* $output = theme_table(
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '<h3>DoA Yearly Received</h3>',
      'colgroups' => array(),
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');*/

 return '<div class="formdvider viewlist">'.$output.'</div>';	
	 
	 }
	 

function backlog_accept_list($form, &$form_state) {
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	 
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  $direc_code = getLoginUserDetailForAsset($user->uid);
  
  $allOfficer = individualAllofficer_list(0);
  
  //print_r($allOfficer); exit;
  
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Directorate Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	
	);
	
	$i=0;
	  foreach($allOfficer as $data){
		$i++;
		if($data->status == 1){
			$status = "Submitted";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		
		$rows[$data->uid.'_'.$data->declaration_yr.'_'.$data->id.'_'.$data->directorate_code] = array( 
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t($data->directorate_name)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }
	  
  $form['table_heading'] = array(
  			'#prefix' => '<div class="col-md-12"><h3>Backlog Accepted DoA to be Forwarded to Directorate</h3>',
			'#suffix' => '</div>'
  );
  	  

  $form['table_data'] = array(
			'#type' => 'tableselect',
			'#required' => TRUE,
			'#header' => $header,
			'#options' => $rows,
			'#empty' => t('No users found'),
			'#attributes' => array('class' => array('table pretty table-bordered table-hover sticky-enabled')),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		);
		
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Forward to Directorate',
			'#attributes' => array('class'=>array('form-control btn btn-success')),
			'#prefix' => '<div class="col-md-3">',
			'#suffix' => '</div>'
		);
	return $form;
}	 

function backlog_accept_list_validate($form, &$form_state){
	$validation_flag = true;
	foreach($form_state['values']['table_data'] as $k=>$val){
		if($val!=0){
			$validation_flag = false;
			break;
		}
	}
	if($validation_flag){
		drupal_set_message('Please select atleast one officer.',$type = 'error');
	}
}

function backlog_accept_list_submit($form, &$form_state) { 
	global $user;
	//$loginuser_code = getLoginUserDetailForAsset($user->uid);
	$asset_user_id = "";
	$asset_id = "";
	$print_id = array();
	
	
	/****************************************Validation part**************************************************************/
	$validation_flag = true;
	$cnt = 0;
	$msg = '';
	//print_r($form_state['values']['table_data']); exit;
	foreach($form_state['values']['table_data'] as $k=>$val){
		/*if($val!=0){
			$validation_flag = false;
			break;
		}*/
		if($k==$val){
			$cnt++;
		}
	}
	if($cnt==0){
		$msg = 'Please select atleast one officer.';
		$validation_flag = false;
		//break;
	}else if($cnt>20){
		$msg = 'More than 20 officers cannot be selected.';
		$validation_flag = false;
		//break;
	}
	
	//echo $cnt; exit;
	if($validation_flag==false){
		drupal_set_message($msg,$type = 'error');
		drupal_goto('backlog-accept-list-from-department');
	}
	/****************************************Validation part End**************************************************************/
	
	foreach($form_state['values']['table_data'] as $k=>$v){
		
		if($k==$v){
	
			$d_arr = explode('_',$v);
			
			$print_id[] = $d_arr[0];
			
			$asset_user_id .= ",".$d_arr[0];
			$asset_id .= ",".$d_arr[2];
			
			
			$user_info = getLoginUserDetailForAsset($d_arr[0]);
			//send_sms($user_info['mobile'],'Your Asset Statement for the year '.$d_arr[1].' has been accepted by the Labour Department.');
		}
	}
	
	$asset_user_id = ltrim($asset_user_id,",");
	$asset_id = ltrim($asset_id,",");
	//print_r($print_id); exit;
	$print_id = base64_encode(serialize($print_id));
	
	$number = forwarding_id();
	$number = $number +1;
	$forwarding_no = 'DOA-'.str_pad($number, 4, "0", STR_PAD_LEFT).'-'.$d_arr[3].'-'.$d_arr[1];
	
	$query1 = db_insert('a_transaction_history');
	$query1->fields(array(
					'uid' => $user->uid,
					'asset_user_id' => $asset_user_id,
					'status' => 'A',
					'remarks'  => '',
					'transaction_date'  => date('Y-m-d H:i:s'),
					'asset_id' => $asset_id,
					'declaration_year' =>  $d_arr[1],
					'buld_pdf_link' => $print_id,
					'directorate_code' => $d_arr[3],
					'forwarding_no' => $forwarding_no
			));
	$transaction_id = $query1->execute();

	//echo $transaction_id;
	//exit;
	
	$myarr = array();
	foreach($form_state['values']['table_data'] as $key=>$val){
		
		if($key==$val){

			$myarr = explode('_',$val);
			
					
			$query = db_update('a_asset_mst');
	  		$query->fields(array(
	  						'forward_status' => 'A',
							'transaction_id' => $transaction_id
					));
			$query->condition('id',$myarr[2],'=');
  			$rs = $query->execute();
			
			
			
		}
	}
	
   //$login_user_info = getLoginUserDetailForAsset($user->uid);  bulkacknowledgement-print
   //send_sms($login_user_info['mobile'],'Your Asset Statement for the year '.$d_arr[1].' has been forwarded to the Labour Department.');

	drupal_set_message('The Selected DoA of officers have been sucessfully accepted by the Labour Department! '.l('PRINT FORWARDING LETTER',
	'bulkacknowledgement-received/'.$print_id.'/'.$d_arr[1], array('html' => TRUE,'attributes'=>array('target'=>'_blank'))));	
	
}

function backlog_outbox_accept_list(){
	
    global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}	
		 
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  $direc_code = getLoginUserDetailForAsset($user->uid);

  $ApprovedList = directorateForwardedList('A',$direc_code['directorate_code']);  
  
  //$ForwardList = directorateForwardedListFromLD('F',$direc_code['directorate_code']);
  
  //print_r($ForwardList); exit;
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Directorate Name</b>')),	
	  array('data' => t('<b>Number of DoA Sent</b>')),
	  array('data' => t('<b>Date of DoA Forwarded</b>')),
	  array('data' => t('<b>PDF Link</b>')),
	);
	
	$i=0;
	  foreach($ApprovedList as $data){
		$i++;
		$arr = explode(",",$data->asset_id);
		
		if(trim($data->directorate_code) == 'DB'){
			$directorate_name = 'Boilers';
		}elseif(trim($data->directorate_code) == 'LC'){
			$directorate_name = 'Labour Commissionerate';
		}elseif(trim($data->directorate_code) == 'DE'){
			$directorate_name = 'Directorate of Employment';
		}elseif(trim($data->directorate_code) == 'DF'){
			$directorate_name = 'Directorate of Factories';
		}elseif(trim($data->directorate_code) == 'ESI'){
			$directorate_name = 'Directorate of ESI (MB) Scheme';
		}elseif(trim($data->directorate_code) == 'LWB'){
			$directorate_name = 'Labour Welfare Board';
		}elseif(trim($data->directorate_code) == 'DEC'){
			$directorate_name = 'Directorate of Employees Compensation';
		}elseif(trim($data->directorate_code) == 'DIT'){
			$directorate_name = 'Directorate of Industrial Tribunal';
		}elseif(trim($data->directorate_code) == 'LD'){
			$directorate_name = 'Labour Department';
		}
		
		$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'bulkacknowledgement-received/'.$data->buld_pdf_link.'/'.$data->declaration_year, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));		
		$rows[] = array( 
		  array('data' => t(l($directorate_name, 'backlog-accept-doa-list-from-ld/'.base64_encode($data->asset_id).'/'.$data->directorate_code))),	
		  array('data' => t(count($arr))),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->transaction_date)))),
		  array('data' => $link),
		);
	  }
	
	
	 $output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  

	
 return '<div class="formdvider viewlist">'.$output.'</div>';	

}

function field_accept_list($form, &$form_state){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  	$direc_code = getLoginUserDetailForAsset($user->uid);
	
	$rsFieldData = individualDoAListByFieldOfficer(0,$direc_code['directorate_code'],$direc_code['office_id']);
	
  
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	
	);
	
	$i=0;
	  foreach($rsFieldData as $data){
		$i++;
		if($data->status == 1){
			$status = "Submitted";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		
		$rows[$data->uid.'_'.$data->declaration_yr.'_'.$data->id.'_'.$data->directorate_code.'_'.$data->office_id] = array( 
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }
	  
  $form['table_heading'] = array(
  			'#prefix' => '<div class="col-md-12"><h3>Accept DoA By Field Officers</h3>',
			'#suffix' => '</div>'
  );
  	  

  $form['table_data'] = array(
		'#type' => 'tableselect',
		//'#caption' => '',
		'#required' => TRUE,
		'#header' => $header,
		'#options' => $rows,
		//'#multiple' => FALSE,
		//'#default_value' => $selected_recipient_data,
		'#empty' => t('No users found'),
		'#attributes' => array('class' => array('table pretty table-bordered table-hover sticky-enabled')),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	);
		
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Forward to Directorate',
		'#attributes' => array('class'=>array('form-control btn btn-success')),
		'#prefix' => '<div class="col-md-3">',
		'#suffix' => '</div>'
	);
	return $form;
}

function field_accept_list_validate($form, &$form_state){
	$validation_flag = true;
	foreach($form_state['values']['table_data'] as $k=>$val){
		if($val!=0){
			$validation_flag = false;
			break;
		}
	}
	if($validation_flag){
		drupal_set_message('Please select atleast one officer.',$type = 'error');
	}
}

function field_accept_list_submit($form, &$form_state) { 
	global $user;
	//$loginuser_code = getLoginUserDetailForAsset($user->uid);
	$asset_user_id = "";
	$asset_id = "";
	$print_id = array();
	
	//print_r($form_state['values']['table_data']); exit;
	
	foreach($form_state['values']['table_data'] as $k=>$v){
		if($k==$v){
	
			$d_arr = explode('_',$v);
			
			$print_id[] = $d_arr[0];
			
			$asset_user_id .= ",".$d_arr[0];
			$asset_id .= ",".$d_arr[2];
			
			
			$user_info = getLoginUserDetailForAsset($d_arr[0]);
			send_sms($user_info['mobile'],'Your Asset Statement for the year '.$d_arr[1].' has been forwarded to the Directorate Nodal Officer.');
		}
	}
	
	$asset_user_id = ltrim($asset_user_id,",");
	$asset_id = ltrim($asset_id,",");
	//print_r($print_id); exit;
	$print_id = base64_encode(serialize($print_id));
	
	$number = forwarding_id();
	$number = $number +1;
	$forwarding_no = 'DOA-'.str_pad($number, 4, "0", STR_PAD_LEFT).'-'.$d_arr[3].'-'.$d_arr[1];
	
	$query1 = db_insert('a_transaction_history');
	$query1->fields(array(
					'uid' => $user->uid,
					'asset_user_id' => $asset_user_id,
					'status' => 'F',
					'remarks'  => '',
					'transaction_date'  => date('Y-m-d H:i:s'),
					'asset_id' => $asset_id,
					'declaration_year' =>  $d_arr[1],
					'buld_pdf_link' => $print_id,
					'directorate_code' => $d_arr[3],
					'forwarding_no' => $forwarding_no,
					'office_id' => $d_arr[4]
					
			));
	$transaction_id = $query1->execute();


	$myarr = array();
	foreach($form_state['values']['table_data'] as $key=>$val){
		
		if($key==$val){

			$myarr = explode('_',$val);
			
					
			$query = db_update('a_asset_mst');
	  		$query->fields(array(
	  						'forward_status' => 'F',
							'transaction_id' => $transaction_id
					));
			$query->condition('id',$myarr[2],'=');
  			$rs = $query->execute();
			
		}
	}
	
	drupal_set_message('The Selected DoA of officers have been sucessfully forwarded to the Directorate! '.l('PRINT FORWARDING LETTER',
	'bulkacknowledgement-print/'.$print_id.'/'.$d_arr[1], array('html' => TRUE,'attributes'=>array('target'=>'_blank'))));	
	
}
	 
function groupA_officer_list($form, &$form_state) {
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	 
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  $direc_code = getLoginUserDetailForAsset($user->uid);
  
  $groupAlist = individualGroupAofficer_list(0,$direc_code['directorate_code']);
  
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	
	);
	
	$i=0;
	  foreach($groupAlist as $data){
		$i++;
		if($data->status == 1){
			$status = "Submitted";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		
		$rows[$data->uid.'_'.$data->declaration_yr.'_'.$data->id.'_'.$data->directorate_code] = array( 
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }
	  
  $form['table_heading'] = array(
  			'#prefix' => '<div class="col-md-12"><h3>DoA GroupA Officers</h3>',
			'#suffix' => '</div>'
  );
  	  

  $form['table_data'] = array(
			'#type' => 'tableselect',
			//'#caption' => '',
			'#required' => TRUE,
			'#header' => $header,
			'#options' => $rows,
			//'#multiple' => FALSE,
			//'#default_value' => $selected_recipient_data,
			'#empty' => t('No users found'),
			'#attributes' => array('class' => array('table pretty table-bordered table-hover sticky-enabled')),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		);
		
 if(in_array(variable_get('assetdiradmin', 10), array_keys($user->roles))){
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Forward to Department',
			'#attributes' => array('class'=>array('form-control btn btn-success')),
			'#prefix' => '<div class="col-md-3">',
			'#suffix' => '</div>'
		);
 }
	return $form;
 //return '<div class="formdvider viewlist">'.$output.'</div>';	
}	 

function groupA_officer_list_validate($form, &$form_state){
	$validation_flag = true;
	foreach($form_state['values']['table_data'] as $k=>$val){
		if($val!=0){
			$validation_flag = false;
			break;
		}
	}
	if($validation_flag){
		drupal_set_message('Please select atleast one officer.',$type = 'error');
	}
}

function groupA_officer_list_submit($form, &$form_state) { 
	global $user;
	//$loginuser_code = getLoginUserDetailForAsset($user->uid);
	$asset_user_id = "";
	$asset_id = "";
	$print_id = array();
	
	foreach($form_state['values']['table_data'] as $k=>$v){
		if($k==$v){
	
			$d_arr = explode('_',$v);
			
			$print_id[] = $d_arr[0];
			
			$asset_user_id .= ",".$d_arr[0];
			$asset_id .= ",".$d_arr[2];
			
			
			$user_info = getLoginUserDetailForAsset($d_arr[0]);
			send_sms($user_info['mobile'],'Your Asset Statement for the year '.date('Y').' has been forwarded to the Labour Department.');
		}
	}
	
	$asset_user_id = ltrim($asset_user_id,",");
	$asset_id = ltrim($asset_id,",");
	//print_r($print_id); exit;
	$print_id = base64_encode(serialize($print_id));
	
	$number = forwarding_id();
	$number = $number +1;
	$forwarding_no = 'DOA-'.str_pad($number, 4, "0", STR_PAD_LEFT).'-'.$d_arr[3].'-'.$d_arr[1];
	
	$query1 = db_insert('a_transaction_history');
	$query1->fields(array(
					'uid' => $user->uid,
					'asset_user_id' => $asset_user_id,
					'status' => 'F',
					'remarks'  => '',
					'transaction_date'  => date('Y-m-d H:i:s'),
					'asset_id' => $asset_id,
					'declaration_year' =>  $d_arr[1],
					'buld_pdf_link' => $print_id,
					'directorate_code' => $d_arr[3],
					'forwarding_no' => $forwarding_no
			));
	$transaction_id = $query1->execute();


	$myarr = array();
	foreach($form_state['values']['table_data'] as $key=>$val){
		
		if($key==$val){

			$myarr = explode('_',$val);
			
					
			$query = db_update('a_asset_mst');
	  		$query->fields(array(
	  						'forward_status' => 'F',
							'transaction_id' => $transaction_id
					));
			$query->condition('id',$myarr[2],'=');
  			$rs = $query->execute();
			
			
			
		}
	}
	
   

	drupal_set_message('The Selected DoA of officers have been sucessfully forwarded to the Labour Department! '.l('PRINT FORWARDING LETTER',
	'bulkacknowledgement-print/'.$print_id.'/'.$d_arr[1], array('html' => TRUE,'attributes'=>array('target'=>'_blank'))));	
	
}

function from_field_officer_list_to_nodal($form, &$form_state, $arg1, $arg2, $arg3) {
  global $user;	 
  $status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
  $asset_id = base64_decode($arg1);
  $direc_code = $arg2;
  $office_id = base64_decode($arg3);	
  
  //$direc_code = getLoginUserDetailForAsset($user->uid);
  
  $groupAlist = bulkGroupAofficer_list('F',$direc_code,$asset_id);
  
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	 
	);
	
	$i=0;
	  foreach($groupAlist as $data){
		$i++;
		if($data->forward_status == 'F'){
			$status = "Forwarded From Field";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		//echo $data->directorate_code; exit;
		
		$rows[$data->uid.'_'.$data->declaration_yr.'_'.$data->id.'_'.$data->directorate_code.'_'.$office_id] = array( 
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }

	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Receive Asset Declaration</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );


  	$form['table_data'] = array(
			'#type' => 'tableselect',
			//'caption' => '<h3>DoA Group A Officers </h3>',
			'#required' => TRUE,
			'#header' => $header,
			'#options' => $rows,
			//'#multiple' => FALSE,
			//'#default_value' => $selected_recipient_data,
			'#empty' => t('No users found'),
			'#attributes' => array('class' => array('table pretty table-bordered table-hover sticky-enabled')),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		);
		
		$form['accept_reject'] = array(
			'#type' => 'select',
			'#title' => t('Please select whether you want to Accept or Reject the Asset Declaration'),
			'#options' => array('1'=>t('Accept'),'2'=>t('Reject')),
			'#ajax' => array(
				'callback' => 'ajax_accept_reject_callback',
			 ),
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Please select whether you want to Accept or Reject the Asset Declaration'),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		);
		if(isset($form_state['values']['accept_reject']) && $form_state['values']['accept_reject']=="2"){
			$form['reject'] = array(
				'#type' => 'select',
				'#title' => t('Reason for rejection'),
				'#options' => array('1'=>t('Mutilated'),'2'=>t('Not Properly Sealed'),'3'=>t('Apparently Blank')),
				'#required' => TRUE,
				'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Reason for rejection'),
				'#prefix' => '<div id="replace_div_reject"><div class="col-md-12">',
				'#suffix' => '</div></div>'
			); 
		}
		$form['reject_blank'] = array(
			'#prefix' => '<div id="replace_div_reject">',
			'#suffix' => '</div>'
		);
		
		
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
			'#attributes' => array('class'=>array('form-control btn btn-info')),
			'#prefix' => '<div class="col-md-2">',
			'#suffix' => '</div>'
		);
		
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );
	return $form;
}

function from_field_officer_list_to_nodal_validate($form, &$form_state){
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	$validation_flag = true;
	foreach($form_state['values']['table_data'] as $k=>$val){
		if($val!=0){
			$validation_flag = false;
			break;
		}
	}
	if($validation_flag){
		drupal_set_message('Please select atleast one officer.',$type = 'error');
	}
}
function from_field_officer_list_to_nodal_submit($form, &$form_state) { 
	global $user;
	//echo $form_state['values']['accept_reject']; exit;
	//$loginuser_code = getLoginUserDetailForAsset($user->uid);
	
	$asset_user_id = "";
	$asset_id = "";
	$print_id = array();
	
	//print_r($form_state['values']['table_data']); exit;
	
	foreach($form_state['values']['table_data'] as $k=>$v){
		if($k==$v){

			$d_arr = explode('_',$v);
			
			$print_id[] = $d_arr[0];
			
		    $asset_user_id .= ",".$d_arr[0];
			$asset_id .= ",".$d_arr[2];
			
			$user_info = getLoginUserDetailForAsset($d_arr[0]);
			if($form_state['values']['accept_reject'] == 2){
				send_sms($user_info['mobile'],'Your Asset Statement for the year '.$d_arr[1].' has been rejected by the Directorate.');
			}else{
				send_sms($user_info['mobile'],'Your Asset Statement for the year '.$d_arr[1].' has been received by the Directorate.');
			}
		}
	}
	
	$asset_user_id = ltrim($asset_user_id,",");
	$asset_id = ltrim($asset_id,",");
	//print_r($print_id); exit;
	$print_id = base64_encode(serialize($print_id));
	
	
	$number = forwarding_id();
	$number = $number +1;
	$forwarding_no = 'DOA-'.str_pad($number, 4, "0", STR_PAD_LEFT).'-'.$d_arr[3].'-'.$d_arr[1];
	
	
	if($form_state['values']['accept_reject'] == 2){
		$sts = 'R';
		$remarks = $form_state['values']['reject'];
	}else{
		$sts = 'A';
		$remarks = "";
	}
	
	$query1 = db_insert('a_transaction_history');
	$query1->fields(array(
					'uid' => $user->uid,
					'asset_user_id' => $asset_user_id,
					'status' => $sts,
					'remarks'  => $remarks,
					'transaction_date'  => date('Y-m-d H:i:s'),
					'asset_id' => $asset_id,
					'declaration_year' =>  $d_arr[1],
					'buld_pdf_link' => $print_id,
					'directorate_code' => $d_arr[3],
					'forwarding_no' => $forwarding_no,
					'office_id' => $d_arr[4],
			));
	$transaction_id = $query1->execute();
	
	$myarr = array();
	foreach($form_state['values']['table_data'] as $key=>$val){
		
		if($key==$val){

			$myarr = explode('_',$val);
			
					
			$query = db_update('a_asset_mst');
	  		$query->fields(array(
	  						'forward_status' => $sts,
							'transaction_id' => $transaction_id
					));
			$query->condition('id',$myarr[2],'=');
  			$rs = $query->execute();
			
		}
	}
	
	if($form_state['values']['accept_reject'] == 2){
		drupal_set_message('The Selected DoA of officers have been rejected by the Directorate! '.l('PRINT ACKNOWLEDGEMENT',
	'bulkacknowledgement-received/'.$print_id, array('html' => TRUE,'attributes'=>array('target'=>'_blank'))));
	}else{
		drupal_set_message('The Selected DoA of officers have been sucessfully received by the Directorate! '.l('PRINT ACKNOWLEDGEMENT',
	'bulkacknowledgement-received/'.$print_id, array('html' => TRUE,'attributes'=>array('target'=>'_blank'))));
	}
	
}

function groupA_officer_list_directorate($form, &$form_state, $arg1, $arg2) {
  global $user;	 
  $status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
  
  ctools_include('modal');
  ctools_modal_add_js();
  
  $asset_id = base64_decode($arg1);
  $direc_code = $arg2;	
  
  //$direc_code = getLoginUserDetailForAsset($user->uid);
  
  $groupAlist = bulkGroupAofficer_list('F',$direc_code,$asset_id);
  //print_r( $groupAlist); exit;
  
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	 
	);
	
	$i=0;
	  foreach($groupAlist as $data){
		$i++;
		if($data->forward_status == 'F'){
			$status = "Forwarded To Department";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		//echo $data->directorate_code; exit;
		
		$rows[$data->uid.'_'.$data->declaration_yr.'_'.$data->id.'_'.$data->directorate_code] = array( 
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }

	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Receive Asset Declaration</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );


  	$form['table_data'] = array(
			'#type' => 'tableselect',
			//'caption' => '<h3>DoA Group A Officers </h3>',
			'#required' => TRUE,
			'#header' => $header,
			'#options' => $rows,
			//'#multiple' => FALSE,
			//'#default_value' => $selected_recipient_data,
			'#empty' => t('No users found'),
			'#attributes' => array('class' => array('table pretty table-bordered table-hover sticky-enabled')),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		);
		
		$form['accept_reject'] = array(
			'#type' => 'select',
			'#title' => t('Please select whether you want to Accept or Reject the Asset Declaration'),
			'#options' => array('1'=>t('Accept'),'2'=>t('Reject')),
			'#ajax' => array(
				'callback' => 'ajax_accept_reject_callback',
			 ),
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Please select whether you want to Accept or Reject the Asset Declaration'),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		);
		if(isset($form_state['values']['accept_reject']) && $form_state['values']['accept_reject']=="2"){
			$form['reject'] = array(
				'#type' => 'select',
				'#title' => t('Reason for rejection'),
				'#options' => array('1'=>t('Mutilated'),'2'=>t('Not Properly Sealed'),'3'=>t('Apparently Blank')),
				'#required' => TRUE,
				'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Reason for rejection'),
				'#prefix' => '<div id="replace_div_reject"><div class="col-md-12">',
				'#suffix' => '</div></div>'
			); 
		}
		$form['reject_blank'] = array(
			'#prefix' => '<div id="replace_div_reject">',
			'#suffix' => '</div>'
		);
		
		
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
			'#attributes' => array('class'=>array('form-control btn btn-info')),
			'#prefix' => '<div class="col-md-2">',
			'#suffix' => '</div>'
		);
		/*$form['back'] = array(
			'#type' => 'submit',
			'#validate' => array('groupA_officer_list_directorate_validate'),
			'#submit'=>array('not_applicable_asset'),
			'#value' => 'Reject',
			'#ajax' => array(
				//'wrapper' => 'id_of_some_unique_element',
				'callback' => 'my_module_callback',  
			  ),
			'#attributes' => array('class'=>array('form-control btn btn-danger')),
			'#prefix' => '<div class="col-md-2">',
			'#suffix' => '</div>'
		);*/
		
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );
	return $form;
 //return '<div class="formdvider viewlist">'.$output.'</div>';	
}

function ajax_accept_reject_callback($form, &$form_state){
	$commands   = array();
	if($form_state['values']['accept_reject']=='2'){
		$commands[] = ajax_command_replace('#replace_div_reject', '<div id="replace_div_reject">'.drupal_render($form['reject']).'</div>');
	}else{
		$commands[] = ajax_command_replace('#replace_div_reject', '<div id="replace_div_reject">'.drupal_render($form['reject_blank']).'</div>');
	}
	return array('#type' => 'ajax', '#commands' => $commands);
}
/*function my_module_callback($form, &$form_state){
	return drupal_get_form('gtnmodal_form');
}*/

/*function not_applicable_asset($form, &$form_state){
   ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'title' => t(''),
	  'gtn_id'=>$form_state['values']['table_data'],
    );
    $output = ctools_modal_form_wrapper('gtnmodal_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  
}

function gtnmodal_form($form, &$form_state){
  $form = array();
  //$form['#attributes']['id'][] = 'my';	
  $form['gtn_id'] = array(
    '#type' => 'textfield',
    '#title' => t('gtn_id'),
	'#required' => TRUE,
	'#default_value' => $form_state['gtn_id'],
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'GTN ID',),
	'#prefix' => '<div class="col-md-12">',
	'#suffix' => '</div>'
  );
  
  $form['notsubmit'] = array(
	'#type' => 'submit',
	'#id' => 'gtn_btn',
	'#ajax' => array(
				'callback' => 'gtnmodal_form_ajax',
				'wrapper' => 'table_div_replace',
			),
	'#value' => 'Reject12',
	'#attributes' => array('class'=>array('form-control btn btn-info')),
	'#prefix' => '<div class="col-md-2">',
	'#suffix' => '</div>'
  );
   return $form;
}


function gtnmodal_form_ajax($form, &$form_state){
	die('hii');
	//return "-->".$form_state['input']['gtn_id'];
}
*/
function groupA_officer_list_directorate_validate($form, &$form_state){
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	$validation_flag = true;
	foreach($form_state['values']['table_data'] as $k=>$val){
		if($val!=0){
			$validation_flag = false;
			break;
		}
	}
	if($validation_flag){
		drupal_set_message('Please select atleast one officer.',$type = 'error');
	}
}

function groupA_officer_list_directorate_submit($form, &$form_state) { 
	global $user;
	//echo $form_state['values']['accept_reject']; exit;
	//$loginuser_code = getLoginUserDetailForAsset($user->uid);
	
	$asset_user_id = "";
	$asset_id = "";
	$print_id = array();
	
	foreach($form_state['values']['table_data'] as $k=>$v){
		if($k==$v){

			$d_arr = explode('_',$v);
			
			$print_id[] = $d_arr[0];
			
		    $asset_user_id .= ",".$d_arr[0];
			$asset_id .= ",".$d_arr[2];
			
			$user_info = getLoginUserDetailForAsset($d_arr[0]);
			if($form_state['values']['accept_reject'] == 2){
				send_sms($user_info['mobile'],'Your Asset Statement for the year '.date('Y').' has been rejected by the Labour Department.');
			}else{
				send_sms($user_info['mobile'],'Your Asset Statement for the year '.date('Y').' has been received by the Labour Department.');
			}
		}
	}
	
	$asset_user_id = ltrim($asset_user_id,",");
	$asset_id = ltrim($asset_id,",");
	//print_r($print_id); exit;
	$print_id = base64_encode(serialize($print_id));
	
	
	$number = forwarding_id();
	$number = $number +1;
	$forwarding_no = 'LABR-'.str_pad($number, 4, "0", STR_PAD_LEFT).'-LD-'.$d_arr[1];
	
	
	if($form_state['values']['accept_reject'] == 2){
		$sts = 'R';
		$remarks = $form_state['values']['reject'];
	}else{
		$sts = 'A';
		$remarks = "";
	}
	
	$query1 = db_insert('a_transaction_history');
	$query1->fields(array(
					'uid' => $user->uid,
					'asset_user_id' => $asset_user_id,
					'status' => $sts,
					'remarks'  => $remarks,
					'transaction_date'  => date('Y-m-d H:i:s'),
					'asset_id' => $asset_id,
					'declaration_year' =>  $d_arr[1],
					'buld_pdf_link' => $print_id,
					'directorate_code' => $d_arr[3],
					'forwarding_no' => $forwarding_no
			));
	$transaction_id = $query1->execute();
	
	$myarr = array();
	foreach($form_state['values']['table_data'] as $key=>$val){
		
		if($key==$val){

			$myarr = explode('_',$val);
			
					
			$query = db_update('a_asset_mst');
	  		$query->fields(array(
	  						'forward_status' => $sts,
							'transaction_id' => $transaction_id
					));
			$query->condition('id',$myarr[2],'=');
  			$rs = $query->execute();
			
		}
	}
	
	if($form_state['values']['accept_reject'] == 2){
		drupal_set_message('The Selected DoA of officers have been rejected by the Labour Department! '.l('PRINT ACKNOWLEDGEMENT',
	'bulkacknowledgement-received/'.$print_id, array('html' => TRUE,'attributes'=>array('target'=>'_blank'))));
	}else{
		drupal_set_message('The Selected DoA of officers have been sucessfully received by the Labour Department! '.l('PRINT ACKNOWLEDGEMENT',
	'bulkacknowledgement-received/'.$print_id, array('html' => TRUE,'attributes'=>array('target'=>'_blank'))));
	}
	
}

function backlog_accept_doa_list_from_ld($arg1,$arg2){	 
  global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}	
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
 //$direc_code = getLoginUserDetailForAsset($user->uid);
 
 $asset_id = base64_decode($arg1);
 $direc_code = $arg2;
  
 $groupAlist = bulkGroupAofficer_list('',$direc_code,$asset_id);
  
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Sl No.  </b>')),	
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	 
	);
	
	$i=0;
	  foreach($groupAlist as $data){
		$i++;
		if($data->forward_status == 'F'){
			$status = "Forwarded To Department";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}elseif($data->forward_status == 'R'){
			$status = "Rejected By Department";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}elseif($data->forward_status == 'A'){
			$status = "Received By Department";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		
		$rows[$data->uid] = array( 
		  $i,
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }
	
	
	 $output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  

	
 return '<div class="formdvider viewlist">'.$output.'</div>';	
}

function field_outbox_list($arg1,$arg2){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}	
  	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$asset_id = base64_decode($arg1);
	$direc_code = $arg2;
	
	$groupAlist = bulkGroupAofficer_list('',$direc_code,$asset_id);
  
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Sl No.  </b>')),	
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	 
	);
	
	$i=0;
	  foreach($groupAlist as $data){
		$i++;
		if($data->forward_status == 'F'){
			$status = "Forwarded To Directorate";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}elseif($data->forward_status == 'R'){
			$status = "Rejected By Directorate";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}elseif($data->forward_status == 'A'){
			$status = "Received By Directorate";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		
		$rows[$data->uid] = array( 
		  $i,
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }
	
	$output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  
 return '<div class="formdvider viewlist">'.$output.'</div>';
	
}

function groupA_outbox_list($arg1,$arg2){	 
  global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}	
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
 //$direc_code = getLoginUserDetailForAsset($user->uid);
 
 $asset_id = base64_decode($arg1);
 $direc_code = $arg2;
  
 $groupAlist = bulkGroupAofficer_list('',$direc_code,$asset_id);
  
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Sl No.  </b>')),	
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	 
	);
	
	$i=0;
	  foreach($groupAlist as $data){
		$i++;
		if($data->forward_status == 'F'){
			$status = "Forwarded To Department";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}elseif($data->forward_status == 'R'){
			$status = "Rejected By Department";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}elseif($data->forward_status == 'A'){
			$status = "Received By Department";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		
		$rows[$data->uid] = array( 
		  $i,
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }
	
	
	 $output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  

	
 return '<div class="formdvider viewlist">'.$output.'</div>';	
}


function groupA_outbox_details_list($arg1,$arg2){	
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	} 
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
 //$direc_code = getLoginUserDetailForAsset($user->uid);
 
 $asset_id = base64_decode($arg1);
 $direc_code = $arg2;
  
 $groupAlist = bulkGroupAofficer_list('',$direc_code,$asset_id);
  
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Sl No.  </b>')),	
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	 
	);
	
	$i=0;
	  foreach($groupAlist as $data){
		$i++;
		if($data->forward_status == 'A'){
			$status = "Received By Department";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}elseif($data->forward_status == 'R'){
			$status = "Rejected";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		
		$rows[$data->uid] = array( 
		  $i,
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }
	
	
	 $output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '<h3>DoA Forwarded List</h3>',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  

	
 return '<div class="formdvider viewlist">'.$output.'</div>';	
}

function directorate_inbox_list_for_Field(){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}	 
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  $direc_code = getLoginUserDetailForAsset($user->uid);

  $ForwardList = directorateForwardedListFromField('F',$direc_code['directorate_code']);
  
  //print_r($ForwardList); exit;
  //$ForwardList = directorateForwardedListFromLD('F',$direc_code['directorate_code']);
  
  //print_r($ForwardList); exit;
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Directorate Name</b>')),	
	  array('data' => t('<b>Number of DoA Received</b>')),
	  array('data' => t('<b>Date of DoA Forwarded</b>')),
	  array('data' => t('<b>PDF Link</b>')),
	);
	
	$i=0;
	$cnt = 0;
	//$cnt = count($ForwardList);
	  foreach($ForwardList as $data){
		$i++;
		
		if(trim($data->directorate_code) == 'DB'){
			$directorate_name = 'Boilers';
		}elseif(trim($data->directorate_code) == 'LC'){
			$directorate_name = 'Labour Commissionerate';
		}elseif(trim($data->directorate_code) == 'DE'){
			$directorate_name = 'Directorate of Employment';
		}elseif(trim($data->directorate_code) == 'DF'){
			$directorate_name = 'Directorate of Factories';
		}elseif(trim($data->directorate_code) == 'ESI'){
			$directorate_name = 'Directorate of ESI (MB) Scheme';
		}elseif(trim($data->directorate_code) == 'LWB'){
			$directorate_name = 'Labour Welfare Board';
		}elseif(trim($data->directorate_code) == 'DEC'){
			$directorate_name = 'Directorate of Employees Compensation';
		}elseif(trim($data->directorate_code) == 'DIT'){
			$directorate_name = 'Directorate of Industrial Tribunal';
		}elseif(trim($data->directorate_code) == 'LD'){
			$directorate_name = 'Labour Department';
		}
		
		$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'bulkacknowledgement-print/'.$data->buld_pdf_link.'/'.$data->declaration_year, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));		
		$rows[] = array( 
		  array('data' => t(l($directorate_name, 'field-inbox-accept-reject/'.base64_encode($data->asset_id).'/'.trim($data->directorate_code).'/'.base64_encode(trim($data->office_id))))),	
		  array('data' => t($data->total_cnt)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->transaction_date)))),
		  array('data' => $link),
		);
	  }
	  
	  
	
	
	 $output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '<h3>DoA Received List Inbox</h3>',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  

	
 return '<div class="formdvider viewlist">'.$output.'</div>';	
}

function directorate_inbox_list_for_LD(){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}	 
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  //$direc_code = getLoginUserDetailForAsset($user->uid);

  $ForwardList = directorateForwardedListFromLD();
  
  //$ForwardList = directorateForwardedListFromLD('F',$direc_code['directorate_code']);
  
  //print_r($ForwardList); exit;
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Directorate Name</b>')),	
	  array('data' => t('<b>Number of DoA Received</b>')),
	  array('data' => t('<b>Date of DoA Forwarded</b>')),
	  array('data' => t('<b>PDF Link</b>')),
	);
	
	$i=0;
	$cnt = 0;
	//$cnt = count($ForwardList);
	  foreach($ForwardList as $data){
		$i++;
		
		if(trim($data->directorate_code) == 'DB'){
			$directorate_name = 'Boilers';
		}elseif(trim($data->directorate_code) == 'LC'){
			$directorate_name = 'Labour Commissionerate';
		}elseif(trim($data->directorate_code) == 'DE'){
			$directorate_name = 'Directorate of Employment';
		}elseif(trim($data->directorate_code) == 'DF'){
			$directorate_name = 'Directorate of Factories';
		}elseif(trim($data->directorate_code) == 'ESI'){
			$directorate_name = 'Directorate of ESI (MB) Scheme';
		}elseif(trim($data->directorate_code) == 'LWB'){
			$directorate_name = 'Labour Welfare Board';
		}elseif(trim($data->directorate_code) == 'DEC'){
			$directorate_name = 'Directorate of Employees Compensation';
		}elseif(trim($data->directorate_code) == 'DIT'){
			$directorate_name = 'Directorate of Industrial Tribunal';
		}elseif(trim($data->directorate_code) == 'LD'){
			$directorate_name = 'Labour Department';
		}
		
		$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'bulkacknowledgement-print/'.$data->buld_pdf_link.'/'.$data->declaration_year, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));		
		$rows[] = array( 
		  array('data' => t(l($directorate_name, 'groupA-inbox-list/'.base64_encode($data->asset_id).'/'.$data->directorate_code))),	
		  array('data' => t($data->total_cnt)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->transaction_date)))),
		  array('data' => $link),
		);
	  }
	  
	  
	
	
	 $output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '<h3>DoA Received List From Directorates</h3>',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  

	
 return '<div class="formdvider viewlist">'.$output.'</div>';	
}

function from_nodal_field_outbox_list(){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  $direc_code = getLoginUserDetailForAsset($user->uid);

  $ForwardList = directorateApproveRejectListFromField($direc_code['directorate_code']);  
  
  //$ForwardList = directorateForwardedListFromLD('F',$direc_code['directorate_code']);
  
  //print_r($ForwardList); exit;
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Directorate Name</b>')),	
	  array('data' => t('<b>Number of DoA Sent</b>')),
	  array('data' => t('<b>Date of DoA Forwarded</b>')),
	  array('data' => t('<b>PDF Link</b>')),
	);
	
	$i=0;
	  foreach($ForwardList as $data){
		$i++;
		$arr = explode(",",$data->asset_id);
		
		if(trim($data->directorate_code) == 'DB'){
			$directorate_name = 'Boilers';
		}elseif(trim($data->directorate_code) == 'LC'){
			$directorate_name = 'Labour Commissionerate';
		}elseif(trim($data->directorate_code) == 'DE'){
			$directorate_name = 'Directorate of Employment';
		}elseif(trim($data->directorate_code) == 'DF'){
			$directorate_name = 'Directorate of Factories';
		}elseif(trim($data->directorate_code) == 'ESI'){
			$directorate_name = 'Directorate of ESI (MB) Scheme';
		}elseif(trim($data->directorate_code) == 'LWB'){
			$directorate_name = 'Labour Welfare Board';
		}elseif(trim($data->directorate_code) == 'DEC'){
			$directorate_name = 'Directorate of Employees Compensation';
		}elseif(trim($data->directorate_code) == 'DIT'){
			$directorate_name = 'Directorate of Industrial Tribunal';
		}elseif(trim($data->directorate_code) == 'LD'){
			$directorate_name = 'Labour Department';
		}
		
		$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'bulkacknowledgement-received/'.$data->buld_pdf_link.'/'.$data->declaration_year, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));		
		$rows[] = array( 
		  array('data' => t(l($directorate_name, 'field-outbox-list/'.base64_encode($data->asset_id).'/'.$data->directorate_code))),	
		  array('data' => t(count($arr))),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->transaction_date)))),
		  array('data' => $link),
		);
	  }
	
	
	 $output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  
 return '<div class="formdvider viewlist">'.$output.'</div>';
}

function directorate_field_inbox_list(){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  $direc_code = getLoginUserDetailForAsset($user->uid);

  $ForwardList = directorateFieldForwardedList('F',$direc_code['directorate_code'],$direc_code['office_id']);  
  
  //$ForwardList = directorateForwardedListFromLD('F',$direc_code['directorate_code']);
  
  //print_r($ForwardList); exit;
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Directorate Name</b>')),	
	  array('data' => t('<b>Number of DoA Sent</b>')),
	  array('data' => t('<b>Date of DoA Forwarded</b>')),
	  array('data' => t('<b>PDF Link</b>')),
	);
	
	$i=0;
	  foreach($ForwardList as $data){
		$i++;
		$arr = explode(",",$data->asset_id);
		
		if(trim($data->directorate_code) == 'DB'){
			$directorate_name = 'Boilers';
		}elseif(trim($data->directorate_code) == 'LC'){
			$directorate_name = 'Labour Commissionerate';
		}elseif(trim($data->directorate_code) == 'DE'){
			$directorate_name = 'Directorate of Employment';
		}elseif(trim($data->directorate_code) == 'DF'){
			$directorate_name = 'Directorate of Factories';
		}elseif(trim($data->directorate_code) == 'ESI'){
			$directorate_name = 'Directorate of ESI (MB) Scheme';
		}elseif(trim($data->directorate_code) == 'LWB'){
			$directorate_name = 'Labour Welfare Board';
		}elseif(trim($data->directorate_code) == 'DEC'){
			$directorate_name = 'Directorate of Employees Compensation';
		}elseif(trim($data->directorate_code) == 'DIT'){
			$directorate_name = 'Directorate of Industrial Tribunal';
		}elseif(trim($data->directorate_code) == 'LD'){
			$directorate_name = 'Labour Department';
		}
		
		$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'bulkacknowledgement-print/'.$data->buld_pdf_link.'/'.$data->declaration_year, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));		
		$rows[] = array( 
		  array('data' => t(l($directorate_name, 'field-outbox-list/'.base64_encode($data->asset_id).'/'.$data->directorate_code))),	
		  array('data' => t(count($arr))),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->transaction_date)))),
		  array('data' => $link),
		);
	  }
	
	
	 $output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  
 return '<div class="formdvider viewlist">'.$output.'</div>';
}

function directorate_inbox_list(){
    global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}	
		 
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  $direc_code = getLoginUserDetailForAsset($user->uid);

  $ForwardList = directorateForwardedList('F',$direc_code['directorate_code']);  
  
  //$ForwardList = directorateForwardedListFromLD('F',$direc_code['directorate_code']);
  
  //print_r($ForwardList); exit;
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Directorate Name</b>')),	
	  array('data' => t('<b>Document No</b>')),
	  array('data' => t('<b>Number of DoA Sent</b>')),
	  array('data' => t('<b>Date of DoA Forwarded</b>')),
	  array('data' => t('<b>PDF Link</b>')),
	);
	
	$i=0;
	  foreach($ForwardList as $data){
		$i++;
		$arr = explode(",",$data->asset_id);
		
		if(trim($data->directorate_code) == 'DB'){
			$directorate_name = 'Boilers';
		}elseif(trim($data->directorate_code) == 'LC'){
			$directorate_name = 'Labour Commissionerate';
		}elseif(trim($data->directorate_code) == 'DE'){
			$directorate_name = 'Directorate of Employment';
		}elseif(trim($data->directorate_code) == 'DF'){
			$directorate_name = 'Directorate of Factories';
		}elseif(trim($data->directorate_code) == 'ESI'){
			$directorate_name = 'Directorate of ESI (MB) Scheme';
		}elseif(trim($data->directorate_code) == 'LWB'){
			$directorate_name = 'Labour Welfare Board';
		}elseif(trim($data->directorate_code) == 'DEC'){
			$directorate_name = 'Directorate of Employees Compensation';
		}elseif(trim($data->directorate_code) == 'DIT'){
			$directorate_name = 'Directorate of Industrial Tribunal';
		}elseif(trim($data->directorate_code) == 'LD'){
			$directorate_name = 'Labour Department';
		}
		
		$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'bulkacknowledgement-print/'.$data->buld_pdf_link.'/'.$data->declaration_year, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));		
		$rows[] = array( 
		  array('data' => t(l($directorate_name, 'groupA-outbox-list/'.base64_encode($data->asset_id).'/'.$data->directorate_code))),	
		  array('data' => $data->forwarding_no),
		  array('data' => t(count($arr))),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->transaction_date)))),
		  array('data' => $link),
		);
	  }
	
	
	 $output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  

	
 return '<div class="formdvider viewlist">'.$output.'</div>';	
}

function directorate_outbox_list(){	 
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  $direc_code = getLoginUserDetailForAsset($user->uid);

  //$ForwardList = directorateForwardedList('A',$direc_code['directorate_code']);
  
  $ForwardList = directorateListFromTransaction($direc_code['directorate_code']); 
  //print_r($ForwardList); exit;
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Directorate Name</b>')),
	  array('data' => t('<b>Document No</b>')),	
	  array('data' => t('<b>Number of DoA Sent</b>')),
	  array('data' => t('<b>Date of DoA Forwarded</b>')),
	  array('data' => t('<b>Status</b>')),
	  array('data' => t('<b>Remarks</b>')),
	  array('data' => t('<b>PDF Link</b>')),
	);
	
	$i=0;
	  foreach($ForwardList as $data){
		$i++;
		$arr = explode(",",$data->asset_id);
		if(trim($data->directorate_code) == 'DB'){
			$directorate_name = 'Boilers';
		}elseif(trim($data->directorate_code) == 'LC'){
			$directorate_name = 'Labour Commissionerate';
		}elseif(trim($data->directorate_code) == 'DE'){
			$directorate_name = 'Directorate of Employment';
		}elseif(trim($data->directorate_code) == 'DF'){
			$directorate_name = 'Directorate of Factories';
		}elseif(trim($data->directorate_code) == 'ESI'){
			$directorate_name = 'Directorate of ESI (MB) Scheme';
		}elseif(trim($data->directorate_code) == 'LWB'){
			$directorate_name = 'Labour Welfare Board';
		}elseif(trim($data->directorate_code) == 'DEC'){
			$directorate_name = 'Directorate of Employees Compensation';
		}elseif(trim($data->directorate_code) == 'DIT'){
			$directorate_name = 'Directorate of Industrial Tribunal';
		}elseif(trim($data->directorate_code) == 'LD'){
			$directorate_name = 'Labour Department';
		}
		
		if(trim($data->status) == 'F'){
			$status = 'Forwarded';
		}elseif(trim($data->status) == 'R'){
			$status = 'Rejected';
		}elseif(trim($data->status) == 'A'){
			$status = 'Accepted';
		}
		
		if(trim($data->remarks) == '1'){
			$remarks = 'Mutilated';
		}elseif(trim($data->status) == '2'){
			$remarks = 'Not Properly Sealed';
		}elseif(trim($data->status) == '3'){
			$remarks = 'Apparently Blank';
		}else{
			$remarks = 'N/A';
		}
		
		$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'bulkacknowledgement-received/'.$data->buld_pdf_link, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));		
		$rows[] = array( 
		  array('data' => t(l($directorate_name, 'groupA-outbox-detail/'.base64_encode($data->asset_id).'/'.$data->directorate_code))),	
		  array('data' => $data->forwarding_no),
		  array('data' => t(count($arr))),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->transaction_date)))),
		  array('data' => $status),
		  array('data' => $remarks),
		  array('data' => $link),
		);
	  }
	
	
	 $output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '<h3>DoA Sent List From Department to Directorates</h3>',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  

	
 return '<div class="formdvider viewlist">'.$output.'</div>';	
}



function directorate_display_list($form, &$form_state, $dcode) {
	
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}

 drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
 $direc_code = getLoginUserDetailForAsset($user->uid);
  
 $groupAlist = groupAofficer_list('F',$dcode);
  
    $header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Declaration Year  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Date of Acceptance  </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>View </b>')),
	 
	);
	
	$i=0;
	  foreach($groupAlist as $data){
		$i++;
		if($data->forward_status == 'F'){
			$status = "Forwarded From Directorate";
			$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$data->uid.'/'.$data->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
		}else{
			$status = "Not Submitted";
			$link = "";
		}
		
		$rows[] = array(  
		  array('data' => t($data->declaration_yr)),	
		  array('data' => t($data->fname)),
		  array('data' => t(date('d-m-Y H:i:s', strtotime($data->created_date)))),
		  array('data' => t($status)),
		  array('data' => t($link)),
		);
	  }
	
	
	 $form['table_data'] = array(
			'#type' => 'tableselect',
			//'#theme' => 'table',
			'#required' => TRUE,
			'#header' => $header,
			'#options' => $rows,
			//'#multiple' => FALSE,
			//'#default_value' => $selected_recipient_data,
			'#empty' => t('No users found'),
			'#attributes' => array('class' => array('table pretty table-bordered table-hover sticky-enabled')),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		);
		
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Generate Ack',
			'#attributes' => array('class'=>array('form-control btn btn-info')),
			'#prefix' => '<div class="col-md-2">',
			'#suffix' => '</div>'
		);
	return $form;
}


function backlog_doa_form($form, &$form_state){
	
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Receive Asset Declaration For Backlog</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	$form['decission_backlog'] = array(
		'#type' => 'hidden',
		'#title' => t('Decission'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Decission'),
		'#prefix' => '<div id="decission_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );  
	 
	$form['fname_backlog'] = array(
		'#type' => 'textfield',
		//'#autocomplete_path' => 'getassetuser/autocomplete',
		'#autocomplete_path' => 'getassetuser/autocompletebacklog',
		'#ajax' => array('event' => 'blur',
                      'callback' => '_reload_mem_order_list_backlog',
                      //'wrapper' => 'dropdown_product_cat',
                      'effect' => 'fade',
                      'progress' => array('type' => '','message' => '',),
                   ),
		'#title' => t('Enter Officers Name'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Officers Name'),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	 ); 
	
	
	
	$form['backlogdate'] = array(
		'#type' => 'textfield',
		'#title' => t('Choose Date'),
		//'#id' =>'order_no_map',
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control','backlogdate'),'placeholder'=>'Choose Date', 'autocomplete' => 'off'),
		'#prefix' => '<div id="order_no_map_backlog_date" style="display:none"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );
	  
	$form['uid_backlog'] = array(
		'#type' => 'hidden',
		'#title' => t('User Id Backlog'),
		//'#id' =>'order_no_map',
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('doc_name_clear','form-control'),'placeholder'=>'User Id Backlog'),
		'#prefix' => '<div id="order_no_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	$form['designation_backlog'] = array(
		'#type' => 'hidden',
		'#title' => t('Designation'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
		'#prefix' => '<div id="designation_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 ); 
	$form['district_backlog'] = array(
		'#type' => 'hidden',
		'#title' => t('District'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'District'),
		'#prefix' => '<div id="district_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	$form['directorate_backlog'] = array(
		'#type' => 'hidden',
		'#title' => t('Directorate'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Directorate'),
		'#prefix' => '<div id="directorate_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );  
	 $form['fetch_data_backlog'] = array(
		'#prefix' => '<div id="fetch_data_map_backlog"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );
	 
	 /*$form['submit_btn'] = array(
		'#prefix' => '<div id="fetch_data_map_submit"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );*/
	  $form['submit'] = array (
        '#type' => 'submit',
        '#value' => 'Accept',
		//'#attributes' => array('class'=>array('btn btn-primary')),
		/*'#prefix' => '<div class="col-md-12">',  
        '#suffix' => '</div>',*/
		//'#attributes' => array('class'=>array('btn btn-success pull-left'),'onclick' => 'this.form.target="_blank";return true;'),
		'#attributes' => array('class'=>array('btn btn-success pull-left')),
		'#prefix' => '<div id="frmbtn_backlog" style="display:none"><div class="col-md-3">',
  		'#suffix' => '</div></div>',
     ); 
	 
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	return $form; 
}


function backlog_doa_form_submit($form, &$form_state) {
	global $user;
	
	$bkdate = date('Y',strtotime($form_state['values']['backlogdate']));
	//echo $bkdate; exit; 
	
	if(trim($form_state['values']['decission_backlog']=='INSERT')){
	$officerInfo		=	array(
										'uid'						=> 	$form_state['values']['uid_backlog'],
										'declaration_yr'			=>	$bkdate,
										'designation'				=>  $form_state['values']['designation_backlog'],
										'directorate_code'			=>  $form_state['values']['directorate_backlog'],
										'district_code'				=>	!empty($form_state['values']['district_backlog'])?trim($form_state['values']['district_backlog']):'',
										'document_no'  				=>  '',
										'created_date' 			 	=>  date('Y-m-d',strtotime($form_state['values']['backlogdate'])), 
										'status'  					=>  '1',
										'operator_uid'  			=>  $user->uid,
								);
   
 //print_r($officerInfo); exit;
   db_insert('a_asset_mst')->fields($officerInfo)->execute();
	}else if(trim($form_state['values']['decission_backlog']=='UPDATE')){
		
		$query = db_update('a_asset_mst');
		$query->fields(array('created_date' =>  date('Y-m-d',strtotime($form_state['values']['backlogdate'])),  'status'  =>  '1', 'operator_uid'  =>  $user->uid));
		$query->condition('uid', trim($form_state['values']['uid_backlog']), '=');
		$query->condition('declaration_yr', date('Y'), '=');
		$rs = $query->execute();
	}
   //print_r($query); exit;
   drupal_set_message('Application for officer '.$form_state['values']['fname'].' has been successfully accepted. '.l('PRINT ACKNOWLEDGEMENT','acknowledgement-print/'.$form_state['values']['uid_backlog'].'/'.date('Y'), array('html' => TRUE,'attributes'=>array('target'=>'_blank'))));
   //drupal_goto('acknowledgement-print');
	
}

function _reload_mem_order_list_backlog($form, $form_state) {
 drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
 $commands   = array();
 //echo $form_state['values']['fname']; exit;
 $user_arr = explode('-',$form_state['values']['fname_backlog']);
 
 //print_r($mydata);
 $verify = getVerifyByUidYear($user_arr[1],date('Y'));
 
 
	$header = array();
	$rows   = array();
	
	$header = array(  
	  array('data' => t('Employee Information'),'colspan' => 4),  
	);
 
 if(!empty($verify) && $verify['status']==1){
	 
	 $rows[] = array( 
	  array('data' => t('You have already submitted asset for this year'),'colspan' => 4),
	);
	 
	 $rows[] = array( 
	  array('data' => l('<strong class="btn btn-danger print-btn"> Print Acknowlwdgement</strong>','acknowledgement-print/'.$user_arr[1].'/'.$verify['declaration_yr'], array('html' => TRUE,'attributes'=>array('target'=>'_blank'))) ,'colspan' => 4),
	);
	 
	
 }else{
	 
	 $mydata = getUserInfoByUid($user_arr[1]);
 
	 $form['uid_backlog']['#value'] = $user_arr[1];
	 $form['designation_backlog']['#value'] = $mydata['designation'];
	 $form['directorate_backlog']['#value'] = $mydata['directorate_code'];
	 $form['district_backlog']['#value'] = $mydata['district_code'];
	 if(!empty($verify) && $verify['status']==0){
		 $form['decission_backlog']['#value'] = 'UPDATE';
	 }else{
		 $form['decission_backlog']['#value'] = 'INSERT';
	 }
	 
	 
	 
		
	
	$rows[] = array(  
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	  array('data' => t('<b>Directorate Name  </b>')),
	  array('data' => t('<b>District Name  </b>')),
	);
	$rows[] = array( 
	  array('data' => t($mydata['fname'])),
	  array('data' => t($mydata['designation'])), 	 
	  array('data' => t($mydata['directorate_name'])), 
	  array('data' => t($mydata['district_name'])),
	);
 }
	
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
  
 //$commands[] = ajax_command_invoke('.doc_name_clear', 'val', array($form['values']['fname']));
 $commands[] = ajax_command_replace('#order_no_map_backlog', '<div id="order_no_map_backlog">'.drupal_render($form['uid_backlog']).'</div>');
 $commands[] = ajax_command_replace('#designation_map_backlog', '<div id="designation_map_backlog">'.drupal_render($form['designation_backlog']).'</div>');
 $commands[] = ajax_command_replace('#directorate_map_backlog', '<div id="directorate_map_backlog">'.drupal_render($form['directorate_backlog']).'</div>');
 $commands[] = ajax_command_replace('#district_map_backlog', '<div id="district_map_backlog">'.drupal_render($form['district_backlog']).'</div>');
 $commands[] = ajax_command_replace('#fetch_data_map_backlog', '<div id="fetch_data_map_backlog"><div class="col-md-12">'.$output.'</div></div>');
 $commands[] = ajax_command_replace('#decission_map_backlog', '<div id="decission_map_backlog">'.drupal_render($form['decission_backlog']).'</div>');
//print_r($commands);
 if(!empty($verify) && $verify['status']==1){
	$commands[] = ajax_command_invoke('#frmbtn_backlog', 'hide');
	$commands[] = ajax_command_invoke('#order_no_map_backlog_date', 'hide');
 }else{
 	$commands[] = ajax_command_invoke('#frmbtn_backlog', 'show');
	$commands[] = ajax_command_invoke('#order_no_map_backlog_date', 'show');
	
 }
 
 return array('#type' => 'ajax', '#commands' => $commands);
}

function backlog_doa_all_form($form, &$form_state){
	
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Receive Asset Declaration For Backlog All</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	/*$form['decission_backlog'] = array(
		'#type' => 'hidden',
		'#title' => t('Decission'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Decission'),
		'#prefix' => '<div id="decission_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );*/  
	 
	$form['fname_backlog'] = array(
		'#type' => 'textfield',
		//'#autocomplete_path' => 'getassetuser/autocomplete',
		'#autocomplete_path' => 'getassetuser/autocompletebacklog',
		'#ajax' => array('event' => 'blur',
                      'callback' => '_reload_mem_order_list_backlog_all',
                      //'wrapper' => 'dropdown_product_cat',
                      'effect' => 'fade',
                      'progress' => array('type' => '','message' => '',),
                   ),
		'#title' => t('Enter Officers Name'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Officers Name'),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	 ); 
	
	
	/*$years = array(
	  '2018' => t('2018'),
	  '2017' => t('2017'), 
	  '2016' => t('2016'),
	  '2015' => t('2015'),
	  '2014' => t('2014'),
	  '2013' => t('2013'),
	  '2012' => t('2012'),
	  '2011' => t('2011'),
	  '2010' => t('2010'),
	  '2009' => t('2009'),
	);*/
	$years = array_combine(range(date('Y'),date('Y')-10), range(date('Y'),date('Y')-10));
	
	if($form_state['values']['fname_backlog']!=""){
	 //echo "-->".$form_state['values']['fname_backlog']; exit;
	 $submittedYear = array();
	 $user_arr = explode('-',$form_state['values']['fname_backlog']);
	 foreach($years as $k=>$y){
		 //echo "-->>".$k; die();
		 $getInfo = array();
		 $getInfo = getAssetDataWithYearStatusUID($k,$user_arr[1],'1');
		 if(!empty($getInfo)){
			 $submittedYear[] = $k; 
			 unset($years[$k]);
		 }
	 }
	
	//print_r($submittedYear); die;
	 
	$form['backlogyear'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Choose Year'),
		//'#id' =>'order_no_map',
		//'#value'=>'',
		//'#default_value'=>$submittedYear,
		'#options' => $years,
		'#required' => TRUE,
		'#attributes' => array('class'=>array('checkbox-inline','checkbox-row'),'placeholder'=>'Choose Year', 'autocomplete' => 'off'),
		'#prefix' => '<div class="year_list"><div id="order_no_map_backlog_date"><div class="col-md-12 container">',
		'#suffix' => '</div></div></div>'
	 );
	 
	}
	
	$form['backlogyear_blank'] = array(
		'#prefix' => '<div class="year_list"><div id="order_no_map_backlog_date"><div class="col-md-12 container">',
		'#suffix' => '</div></div></div>'
	);
	  
	$form['uid_backlog'] = array(
		'#type' => 'hidden',
		'#title' => t('User Id Backlog'),
		//'#id' =>'order_no_map',
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('doc_name_clear','form-control'),'placeholder'=>'User Id Backlog'),
		'#prefix' => '<div id="order_no_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	$form['designation_backlog'] = array(
		'#type' => 'hidden',
		'#title' => t('Designation'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
		'#prefix' => '<div id="designation_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 ); 
	$form['district_backlog'] = array(
		'#type' => 'hidden',
		'#title' => t('District'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'District'),
		'#prefix' => '<div id="district_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	$form['directorate_backlog'] = array(
		'#type' => 'hidden',
		'#title' => t('Directorate'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Directorate'),
		'#prefix' => '<div id="directorate_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );  
	 $form['fetch_data_backlog'] = array(
		'#prefix' => '<div id="fetch_data_map_backlog"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );
	 
	 /*$form['submit_btn'] = array(
		'#prefix' => '<div id="fetch_data_map_submit"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );*/
	  $form['submit'] = array (
        '#type' => 'submit',
        '#value' => 'Accept',
		//'#attributes' => array('class'=>array('btn btn-primary')),
		/*'#prefix' => '<div class="col-md-12">',  
        '#suffix' => '</div>',*/
		//'#attributes' => array('class'=>array('btn btn-success pull-left'),'onclick' => 'this.form.target="_blank";return true;'),
		'#attributes' => array('class'=>array('btn btn-success pull-left')),
		'#prefix' => '<div id="frmbtn_backlog" style="display:none"><div class="col-md-3">',
  		'#suffix' => '</div></div>',
     ); 
	 
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	return $form; 
}

function _reload_mem_order_list_backlog_all($form, $form_state) {
 drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
 $commands   = array();
 //echo $form_state['values']['fname']; exit;
 $user_arr = explode('-',$form_state['values']['fname_backlog']);
 
 //print_r($mydata);
 //$verify = getVerifyByUidYear($user_arr[1],date('Y'));
 
 
	$header = array();
	$rows   = array();
	
	$header = array(  
	  array('data' => t('Employee Information'),'colspan' => 5),  
	);
 
 /*if(!empty($verify) && $verify['status']==1){
	 
	 $rows[] = array( 
	  array('data' => t('You have already submitted asset for this year'),'colspan' => 4),
	);
	 
	 $rows[] = array( 
	  array('data' => l('<strong class="btn btn-danger print-btn"> Print Acknowlwdgement</strong>','acknowledgement-print/'.$user_arr[1].'/'.$verify['declaration_yr'], array('html' => TRUE,'attributes'=>array('target'=>'_blank'))) ,'colspan' => 4),
	);
	 
	
 }else{*/
	 
	 $mydata = getUserInfoByUid($user_arr[1]);
 
	 $form['uid_backlog']['#value'] = $user_arr[1];
	 $form['designation_backlog']['#value'] = $mydata['designation'];
	 $form['directorate_backlog']['#value'] = $mydata['directorate_code'];
	 $form['district_backlog']['#value'] = $mydata['district_code'];
	 /*if(!empty($verify) && $verify['status']==0){
		 $form['decission_backlog']['#value'] = 'UPDATE';
	 }else{
		 $form['decission_backlog']['#value'] = 'INSERT';
	 }*/
	 
	 
	 
		
	
	$rows[] = array(  
	  array('data' => t('<b>HRMS ID  </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	  array('data' => t('<b>Directorate Name  </b>')),
	  array('data' => t('<b>District Name  </b>')),
	);
	$rows[] = array( 
	  array('data' => t($mydata['hrms_id'])),	
	  array('data' => t($mydata['fname'])),
	  array('data' => t($mydata['designation'])), 	 
	  array('data' => t($mydata['directorate_name'])), 
	  array('data' => t($mydata['district_name'])),
	);
 //}
	
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
  
 //$commands[] = ajax_command_invoke('.doc_name_clear', 'val', array($form['values']['fname']));
 $commands[] = ajax_command_replace('#order_no_map_backlog', '<div id="order_no_map_backlog">'.drupal_render($form['uid_backlog']).'</div>');
 $commands[] = ajax_command_replace('#designation_map_backlog', '<div id="designation_map_backlog">'.drupal_render($form['designation_backlog']).'</div>');
 $commands[] = ajax_command_replace('#directorate_map_backlog', '<div id="directorate_map_backlog">'.drupal_render($form['directorate_backlog']).'</div>');
 $commands[] = ajax_command_replace('#district_map_backlog', '<div id="district_map_backlog">'.drupal_render($form['district_backlog']).'</div>');
 $commands[] = ajax_command_replace('#fetch_data_map_backlog', '<div id="fetch_data_map_backlog"><div class="col-md-12">'.$output.'</div></div>');
 //$commands[] = ajax_command_replace('#decission_map_backlog', '<div id="decission_map_backlog">'.drupal_render($form['decission_backlog']).'</div>');
 $commands[] = ajax_command_replace('#order_no_map_backlog_date', '<div id="order_no_map_backlog_date">'.drupal_render($form['backlogyear']).'</div>');
 $commands[] = ajax_command_invoke('#frmbtn_backlog', 'show');
 //$commands[] = ajax_command_invoke('#order_no_map_backlog_date', 'show');
 
//print_r($commands);
 /*if(!empty($verify) && $verify['status']==1){
	$commands[] = ajax_command_invoke('#frmbtn_backlog', 'hide');
	$commands[] = ajax_command_invoke('#order_no_map_backlog_date', 'hide');
 }else{
 	$commands[] = ajax_command_invoke('#frmbtn_backlog', 'show');
	$commands[] = ajax_command_invoke('#order_no_map_backlog_date', 'show');
 }*/
 
 return array('#type' => 'ajax', '#commands' => $commands);
}

function backlog_doa_all_form_submit($form, &$form_state) {
	global $user;
	
	$user_arr = explode('-',$form_state['values']['fname_backlog']);
	//print_r($form_state['values']); exit;
	
	//$bkdate = date('Y',strtotime($form_state['values']['backlogyear']));
	//echo $bkdate; exit; 
	
	//if(trim($form_state['values']['decission_backlog']=='INSERT')){
	foreach($form_state['values']['backlogyear'] as $k=>$y){
		if($k == $y){
			$d = $y.'-04-30';
				
			$officerInfo =	array(
								'uid'						=> 	$form_state['values']['uid_backlog'],
								'declaration_yr'			=>	$y,
								'designation'				=>  $form_state['values']['designation_backlog'],
								'directorate_code'			=>  $form_state['values']['directorate_backlog'],
								'district_code'				=>	!empty($form_state['values']['district_backlog'])?trim($form_state['values']['district_backlog']):'',
								'document_no'  				=>  '',
								'created_date' 			 	=>  date($d), //date('Y-m-d'), 
								'status'  					=>  '1',
								'operator_uid'  			=>  $user->uid,
							);
		   //print_r($officerInfo); exit;
		   db_insert('a_asset_mst')->fields($officerInfo)->execute();
		}
	}
	/*}else if(trim($form_state['values']['decission_backlog']=='UPDATE')){
		
		$query = db_update('a_asset_mst');
		$query->fields(array('created_date' =>  date('Y-m-d',strtotime($form_state['values']['backlogdate'])),  'status'  =>  '1', 'operator_uid'  =>  $user->uid));
		$query->condition('uid', trim($form_state['values']['uid_backlog']), '=');
		$query->condition('declaration_yr', date('Y'), '=');
		$rs = $query->execute();
	}*/
   //print_r($query); exit;
   drupal_set_message('Application for officer '.$user_arr[0].' has been successfully accepted');
   //drupal_set_message('Application for officer '.$form_state['values']['fname'].' has been successfully accepted. '.l('PRINT ACKNOWLEDGEMENT','acknowledgement-print/'.$form_state['values']['uid_backlog'].'/'.date('Y'), array('html' => TRUE,'attributes'=>array('target'=>'_blank'))));
   //drupal_goto('acknowledgement-print');
	
}