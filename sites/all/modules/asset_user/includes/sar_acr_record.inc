<?php

function sar_acr_record_form($form, &$form_state){
	ctools_include('modal');
	ctools_modal_add_js();
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
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">SAR / ACR Availability</h4></div><div class="widget-main">',
		//'#suffix' => '</h4>'
	 );
	 
	 /*$form['decission_sacracr'] = array(
		'#type' => 'hidden',
		'#title' => t('Decission'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Decission'),
		'#prefix' => '<div id="decission_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 ); */
	 
	 $form['fname_saracr'] = array(
		'#type' => 'textfield',
		'#autocomplete_path' => 'getassetuser/autocompletesaracr',
		'#ajax' => array('event' => 'blur',
                      'callback' => '_reload_mem_order_list_saracr',
                      'effect' => 'fade',
                      'progress' => array('type' => '','message' => '',),
                   ),
		'#title' => t('Enter Officers Name'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Enter Officers Name'),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	 ); 
	 
  $form['uid_saracr'] = array(
		'#type' => 'hidden',
		'#title' => t('User Id Backlog'),
		//'#id' =>'order_no_map',
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('doc_name_clear','form-control'),'placeholder'=>'User Id Backlog'),
		'#prefix' => '<div id="order_no_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 
 $form['designation_saracr'] = array(
		'#type' => 'hidden',
		'#title' => t('Designation'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
		'#prefix' => '<div id="designation_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 ); 
	 
	$form['district_saracr'] = array(
		'#type' => 'hidden',
		'#title' => t('District'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'District'),
		'#prefix' => '<div id="district_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 
	$form['directorate_saracr'] = array(
		'#type' => 'hidden',
		'#title' => t('Directorate'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Directorate'),
		'#prefix' => '<div id="directorate_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );  
	 
	 $form['doj_saracr'] = array(
		'#type' => 'hidden',
		'#title' => t('DOJ'),
		//'#value'=>'',
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'DOJ'),
		'#prefix' => '<div id="doj_map_backlog"><div class="col-md-3">',
		'#suffix' => '</div></div>'
	 );
	 
	 
	 $form['fetch_data_saracr'] = array(
		'#prefix' => '<div id="fetch_data_map_backlog"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );
	 
	 $form['fetch_data_year'] = array(
		'#prefix' => '<div id="fetch_data_map_year"><div class="col-md-12">',
		'#suffix' => '</div></div>'
	 );
	 
	 /*$form['submit'] = array (
        '#type' => 'submit',
        '#value' => 'Update',
		'#attributes' => array('class'=>array('btn btn-success pull-left')),
		'#prefix' => '<div id="frmbtn_backlog" style="display:none"><div class="col-md-3">',
  		'#suffix' => '</div></div>',
     ); */
	 
	/* $form['btn_link'] = array (
	 '#type' => 'markup',
	 '#markup' => '<div id="btn_link"><div class="col-md-3"></div></div>',
	);*/
	
	if(isset($form_state['values']['fname_saracr']) && $form_state['values']['fname_saracr']!=""){
		$user_arr = explode('-',$form_state['values']['fname_saracr']);
		$mydata = getUserInfoByUid($user_arr[1]);
		$financial_yr = array();
		$dojyr = explode('-',$mydata['doj']);
		  for($y=$dojyr[0]; $y<=date('Y'); $y++){
				$rsData = array();
				$query = db_select('a_sar_file', 'f');
				$query ->fields('f', array( 'asr_id', 'uid', 'financial_yr', 'doj_yr', 'directorate_code', 'district_code','file_name','sar_file','status'));
				$query->condition('f.uid',$user_arr[1], '='); 
				$query->condition('f.financial_yr', trim($y.'-'.($y+1)), '='); 
				$result = $query->execute();
				$rsData = $result->fetchAll();
				if(empty($rsData)){
					$financial_yr[trim($y.'-'.($y+1))] = trim($y.'-'.($y+1));
				}
		  }
		$form['fy'] = array(
			'#type' => 'select',
			'#title' => t('Financial Year'),
			'#required' => TRUE,
			'#options' => $financial_yr,
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Financial Year',),
			'#prefix' => '<div id="fy_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		);
		$form['doc_file'] = array(
			'#type' => 'file',
			'#required' => TRUE,
			'#title' => t('Upload (PDF only)'),
			'#description' => t('Max size 1MB'),
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Upload documents'),
			'#prefix' => '<div id="doc_file_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
	    );
		$form['type'] = array(
			'#type' => 'select',
			'#title' => t('Type'),
			'#required' => TRUE,
			'#options' => array('Old'=>'Old','New'=>'New'),
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Type'),
			'#prefix' => '<div id="type_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
	    );
		$form['comment'] = array(
			'#type' => 'select',
			'#title' => t('Comment'),
			'#required' => TRUE,
			'#options' => array(''=>'-select-','Outstanding'=>'Outstanding','Excellent'=>'Excellent','Very Good'=>'Very Good','Good'=>'Good','Average'=>'Average','Poor'=>'Poor'),
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Comment'),
			'#prefix' => '<div id="comment_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
	    );
		$form['rating'] = array(
			'#type' => 'textfield',
			'#title' => t('Rating'),
			'#required' => TRUE,
			'#attributes' => array('id'=>'rating_clear_div','class'=>array('form-control','doc_name_clear'),'placeholder'=>'Rating'),
			'#prefix' => '<div id="rating_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
	    );
		$form['add_more_btn'] = array(
			'#type' => 'submit',
			'#submit'=> array(),
			'#ajax' => array(
					'callback' => 'ajax_add_sarfy_callback',
					//'wrapper' => 'table_div_replace',
				),
			'#limit_validation_errors' => array(),	
			'#value' => t('Add'),
			'#attributes' => array('class'=>array('btn btn-info')),
			'#prefix' => '<div id="add_more_btn_replace_div"><div class="col-md-2">',
			'#suffix' => '</div></div>'
		);
		$form['sar_info'] = array(
			'#prefix' => '<div id="sar_info_replace_div"><div class="col-md-12">'.get_sar_file_list($user_arr[1]),
			'#suffix' => '</div></div>'
		);
	}else{
		$form['fy'] = array(
			'#prefix' => '<div id="fy_replace_div">',
			'#suffix' => '</div>'
		);
		$form['doc_file'] = array(
			'#prefix' => '<div id="doc_file_replace_div">',
			'#suffix' => '</div>'
	    );
		$form['type'] = array(
			'#prefix' => '<div id="type_replace_div">',
			'#suffix' => '</div>'
	    );
		$form['comment'] = array(
			'#prefix' => '<div id="comment_replace_div">',
			'#suffix' => '</div>'
	    );
		$form['rating'] = array(
			'#prefix' => '<div id="rating_replace_div">',
			'#suffix' => '</div>'
	    );
		$form['add_more_btn'] = array(
			'#prefix' => '<div id="add_more_btn_replace_div">',
			'#suffix' => '</div>'
		);
		$form['sar_info'] = array(
			'#prefix' => '<div id="sar_info_replace_div">',
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


function _reload_mem_order_list_saracr($form, $form_state) {
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	$commands   = array();
	$user_arr = explode('-',$form_state['values']['fname_saracr']);
	$header_info = array();
	$rows_info   = array();
	$header_info = array(  
	  array('data' => t('Employee Information'),'colspan' => 4),  
	);
	 $mydata = getUserInfoByUid($user_arr[1]);
 
	 $form['uid_saracr']['#value'] = $user_arr[1];
	 $form['designation_saracr']['#value'] = $mydata['designation'];
	 $form['directorate_saracr']['#value'] = $mydata['directorate_code'];
	 $form['district_saracr']['#value'] = $mydata['district_code'];
	 $form['doj_saracr']['#value'] = $mydata['doj'];
	 
	$rows_info[] = array(  
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	  array('data' => t('<b>Directorate Name  </b>')),
	  array('data' => t('<b>District Name  </b>')),
	);
	$rows_info[] = array( 
	  array('data' => t($mydata['fname'])),
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
	 
 //$commands[] = ajax_command_invoke('.doc_name_clear', 'val', array($form['values']['fname']));
 $commands[] = ajax_command_replace('#order_no_map_backlog', '<div id="order_no_map_backlog">'.drupal_render($form['uid_saracr']).'</div>');
 $commands[] = ajax_command_replace('#designation_map_backlog', '<div id="designation_map_backlog">'.drupal_render($form['designation_saracr']).'</div>');
 $commands[] = ajax_command_replace('#directorate_map_backlog', '<div id="directorate_map_backlog">'.drupal_render($form['directorate_saracr']).'</div>');
 $commands[] = ajax_command_replace('#district_map_backlog', '<div id="district_map_backlog">'.drupal_render($form['district_saracr']).'</div>'); 
 $commands[] = ajax_command_replace('#doj_map_backlog', '<div id="doj_map_backlog">'.drupal_render($form['doj_saracr']).'</div>'); 
 $commands[] = ajax_command_replace('#fetch_data_map_backlog', '<div id="fetch_data_map_backlog"><div class="col-md-12">'.$output_info.'</div></div>');
 $commands[] = ajax_command_replace('#fetch_data_map_year', '<div id="fetch_data_map_year"><div class="col-md-12">'.$output.'</div></div>');
 //$commands[] = ajax_command_replace('#decission_map_backlog', '<div id="decission_map_backlog">'.drupal_render($form['decission_sacracr']).'</div>');
 
 $commands[] = ajax_command_replace('#fy_replace_div', '<div id="fy_replace_div">'.drupal_render($form['fy']).'</div>');
 $commands[] = ajax_command_replace('#doc_file_replace_div', '<div id="doc_file_replace_div">'.drupal_render($form['doc_file']).'</div>');
 $commands[] = ajax_command_replace('#type_replace_div', '<div id="type_replace_div">'.drupal_render($form['type']).'</div>');
 $commands[] = ajax_command_replace('#comment_replace_div', '<div id="comment_replace_div">'.drupal_render($form['comment']).'</div>');
 $commands[] = ajax_command_replace('#rating_replace_div', '<div id="rating_replace_div">'.drupal_render($form['rating']).'</div>');
 $commands[] = ajax_command_replace('#add_more_btn_replace_div', '<div id="add_more_btn_replace_div">'.drupal_render($form['add_more_btn']).'</div>');
 $commands[] = ajax_command_replace('#sar_info_replace_div', '<div id="sar_info_replace_div">'.drupal_render($form['sar_info']).'</div>');
 
 return array('#type' => 'ajax', '#commands' => $commands);
}

function getFinancialYear($uid){
	$mydata = getUserInfoByUid($uid);
	$header = array();
	$rows   = array();
	
	$header = array(  
	  array('data' => t('Information'),'colspan' => 4),  
	); 
	$yr_arr = explode('-',$mydata['doj']);
	$y = $yr_arr[0];
	
	 
	 $k = 0; $j=6;
	 $output = '<div id="parent_table_div_sar"><table class="table pretty table-bordered table-hover sticky-enabled tableheader-processed sticky-table"><thead><tr><th colspan="6">Financial Year</th></tr></thead>';
	 for($y=$yr_arr[0]; $y<=date('Y'); $y++){ 
	 	
		$rsData = array();
		$query = db_select('a_sar_file', 'f');
		$query ->fields('f', array( 'asr_id', 'uid', 'financial_yr', 'doj_yr', 'directorate_code', 'district_code','file_name','sar_file','status'));
		$query->condition('f.uid', $uid, '=');
		$query->condition('f.financial_yr', trim($y.'-'.($y+1)), '='); 
		$result = $query->execute();
		$rsData = $result->fetchAll();
		if(!empty($rsData)){
	  		$link = t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/submitted.png">');
		}else{
			$link = t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/not-submitted.png">');
		}
	 	if($k == 0){
			$output .= '<tr>';
			$output .= '<td>'.$link.' '.$y.'-'.($y+1).'</td>'; 	
		}elseif($k%$j == 0){
			$output .= '</tr><tr>';
			$output .= '<td>'.$link.' '.$y.'-'.($y+1).'</td>'; 	
		}else{
			$output .= '<td>'.$link.' '.$y.'-'.($y+1).'</td>'; 		
		}
		$k++;
	 }
	 $output .='</tr></table></div>';
	 return $output;	
}


function ajax_add_sarfy_callback($form, &$form_state){
	global $user;
	
	$commands   = array();
	
	if(trim($form_state['input']['fy'])!="" && trim($_FILES['files']['name']['doc_file'])!=""){
		
		$file_name = trim($_FILES['files']['name']['doc_file']);
		$file_path = $_FILES['files']['tmp_name']['doc_file'];
	  	$file_size = $_FILES['files']['size']['doc_file'];
		$file_ext = pathinfo($file_name, PATHINFO_EXTENSION);
		
		$directory_path	=	file_default_scheme().'://upload/sar/';
		
		$extensions = 'pdf' ; 

	    $validators = array(
		   'file_validate_extensions' => array($extensions),   
		   'file_validate_size' => array(1*1024*1024) // 5MB
		);
		
		$error_description = "";
		if(!$file = file_save_upload('doc_file', $validators, $directory_path, FILE_EXISTS_RENAME)){
			//die('not uploaded');
			
			if(strtolower(trim($file_ext)) != 'pdf'){
				$error_description = "Allow to upload PDF only";
			}else if($file_size >= (1*1024*1024)){
				$error_description = "File is too big";
			}else{
				$error_description = "Unable to upload file";
			}
			$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12">'.$error_description.'</div></div>');
		}else{
			//$file_name = $file->filename;
			
			$file_uri = $file->uri;
			$file_contents = file_get_contents($file_uri);
			//$file->status = FILE_STATUS_PERMANENT; //ADDED
		    file_save($file);
			$upld_directory_path=file_create_url($file->uri); //NOT USED
			$Full_File_Path=$file->uri;
			$doc_file_details = array(
							//'fid' => $file->fid,
							'financial_yr' => trim($form_state['input']['fy']),
							//'financial_yr' => trim($form_state['input']['financial_yr']),
							'doj_yr' =>trim($form_state['input']['doj_saracr']),
							'uid' => trim($form_state['input']['uid_saracr']),
							'directorate_code' => trim($form_state['input']['directorate_saracr']),
							'district_code' => trim($form_state['input']['district_saracr']),
							'file_name' => trim($_FILES['files']['name']['doc_file']),
							'sar_file' => $file_contents,
							'rating' => trim($form_state['input']['rating']),
							'sar_type' => trim($form_state['input']['type']),
							'sar_comment' => trim($form_state['input']['comment']),
							'status' => 0,
						);			
						
			$id = db_insert('a_sar_file')->fields($doc_file_details)->execute();
			if($id){
				
				$mydata = getUserInfoByUid($form_state['input']['uid_saracr']);
				$financial_yr = array();
				$dojyr = explode('-',$mydata['doj']);
				  for($y=$dojyr[0]; $y<=date('Y'); $y++){
						$rsData = array();
						$query = db_select('a_sar_file', 'f');
						$query ->fields('f', array( 'asr_id', 'uid', 'financial_yr', 'doj_yr', 'directorate_code', 'district_code','file_name','sar_file','status'));
						$query->condition('f.uid',$form_state['input']['uid_saracr'], '='); 
						$query->condition('f.financial_yr', trim($y.'-'.($y+1)), '='); 
						$result = $query->execute();
						$rsData = $result->fetchAll();
						if(empty($rsData)){
							$financial_yr[trim($y.'-'.($y+1))] = trim($y.'-'.($y+1));
						}
				  }
				$form['fy']['#options'] = $financial_yr; 
				//$form['type']['#options'] = array(''=>'-Select-','Old'=>'Old','New'=>'New');
				//$form['comment']['#options'] = array(''=>'-Select-','Outstanding'=>'Outstanding','Excellent'=>'Excellent','Very Good'=>'Very Good','Good'=>'Good','Average'=>'Average','Poor'=>'Poor');
				
				$commands[] = ajax_command_invoke('#rating_clear_div', 'val', array(''));
				$commands[] = ajax_command_replace('#fy_replace_div', drupal_render($form['fy']));
				$commands[] = ajax_command_replace('#type_replace_div', drupal_render($form['type']));
				$commands[] = ajax_command_replace('#comment_replace_div', drupal_render($form['comment']));
				$commands[] = ajax_command_replace('#doc_file_replace_div', drupal_render($form['doc_file']));
				$commands[] = ajax_command_replace('#fetch_data_map_year', '<div id="fetch_data_map_year"><div class="col-md-12">'.getFinancialYear(trim($form_state['input']['uid_saracr'])).'</div></div>');
				$commands[] = ajax_command_replace('#sar_info_replace_div', '<div id="sar_info_replace_div"><div class="col-md-12">'.get_sar_file_list(trim($form_state['input']['uid_saracr'])).'</div></div>');
				
				$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12">'.$error_description.'</div></div>');
			}
			
		}
		
	}else{
		$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12">Please Select Financial Year</div></div>');
	}
	return array('#type' => 'ajax', '#commands' => $commands);
}

function get_sar_file_list($uid){
	global $user;
	drupal_add_css(drupal_get_path('module', 'project') . '/def.css');
	
	$output = '';
  	$header = array(
				array('data'=> 'SL No'),
				array('data'=> 'Financial Year'),
				array('data'=> 'Type'),
				array('data'=> 'Comment'),
				array('data'=> 'Rating'),
				array('data'=> 'Action')
			);
			
	$rows = array();
	
	$query = db_select('a_sar_file', 'f');
	$query ->fields('f', array( 'asr_id', 'uid', 'financial_yr', 'doj_yr', 'directorate_code', 'district_code','file_name','sar_file','status','rating','sar_type','sar_comment'));
	$query->condition('f.uid', $uid, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
	$i = 0;
	
	foreach($resultData as $val){
		$i++;
		 $viewLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></div>','display-file/'.$val->asr_id,array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('red'), 'target'=>'_blank')));
	  
	  $rows [] = array(  
	  		  array('data' => t($i)), 	
			  array('data' => t($val->financial_yr)), 
			  array('data' => t($val->sar_type)), 
			  array('data' => t($val->sar_comment)), 
			  array('data' => t($val->rating)),  
			  array('data' => $viewLink),			
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
	  
	  return $output;		
}

function get_asset_user_saracr($string=''){
	
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
	$query->fields('us', array('designation','district_code','directorate_code'));
	
	$query->leftJoin('a_directorate_mst', 'd', 'd.directorate_code = us.directorate_code'); 
	$query->fields('d', array('directorate_name')); 
	
	$query->leftJoin('district_master', 'dis', 'dis.district_code = us.district_code'); 
	$query->fields('dis', array('district_name')); 
	
	$query->fields('u', array('uid','name','access','created','status'));
	$query->fields('ud', array('fname','hrms_id','doj'));
	$query->condition('u.uid', $uid, '=');
	$result = $query->execute();
	$userData = $result->fetchAssoc();
	return $userData;
}

function sar_acr_file_display($arg){
	if($arg != 0){
		$query = db_select('a_sar_file', 'f');
		$query ->fields('f', array('asr_id','file_name','sar_file','status'));
		$query->condition('f.asr_id', $arg, '='); 
		$result = $query->execute();
		$result_data = $result->fetchAssoc();
		header("Content-Type: application/pdf");
		header('Content-Disposition: inline; filename="'.$result_data['file_name'].'"');
		echo $result_data['sar_file'];
		exit();
	}else{
		drupal_set_message('Unable to open file');
	}
}