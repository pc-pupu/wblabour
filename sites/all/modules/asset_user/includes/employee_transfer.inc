<?php

function employee_transfer_form($form, &$form_state){
	//ctools_include('modal');
	//ctools_modal_add_js();
	global $user;
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');	
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
		
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Transfer Employee</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
	 
	 $form['fname_transfer'] = array(
		'#type' => 'textfield',
		'#autocomplete_path' => 'getassetuser/autocompletetransfer',
		'#ajax' => array('event' => 'blur',
                      'callback' => '_reload_mem_order_list_transfer',
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
	 
	$form['user_service_id'] = array(
		'#type' => 'hidden',
		'#title' => t('User Service Id'),
		//'#id' =>'order_no_map',
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'User Service Id'),
		'#prefix' => '<div id="user_service_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 ); 
	 
  	$form['uid_transfer'] = array(
		'#type' => 'hidden',
		'#title' => t('User Id Backlog'),
		//'#id' =>'order_no_map',
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('doc_name_clear','form-control'),'placeholder'=>'User Id Backlog'),
		'#prefix' => '<div id="order_no_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 
 	$form['designation_transfer'] = array(
		'#type' => 'hidden',
		'#title' => t('Designation'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
		'#prefix' => '<div id="designation_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 ); 
	 
	$form['district_transfer'] = array(
		'#type' => 'hidden',
		'#title' => t('District'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'District'),
		'#prefix' => '<div id="district_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 
	$form['directorate_transfer'] = array(
		'#type' => 'hidden',
		'#title' => t('Directorate'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Directorate'),
		'#prefix' => '<div id="directorate_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );  
	 
	 $form['doj_transfer'] = array(
		'#type' => 'hidden',
		'#title' => t('DOJ'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'DOJ'),
		'#prefix' => '<div id="doj_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 
	 $form['pay_scale'] = array(
		'#type' => 'hidden',
		'#title' => t('Pay Scale'),
		//'#value'=>'',
		//'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Pay Scale'),
		'#prefix' => '<div id="pay_scale_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 $form['emp_group'] = array(
		'#type' => 'hidden',
		'#title' => t('Emp Group'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Emp Group'),
		'#prefix' => '<div id="emp_group_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 $form['direct_promotee'] = array(
		'#type' => 'hidden',
		'#title' => t('Direct Promotee'),
		//'#value'=>'',
		//'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Direct Promotee'),
		'#prefix' => '<div id="direct_promotee_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 $form['promotion_date_empgroupa'] = array(
		'#type' => 'hidden',
		'#title' => t('Promotion Date Empgroupa'),
		//'#value'=>'',
		//'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Promotion Date Empgroupa'),
		'#prefix' => '<div id="promotion_date_empgroupa_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 $form['asset_received_manner'] = array(
		'#type' => 'hidden',
		'#title' => t('Asset Received Manner'),
		//'#value'=>'',
		//'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Asset Received Manner'),
		'#prefix' => '<div id="asset_received_manner_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 $form['transfer_from_office'] = array(
		'#type' => 'hidden',
		'#title' => t('Transfer From Office'),
		//'#value'=>'',
		//'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Transfer From Office'),
		'#prefix' => '<div id="transfer_from_office_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 
	 
	 $form['fetch_data_transfer'] = array(
		'#prefix' => '<div id="fetch_data_map_backlog"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );
	 
	 $form['fetch_data_year'] = array(
		'#prefix' => '<div id="fetch_data_map_year"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );
	 
	
	if(isset($form_state['values']['fname_transfer']) && $form_state['values']['fname_transfer']!=""){
		$user_arr = explode('-',$form_state['values']['fname_transfer']);
		$mydata = getUserInfoByUid($user_arr[1]);
		$type = array('T'=>'Transfer','P'=>'Promotion','TP'=>'Transfer with Promotion');   
		$form['type'] = array(
			'#type' => 'select',
			'#title' => t('Select Type'),
			'#ajax'=>array(
					'callback'	=> 'ajax_type_callback',
					'event' 	=> 'change',
					'effect' 	=> 'fade',			
					'progress'	=>	array(
						'type'		=>'throbber',
						'message'	=>t('loading'),
					),
					//'wrapper' => array('district_code_replace_div','designation_replace_div')
			),
			'#required' => TRUE,
			'#options' => $type,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Financial Year',),
			'#prefix' => '<div id="type_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		);
	}
	$form['type_blank'] = array(
		'#prefix' => '<div id="type_replace_div">',
		'#suffix' => '</div>'
	); 
	if(isset($form_state['values']['type']) && trim($form_state['values']['type']) != '' && trim($form_state['values']['type']) == 'T'){
		$form['district_code'] = array(
			'#type' => 'select',
			'#title' => t('District'),
			'#ajax'=>array(
					'callback'	=> 'ajax_district_callback',
					'event' 	=> 'change',
					'effect' 	=> 'fade',			
					'progress'	=>	array(
						'type'		=>'throbber',
						'message'	=>t('loading'),
					),
			),
			'#required' => TRUE,
			'#options' => getDistrictAllList(),
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Type'),
			'#prefix' => '<div id="district_code_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		);
			if(isset($form_state['values']['district_code']) && trim($form_state['values']['district_code']) != '' && trim($form_state['values']['district_code']) != '0'){
				$form['office_id'] = array(
				  '#title' => t('Select Office'),	
				  '#type' => 'select',
				  '#ajax'=>array(
						'callback'	=> 'ajax_office_callback',
						'event' 	=> 'change',
						'effect' 	=> 'fade',			
						'progress'	=>	array(
							'type'		=>'throbber',
							'message'	=>t('loading'),
						),
				  ),
				  //'#multiple' => TRUE,
				  '#required' => TRUE,
				  '#options' => getOfficeListByDistrict($form_state['values']['district_code'],$mydata['directorate_code']),
				  '#attributes' => array('class'=>array('form-control')),
				  '#prefix' => '<div id="office_id_replace_div" class="col-md-2">',
				  '#suffix' => '</div>'
				);
				
				if(isset($form_state['values']['office_id']) && trim($form_state['values']['office_id']) != '' && trim($form_state['values']['office_id']) != '0'){
					$form['order_no'] = array(
						'#type' => 'textfield',
						'#title' => t('Order No'),
						'#required' => TRUE,
						'#attributes' => array('class'=>array('form-control','doc_name_clear'),'placeholder'=>'Order No','autocomplete'=>'off'),
						'#prefix' => '<div id="order_no_replace_div"><div class="col-md-2">',
						'#suffix' => '</div></div>'
					);
					$form['release_date'] = array(
						'#type' => 'textfield',
						'#title' => t('Release Date'),
						'#required' => TRUE,
						'#attributes' => array('id'=>'release_date_clear_div','class'=>array('form-control','doc_name_clear','datepiker'),'placeholder'=>'Release Date','autocomplete'=>'off'),
						'#prefix' => '<div id="release_date_replace_div"><div class="col-md-2">',
						'#suffix' => '</div></div>'
					);
					$form['transfer_submit'] = array(
						'#type' => 'submit',
						//'#submit'=> array(),
						/*'#ajax' => array(
								'callback' => 'ajax_add_sarfy_callback',
								//'wrapper' => 'table_div_replace',
							),
						'#limit_validation_errors' => array(),	*/
						'#value' => t('Submit'),
						'#attributes' => array('class'=>array('btn btn-info')),
						'#prefix' => '<div id="transfer_submit_replace_div"><div class="col-md-12">',
						'#suffix' => '</div></div>'
					);
				}
			 }
	}
	$form['district_code_blank'] = array(
		'#prefix' => '<div id="district_code_replace_div">',
		'#suffix' => '</div>'
	);
	$form['office_id_blank'] = array(
		'#prefix' => '<div id="office_id_replace_div">',
		'#suffix' => '</div>'
	);
	$form['order_no_blank'] = array(
		'#prefix' => '<div id="order_no_replace_div">',
		'#suffix' => '</div>'
	);
	$form['release_date_blank'] = array(
		'#prefix' => '<div id="release_date_replace_div">',
		'#suffix' => '</div>'
	);
	$form['transfer_submit_blank'] = array(
		'#prefix' => '<div id="transfer_submit_replace_div">',
		'#suffix' => '</div>'
	); 
	if(isset($form_state['values']['type']) && trim($form_state['values']['type']) != '' && trim($form_state['values']['type']) == 'P'){
		$form['order_no_p'] = array(
			'#type' => 'textfield',
			'#title' => t('Order No'),
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control','doc_name_clear'),'placeholder'=>'Order No','autocomplete'=>'off'),
			'#prefix' => '<div id="order_no_replace_div_p"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		);
		$form['designation'] = array(
			'#type' => 'textfield',
			'#title' => t('Designation'),
			//'#value'=>'',
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
			'#prefix' => '<div id="designation_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		 ); 
		 $form['emp_group_p'] = array(
			  '#title' => t('Emp Group'),	
			  '#type' => 'select',
			  '#required' => TRUE,
			  '#options' => array('A'=>'A','B'=>'B','C'=>'C'),
			  //'#options' => array('B'=>'B','C'=>'C'),
			  '#attributes' => array('class'=>array('form-control')),
			  '#prefix' => '<div id="emp_group_replace_div_p"><div class="col-md-2">',
			  '#suffix' => '</div></div>'
		); 
		$form['pay_scale_p'] = array(
			'#type' => 'textfield',
			'#title' => t('Pay Scale'),
			//'#value'=>'',
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Pay Scale'),
			'#prefix' => '<div id="pay_scale_replace_div_p"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		 ); 
		 $form['release_date_p'] = array(
			'#type' => 'textfield',
			'#title' => t('Release Date'),
			'#required' => TRUE,
			'#attributes' => array('id'=>'release_date_clear_div','class'=>array('form-control','doc_name_clear','datepiker'),'placeholder'=>'Release Date','autocomplete'=>'off'),
			'#prefix' => '<div id="release_date_replace_div_p"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		);
		$form['date_with_effect_from_p'] = array(
			'#type' => 'textfield',
			'#title' => t('Date With Effect From'),
			'#required' => TRUE,
			'#attributes' => array('id'=>'date_with_effect_from_clear_div','class'=>array('form-control','doc_name_clear','datepiker'),'placeholder'=>'Date With Effect From','autocomplete'=>'off'),
			'#prefix' => '<div id="date_with_effect_from_replace_div_p"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		);
		 $form['transfer_submit_p'] = array(
			'#type' => 'submit',
			//'#submit'=> array(),
			/*'#ajax' => array(
					'callback' => 'ajax_add_sarfy_callback',
					//'wrapper' => 'table_div_replace',
				),
			'#limit_validation_errors' => array(),	*/
			'#value' => t('Submit'),
			'#attributes' => array('class'=>array('btn btn-info')),
			'#prefix' => '<div id="transfer_submit_replace_div_p"><div class="col-md-12">',
			'#suffix' => '</div></div>'
		);
	}
	$form['order_no_p_blank'] = array(
		'#prefix' => '<div id="order_no_replace_div_p">',
		'#suffix' => '</div>'
	);
	$form['designation_blank'] = array(
		'#prefix' => '<div id="designation_replace_div">',
		'#suffix' => '</div>'
	);
	$form['emp_group_p_blank'] = array(
		  '#prefix' => '<div id="emp_group_replace_div_p">',
		  '#suffix' => '</div>'
	); 
	$form['pay_scale_p_blank'] = array(
		'#prefix' => '<div id="pay_scale_replace_div_p">',
		'#suffix' => '</div>'
	 ); 
	$form['release_date_blank_p'] = array(
		'#prefix' => '<div id="release_date_replace_div_p">',
		'#suffix' => '</div>'
	);
	$form['date_with_effect_from_blank_p'] = array(
		'#prefix' => '<div id="date_with_effect_from_replace_div_p">',
		'#suffix' => '</div>'
	);
	$form['transfer_submit_p_blank'] = array(
		'#prefix' => '<div id="transfer_submit_replace_div_p">',
		'#suffix' => '</div>'
	);
	if(isset($form_state['values']['type']) && trim($form_state['values']['type']) != '' && trim($form_state['values']['type']) == 'TP'){
		$form['district_code_tp'] = array(
			'#type' => 'select',
			'#title' => t('District'),
			'#ajax'=>array(
					'callback'	=> 'ajax_district_callback_tp',
					'event' 	=> 'change',
					'effect' 	=> 'fade',			
					'progress'	=>	array(
						'type'		=>'throbber',
						'message'	=>t('loading'),
					),
			),
			'#required' => TRUE,
			'#options' => getDistrictAllList(),
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Type'),
			'#prefix' => '<div id="district_code_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		);
		if(isset($form_state['values']['district_code_tp']) && trim($form_state['values']['district_code_tp']) != '' && trim($form_state['values']['district_code_tp']) != '0'){
				$form['office_id_tp'] = array(
				  '#title' => t('Select Office'),	
				  '#type' => 'select',
				  '#ajax'=>array(
						'callback'	=> 'ajax_office_callback_tp',
						'event' 	=> 'change',
						'effect' 	=> 'fade',			
						'progress'	=>	array(
							'type'		=>'throbber',
							'message'	=>t('loading'),
						),
				  ),
				  //'#multiple' => TRUE,
				  '#required' => TRUE,
				  '#options' => getOfficeListByDistrict($form_state['values']['district_code_tp'],$mydata['directorate_code']),
				  '#attributes' => array('class'=>array('form-control')),
				  '#prefix' => '<div id="office_id_replace_div_tp" class="col-md-2">',
				  '#suffix' => '</div>'
				);
				if(isset($form_state['values']['office_id_tp']) && trim($form_state['values']['office_id_tp']) != '' && trim($form_state['values']['office_id_tp']) != '0'){
					$form['order_no_tp'] = array(
						'#type' => 'textfield',
						'#title' => t('Order No'),
						'#required' => TRUE,
						'#attributes' => array('class'=>array('form-control','doc_name_clear'),'placeholder'=>'Order No','autocomplete'=>'off'),
						'#prefix' => '<div id="order_no_replace_div_tp"><div class="col-md-2">',
						'#suffix' => '</div></div>'
					);
					$form['release_date_tp'] = array(
						'#type' => 'textfield',
						'#title' => t('Release Date'),
						'#required' => TRUE,
						'#attributes' => array('id'=>'release_date_clear_div','class'=>array('form-control','doc_name_clear','datepiker'),'placeholder'=>'Release Date','autocomplete'=>'off'),
						'#prefix' => '<div id="release_date_replace_div_tp"><div class="col-md-2">',
						'#suffix' => '</div></div>'
					);
					$form['designation_tp'] = array(
						'#type' => 'textfield',
						'#title' => t('Designation'),
						//'#value'=>'',
						'#required' => TRUE,
						'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
						'#prefix' => '<div id="designation_replace_div_tp"><div class="col-md-2">',
						'#suffix' => '</div></div>'
					 ); 
					$form['emp_group_tp'] = array(
						  '#title' => t('Emp Group'),	
						  '#type' => 'select',
						  '#required' => TRUE,
						  '#options' => array('A'=>'A','B'=>'B','C'=>'C'),
						  //'#options' => array('B'=>'B','C'=>'C'),
						  '#attributes' => array('class'=>array('form-control')),
						  '#prefix' => '<div id="emp_group_replace_div_tp"><div class="col-md-2">',
						  '#suffix' => '</div></div>'
						); 
					$form['pay_scale_tp'] = array(
						'#type' => 'textfield',
						'#title' => t('Pay Scale'),
						//'#value'=>'',
						'#required' => TRUE,
						'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Pay Scale'),
						'#prefix' => '<div id="pay_scale_replace_div_tp"><div class="col-md-2">',
						'#suffix' => '</div></div>'
					 ); 	
					$form['transfer_submit_tp'] = array(
						'#type' => 'submit',
						//'#submit'=> array(),
						/*'#ajax' => array(
								'callback' => 'ajax_add_sarfy_callback',
								//'wrapper' => 'table_div_replace',
							),
						'#limit_validation_errors' => array(),	*/
						'#value' => t('Submit'),
						'#attributes' => array('class'=>array('btn btn-info')),
						'#prefix' => '<div id="transfer_submit_replace_div_tp"><div class="col-md-12">',
						'#suffix' => '</div></div>'
					);
				}
			 }
		/*$form['designation'] = array(
			'#type' => 'textfield',
			'#title' => t('Designation'),
			//'#value'=>'',
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
			'#prefix' => '<div id="designation_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		 ); */
	}
	
	
	$form['office_id_blank_tp'] = array(
		'#prefix' => '<div id="office_id_replace_div_tp">',
		'#suffix' => '</div>'
	); 
	$form['order_no_blank_tp'] = array(
		'#prefix' => '<div id="order_no_replace_div_tp">',
		'#suffix' => '</div>'
	);
	$form['release_date_blank_tp'] = array(
		'#prefix' => '<div id="release_date_replace_div_tp">',
		'#suffix' => '</div>'
	);
	$form['designation_tp_blank'] = array(
		'#prefix' => '<div id="designation_replace_div_tp">',
		'#suffix' => '</div>'
	 ); 
	$form['emp_group_tp_blank'] = array(
	  	'#prefix' => '<div id="emp_group_replace_div_tp">',
	  	'#suffix' => '</div>'
	); 
	$form['pay_scale_tp_blank'] = array(
		'#prefix' => '<div id="pay_scale_replace_div_tp">',
		'#suffix' => '</div>'
	 ); 
	$form['transfer_submit_blank_tp'] = array(
		'#prefix' => '<div id="transfer_submit_replace_div_tp">',
		'#suffix' => '</div>'
	); 
	$form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	

return $form;	 
}

function ajax_type_callback($form,&$form_state){
	$commands = array();
	if(isset($form_state['values']['type']) && trim($form_state['values']['type']) != '' && trim($form_state['values']['type']) == 'T'){
		$commands[] = ajax_command_replace('#district_code_replace_div', drupal_render($form['district_code']));
		$commands[] = ajax_command_replace('#order_no_replace_div_p', drupal_render($form['order_no_p_blank']));
		$commands[] = ajax_command_replace('#designation_replace_div', drupal_render($form['designation_blank']));
		$commands[] = ajax_command_replace('#emp_group_replace_div_tp', drupal_render($form['emp_group_tp_blank']));
		$commands[] = ajax_command_replace('#pay_scale_replace_div_tp', drupal_render($form['pay_scale_tp_blank']));
		$commands[] = ajax_command_replace('#emp_group_replace_div_p', drupal_render($form['emp_group_p_blank']));
		$commands[] = ajax_command_replace('#pay_scale_replace_div_p', drupal_render($form['pay_scale_p_blank']));
		$commands[] = ajax_command_replace('#release_date_replace_div_p', drupal_render($form['release_date_blank_p']));
		$commands[] = ajax_command_replace('#date_with_effect_from_replace_div_p', drupal_render($form['date_with_effect_from_blank_p']));
		$commands[] = ajax_command_replace('#transfer_submit_replace_div_p', '<div id="transfer_submit_replace_div_p">'.drupal_render($form['transfer_submit_p_blank']).'</div>');
	}elseif(isset($form_state['values']['type']) && trim($form_state['values']['type']) != '' && trim($form_state['values']['type']) == 'P'){
		$commands[] = ajax_command_replace('#order_no_replace_div_p', drupal_render($form['order_no_p']));
		$commands[] = ajax_command_replace('#designation_replace_div', drupal_render($form['designation']));
		$commands[] = ajax_command_replace('#emp_group_replace_div_p', drupal_render($form['emp_group_p']));
		$commands[] = ajax_command_replace('#pay_scale_replace_div_p', drupal_render($form['pay_scale_p']));
		$commands[] = ajax_command_replace('#release_date_replace_div_p', drupal_render($form['release_date_p']));
		$commands[] = ajax_command_replace('#date_with_effect_from_replace_div_p', drupal_render($form['date_with_effect_from_p']));
		$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
		$commands[] = ajax_command_replace('#district_code_replace_div', drupal_render($form['district_code_blank']));
		$commands[] = ajax_command_replace('#emp_group_replace_div_tp', drupal_render($form['emp_group_tp_blank']));
		$commands[] = ajax_command_replace('#pay_scale_replace_div_tp', drupal_render($form['pay_scale_tp_blank']));
		$commands[] = ajax_command_replace('#transfer_submit_replace_div_p', '<div id="transfer_submit_replace_div_p">'.drupal_render($form['transfer_submit_p']).'</div>');
	}elseif(isset($form_state['values']['type']) && trim($form_state['values']['type']) != '' && trim($form_state['values']['type']) == 'TP'){
		$commands[] = ajax_command_replace('#district_code_replace_div', drupal_render($form['district_code_tp']));
		$commands[] = ajax_command_replace('#order_no_replace_div_p', drupal_render($form['order_no_p_blank']));
		$commands[] = ajax_command_replace('#designation_replace_div', drupal_render($form['designation_blank']));
		$commands[] = ajax_command_replace('#emp_group_replace_div_p', drupal_render($form['emp_group_p_blank']));
		$commands[] = ajax_command_replace('#pay_scale_replace_div_p', drupal_render($form['pay_scale_p_blank']));
		$commands[] = ajax_command_replace('#release_date_replace_div_p', drupal_render($form['release_date_blank_p']));
		$commands[] = ajax_command_replace('#date_with_effect_from_replace_div_p', drupal_render($form['date_with_effect_from_blank_p']));
		$commands[] = ajax_command_replace('#transfer_submit_replace_div_p', '<div id="transfer_submit_replace_div_p">'.drupal_render($form['transfer_submit_p_blank']).'</div>');
	}else{
		$commands[] = ajax_command_replace('#district_code_replace_div', drupal_render($form['district_code_blank']));
		$commands[] = ajax_command_replace('#order_no_replace_div_p', drupal_render($form['order_no_p_blank']));
		$commands[] = ajax_command_replace('#designation_replace_div', drupal_render($form['designation_blank']));
		$commands[] = ajax_command_replace('#emp_group_replace_div_p', drupal_render($form['emp_group_p_blank']));
		$commands[] = ajax_command_replace('#pay_scale_replace_div_p', drupal_render($form['pay_scale_p_blank']));
		$commands[] = ajax_command_replace('#emp_group_replace_div_tp', drupal_render($form['emp_group_tp_blank']));
		$commands[] = ajax_command_replace('#pay_scale_replace_div_tp', drupal_render($form['pay_scale_tp_blank']));
		$commands[] = ajax_command_replace('#release_date_replace_div_p', drupal_render($form['release_date_blank_p']));
		$commands[] = ajax_command_replace('#date_with_effect_from_replace_div_p', drupal_render($form['date_with_effect_from_blank_p']));
		$commands[] = ajax_command_replace('#transfer_submit_replace_div_p', '<div id="transfer_submit_replace_div_p">'.drupal_render($form['transfer_submit_p_blank']).'</div>');
	}
	$commands[] = ajax_command_replace('#office_id_replace_div', drupal_render($form['office_id_blank']));
	$commands[] = ajax_command_replace('#office_id_replace_div_tp', drupal_render($form['office_id_blank_tp']));
	
	$commands[] = ajax_command_replace('#order_no_replace_div', drupal_render($form['order_no_blank']));
	$commands[] = ajax_command_replace('#release_date_replace_div', drupal_render($form['release_date_blank']));
	$commands[] = ajax_command_replace('#transfer_submit_replace_div', '<div id="transfer_submit_replace_div">'.drupal_render($form['transfer_submit_blank']).'</div>');
	
	$commands[] = ajax_command_replace('#order_no_replace_div_tp', drupal_render($form['order_no_blank_tp']));
	$commands[] = ajax_command_replace('#release_date_replace_div_tp', drupal_render($form['release_date_blank_tp']));
	$commands[] = ajax_command_replace('#designation_replace_div_tp', drupal_render($form['designation_tp_blank']));
	$commands[] = ajax_command_replace('#transfer_submit_replace_div_tp', '<div id="transfer_submit_replace_div_tp">'.drupal_render($form['transfer_submit_blank_tp']).'</div>');
	/*$commands[] = ajax_command_replace('#district_code_replace_div', drupal_render($form['district_code']));
	$commands[] = ajax_command_replace('#office_id_replace_div', drupal_render($form['office_id']));
	$commands[] = ajax_command_replace('#release_date_replace_div', drupal_render($form['release_date']));
	$commands[] = ajax_command_replace('#order_no_replace_div', drupal_render($form['order_no']));
	$commands[] = ajax_command_replace('#transfer_submit_replace_div', '<div id="transfer_submit_replace_div">'.drupal_render($form['transfer_submit_blank']).'</div>');*/
	return array('#type' => 'ajax', '#commands' => $commands);
}

function ajax_district_callback($form,&$form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#subdivision_replace_div', drupal_render($form['subdivision']));
	$commands[] = ajax_command_replace('#office_id_replace_div', drupal_render($form['office_id']));
	$commands[] = ajax_command_replace('#order_no_replace_div', drupal_render($form['order_no_blank']));
	$commands[] = ajax_command_replace('#release_date_replace_div', drupal_render($form['release_date_blank']));
	$commands[] = ajax_command_replace('#transfer_submit_replace_div', '<div id="transfer_submit_replace_div">'.drupal_render($form['transfer_submit_blank']).'</div>');
	//$commands[] = ajax_command_replace('#release_date_replace_div', drupal_render($form['release_date']));
	return array('#type' => 'ajax', '#commands' => $commands);
}
function ajax_district_callback_tp($form,&$form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#subdivision_replace_div', drupal_render($form['subdivision']));
	$commands[] = ajax_command_replace('#office_id_replace_div_tp', drupal_render($form['office_id_tp']));
	$commands[] = ajax_command_replace('#order_no_replace_div', drupal_render($form['order_no_blank']));
	$commands[] = ajax_command_replace('#release_date_replace_div', drupal_render($form['release_date_blank']));
	$commands[] = ajax_command_replace('#transfer_submit_replace_div', '<div id="transfer_submit_replace_div">'.drupal_render($form['transfer_submit_blank']).'</div>');
	//$commands[] = ajax_command_replace('#release_date_replace_div', drupal_render($form['release_date']));
	return array('#type' => 'ajax', '#commands' => $commands);
}
 
function ajax_office_callback($form,&$form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#order_no_replace_div', '<div id="order_no_replace_div">'.drupal_render($form['order_no']).'</div>');
	$commands[] = ajax_command_replace('#release_date_replace_div', '<div id="release_date_replace_div">'.drupal_render($form['release_date']).'</div>');
	$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
	$commands[] = ajax_command_replace('#transfer_submit_replace_div', '<div id="transfer_submit_replace_div">'.drupal_render($form['transfer_submit']).'</div>');
	return array('#type' => 'ajax', '#commands' => $commands);
}

function ajax_office_callback_tp($form,&$form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#order_no_replace_div_tp', '<div id="order_no_replace_div_tp">'.drupal_render($form['order_no_tp']).'</div>');
	$commands[] = ajax_command_replace('#release_date_replace_div_tp', '<div id="release_date_replace_div_tp">'.drupal_render($form['release_date_tp']).'</div>');
	$commands[] = ajax_command_replace('#designation_replace_div_tp', '<div id="designation_replace_div_tp">'.drupal_render($form['designation_tp']).'</div>');
	$commands[] = ajax_command_replace('#emp_group_replace_div_tp', '<div id="emp_group_replace_div_tp">'.drupal_render($form['emp_group_tp']).'</div>');
	$commands[] = ajax_command_replace('#pay_scale_replace_div_tp', '<div id="emp_group_replace_div_tp">'.drupal_render($form['pay_scale_tp']).'</div>');
	$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
	$commands[] = ajax_command_replace('#transfer_submit_replace_div_tp', '<div id="transfer_submit_replace_div_tp">'.drupal_render($form['transfer_submit_tp']).'</div>');
	return array('#type' => 'ajax', '#commands' => $commands);
}

function _reload_mem_order_list_transfer($form, $form_state) {
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	$commands   = array();
	$mydata = array();
	$output = '';
	$user_arr = explode('-',$form_state['values']['fname_transfer']);
	$header_info = array();
	$rows_info   = array();
	$header_info = array(  
	  array('data' => t('Employee Information'),'colspan' => 7),  
	);
	 $mydata = getUserInfoByUid($user_arr[1]);
 	 if(!empty($mydata)){	
 
	 $form['uid_transfer']['#value'] = $user_arr[1];
	 $form['user_service_id']['#value'] = $mydata['user_service_id'];
	 $form['designation_transfer']['#value'] = $mydata['designation'];
	 $form['directorate_transfer']['#value'] = $mydata['directorate_code'];
	 $form['district_transfer']['#value'] = $mydata['district_code'];
	 $form['doj_transfer']['#value'] = $mydata['doj'];
	 $form['pay_scale']['#value'] = $mydata['pay_scale'];
	 $form['emp_group']['#value'] = $mydata['emp_group'];
	 $form['direct_promotee']['#value'] = $mydata['direct_promotee'];
	 $form['promotion_date_empgroupa']['#value'] = $mydata['promotion_date_empgroupa'];
	 $form['asset_received_manner']['#value'] = $mydata['asset_received_manner'];
	 $form['transfer_from_office']['#value'] = $mydata['office_id'];
	 
	 
	$rows_info[] = array(  
	  array('data' => t('<b>HRMS ID  </b>')),
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Group  </b>')),
	  array('data' => t('<b>Pay Scale  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	  array('data' => t('<b>Directorate Name  </b>')),
	  array('data' => t('<b>District Name  </b>')),
	);
	$rows_info[] = array( 
	  array('data' => t($mydata['hrms_id'])),	
	  array('data' => t($mydata['fname'])),
	  array('data' => t($mydata['emp_group'])),
	  array('data' => t($mydata['pay_scale'])),
	  array('data' => t($mydata['designation'])), 	 
	  array('data' => t($mydata['directorate_name'])), 
	  array('data' => t($mydata['district_name'])),
	);
	
	$output_info = theme_table(
		array(
		  'header' => $header_info,
		  'rows' => $rows_info,
		  'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	  
	  $output = getFinancialYear($user_arr[1]);
	  

 $commands[] = ajax_command_replace('#user_service_map_backlog', '<div id="user_service_map_backlog">'.drupal_render($form['user_service_id']).'</div>');			 
 $commands[] = ajax_command_replace('#order_no_map_backlog', '<div id="order_no_map_backlog">'.drupal_render($form['uid_transfer']).'</div>');
 $commands[] = ajax_command_replace('#designation_map_backlog', '<div id="designation_map_backlog">'.drupal_render($form['designation_transfer']).'</div>');
 $commands[] = ajax_command_replace('#directorate_map_backlog', '<div id="directorate_map_backlog">'.drupal_render($form['directorate_transfer']).'</div>');
 $commands[] = ajax_command_replace('#district_map_backlog', '<div id="district_map_backlog">'.drupal_render($form['district_transfer']).'</div>'); 
 $commands[] = ajax_command_replace('#doj_map_backlog', '<div id="doj_map_backlog">'.drupal_render($form['doj_transfer']).'</div>'); 
 $commands[] = ajax_command_replace('#pay_scale_backlog', '<div id="pay_scale_backlog">'.drupal_render($form['pay_scale']).'</div>'); 
 $commands[] = ajax_command_replace('#emp_group_backlog', '<div id="emp_group_backlog">'.drupal_render($form['emp_group']).'</div>'); 
 $commands[] = ajax_command_replace('#direct_promotee_backlog', '<div id="direct_promotee_backlog">'.drupal_render($form['direct_promotee']).'</div>'); 
 $commands[] = ajax_command_replace('#promotion_date_empgroupa_backlog', '<div id="promotion_date_empgroupa_backlog">'.drupal_render($form['promotion_date_empgroupa']).'</div>'); 
 $commands[] = ajax_command_replace('#asset_received_manner_backlog', '<div id="asset_received_manner_backlog">'.drupal_render($form['asset_received_manner']).'</div>'); 
 $commands[] = ajax_command_replace('#transfer_from_office_backlog', '<div id="transfer_from_office_backlog">'.drupal_render($form['transfer_from_office']).'</div>'); 
 
 $commands[] = ajax_command_replace('#fetch_data_map_backlog', '<div id="fetch_data_map_backlog"><div class="col-md-12">'.$output_info.'</div></div>');
 $commands[] = ajax_command_replace('#fetch_data_map_year', '<div id="fetch_data_map_year"><div class="col-md-12">'.$output.'</div></div>');
 
 $commands[] = ajax_command_replace('#type_replace_div', '<div id="type_replace_div">'.drupal_render($form['type']).'</div>');
 
 $commands[] = ajax_command_replace('#district_code_replace_div', drupal_render($form['district_code_blank']));
 $commands[] = ajax_command_replace('#office_id_replace_div', drupal_render($form['office_id_blank']));
 $commands[] = ajax_command_replace('#release_date_replace_div', drupal_render($form['release_date_blank']));
 $commands[] = ajax_command_replace('#order_no_replace_div', drupal_render($form['order_no_blank']));
 $commands[] = ajax_command_replace('#transfer_submit_replace_div', '<div id="transfer_submit_replace_div">'.drupal_render($form['transfer_submit_blank']).'</div>');
 
	}else{
		$form['uid_transfer']['#value'] = '';	
		 $rows_info[] = array(  
			  array('data' => t('<b>You are not allowed to transfer the employee</b>')),
		  );
		  
		  $output_info = theme_table(
			array(
			  'header' => $header_info,
			  'rows' => $rows_info,
			  'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
			  'sticky' => true,
			  'caption' => '',
			  'colgroups' => array(),
			  'empty' => t("No data found!") // The message to be displayed if table is empty
			)
		  ).theme('pager');	
		  
		  $commands[] = ajax_command_replace('#order_no_map_backlog', '<div id="order_no_map_backlog">'.drupal_render($form['uid_transfer']).'</div>');
		  $commands[] = ajax_command_replace('#fetch_data_map_backlog', '<div id="fetch_data_map_backlog"><div class="col-md-12">'.$output_info.'</div></div>');
		  $commands[] = ajax_command_replace('#fetch_data_map_year', '<div id="fetch_data_map_year"><div class="col-md-12">'.$output.'</div></div>');
		  $commands[] = ajax_command_replace('#type_replace_div', '<div id="type_replace_div">'.drupal_render($form['type_blank']).'</div>');
		  
	 }   
 
 return array('#type' => 'ajax', '#commands' => $commands);
}

function getFinancialYear($uid){
	$mydata = getUserInfoByUid($uid);
	$header = array();
	$rows   = array();
	$output = '<div id="parent_table_div_sar"><table class="table pretty table-bordered table-hover sticky-enabled tableheader-processed sticky-table"><thead><tr><th colspan="6">Office Details</th></tr></thead>';
	 	
	$OfficeAddress = db_select('a_office_master','aom');
	$OfficeAddress->fields('aom', array('office_id','office_name','directorate_code','is_active','office_address')); 
	$OfficeAddress->condition('aom.office_id',$mydata['office_id'],'=');
	$result = $OfficeAddress->execute();
	$OfficeData = $result->fetchAssoc();
	$output .= '<tr>';
	$output .= '<td>Office Name</td><td>'.$OfficeData['office_name'].'</td>'; 	
	$output .= '</tr><tr>';
	$output .= '<td>Office Address</td><td>'.$OfficeData['office_address'].'</td>'; 	
	$output .='</tr></table></div>';
	
	return $output;	
}



function employee_transfer_form_submit($form, &$form_state){
	//print_r($form_state['values']);	
	//exit;
	global $user;
	if($form_state['values']['type'] == 'T'){
		$query = db_update('a_user_details_service');
		$query->fields(array(
							'service_status' => 0, 
							/*'order_no' => trim($form_state['values']['order_no']),
							'release_date' => trim($form_state['values']['release_date']),
							'transfer_promotion_type' => trim($form_state['values']['type']),
							'transfer_by' => $user->uid*/
							));
		$query->condition('uid', trim($form_state['values']['uid_transfer']), '=');
		$query->condition('service_status', 1, '=');
		$rs = $query->execute();
		if($rs){
				/*$query_insert = array(
						'uid' => trim($form_state['values']['uid_transfer']),
						'directorate_code' => trim($form_state['values']['directorate_transfer']),
						'district_code' => trim($form_state['values']['district_code']),
						'designation' =>trim($form_state['values']['designation_transfer']),
						'pay_scale' => trim($form_state['values']['pay_scale']),
						'emp_group' => trim($form_state['values']['emp_group']),
						'direct_promotee' => trim($form_state['values']['direct_promotee']),
						'promotion_date_empgroupa' => date('Y-m-d H:i:s',strtotime(trim($form_state['values']['promotion_date_empgroupa']))),
						'asset_received_manner' => trim($form_state['values']['asset_received_manner']),
						'office_id' => trim($form_state['values']['office_id']),
						'transfer_from_office' => trim($form_state['values']['transfer_from_office']),
						'subdivision' => '0',
						'service_status' => 2,
						'order_no' => trim($form_state['values']['order_no']),
					);	*/
				$query_insert = array(
						'uid' => trim($form_state['values']['uid_transfer']),
						'user_service_id' => trim($form_state['values']['user_service_id']),
						'transfer_from_office' => trim($form_state['values']['transfer_from_office']),
						'transfer_to_office' => trim($form_state['values']['office_id']),
						'pre_designation' =>trim($form_state['values']['designation_transfer']),
						'designation' =>trim($form_state['values']['designation_transfer']),
						'pre_pay_scale' => trim($form_state['values']['pay_scale']),
						'pay_scale' => trim($form_state['values']['pay_scale']),
						'pre_emp_group' => trim($form_state['values']['emp_group']),
						'emp_group' => trim($form_state['values']['emp_group']),
						'order_no' => trim($form_state['values']['order_no']),
						//'release_date' => trim($form_state['values']['release_date']),
						'release_date' => date('Y-m-d H:i:s',strtotime(trim($form_state['values']['release_date']))),
						'transfer_promotion_type' => trim($form_state['values']['type']),
						'transfer_by' => $user->uid,
						'status' => 'P',
                        'district_code' => trim($form_state['values']['district_code'])
					);	
					
			$id = db_insert('a_user_transfer')->fields($query_insert)->execute();
			drupal_set_message('Employee Successfully Transfer');		
		}else{
			drupal_set_message('Unable to Transfer. Please contact to System administrator.');
		}
	}elseif($form_state['values']['type'] == 'P'){
		$query_insert = array(
						'uid' => trim($form_state['values']['uid_transfer']),
						'user_service_id' => trim($form_state['values']['user_service_id']),
						'transfer_from_office' => trim($form_state['values']['transfer_from_office']),
						'transfer_to_office' => trim($form_state['values']['transfer_from_office']),
						'pre_designation' =>trim($form_state['values']['designation_transfer']),
						'designation' =>trim($form_state['values']['designation']),
						'pre_pay_scale' => trim($form_state['values']['pay_scale']),
						'pay_scale' => trim($form_state['values']['pay_scale_p']),
						'pre_emp_group' => trim($form_state['values']['emp_group']),
						'emp_group' => trim($form_state['values']['emp_group_p']),
						'order_no' => trim($form_state['values']['order_no_p']),
						'release_date' => date('Y-m-d H:i:s',strtotime(trim($form_state['values']['release_date_p']))),
						//'release_date' => trim($form_state['values']['release_date_p']),
						'joining_date' => date('Y-m-d H:i:s',strtotime(trim($form_state['values']['date_with_effect_from_p']))),
						'transfer_promotion_type' => trim($form_state['values']['type']),
						'accepted_by' => $user->uid,
						'status' => 'A',
					);	
					
		$id = db_insert('a_user_transfer')->fields($query_insert)->execute();
		
		if($id){
				/*$query_insert = array(
						'uid' => trim($form_state['values']['uid_transfer']),
						'directorate_code' => trim($form_state['values']['directorate_transfer']),
						'district_code' => trim($form_state['values']['district_transfer']),
						'designation' =>trim($form_state['values']['designation']),
						'pay_scale' => trim($form_state['values']['pay_scale_p']),
						'emp_group' => trim($form_state['values']['emp_group_p']),
						'direct_promotee' => trim($form_state['values']['direct_promotee']),
						'promotion_date_empgroupa' => date('Y-m-d H:i:s'),
						'asset_received_manner' => trim($form_state['values']['asset_received_manner']),
						'office_id' => trim($form_state['values']['transfer_from_office']),
						'subdivision' => '0',
						'service_status' => 1,
						'order_no' => trim($form_state['values']['order_no_p']),
						'joining_date'=>date('Y-m-d'),
					);	*/
				$query = db_update('a_user_details_service');
				$query->fields(array(
									'designation' =>trim($form_state['values']['designation']),
									'pay_scale' => trim($form_state['values']['pay_scale_p']),
									'emp_group' => trim($form_state['values']['emp_group_p']),
									));
				$query->condition('user_service_id', trim($form_state['values']['user_service_id']), '=');
				$rs = $query->execute();	
				
			drupal_set_message('Employee Successfully Promoted');		
		}else{
			drupal_set_message('Unable to Transfer. Please contact to System administrator.');
		}
	}elseif($form_state['values']['type'] == 'TP'){
		$query = db_update('a_user_details_service');
		$query->fields(array(
							'service_status' => 0, 
							/*'order_no' => trim($form_state['values']['order_no_tp']),
							'release_date' => trim($form_state['values']['release_date_tp']),
							'transfer_promotion_type' => trim($form_state['values']['type']),
							'transfer_by' => $user->uid*/
							));
		$query->condition('uid', trim($form_state['values']['uid_transfer']), '=');
		$query->condition('service_status', 1, '=');
		$rs = $query->execute();
		if($rs){
				/*$query_insert = array(
						'uid' => trim($form_state['values']['uid_transfer']),
						'directorate_code' => trim($form_state['values']['directorate_transfer']),
						'district_code' => trim($form_state['values']['district_code_tp']),
						'designation' =>trim($form_state['values']['designation_tp']),
						'pay_scale' => trim($form_state['values']['pay_scale_tp']),
						'emp_group' => trim($form_state['values']['emp_group_tp']),
						'direct_promotee' => trim($form_state['values']['direct_promotee']),
						'promotion_date_empgroupa' => date('Y-m-d H:i:s'),
						'asset_received_manner' => trim($form_state['values']['asset_received_manner']),
						'office_id' => trim($form_state['values']['office_id_tp']),
						'transfer_from_office' => trim($form_state['values']['transfer_from_office']),
						'subdivision' => '0',
						'service_status' => 2,
						'order_no' => trim($form_state['values']['order_no_tp']),
					);	*/
					
				$query_insert = array(
						'uid' => trim($form_state['values']['uid_transfer']),
						'user_service_id' => trim($form_state['values']['user_service_id']),
						'transfer_from_office' => trim($form_state['values']['transfer_from_office']),
						'transfer_to_office' => trim($form_state['values']['office_id_tp']),
						'pre_designation' =>trim($form_state['values']['designation_transfer']),
						'designation' =>trim($form_state['values']['designation_tp']),
						'pre_pay_scale' => trim($form_state['values']['pay_scale']),
						'pay_scale' => trim($form_state['values']['pay_scale_tp']),
						'pre_emp_group' => trim($form_state['values']['emp_group']),
						'emp_group' => trim($form_state['values']['emp_group_tp']),
						'order_no' => trim($form_state['values']['order_no_tp']),
						'release_date' => date('Y-m-d H:i:s',strtotime(trim($form_state['values']['release_date_tp']))),
						//'release_date' => trim($form_state['values']['release_date_tp']),
						'transfer_promotion_type' => trim($form_state['values']['type']),
						'transfer_by' => $user->uid,
						'status' => 'P',
						'district_code' => trim($form_state['values']['district_code_tp'])
					);		
					
			$id = db_insert('a_user_transfer')->fields($query_insert)->execute();
			drupal_set_message('Employee Successfully Transfer with Promotion');		
		}else{
			drupal_set_message('Unable to Transfer. Please contact to System administrator.');
		}
	}
	
	
	else{
		drupal_set_message('Unable to Transfer. Please select Transfer from dropdown.');
	}
}

function get_asset_user_transfer($string=''){
	
	global $user;
	
	$direc_code = getLoginUserDetailForAsset($user->uid);  
	
	$matches = array();
	$query = db_select('users', 'u');
	$query->leftJoin('users_roles', 'ur', 'u.uid = ur.uid');  
	$query->leftJoin('role', 'r', 'ur.rid = r.rid'); 
	$query->leftJoin('a_user_details', 'ud', 'u.uid = ud.uid');
	
	$query->leftJoin('a_user_details_service', 'us', 'u.uid = us.uid'); 
	$query->fields('us', array('designation','district_code','directorate_code')); 
	
	$query->fields('u', array('uid','name','access','created','status'));
	$query->fields('ud', array('fname'));
	$query->addField('r', 'name', 'rolename');
	$query->condition('ud.fname', '%' . trim($string) . '%', 'LIKE');
	if($user->uid != 1486){
		$query->condition('us.directorate_code',$direc_code['directorate_code'],'=');
	}
	
	if(in_array(variable_get('field', 11), array_keys($user->roles))){
		//$query->condition('us.emp_group','A','!=');
		$query->condition('us.office_id',$direc_code['office_id'],'=');
	}
	//$query->condition('us.emp_group','A','!=');
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

function getUserInfoByUid($uid){
	$query = db_select('users', 'u');
	$query->leftJoin('a_user_details', 'ud', 'u.uid = ud.uid');
	
	$query->leftJoin('a_user_details_service', 'us', 'u.uid = us.uid'); 
	$query->fields('us', array('user_service_id','designation','district_code','directorate_code','office_id','pay_scale','emp_group','direct_promotee','promotion_date_empgroupa','asset_received_manner','order_no','joining_date','release_date','transfer_from_office'));
	
	$query->leftJoin('a_directorate_mst', 'd', 'd.directorate_code = us.directorate_code'); 
	$query->fields('d', array('directorate_name')); 
	
	$query->leftJoin('district_master', 'dis', 'dis.district_code = us.district_code'); 
	$query->fields('dis', array('district_name')); 
	
	$query->fields('u', array('uid','name','access','created','status'));
	$query->fields('ud', array('fname','hrms_id','doj'));
	$query->condition('u.uid', $uid, '=');
	$query->condition('us.service_status', '1', '=');
	$result = $query->execute();
	$userData = $result->fetchAssoc();
	return $userData;
}

function employee_transfer_out_list(){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
		drupal_goto('profileupdate');
		exit;
	}	
	
	//$user_info = getUserInfoByUid($user->uid);
	//print_r($user_info); exit;
	
	// list for transfer out
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	
	$query = db_select('a_user_transfer', 'ut');
	$query->leftJoin('a_user_details', 'ud', 'ut.uid = ud.uid');
	
	$query->leftJoin('a_user_details_service', 'us', 'ut.uid = us.uid'); 
	$query->fields('us', array('uid','district_code','directorate_code','office_id','direct_promotee','promotion_date_empgroupa','asset_received_manner'));
	
	$query->fields('ut', array('transfer_id','user_service_id','transfer_from_office','transfer_to_office','pre_designation','pre_pay_scale','pre_emp_group','designation','pay_scale','emp_group','order_no','release_date','accepted_by','transfer_promotion_type','status'));
	
	$query->leftJoin('a_directorate_mst', 'd', 'd.directorate_code = us.directorate_code'); 
	$query->fields('d', array('directorate_name')); 
	
	$query->leftJoin('district_master', 'dis', 'dis.district_code = us.district_code'); 
	$query->fields('dis', array('district_name')); 
	
	$query->fields('ud', array('fname','hrms_id','doj'));
	//$query->condition('us.service_status', '0', '=');
	//$query->condition('us.transfer_promotion_type', 'P', '!=');
	$query->condition('ut.transfer_by', $user->uid, '=');
	$result = $query->execute();
	$resultData = $result->fetchAll();
	
	//print_r($resultData); exit;
	
	$output = '';
	$header = array(
				array('data'=> 'Sl No'),
				array('data'=> 'HRMS ID'),
				array('data'=> 'Employee Name'),
				array('data'=> 'Transfer From'),
				array('data'=> 'Transfer To'),
				array('data'=> 'Transfer Type'),
				array('data'=> 'Release Date'),
				array('data'=> 'Status'),
				array('data'=> 'Action')
			);
			
	$rows = array();
	$i = 0;
	foreach($resultData as $val){
		if(trim($val->status) == 'P'){
			$status = 'Approval Pending'; 
		}elseif(trim($val->status) == 'A'){
			$status = 'Approved'; 
		}elseif(trim($val->status) == 'R'){
			$status = 'Rejected'; 
		}else{
			$status = ''; 
		}
		$transfer_from = getOfficeName($val->transfer_from_office);
		$transfer_to = getOfficeName($val->transfer_to_office);
		
		if(trim($val->transfer_promotion_type) == 'T'){
			$transfer_promotion_type = 'Transfer'; 
		}elseif(trim($val->transfer_promotion_type) == 'P'){
			$transfer_promotion_type = 'Promotion'; 
		}elseif(trim($val->transfer_promotion_type) == 'TP'){
			$transfer_promotion_type = 'Transfer with Promotion'; 
		}else{
			$transfer_promotion_type = ''; 
		}
		
		$i++;	
	
	$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/view.png">'), 'transfer-out-display/'.$val->transfer_id, array('html' => TRUE,'attributes'=>array('title' => 'View')));
	  
	  $rows [] = array(  
	  		  $i,	
			  array('data' => t($val->hrms_id)),
			  array('data' => t($val->fname)),
			  array('data' => t($transfer_from['office_name'])),
			  array('data' => t($transfer_to['office_name'])),
			  array('data' => t($transfer_promotion_type)),
			  array('data' => trim(!empty($val->release_date)) ? t(date('d-m-Y',strtotime($val->release_date))) : 'N/A'),
			  array('data' => t($status)),
			  array('data' => t($link)),
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
		  'empty' => t("No data found") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	  
	return $output;	
}

function employee_transfer_in_list(){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
		drupal_goto('profileupdate');
		exit;
	}	
	
	$user_info = getUserInfoByUid($user->uid);
	//print_r($user_info); exit;
	
	// list for transfer out
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$query = db_select('a_user_transfer', 'ut');
	$query->leftJoin('a_user_details', 'ud', 'ut.uid = ud.uid');
	
	$query->leftJoin('a_user_details_service', 'us', 'ut.uid = us.uid'); 
	$query->fields('us', array('uid','district_code','directorate_code','office_id','direct_promotee','promotion_date_empgroupa','asset_received_manner'));
	
	$query->fields('ut', array('transfer_id','user_service_id','transfer_from_office','transfer_to_office','pre_designation','pre_pay_scale','pre_emp_group','designation','pay_scale','emp_group','order_no','release_date','accepted_by','transfer_promotion_type','status'));
	
	$query->leftJoin('a_directorate_mst', 'd', 'd.directorate_code = us.directorate_code'); 
	$query->fields('d', array('directorate_name')); 
	
	$query->leftJoin('district_master', 'dis', 'dis.district_code = us.district_code'); 
	$query->fields('dis', array('district_name')); 
	
	$query->fields('ud', array('fname','hrms_id','doj'));
	
	if(trim($user_info['office_id'])!='0'){
		$query->condition('ut.transfer_to_office', $user_info['office_id'], '=');
		$query->condition('us.directorate_code', $user_info['directorate_code'], '=');
	}
	if(trim($user_info['office_id'])=='0'){
		$query->condition('ut.transfer_to_office', 117, '=');
		$query->condition('us.directorate_code', $user_info['directorate_code'], '=');
	}
	$result = $query->execute();
	$resultData = $result->fetchAll();
	
	//print_r($resultData); exit;
	
	$output = '';
	$header = array(
				array('data'=> 'Sl No'),
				array('data'=> 'HRMS ID'),
				array('data'=> 'Employee Name'),
				//array('data'=> 'New Designation'),
				//array('data'=> 'Emp Group'),
				array('data'=> 'Transfer From'),
				array('data'=> 'Transfer To'),
				array('data'=> 'Transfer Type'),
				array('data'=> 'Status'),
				array('data'=> 'Action'),
			);
			
	$rows = array();
	$i = 0;
	foreach($resultData as $val){
		$transfer_from = getOfficeName($val->transfer_from_office);
		$transfer_to = getOfficeName($val->transfer_to_office);
		
		if(trim($val->status) == 'P'){
			$status = 'Approval Pending'; 
		}elseif(trim($val->status) == 'A'){
			$status = 'Approved'; 
		}elseif(trim($val->status) == 'R'){
			$status = 'Rejected'; 
		}else{
			$status = ''; 
		}
		if(trim($val->transfer_promotion_type) == 'T'){
			$transfer_promotion_type = 'Transfer'; 
		}elseif(trim($val->transfer_promotion_type) == 'P'){
			$transfer_promotion_type = 'Promotion'; 
		}elseif(trim($val->transfer_promotion_type) == 'TP'){
			$transfer_promotion_type = 'Transfer with Promotion'; 
		}else{
			$transfer_promotion_type = ''; 
		}
		
		
		$i++;	
	
		$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/view.png">'), 'transfer-accept/'.$val->transfer_id, array('html' => TRUE,'attributes'=>array('title' => 'View')));
	  
	  $rows [] = array(  
	  		  $i,	
			  array('data' => t($val->hrms_id)),
			  array('data' => t($val->fname)),
			  //array('data' => t($val->designation)),
			  //array('data' => t($val->emp_group)),
			  array('data' => t($transfer_from['office_name'])),
			  array('data' => t($transfer_to['office_name'])),
			  array('data' => t($transfer_promotion_type)),
			  array('data' => t($status)),
			  array('data' => $link),
		); 
		
		//}
	}
	
	$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found") // The message to be displayed if table is empty
		)
	  ).theme('pager');	
	  
	return $output;	
}

function getOfficeName($office_id){
	$OfficeAddress = db_select('a_office_master','aom');
	$OfficeAddress->fields('aom', array('office_id','office_name','directorate_code','is_active','office_address')); 
	$OfficeAddress->condition('aom.office_id', $office_id, '=');
	$result = $OfficeAddress->execute();
	$OfficeData = $result->fetchAssoc();
	return $OfficeData;
}

function transfer_display_form($form, &$form_state, $arg){
	global $user;
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
		
	$form['#attributes']['class'][] = 'form-vertical';
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Transfer Employee</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
		$mydata = array();
		
	$query = db_select('a_user_transfer', 'ut');
	$query->leftJoin('a_user_details', 'ud', 'ut.uid = ud.uid');
	
	$query->leftJoin('a_user_details_service', 'us', 'ut.uid = us.uid'); 
	$query->fields('us', array('uid','district_code','directorate_code','office_id','direct_promotee','promotion_date_empgroupa','asset_received_manner'));
	
	$query->fields('ut', array('transfer_id','user_service_id','transfer_from_office','transfer_to_office','pre_designation','pre_pay_scale','pre_emp_group','designation','pay_scale','emp_group','order_no','release_date','transfer_promotion_type','transfer_by','accepted_by','status'));
	
	$query->leftJoin('a_directorate_mst', 'd', 'd.directorate_code = us.directorate_code'); 
	$query->fields('d', array('directorate_name')); 
	
	$query->leftJoin('district_master', 'dis', 'dis.district_code = us.district_code'); 
	$query->fields('dis', array('district_name')); 
	
	$query->fields('ud', array('fname','hrms_id','doj'));
	$query->condition('ut.transfer_id', $arg, '=');
	$result = $query->execute();
	$mydata = $result->fetchAssoc();
	 //print_r($mydata); exit;
 	 if(!empty($mydata)){	
 
			$transfer_from = getOfficeName($mydata['transfer_from_office']);
			$transfer_to = getOfficeName($mydata['transfer_to_office']);
			
			if(trim($mydata['status']) == 'P'){
				$status = 'Approval Pending'; 
			}elseif(trim($mydata['status']) == 'A'){
				$status = 'Approved'; 
			}elseif(trim($mydata['status']) == 'R'){
				$status = 'Rejected'; 
			}else{
				$status = ''; 
			}
			
			if(trim($mydata['transfer_promotion_type']) == 'T'){
				$transfer_promotion_type = 'Transfer'; 
			}elseif(trim($mydata['transfer_promotion_type']) == 'P'){
				$transfer_promotion_type = 'Promotion'; 
			}elseif(trim($mydata['transfer_promotion_type']) == 'TP'){
				$transfer_promotion_type = 'Transfer with Promotion'; 
			}else{
				$transfer_promotion_type = ''; 
			}
			
			$basic = '';
			$header_info = array();
			$rows_info   = array();
			$header_info = array(  
			  array('data' => t('Employee Information'),'colspan' => 6),  
			); 	
			
			$rows_info[] = array(  
			  array('data' => t('<b>HRMS ID</b>')),
			  array('data' => t('<b>Officers Name </b>')),
			  array('data' => t('<b>Transfer From </b>')),
			  array('data' => t('<b>Transfer To</b>')),
			  array('data' => t('<b>Transfer Type</b>')),
			  array('data' => t('<b>Status</b>')),
			);
			$rows_info[] = array(  
			  array('data' => t($mydata['hrms_id'])),
			  array('data' => t($mydata['fname'])),
			  array('data' => t($transfer_from['office_name'])),
			  array('data' => t($transfer_to['office_name'])),
			  array('data' => t($transfer_promotion_type)),
			  array('data' => t($status)),
			);
			
			
			$basic = theme_table(
				array(
				  'header' => $header_info,
				  'rows' => $rows_info,
				  'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			  ).theme('pager');	
			
			$details = '';
			$header_details = array();
			$rows_details   = array();
			$header_details = array(  
			  array('data' => t('Employee Details Information'),'colspan' => 6),  
			); 	
			
			$rows_details[] = array(  
			  array('data' => t('<b>Previous Designation </b>')),
			  array('data' => t('<b>New Designation</b>')),
			  array('data' => t('<b>Previous Group </b>')),
			  array('data' => t('<b>New Group</b>')),
			  array('data' => t('<b>Previous Pay Scale</b>')),
			  array('data' => t('<b>New Pay Scale</b>')),
			);  
			$rows_details[] = array(  
			  array('data' => t($mydata['pre_designation'])),
			  array('data' => t($mydata['designation'])),
			  array('data' => t($mydata['pre_emp_group'])),
			  array('data' => t($mydata['emp_group'])),
			  array('data' => t($mydata['pre_pay_scale'])),
			  array('data' => t($mydata['pay_scale'])),
			);  
			$details = theme_table(
				array(
				  'header' => $header_details,
				  'rows' => $rows_details,
				  'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			  ).theme('pager');	  
	 }
	 
	 $form['transfer_info_basic'] = array(
		'#prefix' => '<div class="col-md-12">'.$basic,
		'#suffix' => '</div>'
	 );
	 $form['transfer_info_details'] = array(
		'#prefix' => '<div class="col-md-12">'.$details,
		'#suffix' => '</div>'
	 );
	 
	 $form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	 return $form;
}

function transfer_accepted_form($form, &$form_state, $arg){
	//echo $arg; exit;
	global $user;
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
		
	$form['#attributes']['class'][] = 'form-vertical';
	$form['form_begin'] = array(
    	'#type' => 'markup',
    	'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Transfer Employee</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
		$mydata = array();
		
	$query = db_select('a_user_transfer', 'ut');
	$query->leftJoin('a_user_details', 'ud', 'ut.uid = ud.uid');
	
	$query->leftJoin('a_user_details_service', 'us', 'ut.uid = us.uid'); 
	$query->fields('us', array('uid','directorate_code','office_id','direct_promotee','promotion_date_empgroupa','asset_received_manner'));
	
	$query->fields('ut', array('transfer_id','user_service_id','transfer_from_office','transfer_to_office','pre_designation','pre_pay_scale','pre_emp_group','designation','pay_scale','emp_group','order_no','release_date','transfer_promotion_type','transfer_by','accepted_by','status','district_code'));
	
	$query->leftJoin('a_directorate_mst', 'd', 'd.directorate_code = us.directorate_code'); 
	$query->fields('d', array('directorate_name')); 
	
	$query->leftJoin('district_master', 'dis', 'dis.district_code = us.district_code'); 
	$query->fields('dis', array('district_name')); 
	
	$query->fields('ud', array('fname','hrms_id','doj'));
	$query->condition('ut.transfer_id', $arg, '=');
	$result = $query->execute();
	$mydata = $result->fetchAssoc();
	 //print_r($mydata); exit;
 	 if(!empty($mydata)){	
 
			$transfer_from = getOfficeName($mydata['transfer_from_office']);
			$transfer_to = getOfficeName($mydata['transfer_to_office']);
			
			if(trim($mydata['status']) == 'P'){
				$status = 'Approval Pending'; 
			}elseif(trim($mydata['status']) == 'A'){
				$status = 'Approved'; 
			}elseif(trim($mydata['status']) == 'R'){
				$status = 'Rejected'; 
			}else{
				$status = ''; 
			}
			
			if(trim($mydata['transfer_promotion_type']) == 'T'){
				$transfer_promotion_type = 'Transfer'; 
			}elseif(trim($mydata['transfer_promotion_type']) == 'P'){
				$transfer_promotion_type = 'Promotion'; 
			}elseif(trim($mydata['transfer_promotion_type']) == 'TP'){
				$transfer_promotion_type = 'Transfer with Promotion'; 
			}else{
				$transfer_promotion_type = ''; 
			}
			
			$basic = '';
			$header_info = array();
			$rows_info   = array();
			$header_info = array(  
			  array('data' => t('Employee Information'),'colspan' => 6),  
			); 	
			
			$rows_info[] = array(  
			  array('data' => t('<b>HRMS ID</b>')),
			  array('data' => t('<b>Officers Name </b>')),
			  array('data' => t('<b>Transfer From </b>')),
			  array('data' => t('<b>Transfer To</b>')),
			  array('data' => t('<b>Transfer Type</b>')),
			  array('data' => t('<b>Status</b>')),
			);
			$rows_info[] = array(  
			  array('data' => t($mydata['hrms_id'])),
			  array('data' => t($mydata['fname'])),
			  array('data' => t($transfer_from['office_name'])),
			  array('data' => t($transfer_to['office_name'])),
			  array('data' => t($transfer_promotion_type)),
			  array('data' => t($status)),
			);
			
			
			$basic = theme_table(
				array(
				  'header' => $header_info,
				  'rows' => $rows_info,
				  'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			  ).theme('pager');	
			
			$details = '';
			$header_details = array();
			$rows_details   = array();
			$header_details = array(  
			  array('data' => t('Employee Details Information'),'colspan' => 6),  
			); 	
			
			$rows_details[] = array(  
			  array('data' => t('<b>Previous Designation </b>')),
			  array('data' => t('<b>New Designation</b>')),
			  array('data' => t('<b>Previous Group </b>')),
			  array('data' => t('<b>New Group</b>')),
			  array('data' => t('<b>Previous Pay Scale</b>')),
			  array('data' => t('<b>New Pay Scale</b>')),
			);  
			$rows_details[] = array(  
			  array('data' => t($mydata['pre_designation'])),
			  array('data' => t($mydata['designation'])),
			  array('data' => t($mydata['pre_emp_group'])),
			  array('data' => t($mydata['emp_group'])),
			  array('data' => t($mydata['pre_pay_scale'])),
			  array('data' => t($mydata['pay_scale'])),
			);  
			$details = theme_table(
				array(
				  'header' => $header_details,
				  'rows' => $rows_details,
				  'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			  ).theme('pager');	  
	 }
	 
	 $form['transfer_info_basic'] = array(
		'#prefix' => '<div class="col-md-12">'.$basic,
		'#suffix' => '</div>'
	 );
	 $form['transfer_info_details'] = array(
		'#prefix' => '<div class="col-md-12">'.$details,
		'#suffix' => '</div>'
	 );
	 if(trim($mydata['accepted_by'])==""){
		 $form['transfer_id'] = array(
			'#type' => 'hidden',
			'#title' => t('Transfer Id'),
			//'#id' =>'order_no_map',
			'#default_value'=>$mydata['transfer_id'],
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Transfer Id'),
			//'#prefix' => '<div class="col-md-3">',
			//'#suffix' => '</div>'
		 );
		 $form['transfer_promotion_type'] = array(
			'#type' => 'hidden',
			'#title' => t('Transfer Promotion Type'),
			//'#id' =>'order_no_map',
			'#default_value'=>$mydata['transfer_promotion_type'],
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Transfer Promotion Type'),
			//'#prefix' => '<div class="col-md-3">',
			//'#suffix' => '</div>'
		 );
		 $form['designation'] = array(
			'#type' => 'hidden',
			'#title' => t('Designation'),
			//'#id' =>'order_no_map',
			'#default_value'=>$mydata['designation'],
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
			//'#prefix' => '<div class="col-md-3">',
			//'#suffix' => '</div>'
		 );
		 $form['emp_group'] = array(
			'#type' => 'hidden',
			'#title' => t('Emp Group'),
			//'#id' =>'order_no_map',
			'#default_value'=>$mydata['emp_group'],
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Emp Group'),
			//'#prefix' => '<div class="col-md-3">',
			//'#suffix' => '</div>'
		 );
		 $form['pay_scale'] = array(
			'#type' => 'hidden',
			'#title' => t('Pay Scale'),
			//'#id' =>'order_no_map',
			'#default_value'=>$mydata['pay_scale'],
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Pay Scale'),
			//'#prefix' => '<div class="col-md-3">',
			//'#suffix' => '</div>'
		 );
          $form['district_code'] = array(
            '#type' => 'hidden',
            '#title' => t('District code'),
            //'#id' =>'order_no_map',
            '#default_value'=>$mydata['district_code'],
            '#required' => TRUE,
            '#attributes' => array('class'=>array('form-control'),'placeholder'=>'District code'),
            //'#prefix' => '<div class="col-md-3">',
            //'#suffix' => '</div>'
         );
         
		  $form['user_service_id'] = array(
			'#type' => 'hidden',
			'#title' => t('User Service Id'),
			//'#id' =>'order_no_map',
			'#default_value'=>$mydata['user_service_id'],
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'User Service Id'),
			//'#prefix' => '<div class="col-md-3">',
			//'#suffix' => '</div>'
		 );
		 $form['transfer_from_office'] = array(
			'#type' => 'hidden',
			'#title' => t('Transfer From Office'),
			//'#id' =>'order_no_map',
			'#default_value'=>$mydata['transfer_from_office'],
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Transfer From Office'),
			//'#prefix' => '<div class="col-md-3">',
			//'#suffix' => '</div>'
		 );
		 $form['transfer_to_office'] = array(
			'#type' => 'hidden',
			'#title' => t('Transfer To Office'),
			//'#id' =>'order_no_map',
			'#default_value'=>$mydata['transfer_to_office'],
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Transfer To Office'),
			//'#prefix' => '<div class="col-md-3">',
			//'#suffix' => '</div>'
		 );
		 $form['accept_reject'] = array(
			'#type' => 'select',
			'#title' => t('Accept / Reject'),
			'#options' => array('A'=>'Accept','R'=>'Reject'),
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Accept / Reject'),
			'#prefix' => '<div class="col-md-3">',
			'#suffix' => '</div>'
		 );
		 $form['accept_dt'] = array(
			'#type' => 'textfield',
			'#title' => t('Date'),
			//'#value'=>'',
			'#required' => TRUE,
			'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date', 'autocomplete'=>'off'),
			'#prefix' => '<div class="col-md-3">',
			'#suffix' => '</div>'
		 );
		 $form['accept_submit'] = array(
			'#type' => 'submit',
			'#value' => t('Submit'),
			'#attributes' => array('class'=>array('btn btn-info')),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		 );
	 }
	 $form['form_end'] = array(
	 '#type' => 'markup',
	 '#markup' => '</div>',
	 '#suffix' => '</div></div>'
    );	
	 return $form;
}

function transfer_accepted_form_submit($form, &$form_state){
	global $user;
	if($form_state['values']['accept_reject'] == 'A'){
		$query = db_update('a_user_details_service');
		$query->fields(array(
							'service_status' => 1, 
							'designation' => trim($form_state['values']['designation']),
							'emp_group' => trim($form_state['values']['emp_group']),
							'pay_scale' => trim($form_state['values']['pay_scale']),
							'office_id' => trim($form_state['values']['transfer_to_office']),
                            'district_code'=>trim($form_state['values']['district_code'])
							));
		$query->condition('user_service_id', trim($form_state['values']['user_service_id']), '=');
		$rs = $query->execute();
		
		$query1 = db_update('a_user_transfer');
		$query1->fields(array('joining_date' => date('Y-m-d H:i:s',strtotime(trim($form_state['values']['accept_dt']))),
							  //'joining_date' => trim($form_state['values']['accept_dt']),
							  'accepted_by' => $user->uid, 'status'=>'A'));
		$query1->condition('transfer_id', trim($form_state['values']['transfer_id']), '=');
		$rs1 = $query1->execute();
		
		if($rs1){
			drupal_set_message('Successfully Accepted');
		}else{
			drupal_set_message('Unable to accept. Please try again later.');
		}
	}
	
	if($form_state['values']['accept_reject'] == 'R'){
		$query = db_update('a_user_details_service');
		$query->fields(array('service_status' => 1));
		$query->condition('user_service_id', trim($form_state['values']['user_service_id']), '=');
		$rs = $query->execute();
		
		$query1 = db_update('a_user_transfer');
		$query1->fields(array('joining_date' => date('Y-m-d H:i:s',strtotime(trim($form_state['values']['accept_dt']))),
							  //'joining_date' => trim($form_state['values']['accept_dt']), 
							  'accepted_by' => $user->uid, 'status'=>'R'));
		$query1->condition('transfer_id', trim($form_state['values']['transfer_id']), '=');
		$rs1 = $query1->execute();
		
		if($rs1){
			drupal_set_message('Successfully Rejected');
		}else{
			drupal_set_message('Unable to accept. Please try again later.');
		}
	}
	
	drupal_goto('employee-transfer-in-list');
}