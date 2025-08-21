<?php 
function apply_online_form($form, &$form_state, $arg) {
	$user_service_info_id = encryption_decryption_wblabour('decrypt', $arg);
	
	$estservice_list_query = db_select('ld_user_service_info', 'us');
	$estservice_list_query->leftJoin('ld_service_master', 's', 's.id=us.service_id');
	$estservice_list_query->leftJoin('ld_establishment_details','est','est.est_id=us.est_id');
	//$estservice_list_query->leftJoin('ar_authority','a','a.authority_code=us.directorate_code');
	
	$estservice_list_query->leftJoin('all_india_pin_code','alpc','alpc.id=est.postoffice::integer');
	$estservice_list_query->leftJoin('users', 'u', 'u.uid=us.uid');
	$estservice_list_query->leftJoin('ld_users_details', 'lud', 'lud.uid=us.uid');
	$estservice_list_query->fields('u', array( 'name'));
	$estservice_list_query->fields('lud', array('ld_pass','fname','mname','lname','gender','dob','mobile','email','religion','aadharno','voter','pancard','pincode','state','district','subdivision','areatype','block','panchayat','policestation','postoffice','address','country','identity_cardtype','identity_cardno' ));
	
	$estservice_list_query->fields('s',array('act_id','service_name','directorate_name','directorate_code','service_type'));
	$estservice_list_query->fields('us',array('uid','service_id','application_time','act_id','est_id','directorate_code','status'));
	$estservice_list_query->fields('est',array('est_id','e_clinid','est_name','ownership_type','ownership_typesub','ownership_typesub1','ownership_typesub2','ownership_otext','govtpvt_otext','identity_cardtype','identity_cardno','industry_category','pincode','state','district','subdivision','areatype','block','panchayat','policestation','postoffice','address','gstno'));
	//$estservice_list_query->fields('a',array('authority_name','authority_code'));
	$estservice_list_query->fields('alpc',array('po_name'));
	$estservice_list_query->addField('s', 'id', 'ld_service_master_id');
	$estservice_list_query->addField('us', 'id', 'user_service_info_id');
	//$estservice_list_query->addField('a', 'id', 'ar_authority_id');
	
	$estservice_list_query->condition('us.id',$user_service_info_id,'=');
	$estservice_list_query_result = $estservice_list_query->execute();
	$estservice_list_query_result_data = $estservice_list_query_result->fetchAll();
	/*echo '<pre>';
	print_r($estservice_list_query_result_data); die;
	echo '--->mm'.$estservice_list_query_result_data[0]->directorate_code; 
	die;
	exit;*/
	
	//Applicant part
	$state_name = stateNameBypostStateID(trim($estservice_list_query_result_data[0]->state));
	$district_name = districtNameByDistrictID(trim($estservice_list_query_result_data[0]->district));
	$subdivision_name = subdivisionNameBySubdivisionCode(trim($estservice_list_query_result_data[0]->subdivision));
	$block_name = blockNameByBlockCode(trim($estservice_list_query_result_data[0]->block));
	$panchayat_name = villageNameByVillageCode(trim($estservice_list_query_result_data[0]->panchayat)); //exit;
	$police_station_name = policeStationNameByPoliceStationCode(trim($estservice_list_query_result_data[0]->policestation));
	$post_office_name = postOfficeNameBypostOfficeID(trim($estservice_list_query_result_data[0]->postoffice));
	$country_name = countryNameBypostCountryID(trim($estservice_list_query_result_data[0]->country));
	
	//Establishment Part
	$est_state_name = stateNameBypostStateID(trim($estservice_list_query_result_data[0]->est_state));
	$est_district_name = districtNameByDistrictID(trim($estservice_list_query_result_data[0]->est_district));
	$est_subdivision_name = subdivisionNameBySubdivisionCode(trim($estservice_list_query_result_data[0]->est_subdivision));
	$est_block_name = blockNameByBlockCode(trim($estservice_list_query_result_data[0]->est_block));
	$est_panchayat_name = villageNameByVillageCode(trim($estservice_list_query_result_data[0]->est_panchayat));
	$est_policestation_name = policeStationNameByPoliceStationCode(trim($estservice_list_query_result_data[0]->est_policestation));
	
	
	
	//echo $est_state; exit;
	
	$curl_post_data = 	array(
			"source" => "WBLD",
			
			"uname" => trim($estservice_list_query_result_data[0]->name),
			"ld_pass" => trim($estservice_list_query_result_data[0]->ld_pass),
			"fname" => trim($estservice_list_query_result_data[0]->fname),
			"mname" => trim($estservice_list_query_result_data[0]->mname),
			"lname" => trim($estservice_list_query_result_data[0]->lname),
			"gender" => trim($estservice_list_query_result_data[0]->gender),
			//"dob" => "1985-05-06",
			"mobile" => trim($estservice_list_query_result_data[0]->mobile),
			"email" => trim($estservice_list_query_result_data[0]->email),
			"religion" => trim($estservice_list_query_result_data[0]->religion),
			"aadharno" => trim($estservice_list_query_result_data[0]->aadharno),
			"voter" => trim($estservice_list_query_result_data[0]->voter),
			"pancard" => trim($estservice_list_query_result_data[0]->pancard),
			"pincode" => trim($estservice_list_query_result_data[0]->pincode),
			"state" => trim($estservice_list_query_result_data[0]->state),
			"state_name" => trim($state_name),
			"district" => trim($estservice_list_query_result_data[0]->district),
			"district_name" => trim($district_name),  // added for district name
			"subdivision" => trim($estservice_list_query_result_data[0]->subdivision),
			"subdivision_name" => trim($subdivision_name),
			"areatype" => trim($estservice_list_query_result_data[0]->areatype),
			"block" => trim($estservice_list_query_result_data[0]->block),
			"block_name" => trim($block_name),
			"panchayat" => trim($estservice_list_query_result_data[0]->panchayat),
			"panchayat_name" => trim($panchayat_name),
			"policestation" => trim($estservice_list_query_result_data[0]->policestation),
			"police_station_name" => trim($police_station_name),
			"postoffice" => trim($estservice_list_query_result_data[0]->postoffice),
			"post_office_name" => trim($post_office_name),
			"address" => trim($estservice_list_query_result_data[0]->address),
			"country" => trim($estservice_list_query_result_data[0]->country),
			"country_name" => trim($country_name),
			"identity_cardtype" => trim($estservice_list_query_result_data[0]->identity_cardtype),
			"identity_cardno" => trim($estservice_list_query_result_data[0]->identity_cardno),
			
			"industry_category" => trim($estservice_list_query_result_data[0]->industry_category),
			//"gender_of_owner_industry" => trim($estservice_list_query_result_data[0]->gender_of_owner_industry),
			
			"act_id" => trim($estservice_list_query_result_data[0]->act_id),
			"service_name" => trim($estservice_list_query_result_data[0]->service_name),
			"directorate_name" => trim($estservice_list_query_result_data[0]->directorate_name),
			"service_type" => trim($estservice_list_query_result_data[0]->service_type),
			"uid" => trim($estservice_list_query_result_data[0]->uid),
			"service_id" => trim($estservice_list_query_result_data[0]->service_id),
			"application_time" => trim($estservice_list_query_result_data[0]->application_time),
			"us_act_id" => trim($estservice_list_query_result_data[0]->us_act_id),
			"est_id" => trim($estservice_list_query_result_data[0]->est_id),
			"us_directorate_code" => trim($estservice_list_query_result_data[0]->us_directorate_code),
			
			"est_est_id" => trim($estservice_list_query_result_data[0]->est_est_id),
			"e_clinid" => trim($estservice_list_query_result_data[0]->e_clinid),
			"est_name" => trim($estservice_list_query_result_data[0]->est_name),
			"ownership_type" => trim($estservice_list_query_result_data[0]->ownership_type),
			"ownership_typesub" => trim($estservice_list_query_result_data[0]->ownership_typesub),
			"ownership_typesub1" => trim($estservice_list_query_result_data[0]->ownership_typesub1),
			"ownership_typesub2" => trim($estservice_list_query_result_data[0]->ownership_typesub2),
			"ownership_otext" => trim($estservice_list_query_result_data[0]->ownership_otext),
			"govtpvt_otext" => trim($estservice_list_query_result_data[0]->govtpvt_otext),
			"est_identity_cardtype" => trim($estservice_list_query_result_data[0]->est_identity_cardtype),
			"est_identity_cardno" => trim($estservice_list_query_result_data[0]->est_identity_cardno),
			"est_pincode" => trim($estservice_list_query_result_data[0]->est_pincode),
			"est_state" => trim($estservice_list_query_result_data[0]->est_state),
			"est_state_name" => trim($estservice_list_query_result_data[0]->est_state),
			"est_district" => trim($estservice_list_query_result_data[0]->est_district),
			"est_district_name" => trim($est_district_name),
			"est_subdivision" => trim($estservice_list_query_result_data[0]->est_subdivision),
			"est_subdivision_name" => trim($est_subdivision_name),
			"est_areatype" => trim($estservice_list_query_result_data[0]->est_areatype),
			"est_block" => trim($estservice_list_query_result_data[0]->est_block),
			"est_block_name" => trim($est_block_name),
			"est_panchayat" => trim($estservice_list_query_result_data[0]->est_panchayat),
			"est_panchayat_name" => trim($est_panchayat_name),
			"est_policestation" => trim($estservice_list_query_result_data[0]->est_policestation),
			"est_policestation_name" => trim($est_policestation_name),
			"est_postoffice" => trim($estservice_list_query_result_data[0]->est_postoffice),
			"est_po_name" => trim($estservice_list_query_result_data[0]->po_name), 
			"est_address" => trim($estservice_list_query_result_data[0]->est_address),
			"ld_service_master_id" => trim($estservice_list_query_result_data[0]->ld_service_master_id),
			"user_service_info_id" => trim($estservice_list_query_result_data[0]->user_service_info_id),
			"gstno" => trim($estservice_list_query_result_data[0]->gstno),
		);

//echo "<pre>";print_r($curl_post_data);exit;

//echo json_encode( $curl_post_data ); exit;
	
	if(trim($estservice_list_query_result_data[0]->directorate_code)=='B'){
		//echo 'hii'; exit;
		$service_url 	= 	"https://wbboilers.gov.in/ld_swo_new/eservices/service_reg";
		$ch 			= 	curl_init();
		$headers		=	array();
		$headers[]		=	'Accept: application/json';
		$headers[]		=	'Content-Type: application/json';
		$headers[] 		= 	'charset=utf-8';
		curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
		curl_setopt($ch, CURLOPT_URL, $service_url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0); 
		curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 0);
		curl_setopt($ch, CURLOPT_SSLVERSION , 6);
		curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode( $curl_post_data ) );
		curl_setopt($ch, CURLOPT_POST, true);
		$results		=	curl_exec($ch);
		$errors			=	curl_error($ch);
		curl_close($ch);
		$x				=	json_encode( $results );
		$tmp 			= 	json_decode(json_decode(trim($x)), TRUE);
		//echo "abc"; print_r($errors); exit;  
		//print_r($tmp); exit;
		
		try{
		
		//$tmp = print_r(json_decode($results)); exit;
		//echo 'begin7---'; exit;
		//print_r(json_decode($tmp));
		//echo $tmp['code']."--end".$tmp['content']['service_id'];
		//die;
		
		if(($estservice_list_query_result_data[0]->service_id == $tmp['content']['service_id']) && ($estservice_list_query_result_data[0]->user_service_info_id == $tmp['content']['ld_service_unique_id'])){
			if($tmp['content']['service_id'] == 32) 
			{
				if(trim($estservice_list_query_result_data[0]->status) == 2) {
					$param_arr = array (
						'name' => $estservice_list_query_result_data[0]->name,
						'ld_pass' => $estservice_list_query_result_data[0]->ld_pass,
						'service_id' => $estservice_list_query_result_data[0]->service_id,
						'user_service_info_id' => $estservice_list_query_result_data[0]->user_service_info_id,
						'appln_status' => $estservice_list_query_result_data[0]->status
					);
					$param = encrypt_swo_ld($param_arr);
					//$param = base64_encode(serialize($param_arr));
					drupal_goto('https://wbboilers.gov.in/ld-application-payment-redirect/'.$param);
				}			
				else if(trim($estservice_list_query_result_data[0]->status) == 1 || trim($estservice_list_query_result_data[0]->status) == 3 || trim($estservice_list_query_result_data[0]->status) == 4 || trim($estservice_list_query_result_data[0]->status) == 5 || trim($estservice_list_query_result_data[0]->status) == 6 || trim($estservice_list_query_result_data[0]->status) == 7 || trim($estservice_list_query_result_data[0]->status) == 8) {
					$param_arr = array (
						'name' => $estservice_list_query_result_data[0]->name,
						'ld_pass' => $estservice_list_query_result_data[0]->ld_pass,
						'service_id' => $estservice_list_query_result_data[0]->service_id,
						'user_service_info_id' => $estservice_list_query_result_data[0]->user_service_info_id,
						'appln_status' => $estservice_list_query_result_data[0]->status
					);
					//print_r($param_arr); die;
					$param = encrypt_swo_ld($param_arr);
					//$param = base64_encode(serialize($param_arr));
					
					drupal_goto('https://wbboilers.gov.in/ld-application-redirect/'.$param);
				}
				else {
					$param_arr = array (
						'name' => $estservice_list_query_result_data[0]->name,
						'ld_pass' => $estservice_list_query_result_data[0]->ld_pass,
						'service_id' => $estservice_list_query_result_data[0]->service_id,
						'user_service_info_id' => $estservice_list_query_result_data[0]->user_service_info_id,
						'appln_status' => $estservice_list_query_result_data[0]->status
					);
					$param = encrypt_swo_ld($param_arr);
					//$param = base64_encode(serialize($param_arr));
					drupal_goto('https://wbboilers.gov.in/ld-application-redirect/'.$param);
				}
			}

			if($tmp['content']['service_id'] == 33) 
			{
				if(trim($estservice_list_query_result_data[0]->status) == 2) {
					$param_arr = array (
						'name' => $estservice_list_query_result_data[0]->name,
						'ld_pass' => $estservice_list_query_result_data[0]->ld_pass,
						'service_id' => $estservice_list_query_result_data[0]->service_id,
						'user_service_info_id' => $estservice_list_query_result_data[0]->user_service_info_id,
						'appln_status' => $estservice_list_query_result_data[0]->status
					);
					$param = encrypt_swo_ld($param_arr);
					//$param = base64_encode(serialize($param_arr));
					drupal_goto('https://wbboilers.gov.in/ld-application-payment-redirect/'.$param);
				}
				else{
					$param_arr = array (
						'name' => $estservice_list_query_result_data[0]->name,
						'ld_pass' => $estservice_list_query_result_data[0]->ld_pass,
						'service_id' => $estservice_list_query_result_data[0]->service_id,
						'user_service_info_id' => $estservice_list_query_result_data[0]->user_service_info_id,
						'appln_status' => $estservice_list_query_result_data[0]->status
					);
					$param = encrypt_swo_ld($param_arr);
					//$param = base64_encode(serialize($param_arr));
					drupal_goto('https://wbboilers.gov.in/ld-application-redirect/'.$param);
				}
			}
	}
		//$boiler_uid = $tmp['content']['uid'];
		//drupal_goto('https://wbboilers.gov.in/ld-login/'.$boiler_uid);
		//exit;
		
		}catch(exception $e){
			drupal_set_message ($error);
		}
	}
	
	if(trim($estservice_list_query_result_data[0]->directorate_code)=='LC'){
		$service_url 	= 	"https://wblc.gov.in/labourdept/eservices/userNewRegistration";
		$ch 			= 	curl_init();
		$headers		=	array();
		$headers[]		=	'Accept: application/json';
		$headers[]		=	'Content-Type: application/json';
		$headers[] 		= 	'charset=utf-8';
		curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
		curl_setopt($ch, CURLOPT_URL, $service_url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0); 
		curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 0);
		curl_setopt($ch, CURLOPT_SSLVERSION , 6);
		curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode( $curl_post_data ) );
		curl_setopt($ch, CURLOPT_POST, true);
		$results		=	curl_exec($ch);
		$errors			=	curl_error($ch);
		curl_close($ch);
		$x				=	json_encode( $results );
		$tmp 			= 	json_decode(json_decode(trim($x)), TRUE);
		
		
		//print_r(json_encode( $curl_post_data )); exit;
		//echo 'abcd---';
		//$tmp = json_decode($results); exit;
		/*print_r($curl_post_data);
		echo 'tttt---';
		print_r($tmp);
		echo $tmp['ld_service_unique_id']."----kkppp--->>>";
		die;*/

		if(($estservice_list_query_result_data[0]->service_id == $tmp['service_id']) && ($estservice_list_query_result_data[0]->user_service_info_id == $tmp['ld_service_unique_id'])){

			$param_arr = array (
						'name' => $estservice_list_query_result_data[0]->name,
						'ld_pass' => $estservice_list_query_result_data[0]->ld_pass,
						'service_id' => $estservice_list_query_result_data[0]->service_id,
						'user_service_info_id' => $estservice_list_query_result_data[0]->user_service_info_id,
						'est_id' => $estservice_list_query_result_data[0]->est_id,
						'appln_status' => $estservice_list_query_result_data[0]->status
					);
					$param = encrypt_swo_ld($param_arr); 

			//drupal_goto('https://wblc.gov.in/user-authenticate-ld/'.$param);
			drupal_goto('https://wblc.gov.in/user-authenticate-ld/'.encryption_decryption_wblabour('encrypt', $estservice_list_query_result_data[0]->name).'/'.encryption_decryption_wblabour('encrypt',$estservice_list_query_result_data[0]->ld_pass).'/'.encryption_decryption_wblabour('encrypt',$estservice_list_query_result_data[0]->service_id).'/'.encryption_decryption_wblabour('encrypt',$estservice_list_query_result_data[0]->user_service_info_id).'/'.encryption_decryption_wblabour('encrypt',$estservice_list_query_result_data[0]->est_id));
		}else{
			//print_r($tmp); exit;
			drupal_set_message('Something is wrong. service_id and ld_service_unique_id not return from LC.');
		}
		//$boiler_uid = $tmp['content']['uid'];
		//drupal_goto('https://wbboilers.gov.in/ld-login/'.$boiler_uid);
		//exit;
	}
	
	
	
	if(trim($estservice_list_query_result_data[0]->directorate_code)=='F'){
		$service_url 	= 	"https://wbfactories.gov.in/webservices/REST/LD/apply";
		$ch 			= 	curl_init();
		$headers		=	array();
		$headers[]		=	'Accept: application/json';
		$headers[]		=	'Content-Type: application/json';
		$headers[] 		= 	'charset=utf-8';
		curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
		curl_setopt($ch, CURLOPT_URL, $service_url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0); 
		curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 0);
		curl_setopt($ch, CURLOPT_SSLVERSION , 6);
		curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode( $curl_post_data ) );
		curl_setopt($ch, CURLOPT_POST, true);
		$results		=	curl_exec($ch);
		$errors			=	curl_error($ch);
		curl_close($ch);
		//print_r($errors); exit;
		//$x				=	json_encode( $results );
		//$tmp 			= 	json_decode(json_decode(trim($x)), TRUE);
		
		
		$tmp = json_decode($results);
		//echo 'begin7---'; 
		//print_r($tmp);
		//echo $tmp['code']."--end".$tmp['content']['service_id'];
		//die;

		if(($estservice_list_query_result_data[0]->service_id == $tmp->content->service_id) && ($estservice_list_query_result_data[0]->user_service_info_id == $tmp->content->user_service_info_id)){

			/*$param_arr = array (
						'name' => $estservice_list_query_result_data[0]->name,
						'ld_pass' => $estservice_list_query_result_data[0]->ld_pass,
						'service_id' => $estservice_list_query_result_data[0]->service_id,
						'user_service_info_id' => $estservice_list_query_result_data[0]->user_service_info_id,
						'est_id' => $estservice_list_query_result_data[0]->est_id,
						'appln_status' => $estservice_list_query_result_data[0]->status
					);
					$param = encrypt_swo_ld($param_arr); */
					
			drupal_goto($tmp->content->redirect_link);		
					

			//drupal_goto('https://wblc.gov.in/user-authenticate-ld/'.$param);
			/*drupal_goto('https://wblc.gov.in/user-authenticate-ld/'.encryption_decryption_wblabour('encrypt', $estservice_list_query_result_data[0]->name).'/'.encryption_decryption_wblabour('encrypt',$estservice_list_query_result_data[0]->ld_pass).'/'.encryption_decryption_wblabour('encrypt',$estservice_list_query_result_data[0]->service_id).'/'.encryption_decryption_wblabour('encrypt',$estservice_list_query_result_data[0]->user_service_info_id).'/'.encryption_decryption_wblabour('encrypt',$estservice_list_query_result_data[0]->est_id));*/
		}else{
			drupal_set_message('Response error Code: '.$tmp->code.' <br> Response error Message: '.$tmp->content->error);
		}
		//$boiler_uid = $tmp['content']['uid'];
		//drupal_goto('https://wbboilers.gov.in/ld-login/'.$boiler_uid);
		//exit;
	}
	
	
	
	
}
function establishment_list_form($form, &$form_state) {
   global $user;	
   ctools_include('modal');
   ctools_modal_add_js();
	
   $form['form_begin'] = array( 
   '#prefix' => '<div class="page-heading mb-4"><h3>My Establishments</h3>'.l('<i class="fa fa-building"></i> Add Establishment', 'add-establishment', array('html'=>TRUE,'attributes'=>array('class' => array('btn add-establishment btn-sm pull-right mb-3')))).'</div>
  				 <div><div class="card col-lg-12 px-0 mb-4"><div class="card-body">
				 <div class="panel-group" id="accordion" role="tablist" aria-multiselectable="true">',
   '#suffix' => '' ,
 );
 
  $elist = establishment_info($user->uid);
  //print_r($elist); exit;
  if(!empty($elist)){
  for($i=0;$i<sizeof($elist);$i++){
	  
	  if($i == 0){ 
		$bluebarclass = 'more-less fa fa-minus';
		$showclassfirst = 'panel-collapse in collapse show';
	  }else{
		$bluebarclass = 'more-less fa fa-plus'; 
		$showclassfirst = 'panel-collapse collapse';
	  }	  
	
	
	if($i==2){
		//$img = "<img src = 'sites/all/modules/dashboard/images/Action_btm.gif'  style='width: 110px;margin-left: 10px;margin-top: -4px;' />";  
		$img_paynow = "<img src = 'sites/all/modules/dashboard/images/pay_now.gif'  style='width: 130px;' />";
	}else {
		$img = "";  
		$img_paynow = "";
	}
	if($elist[$i]->e_clinid !=""){
		$clin_no = $elist[$i]->e_clinid;
	}else{
		$clin_no = 'XXXXXXXXXXXX';
	} 
  $form['elist_begin_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '<div class="panel panel-default">
	   					<div class="panel-heading" role="tab" id="headingOne_'.$i.'">
	   						<a role="button" data-toggle="collapse" data-parent="#accordion" href="#collapseOne_'.$i.'" aria-expanded="true" aria-controls="collapseOne_'.$i.'">
								<i class="'.$bluebarclass.'"></i>'.$elist[$i]->est_name.$img.'
									<div class="text-right pull-right mr-4">Business Referance ID : <strong>'.$clin_no.'</strong></div>
							</a>
						</div>',
	);
  
  $form['addservice_begin_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '<div id="collapseOne_'.$i.'" class="'.$showclassfirst.'" role="tabpanel" aria-labelledby="headingOne_'.$i.'">
	   					<div class="panel-body">
						  '.l('<i class="fa fa-plus"></i> Add Service With Wizard', 'addajax_wizard_service/nojs/'.$i.'/'.$elist[$i]->est_id, array('html'=>TRUE,'attributes'=>array('class' => array('ctools-use-modal','btn add-service btn-sm pull-right mb-3'))))
						  .l('<i class="fa fa-plus"></i> Add New Service', 'addajaxservice/nojs/'.$i.'/'.$elist[$i]->est_id, array('html'=>TRUE,'attributes'=>array('class' => array('ctools-use-modal','btn add-service btn-sm pull-right mb-3')))).'',
	);
	
	 /*<a href="#" class="btn btn-info btn-sm pull-right mb-3" data-toggle="modal" data-target="#addservice"><i class="fa fa-plus"></i> Add Service</a> */
	
  $form['servicetable_begin_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '<div class="table-responsive all_establishment">',
	);	

/************************** Table Content begin ************************************/	
 $form['table_conent_'.$i] = array(
 	  '#type' => 'markup',
	  '#markup' => estservice_list($elist[$i]->est_id)
 );	
 

/************************** Table Content end ************************************/ 
 
	
  $form['servicetable_end_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '</div>',
	);
 
  /*$form['crf_'.$i] = array(
 	  '#type' => 'markup',
	  '#markup' => '<a href="https://wblc.gov.in/annual-return/year-wise-annual-return-wizard" class="CRF-btn pull-left"><i class="fa fa-link"></i> Submission of Common Return (CRF)</a><a href="payment-details" class="pull-right">'.$img_paynow.'</a>'
 );	*/
 
  $form['addservice_end_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '</div></div>',
	);	


  $form['elist_end_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '</div>',
	);
  }
  }else{
	 $form['empty_msg'] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '<div> No Establishment Found</div>',
	); 
  }
 
 $form['form_end'] = array( 
  '#prefix' => '',
  '#suffix' => '</div></div></div></div>' ,
 );
 
 return $form;
}

