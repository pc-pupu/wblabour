<?php
function asset_admin_dashboard($form, &$form_state){
	global $base_root,$base_path,$user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	$form = array();
	$form['form_begin'] = array(
		'#type' => 'markup',
		'#markup' => 'Welcome to Assets Admin Dashboard',
	 );
	$form['form_print'] = array(
		'#type' => 'markup',
		'#markup' => '<a href="#" id="print-button" class="btn btn-danger" onclick="window.print();return false;" style="float: right;"><i class="fa fa-print"></i> Print</a>',
	 ); 
	
	$form['year_list'] = array(
		'#title' => t('Select Year for Previous Year Dashboard'),	
		'#type' => 'select',
		//'#required' => TRUE,
		'#options' => array('2023'=>'2023','2022'=>'2022','2021'=>'2021','2020'=>'2020','2019'=>'2019'),
		'#ajax' => array(
				'callback' => 'ajax_admin_dashboard_change_callback',
		     ),
		'#attributes' => array('class'=>array('form-control pull-right')),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	); 
	
	$recent_date = isset($form_state['values']['year_list'])? $form_state['values']['year_list'] : date('Y'); 
	
	$form['table_data'] = array(
		'#type' => 'markup',
		'#markup' => getYearWiseAllDirectorateData($recent_date),
		'#prefix' => '<div id="admin_dashboard_change_div">',
		'#suffix' => '</div>'
	 ); 
	 
	 $form['footer_text'] = array(
		'#type' => 'markup',
		'#markup' => '** The figuers shown above are reflecting the data given by the Department / Directorate\'s as on '.date('d-m-Y'),
	 ); 
	 	
	 return $form;
}

function ajax_admin_dashboard_change_callback($form, &$form_state){
	$commands   = array();
	$commands[] = ajax_command_replace('#admin_dashboard_change_div', '<div id="admin_dashboard_change_div">'.drupal_render($form['table_data']).'</div>');
	return array('#type' => 'ajax', '#commands' => $commands);
}

