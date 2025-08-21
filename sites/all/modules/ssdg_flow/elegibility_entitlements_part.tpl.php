<?php global $user,$base_root,$base_path,$base_url;

//die('SDFSJHGHSFJHSVC');
/*if(isset($_REQUEST) && !empty($_REQUEST)) {
		print_r($_REQUEST);
		exit;
	}
	else{
		die('NO REQUEST');
	}
*/
/*var_dump($_REQUEST['confirm_submit']);
exit;*/
if(($_REQUEST['confirm_submit']=="confirm_submit")){
		
		function ld_encryption_decryption($action, $string) {
	    $output 		= false;
	    $encrypt_method = "AES-256-CBC";
	    
	    $secret_key 	= 'secret_key';
	    $secret_iv 		= 'secret_iv';
		
	    $key = hash('sha512', $secret_key);
		
	    $iv = substr(hash('sha512', $secret_iv), 0, 16);

	    if( $action == 'encrypt' ) {
	        $output = openssl_encrypt($string, $encrypt_method, $key, 0, $iv);
	        $output = base64_encode($output);
	    }else if( $action == 'decrypt' ){
	        $output = openssl_decrypt(base64_decode($string), $encrypt_method, $key, 0, $iv);
	    }
	    return $output;
		}
	
	
	$arr   = array();
	//print_r($_REQUEST['chk']); exit;
	foreach($_REQUEST['chk'] as $val){
		$arr   = explode("_",$val);
		$service_id = $arr[0];
		$act_id = $arr[1];
		
		$role=0;
		
		/*if(trim($service_id)=='32' || trim($service_id) == '33'){
			$role=4;
		}else if(trim($service_id)=='35'){
			$role=9;
		}else if(trim($service_id)=='34'){
			$role=12;
		}else{
			$role=0;
		}*/
		
		$role_boilers=0;
		if(trim($service_id)=='32' || trim($service_id) == '33'){
			$role_boilers=4;
		}else if(trim($service_id)=='35'){
			$role_boilers=9;
		}else if(trim($service_id)=='34'){
			$role_boilers=12;
		}else{
			$role_boilers=4;
		}
		
		
		
		/*if(trim($service_id) != '32' || trim($service_id) != '33'){
				$d = date('Y-m-d H:i:s');
				$newService 		= 	array(
					'uid' 			=> $user->uid,
					'service_id' 	=> $service_id, 
					'act_id' 		=> $act_id, 
					'application_time' => $d,
				);
				
				db_insert('ld_user_service_info')->fields($newService)->execute();
			
		}else{*/
			$query = db_select('ld_user_service_info', 'us');
			$query ->fields('us', array( 'uid','service_id','act_id'));
			$query->condition('us.service_id',trim($service_id),'=');
			$query->condition('us.uid',trim($user->uid),'=');
			
			if($act_id!=0){
				$query->condition('us.act_id',trim($act_id),'=');
			}
			$result = $query->execute();
			$data = $result->fetchAssoc();
			if(empty($data)){
				$d = date('Y-m-d H:i:s');
				$newService 		= 	array(
					'uid' 			=> $user->uid,
					'service_id' 	=> $service_id, 
					'act_id' 		=> $act_id, 
					'application_time' => $d,
				);
				
				db_insert('ld_user_service_info')->fields($newService)->execute();
				
			}
		//}
	}
	
	//echo "insert"; exit;
	
	$user_reg_det = db_select('users', 'u');
	$user_reg_det ->fields('u', array('name'));
	$user_reg_det->condition('u.uid',trim($user->uid),'=');
	$user_det = $user_reg_det->execute();
	if($user_det->rowCount()>0){
		$res_det 	= 	$user_det->fetchAssoc();
		$username	=	trim($res_det['name']);
	}
	
	
	
	$query_1 = db_update('ld_users_details');
	$query_1->fields(array('ldapplicationflag'=>"1"));
	$query_1->condition('uid',trim($user->uid),'=');
	$rs = $query_1->execute();
	
	
	
	$app_reg_det = db_select('ld_users_details', 'lud');
	$app_reg_det ->fields('lud', array());
	$app_reg_det->condition('lud.uid',trim($user->uid),'=');
	$result_det = $app_reg_det->execute();
	if($result_det->rowCount() > 0){
		$reg_det 	= 	$result_det->fetchAssoc();
		
		$fname 				=	trim($reg_det['fname']);
		$mname 				=	trim($reg_det['mname']);
		$lname 				=	trim($reg_det['lname']);
		$gender 			=	trim($reg_det['gender']);
		$dob 				=	trim($reg_det['dob']);
		$mobile 			=	trim($reg_det['mobile']);
		$email 				=	trim($reg_det['email']);
		$religion 			=	trim($reg_det['religion']);
		$aadharno 			=	trim($reg_det['aadharno']);
		$voter 				=	trim($reg_det['voter']);
		$pancard 			=	trim($reg_det['pancard']);
		$pincode 			=	trim($reg_det['pincode']);
		$state 				=	trim($reg_det['state']);
		$district 			=	trim($reg_det['district']);
		$subdivision 		=	trim($reg_det['subdivision']);
		$areatype 			=	trim($reg_det['areatype']);
		$block 				=	trim($reg_det['block']);
		$panchayat 			=	trim($reg_det['panchayat']);
		$policestation 		=	trim($reg_det['policestation']);
		$postoffice 		=	trim($reg_det['postoffice']);
		$address 			=	trim($reg_det['address']);
		$ldapplicationflag 	=	trim($reg_det['ldapplicationflag']);
		$status 			=	trim($reg_det['status']);
		$password 			=	trim($reg_det['ld_pass']);
		
		$curl_post_data = array(
			"username"					=>	$username,
			"password"					=>	$password,
			"fname"						=>	$fname,
			"mname"						=>	$mname, 
			"lname"						=>	$lname, 
			"email"						=>	$email,
			"dob"						=>	$dob,
			"mobile"					=>	$mobile,
			"gender"					=>	$gender,
			"religion"					=>	$religion, 
			"aadharno"					=>	$aadharno,
			"voter"						=>	$voter, 
			"pancard"					=>	$pancard,
			"pincode"					=>	$pincode,
			"state"						=>	$state,
			"district"					=>	$district,
			"subdivision"				=>	$subdivision,
			"areatype"					=>	$areatype,
			"block"						=>	$block,
			"panchayat"					=>	$panchayat,
			"policestation"				=>	$policestation,
			"postoffice"				=>	$postoffice,
			"address"					=>	$address,
			"ldapplicationflag"			=>	$ldapplicationflag,
			"ld_uid"					=>	$user->uid,
			"role"                      =>  $role
		);
		
		
		$curl_post_data_boilers = array(
			"username"					=>	$username,
			"password"					=>	$password,
			"fname"						=>	$fname,
			"mname"						=>	$mname, 
			"lname"						=>	$lname, 
			"email"						=>	$email,
			"dob"						=>	$dob,
			"mobile"					=>	$mobile,
			"gender"					=>	$gender,
			"religion"					=>	$religion, 
			"aadharno"					=>	$aadharno,
			"voter"						=>	$voter, 
			"pancard"					=>	$pancard,
			"pincode"					=>	$pincode,
			"state"						=>	$state,
			"district"					=>	$district,
			"subdivision"				=>	$subdivision,
			"areatype"					=>	$areatype,
			"block"						=>	$block,
			"panchayat"					=>	$panchayat,
			"policestation"				=>	$policestation,
			"postoffice"				=>	$postoffice,
			"address"					=>	$address,
			"ldapplicationflag"			=>	$ldapplicationflag,
			"ld_uid"					=>	$user->uid,
			"role"                      =>  $role_boilers
		);
		
		/*echo "<pre>"; 
		print_r($curl_post_data);
		exit;*/
		
		
		//$aadharno2 ="7896 8521 5639";

		if($aadharno == 0){
			$aadharno = "";
		}
		$password2=ld_encryption_decryption('encrypt', $password);
		$curl_post_data_sf = array(
		
		    "source"                    =>  "wbld",
			"username"					=>	$username,
			"password"					=>	$password2,
			"fname"						=>	$fname,
			"mname"						=>	$mname, 
			"lname"						=>	$lname, 
			"email"						=>	$email,
			"dob"						=>	$dob,
			"mobile"					=>	$mobile,
			"gender"					=>	$gender,
			"religion"					=>	$religion, 
			"aadharno"					=>	$aadharno,
			"voter"						=>	$voter, 
			"pancard"					=>	$pancard,
			"pincode"					=>	$pincode,
			"state"						=>	$state,
			"district"					=>	$district,
			"address"					=>	$address,
			"ldapplicationflag"			=>	$ldapplicationflag,
			"ld_uid"					=>	$user->uid,
			"role"                      =>  $role
		);
		
		//print_r($curl_post_data); exit;
		
		/////////////////////    For Labour Commissionerate Insert API     ///////////////////
		
		$lc = 'https://wblc.gov.in/labourdept/eservices/createUser';
		$ch_lc = curl_init();
		curl_setopt($ch_lc, CURLOPT_HTTPHEADER, array('Content-Type: application/json; charset=utf-8'));
		curl_setopt($ch_lc, CURLOPT_URL, $lc);
		curl_setopt($ch_lc, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch_lc, CURLOPT_SSL_VERIFYHOST, 0);
		curl_setopt($ch_lc, CURLOPT_SSL_VERIFYPEER, 0); 
		curl_setopt($ch_lc, CURLOPT_FOLLOWLOCATION, 0);
		curl_setopt($ch_lc, CURLOPT_POSTFIELDS, json_encode( $curl_post_data ) );
		curl_setopt($ch_lc, CURLOPT_POST, true);
		$results_lc=curl_exec($ch_lc);
		$errors_lc=curl_error($ch_lc);
		curl_close($ch_lc);
		
		/////////////////////    End of Labour Commissionerate Insert API     ///////////////////
		
		/////////////////////    For Boilers Insert API     ///////////////////
		
		
		$boilers = 'https://wbboilers.gov.in/labourdept/eservices/createUser';
		$ch_b = curl_init();
		curl_setopt($ch_b, CURLOPT_HTTPHEADER, array('Content-Type: application/json; charset=utf-8'));
		curl_setopt($ch_b, CURLOPT_URL, $boilers);
		curl_setopt($ch_b, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch_b, CURLOPT_SSL_VERIFYHOST, 0);
		curl_setopt($ch_b, CURLOPT_SSL_VERIFYPEER, 0); 
		curl_setopt($ch_b, CURLOPT_FOLLOWLOCATION, 0);
		curl_setopt($ch_b, CURLOPT_POSTFIELDS, json_encode( $curl_post_data_boilers ) );
		curl_setopt($ch_b, CURLOPT_POST, true);
		$results_b=curl_exec($ch_b);
		$errors_b=curl_error($ch_b);
		curl_close($ch_b);
		
		$factory = 'https://wbfactoryonline.in/webservices/REST/createUser';
		$ch_f = curl_init();
		curl_setopt($ch_f, CURLOPT_HTTPHEADER, array('Content-Type: application/json; charset=utf-8'));
		curl_setopt($ch_f, CURLOPT_URL, $factory);
		curl_setopt($ch_f, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch_f, CURLOPT_SSL_VERIFYHOST, 0);
		curl_setopt($ch_f, CURLOPT_SSL_VERIFYPEER, 0); 
		curl_setopt($ch_f, CURLOPT_FOLLOWLOCATION, 0);
		curl_setopt($ch_f, CURLOPT_POSTFIELDS, json_encode( $curl_post_data_sf ) );
		curl_setopt($ch_f, CURLOPT_POST, true);
		$results_f=curl_exec($ch_f);
		$errors_f=curl_error($ch_f);
		curl_close($ch_f);
		
		/*echo "factory error";
		print_r($errors_f);
		echo "factory response";
		print_r($results_f);*/
		
		//exit;
		
		$shops = 'https://wbshopsonline.in/webservices/REST/createUser';
		$ch_s = curl_init();
		curl_setopt($ch_s, CURLOPT_HTTPHEADER, array('Content-Type: application/json; charset=utf-8'));
		curl_setopt($ch_s, CURLOPT_URL, $shops);
		curl_setopt($ch_s, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch_s, CURLOPT_SSL_VERIFYHOST, 0);
		curl_setopt($ch_s, CURLOPT_SSL_VERIFYPEER, 0); 
		curl_setopt($ch_s, CURLOPT_FOLLOWLOCATION, 0);
		curl_setopt($ch_s, CURLOPT_POSTFIELDS, json_encode( $curl_post_data_sf ) );
		curl_setopt($ch_s, CURLOPT_POST, true);
		$results_s=curl_exec($ch_s);
		$errors_s=curl_error($ch_s);
		curl_close($ch_s);
		
		/*echo "<br/>";
		echo "shop error";
		print_r($errors_s);
		echo "shops response";
		print_r($results_s);
		
		exit;*/
		/*echo $errors_b."  -------     ";
		
		print json_encode( $curl_post_data );*/
		
		/////////////////////    End of Boilers Insert API     ///////////////////
		
		drupal_goto('dashboard1'); 
	}else{
		echo "No Records Found";
	}
}
$current_session=$_SESSION['CURRENT_SESSION'];
//print_r($current_session);
//die;
?>