/************* Ajax menu callback.********************************/


function mymodaladdservice_callback($ajax,$ID,$estid){
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'title' => t(''),
	  'noteID'=>$ID,
	  'estid'=>$estid,
    );
    $output = ctools_modal_form_wrapper('mymodaladdservice_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }else {
    return drupal_get_form('mymodaladdservice_form');
  }
} 


function mymodaladdwizardservice_callback($ajax,$ID,$estid){
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'title' => t(''),
	  'noteID'=>$ID,
	  'estid'=>$estid,
    );
    //$output = ctools_modal_form_wrapper('mymodaladdwizardservice_form', $form_state);
    //$output = ctools_modal_form_wrapper('ssdg_flow_question_wizard_form', $form_state);
    $output = ctools_modal_form_wrapper('question_wizard_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }else {
    return drupal_get_form('question_wizard_form');
  }
} 


/**************** Drupal form to be put in a modal*******************/
function mymodaladdservice_form($form, &$form_state){
  

  /*$form['form_begin'] = array(
    	//'#type' => 'markup',
        '#prefix' => '<div id="addservice" class="modal fade" role="dialog"><div class="modal-dialog"><div class="modal-content"><div class="modal-header"><h4 class="modal-title">	
					  Add Service</h4> <button type="button" class="close" data-dismiss="modal">&times;</button>',
		'#suffix' => '</div>'
    );*/
	
  $form['dname'] = array(
	   '#title'=> '',
	   '#type' => 'select', 
	   '#attributes' => array('class'=>array('form-control p-input'), 'placeholder'=>'Select Directorate', 'autocomplete' => 'off', 'aria-describedby'=> 'nameHelp'),
	   '#options' => directorate_list(),
	   '#ajax'=>array(
	   			'callback'	=> 'ajax_dservice_callback',
				'event' 	=> 'change',
				'effect' 	=> 'fade',			
				'progress'	=>	array(
					'type'		=>'throbber',
					'message'	=>t('loading'),
			    ),
		),
	   '#prefix' => '<div class="col-xl-12"><div class="selectpicker">',
	   '#suffix' => '</div></div>'
	);	
	
	if(isset($form_state['values']['dname']) && trim($form_state['values']['dname']) != '' && trim($form_state['values']['ownership']) != '0'){
	 $form['dservice'] = array(
	   '#title'=> '',
	   '#type' => 'select', 
	   '#attributes' => array('class'=>array('form-control p-input'), 'placeholder'=>'Select Service', 'autocomplete' => 'off', 'aria-describedby'=> 'nameHelp'),
	   '#options' => dservice_list($form_state['values']['dname']),
	   '#prefix' => '<div id="ld_dservice_replace" class="col-xl-12"><div class="selectpicker">',
	   '#suffix' => '</div></div>'
	);
  }
  
  $form['dservice_blank'] = array(
			'#prefix' => '<div id="ld_dservice_replace">',
			'#suffix' => '</div>'
		);
  if( $form_state['submitted']){
	  	/*$commands[] = ajax_command_alert('Successfully Added Service.');
        $commands[] = ctools_modal_command_dismiss();
        $commands[] = ctools_ajax_command_replace('estblish-table-'.$form_state['estid'],'abcd');*/
		//$form_state['ajax_commands'][] = ajax_command_alert('Successfully Added Service.');
		$form_state['ajax_commands'][] = ctools_modal_command_dismiss();
		// Tell the browser to replace the old link with the new one.
		//$commands[] = ctools_modal_command_dismiss();
		$form_state['ajax_commands'][] = ajax_command_replace('#estblish-table-'.$form_state['estid'], estservice_list($form_state['estid']));
		
		
    //print ajax_render($commands);
    //exit;
 }	
  $form['submit'] = array(
	   '#title'=> '',
	   '#type' => 'submit',
	   '#value' => 'Submit',
	   '#attributes' => array('class'=>array('btn btn-primary'),'placeholder'=>''),
	   //'#default_value'=>!empty($uamdata) ? $uamdata['fname'] : '',
	   '#prefix' => '<div class="col-xl-12">',
	   '#suffix' => '</div>'
	);
  
  /*$form['form_end'] = array(
        '#prefix' => '',
		'#suffix' => '</div></div></div>'
    );*/
  return $form;
}

