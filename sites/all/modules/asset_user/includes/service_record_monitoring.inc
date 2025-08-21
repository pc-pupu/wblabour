<?php

function service_record_monitoring($form, &$form_state){ 
		
	global $user;
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');	
	$status = getUserProfileStatus($user->uid);
	$userData = getLoginUserDetailForAsset($user->uid);
	
	$directorate_list = getDirectorateListByRoleId($user->uid);
	//print_r($directorate_list); exit;
	$district_list = getDistrictAllList();
	
	$servicegeninfo = array();
	
	$servicegeninfo = servicegeninfo($user->uid);
	
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">General Service Details</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
	 /*$form['fname'] = array(
	  '#title' => t('Full Name'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#default_value' => !empty($userData['fname']) ? $userData['fname'] : '',
	  '#attributes' => array('class'=>array('form-control'),'readonly'=>'readonly'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['hrmsid'] = array(
	  '#title' => t('HRMS ID'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#default_value' => !empty($userData['hrms_id']) ? $userData['hrms_id'] : '',
	  '#attributes' => array('class'=>array('form-control'),'readonly'=>'readonly'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );*/
	
	$form['service_cadre'] = array(
	  '#title' => t('Service/Cadre'),	
	  '#type' => 'select',
	  '#required' => TRUE,
	  '#disabled' => !empty($servicegeninfo['sservice_cadre']) ? TRUE : FALSE,
	  '#options' => array('1'=>t('WBES'),'2'=>t('WBLS'),'3'=>t('Others')),
	  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
	  '#default_value' => !empty($servicegeninfo['sservice_cadre']) ? $servicegeninfo['sservice_cadre'] : '',
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	$form['doj'] = array(
	  '#title' => t('Date of Joining (DD-MM-YYYY)'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#default_value' => !empty($userData['doj']) ? date('d-m-Y',strtotime($userData['doj'])) : '',
	  '#attributes' => array('class'=>array('form-control'),'readonly'=>'readonly'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	$form['confirmation_date'] = array(
	  '#title' => t('Date of Confirmation (DD-MM-YYYY)'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#default_value' => !empty($servicegeninfo['s_confirmdate']) ? date('d-m-Y',strtotime($servicegeninfo['s_confirmdate'])) : '',
	  '#disabled' => !empty($servicegeninfo['s_confirmdate']) ? TRUE : FALSE,
	  '#attributes' => array('class'=>array('form-control', 'servicedate'),'placeholder'=>'Date of Confirmation (DD-MM-YYYY)','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	$form['dob'] = array(
	  '#title' => t('Date of Birth (DD-MM-YYYY)'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#default_value' => !empty($userData['dob']) ? date('d-m-Y',strtotime($userData['dob'])) : '',
	  '#attributes' => array('class'=>array('form-control'),'readonly'=>'readonly',),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	$form['recruitment_type'] = array(
	  '#title' => t('Type of Recruitment'),	
	  '#type' => 'select',
	  '#ajax' => array(
                      'callback' => '_reload_recruitment_type',
                      //'wrapper' => 'dropdown_product_cat',
                      //'effect' => 'fade',
                      //'progress' => array('type' => '','message' => '',),
                   ),
	  '#required' => TRUE,
	  '#options' => array('Direct'=>t('Direct'),'On Promotion'=>t('On Promotion')),
	  '#disabled' => !empty($servicegeninfo['s_recruitmenttype']) ? TRUE : FALSE,
	  '#default_value' => !empty($servicegeninfo['s_recruitmenttype']) ? $servicegeninfo['s_recruitmenttype'] : '',
	  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	if(isset($form_state['values']['recruitment_type']) && trim($form_state['values']['recruitment_type'])=='On Promotion'){
		$form['promotion_doj'] = array(
		  '#title' => t('Promotion Date of Joining (DD-MM-YYYY)'),	
		  '#type' => 'textfield',
		  '#required' => TRUE,
		  '#default_value' => !empty($servicegeninfo['s_promotion_doj']) ? date('d-m-Y',strtotime($servicegeninfo['s_promotion_doj'])) : '',
		  '#attributes' => array('class'=>array('form-control', 'datepiker'),'placeholder'=>'Promotion Date of Joining (DD-MM-YYYY)','autocomplete'=>'off'),
		  '#prefix' => '<div id="replace_promotion_doj_div"><div class="col-md-4">',
		  '#suffix' => '</div></div>'
		);
	}else if(!empty($servicegeninfo['s_promotion_doj'])){
		$form['promotion_doj'] = array(
		  '#title' => t('Promotion Date of Joining (DD-MM-YYYY)'),	
		  '#type' => 'textfield',
		  '#required' => TRUE,
		  '#disabled' => !empty($servicegeninfo['s_promotion_doj']) ? TRUE : FALSE,
		  '#default_value' => !empty($servicegeninfo['s_promotion_doj']) ? date('d-m-Y',strtotime($servicegeninfo['s_promotion_doj'])) : '',
		  '#attributes' => array('class'=>array('form-control', 'datepiker'),'placeholder'=>'Promotion Date of Joining (DD-MM-YYYY)','autocomplete'=>'off'),
		  '#prefix' => '<div id="replace_promotion_doj_div"><div class="col-md-4">',
		  '#suffix' => '</div></div>'
		);
	}else{
		$form['promotion_doj'] = array(
		  '#prefix' => '<div id="replace_promotion_doj_div">',
		  '#suffix' => '</div>'
		);
	} 
	$form['gender'] = array(
	  '#title' => t('Gender'),	
	  '#type' => 'select',
	  '#required' => TRUE,
	  '#options' => array('1'=>t('Male'),'2'=>t('Female')),
	  '#disabled' => !empty($servicegeninfo['s_gender']) ? TRUE : FALSE,
	  '#default_value' => !empty($servicegeninfo['s_gender']) ? $servicegeninfo['s_gender'] : '',
	  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	
	
	/*$form['district'] = array(
	  '#title' => t('District'),	
	  '#type' => 'select',
	  '#required' => TRUE,
	  '#id'=>'district_name',
	  '#options' => get_district_by_id(1),
      '#value' => !empty($district_v) ? $district_v	:'',
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4">',
	  '#suffix' => '</div></div>',
	  '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					   )
    );
	
  $value_district	=	isset($form_state['values']['district']) ? $form_state['values']['district'] : '';	
	
  if(!empty($value_district) && $state_v == 1){
	$form['subdivision'] = array(
	  '#title' => t('Sub-Division'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#options' => common_custom_user_subdivisionlist_list_new($form_state['values']['district']),
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    );
  }else{ 
		
		$form['subdivision'] = array(
		   '#prefix' => '<div id="ld_empsubdv_replace">',
		   '#suffix' => '</div>',
		);
  }*/
  
  if(empty($servicegeninfo)) {
	$form['submit'] = array(
	  '#type'=>'submit',
	  '#value'=> t('Submit'),
	  '#attributes' => array('class'=>array('form-control btn btn-info')),
	  '#prefix' => '<div class="col-md-12"><div class="input-group">',
	  '#suffix' => '</div></div>'
	);	
  }
	
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	
	return $form;

}

function _reload_recruitment_type($form, &$form_state){
	$commands   = array();
	$commands[] = ajax_command_replace('#replace_promotion_doj_div', '<div id="replace_promotion_doj_div">'.drupal_render($form['promotion_doj']).'</div>');
	$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
 	return array('#type' => 'ajax', '#commands' => $commands);
}

function service_record_monitoring_submit($form, &$form_state){
	global $user;
	
	if($form_state['values']['gender'] = '1') {
		  $gender = 'M';
		}else { $gender = 'F'; }
	
	$servicegeninfo = array();
	
	$servicegeninfo = servicegeninfo($user->uid);
	

	/*if(!empty($servicegeninfo)) {
		if(trim($form_state['values']['recruitment_type'])=='On Promotion') {
			$query = db_update('a_service_info');
			$query->fields(array(
							'sservice_cadre'	 => trim($form_state['values']['service_cadre']),
							's_doj'				 => format_date(strtotime($form_state['values']['doj']), 'custom', 'Y-m-d'),
							's_confirmdate' 	 => format_date(strtotime($form_state['values']['confirmation_date']), 'custom', 'Y-m-d'),
							's_dob'				 => format_date(strtotime($form_state['values']['dob']), 'custom', 'Y-m-d'),
							's_recruitmenttype'	 => trim($form_state['values']['recruitment_type']),
							's_promotion_doj'	 => trim($s_promotion_doj),
							's_gender'			 => trim($gender),
							//'s_status'			 => 1,
						 ));
			$query->condition('s_uid', $user->uid);
			$rs = $query->execute();
		
		}
		else {
				$query = db_update('a_service_info');
				$query->fields(array(
							'sservice_cadre'	 => trim($form_state['values']['service_cadre']),
							's_doj'				 => format_date(strtotime($form_state['values']['doj']), 'custom', 'Y-m-d'),
							's_confirmdate' 	 => format_date(strtotime($form_state['values']['confirmation_date']), 'custom', 'Y-m-d'),
							's_dob'				 => format_date(strtotime($form_state['values']['dob']), 'custom', 'Y-m-d'),
							's_recruitmenttype'	 => trim($form_state['values']['recruitment_type']),
							's_gender'			 => trim($gender),
						 ));
				$query->condition('s_uid', $user->uid);
				$rs = $query->execute();
			
			}
	} 
	else {*/
	if(trim($form_state['values']['recruitment_type'])=='On Promotion')
		{
			$s_promotion_doj = format_date(strtotime($form_state['values']['promotion_doj']), 'custom', 'Y-m-d'); 
			
			$service_info = array(
							's_uid'				 => $user->uid,
							//'sfull_name'		 => trim($form_state['values']['fname']),
							//'s_hrms_id'			 => trim($form_state['values']['hrmsid']),
							'sservice_cadre'	 => trim($form_state['values']['service_cadre']),
							's_doj'				 => format_date(strtotime($form_state['values']['doj']), 'custom', 'Y-m-d'),
							's_confirmdate' 	 => format_date(strtotime($form_state['values']['confirmation_date']), 'custom', 'Y-m-d'),
							's_dob'				 => format_date(strtotime($form_state['values']['dob']), 'custom', 'Y-m-d'),
							's_recruitmenttype'	 => trim($form_state['values']['recruitment_type']),
							's_promotion_doj'	 => trim($s_promotion_doj),
							's_gender'			 => trim($gender),
							's_status'			 => 1,
						 );
		
		$service_info_details = db_insert('a_service_info')->fields($service_info)->execute();
		if($service_info_details){
			 drupal_set_message('Your Record has been inserted successfully.');
			 drupal_goto('servicerecord/eduqaulification');
		}else{
			drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
		}
		
		}else { 
				
				$service_info = array(
									's_uid'				 => $user->uid,
									//'sfull_name'		 => trim($form_state['values']['fname']),
									//'s_hrms_id'			 => trim($form_state['values']['hrmsid']),
									'sservice_cadre'	 => trim($form_state['values']['service_cadre']),
									's_doj'				 => format_date(strtotime($form_state['values']['doj']), 'custom', 'Y-m-d'),
									's_confirmdate' 	 => format_date(strtotime($form_state['values']['confirmation_date']), 'custom', 'Y-m-d'),
									's_dob'				 => format_date(strtotime($form_state['values']['dob']), 'custom', 'Y-m-d'),
									's_recruitmenttype'	 => trim($form_state['values']['recruitment_type']),
									's_gender'			 => trim($gender),
									's_status'			 => 1,
								 );
				
				$service_info_details = db_insert('a_service_info')->fields($service_info)->execute();
				if($service_info_details){
					 drupal_set_message('Your Record has been inserted successfully.');
					 drupal_goto('servicerecord/eduqaulification');
				}else{
					drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
				}
		
		}	
	/*}*/
	
}

function eduqaul_form_entry($form, &$form_state){ 

   	global $user;
   	$status = getUserProfileStatus($user->uid);
	$userData = getLoginUserDetailForAsset($user->uid);
	$getServiceInfoId = getServiceInfoId($user->uid);

	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Educational Qualification</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	$form['qualification'] = array(
	  '#title' => t('Exam Passed'),	
	  '#type' => 'select',
	  '#options' => array('Under Graduate'=>t('Under Graduate'),'Graduate'=>t('Graduate'),'Post Graduate'=>t('Post Graduate'),'PhD'=>t('PhD'),'Other'=>t('Other')),
	  '#ajax' => array(
                      'callback' => 'qualification_callback',
                   ),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	if(isset($form_state['values']['qualification']) && trim($form_state['values']['qualification'])=='Under Graduate'){
		$form['under_graduate_type'] = array(
		  '#title' => t('Under Graduate Type'),	
		  '#type' => 'select',
		  '#options' => array('Madhyamik or Equivalent'=>t('Madhyamik or Equivalent'),'Higher Secondary or Equivalent'=>t('Higher Secondary or Equivalent'),'Diploma'=>t('Diploma'),'Others'=>t('Others')),
		  /*'#ajax' => array(
						  'callback' => 'qualification_callback',
					   ),*/
		  '#required' => TRUE,
		  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
		  '#prefix' => '<div id="replace_under_graduate_type"><div class="col-md-4">',
		  '#suffix' => '</div></div>'
		);
	}else{
		$form['under_graduate_type'] = array(
		  '#prefix' => '<div id="replace_under_graduate_type">',
		  '#suffix' => '</div>'
		);
	}
	
	if(isset($form_state['values']['qualification']) && (trim($form_state['values']['qualification'])=='Graduate') || (trim($form_state['values']['qualification'])=='Post Graduate')){
		$form['graduate_type'] = array(
		  '#title' => t('Type'),	
		  '#type' => 'select',
		  '#options' => array('Technical'=>t('Technical'),'Non-Technical'=>t('Non-Technical')),
		  '#ajax' => array(
						  'callback' => 'graduate_type_callback',
					   ),
		  '#required' => TRUE,
		  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
		  '#prefix' => '<div id="replace_graduate_type"><div class="col-md-4">',
		  '#suffix' => '</div></div>'
		);
	}else{
		$form['graduate_type'] = array(
		  '#prefix' => '<div id="replace_graduate_type">',
		  '#suffix' => '</div>'
		);
	}
	
	if( isset($form_state['values']['qualification']) && (trim($form_state['values']['qualification'])=='Graduate' || trim($form_state['values']['qualification'])=='Post Graduate') && isset($form_state['values']['graduate_type']) && trim($form_state['values']['graduate_type'])=='Technical'){
		$form['technical_type'] = array(
		  '#title' => t('Technical Type'),	
		  '#type' => 'select',
		  '#options' => array('Engineering'=>t('Engineering'),'Medical'=>t('Medical'),'Management'=>t('Management'),'Others'=>t('Others')),
		  /*'#ajax' => array(
						  'callback' => 'graduate_type_callback',
					   ),*/
		  '#required' => TRUE,
		  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
		  '#prefix' => '<div id="replace_technical_type"><div class="col-md-4">',
		  '#suffix' => '</div></div>'
		);
	}else{
		$form['technical_type'] = array(
		  '#prefix' => '<div id="replace_technical_type">',
		  '#suffix' => '</div>'
		);
	}
	
	if(isset($form_state['values']['qualification']) && (trim($form_state['values']['qualification'])=='Graduate' || trim($form_state['values']['qualification'])=='Post Graduate') && isset($form_state['values']['graduate_type']) && trim($form_state['values']['graduate_type'])=='Non-Technical'){
		$form['non_technical_type'] = array(
		  '#title' => t('Non-Technical Type'),	
		  '#type' => 'select',
		  '#options' => array('Science'=>t('Science'),'Arts'=>t('Arts'),'Commerce'=>t('Commerce')),
		  /*'#ajax' => array(
						  'callback' => 'graduate_type_callback',
					   ),*/
		  '#required' => TRUE,
		  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
		  '#prefix' => '<div id="replace_non_technical_type"><div class="col-md-4">',
		  '#suffix' => '</div></div>'
		);
	}else{
		$form['non_technical_type'] = array(
		  '#prefix' => '<div id="replace_non_technical_type">',
		  '#suffix' => '</div>'
		);
	}
	/*$form['madhyamik'] = array(
	  '#title' => t('Madhyamik or Equivalent'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Madhyamik or Equivalent'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	$form['higher_secondary'] = array(
	  '#title' => t('Higher Secondary or Equivalent'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Higher Secondary or Equivalent'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	$form['diploma'] = array(
	  '#title' => t('Diploma'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Diploma'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['others'] = array(
	  '#title' => t('Others'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Others'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );*/
	
	if(isset($form_state['values']['qualification']) && trim($form_state['values']['qualification'])=='Other'){
		$form['others'] = array(
		  '#title' => t('Other'),	
		  '#type' => 'textfield',
		  '#required' => TRUE,
		  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Other','autocomplete'=>'off'),
		  '#prefix' => '<div id="replace_others_type"><div class="col-md-4">',
		  '#suffix' => '</div></div>'
    );
	}else{
		$form['others_type'] = array(
		  '#prefix' => '<div id="replace_others_type">',
		  '#suffix' => '</div>'
		);
	}
	
	$form['universityins'] = array(
	  '#title' => t('University/Institute'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	/*$form['subject'] = array(
	  '#title' => t('Subject'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );*/
	
	$form['division'] = array(
	  '#title' => t('Division'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	
	$form['submit'] = array(
	  '#type'=>'submit',
	  '#value'=> t('Add'),
	  '#attributes' => array('class'=>array('form-control btn btn-info')),
	  '#prefix' => '<div class="col-md-12"><div class="input-group">',
	  '#suffix' => '</div></div>'
	);	
	
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	
	$form['edutable'] = array(
	  '#prefix' => '<div class="col-md-12">'.edutable(),
	  '#suffix' => '</div>'
    );

	return $form;
}

function qualification_callback($form, &$form_state){
	$commands   = array();
	$commands[] = ajax_command_replace('#replace_under_graduate_type', '<div id="replace_under_graduate_type">'.drupal_render($form['under_graduate_type']).'</div>');
	$commands[] = ajax_command_replace('#replace_graduate_type', '<div id="replace_graduate_type">'.drupal_render($form['graduate_type']).'</div>');
	$commands[] = ajax_command_replace('#replace_technical_type', '<div id="replace_technical_type">'.drupal_render($form['technical_type']).'</div>');
	$commands[] = ajax_command_replace('#replace_non_technical_type', '<div id="replace_non_technical_type">'.drupal_render($form['non_technical_type']).'</div>');
	$commands[] = ajax_command_replace('#replace_others_type', '<div id="replace_others_type">'.drupal_render($form['others']).'</div>');
	//$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
 	return array('#type' => 'ajax', '#commands' => $commands);
}

function graduate_type_callback($form, &$form_state){
	$commands   = array();
	$commands[] = ajax_command_replace('#replace_technical_type', '<div id="replace_technical_type">'.drupal_render($form['technical_type']).'</div>');
	$commands[] = ajax_command_replace('#replace_non_technical_type', '<div id="replace_non_technical_type">'.drupal_render($form['non_technical_type']).'</div>');
	//$commands[] = ajax_command_replace('#replace_graduate_type', '<div id="replace_graduate_type">'.drupal_render($form['graduate_type']).'</div>');
	//$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
 	return array('#type' => 'ajax', '#commands' => $commands);
}


function edutable(){
	global $user;
	$getServiceInfoId = getServiceInfoId($user->uid);
	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$edu = educationinfo($user->uid);
	
	$output = '';
	
  	$header = array(
				array('data'=> 'Sl No.'),
				array('data'=> 'Qualification'),
				array('data'=> 'Under Graduation Type'),
				array('data'=> 'Graduation/Post Graduation Type'),
				array('data'=> 'Technical Type'),
				array('data'=> 'Non Technical Type'),
				array('data'=> 'University/Institute'),
				array('data'=> 'Division'),
				array('data'=> 'Action'),
			);
			
	$rows = array();
	
	
	$i = 0;
	/*if(!empty($resultData)){
	foreach($resultData as $val){*/
	if(!empty($edu)){
	foreach($edu as $val){
		$i++;
		 $editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'service/eduedit/'.$val->s_edu_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','service/edudel/'.$val->s_edu_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  $rows [] = array(  
	 		  $i,
	  		  array('data' => t($val->s_qual)),
			  array('data' => t($val->s_qual_type)),
			  array('data' => t($val->s_graduate_type)),
			  array('data' => t($val->s_technicaltype)),
			  array('data' => t($val->s_nontechnicaltype)),
			  array('data' => t($val->s_univ)), 
			  array('data' => t($val->s_division)),
			  //array('data' => ($val->landacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->landacquistion_date))) : 'N/A'),
			  array('data' => $editLink.' '.$delLink),			
		); 
	}
  }
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	
	return $output;	
	
	
}

function eduqaul_form_entry_submit($form, &$form_state){  

    global $user;
	$getServiceInfoId = getServiceInfoId($user->uid);
	
	$eduqaul_info = array( 
							's_uid' 	 	  	 => $user->uid,
							's_qual' 	 	  	 => trim($form_state['values']['qualification']),
							's_qual_type' 	 	 => trim($form_state['values']['under_graduate_type']),
							's_graduate_type'  	 => trim($form_state['values']['graduate_type']),
							's_technicaltype' 	 => trim($form_state['values']['technical_type']),
							's_nontechnicaltype' => trim($form_state['values']['non_technical_type']),
							's_univ' 	 	  	 => trim($form_state['values']['universityins']),
							's_division' 	 	 => trim($form_state['values']['division']),
							'service_id' 	  	 => $getServiceInfoId['service_id'],
							's_edu_status'	  	 => '1',
						  );
	
	$eduqaul_info_details = db_insert('a_service_edu')->fields($eduqaul_info)->execute();
		if($service_info_details){
			 drupal_set_message('Your Record has been inserted successfully.');
			 //drupal_goto('servicerecord/eduqaulification');
		}/*else{
			drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
		}*/

}


function postingdetails_form_entry($form, &$form_state){  

	global $user;
	$status = getUserProfileStatus($user->uid);
	$userData = getLoginUserDetailForAsset($user->uid);
	$getServiceInfoId = getServiceInfoId($user->uid);

	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Posting Details</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
	$form['designation'] = array(
	  '#title' => t('Designation Level'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation Level','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['orderno'] = array(
	  '#title' => t('Order Number'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Order No','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['orderdate'] = array(
	  '#title' => t('Order Date'),	
	  '#type' => 'textfield',
	 //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control', 'servicedate'),'placeholder'=>'Order Date','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['officename'] = array(
	  '#title' => t('Office Name'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Name of The Office','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$value_state = 1;
	$form['district'] = array(
	   '#title'=> 'Select District',
	   '#type' => 'select', 
	   '#required' => true,
	   '#id'=>'district_name',
	   //'#disabled' => TRUE,
	   '#options' => get_district_by_id($value_state),
	   //'#value' => !empty($district_v) ? $district_v : '',
	   '#attributes' => array('class'=>array('form-control p-input'), 'placeholder'=>'District', 'autocomplete' => 'off'),
	   //'#default_value'=>!empty($uamdata) ? $uamdata['fname'] : '',
	   '#ajax'				=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',			
									'callback'		=> 'get_ajax_load',
									'progress'		=>	array(
										'type'		=>'throbber',
										'message'	=>t('loading'),
									),
							),
	   '#prefix' => '<div class="col-md-4" id="ld_edit_emp_district_replace">',
	   '#suffix' => '</div>'
	);
	
	$value_district	=	isset($form_state['values']['district']) ? $form_state['values']['district'] : ''; 
	 	
	if(!empty($value_state) && !empty($value_district)){ 
	   $form['subdivision'] = array(
		   '#title'=> 'Select Subdivision',
		   '#type' => 'select',
		   '#required' => true,
		   '#options' => common_custom_user_subdivisionlist_list_new($value_district), 
		   '#attributes' => array('class'=>array('form-control p-input'), 'placeholder'=>'Enter subdivision', 'autocomplete' => 'off'),
		   //'#default_value'=>!empty($uamdata) ? $uamdata['fname'] : '',
			'#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								),
		   '#prefix' => '<div class="col-md-4" id="ld_empsubdv_replace"><div class="selectpicker">',
		   '#suffix' => '</div></div>'
		);
	 }else{ 
			$form['subdivision'] = array(
			   '#title'=> 'Select Subdivision',
			   '#type' => 'select',
			   '#required' => true,
			   '#options' => array(''=>t('Select Sub-division')),
			   '#attributes' => array('class'=>array('form-control p-input'), 'placeholder'=>'Enter subdivision', 'autocomplete' => 'off', 'aria-describedby'=> 'nameHelp'),
			   '#prefix' => '<div class="col-md-4" id="ld_empsubdv_replace">',
			   '#suffix' => '</div>',
			);
	 }
	/*$form['ministrydept'] = array(
	  '#title' => t('Ministry Department'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['exp'] = array(
	  '#title' => t('Experience (Major/Minor)'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );*/
	
	$form['postingtype'] = array(
	  '#title' => t('Type Of Posting'),	
	  '#type' => 'select',
	  '#options' => array('Regular'=>'Regular','On Deputation'=>'On Deputation','Deputation to other Department'=>'Deputation to other Department'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['postingfrom'] = array(
	  '#title' => t('Posting From'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control', 'servicedate'),'autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['postingto'] = array(
	  '#title' => t('Posting Upto'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control', 'servicedate'),'autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	/*$form['duration'] = array(
	  '#title' => t('Duration'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'readonly' => 'readonly'),
	  '#prefix' => '<div class="col-md-4">',
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
	
	$form['postingtable'] = array(
	  '#prefix' => '<div class="col-md-12">'.postingtable(),
	  '#suffix' => '</div>'
    );
	 
	return $form;
}

function postingtable() {
	
	global $user;
	$getServiceInfoId = getServiceInfoId($user->uid);
	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$postinfo = postinginfo($user->uid);
	
	$output = '';
	
  	$header = array(
				array('data'=> 'Sl No.'),
				array('data'=> 'Designation'),
				array('data'=> 'Order Number'),
				array('data'=> 'Order Date'),
				array('data'=> 'Office Name'),
				array('data'=> 'District'),
				array('data'=> 'Sub-division'),
				array('data'=> 'Posting Type'),
				array('data'=> 'Posting From'),
				array('data'=> 'Posting Upto'), 
				array('data'=> 'Action'),
			);
			
	$i = 0;
	/*if(!empty($resultData)){
	foreach($resultData as $val){*/
	if(!empty($postinfo)){
	foreach($postinfo as $val){
		$i++;
		 $editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'service/postingedit/'.$val->s_posting_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','service/postingdel/'.$val->s_posting_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  $rows [] = array(  
	 		  $i,
	  		  array('data' => t($val->s_designation)), 	
			  array('data' => t($val->s_order_no)),
			  array('data' => t($val->s_order_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_order_date))) : 'N/A' ),
			  array('data' => t($val->s_office_name)),
			  array('data' => t($val->district_name)),
			  array('data' => t($val->sub_div_name)),
			  array('data' => t($val->s_posting_type)),
			  array('data' => t($val->s_posting_from) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_posting_from))) : 'N/A' ),
			  array('data' => t($val->s_posting_to) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_posting_to))) : 'N/A' ),
			  //array('data' => ($val->landacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->landacquistion_date))) : 'N/A'),
			  array('data' => $editLink.' '.$delLink),			
		); 
	 }
	}
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	
	return $output;	
	
	
}

function postingdetails_form_entry_submit($form, &$form_state){ 

		global $user;
		$getServiceInfoId = getServiceInfoId($user->uid);
	
		$posting_info = array( 
							's_uid' 				=> $user->uid,
							's_designation' 		=> trim($form_state['values']['designation']),
							's_order_no'			=> trim($form_state['values']['orderno']),
							's_order_date'			=> format_date(strtotime($form_state['values']['orderdate']), 'custom', 'Y-m-d'),
							's_office_name' 		=> trim($form_state['values']['officename']),
							's_posting_district'	=> trim($form_state['values']['district']),
							's_posting_subdivision' => trim($form_state['values']['subdivision']),
							's_posting_type' 		=> trim($form_state['values']['postingtype']),
							's_posting_from' 		=> format_date(strtotime($form_state['values']['postingfrom']), 'custom', 'Y-m-d'),
							's_posting_to'			=> format_date(strtotime($form_state['values']['postingto']), 'custom', 'Y-m-d'),
							's_pstatus'				=> '1',
							'service_id'			=> $getServiceInfoId['service_id'],
							//'s_pduration' 			=> 'NA',
						  ); 
						  
			//print_r($posting_info); exit;			  
	
		$posting_info_details = db_insert('a_posting_details')->fields($posting_info)->execute();
		if($posting_info_details){
			 drupal_set_message('Your Record has been inserted successfully.');
			 //drupal_goto('servicerecord/eduqaulification');
		}/*else{
			drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
		}*/
}

function inservicetrainingdetails_form_entry($form, &$form_state){  

	global $user;
	$getServiceInfoId = getServiceInfoId($user->uid);
		
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');	
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">In-Service / Domestic Training Details</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	
	$form['trainingname'] = array(
	  '#title' => t('Training Name'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Training Name','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );  
	
	$form['trainingtype'] = array(
	  '#title' => t('Training Type'),	
	  '#type' => 'select',
	  '#options' => array('Own Capacity'=>t('Own Capacity'),'Government Sponsor'=>t('Government Sponsor')),
	  /*'#ajax' => array(
                      'callback' => 'trainingtype_callback',
                   ),*/
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['yearfrom'] = array(
	  '#title' => t('Training From'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('id'=>'yearfrom','class'=>array('form-control', 'servicedate'),'placeholder'=>'From Date (DD-MM-YYYY)','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	
	$form['yearto'] = array(
	  '#title' => t('Training Upto'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('id'=>'yearto','class'=>array('form-control', 'servicedate'),'placeholder'=>'To Date (DD-MM-YYYY)','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	$form['institute'] = array(
	  '#title' => t('Training Institute Name'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Institute','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	
	$form['country'] = array(
	  '#title' => t('Training Country'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Country','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['city'] = array(
	  '#title' => t('Training City'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'City','autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	
	$form['duration'] = array(
	  '#title' => t('Training Duration'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  //'#disabled' => TRUE,
	  '#attributes' => array('id'=>'duration','class'=>array('form-control'),'placeholder'=>'Duration','readonly'=>'readonly'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	 
	$form['submit'] = array(
	  '#type'=>'submit',
	  '#value'=> t('Add'),
	  '#attributes' => array('class'=>array('form-control btn btn-info')),
	  '#prefix' => '<div class="col-md-12"><div class="input-group">',
	  '#suffix' => '</div></div>'
	);	
	
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	
	$form['inservicetraining'] = array(
	  '#prefix' => '<div class="col-md-12">'.inservicetraining(),
	  '#suffix' => '</div>'
    );

	return $form;
}

function inservicetraining() {

	global $user;
	$getServiceInfoId = getServiceInfoId($user->uid);
	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$inserviceinfo = inserviceinfo($user->uid);

	$output = '';
	
  	$header = array(
				array('data'=> 'Sl No.'),
				array('data'=> 'Training Name'),
				array('data'=> 'Training Type'),
				array('data'=> 'In-Service Training Year From'),
				array('data'=> 'In-Service Training Year To'),
				array('data'=> 'Training Institute'),
				array('data'=> 'Training Country'),
				array('data'=> 'Training City'),
				array('data'=> 'Training Duration'),
				array('data'=> 'Action'),
			);
			
	$rows = array();
	
	
	$i = 0;
	/*if(!empty($resultData)){
	foreach($resultData as $val){*/
	if(!empty($inserviceinfo)){
	foreach($inserviceinfo as $val){
		$i++;
		 $editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'service/inservedit/'.$val->s_inserv_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','service/inservdel/'.$val->s_inserv_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  $rows [] = array(  
	 		  $i,
			  array('data' => t($val->s_training_name)),
			  array('data' => t($val->s_training_type)),
	  		  array('data' => t($val->s_training_from) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_training_from))) : 'N/A' ),
			  array('data' => t($val->s_training_to) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_training_to))) : 'N/A' ),
			  array('data' => t($val->s_training_institute)),
			  array('data' => t($val->s_training_country)),
			  array('data' => t($val->s_training_city)),
			  array('data' => t($val->s_training_duration)),
			  //array('data' => ($val->landacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->landacquistion_date))) : 'N/A'),
			  array('data' => $editLink.' '.$delLink),			
		); 
	 }
	}
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	
	return $output;	
}

function inservicetrainingdetails_form_entry_submit($form, &$form_state){  

		global $user;
		$getServiceInfoId = getServiceInfoId($user->uid);
	
		$inservicetrainingdetails_info = array( 
							's_uid' 				=> $user->uid,
							's_training_name'		=> trim($form_state['values']['trainingname']),
							's_training_type'		=> trim($form_state['values']['trainingtype']),
							's_training_from' 		=> format_date(strtotime($form_state['values']['yearfrom']), 'custom', 'Y-m-d'),
							's_training_to'			=> format_date(strtotime($form_state['values']['yearto']), 'custom', 'Y-m-d'),
							's_training_institute'	=> trim($form_state['values']['institute']),
							's_training_country'	=> trim($form_state['values']['country']),
							's_training_city'		=> trim($form_state['values']['city']),
							's_training_duration'	=> trim($form_state['values']['duration']),
							'service_id'			=> $getServiceInfoId['service_id'],
						  );
						  
		$inservicetrainingdetails_info_details = db_insert('a_inservice_training')->fields($inservicetrainingdetails_info)->execute();
		if($inservicetrainingdetails_info_details){
			 drupal_set_message('Your Record has been inserted successfully.');
			 //drupal_goto('servicerecord/eduqaulification');
		}/*else{
			drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
		}*/
}

/*function domestictrdetails_form_entry($form, &$form_state){  

	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Domestic Training Details</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
	$form['dtyear'] = array(
	  '#title' => t('Year'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	
	$form['dtname'] = array(
	  '#title' => t('Name'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	
	$form['dtsubject'] = array(
	  '#title' => t('Subject'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	
	$form['dtduration'] = array(
	  '#title' => t('Duration'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	
  $form['submit'] = array(
	  '#type'=>'submit',
	  '#value'=> t('Submit'),
	  '#attributes' => array('class'=>array('form-control btn btn-info')),
	  '#prefix' => '<div class="col-md-6"><div class="input-group">',
	  '#suffix' => '</div></div>'
	);	
	
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	
	$form['domestictraining'] = array(
	  '#prefix' => '<div class="col-md-4">'.domestictraining(),
	  '#suffix' => '</div>'
    );

	return $form;
}*/

/*function domestictraining(){
	
	global $user;
	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	$query = db_select('a_domestic_training', 'adt');
	$query ->leftJoin('a_service_info', 'asi', 'adt.s_uid = asi.s_uid'); 
	$query ->fields('adt', array('s_dtraining_id', 's_dtraining_year', 's_dtraining_name', 's_dtraining_subject', 's_dtraining_duration', 's_dtraining_status'));
	$query->condition('adt.s_dtraining_status', 1, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
 
	$output = '';
	if(!empty($resultData)){
  	$header = array(
				array('data'=> 'Sl No.'),
				array('data'=> 'Year'),
				array('data'=> 'Name'),
				array('data'=> 'Subject'),
				array('data'=> 'Duration'),
				array('data'=> 'Action'),
			);
			
	$rows = array();
	
	$i = 0;
	
	foreach($resultData as $val){
		$i++;
		 $editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'service/dtrainingedit/'.$val->s_dtraining_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','service/dtrainingdel/'.$val->s_dtraining_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  $rows [] = array(  
	 		  $i,
	  		  array('data' => t($val->s_dtraining_year)), 	
			  array('data' => t($val->s_dtraining_name)), 
			  array('data' => t($val->s_dtraining_subject)),
			  array('data' => t($val->s_dtraining_duration)),
			  //array('data' => ($val->landacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->landacquistion_date))) : 'N/A'),
			  array('data' => $editLink.' '.$delLink),			
		); 
	}
	
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	}
	return $output;	
}*/

/*function domestictrdetails_form_entry_submit($form, &$form_state){  

		global $user;
	
		$domestictrdetails_info = array( 
							's_uid' 				=> $user->uid,
							's_dtraining_year' 		=> trim($form_state['values']['dtyear']),
							's_dtraining_name'		=> trim($form_state['values']['dtname']),
							's_dtraining_subject'	=> trim($form_state['values']['dtsubject']),
							's_dtraining_duration'	=> trim($form_state['values']['dtduration']),						
						  );
						  
		$domestictrdetails_info_details = db_insert('a_domestic_training')->fields($domestictrdetails_info)->execute();
		if($domestictrdetails_info_details){
			 drupal_set_message('Your Record has been inserted successfully.');
			 //drupal_goto('servicerecord/eduqaulification');
		}else{
			drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
		}
}*/


function foreigntrdetails_form_entry($form, &$form_state){  

	global $user;
	$getServiceInfoId = getServiceInfoId($user->uid);

	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Foreign Training Details</h4></div><div class="widget-main">',
	 );
	 	
	$form['ftname'] = array(
	  '#title' => t('Name of Training'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Name of Training'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['ftrainingtype'] = array(
	  '#title' => t('Training Type'),	
	  '#type' => 'select',
	  '#options' => array('1'=>t('Own Capacity'),'2'=>t('Government Sponsor')),
	  /*'#ajax' => array(
                      'callback' => 'trainingtype_callback',
                   ),*/
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['ftfrom'] = array(
	  '#title' => t('Training From'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('id'=>'yearfrom','class'=>array('form-control','datepiker'),'placeholder'=>'From (DD-MM-YYYY)'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	$form['ftto'] = array(
	  '#title' => t('Training Upto'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('id'=>'yearto','class'=>array('form-control','datepiker'),'placeholder'=>'To (DD-MM-YYYY)'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	
	$form['ftinstitute'] = array(
	  '#title' => t('Training Institute Name'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Name of Institute'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['ftcountry'] = array(
	  '#title' => t('Training Country'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Country'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
	$form['ftcity'] = array(
	  '#title' => t('Training City'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'City'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	 	 
  $form['ftduration'] = array(
	  '#title' => t('Training Duration'),	
	  '#type' => 'textfield',
	  //'#required' => TRUE,
	  //'#disabled' => TRUE,
	  '#attributes' => array('id'=>'duration','class'=>array('form-control'),'placeholder'=>'Duration','readonly'=>'readonly'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 	
	
  $form['submit'] = array(
	  '#type'=>'submit',
	  '#value'=> t('Add'),
	  '#attributes' => array('class'=>array('form-control btn btn-info')),
	  '#prefix' => '<div class="col-md-12"><div class="input-group">',
	  '#suffix' => '</div></div>'
	);	
	
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	
	$form['foreigntraining'] = array(
	  '#prefix' => '<div class="col-md-12">'.foreigntraining(),
	  '#suffix' => '</div>'
    );

	return $form;
}

function foreigntraining(){
	
	global $user;
	$getServiceInfoId = getServiceInfoId($user->uid);
	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$foreigninfo = foreigninfo($user->uid);
	
	$output = '';
	
  	$header = array(
				array('data'=> 'Sl No.'),
				array('data'=> 'Training Name'),
				array('data'=> 'Training Type'),
				array('data'=> 'Training From'),
				array('data'=> 'Training To'),
				array('data'=> 'Training Institute'),
				array('data'=> 'Country'),
				array('data'=> 'City'),
				array('data'=> 'Duration'),
				array('data'=> 'Action'),
			);
			
	$rows = array();
	
	$i = 0; 
	/*if(!empty($resultData)){
	foreach($resultData as $val){*/
	if(!empty($foreigninfo)){
	foreach($foreigninfo as $val){
		$i++;
		 $editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'service/ftrainingedit/'.$val->s_ftraining_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','service/ftrainingdel/'.$val->s_ftraining_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  $rows [] = array(  
	 		  $i,
			  array('data' => t($val->s_ftraining_name)),
			  array('data' => t($val->s_ftraining_type)),
			  array('data' => t($val->s_ftraining_from) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_ftraining_from))) : 'N/A' ),
			  array('data' => t($val->s_ftraining_to) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_ftraining_to))) : 'N/A' ),  
			  array('data' => t($val->s_ftraining_institute)),
			  array('data' => t($val->s_ftraining_country)),
			  array('data' => t($val->s_ftraining_city)),
			  array('data' => t($val->s_ftraining_duration)),
			  //array('data' => ($val->landacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->landacquistion_date))) : 'N/A'),
			  array('data' => $editLink.' '.$delLink),			
		); 
	 }
	}
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	
	return $output;	
}

function foreigntrdetails_form_entry_submit($form, &$form_state){  

		global $user;
		$getServiceInfoId = getServiceInfoId($user->uid);
			
		$ftraining_info = array( 
							's_uid' 				=> $user->uid,
							's_ftraining_name'		=> trim($form_state['values']['ftname']),
							's_ftraining_type' 		=> trim($form_state['values']['ftrainingtype']),
							's_ftraining_from' 		=> trim($form_state['values']['ftfrom']),
							's_ftraining_to' 		=> trim($form_state['values']['ftto']),
							's_ftraining_institute'	=> trim($form_state['values']['ftinstitute']),
							's_ftraining_country'	=> trim($form_state['values']['ftcountry']),
							's_ftraining_city'	    => trim($form_state['values']['ftcity']),
							's_ftraining_duration'	=> trim($form_state['values']['ftduration']),	
							'service_id'			=> $getServiceInfoId['service_id'],						
						  );
						  
		$ftraining_info_details = db_insert('a_foreign_training')->fields($ftraining_info)->execute();
		if($ftraining_info_details){
			 drupal_set_message('Your Record has been inserted successfully.');
			 //drupal_goto('servicerecord/eduqaulification');
		}/*else{
			drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
		}*/
}

function awardspubl_form_entry($form, &$form_state){  

	global $user;
	$getServiceInfoId = getServiceInfoId($user->uid);

	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Name of the Awards/ Title of Publications</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
	/*$form['aptype'] = array(
	  '#title' => t('Type'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); 
	
	$form['aparea'] = array(
	  '#title' => t('Area'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control')),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    ); */
	
	$form['categorytype'] = array(
	  '#title' => t('Activity Categories'),	
	  '#type' => 'select',
	  '#options' => array('Awards'=>t('Awards'),'Publication'=>t('Publication'),'Conference'=>t('Conference'),'Seminar'=>t('Seminar'),'Workshop'=>t('Workshop'),'Certification'=>t('Certification'),'Other'=>t('Other')),
	  '#ajax' => array(
                      'callback' => 'awards_callback',
                   ),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'autocomplete'=>'off'),
	  '#prefix' => '<div class="col-md-4">',
	  '#suffix' => '</div>'
    );
	
  $form['apname_begin'] = array(
	  '#prefix' => '<div id="replace_awardtype_n"><div class="col-md-12">',
	  '#suffix' => '</div></div>'
    );	
	
  if(isset($form_state['values']['categorytype']) && trim($form_state['values']['categorytype'])=='Awards'){
	
	$form['apname_begin']['apname'] = array(
	  '#title' => t('Award Name'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Name of The Award','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_awardtype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 
	
	$form['apname_begin']['apgivername'] = array(
	  '#title' => t('Award Given By'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Award Given By','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_awardtype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 
	$form['apname_begin']['apyear'] = array(
	  '#title' => t('Award Received Year'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Year (YYYY)','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_awardtype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    );
	
	$form['apname_begin']['apdesc'] = array(
	  '#title' => t('Description'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Description','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_awardtype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 
	
   $form['apname_begin']['aplevel'] = array(
	  '#title' => t('Level'),	
	  '#type' => 'select',
	  '#options' => array('Domestic'=>'Domestic','International'=>'International'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Level','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_awardtype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 		
 }else{
		$form['award_type'] = array(
		  '#prefix' => '<div id="replace_awardtype">',
		  '#suffix' => '</div>'
		);
	}
 
 
   $form['publication_begin'] = array(
	  '#prefix' => '<div id="replace_publication_n"><div class="col-md-12">',
	  '#suffix' => '</div></div>'
    );	  
	
 if(isset($form_state['values']['categorytype']) && trim($form_state['values']['categorytype'])=='Publication'){
	
	$form['publication_begin']['apname'] = array(
	  '#title' => t('Publication Name'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Name of The Publication','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_publicationtype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 
	
	$form['publication_begin']['apgivername'] = array(
	  '#title' => t('Publishers Name'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Publishers Name','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_publicationtype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 
	$form['publication_begin']['apyear'] = array(
	  '#title' => t('Publication Year'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Year (YYYY)','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_publicationtype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    );
	
	$form['publication_begin']['apdesc'] = array(
	  '#title' => t('Publication Description'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Publication Description','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_publicationtype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 
	
   $form['publication_begin']['aplevel'] = array(
	  '#title' => t('Publication Level'),	
	  '#type' => 'select',
	  '#options' => array('Domestic'=>'Domestic','International'=>'International'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Level','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_publicationtype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 		
 }else{
		$form['publication_type'] = array(
		  '#prefix' => '<div id="replace_publicationtype">',
		  '#suffix' => '</div>'
		);
	}
 
 
  $form['other_begin'] = array(
	  '#prefix' => '<div id="replace_other_n"><div class="col-md-12">',
	  '#suffix' => '</div></div>'
    );
 
 if(isset($form_state['values']['categorytype']) && trim($form_state['values']['categorytype'])=='Conference' || trim($form_state['values']['categorytype'])=='Seminar'
		  || trim($form_state['values']['categorytype'])=='Workshop' || trim($form_state['values']['categorytype'])=='Certification' || trim($form_state['values']['categorytype'])=='Other'){
	
	$form['other_begin']['apname'] = array(
	  '#title' => t('Name'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Name','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_othertype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 
	
	$form['other_begin']['apgivername'] = array(
	  '#title' => t('Giver Name'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Giver Name','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_othertype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 
	$form['other_begin']['apyear'] = array(
	  '#title' => t('Year'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Year (YYYY)','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_othertype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    );
	
	$form['other_begin']['apdesc'] = array(
	  '#title' => t('Description'),	
	  '#type' => 'textfield',
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Description','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_othertype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 
	
   $form['other_begin']['aplevel'] = array(
	  '#title' => t('Level'),	
	  '#type' => 'select',
	  '#options' => array('Domestic'=>'Domestic','International'=>'International'),
	  '#required' => TRUE,
	  '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Level','autocomplete'=>'off'),
	  '#prefix' => '<div id="replace_othertype"><div class="col-md-4">',
	  '#suffix' => '</div></div>'
    ); 		
 }else{
		$form['activityother_type'] = array(
		  '#prefix' => '<div id="replace_othertype">',
		  '#suffix' => '</div>'
		);
	}
 
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
	
	$form['sawards'] = array(
	  '#prefix' => '<div class="col-md-12">'.sawards(),
	  '#suffix' => '</div>'
    );

	return $form;
}

function awards_callback($form, &$form_state){
	$commands   = array();
	$commands[] = ajax_command_replace('#replace_awardtype_n', '<div id="replace_awardtype_n">'.drupal_render($form['apname_begin']).'</div>');
	$commands[] = ajax_command_replace('#replace_publication_n', '<div id="replace_publication_n">'.drupal_render($form['publication_begin']).'</div>');
	$commands[] = ajax_command_replace('#replace_other_n', '<div id="replace_other_n">'.drupal_render($form['other_begin']).'</div>');

 	return array('#type' => 'ajax', '#commands' => $commands);
}

function sawards(){
		
	global $user;
	$getServiceInfoId = getServiceInfoId($user->uid);
	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$awardpubinfo = awardpubinfo($user->uid);
 
	$output = '';
	
  	$header = array(
				array('data'=> 'Sl No.'),
				array('data'=> 'Activity Category'),
				array('data'=> 'Name'),
				array('data'=> 'Awards Given By/Publishers Name'),
				array('data'=> 'Year'),
				array('data'=> 'Description'),
				array('data'=> 'Level'),
				array('data'=> 'Action'),
			);
			
	$rows = array();
	
	$i = 0;
	/*if(!empty($resultData)){
	foreach($resultData as $val){*/
	if(!empty($awardpubinfo)){
	foreach($awardpubinfo as $val){
		$i++;
		$editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'service/sawardedit/'.$val->s_awards_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','service/sawarddel/'.$val->s_awards_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  $rows [] = array( 
	 		  $i,
			  array('data' => t($val->s_acategorytype)),
			  array('data' => t($val->s_aname)),
			  array('data' => t($val->s_agivenby)),
			  array('data' => t($val->s_ayear)),
			  array('data' => t($val->s_adesc)),
			  array('data' => t($val->s_alevel)),
			  //array('data' => ($val->landacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->landacquistion_date))) : 'N/A'),
			  array('data' => $editLink.' '.$delLink),			
		); 
	 }
	}
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	
	return $output;	

}


function awardspubl_form_entry_submit($form, &$form_state){  

	global $user;
	$getServiceInfoId = getServiceInfoId($user->uid);
	
	$sawards_info = array( 
						  's_uid' 			=> $user->uid,
						  's_acategorytype' => trim($form_state['values']['categorytype']),
						  's_aname'			=> trim($form_state['values']['apname']),
						  's_agivenby'		=> trim($form_state['values']['apgivername']),
						  's_ayear'			=> trim($form_state['values']['apyear']),
						  's_adesc'			=> trim($form_state['values']['apdesc']),
						  's_alevel'		=> trim($form_state['values']['aplevel']),
						  'service_id'		=> $getServiceInfoId['service_id'],			
						);
						  
	$sawards_info_details = db_insert('a_service_awards')->fields($sawards_info)->execute();
	if($sawards_info_details){
		 drupal_set_message('Your Record has been inserted successfully.');
		 //drupal_goto('servicerecord/eduqaulification');
	}/*else{
		drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
	}*/
}


function finalpdf_form_entry($form, &$form_state){
	
	
	global $user;
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$getServiceInfoId = getServiceInfoId($user->uid);
	
 	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		//'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">General Service Details</h4></div><div class="widget-main">',
	 );	
	 
	$query = db_select('a_service_info', 'asi'); 
	$query ->fields('asi', array('service_id','sservice_cadre','s_doj','s_promotion_doj','s_dob','s_gender','s_uid','s_status','s_confirmdate','s_recruitmenttype'));
	$query->condition('asi.s_status', 1, '='); 
	$query->condition('asi.s_uid', $user->uid, '='); 
	$result = $query->execute();
	$resultData1 = $result->fetchAssoc();
	
	
	
	$form['service_info']['service_infolist'] = array(
	  '#type' => 'markup',
	  '#prefix' => '<div class="heading">'.serviceDetails($user->uid).'',
	  '#suffix' => '</div>'
  	);  
	
  /*----------------------------------------------- Educational Details Begin -----------------------------------------*/ 
	
	$form['edu_info']['edu_infolist'] = array(
		  '#type' => 'markup',
	  	  '#prefix' => '<div class="heading">'.educationDetails($user->uid).'',
	      '#suffix' => '</div>'
    );
	
	/*----------------------------------------------- Educational Details End -----------------------------------------*/
	
	/*----------------------------------------------- Posting Details Begin -----------------------------------------*/
	
	$form['posting_info']['posting_infolist'] = array(
	  '#type' => 'markup',
	  '#prefix' => '<div class="heading">'.postingDetails($user->uid).'',
	  '#suffix' => '</div>'
  	);  
	
	/*----------------------------------------------- Posting Details End -----------------------------------------*/
	
	/*----------------------------------------------- In-service Training Details Begin -----------------------------------------*/
	
	
	$form['inservicetraining_info']['inservicetraining_infolist'] = array(
	  '#type' => 'markup',
	  '#prefix' => '<div class="heading">'.inserviceTrainingDetails($user->uid).'',
	  '#suffix' => '</div>'
  	);  

	/*----------------------------------------------- In-service Training Details End -----------------------------------------*/
	
	/*----------------------------------------------- Foreign Training Details Begin -----------------------------------------*/
	
	$form['foreigntraining_info']['foreigntraining_infolist'] = array(
	  '#type' => 'markup',
	  '#prefix' => '<div class="heading">'.foreignTrainingDetails($user->uid).'',
	  '#suffix' => '</div>'
  	);  

	/*----------------------------------------------- Foreign Training Details End -----------------------------------------*/
	
	/*----------------------------------------------- Awards/Publications Details Begin ------------------------------------*/

	$form['awardspub_info']['awardspub_infolist'] = array(
	  '#type' => 'markup',
	  '#prefix' => '<div class="heading">'.awardpubDetails($user->uid).'',
	  '#suffix' => '</div>'
  	);  
	
	/*----------------------------------------------- Awards/Publications Details End --------------------------------------*/
	
	/*$link1 = array('data' => l('<strong class="btn btn-danger print-btn"> Print Acknowlwdgement</strong>','acknowledgement-print/'.$user_arr[1].'/'.$verify['declaration_yr'], 
				 array('html' => TRUE,'attributes'=>array('target'=>'_blank'))) ,'colspan' => 5);*/
	$servicegeninfo = servicegeninfo($user->uid);
	//print_r($servicegeninfo);	
	if($servicegeninfo['s_forwardstatus']=='F'){		 
	$pdflink = l(t('PDF PRINT'), 'sar-print/'.$resultData1['s_uid'].'/'.$resultData1['service_id'], array('html' => TRUE,'attributes'=>array('title' => 'View')));
	
	
	$form['pdfbutton'] = array(
      '#type' => 'markup',
	  //'#value' => t('PDF Print'),
	  //'#id' => 'search_btnn',
	  '#markup' => $pdflink,
    );	
	}
	
	if($servicegeninfo['s_forwardstatus']=='0'){	
	$form['finalsubmit'] = array(
      '#type' => 'submit',
	  '#value' => t('Final Submit'),
	  //'#id' => 'search_btnn',
    );	
	}
	
	$form['form_end'] = array(
         '#type' => 'markup',
         '#markup' => '</div>',
		 //'#suffix' => '</div></div>',
    );
	
	return $form;
}


function finalpdf_form_entry_submit($form, &$form_state){
	
	global $user;
	
	$servicetable = db_update('a_service_info');
	$servicetable->fields(array('s_forwardstatus' => 'F'));
	$servicetable->condition('s_uid',$user->uid,'=');
    $rs = $servicetable->execute();
		
	$edutable = db_update('a_service_edu');
	$edutable->fields(array('s_forwardstatus' => 'F'));
	$edutable->condition('s_uid',$user->uid,'=');
    $rs = $edutable->execute();
	
	$postingtable = db_update('a_posting_details');
	$postingtable->fields(array('s_forwardstatus' => 'F'));
	$postingtable->condition('s_uid',$user->uid,'=');
    $rs = $postingtable->execute();
	
	$inservicetable = db_update('a_inservice_training');
	$inservicetable->fields(array('s_forwardstatus' => 'F'));
	$inservicetable->condition('s_uid',$user->uid,'=');
    $rs = $inservicetable->execute();
	
	$foreigntable = db_update('a_foreign_training');
	$foreigntable->fields(array('s_forwardstatus' => 'F'));
	$foreigntable->condition('s_uid',$user->uid,'=');
    $rs = $foreigntable->execute();
	
	$awardstable = db_update('a_service_awards');
	$awardstable->fields(array('s_forwardstatus' => 'F'));
	$awardstable->condition('s_uid',$user->uid,'=');
    $rs = $awardstable->execute();
	
	//$finalsubmit =(UPDATE a_service_info SET s_forwardstatus = 'F' WHERE service_id =(SELECT sales_person FROM accounts WHERE name = 'Acme Corporation'));
	
	$assetdashboard	= $base_root.$base_path.'service-empdashboard';
	
	if($rs){
			 drupal_set_message('Application Forwarded For Verification.');
			 drupal_goto($assetdashboard);
		}else{
			 drupal_set_message('Unable to save your record. Please try again later.',$type = 'warning');
		}
}

function serviceofficer_admin_dashboard(){
	
	global $user;
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$getServiceInfoId = getServiceInfoId($user->uid);
	$userData = getLoginUserDetailForAsset($user->uid);
	
	//echo $user->uid; exit;
	//print_r($userData); exit;
	
	$query = db_select('a_service_info', 'asi');
	$query->leftJoin('a_user_details', 'aud', 'asi.s_uid = aud.uid'); 
	$query->leftJoin('a_user_details_service', 'auds', 'asi.s_uid = auds.uid'); 
	$query->fields('asi', array('service_id','sservice_cadre','s_doj','s_promotion_doj','s_dob','s_gender','s_uid','s_status','s_confirmdate','s_recruitmenttype','s_forwardstatus'));
	$query->fields('aud',array('fname','hrms_id'));
	$query->fields('auds',array('directorate_code'));
	$query->condition('asi.s_forwardstatus', 'F', '='); 
	$query->condition('auds.directorate_code', trim($userData['directorate_code']), '='); 
	//$query->condition('asi.s_uid', $user->uid, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
	
	//print_r($result); exit;
	
	$output = '';
	
  	$header = array(
				array('data'=> 'Sl No.'),
				array('data'=> 'Officers Name'),
				array('data'=> 'HRMS ID'),
				array('data'=> 'Service/Cadre'),
				array('data'=> 'Date of Joining'),
				array('data'=> 'Date of Confirmation'),
				array('data'=> 'Date of Birth'),
				array('data'=> 'Type of Recruitment'),
				array('data'=> 'Action'),
			);
			
	$rows = array();
	
	$i = 0; 
	if(!empty($resultData)){
	foreach($resultData as $val){
		$i++;
		 //$editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'service/ftrainingedit/'.$val->s_ftraining_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		//$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','service/ftrainingdel/'.$val->s_ftraining_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  //$ViewLink = ;
	  $ViewLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i></div>', 
	  			  'service-officerdashboard/approvalview/'.$val->service_id, 
				  array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array('green'))));
	  $rows [] = array(  
	 		  $i,
			  array('data' => t($val->fname)),
			  array('data' => t($val->hrms_id)),
			  array('data' => t($val->sservice_cadre)),
			  array('data' => ($val->s_doj) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_doj))) : 'N/A'),
			  array('data' => ($val->s_confirmdate) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_confirmdate))) : 'N/A'),
			  array('data' => ($val->s_dob) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_dob))) : 'N/A'),
			  array('data' => t($val->s_recruitmenttype)),
			  //array('data' => ($val->landacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->landacquistion_date))) : 'N/A'),
			  array('data' => $ViewLink),			
		); 
	 }
	}
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	
	return $output;		
}

function serviceemp_admin_dashboard(){
	
	global $user;
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$getServiceInfoId = getServiceInfoId($user->uid);
	$userData = getLoginUserDetailForAsset($user->uid);
	
	//echo $user->uid; exit;
	//print_r($userData); exit;
	
	$query = db_select('a_service_info', 'asi');
	$query->leftJoin('a_user_details', 'aud', 'asi.s_uid = aud.uid'); 
	$query->leftJoin('a_user_details_service', 'auds', 'asi.s_uid = auds.uid'); 
	$query->fields('asi', array('service_id','sservice_cadre','s_doj','s_promotion_doj','s_dob','s_gender','s_uid','s_status','s_confirmdate','s_recruitmenttype','s_forwardstatus'));
	$query->fields('aud',array('fname','hrms_id'));
	$query->fields('auds',array('directorate_code'));
	$query->condition('asi.s_forwardstatus', 'F', '='); 
	//$query->condition('auds.directorate_code', trim($userData['directorate_code']), '='); 
	$query->condition('asi.s_uid', $user->uid, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
	
	//print_r($result); exit;
	
	$output = '';
	
  	$header = array(
				array('data'=> 'Sl No.'),
				array('data'=> 'Officers Name'),
				array('data'=> 'HRMS ID'),
				array('data'=> 'Service/Cadre'),
				array('data'=> 'Date of Joining'),
				array('data'=> 'Date of Confirmation'),
				array('data'=> 'Date of Birth'),
				array('data'=> 'Type of Recruitment'),
				//array('data'=> 'Action'),
			);
			
	$rows = array();
	
	$i = 0; 
	if(!empty($resultData)){
	foreach($resultData as $val){
		$i++;
		 //$editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'service/ftrainingedit/'.$val->s_ftraining_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		//$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','service/ftrainingdel/'.$val->s_ftraining_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
    $ViewLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'service-empdashboard/ftrainingedit/'.$val->service_id, array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array('green'))));
	  $rows [] = array(  
	 		  $i,
			  array('data' => t($val->fname)),
			  array('data' => t($val->hrms_id)),
			  array('data' => t($val->sservice_cadre)),
			  array('data' => ($val->s_doj) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_doj))) : 'N/A'),
			  array('data' => ($val->s_confirmdate) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_confirmdate))) : 'N/A'),
			  array('data' => ($val->s_dob) != 'N/A' ? t(date('d-m-Y',strtotime($val->s_dob))) : 'N/A'),
			  array('data' => t($val->s_recruitmenttype)),
			  //array('data' => ($val->landacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->landacquistion_date))) : 'N/A'),
			  //array('data' => $ViewLink),			
		); 
	 }
	}
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	
	return $output;		
}

function serviceofficer_approval($form, &$form_state, $args1){
	
	global $users;
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$getServiceInfoId = getServiceInfoId($user->uid);
	
	$form['service_info']['service_infolist'] = array(
	  '#type' => 'markup',
	  '#prefix' => '<div class="heading">'.servicegeninfo($user->uid).'',
	  '#suffix' => '</div>'
  	);  
	
	return $form;	
}