<link href="<?php print $base_path ?>sites/all/modules/ssdg_flow/css/checkbox-x.css" rel="stylesheet">
<link href="<?php print $base_path ?>sites/all/modules/ssdg_flow/css/theme-krajee-flatblue.css" rel="stylesheet">
<!--<script src="<?php print $base_path ?>sites/all/modules/ssdg_flow/js/checkbox-x.js" type="text/javascript"></script>-->
<!-- <link href="<?php print $base_path ?>sites/all/modules/dashboard/build/css/custom.css" rel="stylesheet"> -->
<link href="<?php print $base_path ?>sites/all/modules/applicant_registration/css/sky-forms.css" rel="stylesheet">

<div class="messages error qstn_elligibility_error_msg" style="display:none"></div>
<div class="container body">
  <div class="main_container">
    <div class="x_panel">
      <div class="x_title">
      	<div class="row">
        <div class="col-md-12 col-sm-12 col-xs-12">
        	<div class="col-md-11"><h1><span>E</span>ligible e-Services</h1></div>
            <div class="col-md-1"><img onclick="PrintDiv();" src="<?php echo $base_root.$base_path?>sites/all/themes/labourdept/images/print.png" alt="" style="margin-top:0px;"></div>
        </div>
        </div>
        <div class="clearfix"></div>
      </div>
      <fieldset>
      	<div id="service-table">
      <form action="" method="post">
        <p>Based on your answers, these are the possible services that you can avail :-</p>
        <div class="table-responsive" id="divToPrint">
          <table class="table table-striped jambo_table bulk_action">
            <thead>
              <tr class="headings">
                <th class="column-title">Directorate </th>
                <th class="column-title">Service Name </th>
                <th class="column-title">Category </th>
                <th class="column-title">Action </th>
              </tr>
            </thead>
            <tbody>
            <?php
			
			$query_lc = db_select('ld_elligibility_question_answer','ea');
			$query_lc->fields('ea',array('question_id','answer','directorate_code'));
			//$query_lc->condition('ea.uid',trim($user->uid),'=');
			$query_lc->condition('ea.current_session_id',$current_session,'=');
			$result_lc = $query_lc->execute();
			$result_data_lc = $result_lc->fetchAll();
			
			$result_data_lc1 = array();
			foreach($result_data_lc as $qs){
				if(trim($qs->question_id) == 4 && trim($qs->answer)=='N'){
					$ans4 = $qs->answer;
				}
				if(trim($qs->question_id) == 16 && trim($qs->answer)=='Y'){
					if($ans4 == 'N'){
						$query_lc1 = db_select('ld_question_answer_transaction','t');
						$query_lc1->fields('t',array('service_id','directorate_code'));
						$query_lc1->condition('t.question_id',trim($qs->question_id),'=');
						$query_lc1->condition('t.answer',trim($qs->answer),'=');
						$query_lc1->condition('t.directorate_code',trim($qs->directorate_code),'=');
						$result_lc1 = $query_lc1->execute();
						$result_data_lc1[]= $result_lc1->fetchAssoc();
					}
				}else{
					$query_lc1 = db_select('ld_question_answer_transaction','t');
					$query_lc1->fields('t',array('service_id','directorate_code'));
					$query_lc1->condition('t.question_id',trim($qs->question_id),'=');
					$query_lc1->condition('t.answer',trim($qs->answer),'=');
					$query_lc1->condition('t.directorate_code',trim($qs->directorate_code),'=');
					$result_lc1 = $query_lc1->execute();
					$result_data_lc1[]= $result_lc1->fetchAssoc();
				}
				
			}
			//print_r($result_data_lc1); exit;
			$str = "";
			if(!empty($result_data_lc1)){
				foreach($result_data_lc1 as $sid){
					if($sid["service_id"] != '0' && $sid["service_id"] != '-1'){
						if($str == ""){
							//echo "inside".$sid["service_id"];
							$str .=$sid["service_id"];
						}else{
							$str .= ",".$sid["service_id"];
						}
					}
				}
			}
			
			
			$mysidarr = array();
			$strdata = explode(",",$str);
			foreach($strdata as $v){
				array_push($mysidarr, intval($v));
			}
			
			$query = db_select('ld_service_master','s');
			$query->leftJoin('ld_act_master', 'a', 'a.id=s.act_id');
			$query->fields('s',array('id','act_id','service_name','directorate_name','directorate_code','service_type'));
			$query->fields('a',array('act_title','directorate_code'));
			//$query->condition('s.is_active','Y','=');
			//if($mysidarr[0]!=0){
			$query->condition('s.id',$mysidarr,'IN');
			//}
			$query->orderBy('s.service_type','ASC');
 			$result = $query->execute();
			$result_data = $result->fetchAll();
			$i = 0;
			if(!empty($result_data)){
			foreach($result_data as $data){ $i++;

				$q = db_select('ld_user_service_info','lusi');
				$q->fields('lusi',array('id'));
				$q->condition('lusi.uid',$user->uid,'=');
				$q->condition('lusi.service_id',$data->id,'=');
				$q->condition('lusi.act_id',$data->act_id,'=');
				//$q->condition(trim('lusi.directorate_code'),trim($dc),'=');
				$q->condition('lusi.est_id',$estid,'=');
				//print $q;exit;
				$q_result = $q->execute();
				$num_of_results = $q_result->rowCount();
			?>
            
              <tr class="even pointer">
                <td class=" "><?php echo $data->directorate_name;?></td>
                <td class=" "><?php echo $data->service_name.", ".$data->act_title;?></td>
                 <td class=" "><?php if($data->service_type=="1"){ echo "Pre-Establishement";}else if($data->service_type=="2"){echo "Pre-Operation";}else if($data->service_type=="3"){echo "Others";}else{echo "--";}?></td>
                 <td> <?php if ($num_of_results > 0 && trim($data->directorate_code) == 'LC') {
								echo '<span style="color: #000000;font-weight: 600;white-space: nowrap;">Service Added</span>';
							}
							elseif ($num_of_results > 0){
								echo '<span style="color: #000000;font-weight: 600;white-space: nowrap;">Previously Added:'.$num_of_results.'</span><br>'.l( $del.t('Add More'), 'add_service_with_wizard/'.base64_encode($estid).'/'.base64_encode(trim($data->directorate_code)).'/'.base64_encode($data->id).'/'.base64_encode($data->act_id), array('html' => TRUE,'attributes'=>array('title' => 'Add More','class' => array('btn btn-primary use-ajax'))));
							}

						else {
						 echo l( $del.t('Add Service'), 'add_service_with_wizard/'.base64_encode($estid).'/'.base64_encode(trim($data->directorate_code)).'/'.base64_encode($data->id).'/'.base64_encode($data->act_id), array('html' => TRUE,'attributes'=>array('title' => 'Add Service','class' => array('btn btn-primary use-ajax'))));
						}
						?>
                 </td>
              </tr>
              
             <?php }
			 	$makeBtnProp = 'processBtnEnabled';
			 }else{ $makeBtnProp='processBtnDisabled';?> 
             <tr class="even pointer"><td class="" colspan="4"> You are not elligible for any services</td></tr>
             <?php }?>
            </tbody>
          </table>
        </div>
        <!--<footer>-->
         <!-- <input type="submit" value="confirm_submit" name="confirm_submit" />-->
          <!--<button type="button" id="<?php echo $makeBtnProp;?>" class="btn btn-success" data-toggle="modal" data-target="#popup">Proceed</button>-->
       <!-- </footer>-->
        <!--<div class="modal fade popup" id="popup" role="dialog">
          <div class="modal-dialog"> 
            <div class="modal-content">
              <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal">&times;</button>
              </div>
              <div class="modal-body">
                <h1>Are You Sure?</h1>
                <button type="submit" name="confirm_submit"  value="confirm_submit" class="btn btn-success">Yes</button>
                <button type="button" class="btn btn-danger" data-dismiss="modal">No</button>
                </div>
            </div>
          </div>
        </div>-->
        </form>
    </div>
      </fieldset>
    </div>
  </div>
</div>
<script src="<?php print $base_path ?>sites/all/modules/ssdg_flow/js/question_elligibility.js"></script> 
<!-- <script type="text/javascript">
	jQuery(document).ready(function(){

	$('.delete-icon').click(function(){
		//val = $(this).val();
		 $(this).closest("tr").hide();
		
		
	});
	});
</script> -->