function directorate_list(){
  $default_select = array(""=>"- Select Directorate-");
  $query  = db_select('ar_authority','o')->fields('o',array('id','authority_name','authority_code'));
  $query  = $query->condition('authority_code',array('LC','B','F'),'IN');
  $query  = $query->orderBy('id'); 
  $result = $query->execute();
  //print_r($result); exit;
  $list = array();
  foreach ($result as $record) {
    $list[$record->authority_code] = t('@authority_name', array(
    '@authority_name' => $record->authority_name,
    ));
  }
  return ($default_select+$list);
}

function ajax_dservice_callback($form,&$form_state){
	$commands = array();
	if(trim($form_state['values']['dname'])== 'LC' || trim($form_state['values']['dname'])== 'F' || trim($form_state['values']['dname'])== 'B'){
		$commands[] = ajax_command_replace('#ld_dservice_replace', drupal_render($form['dservice']));
	}else{
		$commands[] = ajax_command_replace('#ld_dservice_replace', drupal_render($form['dservice_blank']));
	}
	return array('#type' => 'ajax', '#commands' => $commands);
 }
 
function dservice_list($dcode){
	$default_select1 = array(""=>"- Select Service-");
	
	//$q = db_query("SELECT service_name from {ld_service_master} WHERE directorate_code = '$dcode'")->fetchAll();
	 
	 //print_r($q); exit;
	
	$q = db_select('ld_service_master','s');
	$q->leftJoin('ld_act_master', 'a', 'a.id=s.act_id');
	$q->fields('s',array('id','act_id','service_name','directorate_name','directorate_code','service_type'));
	$q->fields('a',array('act_title','directorate_code'));
	$q->condition('s.is_active','Y','=');
	$q->condition('s.directorate_code',$dcode,'=');
	//$q->orderBy('s.service_type','ASC');
	$q->orderBy('s.ord_col','ASC');
	//return $dserivce_result; exit;
	$q_result = $q->execute();
	
	$q_result_data = $q_result->fetchAll();

    $list1 = array();
  	foreach ($q_result_data as $data) {
     
	  $actname = '';
	  if($data->act_title != '') {
		 $actname = '['.$data->act_title.']';  
	  }
      $list1[$data->id.'_'.$data->act_id] = t('@service_name', array(
     '@service_name' => $data->service_name.' '.$actname,
    ));
  }
  return ($default_select1+$list1);
	 
 } 
