<?php

function asset_form_entry($form, &$form_state){
   global $user;
  
   /****************************** Check IF Profile is Fillup or Not************************************************/
   $status = getUserProfileStatus($user->uid);
   if($status['one_time_pass_flag'] == '0') {
		drupal_goto('profileupdate');
		exit;
   }
   $resultDataValidate = getAssetDataWithStatus($user->uid, 1);
   if($resultDataValidate['declaration_yr']==date('Y')){
	  drupal_set_message('You have already submitted your asset for this year.', $type='warning');
	  drupal_goto('propertyuser-dashboard');
	  exit;
  }
   /********************************** End Profile is Fillup Cheaking************************************************/
   $resultData = array(); 
   $resultData = getAssetDataWithStatus($user->uid, 0);
   $form = array();
   $form['#attributes']['class'][] = 'form-vertical';
  
  if(!empty($resultData)){
	  $yr = $resultData['declaration_yr'];
  }else{
	  $yr = date('Y');
  }
  
  $form['form_begin'] = array(
	'#type' => 'markup',
	'#markup' => '<div class="row">',
	'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Declaration of Assets as they stood on 1st January '.$yr.'</h4> <div class="widget-toolbar">
				   </div></div><div class="widget-main">',
	//'#suffix' => ''
  );
  $form['asset_id'] = array(
	'#title' => t('Asset ID'),	
	'#type' => 'hidden',
	'#required' => TRUE,
	'#default_value' => !empty($resultData)? $resultData['id'] : 0,
  );		 		 
  $form['declaration_yr'] = array(
	'#type' => 'hidden',
	'#title' => t('Declaration of Assets as they stood on'),
	'#required' => TRUE,
	'#default_value' => !empty($resultData)? $resultData['declaration_yr'] : date('Y'),
	'#attributes' => array('class'=>array('form-control','datepiker_yr'),'placeholder'=>'Declaration of Assets as they stood on','autocomplete'=>'off'),
	//'#prefix' => '<div class="col-md-4">',
	//'#suffix' => '</div>'
  );
  $form['officer_name'] = array(
	'#type' => 'textfield',
	'#title' => t('Name (in full) of Officer'),
	'#required' => TRUE,
	'#default_value' => !empty($status)? $status['fname'] : 0,
	'#disabled'=>true,
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Name (in full) of Officer'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['service_type'] = array(
	'#type' => 'textfield',
	'#title' => t('Service'),
	'#required' => TRUE,
	'#default_value' => !empty($resultData)? $resultData['service_type'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Service'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  
  $form['designation'] = array(
	'#type' => 'textfield',
	'#title' => t('Designation'),
	'#required' => TRUE,
	'#default_value' => !empty($resultData)? $resultData['designation'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Designation'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  
  $form['appointed_as'] = array(
	'#type' => 'textfield',
	'#title' => t('Now appointed as'),
	'#required' => TRUE,
	'#default_value' => !empty($resultData)? $resultData['appointed_as'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Now appointed as'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  
  $form['substantive_pay'] = array(
	'#type' => 'textfield',
	'#title' => t('Substantive Pay'),
	'#required' => TRUE,
	'#default_value' => !empty($resultData)? $resultData['substantive_pay'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Substantive Pay'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  
  $form['special_pay'] = array(
	'#type' => 'textfield',
	'#title' => t('Special Pay'),
	'#required' => TRUE,
	'#default_value' => !empty($resultData)? $resultData['special_pay'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Special Pay'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  
  $form['submit_asset'] = array(
	'#type' => 'submit',
	'#value' => 'Save & Continue',
	'#attributes' => array('class'=>array('form-control btn btn-primary')),
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

function asset_form_entry_submit($form, &$form_state){
	global $user;
	if($form_state['values']['asset_id'] == 0){
		$assetInfo = array(	'declaration_yr'						=>	trim($form_state['values']['declaration_yr']),
							'uid'									=>	$user->uid,
							//'officer_name'							=>	trim($form_state['values']['officer_name']),
							'service_type'							=>	trim($form_state['values']['service_type']),
							'designation'							=>	trim($form_state['values']['designation']),
							'appointed_as'							=>	trim($form_state['values']['appointed_as']),
							'substantive_pay'						=>	trim($form_state['values']['substantive_pay']),
							'special_pay'							=>	trim($form_state['values']['special_pay']),
							'document_no'							=> 'N/A',
							'created_date'							=>	date('Y-m-d H:i:s'),
							'update_date'							=>	date('Y-m-d H:i:s'),
							'pdf_generated_flag'					=> '0',
							'status' 								=> 0
							);
							
		$asset_id = db_insert('a_asset_mst')->fields($assetInfo)->execute();
		if($asset_id){
			 drupal_set_message('Your Record has been inserted successfully.');
			 drupal_goto('asset/land');
		}else{
			drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
		}
	}else{
		$query = db_update('a_asset_mst');
		$query->fields(array('declaration_yr'						=>	trim($form_state['values']['declaration_yr']),
							//'uid'									=>	$user->uid,
							//'officer_name'							=>	trim($form_state['values']['officer_name']),
							'service_type'							=>	trim($form_state['values']['service_type']),
							'designation'							=>	trim($form_state['values']['designation']),
							'appointed_as'							=>	trim($form_state['values']['appointed_as']),
							'substantive_pay'						=>	trim($form_state['values']['substantive_pay']),
							'special_pay'							=>	trim($form_state['values']['special_pay']),
							'update_date'							=>	date('Y-m-d H:i:s'),
							//'status' 								=>	0
							));
							
		$query->condition('id', trim($form_state['values']['asset_id']));
		$rs = $query->execute();					
							
		if($rs){
			 drupal_set_message('Your record has been updated successfully.');
			 drupal_goto('asset/land');
		}else{
			 drupal_set_message('Unable to update your record. Please try again later.',$type = 'warning');
			 drupal_goto('asset/land');
		}
	}
}

/* -------------------------------------------- Immovable Property (Land) Begin ------------------------------------------------------- */
function land_form_entry($form, &$form_state) {
	global $user;
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');	
	
	$resultData = array();
	$resultData = getAssetDataWithStatus($user->uid, 0); 
	if(empty($resultData)){
	  drupal_set_message('Please fill up Asset tab first.',$type = 'warning');
	  drupal_goto('asset'); 
    }else{
	
  $form = array();
  $form['#attributes']['class'][] = 'form-vertical';

  $form['form_begin'] = array(
		'#type' => 'markup',
		//'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Immovable Property - Land</h4> <div class="widget-toolbar">
					   </div></div><div class="widget-main">',
		//'#suffix' => ''
	 );
  $form['asset_id'] = array(
	'#type' => 'hidden',
	'#required' => TRUE,
	'#default_value' => $resultData['id'],
  );
  $form['uid'] = array(
	'#type' => 'hidden',
	'#required' => TRUE,
	'#default_value' => $resultData['uid'],
  );
  $landYearData = getImmovableLandByUidAndYear($user->uid, $resultData['declaration_yr']);
  $form['firstRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  ); 
  $form['applicability'] = array(
	'#type' => 'hidden',
	'#required' => TRUE,
	'#default_value'=> !empty($landYearData)? $landYearData['applicability'] : 'Y',
  );
 $form['doc_list'] = array(
	'#prefix' => '<div id="table_div_replace_material"><div class="col-md-12">'.get_immovable_land_list($resultData['id']),
	'#suffix' => '</div></div>'
  );
 $form['firstRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  ); 
 if(empty($landYearData) || !empty($form_state['values']['applicability'])){
	 $form['applicability_div']['secondRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	 );
 $form['applicability_div']['precise_landlocation'] = array(
	'#type' => 'textfield',
	'#title' => t('Precise Location of Land'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Precise Location of Land'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['land_area'] = array(
	'#type' => 'textfield',
	'#title' => t('Area of Land'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Area of Land'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['land_nature'] = array(
	'#type' => 'textfield',
	'#title' => t('Nature of Land'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Nature of Land'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['secondRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['thirdRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
   $form['applicability_div']['landextent_interest'] = array(
	'#type' => 'textfield',
	'#title' => t('Extent of Interest of Land'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Extent of Interest of Land'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['land_value'] = array(
	'#type' => 'textfield',
	'#title' => t('Value of Land'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Value of Land'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['land_innameof'] = array(
	'#type' => 'textfield',
	'#title' => t('In whose name the asset is'),
	'#description'=>t('(wife, child,dependant,other relationor benamdar)'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In whose name(wife, child,dependant,other relationor benamdar)the asset is'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['thirdRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['fourthRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
  $form['applicability_div']['landacquistion_date'] = array(
	'#type' => 'textfield',
	'#title' => t('Date of Acquisition'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Acquisition'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['landacquistion_manner'] = array(
	'#type' => 'textfield',
	'#title' => t('Manner of Acquisition'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Manner of Acquisition'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['fourthRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['fifthRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
  $form['applicability_div']['land_remarks'] = array(
	'#type' => 'textarea',
	'#title' => t('Remarks'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Remarks'),
	'#prefix' => '<div class="col-md-12">',
	'#suffix' => '</div>'
  );
  $form['applicability_div']['fifthRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
 $form['applicability_div']['sixthRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
 //if(empty($landYearData) || (!empty($landYearData) && $landYearData['applicability']=='Y')){
	   $form['applicability_div']['submit_land'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
		//'#submit'=>array('land_form_entry_manual_submit'),
		'#attributes' => array('class'=>array('form-control btn btn-primary')),
		'#prefix' => '<div class="col-md-6"><div class="input-group">',
		'#suffix' => '</div></div>'
	  );
	if(empty($landYearData)){  
	  $form['applicability_div']['submit_land_not'] = array(
		'#type' => 'submit',
		'#value' => 'Not Applicable',
		'#limit_validation_errors' => array(array('asset_id'),array('uid')),
		'#submit'=>array('not_applicable_submit'),
		'#attributes' => array('class'=>array('form-control btn btn-primary')),
		'#prefix' => '<div class="col-md-6"><div class="input-group pull-right">',
		'#suffix' => '</div></div>'
	  ); 
	}
  //}
  
  $form['applicability_div']['sixthRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
 }else if($landYearData['applicability']=='Y'){
	 $form['seventhRowStart'] = array(	
		'#prefix' => '<div id="applicable_div_replace"><div class="row">',
		'#suffix' => ''
	  );
	 $form['submit_land_add_more'] = array(
		'#type' => 'button',
		'#value' => 'Add More',
		'#ajax' => array(
			'callback' => 'ajax_applicable_callback',
			//'wrapper' => 'applicable_div_replace'
		),
		'#attributes' => array('class'=>array('form-control btn btn-primary')),
		'#prefix' => '<div class="col-md-12"><div class="input-group">',
		'#suffix' => '</div></div>'
	  );
	  $form['seventhRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div></div>'
	  );
 }
 $form['form_end'] = array(
	 '#type' => 'markup',
	 //'#markup' => '</div>',
	 '#suffix' => '</div></div>'
   );
   																	
  return $form;	
	}
}
function not_applicable_submit($form, &$form_state){
	$assetLand = array('asset_id'							=>	trim($form_state['values']['asset_id']),
					'uid'									=>	trim($form_state['values']['uid']),
					'applicability'							=>	'N',
					'precise_landlocation'					=>	'N/A',
					'land_area'								=>	'N/A',
					'land_nature'							=>	'N/A',
					'landextent_interest'					=>	'N/A',
					'land_value'							=>	'N/A',
					'land_innameof'							=>	'N/A',
					'landacquistion_date'					=>	'N/A',
					'landacquistion_manner'					=>	'N/A',
					'land_remarks'							=>	'N/A',
					'created_date'							=>	date('Y-m-d H:i:s'),
					'update_date'							=>	date('Y-m-d H:i:s'),
					'status' 								=>	0
				);
	$asset_land_id = db_insert('a_im_land')->fields($assetLand)->execute();
	
	if($asset_land_id){
		 drupal_set_message('Your Record has been inserted successfully.');
	}else{
		drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
	}
}
function land_form_entry_validate($form, &$form_state){
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
}
function land_form_entry_submit($form, &$form_state){
 $assetLand = array('asset_id'								=>	trim($form_state['values']['asset_id']),
					'uid'									=>	trim($form_state['values']['uid']),
					'applicability'							=>	trim($form_state['values']['applicability']),
					'precise_landlocation'					=>	($form_state['values']['applicability'])=='Y'? trim($form_state['values']['precise_landlocation']) : 'N/A',
					'land_area'								=>	($form_state['values']['applicability'])=='Y'? trim($form_state['values']['land_area']) : 'N/A',
					'land_nature'							=>	($form_state['values']['applicability'])=='Y'? trim($form_state['values']['land_nature']) : 'N/A',
					'landextent_interest'					=>	($form_state['values']['applicability'])=='Y'? trim($form_state['values']['landextent_interest']) : 'N/A',
					'land_value'							=>	($form_state['values']['applicability'])=='Y'? trim($form_state['values']['land_value']) : 'N/A',
					'land_innameof'							=>	($form_state['values']['applicability'])=='Y'? trim($form_state['values']['land_innameof']) : 'N/A',
					'landacquistion_date'					=>	($form_state['values']['applicability'])=='Y'? date('Y-m-d H:i:s',strtotime(trim($form_state['values']['landacquistion_date']))) : 'N/A',
					'landacquistion_manner'					=>	($form_state['values']['applicability'])=='Y'? trim($form_state['values']['landacquistion_manner']) : 'N/A',
					'land_remarks'							=>	($form_state['values']['applicability'])=='Y'? trim($form_state['values']['land_remarks']) : 'N/A',
					'created_date'							=>	date('Y-m-d H:i:s'),
					'update_date'							=>	date('Y-m-d H:i:s'),
					'status' 								=>	0
				);
	$asset_land_id = db_insert('a_im_land')->fields($assetLand)->execute();
	
	if($asset_land_id){
		 drupal_set_message('Your Record has been inserted successfully.');
		 //drupal_goto('asset/house');
	}else{
		drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
	}
}
function ajax_applicable_callback($form,&$form_state){
	$commands   	= array();
	if($form_state['values']['applicability'] == "Y"){
		$commands[] = ajax_command_replace('#applicable_div_replace', '<div id="applicable_div_replace">'.drupal_render($form['applicability_div']).'</div>');
		$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
	}else{
		$commands[] = ajax_command_replace('#applicable_div_replace', '<div id="applicable_div_replace"></div>');
	}
	//$commands[] = ajax_command_replace('#user_list_div', drupal_render($form['table_data']));
	return array('#type' => 'ajax', '#commands' => $commands);
}
function get_immovable_land_list($asset_id){
	//die('hello');
	global $user;
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$query = db_select('a_im_land', 'ail');
	$query ->leftJoin('a_asset_mst', 'assetmst', 'ail.asset_id = assetmst.id'); 
	$query ->fields('assetmst', array('declaration_yr','service_type','designation'));
	$query ->fields('ail', array( 'id', 'asset_id', 'uid', 'precise_landlocation', 'land_area', 'land_nature', 'landextent_interest','land_value','land_innameof','landacquistion_date','landacquistion_manner','land_remarks','created_date','update_date','status'));
	$query->condition('ail.asset_id', $asset_id, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
	
	$output = '';
	if(!empty($resultData)){
	
  	$header = array(
				array('data'=> 'AY Year'),
				array('data'=> 'Precise Location of Land'),
				array('data'=> 'Area of Land'),
				array('data'=> 'Nature of Land'),
				array('data'=> 'Extent of Intrest of Land'),
				array('data'=> 'Value of Land'),
				array('data'=> 'Date of Acquisition'),
				array('data'=> 'Action')
			);
			
	$rows = array();
	$i = 0;
	
	foreach($resultData as $val){
		$i++;
		 $editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'asset/landedit/'.$val->id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		 $delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','asset/landdel/'.$val->id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  $rows [] = array(  
	  		  array('data' => t($val->declaration_yr)), 	
			  array('data' => t($val->precise_landlocation)), 
			  array('data' => t($val->land_area)),
			  array('data' => t($val->land_nature)),
			  array('data' => t($val->landextent_interest)), 
			  array('data' => t($val->land_value)),
			  array('data' => ($val->landacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->landacquistion_date))) : 'N/A'),
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
	  
	return $output;	
	}
}
function asset_land_del($args){
 if (trim($args) != 0) {
	 $query = db_delete('a_im_land');
	 $query->condition('id', trim($args));
	 $query->execute();
	 drupal_set_message('Your Record has been deleted successfully.');
	 drupal_goto('asset/land');
 }else{
	 drupal_set_message('Unable to delete record. Please try again later.',$type = 'warning');
	 drupal_goto('asset/land');
 }
}

function land_form_edit($form, &$form_state, $args){
  global $user;
	
  $query = db_select('a_im_land', 'ail');
  $query ->fields('ail', array( 'id', 'asset_id', 'uid', 'precise_landlocation', 'land_area', 'land_nature', 'landextent_interest','land_value','land_innameof','landacquistion_date','landacquistion_manner','land_remarks','created_date','update_date','status'));
  $query->condition('ail.id', $args, '='); 
  $result = $query->execute();
  $resultData = $result->fetchAssoc();
	
  $form = array();
  $form['#attributes']['class'][] = 'form-vertical';
  $form['form_begin'] = array(
	'#type' => 'markup',
	//'#markup' => '<div class="row">',
	'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Immovable Property - Land</h4> <div class="widget-toolbar">
				   </div></div><div class="widget-main">',
	//'#suffix' => ''
  );
  $form['land_id'] = array(
	'#type' => 'hidden',
	'#required' => TRUE,
	'#default_value' => trim($args),
  );
  $form['secondRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
  $form['precise_landlocation'] = array(
	'#type' => 'textfield',
	'#title' => t('Precise Location of Land'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['precise_landlocation'])!='N/A'? $resultData['precise_landlocation'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Precise Location of Land'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['land_area'] = array(
	'#type' => 'textfield',
	'#title' => t('Area of Land'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['land_area'])!='N/A'? $resultData['land_area'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Area of Land'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
   $form['land_nature'] = array(
	'#type' => 'textfield',
	'#title' => t('Nature of Land'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['land_nature'])!='N/A'? $resultData['land_nature'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Nature of Land'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['secondRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
  $form['thirdRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
   $form['landextent_interest'] = array(
	'#type' => 'textfield',
	'#title' => t('Extent of Interest of Land'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['landextent_interest'])!='N/A'? $resultData['landextent_interest'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Extent of Interest of Land'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
   $form['land_value'] = array(
	'#type' => 'textfield',
	'#title' => t('Value of Land'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['land_value'])!='N/A'? $resultData['land_value'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Value of Land'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['land_innameof'] = array(
	'#type' => 'textfield',
	'#title' => t('In whose name the asset is'),
	'#description'=>t('(wife, child,dependant,other relationor benamdar)'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['land_innameof'])!='N/A'? $resultData['land_innameof'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In whose name(wife, child,dependant,other relationor benamdar)the asset is'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['thirdRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
  $form['fourthRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
  $form['landacquistion_date'] = array(
	'#type' => 'textfield',
	'#title' => t('Date of Acquisition'),
	'#required' => TRUE,
	'#default_value' => ($resultData['landacquistion_date'])!='N/A'? date('d-m-Y',strtotime(trim($resultData['landacquistion_date']))) : '',
	'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Acquisition'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['landacquistion_manner'] = array(
	'#type' => 'textfield',
	'#title' => t('Manner of Acquisition'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['landacquistion_manner'])!='N/A'? $resultData['landacquistion_manner'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Manner of Acquisition'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['fourthRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
  $form['fifthRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
  $form['land_remarks'] = array(
	'#type' => 'textarea',
	'#title' => t('Remarks'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['land_remarks'])!='N/A'? $resultData['land_remarks'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Remarks'),
	'#prefix' => '<div class="col-md-12">',
	'#suffix' => '</div>'
  );
  $form['fifthRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
  $form['sixthRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
  $form['submit_land'] = array(
	'#type' => 'submit',
	'#value' => 'Update',
	'#attributes' => array('class'=>array('form-control btn btn-primary')),
	'#prefix' => '<div class="col-md-12"><div class="input-group">',
	'#suffix' => '</div></div>'
  );
  $form['sixthRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  ); 
 $form['form_end'] = array(
	 '#type' => 'markup',
	 //'#markup' => '</div>',
	 '#suffix' => '</div></div>'
   );
  return $form;	
}
function land_form_edit_submit($form, &$form_state){
  $query = db_update('a_im_land');
  $query->fields(array(	'applicability'							=>  'Y',
  						'precise_landlocation'					=>	trim($form_state['values']['precise_landlocation']),
						'land_area'								=>	trim($form_state['values']['land_area']),
						'land_nature'							=>	trim($form_state['values']['land_nature']),
						'landextent_interest'					=>	trim($form_state['values']['landextent_interest']),
						'land_value'							=>	trim($form_state['values']['land_value']),
						'land_innameof'							=>	trim($form_state['values']['land_innameof']),
						'landacquistion_date'					=>	trim($form_state['values']['landacquistion_date'])!='N/A'? date('Y-m-d H:i:s',strtotime(trim($form_state['values']['landacquistion_date']))) : 'N/A',
						'landacquistion_manner'					=>	trim($form_state['values']['landacquistion_manner']),
						'land_remarks'							=>	trim($form_state['values']['land_remarks']),
						'update_date'							=>	date('Y-m-d H:i:s'),
						));
  $query->condition('id', trim($form_state['values']['land_id']));
  $rs = $query->execute();	
  if($rs){
	 drupal_set_message('Your record has been updated successfully.');
	 drupal_goto('asset/land');
  }else{
	 drupal_set_message('Unable to update your record. Please try again later.',$type = 'warning');
	 drupal_goto('asset/land');
  }				
}

/* -------------------------------------------- Immovable Property (Land) End ------------------------------------------------------- */
	
/* -------------------------------------------- Immovable Property (House) Begin ----------------------------------------------------- */
function house_form_entry($form, &$form_state) {
  global $user;
  drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');	
	
  $resultData = array();
  $resultData = getAssetDataWithStatus($user->uid, 0);
  $ImmovableLand = getImmovableLandDataWithStatus($user->uid, 0);
  if(empty($resultData)){
	  drupal_set_message('Please fill up Asset tab first.',$type = 'warning');
	  drupal_goto('asset'); 
  }else if(empty($ImmovableLand)){
	  drupal_set_message('Please fill Immovable-Land tab first.',$type = 'warning');
	  drupal_goto('asset/land'); 
  }
  $form = array();
  $form['#attributes']['class'][] = 'form-vertical';
	
  $form['form_begin'] = array(
	'#type' => 'markup',
	//'#markup' => '<div class="row">',
	'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Immovable Property - House</h4> <div class="widget-toolbar">
				   </div></div><div class="widget-main">',
	//'#suffix' => ''
   );
   
   $form['asset_id'] = array(
	'#type' => 'hidden',
	'#required' => TRUE,
	'#default_value' => $resultData['id'],
   );
   $form['uid'] = array(
	'#type' => 'hidden',
	'#required' => TRUE,
	'#default_value' => $resultData['uid'],
   );
  $houseYearData = getImmovableHouseByUidAndYear($user->uid, $resultData['declaration_yr']);
  $form['firstRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  ); 
  $form['applicability'] = array(
	'#title' => t('Wheather Applicable or not ?'),
	'#type' => 'select',
	'#options'=>array(''=>'-Select-','N'=>'No','Y'=>'Yes'),
	'#ajax' => array(
			'callback' => 'ajax_applicable_house_callback',
			//'wrapper' => 'applicable_div_replace'
		),
	'#required' => TRUE,
	'#default_value'=> !empty($houseYearData)? $houseYearData['applicability'] : '',
	'#disabled'=> !empty($houseYearData)? TRUE : FALSE,
	'#attributes' => array('class'=>array('form-control')),
	'#prefix' => '<div class="col-md-12">',
	'#suffix' => '</div>'
  ); 
 $form['firstRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  ); 
 $form['applicability_house_div'] = array(
 	'#prefix' => '<div id="applicability_house_div_replace">',
	'#suffix' => '</div>'
 );
 
 if($form_state['values']['applicability']=="Y" || $houseYearData['applicability']=='Y'){
	$form['applicability_house_div']['secondRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);		 
   $form['applicability_house_div']['precise_houselocation'] = array(
	'#type' => 'textfield',
	'#title' => t('Precise Location of House'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Precise Location of House'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
   );
   $form['applicability_house_div']['houseextent_interest'] = array(
	'#type' => 'textfield',
	'#title' => t('Extent of Interest of House'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Extent of Interest of House'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
   );
   $form['applicability_house_div']['house_value'] = array(
	'#type' => 'textfield',
	'#title' => t('Value of House'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Value of House'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
   );
   $form['applicability_house_div']['secondRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
   $form['applicability_house_div']['thirdRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);	
   $form['applicability_house_div']['house_innameof'] = array(
	'#type' => 'textfield',
	'#title' => t('In whose name the asset is'),
	'#required' => TRUE,
	'#description'=> t('(wife, child,dependant,other relationor benamdar)'),
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In whose name the asset is'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
   );
   $form['applicability_house_div']['houseacquistion_date'] = array(
	'#type' => 'textfield',
	'#title' => t('Date of Acquisition'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Acquisition'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
   );
   $form['applicability_house_div']['houseacquistion_manner'] = array(
	'#type' => 'textfield',
	'#title' => t('Manner of Acquisition'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Manner of Acquisition'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
   );
   $form['applicability_house_div']['thirdRowend'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['applicability_house_div']['fourthRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);
   $form['applicability_house_div']['house_remarks'] = array(
	'#type' => 'textarea',
	'#title' => t('Remarks'),
	'#required' => TRUE,
	//'#default_value' => '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Remarks'),
	'#prefix' => '<div class="col-md-12">',
	'#suffix' => '</div>'
   );
   $form['applicability_house_div']['fourthRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
 }
 $form['fifthRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);
  if(empty($houseYearData) || (!empty($houseYearData) && $houseYearData['applicability']=='Y')){ 	
   $form['submit_house'] = array(
	'#type' => 'submit',
	'#value' => 'Save',
	'#attributes' => array('class'=>array('form-control btn btn-primary')),
	'#prefix' => '<div class="col-md-12"><div class="input-group">',
	'#suffix' => '</div></div>'
   ); 
  }
   $form['doc_list'] = array(
	'#prefix' => '<div id="table_div_replace_material"><div class="col-md-12">'.get_immovable_house_list($resultData['id']),
	'#suffix' => '</div></div>'
   );
   $form['fifthRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
   $form['form_end'] = array(
	 '#type' => 'markup',
	 //'#markup' => '</div>',
	 '#suffix' => '</div></div>'
   );
  return $form;		
}
function house_form_entry_validate($form, &$form_state){
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
}
function house_form_entry_submit($form, &$form_state){
	
 $assetHouse = array('asset_id'								=>	trim($form_state['values']['asset_id']),
					'uid'									=>	trim($form_state['values']['uid']),
					'applicability'							=>	trim($form_state['values']['applicability']),
					'precise_houselocation'					=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['precise_houselocation']) : 'N/A',
					'houseextent_interest'					=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['houseextent_interest']) : 'N/A',
					'house_value'							=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['house_value']) : 'N/A',
					'house_innameof'						=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['house_innameof']) : 'N/A',
					'houseacquistion_date'					=>	trim($form_state['values']['applicability'])=='Y'? date('Y-m-d H:i:s',strtotime(trim($form_state['values']['houseacquistion_date']))) : 'N/A',
					'houseacquistion_manner'				=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['houseacquistion_manner']) : 'N/A',
					'house_remarks'							=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['house_remarks']) : 'N/A',
					'created_date'							=>	date('Y-m-d H:i:s'),
					'update_date'							=>	date('Y-m-d H:i:s'),
					'status' 								=>	0
				);
	$asset_house_id = db_insert('a_im_house')->fields($assetHouse)->execute();
	
	if($asset_house_id){
		 drupal_set_message('Your Record has been inserted successfully.');
		 //drupal_goto('asset/house');
	}else{
		drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
	}
}
function ajax_applicable_house_callback($form,&$form_state){
  $commands   	= array();
  if($form_state['values']['applicability'] == "Y"){
	$commands[] = ajax_command_replace('#applicability_house_div_replace', '<div id="applicability_house_div_replace">'.drupal_render($form['applicability_house_div']).'</div>');
	$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
  }else{
	$commands[] = ajax_command_replace('#applicability_house_div_replace', '<div id="applicability_house_div_replace"></div>');
  }
	//$commands[] = ajax_command_replace('#user_list_div', drupal_render($form['table_data']));
  return array('#type' => 'ajax', '#commands' => $commands);
}
function get_immovable_house_list($asset_id){
	//die('hello');
	global $user;
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$output = '';
  	$header = array(
				array('data'=> 'AY Year'),
				array('data'=> 'Precise Location of House'),
				array('data'=> 'Extent of Intrest of House '),
				array('data'=> 'Value of House'),
				array('data'=> 'In whose name the asset is'),
				array('data'=> 'Date of Acquisition'),
				array('data'=> 'Manner of Acquisition'),
				array('data'=> 'Action')
			);
			
	$rows = array();
	
	$query = db_select('a_im_house', 'aih');
	$query ->leftJoin('a_asset_mst', 'assetmst', 'aih.asset_id = assetmst.id'); 
	$query ->fields('assetmst', array('declaration_yr','service_type','designation'));
	$query ->fields('aih', array( 'im_house_id', 'asset_id', 'uid', 'precise_houselocation', 'houseextent_interest', 'house_value', 'house_innameof','houseacquistion_date','houseacquistion_manner','house_remarks','created_date','update_date','status'));
	$query->condition('aih.asset_id', $asset_id, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
	$i = 0;
	
	foreach($resultData as $val){
		$i++;
		 $editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'asset/houseedit/'.$val->im_house_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		 $delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','asset/housedel/'.$val->im_house_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  
	  $rows [] = array(  
	  		  array('data' => t($val->declaration_yr)), 	
			  array('data' => t($val->precise_houselocation)), 
			  array('data' => t($val->houseextent_interest)),
			  array('data' => t($val->house_value)),
			  array('data' => t($val->house_innameof)),
			  array('data' => ($val->houseacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->houseacquistion_date))) : 'N/A'), 
			  array('data' => t($val->houseacquistion_manner)),
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
	  
	return $output;		
}
function asset_house_del($args){
 if (trim($args) != 0) {
	 $query = db_delete('a_im_house');
	 $query->condition('im_house_id', trim($args));
	 $query->execute();
	 drupal_set_message('Your Record has been deleted successfully.');
	 drupal_goto('asset/house');
 }else{
	 drupal_set_message('Unable to delete record. Please try again later.',$type = 'warning');
	 drupal_goto('asset/house');
 }
}

function house_form_edit($form, &$form_state, $args){
  global $user;
	
  $query = db_select('a_im_house', 'aih');
  $query ->fields('aih', array( 'im_house_id', 'asset_id', 'uid', 'precise_houselocation', 'houseextent_interest', 'house_value', 'house_innameof','houseacquistion_date','houseacquistion_manner','house_remarks','created_date','update_date','status'));
  $query->condition('aih.im_house_id', $args, '='); 
  $result = $query->execute();
  $resultData = $result->fetchAssoc();
	
  $form = array();
  $form['#attributes']['class'][] = 'form-vertical';
  $form['form_begin'] = array(
	'#type' => 'markup',
	//'#markup' => '<div class="row">',
	'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Immovable Property - Land</h4> <div class="widget-toolbar">
				   </div></div><div class="widget-main">',
	//'#suffix' => ''
  );
  $form['house_id'] = array(
	'#type' => 'hidden',
	'#required' => TRUE,
	'#default_value' => trim($args),
  );
  $form['secondRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  ); 
  $form['precise_houselocation'] = array(
	'#type' => 'textfield',
	'#title' => t('Precise Location of House'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['precise_houselocation'])!='N/A'? $resultData['precise_houselocation'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Precise Location of House'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['houseextent_interest'] = array(
	'#type' => 'textfield',
	'#title' => t('Extent of Interest of House'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['houseextent_interest'])!='N/A'? $resultData['houseextent_interest'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Extent of Interest of House'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
   $form['house_value'] = array(
	'#type' => 'textfield',
	'#title' => t('Value of House'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['house_value'])!='N/A'? $resultData['house_value'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Value of House'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['secondRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
  $form['thirdRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
   $form['house_innameof'] = array(
	'#type' => 'textfield',
	'#title' => t('In whose name the asset is'),
	'#description' => t('(wife, child,dependant,other relationor benamdar)'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['house_innameof'])!='N/A'? $resultData['house_innameof'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In whose name the asset is'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['houseacquistion_date'] = array(
	'#type' => 'textfield',
	'#title' => t('Date of Acquisition'),
	'#required' => TRUE,
	'#default_value' => ($resultData['houseacquistion_date'])!='N/A'? date('d-m-Y',strtotime(trim($resultData['houseacquistion_date']))) : '',
	'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Acquisition'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['houseacquistion_manner'] = array(
	'#type' => 'textfield',
	'#title' => t('Manner of Acquisition'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['houseacquistion_manner'])!='N/A'? $resultData['houseacquistion_manner'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Manner of Acquisition'),
	'#prefix' => '<div class="col-md-4">',
	'#suffix' => '</div>'
  );
  $form['thirdRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
  $form['fourthRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
  $form['house_remarks'] = array(
	'#type' => 'textarea',
	'#title' => t('Remarks'),
	'#required' => TRUE,
	'#default_value' => trim($resultData['house_remarks'])!='N/A'? $resultData['house_remarks'] : '',
	'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Remarks'),
	'#prefix' => '<div class="col-md-12">',
	'#suffix' => '</div>'
  );
  $form['fourthRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
  $form['fifthRowStart'] = array(	
	'#prefix' => '<div class="row">',
	'#suffix' => ''
  );
  $form['submit_land'] = array(
	'#type' => 'submit',
	'#value' => 'Update',
	'#attributes' => array('class'=>array('form-control btn btn-primary')),
	'#prefix' => '<div class="col-md-12"><div class="input-group">',
	'#suffix' => '</div></div>'
  ); 
  $form['fifthRowEnd'] = array(	
	'#prefix' => '',
	'#suffix' => '</div>'
  );
 $form['form_end'] = array(
	 '#type' => 'markup',
	 //'#markup' => '</div>',
	 '#suffix' => '</div></div>'
   );
 return $form;
  
}
function house_form_edit_submit($form, &$form_state){
  $query = db_update('a_im_house');
  $query->fields(array(	'applicability'							=>  'Y',
  						'precise_houselocation'					=>	trim($form_state['values']['precise_houselocation']),
						'houseextent_interest'					=>	trim($form_state['values']['houseextent_interest']),
						'house_value'							=>	trim($form_state['values']['house_value']),
						'house_innameof'						=>	trim($form_state['values']['house_innameof']),
						'houseacquistion_date'					=>	trim($form_state['values']['houseacquistion_date'])!='N/A'? date('Y-m-d H:i:s',strtotime(trim($form_state['values']['houseacquistion_date']))) : 'N/A',
						'houseacquistion_manner'				=>	trim($form_state['values']['houseacquistion_manner']),
						'house_remarks'							=>	trim($form_state['values']['house_remarks']),
						'update_date'							=>	date('Y-m-d H:i:s'),
						));
  $query->condition('im_house_id', trim($form_state['values']['house_id']));
  $rs = $query->execute();	
  if($rs){
	 drupal_set_message('Your record has been updated successfully.');
	 drupal_goto('asset/house');
  }else{
	 drupal_set_message('Unable to update your record. Please try again later.',$type = 'warning');
	 drupal_goto('asset/house');
  }				
}
/* -------------------------------------------- Immovable Property (House) End ----------------------------------------------------- */



/* -------------------------------------------- Immovable Property (Mortgage and Others) Begin ----------------------------------------------------- */
function other_immovable_form_entry($form, &$form_state) {
	global $user;
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');	
	
	$resultData = array();
	$resultData = getAssetDataWithStatus($user->uid, 0);
	$ImmovableLand = getImmovableLandDataWithStatus($user->uid, 0);
	$ImmovableHouse = getImmovableHouseDataWithStatus($user->uid, 0);
	if(empty($resultData)){
	  	drupal_set_message('Please fill up Asset tab first.',$type = 'warning');
	  	drupal_goto('asset'); 
	}else if(empty($ImmovableLand)){
	  	drupal_set_message('Please fill Immovable-Land tab first.',$type = 'warning');
	  	drupal_goto('asset/land'); 
	}else if(empty($ImmovableHouse)){
	  	drupal_set_message('Please fill Immovable-House tab first.',$type = 'warning');
	  	drupal_goto('asset/house'); 
	}
	$form = array();
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
		'#type' => 'markup',
		//'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">IMMOVABLE PROPERTIES OF OTHER DESCRIPTION - 
						(Including mortgages and such other rights)</h4> <div class="widget-toolbar">
					   </div></div><div class="widget-main">',
		//'#suffix' => ''
	);
	$form['asset_id'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => $resultData['id'],
	);
	$form['uid'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => $resultData['uid'],
	);
	$immovableOtherYearData = getImmovableOtherByUidAndYear($user->uid, $resultData['declaration_yr']);
	$form['firstRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	); 
	$form['applicability'] = array(
		'#title' => t('Wheather Applicable or not ?'),
		'#type' => 'select',
		'#options'=>array(''=>'-Select-','N'=>'No','Y'=>'Yes'),
		'#ajax' => array(
				'callback' => 'ajax_applicable_immovable_other_callback',
				//'wrapper' => 'applicable_div_replace'
				),
		'#required' => TRUE,
		'#default_value'=> !empty($immovableOtherYearData)? $immovableOtherYearData['applicability'] : '',
		'#disabled'=> !empty($immovableOtherYearData)? TRUE : FALSE,
		'#attributes' => array('class'=>array('form-control')),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	); 	
	$form['firstRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['applicability_other_div'] = array(
		'#prefix' => '<div id="applicability_other_div_replace">',
		'#suffix' => '</div>'
	);
	if($form_state['values']['applicability']=="Y" || $immovableOtherYearData['applicability']=='Y'){ 
		$form['applicability_other_div']['secondRowStart'] = array(	
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$form['applicability_other_div']['precise_otherlocation'] = array(
			'#type' => 'textfield',
			'#title' => t('Precise Location'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Precise Location'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_other_div']['otherextent_interest'] = array(
			'#type' => 'textfield',
			'#title' => t('Extent of Interest'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Extent of Interest'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_other_div']['other_value'] = array(
			'#type' => 'textfield',
			'#title' => t('Value'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Value'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_other_div']['secondRowEnd'] = array(	
			'#prefix' => '',
			'#suffix' => '</div>'
		);
		$form['applicability_other_div']['ThirdRowStart'] = array(	
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$form['applicability_other_div']['other_innameof'] = array(
			'#type' => 'textfield',
			'#title' => t('In whose name the asset is'),
			'#description'=>t('(wife, child,dependant,other relationor benamdar)'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In whose name(wife, child,dependant,other relationor benamdar)the asset is'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_other_div']['otheracquistion_date'] = array(
			'#type' => 'textfield',
			'#title' => t('Date of Acquisition'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Acquisition'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_other_div']['otheracquistion_manner'] = array(
			'#type' => 'textfield',
			'#title' => t('Manner of Acquisition'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Manner of Acquisition'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_other_div']['ThirdRowEnd'] = array(	
			'#prefix' => '',
			'#suffix' => '</div>'
		);
		$form['applicability_other_div']['FourthRowStart'] = array(	
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$form['applicability_other_div']['other_remarks'] = array(
			'#type' => 'textarea',
			'#title' => t('Remarks'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Remarks'),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		);
		$form['FourthRowEnd'] = array(	
			'#prefix' => '',
			'#suffix' => '</div>'
		);
	}
	$form['FifthRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);
	if(empty($immovableOtherYearData) || (!empty($immovableOtherYearData) && $immovableOtherYearData['applicability']=='Y')){
		$form['submit_imother'] = array(
			'#type' => 'submit',
			'#value' => 'Save',
			'#attributes' => array('class'=>array('form-control btn btn-primary')),
			'#prefix' => '<div class="col-md-12"><div class="input-group">',
			'#suffix' => '</div></div>'
		); 
	}
	$form['doc_list'] = array(
		'#prefix' => '<div id="table_div_replace_material"><div class="col-md-12">'.get_immovable_other_list($resultData['id']),
		'#suffix' => '</div></div>'
	);
	$form['FifthRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['form_end'] = array(
	 '#type' => 'markup',
	 //'#markup' => '</div>',
	 '#suffix' => '</div></div>'
	);
	return $form;	
}
function other_immovable_form_entry_validate($form, &$form_state){
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
}
function other_immovable_form_entry_submit($form, &$form_state){
 $assetOther = array('asset_id'								=>	trim($form_state['values']['asset_id']),
					'uid'									=>	trim($form_state['values']['uid']),
					'applicability'							=>	trim($form_state['values']['applicability']),
					'precise_otherlocation'					=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['precise_otherlocation']) : 'N/A',
					'otherextent_interest'					=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['otherextent_interest']) : 'N/A',
					'other_value'							=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['other_value']) : 'N/A',
					'other_innameof'						=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['other_innameof']) : 'N/A',
					'otheracquistion_date'					=>	trim($form_state['values']['applicability'])=='Y'? date('Y-m-d H:i:s',strtotime(trim($form_state['values']['otheracquistion_date']))) : 'N/A',
					'otheracquistion_manner'				=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['otheracquistion_manner']) : 'N/A',
					'other_remarks'							=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['other_remarks']) : 'N/A',
					'created_date'							=>	date('Y-m-d H:i:s'),
					'update_date'							=>	date('Y-m-d H:i:s'),
					'status' 								=>	0
				);
	$asset_other_id = db_insert('a_im_other')->fields($assetOther)->execute();
	
	if($asset_other_id){
		 drupal_set_message('Your Record has been inserted successfully.');
	}else{
		drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
	}
}
function ajax_applicable_immovable_other_callback($form,&$form_state){
  $commands   	= array();
  if($form_state['values']['applicability'] == "Y"){
	$commands[] = ajax_command_replace('#applicability_other_div_replace', '<div id="applicability_other_div_replace">'.drupal_render($form['applicability_other_div']).'</div>');
	$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
  }else{
	$commands[] = ajax_command_replace('#applicability_other_div_replace', '<div id="applicability_other_div_replace"></div>');
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}
function get_immovable_other_list($asset_id){
	//die('hello');
	global $user;
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$output = '';
  	$header = array(
				array('data'=> 'AY Year'),
				array('data'=> 'Precise Location'),
				array('data'=> 'Extent of Intrest'),
				array('data'=> 'Value'),
				array('data'=> 'In whose name the asset is'),
				array('data'=> 'Date of Acquisition'),
				array('data'=> 'Manner of Acquisition'),
				array('data'=> 'Action')
			);
			
	$rows = array();
	
	$query = db_select('a_im_other', 'aio');
	$query ->leftJoin('a_asset_mst', 'assetmst', 'aio.asset_id = assetmst.id'); 
	$query ->fields('assetmst', array('declaration_yr','service_type','designation'));
	$query ->fields('aio', array('im_other_id', 'asset_id', 'uid', 'applicability', 'precise_otherlocation', 'otherextent_interest', 'other_value', 'other_innameof','otheracquistion_date','otheracquistion_manner','other_remarks','created_date','update_date','status'));
	$query->condition('aio.asset_id', $asset_id, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
	$i = 0;
	
	foreach($resultData as $val){
		$i++;
		 $editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'asset/otheredit/'.$val->im_other_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		 $delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','asset/otherdel/'.$val->im_other_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  
	  $rows [] = array(  
	  		  array('data' => t($val->declaration_yr)), 	
			  array('data' => t($val->precise_otherlocation)), 
			  array('data' => t($val->otherextent_interest)),
			  array('data' => t($val->other_value)),
			  array('data' => t($val->other_innameof)),
			  array('data' => ($val->otheracquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->otheracquistion_date))) : 'N/A'), 
			  array('data' => t($val->otheracquistion_manner)),
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
	  
	return $output;		
}
function asset_other_immovable_del($args){
 if (trim($args) != 0) {
	 $query = db_delete('a_im_other');
	 $query->condition('im_other_id', trim($args));
	 $query->execute();
	 drupal_set_message('Your Record has been deleted successfully.');
	 drupal_goto('asset/other-immovable');
 }else{
	 drupal_set_message('Unable to delete record. Please try again later.',$type = 'warning');
	 drupal_goto('asset/other-immovable');
 }
}
function other_immovable_form_edit($form, &$form_state, $args){
	global $user;
	
	$query = db_select('a_im_other', 'aio');
	$query ->fields('aio', array('im_other_id', 'asset_id', 'uid', 'applicability', 'precise_otherlocation', 'otherextent_interest', 'other_value', 'other_innameof','otheracquistion_date','otheracquistion_manner','other_remarks','created_date','update_date','status'));
	$query->condition('aio.im_other_id', $args, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAssoc();
	
	$form = array();
	$form['#attributes']['class'][] = 'form-vertical';
	$form['form_begin'] = array(
		'#type' => 'markup',
		'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Immovable Property - Land</h4> <div class="widget-toolbar">
					   </div></div><div class="widget-main">',
		//'#suffix' => ''
	);
	$form['im_other_id'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => trim($args),
	);
	$form['precise_otherlocation'] = array(
		'#type' => 'textfield',
		'#title' => t('Precise Location'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['precise_otherlocation'])!='N/A'? $resultData['precise_otherlocation'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Precise Location'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['otherextent_interest'] = array(
		'#type' => 'textfield',
		'#title' => t('Extent of Interest'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['otherextent_interest'])!='N/A'? $resultData['otherextent_interest'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Extent of Interest'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['other_value'] = array(
		'#type' => 'textfield',
		'#title' => t('Value'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['other_value'])!='N/A'? $resultData['other_value'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Value'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['other_innameof'] = array(
		'#type' => 'textfield',
		'#title' => t('In whose name the asset is'),
		'#description'=>t('(wife, child,dependant,other relationor benamdar)'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['other_innameof'])!='N/A'? $resultData['other_innameof'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In whose name(wife, child,dependant,other relationor benamdar)the asset is'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['otheracquistion_date'] = array(
		'#type' => 'textfield',
		'#title' => t('Date of Acquisition'),
		'#required' => TRUE,
		'#default_value' => ($resultData['otheracquistion_date'])!='N/A'? date('d-m-Y',strtotime(trim($resultData['otheracquistion_date']))) : '',
		'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Acquisition'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['otheracquistion_manner'] = array(
		'#type' => 'textfield',
		'#title' => t('Manner of Acquisition'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['otheracquistion_manner'])!='N/A'? $resultData['otheracquistion_manner'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Manner of Acquisition'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['other_remarks'] = array(
		'#type' => 'textarea',
		'#title' => t('Remarks'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['other_remarks'])!='N/A'? $resultData['other_remarks'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Remarks'),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	);
	$form['submit_imother'] = array(
		'#type' => 'submit',
		'#value' => 'Update',
		'#attributes' => array('class'=>array('form-control btn btn-primary')),
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
function other_immovable_form_edit_submit($form, &$form_state){
	$query = db_update('a_im_other');
	$query->fields(array('applicability'						=>  'Y',
						'precise_otherlocation'					=>	trim($form_state['values']['precise_otherlocation']),
						'otherextent_interest'					=>	trim($form_state['values']['otherextent_interest']),
						'other_value'							=>	trim($form_state['values']['other_value']),
						'other_innameof'						=>	trim($form_state['values']['other_innameof']),
						'otheracquistion_date'					=>	trim($form_state['values']['otheracquistion_date'])!='N/A'? date('Y-m-d H:i:s',strtotime(trim($form_state['values']['otheracquistion_date']))) : 'N/A',
						'otheracquistion_manner'				=>	trim($form_state['values']['otheracquistion_manner']),
						'other_remarks'							=>	trim($form_state['values']['other_remarks']),
						'update_date'							=>	date('Y-m-d H:i:s'),
						));
	$query->condition('im_other_id', trim($form_state['values']['im_other_id']));
	$rs = $query->execute();	
	if($rs){
	 	drupal_set_message('Your record has been updated successfully.');
	 	drupal_goto('asset/other-immovable');
	}else{
	 	drupal_set_message('Unable to update your record. Please try again later.',$type = 'warning');
	 	drupal_goto('asset/other-immovable');
	}				
}
/* -------------------------------------------- Immovable Property (Mortgage and Others) End ----------------------------------------------------- */



/* -------------------------------------------- Movable Property Begin ------------------------------------------------------------------------- */
function movable_form_entry($form, &$form_state) {
	global $user;
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');	
	
	$resultData 		= array();
	$resultData 		= getAssetDataWithStatus($user->uid, 0);
	$ImmovableLand 		= getImmovableLandDataWithStatus($user->uid, 0);
	$ImmovableHouse 	= getImmovableHouseDataWithStatus($user->uid, 0);
	$ImmovableOthers 	= getImmovableOthersDataWithStatus($user->uid, 0);
	if(empty($resultData)){
	  	drupal_set_message('Please fill up Asset tab first.',$type = 'warning');
	  	drupal_goto('asset'); 
	}else if(empty($ImmovableLand)){
	  	drupal_set_message('Please fill Immovable-Land tab first.',$type = 'warning');
	  	drupal_goto('asset/land'); 
	}else if(empty($ImmovableHouse)){
	  	drupal_set_message('Please fill Immovable-House tab first.',$type = 'warning');
	  	drupal_goto('asset/house'); 
	}else if(empty($ImmovableOthers)){
	  	drupal_set_message('Please fill Immovable-Others tab first.',$type = 'warning');
	  	drupal_goto('asset/other-immovable'); 
	}
	$form = array();
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
		'#type' => 'markup',
		//'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Movable Property - [CASH, BANK BALANCE, CREDIT, INSURANCE POLICIES, SHARES, 	
						DEBENTURES, ETC.]</h4> <div class="widget-toolbar">
					 </div></div><div class="widget-main">',
		//'#suffix' => ''
	);
	$form['asset_id'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => $resultData['id'],
	);
	$form['uid'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => $resultData['uid'],
	);
	$movablePropertyYearData = getMovablePropertyByUidAndYear($user->uid, $resultData['declaration_yr']);
	$form['firstRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	); 
	$form['applicability'] = array(
		'#title' => t('Wheather Applicable or not ?'),
		'#type' => 'select',
		'#options'=>array(''=>'-Select-','N'=>'No','Y'=>'Yes'),
		'#ajax' => array(
				'callback' => 'applicability_movable_div_replace',
				//'wrapper' => 'applicable_div_replace'
				),
		'#required' => TRUE,
		'#default_value'=> !empty($movablePropertyYearData)? $movablePropertyYearData['applicability'] : '',
		'#disabled'=> !empty($movablePropertyYearData)? TRUE : FALSE,
		'#attributes' => array('class'=>array('form-control')),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	); 	
	$form['firstRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['applicability_movable_div'] = array(
		'#prefix' => '<div id="applicability_movable_div_replace">',
		'#suffix' => '</div>'
	);
	if($form_state['values']['applicability']=="Y" || $movablePropertyYearData['applicability']=='Y'){ 
		$form['applicability_movable_div']['secondRowStart'] = array(	
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$form['applicability_movable_div']['item_description'] = array(
			'#type' => 'textfield',
			'#title' => t('Description of Items'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Description of Item'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['movable_value'] = array(
			'#type' => 'textfield',
			'#title' => t('Value'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Value'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['movable_innameof'] = array(
			'#type' => 'textfield',
			'#title' => t('In whose name the asset is'),
			'#description'=>t('(wife, child,dependant,other relationor benamdar)'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In whose name(wife, child,dependant,other relationor benamdar)the asset is'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['secondRowEnd'] = array(	
			'#prefix' => '',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['thirdRowStart'] = array(	
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$form['applicability_movable_div']['loan_innameof'] = array(
			'#type' => 'textfield',
			'#title' => t('Name of the person from whom the loan was taken'),
			'#description'=>t('In the case of Loan ( If not Applicable simply put N/A )'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In the case of, loan the name of the person from whom the loan was taken'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['loanee_relationship'] = array(
			'#type' => 'textfield',
			'#title' => t('The relationship of the loanee with that person'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'he relationship of the loanee with that person'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['movableacquistion_date'] = array(
			'#type' => 'textfield',
			'#title' => t('Date of Acquisition'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Acquisition'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['thirdRowEnd'] = array(	
			'#prefix' => '',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['fourthRowStart'] = array(	
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$form['applicability_movable_div']['movableacquistion_manner'] = array(
			'#type' => 'textfield',
			'#title' => t('Manner of Acquisition'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Manner of Acquisition'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['fourthRowEnd'] = array(	
			'#prefix' => '',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['fifthRowStart'] = array(	
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$form['applicability_movable_div']['movable_remarks'] = array(
			'#type' => 'textarea',
			'#title' => t('Remarks'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Remarks'),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_div']['fifthRowEnd'] = array(	
			'#prefix' => '',
			'#suffix' => '</div>'
		);
	}
	$form['sixthRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);	
	if(empty($movablePropertyYearData) || (!empty($movablePropertyYearData) && $movablePropertyYearData['applicability']=='Y')){ 
		$form['submit_movable'] = array(
			'#type' => 'submit',
			'#value' => 'Save',
			'#attributes' => array('class'=>array('form-control btn btn-primary')),
			'#prefix' => '<div class="col-md-12"><div class="input-group">',
			'#suffix' => '</div></div>'
		);
	}
	$form['doc_list'] = array(
		'#prefix' => '<div id="table_div_replace_material"><div class="col-md-12">'.get_movable_property_list($resultData['id']),
		'#suffix' => '</div></div>'
	);
	$form['sixthRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);	 
	$form['form_end'] = array(
		'#type' => 'markup',
		//'#markup' => '</div>',
		'#suffix' => '</div></div>'
	);
	return $form;	
}
function movable_form_entry_validate($form, &$form_state){
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
}
function movable_form_entry_submit($form, &$form_state){
 $assetMovable = array('asset_id'								=>	trim($form_state['values']['asset_id']),
						'uid'									=>	trim($form_state['values']['uid']),
						'applicability'							=>	trim($form_state['values']['applicability']),
						'item_description'						=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['item_description']) : 'N/A',
						'movable_value'							=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['movable_value']) : 'N/A',
						'movable_innameof'						=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['movable_innameof']) : 'N/A',
						'loan_innameof'							=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['loan_innameof']) : 'N/A',
						'loanee_relationship'					=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['loanee_relationship']) : 'N/A',
						'movableacquistion_date'				=>	trim($form_state['values']['applicability'])=='Y'? date('Y-m-d H:i:s',strtotime(trim($form_state['values']['movableacquistion_date']))) : 'N/A',
						'movableacquistion_manner'				=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['movableacquistion_manner']) : 'N/A',
						'movable_remarks'						=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['movable_remarks']) : 'N/A',
						'created_date'							=>	date('Y-m-d H:i:s'),
						'update_date'							=>	date('Y-m-d H:i:s'),
						'status' 								=>	0
				);
	$asset_movable_id = db_insert('a_m_property')->fields($assetMovable)->execute();
	
	if($asset_movable_id){
		 drupal_set_message('Your Record has been inserted successfully.');
	}else{
		drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
	}
}
function applicability_movable_div_replace($form,&$form_state){
  $commands   	= array();
  if($form_state['values']['applicability'] == "Y"){
	$commands[] = ajax_command_replace('#applicability_movable_div_replace', '<div id="applicability_movable_div_replace">'.drupal_render($form['applicability_movable_div']).'</div>');
	$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
  }else{
	$commands[] = ajax_command_replace('#applicability_movable_div_replace', '<div id="applicability_movable_div_replace"></div>');
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}
function get_movable_property_list($asset_id){
	//die('hello');
	global $user;
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$output = '';
  	$header = array(
				array('data'=> 'AY Year'),
				array('data'=> 'Item Description'),
				array('data'=> 'Value'),
				array('data'=> 'In whose name the asset is'),
				array('data'=> 'Loan taken person name'),
				array('data'=> 'Relationship of the loanee with that person'),
				array('data'=> 'Date of Acquisition'),
				array('data'=> 'Manner of Acquisition'),
				array('data'=> 'Action')
			);
			
	$rows = array();
	
	$query = db_select('a_m_property', 'amp');
	$query ->leftJoin('a_asset_mst', 'assetmst', 'amp.asset_id = assetmst.id'); 
	$query ->fields('assetmst', array('declaration_yr','service_type','designation'));
	$query ->fields('amp', array('m_property_id', 'asset_id', 'uid', 'applicability', 'item_description', 'movable_value', 'movable_innameof', 'loan_innameof','loanee_relationship','movableacquistion_date','movableacquistion_manner','movable_remarks','created_date','update_date','status'));
	$query->condition('amp.asset_id', $asset_id, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
	$i = 0;
	
	foreach($resultData as $val){
		$i++;
		 $editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'asset/movablepropertyedit/'.$val->m_property_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		 $delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','asset/movablepropertydel/'.$val->m_property_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  
	  $rows [] = array(  
	  		  array('data' => t($val->declaration_yr)), 	
			  array('data' => t($val->item_description)), 
			  array('data' => t($val->movable_value)),
			  array('data' => t($val->movable_innameof)),
			  array('data' => t($val->loan_innameof)),
			  array('data' => t($val->loanee_relationship)),
			  array('data' => ($val->movableacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->movableacquistion_date))) : 'N/A'), 
			  array('data' => t($val->movableacquistion_manner)),
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
	  
	return $output;		
}
function asset_movable_property_del($args){
 if (trim($args) != 0) {
	 $query = db_delete('a_m_property');
	 $query->condition('m_property_id', trim($args));
	 $query->execute();
	 drupal_set_message('Your Record has been deleted successfully.');
	 drupal_goto('asset/movabale');
 }else{
	 drupal_set_message('Unable to delete record. Please try again later.',$type = 'warning');
	 drupal_goto('asset/movabale');
 }
}
function movable_form_edit($form, &$form_state, $args) {
	global $user;
	
	$query = db_select('a_m_property', 'amp');
	$query ->fields('amp', array('m_property_id', 'asset_id', 'uid', 'applicability', 'item_description', 'movable_value', 'movable_innameof', 'loan_innameof','loanee_relationship','movableacquistion_date','movableacquistion_manner','movable_remarks','created_date','update_date','status'));
	$query->condition('amp.m_property_id', $args, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAssoc();
	
	$form = array();
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
		'#type' => 'markup',
		//'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Movable Property - [CASH, BANK BALANCE, CREDIT, INSURANCE POLICIES, SHARES, 	
						DEBENTURES, ETC.]</h4> <div class="widget-toolbar">
					 </div></div><div class="widget-main">',
		//'#suffix' => ''
	);
	$form['m_property_id'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => trim($args),
	);
	$form['secondRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);
	$form['item_description'] = array(
		'#type' => 'textfield',
		'#title' => t('Description of Items'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['item_description'])!='N/A'? $resultData['item_description'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Description of Item'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['movable_value'] = array(
		'#type' => 'textfield',
		'#title' => t('Value'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['movable_value'])!='N/A'? $resultData['movable_value'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Value'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['movable_innameof'] = array(
		'#type' => 'textfield',
		'#title' => t('In whose name the asset is'),
		'#description'=>t('(wife, child,dependant,other relationor benamdar)'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['movable_innameof'])!='N/A'? $resultData['movable_innameof'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In whose name(wife, child,dependant,other relationor benamdar)the asset is'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['secondRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['thirdRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);
	$form['loan_innameof'] = array(
		'#type' => 'textfield',
		'#title' => t('Name of the person from whom the loan was taken'),
		'#description'=>t('In the case of Loan ( If not Applicable simply put N/A )'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['loan_innameof'])!='N/A'? $resultData['loan_innameof'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In the case of, loan the name of the person from whom the loan was taken'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['loanee_relationship'] = array(
		'#type' => 'textfield',
		'#title' => t('The relationship of the loanee with that person'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['loanee_relationship'])!='N/A'? $resultData['loanee_relationship'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'he relationship of the loanee with that person'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['movableacquistion_date'] = array(
		'#type' => 'textfield',
		'#title' => t('Date of Acquisition'),
		'#required' => TRUE,
		'#default_value' => ($resultData['movableacquistion_date'])!='N/A'? date('d-m-Y',strtotime(trim($resultData['movableacquistion_date']))) : '',
		'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Acquisition'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['thirdRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['fourthRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);
	$form['movableacquistion_manner'] = array(
		'#type' => 'textfield',
		'#title' => t('Manner of Acquisition'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['movableacquistion_manner'])!='N/A'? $resultData['movableacquistion_manner'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Manner of Acquisition'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['fourthRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['fifthRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);
	$form['movable_remarks'] = array(
		'#type' => 'textarea',
		'#title' => t('Remarks'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['movable_remarks'])!='N/A'? $resultData['movable_remarks'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Remarks'),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	);
	$form['fifthRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['sixthRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);	 
	$form['submit_movable'] = array(
		'#type' => 'submit',
		'#value' => 'Update',
		'#attributes' => array('class'=>array('form-control btn btn-primary')),
		'#prefix' => '<div class="col-md-12"><div class="input-group">',
		'#suffix' => '</div></div>'
	);
	$form['sixthRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);	 
	$form['form_end'] = array(
		'#type' => 'markup',
		//'#markup' => '</div>',
		'#suffix' => '</div></div>'
	);
	return $form;	
}
function movable_form_edit_submit($form, &$form_state){
	$query = db_update('a_m_property');
	$query->fields(array('applicability'						=>  'Y',
						'item_description'						=>	trim($form_state['values']['item_description']),
						'movable_value'							=>	trim($form_state['values']['movable_value']),
						'movable_innameof'						=>	trim($form_state['values']['movable_innameof']),
						'loan_innameof'							=>	trim($form_state['values']['loan_innameof']),
						'loanee_relationship'					=>	trim($form_state['values']['loanee_relationship']),
						'movableacquistion_date'				=>	trim($form_state['values']['movableacquistion_date'])!='N/A'? date('Y-m-d H:i:s',strtotime(trim($form_state['values']['movableacquistion_date']))) : 'N/A',
						'movableacquistion_manner'				=>	trim($form_state['values']['movableacquistion_manner']),
						'movable_remarks'						=>	trim($form_state['values']['movable_remarks']),
						'update_date'							=>	date('Y-m-d H:i:s'),
						));
	$query->condition('m_property_id', trim($form_state['values']['m_property_id']));
	$rs = $query->execute();	
	if($rs){
	 	drupal_set_message('Your record has been updated successfully.');
	 	drupal_goto('asset/movabale');
	}else{
	 	drupal_set_message('Unable to update your record. Please try again later.',$type = 'warning');
	 	drupal_goto('asset/movabale');
	}				
}

/* -------------------------------------------- Movable Property End ---------------------------------------------------------------------------- */



/* -------------------------------------------- Other Movable Property () Begin ----------------------------------------------------- */
function other_movable_form_entry($form, &$form_state) {
	global $user;
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');	
	
	$resultData 		= array();
	$resultData 		= getAssetDataWithStatus($user->uid, 0);
	$ImmovableLand 		= getImmovableLandDataWithStatus($user->uid, 0);
	$ImmovableHouse 	= getImmovableHouseDataWithStatus($user->uid, 0);
	$ImmovableOthers 	= getImmovableOthersDataWithStatus($user->uid, 0);
	$MmovableProperty 	= getMovablePropertyDataWithStatus($user->uid, 0);
	if(empty($resultData)){
	  	drupal_set_message('Please fill up Asset tab first.',$type = 'warning');
	  	drupal_goto('asset'); 
	}else if(empty($ImmovableLand)){
	  	drupal_set_message('Please fill Immovable-Land tab first.',$type = 'warning');
	  	drupal_goto('asset/land'); 
	}else if(empty($ImmovableHouse)){
	  	drupal_set_message('Please fill Immovable-House tab first.',$type = 'warning');
	  	drupal_goto('asset/house'); 
	}else if(empty($ImmovableOthers)){
	  	drupal_set_message('Please fill Immovable-Others tab first.',$type = 'warning');
	  	drupal_goto('asset/other-immovable'); 
	}else if(empty($MmovableProperty)){
	  	drupal_set_message('Please fill Mmovable-Property tab first.',$type = 'warning');
	  	drupal_goto('asset/movabale'); 
	}
	$form = array();
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
		'#type' => 'markup',
		//'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">OTHER MOVABLES - (Including jewellery and other valuables, motor vehicles, 
					  refrigerators and other articles or materials of Rs. 500 and over for each item)</h4> <div class="widget-toolbar">
					 </div></div><div class="widget-main">',
		//'#suffix' => ''
	);
	$form['asset_id'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => $resultData['id'],
	);
	$form['uid'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => $resultData['uid'],
	);
	$movableOtherYearData = getMovableOtherByUidAndYear($user->uid, $resultData['declaration_yr']);
	$form['firstRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	); 
	$form['applicability'] = array(
		'#title' => t('Wheather Applicable or not ?'),
		'#type' => 'select',
		'#options'=>array(''=>'-Select-','N'=>'No','Y'=>'Yes'),
		'#ajax' => array(
				'callback' => 'applicability_movable_other_callback',
				//'wrapper' => 'applicable_div_replace'
				),
		'#required' => TRUE,
		'#default_value'=> !empty($movableOtherYearData)? $movableOtherYearData['applicability'] : '',
		'#disabled'=> !empty($movableOtherYearData)? TRUE : FALSE,
		'#attributes' => array('class'=>array('form-control')),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	); 	
	$form['firstRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['applicability_movable_others_div'] = array(
		'#prefix' => '<div id="applicability_movable_others_div_replace">',
		'#suffix' => '</div>'
	);
	if($form_state['values']['applicability']=="Y" || $movableOtherYearData['applicability']=='Y'){ 
		$form['applicability_movable_others_div']['secondRowStart'] = array(	
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$form['applicability_movable_others_div']['moitem_description'] = array(
			'#type' => 'textfield',
			'#title' => t('Description of Items'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Description of Item'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_others_div']['movableother_value'] = array(
			'#type' => 'textfield',
			'#title' => t('Value'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Value'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_others_div']['movableother_innameof'] = array(
			'#type' => 'textfield',
			'#title' => t('In whose name the asset is'),
			'#description' => t('(wife, child,dependant,other relationor benamdar)'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In whose name(wife, child,dependant,other relationor benamdar)the asset is'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_others_div']['secondRowEnd'] = array(	
			'#prefix' => '',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_others_div']['thirdRowStart'] = array(	
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$form['applicability_movable_others_div']['moacquistion_date'] = array(
			'#type' => 'textfield',
			'#title' => t('Date of Acquisition'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Acquisition'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_others_div']['moacquistion_manner'] = array(
			'#type' => 'textfield',
			'#title' => t('Manner of Acquisition'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Manner of Acquisition'),
			'#prefix' => '<div class="col-md-4">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_others_div']['thirdRowEnd'] = array(	
			'#prefix' => '',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_others_div']['fourthRowStart'] = array(	
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$form['applicability_movable_others_div']['mo_remarks'] = array(
			'#type' => 'textarea',
			'#title' => t('Remarks'),
			'#required' => TRUE,
			//'#default_value' => '',
			'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Remarks'),
			'#prefix' => '<div class="col-md-12">',
			'#suffix' => '</div>'
		);
		$form['applicability_movable_others_div']['fourthRowEnd'] = array(	
			'#prefix' => '',
			'#suffix' => '</div>'
		);
	}
	$form['fifthRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);	
	if(empty($movableOtherYearData) || (!empty($movableOtherYearData) && $movableOtherYearData['applicability']=='Y')){  
		$form['submit_movableothers'] = array(
			'#type' => 'submit',
			'#value' => 'Save & Continue',
			'#attributes' => array('class'=>array('form-control btn btn-primary')),
			'#prefix' => '<div class="col-md-12"><div class="input-group">',
			'#suffix' => '</div></div>'
		);
	}
	$form['doc_list'] = array(
		'#prefix' => '<div id="table_div_replace_material"><div class="col-md-12">'.get_movable_other_list($resultData['id']),
		'#suffix' => '</div></div>'
	);
	$form['fifthRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	); 
	$form['form_end'] = array(
		'#type' => 'markup',
		//'#markup' => '</div>',
		'#suffix' => '</div></div>'
	);
	return $form;
}
function other_movable_form_entry_validate($form, &$form_state){
	drupal_add_js(drupal_get_path('module', 'asset_user') . '/myfunction.js');
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
}
function other_movable_form_entry_submit($form, &$form_state){
 $movableOther = array('asset_id'								=>	trim($form_state['values']['asset_id']),
						'uid'									=>	trim($form_state['values']['uid']),
						'applicability'							=>	trim($form_state['values']['applicability']),
						'moitem_description'					=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['moitem_description']) : 'N/A',
						'movableother_value'					=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['movableother_value']) : 'N/A',
						'movableother_innameof'					=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['movableother_innameof']) : 'N/A',
						'moacquistion_date'						=>	trim($form_state['values']['applicability'])=='Y'? date('Y-m-d H:i:s',strtotime(trim($form_state['values']['moacquistion_date']))) : 'N/A',
						'moacquistion_manner'					=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['moacquistion_manner']) : 'N/A',
						'mo_remarks'							=>	trim($form_state['values']['applicability'])=='Y'? trim($form_state['values']['mo_remarks']) : 'N/A',
						'created_date'							=>	date('Y-m-d H:i:s'),
						'update_date'							=>	date('Y-m-d H:i:s'),
						'status' 								=>	0
				);
	$asset_movable_other_id = db_insert('a_m_other')->fields($movableOther)->execute();
	
	if($asset_movable_other_id){
		drupal_set_message('Your Record has been inserted successfully.');
	}else{
		drupal_set_message('Unable to insert your record. Please try again later.', $type='warning');
	}
}

function applicability_movable_other_callback($form,&$form_state){
  $commands   	= array();
  if($form_state['values']['applicability'] == "Y"){
	$commands[] = ajax_command_replace('#applicability_movable_others_div_replace', '<div id="applicability_movable_others_div_replace">'.drupal_render($form['applicability_movable_others_div']).'</div>');
	$commands[] = ajax_command_invoke(NULL, "myJqueryDatePiker", array('anyparametervalue') );
  }else{
	$commands[] = ajax_command_replace('#applicability_movable_others_div_replace', '<div id="applicability_movable_others_div_replace"></div>');
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}
function get_movable_other_list($asset_id){
	//die('hello');
	global $user;
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$output = '';
  	$header = array(
				array('data'=> 'AY Year'),
				array('data'=> 'Item Description'),
				array('data'=> 'Value'),
				array('data'=> 'In whose name the asset is'),
				array('data'=> 'Date of Acquisition'),
				array('data'=> 'Manner of Acquisition'),
				array('data'=> 'Action')
			);
			
	$rows = array();
	
	$query = db_select('a_m_other', 'amo');
	$query ->leftJoin('a_asset_mst', 'assetmst', 'amo.asset_id = assetmst.id'); 
	$query ->fields('assetmst', array('declaration_yr','service_type','designation'));
	$query ->fields('amo', array('m_other_id', 'asset_id', 'uid', 'applicability', 'moitem_description', 'movableother_value', 'movableother_innameof', 'moacquistion_date','moacquistion_manner','mo_remarks','created_date','update_date','status'));
	$query->condition('amo.asset_id', $asset_id, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
	$i = 0;
	
	foreach($resultData as $val){
		$i++;
		 $editLink = l('<div class="hidden-sm hidden-xs action-buttons"><i class="ace-icon fa fa-pencil bigger-130"></i>', 'asset/movableotheredit/'.$val->m_other_id, array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('green'))));	
		 $delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i></div>','asset/movableotherdel/'.$val->m_other_id,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red'))));
	  
	  
	  $rows [] = array(  
	  		  array('data' => t($val->declaration_yr)), 	
			  array('data' => t($val->moitem_description)), 
			  array('data' => t($val->movableother_value)),
			  array('data' => t($val->movableother_innameof)),
			  array('data' => ($val->moacquistion_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->moacquistion_date))) : 'N/A'), 
			  array('data' => t($val->moacquistion_manner)),
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
	  
	return $output;		
}
function asset_movable_other_del($args){
 if (trim($args) != 0) {
	 $query = db_delete('a_m_other');
	 $query->condition('m_other_id', trim($args));
	 $query->execute();
	 drupal_set_message('Your Record has been deleted successfully.');
	 drupal_goto('asset/other-movabale');
 }else{
	 drupal_set_message('Unable to delete record. Please try again later.',$type = 'warning');
	 drupal_goto('asset/other-movabale');
 }
}
function movable_other_form_edit($form, &$form_state, $args) {
	global $user;
	
	$query = db_select('a_m_other', 'amo');
	$query ->fields('amo', array('m_other_id', 'asset_id', 'uid', 'applicability', 'moitem_description', 'movableother_value', 'movableother_innameof', 'moacquistion_date','moacquistion_manner','mo_remarks','created_date','update_date','status'));
	$query->condition('amo.m_other_id', $args, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAssoc();
	
	$form = array();
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
		'#type' => 'markup',
		//'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">OTHER MOVABLES - (Including jewellery and other valuables, motor vehicles, 
					  refrigerators and other articles or materials of Rs. 500 and over for each item)</h4> <div class="widget-toolbar">
					 </div></div><div class="widget-main">',
		//'#suffix' => ''
	);
	$form['m_other_id'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => trim($args),
	);
	
	$form['secondRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);
	$form['moitem_description'] = array(
		'#type' => 'textfield',
		'#title' => t('Description of Items'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['moitem_description'])!='N/A'? $resultData['moitem_description'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Description of Item'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['movableother_value'] = array(
		'#type' => 'textfield',
		'#title' => t('Value'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['movableother_value'])!='N/A'? $resultData['movableother_value'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Value'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['movableother_innameof'] = array(
		'#type' => 'textfield',
		'#title' => t('In whose name the asset is'),
		'#description' => t('(wife, child,dependant,other relationor benamdar)'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['movableother_innameof'])!='N/A'? $resultData['movableother_innameof'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'In whose name(wife, child,dependant,other relationor benamdar)the asset is'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['secondRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['thirdRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);
	$form['moacquistion_date'] = array(
		'#type' => 'textfield',
		'#title' => t('Date of Acquisition'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['moacquistion_date'])!='N/A'? date('d-m-Y',strtotime(trim($resultData['moacquistion_date']))) : '',
		'#attributes' => array('class'=>array('form-control','datepiker'),'placeholder'=>'Date of Acquisition'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['moacquistion_manner'] = array(
		'#type' => 'textfield',
		'#title' => t('Manner of Acquisition'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['moacquistion_manner'])!='N/A'? $resultData['moacquistion_manner'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Manner of Acquisition'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['thirdRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['fourthRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);
	$form['mo_remarks'] = array(
		'#type' => 'textarea',
		'#title' => t('Remarks'),
		'#required' => TRUE,
		'#default_value' => trim($resultData['mo_remarks'])!='N/A'? $resultData['mo_remarks'] : '',
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Remarks'),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	);
	$form['fourthRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	);
	$form['fifthRowStart'] = array(	
		'#prefix' => '<div class="row">',
		'#suffix' => ''
	);	 
	$form['submit_movableothers'] = array(
		'#type' => 'submit',
		'#value' => 'Update',
		'#attributes' => array('class'=>array('form-control btn btn-primary')),
		'#prefix' => '<div class="col-md-12"><div class="input-group">',
		'#suffix' => '</div></div>'
	);
	$form['fifthRowEnd'] = array(	
		'#prefix' => '',
		'#suffix' => '</div>'
	); 
	$form['form_end'] = array(
		'#type' => 'markup',
		//'#markup' => '</div>',
		'#suffix' => '</div></div>'
	);
	return $form;
}
function movable_other_form_edit_submit($form, &$form_state){
	$query = db_update('a_m_other');
	$query->fields(array('applicability'						=>  'Y',
						'moitem_description'					=>	trim($form_state['values']['moitem_description']),
						'movableother_value'					=>	trim($form_state['values']['movableother_value']),
						'movableother_innameof'					=>	trim($form_state['values']['movableother_innameof']),
						'moacquistion_date'						=>	trim($form_state['values']['moacquistion_date'])!='N/A'? date('Y-m-d H:i:s',strtotime(trim($form_state['values']['moacquistion_date']))) : 'N/A',
						'moacquistion_manner'					=>	trim($form_state['values']['moacquistion_manner']),
						'mo_remarks'							=>	trim($form_state['values']['mo_remarks']),
						'update_date'							=>	date('Y-m-d H:i:s'),
						));
	$query->condition('m_other_id', trim($form_state['values']['m_other_id']));
	$rs = $query->execute();	
	if($rs){
	 	drupal_set_message('Your record has been updated successfully.');
	 	drupal_goto('asset/other-movabale');
	}else{
	 	drupal_set_message('Unable to update your record. Please try again later.',$type = 'warning');
	 	drupal_goto('asset/other-movabale');
	}				
}
function asset_generate_report($form, &$form_state){
	global $user;	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$resultData 		= array();
	$resultData 		= getAssetDataWithStatus($user->uid, 0);
	$ImmovableLand 		= getImmovableLandDataWithStatus($user->uid, 0);
	$ImmovableHouse 	= getImmovableHouseDataWithStatus($user->uid, 0);
	$ImmovableOthers 	= getImmovableOthersDataWithStatus($user->uid, 0);
	$MmovableProperty 	= getMovablePropertyDataWithStatus($user->uid, 0);
	$MmovableOthers 	= getMovableOthersDataWithStatus($user->uid, 0);
	if(empty($resultData)){
	  	drupal_set_message('Please fill up Asset tab first.',$type = 'warning');
	  	drupal_goto('asset'); 
	}else if(empty($ImmovableLand)){
	  	drupal_set_message('Please fill Immovable-Land tab first.',$type = 'warning');
	  	drupal_goto('asset/land'); 
	}else if(empty($ImmovableHouse)){
	  	drupal_set_message('Please fill Immovable-House tab first.',$type = 'warning');
	  	drupal_goto('asset/house'); 
	}else if(empty($ImmovableOthers)){
	  	drupal_set_message('Please fill Immovable-Others tab first.',$type = 'warning');
	  	drupal_goto('asset/other-immovable'); 
	}else if(empty($MmovableProperty)){
	  	drupal_set_message('Please fill Movable-Property tab first.',$type = 'warning');
	  	drupal_goto('asset/movabale'); 
	}else if(empty($MmovableOthers)){
	  	drupal_set_message('Please fill Movable-Others tab first.',$type = 'warning');
	  	drupal_goto('asset/other-movabale'); 
	}
	$form = array();
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
		'#type' => 'markup',
		'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Preview Before Final Submission</h4> <div class="widget-toolbar">
					 </div></div><div class="widget-main">',
		//'#suffix' => ''
	);
	$form['asset_id'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => $resultData['id'],
	);
	$result	= getAllUidInfoFromPid($user->uid);
	$form['file_pass'] = array(
		'#type' => 'textfield',
		'#title' => t('Password for your signed document'),
		'#required' => TRUE,
		'#attributes' => array('class'=>array('form-control','doc_name_clear'),'placeholder'=>'Password for your signed document'),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	  );  
	$form['submit'] = array(
    	'#type' => 'submit',
		'#value' => 'Submit',
		'#attributes' => array('class'=>array('btn btn-info')),
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	);
	/*$header_asset = array();
    $rows_asset   = array();
	  
	$header_asset = array(  
		 array('data' => t('Asset Information'),'colspan' => 4),  
	);	
	$rows_asset[] = array(  
		 array('data' => t('<b>Name : </b>'.$result['fname'])),
		 array('data' => t('<b>Designation : </b>'.$resultData['designation'])), 
		 array('data' => t('<b>Contact No : </b>'.$result['mobile'])),
		 array('data' => t('<b>Email id : </b>'.$result['mail'])),
	);
	$rows_asset[] = array(  
		array('data' => t('<b>AY Year : </b>'.$resultData['declaration_yr'])), 
		array('data' => t('<b>Service : </b>'.$resultData['service_type'])), 
		array('data' => t('<b>Appointed As : </b>'.$resultData['appointed_as'])), 
		array('data' => t('<b>Substantive Pay : </b>'.$resultData['substantive_pay'])),
	);
	$form['asset_info'] = array(
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	);	
	$form['asset_info']['asset_details'] = array(
		'#theme'  => 'table',
		'#header' => $header_asset,
		'#rows'   => $rows_asset,
		'#attributes' => array('class' => array('table pretty table-bordered table-hover sticky-enabled')),
		'#empty'  => t('<center>No Records Found</center>'),
    );
	$form['immovable_land'] = array(
		'#prefix' => '<div class="col-md-12">'.get_immovable_land_list_for_report($resultData['id']),
		'#suffix' => '</div>'
	);
	$form['immovable_house'] = array(
		'#prefix' => '<div class="col-md-12">'.get_immovable_house_list_for_report($resultData['id']),
		'#suffix' => '</div>'
	);
	$form['immovable_others'] = array(
		'#prefix' => '<div class="col-md-12">'.get_immovable_other_list_for_report($resultData['id']),
		'#suffix' => '</div>'
	);
	$form['movable_property'] = array(
		'#prefix' => '<div class="col-md-12">'.get_movable_property_list_for_report($resultData['id']),
		'#suffix' => '</div>'
	);
	$form['movable_others'] = array(
		'#prefix' => '<div class="col-md-12">'.get_movable_other_list_for_report($resultData['id']),
		'#suffix' => '</div>'
	);
	$form['submit'] = array(
    	'#type' => 'submit',
		'#value' => 'Final Submit',
		'#attributes' => array('class'=>array('btn btn-info')),
		'#prefix' => '<div class="col-md-2">',
		'#suffix' => '</div>'
	);
	$generatePDF = l('View Generated PDF','generate/assetreport/'.$resultData['id'],array('html' => TRUE,'attributes'=>array('target'=>'_blank','title' => 'View','class'=>array('btn btn-yellow'))));
	
	  $form['generate_pdf'] = array(
	  	'#type' => 'markup',
		'#markup' => $generatePDF,
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	  );*/
	$form['form_end'] = array(
		'#type' => 'markup',
		'#markup' => '</div>',
		'#suffix' => '</div></div>'
	);
	return $form;
}
function asset_generate_report_submit($form, &$form_state){
	$query = db_update('a_asset_mst');
	$query->fields(array(
							'file_pass'=> trim($form_state['values']['file_pass']),
					));
	$query->condition('id', trim($form_state['values']['asset_id']), '=');
	$rs = $query->execute();	
	if($rs){
		drupal_set_message('Your password successfully saved.');
		drupal_goto('asset/final');
	}else{
		drupal_set_message('Unable to update your record. Please try again later.',$type = 'warning');
		drupal_goto('asset/report');
	}
}
/*function asset_generate_report_submit($form, &$form_state){
	$query = db_update('a_asset_mst');
	$query->fields(array(
							'status' => '1',
							'document_no'=> 'ASSET-'.date('Y-m-d').'-'.trim($form_state['values']['asset_id']),
							'created_date'=> date('Y-m-d H:i:s'),
							'update_date'=> date('Y-m-d H:i:s'),
							'pdf_generated_flag'=>'1'
					));
	$query->condition('id', trim($form_state['values']['asset_id']), '=');
	$rs = $query->execute();	
	if($rs){
		$query_l = db_update('a_im_land');
		$query_l->fields(array(
								'status' => '1',
						));
		$query_l->condition('asset_id', trim($form_state['values']['asset_id']), '=');
		$rs_l = $query_l->execute();
		
		$query_h = db_update('a_im_house');
		$query_h->fields(array(
								'status' => '1',
						));
		$query_h->condition('asset_id', trim($form_state['values']['asset_id']), '=');
		$rs_h = $query_h->execute();
		
		$query_o = db_update('a_im_other');
		$query_o->fields(array(
								'status' => '1',
						));
		$query_o->condition('asset_id', trim($form_state['values']['asset_id']), '=');
		$rs_o = $query_o->execute();
		
		$query_mo = db_update('a_m_other');
		$query_mo->fields(array(
								'status' => '1',
						));
		$query_mo->condition('asset_id', trim($form_state['values']['asset_id']), '=');
		$rs_mo = $query_mo->execute();
		
		$query_p = db_update('a_m_property');
		$query_p->fields(array(
								'status' => '1',
						));
		$query_p->condition('asset_id', trim($form_state['values']['asset_id']), '=');
		$rs_p = $query_p->execute();
		
		drupal_set_message('Your record successfully saved.');
		drupal_goto('propertyuser-dashboard');
	}else{
		drupal_set_message('Unable to update your record. Please try again later.',$type = 'warning');
		drupal_goto('asset/report');
	}
}*/
/* -------------------------------------------- Other Movable Property End ----------------------------------------------------- */

/* ---------------------------------------------- Assets Final start -------------------------------------------------------------*/

function asset_final_form($form, &$form_state){
	global $user;	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$resultData 		= array();
	$resultData 		= getAssetDataWithStatus($user->uid, 0);
	$ImmovableLand 		= getImmovableLandDataWithStatus($user->uid, 0);
	$ImmovableHouse 	= getImmovableHouseDataWithStatus($user->uid, 0);
	$ImmovableOthers 	= getImmovableOthersDataWithStatus($user->uid, 0);
	$MmovableProperty 	= getMovablePropertyDataWithStatus($user->uid, 0);
	$MmovableOthers 	= getMovableOthersDataWithStatus($user->uid, 0);

	if(empty($resultData)){
	  	drupal_set_message('Please fill up Asset tab first.',$type = 'warning');
	  	drupal_goto('asset'); 
	}else if(empty($ImmovableLand)){
	  	drupal_set_message('Please fill Immovable-Land tab first.',$type = 'warning');
	  	drupal_goto('asset/land'); 
	}else if(empty($ImmovableHouse)){
	  	drupal_set_message('Please fill Immovable-House tab first.',$type = 'warning');
	  	drupal_goto('asset/house'); 
	}else if(empty($ImmovableOthers)){
	  	drupal_set_message('Please fill Immovable-Others tab first.',$type = 'warning');
	  	drupal_goto('asset/other-immovable'); 
	}else if(empty($MmovableProperty)){
	  	drupal_set_message('Please fill Movable-Property tab first.',$type = 'warning');
	  	drupal_goto('asset/movabale'); 
	}else if(empty($MmovableOthers)){
	  	drupal_set_message('Please fill Movable-Others tab first.',$type = 'warning');
	  	drupal_goto('asset/other-movabale'); 
	}else if(empty($resultData['file_pass'])){
	  	drupal_set_message('Please fill Set Password tab first.',$type = 'warning');
	  	drupal_goto('asset/report'); 
	}
	$form = array();
	$form['#attributes']['class'][] = 'form-vertical';
	
	$form['form_begin'] = array(
		'#type' => 'markup',
		'#markup' => '<div class="row">',
		'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Final Submission</h4> <div class="widget-toolbar">
					 </div></div><div class="widget-main">',
		//'#suffix' => ''
	);
	$form['asset_id'] = array(
		'#type' => 'hidden',
		'#required' => TRUE,
		'#default_value' => $resultData['id'],
	);
	$result	= getAllUidInfoFromPid($user->uid);
	
	$generatePDF = l('Click here to download the PDF and Signature on it','generate/assetreport/'.$resultData['id'],array('html' => TRUE,'attributes'=>array('target'=>'_blank','title' => 'View','class'=>array('btn btn-success'))));
	
	$form['generate_pdf'] = array(
		'#type' => 'markup',
		'#markup' => $generatePDF,
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>'
	);
	$form['doc_file'] = array(
		'#type' => 'file',
		'#title' => t('Upload Signed (PDF only, Max size 1MB)'),
		'#attributes' => array('class'=>array('form-control'),'placeholder'=>'Upload documents'),
		'#prefix' => '<div id="replace_div_file"><div class="col-md-4">',
		'#suffix' => '</div></div>'
	  );
	$form['submit'] = array(
    	'#type' => 'submit',
		'#value' => 'Final Submit',
		'#attributes' => array('class'=>array('btn btn-info')),
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
function asset_final_form_submit($form, &$form_state){
	if(trim($_FILES['files']['name']['doc_file'])!=""){
		
		$asset_id = trim($form_state['input']['asset_id']);
		//$file_pass = trim($form_state['input']['file_pass']);
		$file_name = trim($_FILES['files']['name']['doc_file']);
		$file_path = $_FILES['files']['tmp_name']['doc_file'];
	  	$file_size = $_FILES['files']['size']['doc_file'];
		$file_ext = pathinfo($file_name, PATHINFO_EXTENSION);
		
		$directory_path	=	file_default_scheme().'://upload/asset/';
		
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
			drupal_set_message($error_description, $type='error');
		}else{
			$file->status = FILE_STATUS_PERMANENT; //ADDED
		    file_save($file);
			$upld_directory_path=file_create_url($file->uri); //NOT USED
			$Full_File_Path=$file->uri;
			
			$pos = strrpos($upld_directory_path, '/');
			$filename = $pos === false ? $upld_directory_path : substr($upld_directory_path, $pos + 1);
			
			$query = db_update('a_asset_mst');
			$query->fields(array(
									'status' => '1',
									'document_no'=> 'ASSET-'.date('Y-m-d').'-'.trim($form_state['values']['asset_id']),
									'created_date'=> date('Y-m-d H:i:s'),
									'update_date'=> date('Y-m-d H:i:s'),
									'pdf_generated_flag'=>'1',
									//'file_pass' => trim($form_state['input']['file_pass']),
									'file_name' => trim($filename),
							));
			$query->condition('id', trim($form_state['input']['asset_id']));
			$rs = $query->execute();	
			if($rs){
				$query_l = db_update('a_im_land');
				$query_l->fields(array(
										'status' => '1',
								));
				$query_l->condition('asset_id', trim($form_state['input']['asset_id']), '=');
				$rs_l = $query_l->execute();
				
				$query_h = db_update('a_im_house');
				$query_h->fields(array(
										'status' => '1',
								));
				$query_h->condition('asset_id', trim($form_state['input']['asset_id']), '=');
				$rs_h = $query_h->execute();
				
				$query_o = db_update('a_im_other');
				$query_o->fields(array(
										'status' => '1',
								));
				$query_o->condition('asset_id', trim($form_state['input']['asset_id']), '=');
				$rs_o = $query_o->execute();
				
				$query_mo = db_update('a_m_other');
				$query_mo->fields(array(
										'status' => '1',
								));
				$query_mo->condition('asset_id', trim($form_state['input']['asset_id']), '=');
				$rs_mo = $query_mo->execute();
				
				$query_p = db_update('a_m_property');
				$query_p->fields(array(
										'status' => '1',
								));
				$query_p->condition('asset_id', trim($form_state['input']['asset_id']), '=');
				$rs_p = $query_p->execute();
				
				drupal_set_message('Your record successfully saved.');
				drupal_goto('propertyuser-dashboard');
			}else{
				drupal_set_message('Unable to update your record. Please try again later.',$type = 'warning');
				drupal_goto('asset/final');
			}
			
			
			
		}
	}else{
		drupal_set_message('Submit with proper inputs.', $type='warning');
	}
}

/* ---------------------------------------------- Assets Final End -------------------------------------------------------------*/