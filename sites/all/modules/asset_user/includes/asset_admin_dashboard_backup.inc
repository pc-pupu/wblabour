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
	
	$form['table_data'] = array(
		'#type' => 'markup',
		'#markup' => getYearWiseAllDirectorateData(date('Y')),
	 ); 
	 
	 $form['footer_text'] = array(
		'#type' => 'markup',
		'#markup' => '** The figures shown above are reflecting the data given by the Department / Directorates as on '.date('d-m-Y'),
	 ); 
	 	
	 return $form;
}

function getYearWiseAllDirectorateData($current_year){
	
	drupal_add_css(drupal_get_path('module', 'asset_user') . '/def.css');	
	
   
  $query = db_select('a_asset_mst','am');
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
  $rsData = $result->fetchAll();
  
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
	   
	   /* --------------------------------------------- LD BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'LD' AND $data->emp_group == 'A'){
				$ldtotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'LD' AND $data->emp_group == 'A' AND $data->status == '1' ){
				$ldsubmitted_cntA++;
	  }
	   if(trim($data->directorate_code) == 'LD' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$ldpending_cntA++;
	  }
	   if(trim($data->directorate_code) == 'LD' AND $data->emp_group != 'A'){
				$ldtotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'LD' AND $data->emp_group != 'A' AND $data->status == '1' ){
				$ldsubmitted_cntBC++;
	  }
	   if(trim($data->directorate_code) == 'LD' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$ldpending_cntBC++;
	  }
	  
    /* --------------------------------------------- LD END ---------------------------- */	
		
		
	  /* --------------------------------------------- LC BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'LC' AND $data->emp_group == 'A'){
				$lctotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'LC' AND $data->emp_group == 'A' AND $data->status == '1' ){
				$lcsubmitted_cntA++;
	  }
	   if(trim($data->directorate_code) == 'LC' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$lcpending_cntA++;
	  }
	   if(trim($data->directorate_code) == 'LC' AND $data->emp_group != 'A'){
				$lctotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'LC' AND $data->emp_group != 'A' AND $data->status == '1' ){
				$lcsubmitted_cntBC++;
	  }
	   if(trim($data->directorate_code) == 'LC' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$lcpending_cntBC++;
	  }
    /* --------------------------------------------- LC END ---------------------------- */	
	
    /* --------------------------------------------- EMP BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'DE' AND $data->emp_group == 'A'){
				$detotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'DE' AND $data->emp_group == 'A' AND $data->status == '1' ){
				$desubmitted_cntA++;
	  }
	   if(trim($data->directorate_code) == 'DE' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$depending_cntA++;
	  }
	   if(trim($data->directorate_code) == 'DE' AND $data->emp_group != 'A'){
				$detotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'DE' AND $data->emp_group != 'A' AND $data->status == '1' ){
				$desubmitted_cntBC++;
	  }
	   if(trim($data->directorate_code) == 'DE' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$depending_cntBC++;
	  }
	
	 /* --------------------------------------------- EMP END ---------------------------- */	
	
   /* --------------------------------------------- ESI BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'ESI' AND $data->emp_group == 'A'){
				$esitotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'ESI' AND $data->emp_group == 'A' AND $data->status == '1' ){
				$esisubmitted_cntA++;
	  }
	   if(trim($data->directorate_code) == 'ESI' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$esipending_cntA++;
	  }
	   if(trim($data->directorate_code) == 'ESI' AND $data->emp_group != 'A'){
				$esitotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'ESI' AND $data->emp_group != 'A' AND $data->status == '1' ){
				$esisubmitted_cntBC++;
	  }
	   if(trim($data->directorate_code) == 'ESI' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$esipending_cntBC++;
	  }
	
	 /* --------------------------------------------- ESI END ---------------------------- */	
	
	 /* --------------------------------------------- Factories BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'DF' AND $data->emp_group == 'A'){
				$factoriestotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'DF' AND $data->emp_group == 'A' AND $data->status == '1' ){
				$factoriessubmitted_cntA++;
	  }
	   if(trim($data->directorate_code) == 'DF' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$factoriespending_cntA++;
	  }
	   if(trim($data->directorate_code) == 'DF' AND $data->emp_group != 'A'){
				$factoriestotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'DF' AND $data->emp_group != 'A' AND $data->status == '1' ){
				$factoriessubmitted_cntBC++;
	  }
	   if(trim($data->directorate_code) == 'DF' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$factoriespending_cntBC++;
	  }
	
	 /* --------------------------------------------- Factories END ---------------------------- */	
	 
    /* --------------------------------------------- Boilers BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'DB' AND $data->emp_group == 'A'){
				$dbtotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'DB' AND $data->emp_group == 'A' AND $data->status == '1' ){
				$dbsubmitted_cntA++;
	  }
	   if(trim($data->directorate_code) == 'DB' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$dbpending_cntA++;
	  }
	   if(trim($data->directorate_code) == 'DB' AND $data->emp_group != 'A'){
				$dbtotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'DB' AND $data->emp_group != 'A' AND $data->status == '1' ){
				$dbsubmitted_cntBC++;
	  }
	   if(trim($data->directorate_code) == 'DB' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$dbpending_cntBC++;
	  }
	
	 /* --------------------------------------------- Boilers END ---------------------------- */	
	
	
	 /* --------------------------------------------- Industrial Tribunal BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'DIT' AND $data->emp_group == 'A'){
				$dittotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'DIT' AND $data->emp_group == 'A' AND $data->status == '1' ){
				$ditsubmitted_cntA++;
	  }
	   if(trim($data->directorate_code) == 'DIT' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$ditpending_cntA++;
	  }
	   if(trim($data->directorate_code) == 'DIT' AND $data->emp_group != 'A'){
				$dittotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'DIT' AND $data->emp_group != 'A' AND $data->status == '1' ){
				$ditsubmitted_cntBC++;
	  }
	   if(trim($data->directorate_code) == 'DIT' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$ditpending_cntBC++;
	  }
	
	 /* --------------------------------------------- Industrial Tribunal END ---------------------------- */	
	
	 /* --------------------------------------------- Directorate of Employees Compensation BEGIN ---------------------------- */			
	  if(trim($data->directorate_code) == 'DEC' AND $data->emp_group == 'A'){
				$dectotal_cntA++;
	  }
	  if(trim($data->directorate_code) == 'DEC' AND $data->emp_group == 'A' AND $data->status == '1' ){
				$decsubmitted_cntA++;
	  }
	   if(trim($data->directorate_code) == 'DEC' AND $data->emp_group == 'A' AND $data->status == '0' ){
				$decpending_cntA++;
	  }
	   if(trim($data->directorate_code) == 'DEC' AND $data->emp_group != 'A'){
				$dectotal_cntBC++;
	  }
	  if(trim($data->directorate_code) == 'DEC' AND $data->emp_group != 'A' AND $data->status == '1' ){
				$decsubmitted_cntBC++;
	  }
	   if(trim($data->directorate_code) == 'DEC' AND $data->emp_group != 'A' AND $data->status == '0' ){
				$decpending_cntBC++;
	  }
	
	 /* --------------------------------------------- Directorate of Employees Compensation END ---------------------------- */	
   }
   
      $ldsumtotalABC = $ldtotal_cntA + $ldtotal_cntBC;
 	  $ldsumtotalsubmittedABC = $ldsubmitted_cntA + $ldsubmitted_cntBC;
 	  $ldsumtotalpendingABC = $ldpending_cntA + $ldpending_cntBC;
	  
	  $lcsumtotalABC = $lctotal_cntA + $lctotal_cntBC;
 	  $lcsumtotalsubmittedABC = $lcsubmitted_cntA + $lcsubmitted_cntBC;
 	  $lcsumtotalpendingABC = $lcpending_cntA + $lcpending_cntBC;
	  
	  $desumtotalABC = $detotal_cntA + $detotal_cntBC;
 	  $desumtotalsubmittedABC = $desubmitted_cntA + $desubmitted_cntBC;
 	  $desumtotalpendingABC = $depending_cntA + $depending_cntBC;
	  
	  $esisumtotalABC = $esitotal_cntA + $esitotal_cntBC;
 	  $esisumtotalsubmittedABC = $esisubmitted_cntA + $esisubmitted_cntBC;
 	  $esisumtotalpendingABC = $esipending_cntA + $esipending_cntBC;
	  
	  $factoriessumtotalABC = $factoriestotal_cntA + $factoriestotal_cntBC;
 	  $factoriessumtotalsubmittedABC = $factoriessubmitted_cntA + $factoriessubmitted_cntBC;
 	  $factoriessumtotalpendingABC = $factoriespending_cntA + $factoriespending_cntBC;
	  
	  $dbsumtotalABC = $dbtotal_cntA + $dbtotal_cntBC;
 	  $dbsumtotalsubmittedABC = $dbsubmitted_cntA + $dbsubmitted_cntBC;
 	  $dbsumtotalpendingABC = $dbpending_cntA + $dbpending_cntBC;
	  
	  $ditsumtotalABC = $dittotal_cntA + $dittotal_cntBC;
 	  $ditsumtotalsubmittedABC = $ditsubmitted_cntA + $ditsubmitted_cntBC;
 	  $ditsumtotalpendingABC = $ditpending_cntA + $ditpending_cntBC;
	  
	  $decsumtotalABC = $dectotal_cntA + $dectotal_cntBC;
 	  $decsumtotalsubmittedABC = $decsubmitted_cntA + $decsubmitted_cntBC;
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
				array('data' => $ldsubmitted_cntA),
				array('data' => $ldpending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $ldtotal_cntBC),
				array('data' => $ldsubmitted_cntBC),
				array('data' => $ldpending_cntBC),
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
		
	// for Directorate of Employment
	$rows[] = array(
				array('data' => 'Directorate of Employment', 'rowspan'=>'3', 'align'=>'center', 'style'=>'text-align: center;'),
				array('data' => 'Group A'),
				array('data' => $detotal_cntA),
				array('data' => $desubmitted_cntA),
				array('data' => $depending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $detotal_cntBC),
				array('data' => $desubmitted_cntBC),
				array('data' => $depending_cntBC),
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
				array('data' => $esisubmitted_cntA),
				array('data' => $esipending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $esitotal_cntBC),
				array('data' => $esisubmitted_cntBC),
				array('data' => $esipending_cntBC),
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
				array('data' => $factoriessubmitted_cntA),
				array('data' => $factoriespending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $factoriestotal_cntBC),
				array('data' => $factoriessubmitted_cntBC),
				array('data' => $factoriespending_cntBC),
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
				array('data' => $dbsubmitted_cntA),
				array('data' => $dbpending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $dbtotal_cntBC),
				array('data' => $dbsubmitted_cntBC),
				array('data' => $dbpending_cntBC),
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
				array('data' => $ditsubmitted_cntA),
				array('data' => $ditpending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $dittotal_cntBC),
				array('data' => $ditsubmitted_cntBC),
				array('data' => $ditpending_cntBC),
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
				array('data' => $decsubmitted_cntA),
				array('data' => $decpending_cntA),
		);
	$rows[] = array(
				array('data' => 'Group B & C'),
				array('data' => $dectotal_cntBC),
				array('data' => $decsubmitted_cntBC),
				array('data' => $decpending_cntBC),
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