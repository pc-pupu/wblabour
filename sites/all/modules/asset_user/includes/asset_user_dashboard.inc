<?php
function asset_user_dashboard($form, &$form_state){
	global $base_root,$base_path,$user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}else{
		drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
		
		$form = array();
		$form['#attributes']['class'][] = 'form-vertical';
		$form['form_begin'] = array(
			'#type' => 'markup',
			'#markup' => '<div class="row">',
			'#prefix' => '<div class="widget-box"><div class="widget-header"><h4 class="widget-title">Submitted Data</h4> <div class="widget-toolbar">
						 </div></div><div class="widget-main">',
			//'#suffix' => ''
		);
		$form['submission_data'] = array(
			'#prefix' => '<div class="col-md-12">'.getSubmissionData($user->uid, 1),
			'#suffix' => '</div>'
		);
	 	$form['form_end'] = array(
			'#type' => 'markup',
			'#markup' => '</div>',
			'#suffix' => '</div></div>'
		);
		return $form;
	}
}

function getSubmissionData($uid, $status){
	$query = db_select('a_asset_mst', 'assetmst');
	$query ->fields('assetmst', array('id','uid','declaration_yr','designation','created_date','status','forward_status','operator_uid'));
	$query->condition('assetmst.status',$status,'=');
	$query->condition('assetmst.uid', $uid, '='); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
	
	//print_r($resultData); exit;
	
	$output = '';
	$header = array(
				array('data'=> 'Year'),
				//array('data'=> 'Designation'),
				array('data'=> 'Submission Date'),
				array('data'=> 'Status'),
				array('data'=> 'PDF'),
			);
			
	$rows = array();
	foreach($resultData as $val){
		
		$operatorInfo = getLoginUserDetailForAsset($val->operator_uid); 
		
		if($val->forward_status == '0'){
			if($operatorInfo['directorate_code'] == 'DB'){
				$status = "Received at Boilers Directorate"; 
			}elseif($operatorInfo['directorate_code'] == 'LC'){
				$status = "Received at Labour Commissionerate"; 
			}elseif($operatorInfo['directorate_code'] == 'DE'){
				$status = "Received at Employment Directorate";
			}elseif($operatorInfo['directorate_code'] == 'DF'){
				$status = "Received at Factories Directorate";
			}elseif($operatorInfo['directorate_code'] == 'ESI'){
				$status = "Received at ESI(MB) Scheme Directorate";
			}elseif($operatorInfo['directorate_code'] == 'LD'){
			   $status = "Received at Labour Department"; 
			}elseif($operatorInfo['directorate_code'] == 'DIT'){
				$status = "Received at Industrial Tribunal Directorate";
			}elseif($operatorInfo['directorate_code'] == 'EIC'){
				$status = "Received at Employees Insurance Court";
			}elseif($operatorInfo['directorate_code'] == 'DEC'){
				$status = "Received at Employees Compensation Directorate";
			}
		}elseif($val->forward_status == 'F'){
			$status = "Forwarded to Labour Department";
		}elseif($val->forward_status == 'R'){
			$status = "Rejected at Labour Department";
		}elseif($val->forward_status == 'A'){
			$status = "Received at Labour Department";
		}else{
			$status = "N/A";
		}
	
	/*$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'acknowledgement-print/'.$val->uid.'/'.$val->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));*/
						 
	$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 
						 'ack-file/'.$val->uid.'/'.$val->declaration_yr, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
	  
	  $rows [] = array(  
			  array('data' => t($val->declaration_yr)), 	
			  //array('data' => t($val->designation)),
			  array('data' => trim($val->created_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->created_date))) : 'N/A'),
			  array('data' => $status),
			  array('data' => $link),
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

function individual_officer_list() {
  global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}	
  drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
  //$direc_code = getLoginUserDetailForAsset($user->uid);
	 
  
	$querynodal = db_select('a_user_details','ud');
	$querynodal->leftJoin('a_user_details_service', 'us', 'ud.uid = us.uid');
	$querynodal->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = us.directorate_code'); 
	$querynodal->fields('ud', array('uid','fname','status'));
	$querynodal->fields('dm', array('id','directorate_name'));
	$querynodal->fields('us', array('designation','directorate_code','district_code','service_status','emp_group','office_id'));
	$querynodal->condition('ud.status',0,'=');
	$querynodal->condition('us.service_status',1,'=');
	//$querynodal->condition('us.directorate_code',$direc_code['directorate_code'],'=');
	$querynodal->condition('ud.uid',$user->uid,'=');
	$result1 = $querynodal->execute();
	$querynodalfinal = $result1->fetchAll();
	
	//print_r($querynodalfinal); exit;
	 
	$header = array();
	$rows   = array();
	$output = '';

	
	$header = array(  
	  //array('data' => t('<b>Sl No.  </b>')),	
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
		
		$rows[] = array( 
		  //$i,
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
	
	$output = theme_table(
    array(
	  'type' => 'table',
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id'=>'table_div_replace',  'class' => array('table', 'pretty', 'table-bordered table-hover')),
      'sticky' => true,
      'caption' => '<h3>Yearly Received List</h3>',
      'colgroups' => array(),
	  //'multiple' => FALSE,
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  );

 return '<div class="formdvider viewlist">'.$output.'</div>';	
	 
}

function individual_showcause_list(){
	global $user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
		drupal_goto('profileupdate');
		exit;
	}	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
	
	$query = db_select('a_showcause_notice', 'assetmst');
	$query ->fields('assetmst', array('showcause_id','uid','message','send_by','created_date','status'));
	$query->condition('assetmst.status','1','=');
	$query->condition('assetmst.uid', $user->uid, '='); 
	$query->orderBy('assetmst.created_date', 'DESC'); 
	$result = $query->execute();
	$resultData = $result->fetchAll();
	
	//print_r($resultData); exit;
	
	$output = '';
	$header = array(
				array('data'=> 'Sl No'),
				array('data'=> 'Message'),
				//array('data'=> 'Send By'),
				array('data'=> 'Date'),
				array('data'=> 'PDF'),
			);
			
	$rows = array();
	$i = 0;
	foreach($resultData as $val){
		
		$i++;	
	
	$link =  l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'asset').'/images/pdf.png">'), 'showcause-print/'.$val->showcause_id.'/'.date('Y'), array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')));
	  
	  $rows [] = array(  
	  		  $i,	
			  array('data' => t($val->message)),
			  //array('data' => t($val->send_by)),
			  array('data' => trim($val->created_date) != 'N/A' ? t(date('d-m-Y',strtotime($val->created_date))) : 'N/A'),
			  array('data' => $link),
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