function mymodaladdservice_form_validate($form,&$form_state){
	if (!$form_state['values']['dname']) {
    	form_set_error('dname', 'You must select dname to continuing');    
  	}else if (!$form_state['values']['dservice']) {
    	form_set_error('dservice', 'You must select dservice to continuing');    
  	}
}
function mymodaladdservice_form_submit($form,&$form_state){ 

	global $user;
	$service_act = explode("_",$form_state['values']['dservice']);
		$q = db_select('ld_user_service_info','lusi');
		$q->fields('lusi',array('id'));
		$q->condition('lusi.uid',$user->uid,'=');
		$q->condition('lusi.service_id',$service_act[0],'=');
		$q->condition('lusi.act_id',$service_act[1],'=');
		$q->condition('lusi.directorate_code',$form_state['values']['dname'],'=');
		$q->condition('lusi.est_id',$form_state['estid'],'=');
		$q_result = $q->execute();
		$num_of_results = $q_result->rowCount();
		
		if ($num_of_results > 0 && trim($form_state['values']['dname']) == 'LC') {
			form_set_error('dservice', 'Service already exist for this establishment');  
		}
		else if(trim($form_state['values']['dname']) == 'LC') {
			$d = date('Y-m-d H:i:s');
			$newService 		= 	array(
				'uid' 				=> $user->uid,
				//'service_id' 		=> $service_id, 
				'service_id'        => $service_act[0],
				'act_id' 			=> $service_act[1], 
				'application_time'  => $d,
				'directorate_code' 	=> $form_state['values']['dname'],
				'est_id'			=> $form_state['estid'],
				'modified_date'			=> $d
			);
			
			db_insert('ld_user_service_info')->fields($newService)->execute();
			
		}
		else{
			$d = date('Y-m-d H:i:s');
			$newService 		= 	array(
				'uid' 				=> $user->uid,
				//'service_id' 		=> $service_id, 
				'service_id'        => $service_act[0],
				'act_id' 			=> $service_act[1], 
				'application_time'  => $d,
				'directorate_code' 	=> $form_state['values']['dname'],
				'est_id'			=> $form_state['estid'],
				'status'			=> 0,
				'modified_date'			=> $d
			);
			
			db_insert('ld_user_service_info')->fields($newService)->execute();
		}
		
$form_state['rebuild'] = TRUE;


	//$service_act = explode("_",$form_state['values']['dservice']);
	//print_r($service_act); exit;
	
}



