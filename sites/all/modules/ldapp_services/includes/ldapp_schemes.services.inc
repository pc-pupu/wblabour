<?php
function ldapp_schemes_services_resource() {
  $api = array(
	'dashboard' => array(
  	'operations' => array(
    	
		 'create' => array(
          'help' => 'Dashboard',
          'callback' => 'dashboard_ld',
          'file' => array('type' => 'inc', 'module' => 'ldapp_services', 'name' => 'includes/ldapp_schemes.services'),
          'access callback' => 'user_access',
          'access arguments' => array('access content'),
          'access arguments append' => FALSE,
          'args' => array(
            array(
              'name' => 'account',
              'type' => 'array',
              'description' => 'The user object',
              'source' => 'data',
              'optional' => FALSE,
            ),
          ),
        ),
      	),
	),
	
	'dashboardld' => array(
  	'operations' => array(
    	
		 'create' => array(
          'help' => 'Dashboard',
          'callback' => 'dashboard_ldfun',
          'file' => array('type' => 'inc', 'module' => 'ldapp_services', 'name' => 'includes/ldapp_schemes.services'),
          'access callback' => 'user_access',
          'access arguments' => array('access content'),
          'access arguments append' => FALSE,
          'args' => array(
            array(
              'name' => 'account',
              'type' => 'array',
              'description' => 'The user object',
              'source' => 'data',
              'optional' => FALSE,
            ),
          ),
        ),
      	),
	),
	
	
	
	
  );

  return $api;
}


function dashboard_ld($user_arr = NULL){
	
	$uid=$user_arr['uid'];
	return array('uid'=>$uid);
	$query = db_select('ld_users_details', 'us');
$query->leftJoin('users', 'u', 'u.uid=us.uid');
$query ->fields('us', array( 'fname','mname','lname','gender','dob','mobile','email','pincode','state','district','subdivision','areatype','block','panchayat','policestation','postoffice','address','ldapplicationflag'));
$query ->fields('u', array( 'name'));
$query->condition('us.uid',trim($uid),'=');
$result = $query->execute();
$data = $result->fetchObject();


$name=$data->name;
if(!empty($data->dob)){ $dob= format_date(strtotime($data->dob), 'custom', 'd-m-Y');}else{ $dob= "N/A";}
if(!empty($data->email)){ $email= $data->email;}else{ $email= "N/A";}
if(!empty($data->mobile)){ $mobile= $data->mobile;}else{ $mobile= "N/A";}
if(!empty($data->pincode)){ $pincode= $data->pincode;}else{ $pincode= "N/A";}
if(!empty($data->address)){ $address= $data->address;}else{ $address= "N/A";}



$query = db_select('ld_user_service_info', 'us');
$query->leftJoin('ld_service_master', 'sm', 'sm.id=us.service_id');
$query ->fields('sm', array( 'service_name','directorate_name','directorate_code'));
$query->condition('us.uid',trim($uid),'=');
$query->condition('sm.is_active','Y','=');
$service_data = $query->execute();
$service_array = $service_data->fetchAll();
$lc_service_count = 0;
$boilers_service_count = 0;
$factory_service_count = 0;
$shops_service_count = 0;
foreach($service_array as $val){
	if(trim($val->directorate_code) == 'LC'){
		$lc_service_count = $lc_service_count+1;
	}
	if(trim($val->directorate_code) == 'B'){
		$boilers_service_count = $boilers_service_count+1;
	}
	if(trim($val->directorate_code) == 'F'){
		$factory_service_count = $factory_service_count+1;
	}
	if(trim($val->directorate_code) == 'S'){
		$shops_service_count = $shops_service_count+1;
	}
}


if($data->ldapplicationflag=='0'){
	$tmpdashboard='Y';
	
	return array('tmpdashboard'=>$tmpdashboard,'name'=>$name,'dob'=>$dob,'email'=>$email,'mobile'=>$mobile,'pincode'=>$pincode,'address'=>$address,'lc_service_count'=>$lc_service_count,'boilers_service_count'=>$boilers_service_count,'factory_service_count'=>$factory_service_count,'shops_service_count'=>$shops_service_count);
}
else
{
	$tmpdashboard='N';
	
	return array('tmpdashboard'=>$tmpdashboard,'name'=>$name,'dob'=>$dob,'email'=>$email,'mobile'=>$mobile,'pincode'=>$pincode,'address'=>$address);
}

}