function getYearWiseAllDirectorateData($current_year){
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');	
	
	$query = db_select('a_user_details','ud');
	$query->leftJoin('a_user_details_service', 'us', 'ud.uid = us.uid');
	$query->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = us.directorate_code'); 
	$query->fields('ud', array('uid','fname','status'));
	$query->fields('dm', array('id','directorate_name'));
	$query->fields('us', array('designation','directorate_code','district_code','service_status','emp_group','office_id'));
	$query->condition('ud.status',0,'=');
	$query->condition('us.service_status',1,'=');
	//$query->condition('us.directorate_code',$direc_code['directorate_code'],'=');
	//$query->condition('us.office_id',$fdata->office_id,'=');
	//$query->condition('us.emp_group',array('B','C'),'IN');
	$result = $query->execute();
	$rsData = $result->fetchAll(); 
	
	//print_r($rsData); exit;
    
 /* $query = db_select('a_asset_mst','am');
  $query->leftJoin('a_user_details', 'ud', 'ud.uid = am.uid');  
  $query->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code'); 
  $query->leftJoin('a_user_details_service', 'us', 'am.uid = us.uid');  
  $query->fields('am', array('uid','declaration_yr','designation','directorate_code','status','created_date'));
  $query->fields('ud', array('fname','status'));
  $query->fields('dm', array('id','directorate_name'));
  $query->fields('us', array('designation','district_code','service_status','emp_group')); 
  $query->condition('ud.status',0,'=');
  $query->condition('us.service_status',1,'=');
  $query->condition('am.declaration_yr',$current_year,'=');
  $result = $query->execute();
  $rsData = $result->fetchAll();*/
  
   //$querypending->condition('am.status',0,'=');
  //print_r($rsData); exit;
  
  $ldsumtotalABC = 0;
  $ldsumtotalsubmittedABC = 0;
  $ldsumtotalpendingABC = 0;
  
  $ldtotal_cntA = 0;
  $ldsubmitted_cntA = 0;
  $ldpending_cntA = 0;
  $ldtotal_cntBC = 0;
  $ldsubmitted_cntBC = 0;
  $ldpending_cntBC = 0;
  
  $lcsumtotalABC = 0;
  $lcsumtotalsubmittedABC = 0;
  $lcsumtotalpendingABC = 0;
   
  $lctotal_cntA = 0;
  $lcsubmitted_cntA = 0;
  $lcpending_cntA = 0;
  $lctotal_cntBC = 0;
  $lcsubmitted_cntBC = 0;
  $lcpending_cntBC = 0;
  
  $desumtotalABC = 0;
  $desumtotalsubmittedABC = 0;
  $desumtotalpendingABC = 0;
  
  $detotal_cntA = 0;
  $desubmitted_cntA = 0;
  $depending_cntA = 0;
  $detotal_cntBC = 0;
  $desubmitted_cntBC = 0;
  $depending_cntBC = 0;
  
  $esisumtotalABC = 0;
  $esisumtotalsubmittedABC = 0;
  $esisumtotalpendingABC = 0;
  
  $esitotal_cntA = 0;
  $esisubmitted_cntA = 0;
  $esipending_cntA = 0;
  $esitotal_cntBC = 0;
  $esisubmitted_cntBC = 0;
  $esipending_cntBC = 0;
  
  $factoriessumtotalABC = 0;
  $factoriessumtotalsubmittedABC = 0;
  $factoriessumtotalpendingABC = 0; 
  
  $factoriestotal_cntA = 0;
  $factoriessubmitted_cntA = 0;
  $factoriespending_cntA = 0;
  $factoriestotal_cntBC = 0;
  $factoriessubmitted_cntBC = 0;
  $factoriespending_cntBC = 0;
  
  $dbsumtotalABC = 0;
  $dbsumtotalsubmittedABC = 0;
  $dbsumtotalpendingABC = 0; 
  
  $dbtotal_cntA = 0;
  $dbsubmitted_cntA = 0;
  $dbpending_cntA = 0;
  $dbtotal_cntBC = 0;
  $dbsubmitted_cntBC = 0;
  $dbpending_cntBC = 0;
  
  $ditsumtotalABC = 0;
  $ditsumtotalsubmittedABC = 0;
  $ditsumtotalpendingABC = 0; 
  
  $dittotal_cntA = 0;
  $ditsubmitted_cntA = 0;
  $ditpending_cntA = 0;
  $dittotal_cntBC = 0;
  $ditsubmitted_cntBC = 0;
  $ditpending_cntBC = 0;
  
  $decsumtotalABC = 0;
  $decsumtotalsubmittedABC = 0;
  $decsumtotalpendingABC = 0; 
  
  $dectotal_cntA = 0;
  $decsubmitted_cntA = 0;
  $decpending_cntA = 0;
  $dectotal_cntBC = 0;
  $decsubmitted_cntBC = 0;
  $decpending_cntBC = 0;
  
   
  
   foreach($rsData as $data){
	   $rs = yearWiseIndividualUserData(array('0'=>$current_year),$data->uid);
	   /* --------------------------------------------- LD BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'LD' AND $data->emp_group == 'A'){
				$ldtotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'LD' AND $data->emp_group == 'A' AND $rs[0]->status == '1' ){
				$ldsubmitted_cntA++;
	  }
	  /* if(trim($data->directorate_code) == 'LD' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$ldpending_cntA++;
	  }*/
	   if(trim($data->directorate_code) == 'LD' AND ($data->emp_group == 'B' OR $data->emp_group == 'C')){
				$ldtotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'LD' AND ($data->emp_group == 'B' OR $data->emp_group == 'C') AND $rs[0]->status == '1' ){
				$ldsubmitted_cntBC++;
	  }
	   /*if(trim($data->directorate_code) == 'LD' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$ldpending_cntBC++;
	  }*/
	  
    /* --------------------------------------------- LD END ---------------------------- */	
		
		
	  /* --------------------------------------------- LC BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'LC' AND $data->emp_group == 'A'){
				$lctotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'LC' AND $data->emp_group == 'A' AND $rs[0]->status == '1' ){
				$lcsubmitted_cntA++;
	  }
	  /* if(trim($data->directorate_code) == 'LC' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$lcpending_cntA++;
	  }*/
	   if(trim($data->directorate_code) == 'LC' AND ($data->emp_group == 'B' OR $data->emp_group == 'C')){
				$lctotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'LC' AND ($data->emp_group == 'B' OR $data->emp_group == 'C') AND $rs[0]->status == '1' ){
				$lcsubmitted_cntBC++;
	  }
	   /*if(trim($data->directorate_code) == 'LC' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$lcpending_cntBC++;
	  }*/
    /* --------------------------------------------- LC END ---------------------------- */	
	
    /* --------------------------------------------- EMP BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'DE' AND $data->emp_group == 'A'){
				$detotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'DE' AND $data->emp_group == 'A' AND $rs[0]->status == '1' ){
				$desubmitted_cntA++;
	  }
	   /*if(trim($data->directorate_code) == 'DE' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$depending_cntA++;
	  }*/
	   if(trim($data->directorate_code) == 'DE' AND ($data->emp_group == 'B' OR $data->emp_group == 'C')){
				$detotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'DE' AND ($data->emp_group == 'B' OR $data->emp_group == 'C') AND $rs[0]->status == '1' ){
				$desubmitted_cntBC++;
	  }
	   /*if(trim($data->directorate_code) == 'DE' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$depending_cntBC++;
	  }*/
	
	 /* --------------------------------------------- EMP END ---------------------------- */	
	
   /* --------------------------------------------- ESI BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'ESI' AND $data->emp_group == 'A'){
				$esitotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'ESI' AND $data->emp_group == 'A' AND $rs[0]->status == '1' ){
				$esisubmitted_cntA++;
	  }
	   /*if(trim($data->directorate_code) == 'ESI' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$esipending_cntA++;
	  }*/
	   if(trim($data->directorate_code) == 'ESI' AND ($data->emp_group == 'B' OR $data->emp_group == 'C')){
				$esitotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'ESI' AND ($data->emp_group == 'B' OR $data->emp_group == 'C') AND $rs[0]->status == '1' ){
				$esisubmitted_cntBC++;
	  }
	   /*if(trim($data->directorate_code) == 'ESI' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$esipending_cntBC++;
	  }*/
	
	 /* --------------------------------------------- ESI END ---------------------------- */	
	
	 /* --------------------------------------------- Factories BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'DF' AND $data->emp_group == 'A'){
				$factoriestotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'DF' AND $data->emp_group == 'A' AND $rs[0]->status == '1' ){
				$factoriessubmitted_cntA++;
	  }
	  /* if(trim($data->directorate_code) == 'DF' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$factoriespending_cntA++;
	  }*/
	   if(trim($data->directorate_code) == 'DF' AND ($data->emp_group == 'B' OR $data->emp_group == 'C')){
				$factoriestotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'DF' AND ($data->emp_group == 'B' OR $data->emp_group == 'C') AND $rs[0]->status == '1' ){
				$factoriessubmitted_cntBC++;
	  }
	  /* if(trim($data->directorate_code) == 'DF' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$factoriespending_cntBC++;
	  }*/
	
	 /* --------------------------------------------- Factories END ---------------------------- */	
	 
    /* --------------------------------------------- Boilers BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'DB' AND $data->emp_group == 'A'){
				$dbtotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'DB' AND $data->emp_group == 'A' AND $rs[0]->status == '1' ){
				$dbsubmitted_cntA++;
	  }
	   /*if(trim($data->directorate_code) == 'DB' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$dbpending_cntA++;
	  }*/
	   if(trim($data->directorate_code) == 'DB' AND ($data->emp_group == 'B' OR $data->emp_group == 'C')){
				$dbtotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'DB' AND ($data->emp_group == 'B' OR $data->emp_group == 'C') AND $rs[0]->status == '1' ){
				$dbsubmitted_cntBC++;
	  }
	   /*if(trim($data->directorate_code) == 'DB' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$dbpending_cntBC++;
	  }*/
	
	 /* --------------------------------------------- Boilers END ---------------------------- */	
	
	
	 /* --------------------------------------------- Industrial Tribunal BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'DIT' AND $data->emp_group == 'A'){
				$dittotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'DIT' AND $data->emp_group == 'A' AND $rs[0]->status == '1' ){
				$ditsubmitted_cntA++;
	  }
	   /*if(trim($data->directorate_code) == 'DIT' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$ditpending_cntA++;
	  }*/
	   if(trim($data->directorate_code) == 'DIT' AND ($data->emp_group == 'B' OR $data->emp_group == 'C')){
				$dittotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'DIT' AND ($data->emp_group == 'B' OR $data->emp_group == 'C') AND $rs[0]->status == '1' ){
				$ditsubmitted_cntBC++;
	  }
	   /*if(trim($data->directorate_code) == 'DIT' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$ditpending_cntBC++;
	  }*/
	
	 /* --------------------------------------------- Industrial Tribunal END ---------------------------- */	
	
	 /* --------------------------------------------- Directorate of Employees Compensation BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'DEC' AND $data->emp_group == 'A'){
				$dectotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'DEC' AND $data->emp_group == 'A' AND $rs[0]->status == '1' ){
				$decsubmitted_cntA++;
	  }
	   /*if(trim($data->directorate_code) == 'DEC' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$decpending_cntA++;
	  }*/
	   if(trim($data->directorate_code) == 'DEC' AND ($data->emp_group == 'B' OR $data->emp_group == 'C')){
				$dectotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'DEC' AND ($data->emp_group == 'B' OR $data->emp_group == 'C') AND $rs[0]->status == '1' ){
				$decsubmitted_cntBC++;
	  }
	   /*if(trim($data->directorate_code) == 'DEC' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$decpending_cntBC++;
	  }*/
	
	 /* --------------------------------------------- Directorate of Employees Compensation END ---------------------------- */	
   }
   
      $ldsumtotalABC = $ldtotal_cntA + $ldtotal_cntBC;
 	  $ldsumtotalsubmittedABC = $ldsubmitted_cntA + $ldsubmitted_cntBC;
	  $ldpending_cntA = $ldtotal_cntA - $ldsubmitted_cntA;
	  $ldpending_cntBC = $ldtotal_cntBC - $ldsubmitted_cntBC;
 	  $ldsumtotalpendingABC = $ldpending_cntA + $ldpending_cntBC;
	  
	  $lcsumtotalABC = $lctotal_cntA + $lctotal_cntBC;
 	  $lcsumtotalsubmittedABC = $lcsubmitted_cntA + $lcsubmitted_cntBC;
	  $lcpending_cntA = $lctotal_cntA - $lcsubmitted_cntA;
	  $lcpending_cntBC = $lctotal_cntBC - $lcsubmitted_cntBC;
 	  $lcsumtotalpendingABC = $lcpending_cntA + $lcpending_cntBC;
	  
	  $desumtotalABC = $detotal_cntA + $detotal_cntBC;
 	  $desumtotalsubmittedABC = $desubmitted_cntA + $desubmitted_cntBC;
	  $depending_cntA = $detotal_cntA - $desubmitted_cntA;
	  $depending_cntBC = $detotal_cntBC - $desubmitted_cntBC;
 	  $desumtotalpendingABC = $depending_cntA + $depending_cntBC;
	  
	  $esisumtotalABC = $esitotal_cntA + $esitotal_cntBC;
 	  $esisumtotalsubmittedABC = $esisubmitted_cntA + $esisubmitted_cntBC;
	  $esipending_cntA = $esitotal_cntA - $esisubmitted_cntA;
	  $esipending_cntBC = $esitotal_cntBC - $esisubmitted_cntBC;
 	  $esisumtotalpendingABC = $esipending_cntA + $esipending_cntBC;
	  
	  $factoriessumtotalABC = $factoriestotal_cntA + $factoriestotal_cntBC;
 	  $factoriessumtotalsubmittedABC = $factoriessubmitted_cntA + $factoriessubmitted_cntBC;
	  $factoriespending_cntA = $factoriestotal_cntA - $factoriessubmitted_cntA;
	  $factoriespending_cntBC = $factoriestotal_cntBC - $factoriessubmitted_cntBC;
 	  $factoriessumtotalpendingABC = $factoriespending_cntA + $factoriespending_cntBC;
	  
	  $dbsumtotalABC = $dbtotal_cntA + $dbtotal_cntBC;
 	  $dbsumtotalsubmittedABC = $dbsubmitted_cntA + $dbsubmitted_cntBC;
	  $dbpending_cntA = $dbtotal_cntA - $dbsubmitted_cntA;
	  $dbpending_cntBC = $dbtotal_cntBC - $dbsubmitted_cntBC;
 	  $dbsumtotalpendingABC = $dbpending_cntA + $dbpending_cntBC;
	  
	  $ditsumtotalABC = $dittotal_cntA + $dittotal_cntBC;
 	  $ditsumtotalsubmittedABC = $ditsubmitted_cntA + $ditsubmitted_cntBC;
	  $ditpending_cntA = $dittotal_cntA - $ditsubmitted_cntA;
	  $ditpending_cntBC = $dittotal_cntBC - $ditsubmitted_cntBC;
 	  $ditsumtotalpendingABC = $ditpending_cntA + $ditpending_cntBC;
	  
	  $decsumtotalABC = $dectotal_cntA + $dectotal_cntBC;
 	  $decsumtotalsubmittedABC = $decsubmitted_cntA + $decsubmitted_cntBC;
	  $decpending_cntA = $dectotal_cntA - $decsubmitted_cntA;
	  $decpending_cntBC =  $dectotal_cntBC - $decsubmitted_cntBC;
 	  $decsumtotalpendingABC = $decpending_cntA + $decpending_cntBC;     

	
	$header = array();
	$rows = array();
	$header = array(
				array('data'=> 'Directorate'),
				array('data'=> 'Designation'),
				array('data'=> 'Total'),
				array('data'=> 'Submitted'),
				array('data'=> 'Pending'),
			);
	// for Labour Department		
	$rows[] = array(
				array('data' => 'Labour Department', 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center;'),
				array('data' => 'Group A'),
				array('data' => $ldtotal_cntA),
				//array('data' => $ldsubmitted_cntA),
				array('data' => l($ldsubmitted_cntA, 'submitted-list/LD/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($ldpending_cntA, 'pending-list/LD/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $ldpending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $ldtotal_cntBC),
				//array('data' => $ldsubmitted_cntBC),
				array('data' => l($ldsubmitted_cntBC, 'submitted-list/LD/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($ldpending_cntBC, 'pending-list/LD/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $ldpending_cntBC),
		);	
		
	$rows[] = array(
				array('data' => 'Total', 'style'=>'font-weight: bold;'),
				array('data' => $ldsumtotalABC, 'style'=>'font-weight: bold;'),
				array('data' => $ldsumtotalsubmittedABC, 'style'=>'font-weight: bold;'),
				array('data' => $ldsumtotalpendingABC, 'style'=>'font-weight: bold;'),
		);		
	// Labour Department end
		
	$rows[] = array(
				array('data' => '&nbsp;', 'colspan'=>'5'),
		);	
		
	// for Labour Commissionerate
	$rows[] = array(
				array('data' => 'Labour Commissionerate', 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center;'),
				array('data' => 'Group A'),
				array('data' => $lctotal_cntA),
				//array('data' => $lcsubmitted_cntA),
				array('data' => l($lcsubmitted_cntA, 'submitted-list/LC/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($lcpending_cntA, 'pending-list/LC/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $lcpending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $lctotal_cntBC),
				//array('data' => $lcsubmitted_cntBC),
				array('data' => l($lcsubmitted_cntBC, 'submitted-list/LC/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($lcpending_cntBC, 'pending-list/LC/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $lcpending_cntBC),
		);
		
	$rows[] = array(
				array('data' => 'Total', 'style'=>'font-weight: bold;'),
				array('data' => $lcsumtotalABC, 'style'=>'font-weight: bold;'),
				array('data' => $lcsumtotalsubmittedABC, 'style'=>'font-weight: bold;'),
				array('data' => $lcsumtotalpendingABC, 'style'=>'font-weight: bold;'),
		);						
  	//Labour Commissionerate end
	
	$rows[] = array(
				array('data' => '&nbsp;', 'colspan'=>'5'),
		);	
		
	// for Directorate of Employment
	$rows[] = array(
				array('data' => 'Directorate of Employment', 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center;'),
				array('data' => 'Group A'),
				array('data' => $detotal_cntA),
				//array('data' => $desubmitted_cntA),
				array('data' => l($desubmitted_cntA, 'submitted-list/DE/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($depending_cntA, 'pending-list/DE/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $depending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $detotal_cntBC),
				//array('data' => $desubmitted_cntBC),
				array('data' => l($desubmitted_cntBC, 'submitted-list/DE/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($depending_cntBC, 'pending-list/DE/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $depending_cntBC),
		);	
	$rows[] = array(
				array('data' => 'Total', 'style'=>'font-weight: bold;'),
				array('data' => $desumtotalABC, 'style'=>'font-weight: bold;'),
				array('data' => $desumtotalsubmittedABC, 'style'=>'font-weight: bold;'),
				array('data' => $desumtotalpendingABC, 'style'=>'font-weight: bold;'),
		);			
  	//Directorate of Employment end
	
	$rows[] = array(
				array('data' => '&nbsp;', 'colspan'=>'5'),
	);	

	// for Directorate of ESI (MB) Scheme
	$rows[] = array(
				array('data' => 'Directorate of ESI (MB) Scheme', 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center;'),
				array('data' => 'Group A'),
				array('data' => $esitotal_cntA),
				//array('data' => $esisubmitted_cntA),
				array('data' => l($esisubmitted_cntA, 'submitted-list/ESI/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($esipending_cntA, 'pending-list/ESI/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $esipending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $esitotal_cntBC),
				//array('data' => $esisubmitted_cntBC),
				array('data' => l($esisubmitted_cntBC, 'submitted-list/ESI/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($esipending_cntBC, 'pending-list/ESI/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $esipending_cntBC),
		);	
	$rows[] = array(
				array('data' => 'Total', 'style'=>'font-weight: bold;'),
				array('data' => $esisumtotalABC, 'style'=>'font-weight: bold;'),
				array('data' => $esisumtotalsubmittedABC, 'style'=>'font-weight: bold;'),
				array('data' => $esisumtotalpendingABC, 'style'=>'font-weight: bold;'),
		);			
  	//Directorate of ESI (MB) Scheme end
	
	$rows[] = array(
				array('data' => '&nbsp;', 'colspan'=>'5'),
	);	
	
	// for Directorate of Factories
	$rows[] = array(
				array('data' => 'Directorate of Factories', 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center;'),
				array('data' => 'Group A'),
				array('data' => $factoriestotal_cntA),
				//array('data' => $factoriessubmitted_cntA),
				array('data' => l($factoriessubmitted_cntA, 'submitted-list/DF/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($factoriespending_cntA, 'pending-list/DF/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $factoriespending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $factoriestotal_cntBC),
				//array('data' => $factoriessubmitted_cntBC),
				array('data' => l($factoriessubmitted_cntBC, 'submitted-list/DF/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($factoriespending_cntBC, 'pending-list/DF/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $factoriespending_cntBC),
		);	
	$rows[] = array(
				array('data' => 'Total', 'style'=>'font-weight: bold;'),
				array('data' => $factoriessumtotalABC, 'style'=>'font-weight: bold;'),
				array('data' => $factoriessumtotalsubmittedABC, 'style'=>'font-weight: bold;'),
				array('data' => $factoriessumtotalpendingABC, 'style'=>'font-weight: bold;'),
		);		
  	//Directorate of Factories end
	
	$rows[] = array(
				array('data' => '&nbsp;', 'colspan'=>'5'),
	);	
	
	// for Directorate of Boilers
	$rows[] = array(
				array('data' => 'Directorate of Boilers', 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center;'),
				array('data' => 'Group A'),
				array('data' => $dbtotal_cntA),
				//array('data' => $dbsubmitted_cntA),
				array('data' => l($dbsubmitted_cntA, 'submitted-list/DB/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($dbpending_cntA, 'pending-list/DB/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $dbpending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $dbtotal_cntBC),
				//array('data' => $dbsubmitted_cntBC),
				array('data' => l($dbsubmitted_cntBC, 'submitted-list/DB/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($dbpending_cntBC, 'pending-list/DB/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $dbpending_cntBC),
		);
	$rows[] = array(
				array('data' => 'Total', 'style'=>'font-weight: bold;'),
				array('data' => $dbsumtotalABC, 'style'=>'font-weight: bold;'),
				array('data' => $dbsumtotalsubmittedABC, 'style'=>'font-weight: bold;'),
				array('data' => $dbsumtotalpendingABC, 'style'=>'font-weight: bold;'),
		);			
  	//Directorate of Boilers end
	
		$rows[] = array(
				array('data' => '&nbsp;', 'colspan'=>'5'),
	);	
	
	// for Industrial Tribunals
	$rows[] = array(
				array('data' => 'Industrial Tribunals', 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center;'),
				array('data' => 'Group A'),
				array('data' => $dittotal_cntA),
				//array('data' => $ditsubmitted_cntA),
				array('data' => l($ditsubmitted_cntA, 'submitted-list/DIT/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($ditpending_cntA, 'pending-list/DIT/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $ditpending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $dittotal_cntBC),
				//array('data' => $ditsubmitted_cntBC),
				array('data' => l($ditsubmitted_cntBC, 'submitted-list/DIT/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($ditpending_cntBC, 'pending-list/DIT/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $ditpending_cntBC),
		);	
	$rows[] = array(
				array('data' => 'Total', 'style'=>'font-weight: bold;'),
				array('data' => $ditsumtotalABC, 'style'=>'font-weight: bold;'),
				array('data' => $ditsumtotalsubmittedABC, 'style'=>'font-weight: bold;'),
				array('data' => $ditsumtotalpendingABC, 'style'=>'font-weight: bold;'),
		);			
  	//Industrial Tribunals end
	
		$rows[] = array(
				array('data' => '&nbsp;', 'colspan'=>'5'),
	);	

	// for Directorate of Employees Compensation
	$rows[] = array(
				array('data' => 'Employees Compensation', 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center;'),
				array('data' => 'Group A'),
				array('data' => $dectotal_cntA),
				//array('data' => $decsubmitted_cntA),
				array('data' => l($decsubmitted_cntA, 'submitted-list/DEC/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($decpending_cntA, 'pending-list/DEC/A', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $decpending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $dectotal_cntBC),
				//array('data' => $decsubmitted_cntBC),
				array('data' => l($decsubmitted_cntBC, 'submitted-list/DEC/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				array('data' => l($decpending_cntBC, 'pending-list/DEC/BC', array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
				//array('data' => $decpending_cntBC),
		);	
	$rows[] = array(
				array('data' => 'Total', 'style'=>'font-weight: bold;'),
				array('data' => $decsumtotalABC, 'style'=>'font-weight: bold;'),
				array('data' => $decsumtotalsubmittedABC, 'style'=>'font-weight: bold;'),
				array('data' => $decsumtotalpendingABC, 'style'=>'font-weight: bold;'),
		);			
  	//Directorate of Employees Compensation end
	
	
	
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
  return '<div class="formdvider viewlist">'.$output.'</div>';
}

function asset_diradmin_dashboard($form, &$form_state){
	global $base_root,$base_path,$user;
	$status = getUserProfileStatus($user->uid);
	if($status['one_time_pass_flag'] == '0') {
			drupal_goto('profileupdate');
			exit;
	}
	$form = array();
	$form['form_begin'] = array(
		'#type' => 'markup',
		'#markup' => 'Welcome to Assets Directorate Admin Dashboard',
	 );
	
	$form['table_data'] = array(
		'#type' => 'markup',
		'#markup' => getYearWiseAllindividualData(date('Y')),
	 ); 
	 
	 $form['footer_text'] = array(
		'#type' => 'markup',
		'#markup' => '** The figuers shown above are reflecting the data given by the Directorate\'s as on '.date('d-m-Y'),
	 ); 
	 	
	 return $form;
}

function asset_pendingall_dashboard($direc_code='', $emp_group=''){
	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');	
	
	$query = db_select('a_user_details','ud');
	$query->leftJoin('a_user_details_service', 'us', 'ud.uid = us.uid');
	$query->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = us.directorate_code'); 
	$query->fields('ud', array('uid','fname','status'));
	$query->fields('dm', array('id','directorate_name'));
	$query->fields('us', array('designation','directorate_code','district_code','service_status','emp_group','office_id'));
	$query->condition('ud.status',0,'=');
	$query->condition('us.service_status',1,'=');
	$query->condition('us.directorate_code',$direc_code,'=');
	if($emp_group == 'A' ){
	$query->condition('us.emp_group',$emp_group,'=');
	}else{
			$query->condition('us.emp_group',array('B','C'),'IN');
		}
	$query->orderBy('ud.fname','ASC');
	$result = $query->execute();
	$rsData = $result->fetchAll(); 

	$header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Sl No. </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	  array('data' => t('<b>Group </b>')),
	  array('data' => t('<b>Status </b>')),
	);
	 $i=0;
	  foreach($rsData as $data){
		//$i++;
		$pending = array();
		$pending = yearWiseIndividualUserDataSubmitted(array(date('Y')),$data->uid);
		
		if(empty($pending)){
			$i++;
			$status = "Not Submitted";
			$rows[] = array( 
						$i,	
						array('data' => t($data->fname)),
						array('data' => t($data->designation)), 	 
						array('data' => t($data->emp_group)), 
						array('data' => t($status)),
		);
	   }
	  }
	  
   $output .= theme('datatable', array(
							  'header' => $header,
							  'rows' => $rows,
							  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
							  'sticky' => true, 
							  'caption' => '<h3>All DoA Pending List Of ' . $data->directorate_name .' For Group '. $data->emp_group .' Employees</h3>' ,
							  'colgroups' => array(),
							  'empty' => t("No data found!") // The message to be displayed if table is empty
							)
						  ).theme('pager');	  	

  return '<div class="formdvider viewlist">'.$output.'</div>';		
	
}

function asset_submittedall_dashboard($direc_code='', $emp_group=''){
	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');	
		
	//$direc_code = getLoginUserDetailForAsset($user->uid);  
	
	  $query = db_select('a_asset_mst','am');
	  $query->leftJoin('users', 'u', 'u.uid = am.uid');  
	  $query->leftJoin('a_user_details', 'ud', 'ud.uid = am.uid');  
	  $query->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code');  
	  $query->leftJoin('a_user_details_service', 'us', 'am.uid = us.uid'); 
	  $query->fields('am', array('uid','declaration_yr','designation','directorate_code','status','created_date'));
	  $query->fields('u', array('name','access','created'));
	  $query->fields('ud', array('fname','status'));
	  $query->fields('dm', array('id','directorate_name'));
	  $query->fields('us', array('district_code','emp_group')); 
	  $query->condition('am.declaration_yr',date('Y'),'=');	
	  $query->condition('am.status',1,'=');
	  $query->condition('ud.status',0,'=');
	  $query->condition('us.directorate_code',$direc_code,'=');
	  if($emp_group == 'A' ){
		  $query->condition('us.emp_group',$emp_group,'=');
		  }else{
			$query->condition('us.emp_group',array('B','C'),'IN');
		}
	  $query->orderBy('ud.fname','ASC');
	  $result = $query->execute();
	  $rsData = $result->fetchAll();
	  
	  //print_r($rsData); exit;

	$header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Sl No. </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	  array('data' => t('<b>Group </b>')),
	  array('data' => t('<b>Status </b>')),
	  array('data' => t('<b>Asset Accepted On</b>'))
	);
	 $i=0;
	  foreach($rsData as $data){
		$i++;
		$submitted = array();
		$submitted = yearWiseIndividualUserDataSubmitted(array(date('Y')),$data->uid);
		
		//print_r($submitted); exit;
		//echo '---'.$data->fname; exit;
				
		if(!empty($submitted)){
			$status = "Submitted";
			$access = date('d-m-Y H:i:s',strtotime($data->created_date));
			
			$rows[] = array( 
						$i,	
						array('data' => t($data->fname)),
						array('data' => t($data->designation)), 	 
						array('data' => t($data->emp_group)), 
						array('data' => t($status)),
						array('data' => t($access)),
		);
	   }
	  }
	  
	  
   $output .= theme('datatable', array(
							  'header' => $header,
							  'rows' => $rows,
							  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
							  'sticky' => true,
							  'caption' => '<h3>All DoA Submited List Of ' . $data->directorate_name .' For Group '. $data->emp_group .' Employees</h3>' ,
							  'colgroups' => array(),
							  'empty' => t("No data found!") // The message to be displayed if table is empty
							)
						  ).theme('pager');	  	

  return '<div class="formdvider viewlist">'.$output.'</div>';		
	
}


function getYearWiseAllindividualData($current_year){ 
 global $user;
 drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');
 
 $direc_code = getLoginUserDetailForAsset($user->uid); 

  //print_r($direc_code); exit;
  
	$query = db_select('a_user_details','ud');
	$query->leftJoin('a_user_details_service', 'us', 'ud.uid = us.uid');
	$query->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = us.directorate_code'); 
	$query->leftJoin('a_office_master', 'aom', 'us.office_id = aom.office_id');
	$query->fields('ud', array('uid','fname','status'));
	$query->fields('dm', array('id','directorate_name'));
	$query->fields('us', array('designation','directorate_code','district_code','service_status','emp_group','office_id'));
	$query->condition('ud.status',0,'=');
	$query->condition('us.service_status',1,'=');
	$query->condition('us.directorate_code',$direc_code['directorate_code'],'=');
	$query->condition('aom.is_active','Y','=');
	//$query->condition('us.office_id',$fdata->office_id,'=');
	//$query->condition('us.emp_group',array('B','C'),'IN');
	$result = $query->execute();
	$rsData = $result->fetchAll(); 
 
  /*$query = db_select('a_asset_mst','am');
  $query->leftJoin('a_user_details', 'ud', 'ud.uid = am.uid');  
  $query->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code'); 
  $query->leftJoin('a_user_details_service', 'us', 'am.uid = us.uid');  
  //$query->leftJoin('a_office_master', 'ao', 'ao.directorate_code = am.directorate_code');  
  $query->fields('am', array('uid','declaration_yr','designation','directorate_code','status','created_date'));
  $query->fields('ud', array('fname','status'));
  $query->fields('dm', array('id','directorate_name'));
  $query->fields('us', array('designation','district_code','service_status','emp_group')); 
  //$query->fields('ao', array('office_id','office_name','district_code'));
  $query->condition('ud.status',0,'=');
  $query->condition('us.service_status',1,'=');
  $query->condition('am.directorate_code',$direc_code['directorate_code'],'=');
  $query->condition('am.declaration_yr',$current_year,'=');
  $result = $query->execute();
  $rsData = $result->fetchAll();*/
  
  
  
  //print_r($rsData); exit;
  
  $lcsumtotalABC = 0;
  $lcsumtotalsubmittedABC = 0;
  $lcsumtotalpendingABC = 0;
   
  $lctotal_cntA = 0;
  $lcsubmitted_cntA = 0;
  $lcpending_cntA = 0;
  $lctotal_cntBC = 0;
  $lcsubmitted_cntBC = 0;
  $lcpending_cntBC = 0; 
  
 
   
  foreach($rsData as $data){
	
	$rs = yearWiseIndividualUserData(array('0'=>$current_year),$data->uid);
	
	//print_r($rs); exit;
	  $directorate_name = $data->directorate_name;
	  $directorate_code = $data->directorate_code;	
				
  	  if($data->emp_group == 'A'){
				$lctotal_cntA++;
	  }
	  if($data->emp_group == 'A' AND $rs[0]->status == '1' ){
				$lcsubmitted_cntA++;
	  }
	  if($data->emp_group == 'B' OR  $data->emp_group == 'C'){
				$lctotal_cntBC++;
	  }
	  if(($data->emp_group == 'B' OR  $data->emp_group == 'C') AND $rs[0]->status == '1' ){
				$lcsubmitted_cntBC++;
	  }
   }
  
	$lcsumtotalABC = $lctotal_cntA + $lctotal_cntBC;
	$lcsumtotalsubmittedABC = $lcsubmitted_cntA + $lcsubmitted_cntBC;
	$lcsumtotalpendingABC = $lcsumtotalABC - $lcsumtotalsubmittedABC;
	
	$lcpending_cntA = $lctotal_cntA - $lcsubmitted_cntA;
	$lcpending_cntBC = $lctotal_cntBC - $lcsubmitted_cntBC;
 
 	$header = array();
	$rows = array();
	$header = array(
				array('data'=> 'Directorate'),
				array('data'=> 'Designation'),
				array('data'=> 'Total'),
				array('data'=> 'Submitted'),
				array('data'=> 'Pending'),
			);
            
            
     // for Labour Commissionerate
	$rows[] = array(
				array('data' => $directorate_name, 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center;'),
				array('data' => 'Group A'),
				array('data' => $lctotal_cntA),
				array('data' => $lcsubmitted_cntA),
				array('data' => $lcpending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $lctotal_cntBC),
				array('data' => $lcsubmitted_cntBC),
				array('data' => $lcpending_cntBC),
		);
		
	$rows[] = array(
				array('data' => 'Total', 'style'=>'font-weight: bold;'),
				array('data' => $lcsumtotalABC, 'style'=>'font-weight: bold;'),
				array('data' => $lcsumtotalsubmittedABC, 'style'=>'font-weight: bold;'),
				array('data' => $lcsumtotalpendingABC, 'style'=>'font-weight: bold;'),
		);						
  	//Labour Commissionerate end
	
		$rows[] = array(
				array('data' => '&nbsp;', 'colspan'=>'5'),
	);	
    
	
	/*------------------------------- FIELD OFFICE LIST FOR DASHBOARD BEGIN ---------------------------------------- */
    
	if($directorate_code == 'LC'){
	$or = db_or();
	
	$queryfield = db_select('a_office_master','ao');
	$queryfield->fields('ao', array('office_id','office_name','district_code','district_code','directorate_code'));
	$or->condition('ao.directorate_code','LC','=');
	$or->condition('ao.directorate_code','ALL','=');
	$queryfield->condition($or);
	$queryfield->condition('ao.is_active','Y','=');
	$resultField = $queryfield->execute();
	$rsDataField = $resultField->fetchAll();
	
	$totbc = 0;
	$cntof_b_total = 0;
	$cntof_b_pending = 0;
	$cntof_b_submitted = 0;
	$cntof_c_total = 0;
	$cntof_c_pending = 0;
	$cntof_c_submitted = 0;
	foreach($rsDataField as $fdata){
		
		if($fdata->directorate_code == 'ALL'){
			$directorate_code = 'LC';
		}else{
			$directorate_code = $fdata->directorate_code;
		}
		
		$fquery = db_select('a_user_details','ud');
		$fquery->leftJoin('a_user_details_service', 'us', 'ud.uid = us.uid');
		$fquery->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = us.directorate_code'); 
		$fquery->fields('ud', array('uid','fname','status'));
		$fquery->fields('dm', array('id','directorate_name'));
		$fquery->fields('us', array('designation','district_code','service_status','emp_group','office_id'));
		$fquery->condition('ud.status',0,'=');
		$fquery->condition('us.service_status',1,'=');
		$fquery->condition('us.directorate_code',$directorate_code,'=');
		$fquery->condition('us.office_id',$fdata->office_id,'=');
		$fquery->condition('us.emp_group',array('B','C'),'IN');
		$fresult = $fquery->execute();
		$frsData = $fresult->fetchAll();
		
		//print_r($frsData); exit;
		
		/*$fquery = db_select('a_asset_mst','am');
		$fquery->leftJoin('a_user_details', 'ud', 'ud.uid = am.uid');  
		$fquery->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code'); 
		$fquery->leftJoin('a_user_details_service', 'us', 'am.uid = us.uid');  
		//$query->leftJoin('a_office_master', 'ao', 'ao.directorate_code = am.directorate_code');  
		$fquery->fields('am', array('uid','declaration_yr','designation','directorate_code','status','created_date'));
		$fquery->fields('ud', array('fname','status'));
		$fquery->fields('dm', array('id','directorate_name'));
		$fquery->fields('us', array('designation','district_code','service_status','emp_group','office_id')); 
		//$query->fields('ao', array('office_id','office_name','district_code'));
		$fquery->condition('ud.status',0,'=');
		$fquery->condition('us.service_status',1,'=');
		$fquery->condition('am.directorate_code',$directorate_code,'=');
		$fquery->condition('am.declaration_yr',$current_year,'=');
		$fquery->condition('us.office_id',$fdata->office_id,'=');
		$fquery->condition('us.emp_group',array('B','C'),'IN');
		$fresult = $fquery->execute();
		$frsData = $fresult->fetchAll();*/
		
		
		$cntof_B_C_total = 0;
		$cntof_B_C_pending = 0;
		$cntof_B_C_submitted = 0;
		$emp_gr_B = 0;
		$emp_gr_B_pending = 0;
		$emp_gr_B_submitted = 0;
		$emp_gr_C = 0;
		$emp_gr_C_pending = 0;
		$emp_gr_C_submitted = 0;
		
		
		foreach($frsData as $k){
			if($fdata->office_id == $k->office_id){
				
				$rsData = yearWiseIndividualUserData(array('0'=>$current_year),$k->uid);
				
				/*$query = db_select('a_asset_mst','am');
				$query->fields('am', array('declaration_yr','designation','directorate_code','status','created_date'));
				$query->condition('am.declaration_yr',array($current_year),'IN');
				$query->condition('am.uid',$k->uid,'=');
				$result = $query->execute();
				$rsData = $result->fetchAll();*/
				
				
				if($k->emp_group == 'B'){
					$emp_gr_B++;
					$cntof_b_total++;
				}
				if($k->emp_group == 'B' AND $rsData[0]->status == 0){
					$emp_gr_B_pending++;
					$cntof_B_C_pending++;
					$cntof_b_pending++;
				}
				if($k->emp_group == 'B' AND $rsData[0]->status == 1){
					$emp_gr_B_submitted++;
					$cntof_B_C_submitted++;
					$cntof_b_submitted++;
				}
				if($k->emp_group == 'C'){
					$emp_gr_C++;
					$cntof_c_total++;
				}
				if($k->emp_group == 'C' AND $rsData[0]->status == 0){
					$emp_gr_C_pending++;
					$cntof_B_C_pending++;
					$cntof_c_pending++;
				}
				if($k->emp_group == 'C' AND $rsData[0]->status == 1){
					$emp_gr_C_submitted++;
					$cntof_B_C_submitted++;
					$cntof_c_submitted++;
				}
				
				$cntof_B_C_total++;
			}
		}
		$totbc = $totbc + $cntof_B_C_total;
	
			$rows[] = array(
						array('data' => $fdata->office_name, 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center; width:25%'),
						array('data' => 'Group B'),
						array('data' => $emp_gr_B),
						array('data' => $emp_gr_B_submitted),
						array('data' => l($emp_gr_B_pending, 'dir-pending-list/LC/B/'.$fdata->office_id, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
						//array('data' => $emp_gr_B_pending),
				);
				
			$rows[] = array(
						array('data' => 'Group C'),
						array('data' => $emp_gr_C),
						array('data' => $emp_gr_C_submitted),
						array('data' => l($emp_gr_C_pending, 'dir-pending-list/LC/C/'.$fdata->office_id, array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank')))),
						//array('data' => $emp_gr_C_pending),
				);
			$rows[] = array(
						array('data' => 'Total', 'style'=>'font-weight: bold;'),
						array('data' => $cntof_B_C_total, 'style'=>'font-weight: bold;'),
						array('data' => $cntof_B_C_submitted, 'style'=>'font-weight: bold;'),
						array('data' => $cntof_B_C_pending, 'style'=>'font-weight: bold;'),
				);		
			$rows[] = array(
						array('data' => '&nbsp;', 'colspan'=>'5'),
			);	
		
	
	}
	
	$rows[] = array(
				array('data' => 'Grand Total', 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center; width:25%'),
				array('data' => 'Total Group B'),
				array('data' => $cntof_b_total),
				array('data' => $cntof_b_submitted),
				array('data' => $cntof_b_pending),
		);
		
	$rows[] = array(
				array('data' => 'Total Group C'),
				array('data' => $cntof_c_total),
				array('data' => $cntof_c_submitted),
				array('data' => $cntof_c_pending),
		);
	$rows[] = array(
				array('data' => 'Total Group B & C', 'style'=>'font-weight: bold;'),
				array('data' => $totbc, 'style'=>'font-weight: bold;'),
				array('data' => $cntof_b_submitted + $cntof_c_submitted, 'style'=>'font-weight: bold;'),
				array('data' => $cntof_b_pending + $cntof_c_pending, 'style'=>'font-weight: bold;'),
		);		
	
	}
	
	
	
	
	
    
    /*------------------------------- FIELD OFFICE LIST FOR DASHBOARD END ---------------------------------------- */
	
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
  return '<div class="formdvider viewlist">'.$output.'</div>';       

}

function asset_dirpendingall_dashboard($direc_code='', $emp_group='', $office_id=''){
	
	//echo $direc_code .'----'. $emp_group .'----'.$office_id;  exit;
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');	
	
	$or = db_or();
	
	$queryfield = db_select('a_office_master','ao');
	$queryfield->fields('ao', array('office_id','office_name','district_code','district_code','directorate_code'));
	$or->condition('ao.directorate_code','LC','=');
	$or->condition('ao.directorate_code','ALL','=');
	$queryfield->condition($or);
	$queryfield->condition('ao.is_active','Y','=');
	$resultField = $queryfield->execute();
	$rsDataField = $resultField->fetchAll();
	
	$fquery = db_select('a_user_details','ud');
	$fquery->leftJoin('a_user_details_service', 'us', 'ud.uid = us.uid');
	$fquery->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = us.directorate_code'); 
	$fquery->fields('ud', array('uid','fname','status'));
	$fquery->fields('dm', array('id','directorate_name'));
	$fquery->fields('us', array('designation','district_code','service_status','emp_group','office_id'));
	$fquery->condition('ud.status',0,'=');
	$fquery->condition('us.service_status',1,'=');
	$fquery->condition('us.directorate_code',$direc_code,'=');
	$fquery->condition('us.office_id',$office_id,'=');
	$fquery->condition('us.emp_group',$emp_group,'=');
	$fresult = $fquery->execute();
	$frsData = $fresult->fetchAll();
	
	
	/*$query = db_select('a_user_details','ud');
	$query->leftJoin('a_user_details_service', 'us', 'ud.uid = us.uid');
	$query->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = us.directorate_code'); 
	$query->leftJoin('a_office_master', 'aom', 'us.office_id = aom.office_id');
	$query->fields('ud', array('uid','fname','status'));
	$query->fields('dm', array('id','directorate_name'));
	$query->fields('us', array('designation','directorate_code','district_code','service_status','emp_group','office_id'));
	$query->condition('ud.status',0,'=');
	$query->condition('us.service_status',1,'=');
	$query->condition('us.directorate_code',$direc_code,'=');
	$query->condition('aom.is_active','Y','=');
	if($emp_group == 'A' ){
	$query->condition('us.emp_group',$emp_group,'=');
	}else{
			$query->condition('us.emp_group',array('B','C'),'IN');
		}
	$result = $query->execute();
	$rsData = $result->fetchAll(); */

	$header = array();
	$rows   = array();
	$output = '';

	$header = array(  
	  array('data' => t('<b>Sl No. </b>')),	
	  array('data' => t('<b>Officers Name  </b>')),
	  array('data' => t('<b>Officers Designation </b>')),
	  array('data' => t('<b>Group </b>')),
	  array('data' => t('<b>Status </b>')),
	);
	 $i=0;
	  foreach($frsData as $data){
		$i++;
		$pending = array();
		$pending = yearWiseIndividualUserDataSubmitted(array(date('Y')),$data->uid);
		
		if(empty($pending)){
			$status = "Not Submitted";
			$rows[] = array( 
						$i,	
						array('data' => t($data->fname)),
						array('data' => t($data->designation)), 	 
						array('data' => t($data->emp_group)), 
						array('data' => t($status)),
		);
	   }
	  }
	  
	  
   $output .= theme('datatable', array(
							  'header' => $header,
							  'rows' => $rows,
							  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
							  'sticky' => true,
							  'caption' => '<h3>All DoA Pending List Of</h3>' .$data->directorate_name .'<h3>For Group</h3>'. $data->emp_group .'<h3>Employees</h3>' ,
							  'colgroups' => array(),
							  'empty' => t("No data found!") // The message to be displayed if table is empty
							)
						  ).theme('pager');	  	

  return '<div class="formdvider viewlist">'.$output.'</div>';		
}