function estservice_info($est_id){
	//echo "--->".$est_id; exit;
	$estservice_list_query_result_data = array();
	
	 $sort = 'DESC';
	 $order = 'authority_name';
	
	 $estservice_list_query = db_select('ld_user_service_info', 'us');
	 $estservice_list_query->leftJoin('ld_service_master', 's', 's.id=us.service_id');
	 $estservice_list_query->leftJoin('ar_authority','a','a.authority_code=us.directorate_code');

	 $estservice_list_query->leftJoin('ld_act_master', 'aa', 'aa.id=s.act_id');
	 $estservice_list_query->fields('aa',array('act_title'));
	 
	 $estservice_list_query->leftJoin('users', 'u', 'u.uid=us.uid');
	 $estservice_list_query->leftJoin('ld_users_details', 'lud', 'lud.uid=us.uid');
	 $estservice_list_query->fields('u', array( 'name'));
	 $estservice_list_query->fields('lud', array( 'ld_pass' ));
	 
	 $estservice_list_query->fields('s',array('act_id','service_name','directorate_name','directorate_code','service_type'));
	 $estservice_list_query->fields('us',array('uid','service_id','application_time','act_id','est_id','directorate_code','status'));
	 $estservice_list_query->fields('a',array('authority_name','authority_code'));
	 
	 $estservice_list_query->addField('s', 'id', 'ld_service_master_id');
	 $estservice_list_query->addField('us', 'id', 'user_service_info_id');
	 $estservice_list_query->addField('a', 'id', 'ar_authority_id');
	 
	 $estservice_list_query->condition('us.est_id',$est_id,'=');
	 $estservice_list_query->orderBy($order, $sort); 
	 $estservice_list_query_result = $estservice_list_query->execute();
	 $estservice_list_query_result_data = $estservice_list_query_result->fetchAll();
	 
	 /*echo "mmm-->";
	 print_r($estservice_list_query_result_data);
	 exit;*/
	 
	 return $estservice_list_query_result_data;
}  
  
  
function estservice_list($est_id){
	 	 
	 global $base_root, $base_path,$user;
	 
	 $estservice_list_query_result_data = estservice_info($est_id);
	 
	 //print_r($estservice_list_query_result_data); exit;
	 
	 $rows = array();
     $header = array();
  	 $output = '';
	  																		
	 //Define table columns
	 $header = array(
	 	  //array('data'=> 'Sl No.'),
          array('data'=> 'Department / Parastatal'),
		  array('data'=> 'Service'),
		  array('data'=> 'Category'),
		  array('data'=> 'Application Date'),
		  array('data'=> 'Status'),
		  array('data'=> 'Action'),
      );
	  
	//Table data.
	
	//$i=0;
	 foreach($estservice_list_query_result_data as $data){
		//$i++;
		if($data->service_type=="1"){ 
			$service_type = "Pre-Establishement";
		}else if($data->service_type=="2"){
			$service_type = "Pre-Operation";
		}else if($data->service_type=="3"){
			$service_type = "Others";
		}else{
			$service_type = "--";
		}
	 $del = "<i class='fa fa-trash'></i>"; 
	$service_status = "NA";
	$link = array('data' =>l(t('Apply Online'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Apply Online','class' => array('btn btn-outline-warning btn-sm')))).'&nbsp;| &nbsp;'.l( $del.t(''), 'ajaxdelservice/'.$est_id.'/'.$data->user_service_info_id, array('html' => TRUE,'attributes'=>array('title' => 'Delete','class' => array('delete-icon use-ajax')))));
//	print_r ($data->directorate_code);exit;
	if (trim($data->directorate_code) == 'B') { 
		if ($data->service_id == 32) {
			switch ($data->status) {
			    case 1:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Pending</span>';
			        $link = array('data' =>l(t('Please click here to complete the application'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
			    case 2:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/fees_pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Payment Pending</span>';
			         $link = array('data' =>l(t('Pay Now'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Pay Now','class' => array('action_icon'),'style'=>'background: #e43c3c;'))));
			        break;
			    case 3:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/applied.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Applied / Submitted</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #5d7aba;'))));
			        break;
			    case 4:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/in_process.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Inspection Ongoing / Processing</span>';
			         $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Inspection Ongoing','class' => array('action_icon'),'style'=>'background: #5d7aba;'))));
			        break;
			    case 5:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/approved.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Completed</span>';
			         $link = array('data' =>l(t('Download Certificate'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #5d7aba;'))).l(t('Renew'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #894545;'))).'<br>');
			        break;
					/* --------- After Hydraulic Test Renew Button along with Inspection Process Ongoing----------*/
			    case 6:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/in_process.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Inspection Ongoing / Processing</span>';
			          $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Click for Further Action','class' => array('action_icon'),'style'=>'background: #5d7aba;'))).l(t('Renew'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Renew','class' => array('action_icon'),'style'=>'background: #894545;'))).'<br>');
			        break;
			    case 7:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/fees_pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Correction Required</span>';
			         $link = array('data' =>l(t('Back for Correction'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Back for Correction','class' => array('action_icon'),'style'=>'background: #e43c3c;'))));
			        break;
			   /* case 8:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/incomplete.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Repair Required</span>';
			         $link = array('data' =>l(t('View Details'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Repair Required','class' => array('action_icon'),'style'=>'background: #e94033;'))));
			        break;*/
			    default:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/apply-icon.png' />";
			    	$service_status = '<span class="status_icon">'.$img.'Not Applied</span>';
			    	$link = array('data' =>l(t('Apply Online'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Apply Online','class' => array('action_icon'),'style'=>'background: #e94033;'))).'&nbsp;|&nbsp;'.l( $del.t(''), 'ajaxdelservice/'.$est_id.'/'.$data->user_service_info_id, array('html' => TRUE,'attributes'=>array('title' => 'Delete','class' => array('delete-icon use-ajax')))));
			        break;
			}
		}

		if ($data->service_id == 33) {
			switch ($data->status) {
				 case 2:
				 	$img = "<img src = 'sites/all/modules/dashboard/images/paynow.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Renew Pay Now</span>';
			         $link = array('data' =>l(t('Renew Pay Now'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Renew Pay Now','class' => array('action_icon'),'style'=>'background: #23a285;'))));
			        break;
			     default:
			     	$img = "<img src = 'sites/all/modules/dashboard/images/rectification.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Renew</span>';
			         $link = array('data' =>l(t('View Details'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #894545;'))));
			        break;

			}
		}
	}
	
	if (trim($data->directorate_code) == 'F') { 
		if ($data->service_id == 46) {
			switch ($data->status) {
			    case 1:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/incomplete.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Incomplete Application Not Submitted</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 2:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Submitted but CAF with DSC not uploaded yet</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 3:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Payment Done</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 4:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Submitted and send to Inspector / Asst. Director</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 5:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application send to Inspector (Chemical) / Asst. Director (Chemical)</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 6:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/rectification.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application send back to Applicant</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 7:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Data Re-submitted but CAF with DSC not uploaded yet</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 8:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/rectification.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application send back to Applicant for proper document</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 9:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application send back to Applicant for Repayment</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 10:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Repayment Done</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 11:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Sent to Deputy Director</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 12:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Sent to Deputy Director (chemical)</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 13:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Sent to Jt. CIF</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 14:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Sent to Jt. CIF (Chemical)</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 15:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Approved by Jt. CIF (Chemical) but pending from Jt. CIF (General)</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 16:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/issued.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Issued / Certificate Delivered</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;											
				default:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/apply-icon.png' />";
			    	$service_status = '<span class="status_icon">'.$img.'Not Applied</span>';
			    	$link = array('data' =>l(t('Apply Online'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Apply Online','class' => array('action_icon'),'style'=>'background: #e94033;'))).'&nbsp;|&nbsp;'.l( $del.t(''), 'ajaxdelservice/'.$est_id.'/'.$data->user_service_info_id, array('html' => TRUE,'attributes'=>array('title' => 'Delete','class' => array('delete-icon use-ajax')))));
			        break;	
					
			}
		}
		if ($data->service_id == 44) {
			switch ($data->status) {
			    case 1:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/incomplete.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Incomplete Application Not Submitted</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 2:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Submitted but CAF with DSC not uploaded yet</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 3:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Payment Done</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 4:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Submitted and send to Inspector / Asst. Director</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 5:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application send to Inspector (Chemical) / Asst. Director (Chemical)</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 6:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/rectification.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application send back to Applicant</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 7:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Data Re-submitted but CAF with DSC not uploaded yet</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 8:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/rectification.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application send back to Applicant for proper document</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 9:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application send back to Applicant for Repayment</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 10:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Repayment Done</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 11:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Sent to Deputy Director</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 12:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Sent to Deputy Director (chemical)</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 13:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Sent to Jt. CIF</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 14:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Sent to Jt. CIF (Chemical)</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;
				case 15:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Application Approved by Jt. CIF (Chemical) but pending from Jt. CIF (General)</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;	
				case 16:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/issued.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Issued / Certificate Delivered</span>';
			        $link = array('data' =>l(t('Click for Further Action'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('action_icon'),'style'=>'background: #1ca033;'))));
			        break;											
				default:
			    	$img = "<img src = 'sites/all/modules/dashboard/images/apply-icon.png' />";
			    	$service_status = '<span class="status_icon">'.$img.'Not Applied</span>';
			    	$link = array('data' =>l(t('Apply Online'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Apply Online','class' => array('action_icon'),'style'=>'background: #e94033;'))).'&nbsp;|&nbsp;'.l( $del.t(''), 'ajaxdelservice/'.$est_id.'/'.$data->user_service_info_id, array('html' => TRUE,'attributes'=>array('title' => 'Delete','class' => array('delete-icon use-ajax')))));
			        break;	
					
			}
		}
	}


	if (trim($data->directorate_code) == 'LC') {
		if ($data->service_id == 1 || $data->service_id == 4 || $data->service_id == 2 || $data->service_id == 3) {
			switch ($data->status) {
			    case "0":
			     	$img = "<img src = 'sites/all/modules/dashboard/images/applied.png' />";
			        /*$service_status = 'Application Pending';
			        $link = array('data' =>l(t('Complete Application'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('btn btn-outline-warning btn-sm')))));*/
			        $service_status = '<span class="status_icon">'.$img.'Applied</span>';
			    	/*$link = array('data' =>l(t('Apply Online'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Apply Online','class' => array('btn btn-outline-warning btn-sm')))).'&nbsp;'.l(t('Delete'), 'ajaxdelservice/'.$est_id.'/'.$data->user_service_info_id, array('html' => TRUE,'attributes'=>array('title' => 'Delete','class' => array('btn btn-danger btn-sm use-ajax')))));*/
			    	$link = array('data' =>l(t('View Details'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #894545;')))

			    		/*.l(t('Feedback'), 'addajaxservice/nojs/'.$i.'/'.$elist[$i]->est_id, array('html' => TRUE,'attributes'=>array('title' => 'Feedback','class' => array('action_icon'),'style'=>'background: #894545;')))*/);
			        break;
			   
			    case "V":
			     	$img = "<img src = 'sites/all/modules/dashboard/images/fees_pending.png' />";
			        /*$service_status = 'Application Pending';
			        $link = array('data' =>l(t('Complete Application'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Complete Application','class' => array('btn btn-outline-warning btn-sm')))));*/
			        $service_status = '<span class="status_icon">'.$img.'Approved / Fees pending</span>';
			    	$link = array('data' =>l(t('Pay now'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Pay Now','class' => array('action_icon'),'style'=>'background: #6b73a2;'))));
			        break;
			   
			    case "B":
			     	$img = "<img src = 'sites/all/modules/dashboard/images/rectification.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Back for Rectification</span>';
			    	$link = array('data' =>l(t('View Details'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Back for Rectification','class' => array('action_icon'),'style'=>'background: #a15757;'))));
			        break;
			   
			    case "VA":
			     	$img = "<img src = 'sites/all/modules/dashboard/images/fees_pending.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Approved / With out Fees</span>';
			    	$link = array('data' =>l(t('View Details'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #6b73a2;'))));
			        break;
			   
			    case "S":
			     	$img = "<img src = 'sites/all/modules/dashboard/images/view-details-icon.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Final Submitted</span>';
			    	$link = array('data' =>l(t('View Details'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #a3d117;'))));
			        break;
			   
			    case "T":
			     	$img = "<img src = 'sites/all/modules/dashboard/images/fees_paid.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Payment Success</span>';
			    	$link = array('data' =>l(t('View Details'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #66bb6a;'))));
			        break;
			   
			    case "I":
			     	$img = "<img src = 'sites/all/modules/dashboard/images/issued.png' />";
			        $service_status = '<span class="status_icon">'.$img.'Issued</span>';
			    	$link = array('data' =>l(t('View Details'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #90a270;'))));
			        break;
			   
			    case "BI":
			     	$img = "<img src = 'sites/all/modules/dashboard/images/in_process.png' />";
			        $service_status = '<span class="status_icon">'.$img.'In Processing</span>';
			    	$link = array('data' =>l(t('View Details'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #446c6c;'))));
			        break;
			   
			    case "F":
			     	$img = "<img src = 'sites/all/modules/dashboard/images/in_process.png' />";
			        $service_status = '<span class="status_icon">'.$img.'In Processing</span>';
			    	$link = array('data' =>l(t('View Details'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'View Details','class' => array('action_icon'),'style'=>'background: #446c6c;'))));
			        break;

			    default:
			     	$img = "<img src = 'sites/all/modules/dashboard/images/apply-icon.png' />";
			    	$service_status = '<span class="status_icon">'.$img.'Not Applied</span>';
			    	$link = array('data' =>l(t('Apply Online'), 'apply-online/'.encryption_decryption_wblabour('encrypt',$data->user_service_info_id), array('html' => TRUE,'attributes'=>array('title' => 'Apply Online','class' => array('action_icon'),'style'=>'background: #e94033;'))).'&nbsp;|&nbsp;'.l( $del.t(''), 'ajaxdelservice/'.$est_id.'/'.$data->user_service_info_id, array('html' => TRUE,'attributes'=>array('title' => 'Delete','class' => array('delete-icon use-ajax')))));
			        break;
			}
		}

	}
	$actname = '';
					  if($data->act_title != '') {
						 $actname = '&nbsp;['.$data->act_title.']';  
					  }
		$rows[] = array(
					//$i,
					$data->authority_name,
      				$data->service_name.$actname,
					$service_type,
					date('d-m-Y', strtotime($data->application_time)),
					$service_status,
					
					//array('data' =>l(t('NA'), 'detailsview/nojs/'.$est_id, array('html' => TRUE,'attributes'=>array('title' => 'NA','class' => array('ctools-use-modal badge badge-success'))))),
					$link
					//array('data' =>l(t('Delete'), 'ajaxdelservice/'.$data->user_service_info_id, array('html' => TRUE,'attributes'=>array('title' => 'Delete','class' => array('btn btn-outline-warning btn-sm')))))
					/*$data->,
					$data->,*/
					
					//
	  	);   
	 }
	 
	  $output = theme_table( array(
							  'header' => $header,
							  'rows' => $rows,
							  'attributes' => array('class' => array('table','center-aligned-table')),
							  'sticky' => true,
							  'caption' => '',
							  'colgroups' => array(),
							  'empty' => t("No data found!") // The message to be displayed if table is empty
							)
						  ).theme('pager');
	  
	return '<div id="estblish-table-'.$est_id.'">'.$output.'</div>'; 
 }
 
 function est_service_del($est_id,$user_service_info_id){
	//drupal_add_library('system', 'drupal.ajax');
	
	 if (trim($user_service_info_id) != 0) {
		 
		 $query = db_delete('ld_user_service_info');
		 $query->condition('id', trim($user_service_info_id));
		 $query->execute();
		 
		 $commands = array();
		 //$form_state['ajax_commands'][] = ajax_command_replace('#estblish-table-'.$form_state['estid'], estservice_list($form_state['estid']));
		 $commands[] = ajax_command_replace('#estblish-table-'.$est_id.'', "<div id='estblish-table-".$est_id."'>".estservice_list($est_id)."</div>");
		 $page = array('#type' => 'ajax', '#commands' => $commands);
		 ajax_deliver($page);
		
	 }else{
		  return array(
		  '#markup' => 'TTTTT',
		);
	 }
	 
}


//-------------  Ganga Code date:14-11-2019  

function showstatus_callback($ajax,$estid){
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'title' => t(''),
	  'noteID'=>'',
	  'estid'=>$estid,
    );
    $output = ctools_modal_form_wrapper('showstatus_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }else {
    return drupal_get_form('showstatus_form');
  }
} 

/*

$header = array(
	 	  //array('data'=> 'Sl No.'),
          array('data'=> 'Directorate Name'),
		  array('data'=> 'Service'),
		  array('data'=> 'Category'),
		  array('data'=> 'Application Date'),
		  array('data'=> 'Status'),
		  array('data'=> 'Action'),
      );

*/

function showstatus_form($form, &$form_state){
	$est_id = $form_state['estid'];
	 $estservice_list_query_result_data = estservice_info($est_id);
	 $row='';
	 foreach($estservice_list_query_result_data as $data){
		 	if($data->service_type=="1"){ 
			$service_type = "Pre-Establishement";
			}else if($data->service_type=="2"){
				$service_type = "Pre-Operation";
			}else if($data->service_type=="3"){
				$service_type = "Others";
			}else{
				$service_type = "--";
			}
			$row.='<tr><td>'.$data->authority_name.'</td>
      			<td>'.$data->service_name.'</td>
				<td>'.$service_type.'</td>
				<td>'.date('d-m-Y', strtotime($data->application_time)).'</td>
				</tr>'; 
	}
	$form['info'] = array(
		'#type' => 'markup',
		'#markup' => '<table width="100%" border="0" cellspacing="0" cellpadding="0">
		 <tr>
			<th>Directorate Name</th>
			<th>Service</th>
			<th>Category</th>
			<th>Application Date</th>
		  </tr>'.$row.'
</table>'
	);
  return $form;
	
}





/********************PAYMENT DETAILS************************/

function payment_details_form($form, &$form_state) {
   global $user;	
   ctools_include('modal');
   ctools_modal_add_js();
	
   $form['form_begin'] = array( 
   '#prefix' => '<div class="page-heading mb-4"><h3>PAYMENT DETAILS</h3></div>
  				 <div class="card-deck"><div class="card col-lg-12 px-0 mb-4"><div class="card-body">
				 <div class="panel-group" id="accordion" role="tablist" aria-multiselectable="true">',
   '#suffix' => '' ,
 );
 $i =1;
  //$elist = establishment_info($user->uid);
  //print_r($elist); exit;
  //if(!empty($elist)){
  //for($i=0;$i<sizeof($elist);$i++){
	  
	  //if($i == 0){ 
		$bluebarclass = 'more-less fa fa-minus';
		$showclassfirst = 'panel-collapse in collapse show';
	 // }else{
	//	$bluebarclass = 'more-less fa fa-plus'; 
	//	$showclassfirst = 'panel-collapse collapse';
	  //}	  
  //$img = "<img src = 'sites/all/modules/dashboard/images/Action_btm.gif'  style='width: 110px;margin-left: 10px;margin-top: -4px;' />";
  $form['elist_begin_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '<div class="panel panel-default">
	   					<div class="panel-heading" role="tab" id="headingOne_'.$i.'">
	   						<a role="button" data-toggle="collapse" data-parent="#accordion" href="#collapseOne_'.$i.'" aria-expanded="true" aria-controls="collapseOne_'.$i.'">
								<i class="'.$bluebarclass.'"></i>'."Establisment 1".'
									<div class="text-right pull-right mr-4">CLIN ID : <strong>XXXXXXXXXXXX</strong></div>
							</a>
						</div>',
	);
  
  $form['addservice_begin_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '<div id="collapseOne_'.$i.'" class="'.$showclassfirst.'" role="tabpanel" aria-labelledby="headingOne_'.$i.'">
	   					<div class="panel-body">
						  
	   					
	   							<div class="row">
			   					<div class="col-md-4">
			   					<address>
			   					<strong>Depositor′s Name :</strong>&nbsp; Gangadhar Bauri</br>
			   					<strong>Mobile Number :</strong>&nbsp; 9874028298</br>
			   					<strong>Email Address :</strong>&nbsp; gangadharbouri@gmail.com</div>
			   					</address>
			   					<div class="col-md-8 text-right total-amount"></div>
			   					</div>
		   				


						  ',
	);
	
	 /*<a href="#" class="btn btn-info btn-sm pull-right mb-3" data-toggle="modal" data-target="#addservice"><i class="fa fa-plus"></i> 
							Add Service</a> */
	
  $form['servicetable_begin_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '<div class="table-responsive all_establishment">',
	);	

/************************** Table Content begin ************************************/	
 $form['table_conent_'.$i] = array(
 	  '#type' => 'markup',
	  '#markup' => '<div id="estblish-table-1">
	  	<table class="table table-striped center-aligned-table sticky-enabled">
	  	<caption></caption>
			 <thead><tr><th width="12%">Directorate Name</th><th width="45%">Service</th><th width="8%">Amount</th><th width="15%">Action</th> </tr></thead>
			<tbody>
			 <tr class="odd">
				 <td>Labour Commissionerate</td>
				 <td>Registration of establishment by Principal Employer, amendment thereof&nbsp;[Inter State Migrant Workmen (Regulation of Employment &amp; Conditions of Service)Act 1979]</td>
				 <td>3990.00</td>
				 <td><a href="/demowblabour/ajaxdelservice/16/10904" title="Delete" class="delete-icon use-ajax ajax-processed"><i class="fa fa-trash"></i></a></td> 
			 </tr>
			 <tr class="even">
				 <td>Directorate of Boilers</td>
				 <td>Registration of Boilers under The Boilers Act, 1923</td>
				 <td>4510.00</td>
				 <td><a href="/demowblabour/ajaxdelservice/16/10905" title="Delete" class="delete-icon use-ajax ajax-processed"><i class="fa fa-trash"></i></a></td> 
			 </tr>
			</tbody>
		</table>
	  </div>'
 );	
 

/************************** Table Content end ************************************/ 
 
	
  $form['servicetable_end_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '</div>',
	);

 $form['total_amount_div'] = array(
 	  '#type' => 'markup',
	  '#markup' => ' <div class="text-right total-amount"><strong > Total Amount :</strong> <span>Rs. 8500/-</span></div><hr><br/>'
 );	
 
  $form['payment_option'] = array(
 	  '#type' => 'markup',
	  '#markup' => '
	  <div class="payment_mode">
<div class="row">
<div class="col-md-2"><strong>Select Payment Mode:</strong></div>
<div class="col-md-10">
	  							<div id="edit-payment-mode" class="form-radios">
	  								<div class="row">
	  									<div class="col-md-2">
	  										<label class="radio-inline">
										      <input type="radio" id="edit-payment-mode-1" name="payment_mode">Online Payment
										    </label>
				   					    </div>

				   					    <div class="col-md-2">
	  										<label class="radio-inline">
										      <input type="radio" id="edit-payment-mode-2" name="payment_mode">Counter Payment
										    </label>
				   					    </div>

				   					    <div class="col-md-2">
	  										<label class="radio-inline">
										      <input type="radio" id="edit-payment-mode-5" name="payment_mode">Debit Card Payment
										    </label>
				   					    </div>

				   					    <div class="col-md-2">
	  										<label class="radio-inline">
										      <input type="radio" id="edit-payment-mode-8" name="payment_mode">SBI ePay 
										    </label>
				   					    </div>

					   			


'
 );	
 
 
  $form['crf_'.$i] = array(
 	  '#type' => 'markup',
	  '#markup' => ' <div class="col-md-4"><a href="#" class="pay-btn pull-right"><i class="fa fa-credit-card"></i>&nbsp; Pay Now</a></div></div></div></div></div></div>'
 );	
 
  $form['addservice_end_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '</div></div>',
	);	


  $form['elist_end_'.$i] = array(
	   '#title'=> '',
	   '#type' => 'markup', 
	   '#markup' => '</div>',
	);
  //}
 // }
 
 $form['form_end'] = array( 
  '#prefix' => '',
  '#suffix' => '</div></div></div></div>' ,
 );
 
 return $form;
}


	