function dashboard_ldfun($user_arr = NULL){
	
	$uid=$user_arr['uid'];
	$query = db_select('ld_users_details', 'us');
$query->leftJoin('users', 'u', 'u.uid=us.uid');
$query ->fields('us', array( 'fname','mname','lname','gender','dob','mobile','email','pincode','state','district','subdivision','areatype','block','panchayat','policestation','postoffice','address','ldapplicationflag'));
$query ->fields('u', array( 'name'));
$query->condition('us.uid',trim($uid),'=');
$result = $query->execute();
$data = $result->fetchObject();


$name=$data->name;
if(!empty($data->dob)){ $dob= format_date(strtotime($data->dob), 'custom', 'd-m-Y');}else{ $dob= "N/A";}
if(!empty($data->email)){ $email= $data->email;}else{ $email= "N/A";}
if(!empty($data->mobile)){ $mobile= $data->mobile;}else{ $mobile= "N/A";}
if(!empty($data->pincode)){ $pincode= $data->pincode;}else{ $pincode= "N/A";}
if(!empty($data->address)){ $address= $data->address;}else{ $address= "N/A";}

$fullname=$data->fname." ".$data->mname." ".$data->lname;



$query = db_select('ld_user_service_info', 'us');
$query->leftJoin('ld_service_master', 'sm', 'sm.id=us.service_id');
$query ->fields('sm', array( 'service_name','directorate_name','directorate_code'));
$query->condition('us.uid',trim($uid),'=');
$query->condition('sm.is_active','Y','=');
$service_data = $query->execute();
$service_array = $service_data->fetchAll();
$lc_service_count = 0;
$boilers_service_count = 0;
$factory_service_count = 0;
$shops_service_count = 0;
foreach($service_array as $val){
	if(trim($val->directorate_code) == 'LC'){
		$lc_service_count = $lc_service_count+1;
	}
	if(trim($val->directorate_code) == 'B'){
		$boilers_service_count = $boilers_service_count+1;
	}
	if(trim($val->directorate_code) == 'F'){
		$factory_service_count = $factory_service_count+1;
	}
	if(trim($val->directorate_code) == 'S'){
		$shops_service_count = $shops_service_count+1;
	}
}








if($data->ldapplicationflag=='0'){
	$tmpdashboard='Y';
	
	return array('tmpdashboard'=>$tmpdashboard,'name'=>$name,'dob'=>$dob,'email'=>$email,'mobile'=>$mobile,'pincode'=>$pincode,'address'=>$address,'error_code'=>0);
	
}
else
{
	
			$query = db_select('ld_user_service_info', 'us');
			$query->leftJoin('ld_service_master', 'sm', 'sm.id=us.service_id');
			$query->leftJoin('ld_act_master', 'a', 'a.id=us.act_id');
			$query->leftJoin('users', 'u', 'u.uid=us.uid');
			$query->leftJoin('ld_users_details', 'lud', 'lud.uid=us.uid');
			$query ->fields('a', array( 'act_title'));
			$query ->fields('u', array( 'name'));
			$query ->fields('us', array( 'id', 'uid','service_id','application_time'));
			$query ->fields('sm', array( 'service_name','directorate_name','directorate_code','service_type'));
			$query ->fields('lud', array( 'ld_pass' ));
			$query->condition('us.uid',trim($uid),'=');
			$query->condition('sm.directorate_code','B','=');
			$query->orderBy('us.service_id','ASC');
			$query->orderBy('sm.service_type','ASC');
			//echo $query; exit;
			$service = $query->execute();
			$servicedata = $service->fetchAll();
			foreach($servicedata as $key=>$val){
			if(trim($val->service_id)=='32' || trim($val->service_id) != '33'){
				$role='4';
			}else if(trim($val->service_id)=='35'){
				$role='9';
			}else if(trim($val->service_id)=='34'){
				$role='12';
			}else{
				$role=0;
			}
			}
			
			//print_r($servicedata);
			//echo $user->uid; 
			$service_url 	= 	"https://wbboilers.gov.in/labourdept/eservices/getEservicesStatusData";
			
			$ch 			= 	curl_init();
			$headers		=	array();
			$curl_post_data = 	array(
				"ld_uid"	=> $uid,
				 "role"    => $role
			);
			$headers[]		=	'Accept: application/json';
			$headers[]		=	'Content-Type: application/json';
			$headers[] 		= 	'charset=utf-8';
			curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
			curl_setopt($ch, CURLOPT_URL, $service_url);
			curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
			curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
			curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0); 
			curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 0);
			curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode( $curl_post_data ) );
			curl_setopt($ch, CURLOPT_POST, true);
			$results		=	curl_exec($ch);
			$errors			=	curl_error($ch);
			curl_close($ch);
			$x				=	json_encode( $results );
			$tmp 			= 	json_decode(json_decode(trim($x)), TRUE);
	
	
	if(!empty($servicedata)){
		 
				if(!empty($tmp['list'])){
						$newservicedata = array();
						//print_r($servicedata); exit;
						//print_r($tmp['list']); exit;
						$i=0;
						foreach($servicedata as $key=>$val){
							
							//foreach($tmp['list'] as $k=>$s){
								
								//echo $tmp['list']['boiler_enroll_no'];
								if($val->service_id == $tmp['list'][$i]['service_id']){
									//print_r($s);
									$newservicedata[$key]['user_service_info_id'] = $val->id;
									$newservicedata[$key]['act_title'] = $val->act_title;
									$newservicedata[$key]['name'] = $val->name;
									$newservicedata[$key]['uid'] = $val->uid;
									$newservicedata[$key]['service_id'] = $val->service_id;
									$newservicedata[$key]['application_time'] = $val->application_time;
									$newservicedata[$key]['service_name'] = $val->service_name;
									$newservicedata[$key]['service_type'] = $val->service_type;
									$newservicedata[$key]['directorate_name'] = $val->directorate_name;
									$newservicedata[$key]['directorate_code'] = $val->directorate_code;
									$newservicedata[$key]['ld_pass'] = $val->ld_pass;
									
									
									$newservicedata[$key]['e_name'] = $tmp['list'][$i]['factory_name'];
									$newservicedata[$key]['status'] = $tmp['list'][$i]['status'];
									//$newservicedata[$key]['final_submit_status'] =$s[0]['final_submit_status'];
									$newservicedata[$key]['application_date'] =$tmp['list'][$i]['payment_date'];
									
									$newservicedata[$key]['l_status'] = $tmp['list'][$i]['l_status'];
									$newservicedata[$key]['inspector_approval'] = $tmp['list'][$i]['inspector_approval'];
									$newservicedata[$key]['boiler_enroll_no'] = $tmp['list'][$i]['boiler_enroll_no'];
									$newservicedata[$key]['seen_status'] = $tmp['list'][$i]['seen_status'];
									
									$i++;
									
									/*$servicedata[$key]['e_name'] = $s[0]['e_name'];
									$servicedata[$key]['status'] = $s[0]['status'];
									$servicedata[$key]['final_submit_status'] = $s[0]['final_submit_status'];
									$servicedata[$key]['act_id'] = $s[0]['act_id'];
									$servicedata[$key]['application_date'] = $s[0]['application_date'];*/
								}else{
									$newservicedata[$key]['user_service_info_id'] = $val->id;
									$newservicedata[$key]['act_title'] = $val->act_title;
									$newservicedata[$key]['name'] = $val->name;
									$newservicedata[$key]['uid'] = $val->uid;
									$newservicedata[$key]['service_id'] = $val->service_id;
									$newservicedata[$key]['application_time'] = $val->application_time;
									$newservicedata[$key]['service_name'] = $val->service_name;
									$newservicedata[$key]['service_type'] = $val->service_type;
									$newservicedata[$key]['directorate_name'] = $val->directorate_name;
									$newservicedata[$key]['directorate_code'] = $val->directorate_code;
									$newservicedata[$key]['ld_pass'] = $val->ld_pass;
									
									$newservicedata[$key]['e_name'] = 'Not Assigned';
									$newservicedata[$key]['status'] = 'Not Assigned';
									$newservicedata[$key]['final_submit_status'] ='Not Assigned';
									$newservicedata[$key]['act_id'] = 'Not Assigned';
									$newservicedata[$key]['application_date'] = 'Not Assigned';
									
									$newservicedata[$key]['l_status'] = 'Not Assigned';
									$newservicedata[$key]['inspector_approval'] = 'Not Assigned';
									$newservicedata[$key]['boiler_enroll_no'] = '';
									$newservicedata[$key]['seen_status'] = 'Not Assigned';
									
								}
							//}
							
						}
						//print_r($newservicedata); exit;
						
						foreach($newservicedata as $key=>$tmp){
							
							if($tmp['service_id']=='32')
							{
							
							if($tmp['status'] < '5' && $tmp['status']>0){
							//$current_status = 'Pending';
							$linkText = 'View Details';
							$current_status = 'Pending';
						}	
						elseif($tmp['status'] == '5' && $tmp['l_status']=='0'){
							//$current_status = 'Pay Now';
							$current_status = 'Pay Now';
							$linkText = 'View Details';
							
							
							/*$query_chk_rating = db_select('ld_user_service_star_rating', 'ur');
							$query_chk_rating ->fields('ur', array( 'id' ));
							$query_chk_rating->condition('ur.uid',trim($user->uid),'=');
							$query_chk_rating->condition('ur.user_service_info_id',$tmp['user_service_info_id'],'=');
							$rating = $query_chk_rating->execute();
							$ratingdata = $rating->fetchAssoc();
							if(empty($ratingdata)){
								$rating 		= 	array(
									'uid' 			=> $user->uid,
									'user_service_info_id' 	=> $tmp['user_service_info_id'], 
									'rating' 		=> 0, 
								);
								db_insert('ld_user_service_star_rating')->fields($rating)->execute();
							}*/
							
						}
						elseif($tmp['status'] == '5' && $tmp['l_status']=='1' && $tmp['inspector_approval']=='0'){
							//$current_status = 'Applied';
							$current_status = 'Applied';
							$linkText = 'View Details';
							//$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/backed.png" alt="" title="">';
						}
						elseif($tmp['status'] == '5' && $tmp['l_status']=='1' && $tmp['inspector_approval']=='1'){
							$current_status = 'Verified';
							$linkText = 'View Details';
							//$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/applicant_called_by.png" alt="" title="Verified">';
						}
						/*elseif($tmp['list'][$key][0]['status'] == '5'){
							$current_status = 'Inspection Ongoing';
							
						}*/
						elseif($tmp['status'] == '6'){
							//$current_status = 'Registered(Download Certificate)';
							$current_status = 'Download Certificate';
							$linkText = 'View Details';
							//$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/forward.png" alt="" title="Download Certificate">';
						}
						
						else{
							$current_status = 'Not Assigned';
							$linkText = 'View Details';
						}
							}
							
							else if($tmp['service_id']=='33')
							{
								
								if($tmp['status'] =='0' && $tmp['l_status']==0){
							     $current_status = 'Pay Now';
								 $linkText = 'View Details';
								}
								else if($tmp['status'] =='0' && $tmp['l_status']==1)
								{
									 $current_status = 'Applied';
									 $linkText = 'View Details';
								}
								
								else if($tmp['status'] =='0' && $tmp['seen_status']==1)
								{
									 $current_status = 'Verifird';
									 $linkText = 'View Details';
								}
								else if($tmp['status'] =='1' && $tmp['seen_status']==1)
								{
									 $current_status = 'Compled';
									 $linkText = 'View Details';
								}
								else
							   {
								$current_status = 'Not Assigned';
								$linkText = 'View Details';
							    }
								
								
							}
							else
							{
								$current_status = 'Not Assigned';
								$linkText = 'Apply Online';
							}
					
						//echo "test ".$servicedata->service_name;
					
                 
                    $e_name= $tmp['e_name']; 
                    $service_name= $tmp['service_name'];
                   if($tmp['service_type']=="1"){ $service_type= "Pre-Establishement";}
				   else if($tmp['service_type']=="2"){$service_type= "Pre-Operation";}
				   else if($tmp['service_type']=="3"){$service_type= "Others";}
				   else{echo "--";}
                   $application_date= !empty($tmp['application_date'])? format_date(strtotime($tmp['application_date']), 'custom', 'd-m-Y') : "--" ;
                   $current_status2= $current_status;
                 
                    if($tmp['status'] != '6' ){ 
					if($tmp['service_id']=='32' || $tmp['service_id']=='33' || $tmp['service_id']=='34' || $tmp['service_id']=='35'){
				
                   /* $link="https://wbboilers.gov.in/application-edit/encryption_decryption_wblabour('encrypt', $tmp['name'])/encryption_decryption_wblabour('encrypt', $tmp['ld_pass'])./. encryption_decryption_wblabour('encrypt', $tmp['service_id'])./.  encryption_decryption_wblabour('encrypt', $tmp['boiler_enroll_no'])";*/
					
					 $link="https://wbboilers.gov.in/application-edit/".encryption_decryption_wblabour('encrypt', $tmp['name'])."/".encryption_decryption_wblabour('encrypt', $tmp['ld_pass'])."/".encryption_decryption_wblabour('encrypt', $tmp['service_id'])."/". encryption_decryption_wblabour('encrypt', $tmp['boiler_enroll_no']);
					
					}
					else
					{
					
                         $link="Coming Soon";
                       
					}
					
					
					}
					//&& ($tmp['service_id']!='32' && $tmp['service_id']!='33')
					else{ 
					
					 $service_url 	= 	"https://wbboilers.gov.in/labourdept/eservices/downloadCert";
			
					$ch 			= 	curl_init();
					$headers		=	array();
					$curl_post_data2 = 	array(
							"boiler_enroll_no"	=> $tmp['boiler_enroll_no']
						   
					);
					$headers[]		=	'Accept: application/json';
					$headers[]		=	'Content-Type: application/json';
					$headers[] 		= 	'charset=utf-8';
					curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
					curl_setopt($ch, CURLOPT_URL, $service_url);
					curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
					curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
					curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0); 
					curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 0);
					curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode( $curl_post_data2 ) );
					curl_setopt($ch, CURLOPT_POST, true);
					$results		=	curl_exec($ch);
					$errors			=	curl_error($ch);
					curl_close($ch);
					$x				=	json_encode( $results );
					$tmp2			= 	json_decode(json_decode(trim($x)), TRUE);
					
					
					
                    $link2=$tmp2['link'];
                     } 
                   $i++;}
				  
				  
				   $servicesarray[] = array('e_name'=> $e_name,'service_name'=> $service_name,'service_type'=>$service_type,'application_date'=>$application_date,'current_status'=>$current_status,'link'=>$link);
				  
				}else{
				
				foreach($servicedata as $val){
                
                $service_name= $val->service_name;
                 if($val->service_type=="1"){ $service_type= "Pre-Establishement";}else if($val->service_type=="2"){$service_type= "Pre-Operation";}else if($val->service_type=="3"){$service_type= "Others";}else{$service_type= "--";}
                  
           $link="https://wbboilers.gov.in/application-edit/".encryption_decryption_wblabour('encrypt', $val->name)."/".encryption_decryption_wblabour('encrypt', $val->ld_pass)."/".encryption_decryption_wblabour('encrypt', $val->service_id); 
				  
				    /*<td class="last" align="center"> <a class="icon-table" target="_blank" href="https://wbboilers.gov.in/application-edit/<?php echo encryption_decryption_wblabour('encrypt', $val->name); ?>/<?php echo encryption_decryption_wblabour('encrypt', $val->ld_pass); ?>/<?php echo encryption_decryption_wblabour('encrypt', $val->service_id); ?>"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a> */
           
  				 $servicesarray[] = array('e_name'=> '','service_name'=>$service_name,'service_type'=>$service_type,'application_date'=>'','current_status'=>'','link'=>$link);
                
                 	}
				  }/*else{ ?>
                	<tr class="even pointer">
                      	<td colspan="6" class=" ">Not Data Found</td>
                    </tr>
                <?php } */
				 }
	

	
	$tmpdashboard='N';
	
	return array('tmpdashboard'=>$tmpdashboard,'error_code'=>0,'fullname'=>$fullname,'clinid'=>$name,'dob'=>$dob,'email'=>$email,'mobile'=>$mobile,'pincode'=>$pincode,'address'=>$address,'lc_service_count'=>$lc_service_count,'boilers_service_count'=>$boilers_service_count,'factory_service_count'=>$factory_service_count,'shops_service_count'=>$shops_service_count,'servicesarray'=>$tmp);
	
	
}

}

?>