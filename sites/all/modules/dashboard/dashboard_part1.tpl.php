<?php global $user,$base_root,$base_path,$base_url;
	$authkay=$user->sid;
	$user_name=$user->name;
	/*print_r($user);
	exit;
*/


?>

<?php if($_REQUEST['frmsubmt'] == 'frmsubmt' && $_REQUEST['user_servive_info_id']!=""){
	$query_rating = db_update('ld_user_service_star_rating');
	$query_rating->fields(array('rating'=>$_REQUEST['rating'][0]));
	$query_rating->condition('uid',trim($user->uid),'=');
	$query_rating->condition('user_service_info_id',trim($_REQUEST['user_servive_info_id']),'=');
	$rs = $query_rating->execute();
}

if($_REQUEST["addservice_submit"] == "addservice" && $_REQUEST["user_id"]==$user->uid){
	$arr_service   = array();
	foreach($_REQUEST['chk_add_service'] as $val){
		$arr_service   	= explode("_",$val);
		$service_id 	= $arr_service[0];
		$act_id 		= $arr_service[1];
		
		$d = date('Y-m-d H:i:s');
		$newService 		= 	array(
			'uid' 			=> $user->uid,
			'service_id' 	=> $service_id, 
			'act_id' 		=> $act_id, 
			'application_time' => $d,
		);
		
		db_insert('ld_user_service_info')->fields($newService)->execute();
	}
}
?>

<?php
$query = db_select('ld_users_details', 'us');
$query->leftJoin('users', 'u', 'u.uid=us.uid');
$query ->fields('us', array( 'fname','mname','lname','gender','dob','mobile','email','pincode','state','district','subdivision','areatype','block','panchayat','policestation','postoffice','address','ldapplicationflag'));
$query ->fields('u', array( 'name'));
$query->condition('us.uid',trim($user->uid),'=');
$result = $query->execute();
$data = $result->fetchObject();
if($data->ldapplicationflag=='0'){
	drupal_goto('tmpdashboard');
}


$query = db_select('ld_user_service_info', 'us');
$query->leftJoin('ld_service_master', 'sm', 'sm.id=us.service_id');
$query ->fields('sm', array( 'service_name','directorate_name','directorate_code'));
$query->condition('us.uid',trim($user->uid),'=');
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
?>
<style>
.wizard_steps a {background:none;color:#34495e !important;}
.small_line ul.wizard_steps li a::before {top:8px !important;}
.small_circle {width: 20px !important;height: 20px !important;line-height: 20px !important;}
.myalign > tbody > tr > td {vertical-align:middle;}
.icon-table{width: 100%; }
.icon-legend h2{text-transform:capitalize;text-align: center;margin: 50px 0 20px;}
.icon-legend .icon-table img{ width:35px; float:left; margin:0 10px; }
.icon-legend .icon-table span{ line-height:30px !important; text-transform:capitalize;font-weight: 600;font-size: 12px;color: #8d8d8d;}
.icon-legend .icon-table tbody tr:hover td{ background:none !important; border-top: 1px solid #ddd !important; border-bottom: 1px solid #ddd !important;}
.icon-legend .icon-table tbody > tr:nth-of-type(2n+1){ background:none !important;border-top: 1px solid #ddd !important; }
.icon-legend .icon-table tbody > tr > td {border-left: 1px solid #ddd;padding: 5px;}
.widthfix{ width:45%;}

#accordion .table > thead > tr > th{font-size: 13px;}
#accordion .panel-body {padding: 0;}
#accordion .glyphicon.pull-right {margin-top: -15px;}

.accordion .panel-heading {border-bottom: 1px solid #D9DEE4 !important;margin-bottom: 10px;display: block;color: #fff!important; background-color: #016090 !important;}

table.jambo_table thead {/* background: rgba(52, 73, 94, 0.67); */color: #fff!important;background-color: #92a9d2 !important;}
.buttondashboardstar{ width:95% !important; padding:0px !important; text-align:left !important;/* fallback for old browsers */color: #666; font-weight:bold;}

@media (max-width:767px){
.icon-legend .icon-table tbody > tr > td { text-align: center;}	
.icon-legend .icon-table img {float: none;display: inline-block;}
.icon-legend .icon-table span {display: block;}
}

</style>

<link href="<?php print $base_root.$base_path ?>sites/all/modules/ssdg_flow/css/checkbox-x.css" rel="stylesheet">
<!-- Bootstrap -->
<!--<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/bootstrap/dist/css/bootstrap.min.css" rel="stylesheet">-->
<!-- Font Awesome -->
<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/font-awesome/css/font-awesome.min.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/font-awesome/css/font-awesome.css" rel="stylesheet">
<!-- NProgress -->
<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/nprogress/nprogress.css" rel="stylesheet">
<!-- iCheck -->
<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/iCheck/skins/flat/green.css" rel="stylesheet">

<!-- bootstrap-progressbar -->
<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/bootstrap-progressbar/css/bootstrap-progressbar-3.3.4.min.css" rel="stylesheet">
<!-- JQVMap -->
<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/jqvmap/dist/jqvmap.min.css" rel="stylesheet"/>
<!-- bootstrap-daterangepicker -->
<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/bootstrap-daterangepicker/daterangepicker.css" rel="stylesheet">

<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/build/css/star_rating.css" rel="stylesheet">

<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/build/css/tmpdashboard.css" rel="stylesheet">
<!-- Custom Theme Style -->
<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/build/css/custom.css" rel="stylesheet">

<body class="nav-md" onLoad="init_chart_doughnut_edit('<?php echo $lc_service_count?>','<?php echo $boilers_service_count?>','<?php echo $factory_service_count?>','<?php echo $shops_service_count?>')">
<div class="row">
 <h4 class="brief"><i>Welcome on Board</i></h4>
  <div class="col-md-8 col-sm-8 col-xs-12 profile_details">
    <div class="col-sm-12">
      <div class="right col-xs-5 text-center">
        <!--<div class="text-center myprofilepic"> 
        <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/user.png" alt="" class="img-circle img-responsive#"></div>-->
        <div class="sidebar-widget">
        	<h2><?php if(!empty($data->fname) && (!empty($data->lname))){echo $data->fname." ".$data->mname." ".$data->lname;}else{ echo "N/A";}?></h2>
          <!--<canvas width="150" height="80" id="chart_gauge_01" class="" style="width: 160px; height: 100px;"></canvas>-->
          <?php /*?><canvas width="150" height="80" id="chart_gauge_01" class="custom-spedo-meter"></canvas>
          <div class="goal-wrapper"> <span id="gauge-text" class="gauge-value pull-left">0</span> <span class="gauge-value pull-left">%</span> <span id="goal-text" class="goal-value pull-right">100%</span> </div>
          <h4>Profile Completion</h4><?php */?>
        </div>
      </div>
      <div class="left col-xs-7">
        
        <div class="temporary-id-panel">
        <div class="temporary-id">CLIN ID -<?php if(!empty($data->name)){ echo $data->name;}else{ echo "N/A";}?></div>
        </div>
        <table class="data table table-striped no-margin">
          <thead>
          	<!--<tr>
              <th><a href="<?php print $base_root.$base_path ?>change-password">Change Password</a>
                </li></th>
            </tr>-->
            <!--<tr>
              <th><i class="fa fa-birthday-cake"></i> DOB : <?php if(!empty($data->dob)){ echo format_date(strtotime($data->dob), 'custom', 'd-m-Y');}else{ echo "N/A";}?>
                </li></th>
            </tr>-->
            <tr>
              <th><i class="fa fa-envelope"></i> Email : <?php if(!empty($data->email)){ echo $data->email;}else{ echo "N/A";}?></th>
            </tr>
            <tr>
              <th><i class="fa fa-phone"></i> Phone : <?php if(!empty($data->mobile)){ echo $data->mobile;}else{ echo "N/A";}?></th>
            </tr>
            <tr>
              <th class="hidden-phone"><i class="fa fa-map-marker"></i> Pin : <?php if(!empty($data->pincode)){ echo $data->pincode;}else{ echo "N/A";}?></th>
            </tr>
            <tr>
              <th><i class="fa fa-building"></i> Address: <?php if(!empty($data->address)){ echo $data->address;}else{ echo "N/A";}?></th>
            </tr>
          </thead>
        </table>
      </div>
    </div>
  </div>
  <div class="col-md-4 col-sm-4 col-xs-12">
  	<!--<div class="x_panel tile fixed_height_320 overflow_hidden">-->
    <div class="x_panel tile overflow_hidden">
      <div class="x_title">
        <h2 class="service-info-title">Services &nbsp;&nbsp;
        	<a href="#" data-toggle="modal" data-target="#myModalAddService">[+ Add Services]</a>
        </h2>
        <div class="clearfix"></div>
      </div>
      <div class="x_content graphbrdr">
        <table class="" style="width:100%">
          <tr>
            <td><canvas class="canvasDoughnut" height="140" width="140" style="margin-left:25%"></canvas></td></tr>
            <tr>
            <td><table class="tile_info">
                <tr>
                  <td><p><i class="fa fa-square blue"></i>Labour Commissionerate</p></td>
                  <td><?php echo $lc_service_count;?></td>
                </tr>
                <tr>
                  <td><p><i class="fa fa-square red"></i>Directorate of Boilers</p></td>
                  <td><?php echo $boilers_service_count;?></td>
                </tr>
                <tr>
                  <td><p><i class="fa fa-square green-new"></i>Directorate of Factories</p></td>
                  <td><?php echo $factory_service_count;?></td>
                </tr>
                <!--<tr>
                  <td><p><i class="fa fa-square purple"></i>Directorate of Shops </p></td>
                  <td><?php echo $shops_service_count;?></td>
                </tr>-->
                <!--<tr>
                  <td><p><i class="fa fa-square green-new"></i>INFORMATION </p></td>
                  <td>10%</td>
                </tr>-->
              </table></td>
          </tr>
        </table>
      </div>
    </div>
  </div>
  <div class="col-md-12 col-sm-12 col-xs-12">
    <div class="x_content">
      <div class="accordion" id="accordion" role="tablist" aria-multiselectable="true">
      
      <!-- Boilers section start-->
      
      <?php
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
			$query->condition('us.uid',trim($user->uid),'=');
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
				"ld_uid"	=> $user->uid,
				 "role"    =>$role
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
			$boiler 			= 	json_decode(json_decode(trim($x)), TRUE);
			//$tmp=print_r(json_decode($results)); //exit;
			/*print_r($tmp);
			exit;*/
			
			
			
			//factory 
			//https://wbfactoryonline.in/webservices/REST/getEservicesStatusData
			 //https://wbshopsonline.in/webservices/REST/getEservicesStatusData 
			
			
			
			
			/*$service_url 	= 	"https://wbshopsonline.in/webservices/REST/getEservicesStatusData";
			
			$ch 			= 	curl_init();
			$headers		=	array();
			$curl_post_data = 	array(
				"user_name"	=> $user->uid,
				 "role"    =>$role
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
			$tmp 			= 	json_decode(json_decode(trim($x)), TRUE);*/
			
			
			$i = 0;
			
			if(!empty($servicedata)){
		  ?>
          
        <div class="panel"> 
        <a class="panel-heading collapsed" role="tab" id="headingOne" data-toggle="collapse" data-parent="#accordion" href="#collapseOne" aria-expanded="true" aria-controls="collapseOne">
          <h4 class="panel-title">Directorate of Boilers</h4><span class="glyphicon glyphicon-minus pull-right"></span>
          </a>
          <div id="collapseOne" class="panel-collapse collapse in" role="tabpanel" aria-labelledby="headingOne">
            <div class="panel-body">
            <div class="table-responsive">
              <table class="table table-striped jambo_table bulk_action myalign">
                <thead>
                  <tr class="headings">
                    <th class="column-title">Establishment Name</th>
                    <th class="column-title widthfix">Service Name </th>
                    <th class="column-title" style="text-align:center;">Category </th>
                    <th class="column-title">Application Date</th>
                    <th class="column-title" style="text-align:center;">Application Status </th>
                    <th class="column-title no-link last" style="text-align:center;">Action</th>
                  </tr>
                </thead>
                <tbody>
                <?php 
				
				
				
				
				
				
				
				
				
				//echo count($tmp['list']).'---'.count($servicedata); // no of records returned from boiler end
				/*echo '<pre>';
				 print_r($tmp['list']); 
				  echo '<pre>';
				 print_r($servicedata);*/ 	
				
				/*$ld_serv_id_arr = array();
				$boiler_serv_id_arr = array();
				
				
					foreach($servicedata as $val1){
						array_push($ld_serv_id_arr,$val1->service_id);
					}					
					foreach($tmp['list'] as $val2){
						array_push($boiler_serv_id_arr,$val2['service_id']);
					}
					sort($ld_serv_id_arr);
					sort($boiler_serv_id_arr);
					
					
					print_r($ld_serv_id_arr);
					print_r($boiler_serv_id_arr);*/
					
				/*echo count($servicedata).'-----------'.count($tmp['list']);
				
				if(count($servicedata) > count($tmp['list'])){
					//do nothing
				}else if(count($servicedata) <= count($tmp['list'])){
					foreach($tmp['list'] as $v1){
						for($i = 0; $i<count($servicedata); $i++){
							if($v1['service_id'] == $servicedata[$i]->service_id)
								echo 'matched---'.$v1['service_id'].'------'.$servicedata[$i]->service_id;
								unset($servicedata[$i]);
						}
					}
					print_r($servicedata); die;
					
					for($i = 0; $i < count($tmp['list']); $i++){
						$field_arr[] = array('uid' => $user->uid, 'service_id' => $tmp['list'][$i]['service_id'], 'application_time' => now(), 'act_id' => 0);
						//db_insert('ld_user_service_info')->fields($field_arr)->execute();
					}
				}
				
				print_r($field_arr); exit;*/
				
				
				if(!empty($boiler['list'])){
						$newservicedata = array();
						//echo "<pre>";
						//print_r($servicedata); exit;
						//print_r($tmp['list']); exit;
						$i=0;
						
						for($j=0;$j<sizeof($servicedata);$j++){
							
							//echo "service_id-->".$servicedata[$j]->service_id."<br>";
							 for($k=0; $k<sizeof($boiler['list']); $k++){
								 
								  //echo "service_id-->".$servicedata[$j]->id."<br>"; 
								  //echo "unique_id-->".$boiler['list'][$k]['ld_service_unique_id']."<br>"; 
								  
								 if(trim($servicedata[$j]->id) == trim($boiler['list'][$k]['ld_service_unique_id'])){
									$newservicedata[$j]['user_service_info_id'] = $servicedata[$j]->id;
									$newservicedata[$j]['act_title'] = $servicedata[$j]->act_title;
									$newservicedata[$j]['name'] = $servicedata[$j]->name;
									$newservicedata[$j]['uid'] = $servicedata[$j]->uid;
									$newservicedata[$j]['service_id'] = $servicedata[$j]->service_id;
									$newservicedata[$j]['application_time'] = $servicedata[$j]->application_time;
									$newservicedata[$j]['service_name'] = $servicedata[$j]->service_name;
									$newservicedata[$j]['service_type'] = $servicedata[$j]->service_type;
									$newservicedata[$j]['directorate_name'] = $servicedata[$j]->directorate_name;
									$newservicedata[$j]['directorate_code'] = $servicedata[$j]->directorate_code;
									$newservicedata[$j]['ld_pass'] = $servicedata[$j]->ld_pass;
									
									$newservicedata[$j]['e_name'] = $boiler['list'][$k]['factory_name'];
									$newservicedata[$j]['status'] = $boiler['list'][$k]['status'];
									//$newservicedata[$j]['final_submit_status'] = $tmp['list'][$k][0]['final_submit_status'];
									$newservicedata[$j]['application_date'] = $boiler['list'][$k]['payment_date'];
									$newservicedata[$j]['l_status'] = $boiler['list'][$k]['l_status'];
									$newservicedata[$j]['inspector_approval'] = $boiler['list'][$k]['inspector_approval'];
									$newservicedata[$j]['boiler_enroll_no'] = $boiler['list'][$k]['boiler_enroll_no'];
									$newservicedata[$j]['repairer_enroll_no'] = $boiler['list'][$k]['repairer_enroll_no'];
									$newservicedata[$j]['seen_status'] = $boiler['list'][$k]['seen_status'];
									
									break;
									//continue;
									
								 }else{
									 //echo "inside"; exit;
									 
									 
									 
									$newservicedata[$j]['user_service_info_id'] = $servicedata[$j]->id;
									$newservicedata[$j]['act_title'] = $servicedata[$j]->act_title;
									$newservicedata[$j]['name'] = $servicedata[$j]->name;
									$newservicedata[$j]['uid'] = $servicedata[$j]->uid;
									$newservicedata[$j]['service_id'] = $servicedata[$j]->service_id;
									$newservicedata[$j]['application_time'] = $servicedata[$j]->application_time;
									$newservicedata[$j]['service_name'] = $servicedata[$j]->service_name;
									$newservicedata[$j]['service_type'] = $servicedata[$j]->service_type;
									$newservicedata[$j]['directorate_name'] = $servicedata[$j]->directorate_name;
									$newservicedata[$j]['directorate_code'] = $servicedata[$j]->directorate_code;
									$newservicedata[$j]['ld_pass'] = $servicedata[$j]->ld_pass;
									
									$newservicedata[$j]['e_name'] = 'Not Assigned';
									$newservicedata[$j]['status'] = 'Not Assigned';
									//$newservicedata[$j]['final_submit_status'] = $tmp['list'][$k][0]['final_submit_status'];
									$newservicedata[$j]['application_date'] = 'Not Assigned';
									$newservicedata[$j]['l_status'] = 'Not Assigned';
									$newservicedata[$j]['inspector_approval'] = 'Not Assigned';
									$newservicedata[$j]['boiler_enroll_no'] = 'Not Assigned';
									$newservicedata[$j]['repairer_enroll_no'] = 'Not Assigned';
									$newservicedata[$j]['seen_status'] = 'Not Assigned';
									
									 
								 }
								 
							 }
						}
						
						
						
						
						
						
						
						
						
						
						//print_r($newservicedata); exit;
						
						foreach($newservicedata as $key=>$tmp){
							if($tmp['service_id']=='32')
							{
							if($tmp['status'] < '5' && $tmp['status']>0){
							//$current_status = 'Pending';
							$linkText = 'View Details';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/pending.png" alt="" title="Pending">';
						}	
						
						elseif($tmp['status'] == '5' && $tmp['l_status']=='0'){
							//$current_status = 'Pay Now'; exit;
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/paynow.png" alt="" title="Pay Now">';
							$linkText = 'View Details';
							
							
							$query_chk_rating = db_select('ld_user_service_star_rating', 'ur');
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
							}
							
						}
						elseif($tmp['status'] == '5' && $tmp['l_status']=='1' && $tmp['inspector_approval']=='0'){
							//$current_status = 'Applied';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/applied.png" alt="" title="Applied">';
							$linkText = 'View Details';
							//$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/backed.png" alt="" title="">';
						}
						elseif($tmp['status'] == '5' && $tmp['l_status']=='1' && $tmp['inspector_approval']=='1'){
							//$current_status = 'Verified';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/verification.png" alt="" title="Verified">';
							$linkText = 'View Details';
							//$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/applicant_called_by.png" alt="" title="Verified">';
						}
						/*elseif($tmp['list'][$key][0]['status'] == '5'){
							$current_status = 'Inspection Ongoing';
							
						}*/
						elseif($tmp['status'] == '6'){
							//$current_status = 'Registered(Download Certificate)';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/issued.png" alt="" title="Download Certificate">';
							$linkText = 'View Details';
							$renewCertificate = '<a class="icon-table" target="_blank" href="https://wbboilers.gov.in/ld-application-redirect/'.encryption_decryption_wblabour('encrypt', $tmp['name']).'/'.encryption_decryption_wblabour('encrypt', $tmp['ld_pass']).'/'.encryption_decryption_wblabour('encrypt', '33').'/'.encryption_decryption_wblabour('encrypt', $tmp['boiler_enroll_no']).'/'.encryption_decryption_wblabour('encrypt', $tmp['user_service_info_id']).'">Renew</a>';
							//$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/forward.png" alt="" title="Download Certificate">';
						}
						
						else{
							$current_status = 'Not Assigned';
							$linkText = 'Apply Online';
						}
							}
							
							else if($tmp['service_id']=='33')
							{
								//echo "inside"; exit;
								
								if($tmp['status'] =='0' && $tmp['l_status']==0){
							     //$current_status = 'Pay Now';
								 $current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/paynow.png" alt="" title="Pay Now">';
								 $linkText = 'View Details';
								}
								else if($tmp['status'] =='1' && $tmp['l_status']==1)
								{
									// $current_status = 'Applied';
									$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/applied.png" alt="" title="Applied">';
									 $linkText = 'View Details';
								}
								
								else if($tmp['status'] =='0' && $tmp['seen_status']==1)
								{
									 //$current_status = 'Verified';
									 $current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/verification.png" alt="" title="Verified">';
									 $linkText = 'View Details';
								}
								else if($tmp['status'] =='1' && $tmp['seen_status']==1)
								{
									 $current_status = 'Completed';
									 $linkText = 'View Details';
								}
								else
							   {
								$current_status = 'Not Assigned';
								$linkText = 'Apply Online';
							    }
								
								
							}
							else
							{
								$current_status = 'Not Assigned';
								$linkText = 'Apply Online';
							}
					
						//echo "test ".$servicedata->service_name;
					?>
                  <tr class="even pointer">
                    <td class=" "><?php echo $tmp['e_name']; ?></td>
                    <td class=" "><?php echo $tmp['service_name'];?></td>
                    <td class=" "><?php if($tmp['service_type']=="1"){ echo "Pre-Establishement";}else if($tmp['service_type']=="2"){echo "Pre-Operation";}else if($tmp['service_type']=="3"){echo "Others";}else{echo "--";}?></td>
                    <td class=" "><?php echo !empty($tmp['application_date'])? format_date(strtotime($tmp['application_date']), 'custom', 'd-m-Y') : "--" ;?></td>
                    <td class=" "><div class="status-icon"><?php echo $current_status;?></div><?php if($tmp['status'] == '6' ){if($tmp['service_id']=='32'){echo $renewCertificate;}}?></td>
                    <td class="last" align="center">
                    <?php if($tmp['status'] != '6' ){ 
					if($tmp['service_id']=='32' || $tmp['service_id']=='34'){
					?>
                    <a class="icon-table" target="_blank" href="https://wbboilers.gov.in/ld-application-redirect/<?php echo encryption_decryption_wblabour('encrypt', $tmp['name']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['ld_pass']); ?>/<?php echo  encryption_decryption_wblabour('encrypt',$tmp['service_id']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['boiler_enroll_no']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['user_service_info_id']); ?>"><img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png"><?php echo $linkText;?></a> 
                    
                    <?php 
					}else if($tmp['service_id']=='33'){?>
						<a class="icon-table" target="_blank" href="https://wbboilers.gov.in/ld-application-redirect/<?php echo encryption_decryption_wblabour('encrypt', $tmp['name']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['ld_pass']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['service_id']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['boiler_enroll_no']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['user_service_info_id']); ?>"><img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png"><?php echo $linkText;?></a>
				<?php }elseif($tmp['service_id']=='35'){?>
						
						<a class="icon-table" target="_blank" href="https://wbboilers.gov.in/ld-application-redirect/<?php echo  encryption_decryption_wblabour('encrypt', $tmp['name']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['ld_pass']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['service_id']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['repairer_enroll_no']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['user_service_info_id']); ?>"><img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png"><?php echo $linkText;?></a>
				<?php }
					else
					{
						?>
                          <a class="icon-table" href="#"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/coming_soon.png" >Coming Soon</a>
                        <?php
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
					
					
					?>
                    
                     <a class="icon-table" target="_blank" href="<?php echo $tmp2['link'];?>"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/download-icon.png" title="Download Certificate">Download</a>
                    
                    <?php } ?>
                    </td>
                  </tr> 
                  <?php $i++;}
				  
				  
				}else{
				
				foreach($servicedata as $val){?>
                  <tr class="even pointer">
                    <td class=" ">Not Assigned</td>
                    <td class=" "><?php echo $val->service_name;?></td>
                    <td class=" "><?php if($val->service_type=="1"){ echo "Pre-Establishement";}else if($val->service_type=="2"){echo "Pre-Operation";}else if($val->service_type=="3"){echo "Others";}else{echo "--";}?></td>
                    <td class=" ">Not Assigned</td>
                    <td class="">Not Assigned</td>
                    <?php if($val->service_id!="35"){?>
                    <td class="last" align="center"> <a class="icon-table" target="_blank" href="https://wbboilers.gov.in/ld-application-redirect/<?php echo encryption_decryption_wblabour('encrypt', $val->name); ?>/<?php echo encryption_decryption_wblabour('encrypt', $val->ld_pass); ?>/<?php echo encryption_decryption_wblabour('encrypt', $val->service_id); ?>/<?php echo encryption_decryption_wblabour('encrypt', 'Not Assigned'); ?>/<?php echo encryption_decryption_wblabour('encrypt', $val->id); ?>"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a> 
                      </td>
                      <?php }else{?>
                      <td>
                      	<a class="icon-table" target="_blank" href="https://wbboilers.gov.in/ld-application-redirect/<?php echo  encryption_decryption_wblabour('encrypt', $tmp['name']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['ld_pass']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['service_id']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['repairer_enroll_no']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['user_service_info_id']); ?>"><img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png"><?php echo $linkText;?></a>
                      </td>
                      <?php }?>
                  </tr>
                  <?php }
				  }/*else{ ?>
                	<tr class="even pointer">
                      	<td colspan="6" class=" ">Not Data Found</td>
                    </tr>
                <?php } */?>
                </tbody>
              </table>
            </div>
            </div>
          </div>
        </div>
         <?php }?>
        <!-- Boilers section End-->
        
        <!-- LC Section-->
       <?php
			$query = db_select('ld_user_service_info', 'us');
			$query->leftJoin('ld_service_master', 'sm', 'sm.id=us.service_id');
			$query->leftJoin('ld_act_master', 'a', 'a.id=us.act_id');
			$query->leftJoin('users', 'u', 'u.uid=us.uid');
			$query->leftJoin('ld_users_details', 'lud', 'lud.uid=us.uid');
			$query ->fields('a', array( 'act_title'));
			$query ->fields('u', array( 'name'));
			$query ->fields('us', array( 'id','uid','service_id','application_time'));
			$query ->fields('sm', array( 'service_name','directorate_name','directorate_code','service_type','coming_soon'));
			$query ->fields('lud', array( 'ld_pass' ));
			$query->condition('sm.is_active','Y','=');
			$query->condition('us.uid',trim($user->uid),'=');
			$query->condition('sm.directorate_code','LC','=');
			$query->orderBy('sm.service_type','ASC');
			
			//echo $query; exit;
			$service = $query->execute();
			$servicedatalc = $service->fetchAll();
			//print_r($servicedatalc); exit;
			//echo $user->uid; 
			$service_url 	= 	"https://wblc.gov.in/labourdept/eservices/getEservicesStatusData";
			$ch 			= 	curl_init();
			$headers		=	array();
			$curl_post_data = 	array(
				"ld_uid"	=> $user->uid
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
			//print_r($tmp);
			//exit;
			$i = 0;
			
			if(!empty($servicedatalc)){
		  ?>
        
        
        <div class="panel"> <a class="panel-heading collapsed" role="tab" id="headingTwo" data-toggle="collapse" data-parent="#accordion" href="#collapseTwo" aria-expanded="false" aria-controls="collapseTwo">
          <h4 class="panel-title">Labour Commissionerate</h4> <span class="glyphicon glyphicon-plus pull-right"></span>
          </a>
          <div id="collapseTwo" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingTwo">
            <div class="panel-body">
              <div class="table-responsive">
                <table class="table table-striped jambo_table bulk_action myalign">
                <thead>
                  <tr class="headings">
                    <th class="column-title">Establishment Name</th>
                    <th class="column-title widthfix">Service Name </th>
                    <th class="column-title" style="text-align:center;">Category </th>
                    <th class="column-title">Application Date </th>
                    <th class="column-title" style="text-align:center;">Application Status </th>
                    <th class="column-title no-link last" style="text-align:center;">Action</th>
                  </tr>
                </thead>
                <tbody>
               
                <?php 
				if(!empty($tmp['list'])){
						$newservicedata = array();
						//$k = 0;
						for($j=0;$j<sizeof($servicedatalc);$j++){
							//echo "service_id-->".$servicedatalc[$j]->service_id."<br>";
							 for($k=0; $k<sizeof($tmp['list']); $k++){
								//echo "act_id-->".$tmp['list'][$k][0]['act_id']."<br>";
								if(trim($servicedatalc[$j]->service_id) == trim($tmp['list'][$k][0]['act_id'])){
									$newservicedata[$j]['user_service_info_id'] = $servicedatalc[$j]->id;
									$newservicedata[$j]['act_title'] = $servicedatalc[$j]->act_title;
									$newservicedata[$j]['name'] = $servicedatalc[$j]->name;
									$newservicedata[$j]['uid'] = $servicedatalc[$j]->uid;
									$newservicedata[$j]['service_id'] = $servicedatalc[$j]->service_id;
									$newservicedata[$j]['application_time'] = $servicedatalc[$j]->application_time;
									$newservicedata[$j]['service_name'] = $servicedatalc[$j]->service_name;
									$newservicedata[$j]['service_type'] = $servicedatalc[$j]->service_type;
									$newservicedata[$j]['directorate_name'] = $servicedatalc[$j]->directorate_name;
									$newservicedata[$j]['directorate_code'] = $servicedatalc[$j]->directorate_code;
									$newservicedata[$j]['coming_soon'] = $servicedatalc[$j]->coming_soon;
									$newservicedata[$j]['ld_pass'] = $servicedatalc[$j]->ld_pass;
									
									
									$newservicedata[$j]['e_name'] = $tmp['list'][$k][0]['e_name'];
									$newservicedata[$j]['status'] = $tmp['list'][$k][0]['status'];
									$newservicedata[$j]['final_submit_status'] = $tmp['list'][$k][0]['final_submit_status'];
									$newservicedata[$j]['act_id'] = $tmp['list'][$k][0]['act_id'];
									$newservicedata[$j]['application_date'] = $tmp['list'][$k][0]['application_date'];
									$newservicedata[$j]['is_apply_status'] = $tmp['list'][$k][0]['is_apply_status'];
									$newservicedata[$j]['serial_no_from_v'] = $tmp['list'][$k][0]['serial_no_from_v'];
									$newservicedata[$j]['created_date'] = $tmp['list'][$k][0]['created_date'];
									$newservicedata[$j]['filename'] = $tmp['list'][$k][0]['filename'];
									
									break;
								}else{
									
									$newservicedata[$j]['user_service_info_id'] =  $servicedatalc[$j]->id;
									$newservicedata[$j]['act_title'] =  $servicedatalc[$j]->act_title;
									$newservicedata[$j]['name'] =  $servicedatalc[$j]->name;
									$newservicedata[$j]['uid'] =  $servicedatalc[$j]->uid;
									$newservicedata[$j]['service_id'] =  $servicedatalc[$j]->service_id;
									$newservicedata[$j]['application_time'] =  $servicedatalc[$j]->application_time;
									$newservicedata[$j]['service_name'] =  $servicedatalc[$j]->service_name;
									$newservicedata[$j]['service_type'] =  $servicedatalc[$j]->service_type;
									$newservicedata[$j]['directorate_name'] =  $servicedatalc[$j]->directorate_name;
									$newservicedata[$j]['directorate_code'] =  $servicedatalc[$j]->directorate_code;
									$newservicedata[$j]['coming_soon'] =  $servicedatalc[$j]->coming_soon;
									$newservicedata[$j]['ld_pass'] =  $servicedatalc[$j]->ld_pass;
									
									
									$newservicedata[$j]['e_name'] = 'Not Assigned';
									$newservicedata[$j]['status'] = 'Not Assigned';
									$newservicedata[$j]['final_submit_status'] ='Not Assigned';
									$newservicedata[$j]['act_id'] = 'Not Assigned';
									$newservicedata[$j]['application_date'] = 'Not Assigned';
									
									$newservicedata[$j]['is_apply_status'] = "";
									$newservicedata[$j]['serial_no_from_v'] = "";
									$newservicedata[$j]['created_date'] ="";
								}
							 }
							 
							 
								//$k++;
								/*if(trim($servicedatalc[$j]->service_id) == trim($tmp['list'][$k][0]['act_id'])){
									
									$newservicedata[$j]['user_service_info_id'] = $servicedatalc[$j]->id;
									$newservicedata[$j]['act_title'] = $servicedatalc[$j]->act_title;
									$newservicedata[$j]['name'] = $servicedatalc[$j]->name;
									$newservicedata[$j]['uid'] = $servicedatalc[$j]->uid;
									$newservicedata[$j]['service_id'] = $servicedatalc[$j]->service_id;
									$newservicedata[$j]['application_time'] = $servicedatalc[$j]->application_time;
									$newservicedata[$j]['service_name'] = $servicedatalc[$j]->service_name;
									$newservicedata[$j]['service_type'] = $servicedatalc[$j]->service_type;
									$newservicedata[$j]['directorate_name'] = $servicedatalc[$j]->directorate_name;
									$newservicedata[$j]['directorate_code'] = $servicedatalc[$j]->directorate_code;
									$newservicedata[$j]['coming_soon'] = $servicedatalc[$j]->coming_soon;
									$newservicedata[$j]['ld_pass'] = $servicedatalc[$j]->ld_pass;
									
									
									$newservicedata[$j]['e_name'] = $tmp['list'][$k][0]['e_name'];
									$newservicedata[$j]['status'] = $tmp['list'][$k][0]['status'];
									$newservicedata[$j]['final_submit_status'] = $tmp['list'][$k][0]['final_submit_status'];
									$newservicedata[$j]['act_id'] = $tmp['list'][$k][0]['act_id'];
									$newservicedata[$j]['application_date'] = $tmp['list'][$k][0]['application_date'];
									
									$k++;
								}else{
									
									$newservicedata[$j]['user_service_info_id'] =  $servicedatalc[$j]->id;
									$newservicedata[$j]['act_title'] =  $servicedatalc[$j]->act_title;
									$newservicedata[$j]['name'] =  $servicedatalc[$j]->name;
									$newservicedata[$j]['uid'] =  $servicedatalc[$j]->uid;
									$newservicedata[$j]['service_id'] =  $servicedatalc[$j]->service_id;
									$newservicedata[$j]['application_time'] =  $servicedatalc[$j]->application_time;
									$newservicedata[$j]['service_name'] =  $servicedatalc[$j]->service_name;
									$newservicedata[$j]['service_type'] =  $servicedatalc[$j]->service_type;
									$newservicedata[$j]['directorate_name'] =  $servicedatalc[$j]->directorate_name;
									$newservicedata[$j]['directorate_code'] =  $servicedatalc[$j]->directorate_code;
									$newservicedata[$j]['coming_soon'] =  $servicedatalc[$j]->coming_soon;
									$newservicedata[$j]['ld_pass'] =  $servicedatalc[$j]->ld_pass;
									
									
									$newservicedata[$j]['e_name'] = 'Not Assigned';
									$newservicedata[$j]['status'] = 'Not Assigned';
									$newservicedata[$j]['final_submit_status'] ='Not Assigned';
									$newservicedata[$j]['act_id'] = 'Not Assigned';
									$newservicedata[$j]['application_date'] = 'Not Assigned';
								}*/

						}
						
						
						//print_r($newservicedata); exit;
						
						foreach($newservicedata as $key=>$tmp){
						if($tmp['status'] == '0'){
							//$current_status = 'Application is Approved & does not require Fees';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/applied.png" alt="" title="Applied">';
							$linkText = 'View Details';
							
							$query_chk_rating = db_select('ld_user_service_star_rating', 'ur');
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
							}
						}
						elseif($tmp['service_id'] == '12'){
							//$current_status = 'Rectification';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/view-details-icon.png" alt="" title="View Status">';
							$linkText = 'Apply & View Status';
						}
						elseif($tmp['status'] == 'B'){
							//$current_status = 'Rectification';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/rectification.png" alt="" title="Rectification">';
							$linkText = 'View Details';
						}
						elseif($tmp['status'] == 'BI'){
							//$current_status = 'Application is BACKED TO INSPECTOR';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/backed.png" alt="" title="Backed to Inspector">';
							$linkText = 'View Details';
						}
					/*	elseif($tmp['status'] == 'C'){
							//$current_status = 'Applicant is CALLED BY ALC';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/applicant_called_by.png" alt="" title="Called by ALC">';
							$linkText = 'View Details';
						}*/
						elseif($tmp['status'] == 'I'){
							//$current_status = 'REGISTRATION CERTIFICATE IS ISSUED';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/issued.png" alt="" title="Certificate Issued">';
							$linkText = 'View Details';
						}
						elseif($tmp['status'] == 'F'){
							//$current_status = 'Application is FORWARDED TO ALC';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/forward.png" alt="" title="Forwarded to ALC">';
							$linkText = 'View Details';
						}
						elseif($tmp['status'] == 'T'){
							//$current_status = 'TRANSACTION IS SUCCESSFULL for this Application';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/fees_paid.png" alt="" title="Fees Paid">';
							$linkText = 'View Details';
						}
						elseif($tmp['status'] == 'V'){
							//$current_status = 'Application is VERIFIED & GIVEN APPROVAL FOR FEES SUBMISSION';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/fees_pending.png" alt="" title="Fees Pending">';
							$linkText = 'View Details';
						}
						elseif($tmp['status'] == 'R'){
							//$current_status = 'Application is REJECTED';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/reject.png" alt="" title="Rejected">';
							$linkText = 'View Details';
						}
						elseif($tmp['status'] == 'S'){
							//$current_status = 'Form-I Final Submit';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/final_submit.png" alt="" title="Form-I Final Submit">';
							$linkText = 'View Details';
						}
						elseif($tmp['status'] == 'VA'){
							//$current_status = 'Application is Approved & does not require Fees';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/approved.png" alt="" title="Approved & does not require Fees">';
							$linkText = 'View Details';
						}
						elseif(empty($tmp['status'])){
							//$current_status = 'CURRENT STATUS: Application is incomplete';
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/incomplete.png" alt="" title="Incomplete Application">';
							$linkText = 'View Details';
						}
						
						elseif($tmp['is_apply_status']=="0" || empty($tmp['status'])){
						$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/incomplete.png" alt="" title="Incomplete Application">';
						$echoStatus					=	'Incomplete';
						$linkText = 'View Details';
		                }
		
						elseif($tmp['is_apply_status']=="1" && $tmp['status']=='F'){
							$echoStatus					=	'Applied';
							$linkText = 'View Details';
						}
		
						elseif($tmp['is_apply_status']=="1" && $tmp['status']=='A'){
							$echoStatus					=	'Fees Pending';	
							$linkText = 'View Details';
						}
						elseif($tmp['is_apply_status']=="1" && $tmp['status']=='B'){
							$echoStatus					='Back For Correction';
							$linkText = 'View Details';
						}
					 elseif($tmp['is_apply_status']=="1" && $tmp['status']=='BI'){
						$echoStatus					=	'In Process';
						$linkText = 'View Details';
					}
					
					 elseif($tmp['is_apply_status']=="1" && $tmp['status']=='C'){
						$echoStatus					= 'Call Applicant';	
						$linkText = 'View Details';
					}
		
					elseif($tmp['is_apply_status']=="1" && $tmp['status']=='FW'){
						$echoStatus					= 'In Process';	
						$linkText = 'View Details';
					}
					
					 elseif($tmp['is_apply_status']=="1" && $tmp['status']=='P'){			
						$echoStatus					=	'Fees Paid';
						$linkText = 'View Details';	
					}
		
					 elseif($tmp['is_apply_status']=="1" && $tmp['status']=='I'){
							 $echoStatus					= 'Issued';	
							$linkText = 'View Details';
					}
					
					
					elseif($tmp['is_apply_status']=="1" && $tmp['status']=='R'){
						$echoStatus					= 'Rejected';
						$linkText = 'View Details';
					}
		
					elseif($tmp['is_apply_status']=="1" && $tmp['status']=='U'){			
						$echoStatus					= 	'Final Submit';
						$linkText = 'View Details';
					}	
		
						else{
							$current_status = 'NIL';
							$linkText = 'Apply Online';
						}
						//echo "test ".$servicedata->service_name;
					?>
                  <tr class="even pointer">
                    <td class=" "><?php echo $tmp['e_name'].$tmp['serial_no_from_v']; ?></td>
                    <td class=" "><?php echo $tmp['service_name'].", ".$tmp['act_title'];?></td>
                     <td class=" "><?php if($tmp['service_type']=="1"){ echo "Pre-Establishement";}else if($tmp['service_type']=="2"){echo "Pre-Operation";}else if($tmp['service_type']=="3"){echo "Others";}else{echo "--";}?></td>
                    <td class=" "><?php echo !empty($tmp['application_date'])? format_date(strtotime($tmp['application_date']), 'custom', 'd-m-Y') : "--" ;?></td>
                    <td class=" "><div class="status-icon"><?php echo $current_status;?></div> </td>
                    <td class="last" align="center">
                    
                     <?php if($tmp['coming_soon'] == 'C'){?>
                     
                     	<a class="icon-table" href="#"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/coming_soon.png">Coming Soon</a> 
                        
                     <?php }else{?>
                     
                      <?php if($tmp['status'] != 'I'){ ?>
                      
                        <a class="icon-table" target="_blank" href="https://wblc.gov.in/user-authenticate-ld/<?php echo encryption_decryption_wblabour('encrypt', $tmp['name']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['ld_pass']); ?>/<?php echo encryption_decryption_wblabour('encrypt', $tmp['service_id']); ?>"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png"><?php echo $linkText;?></a> 
                        <?php }else{ 
						if($tmp['act_id'] == '1'){
							$dirname = 'alc_upload_certificates_clra';
						}else if($tmp['act_id'] == '2'){
							$dirname = 'BOCWA_Registration_Certificate';
						 }else if($tmp['act_id'] == '3'){
							$dirname = 'MTW_Registration_Certificate';
						 }else if($tmp['act_id'] == '4'){
							$dirname = 'ISMW_Registration_Certificate';
						 }
						?>
                        <!--<a class="icon-table" href="#"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/download-icon.png">Download</a>-->
                        <a class="icon-table" target="_blank" href="https://wblc.gov.in/sites/default/files/upload/<?php print $dirname;?>/<?php print $tmp['filename'];?>"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/download-icon.png">Download</a>
                        <?php } ?>
                     
                     <?php }?>
                    
                   
                    </td>
                  </tr> 
                  <?php $i++;}
				  }else{ 
				  
				  	foreach($servicedatalc as $val){
				  ?>
					  <tr class="even pointer">
                      	<td class=" ">Not Assigned</td>
                    	<td class=" "><?php echo $val->service_name.", ".$val->act_title;?></td>
                        <td class=" "><?php if($val->service_type=="1"){ echo "Pre-Establishement";}else if($val->service_type=="2"){echo "Pre-Operation";}else if($val->service_type=="3"){echo "Others";}else{echo "--";}?></td>
                        <td class=" ">Not Assigned</td>
                    	<td class=" ">Not Assigned</td>
                        <td class="last" align="center">
                        <?php if($val->coming_soon == 'C'){?>
                        <a class="icon-table" href="#"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/coming_soon.png">Coming Soon</a> 
                        <?php }else{?>
                        <a class="icon-table" target="_blank" href="https://wblc.gov.in/user-authenticate-ld/<?php echo encryption_decryption_wblabour('encrypt', $val->name); ?>/<?php echo encryption_decryption_wblabour('encrypt', $val->ld_pass); ?>/<?php echo encryption_decryption_wblabour('encrypt', $val->service_id); ?>"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a> 
                        <?php }?>
                    
                    </td>
                      </tr>
				<?php  } }/*else{ ?>
                	<tr class="even pointer">
                      	<td colspan="6" class=" ">Not Data Found</td>
                    </tr>
                <?php }*/ ?>
                  
                  <!--<tr class="even pointer">
                    <td class=" ">Shanti Pvt. Ltd.</td>
                    <td class=" ">CLRA</td>
                    <td class=" "><div id="wizard" class="form_wizard wizard_horizontal small_line">
                        <ul class="wizard_steps">
                          <li> <a href="#step-1" class="done" data-toggle="tooltip" title="Submited On 15/08/2015"> <span class="step_no small_circle"><i class="ace-icon fa fa-hourglass-half"></i></span> <span class="step_descr"><small>Pending</small></span> </a> </li>
                          <li> <a href="#step-3" class="disabled"> <span class="step_no small_circle"><i class="ace-icon fa fa-send"></i></span> <span class="step_descr"><small>Applied</small></span> </a> </li>
                           <li> <a href="#step-2" class="selected"> <span class="step_no small_circle"><i class="fa fa-history"></i></span> <span class="step_descr"><small>Rectification</small></span> </a> </li>
                          <li> <a href="#step-4" class="disabled"> <span class="step_no small_circle"><i class="fa fa-spinner"></i></span> <span class="step_descr"><small>In Process</small></span> </a> </li>
                          <li> <a href="#step-4" class="disabled"> <span class="step_no small_circle"><i class="fa fa-credit-card"></i></span> <span class="step_descr"><small>Fees Pending</small></span> </a> </li>
                          <li> <a href="#step-4" class="disabled"> <span class="step_no small_circle"><i class="fa fa-check"></i></span> <span class="step_descr"><small>
                          Approved</small></span> </a> </li>
                          <li> <a href="#step-4" class="disabled"> <span class="step_no small_circle"><i class="fa fa-credit-card"></i></span> <span class="step_descr"><small>
                          Fees Payment</small></span> </a> </li>
                          <li> <a href="#step-4" class="disabled"> <span class="step_no small_circle"><i class="ace-icon fa fa-send"></i></span> <span class="step_descr"><small>
                          Final Submit</small></span> </a> </li>
                        </ul>
                      </div></td>
                    <td class="last" align="center"><a class="icon-table" href="#"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a> <a class="icon-table" href="#"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/download-icon.png">Download</a></td>
                  </tr>-->
                </tbody>
              </table>
              </div>
            </div>
          </div>
        </div>
        <?php }?>
        <!-- LC Section End-->
        
        <!-- Factory Section Start -->
       <?php
        $query = db_select('ld_user_service_info', 'us');
		$query->leftJoin('ld_service_master', 'sm', 'sm.id=us.service_id');
		$query->leftJoin('ld_act_master', 'a', 'a.id=us.act_id');
		$query->leftJoin('users', 'u', 'u.uid=us.uid');
		$query->leftJoin('ld_users_details', 'lud', 'lud.uid=us.uid');
		$query ->fields('a', array( 'act_title'));
		$query ->fields('u', array( 'name'));
		$query ->fields('us', array( 'uid','service_id','application_time'));
		$query ->fields('sm', array( 'service_name','directorate_name','directorate_code','service_type','coming_soon'));
		$query ->fields('lud', array( 'ld_pass' ));
		$query->condition('us.uid',trim($user->uid),'=');
		$query->condition('sm.directorate_code','F','=');
		$query->orderBy('sm.service_type','ASC');
		//echo $query; exit;
		$service = $query->execute();
		$servicedatafactory = $service->fetchAll();
	
		
		$service_url 	= 	"https://wbfactoryonline.in/webservices/REST/getEservicesStatusData";
			
		$ch 			= 	curl_init();
		$headers		=	array();
		$curl_post_data_f = 	array(
			"user_name"	=> $user_name,
			"source"	=> "WBLD",
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
		curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode( $curl_post_data_f ) );
		curl_setopt($ch, CURLOPT_POST, true);
		$results_f		=	curl_exec($ch);
		$errors			=	curl_error($ch);
		curl_close($ch);
		$x_f				=	json_encode( $results_f );
		$tmp_f 			= 	json_decode(json_decode(trim($x_f)), TRUE);
		
		//echo "userid".$user->uid;
		//print_r($tmp_f);
		//exit;
		if(!empty($servicedatafactory)){ 
	  ?>
        <div class="panel"> <a class="panel-heading collapsed" role="tab" id="headingThree" data-toggle="collapse" data-parent="#accordion" href="#collapseThree" aria-expanded="false" aria-controls="collapseThree">
          <h4 class="panel-title">Directorate of Factories</h4> <span class="glyphicon glyphicon-plus pull-right"></span>
          </a>
          <div id="collapseThree" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingThree">
            <div class="panel-body">
              <div class="table-responsive">
                <table class="table table-striped jambo_table bulk_action myalign">
                <thead>
                  <tr class="headings">
                    <th class="column-title">Establishment Name</th>
                    <th class="column-title widthfix">Service Name </th>
                    <th class="column-title" style="text-align:center;">Category </th>
                    <th class="column-title">Application Date </th>
                    <th class="column-title" style="text-align:center;">Application Status </th>
                    <th class="column-title no-link last" style="text-align:center;">Action</th>
                  </tr>
                </thead>
                <tbody>
                <?php $current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/final_submit.png" alt="" title="">';?>
                <?php
				//print_r($tmp_f['content']['error']);exit;
				
				if(!empty($tmp_f['content']['error'])){ 
				  	foreach($servicedatafactory as $val){
				?>
                  <tr class="even pointer">
                      	<td class=" ">Not Assigned</td>
                    	<td class=" "><?php echo $val->service_name;?></td>
                        <td class=" "><?php if($val->service_type=="1"){ echo "Pre-Establishement";}else if($val->service_type=="2"){echo "Pre-Operation";}else if($val->service_type=="3"){echo "Others";}else{echo "--";}?></td>
                        <td class=" ">Not Assigned</td>
                    	<td class=" ">Not Assigned</td>
                        <td class="last" align="center">
                    	<!--<a class="icon-table" href="#"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/coming_soon.png">Coming Soon</a> -->
                  
                  <a class="icon-table" href="https://wbfactoryonline.in/factory/forms/form_caf?src=WBLD&service_id=<?php echo $val->service_id;?>&username=<?php echo $user_name;?>&authkey=<?php echo $authkay;?>" target="_blank"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a>
                    </td>
                  </tr>
                  <?php } 
				  }elseif(!empty($tmp_f['content'])){
					  //echo "aa66"; exit;
					  //print_r($servicedatafactory);
					  //print_r($tmp_f['content']);
					$newservicedatafactory = array();
					for($j=0;$j<sizeof($servicedatafactory);$j++){
						//echo "service_id-->".$servicedatafactory[$j]->service_id."<br>";
						 for($k=0; $k<sizeof($tmp_f['content']); $k++){
							//echo "service_id_webservice-->".$tmp_f['content'][$k]['service_id']."<br>";
							if(trim($servicedatafactory[$j]->service_id) == trim($tmp_f['content'][$k]['service_id'])){
								
								//echo $tmp_f['content'][$k]['application_no'];
								
								//$newservicedatafactory[$j]['user_service_info_id'] = $servicedatafactory[$j]->id;
								//$newservicedatafactory[$j]['act_title'] = $servicedatafactory[$j]->act_title;
								$newservicedatafactory[$j]['name'] = $servicedatafactory[$j]->name;
								$newservicedatafactory[$j]['uid'] = $servicedatafactory[$j]->uid;
								$newservicedatafactory[$j]['service_id'] = $servicedatafactory[$j]->service_id;
								//$newservicedatafactory[$j]['application_time'] = $servicedatafactory[$j]->application_time;
								$newservicedatafactory[$j]['service_name'] = $servicedatafactory[$j]->service_name;
								$newservicedatafactory[$j]['service_type'] = $servicedatafactory[$j]->service_type;
								$newservicedatafactory[$j]['directorate_name'] = $servicedatafactory[$j]->directorate_name;
								$newservicedatafactory[$j]['directorate_code'] = $servicedatafactory[$j]->directorate_code;
								$newservicedatafactory[$j]['coming_soon'] = $servicedatafactory[$j]->coming_soon;
								$newservicedatafactory[$j]['ld_pass'] = $servicedatafactory[$j]->ld_pass;
								
								
								$newservicedatafactory[$j]['e_name'] = $tmp_f['content'][$k]['unit_name'];
								$newservicedatafactory[$j]['status'] = $tmp_f['content'][$k]['application_status'];
								//$newservicedatafactory[$j]['final_submit_status'] = $tmp_f['content'][$k]['final_submit_status'];
								$newservicedatafactory[$j]['application_no'] = $tmp_f['content'][$k]['application_no'];
								$newservicedatafactory[$j]['application_date'] = $tmp_f['content'][$k]['application_date'];
								break;
								
								
							}else{
								$newservicedatafactory[$j]['name'] = $servicedatafactory[$j]->name;
								$newservicedatafactory[$j]['uid'] = $servicedatafactory[$j]->uid;
								$newservicedatafactory[$j]['service_id'] = $servicedatafactory[$j]->service_id;
								//$newservicedatafactory[$j]['application_time'] = $servicedatafactory[$j]->application_time;
								$newservicedatafactory[$j]['service_name'] = $servicedatafactory[$j]->service_name;
								$newservicedatafactory[$j]['service_type'] = $servicedatafactory[$j]->service_type;
								$newservicedatafactory[$j]['directorate_name'] = $servicedatafactory[$j]->directorate_name;
								$newservicedatafactory[$j]['directorate_code'] = $servicedatafactory[$j]->directorate_code;
								$newservicedatafactory[$j]['coming_soon'] = $servicedatafactory[$j]->coming_soon;
								$newservicedatafactory[$j]['ld_pass'] = $servicedatafactory[$j]->ld_pass;
								
								
								$newservicedatafactory[$j]['e_name'] = 'Not Assigned';
								$newservicedatafactory[$j]['status'] = 'Not Assigned';
								$newservicedatafactory[$j]['application_no'] = 'Not Assigned';
								$newservicedatafactory[$j]['application_date'] = 'Not Assigned';
							}
						 }
					}
					
					//print_r($newservicedatafactory);
					//exit;
					foreach($newservicedatafactory as $key=>$val){
                    	if(trim($val['status']) == 'SUBMITTED TO OFFICE'){
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/applied.png" alt="" title="Applied">';
							$linkText = '<a class="icon-table" href="https://wbfactoryonline.in/dashboard?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">View Details</a>';
							
						}elseif(trim($val['status']) == 'FORWARDED TO CONCERN AUTHORITY'){
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/forward.png" alt="" title="Forwarded">';
							$linkText = '<a class="icon-table" href="https://wbfactoryonline.in/dashboard?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">View Details</a>';
						}elseif(trim($val['status']) == 'INSTRUCTED FOR RESUBMIT APPLICATION'){
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/backed.png" alt="" title="Backed">';
							$linkText = '<a class="icon-table" href="https://wbfactoryonline.in/dashboard?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">View Details</a>';
						}elseif(trim($val['status']) == 'RESUBMITTED'){
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/backed.png" alt="" title="Resubmitted">';
							$linkText = '<a class="icon-table" href="https://wbfactoryonline.in/dashboard?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">View Details</a>';
						}elseif(trim($val['status']) == 'CERTIFICATE GENERATED'){
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/issued.png" alt="" title="Certificate Generated">';
							$linkText = '<a class="icon-table" href="https://wbfactoryonline.in/dashboard?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">View Details</a>';
						}elseif(trim($val['status']) == 'MESSAGE'){
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/applicant_called_by.png" alt="" title="Message">';
							$linkText = '<a class="icon-table" href="https://wbfactoryonline.in/dashboard?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">View Details</a>';
						}
						elseif(trim($val['status']) == 'ATTACHMENTS UPLOADED / REUPLOADED'){
						$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/applicant_called_by.png" alt="" title="Attachment Re-uploaded">';
							$linkText = '<a class="icon-table" href="https://wbfactoryonline.in/dashboard?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">View Details</a>';
						}elseif(trim($val['status']) == 'REJECTED'){
						$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/reject.png" alt="" title="Rejected">';
							$linkText = '<a class="icon-table" href="https://wbfactoryonline.in/dashboard?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">View Details</a>';
						}
						elseif(trim($val['status']) == 'CERTIFICATE READY FOR DOWNLOAD'){
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/download-icon.png" alt="" title="Download Certificate">';
							$linkText = '<a class="icon-table" href="https://wbfactoryonline.in/dashboard?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">View Details</a>';
						}else{
							$current_status = 'Not Assigned';
							$linkText = '<a class="icon-table" href="https://wbfactoryonline.in/factory/forms/form_caf?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a>';
						}
					?>	
                         <tr class="even pointer">
                            <td class=" "><?php echo $val['e_name'];?></td>
                            <td class=" "><?php echo $val['service_name'];?></td>
                            <td class=" "><?php if($val['service_type']=="1"){ echo "Pre-Establishement";}else if($val['service_type']=="2"){echo "Pre-Operation";}else if($val['service_type']=="3"){echo "Others";}else{echo "--";}?></td>
                            <td class=" "><?php if($val['application_date']!='Not Assigned'){echo format_date(strtotime($val['application_date']), 'custom', 'd-m-Y');}else{echo "Not Assigned";}?></td>
                            <td class=" "><div class="status-icon"><?php echo $current_status;?></div></td>
                            <td class="last" align="center">
                            <!--<a class="icon-table" href="#"><img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/coming_soon.png">Coming Soon</a> -->
                      		<?php echo $linkText;?>
                   <?php /*?>   <a class="icon-table" href="https://wbfactoryonline.in/factory/forms/form_caf?src=WBLD&service_id=<?php echo $val['service_id'];?>&username=<?php echo $user_name;?>&authkey=<?php echo $authkay;?>" target="_blank"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a><?php */?>
              
               <!--<a class="icon-table" href="https://wbfactoryonline.in/factory/forms/form_caf?src=WBLD&service_id=<?php echo $val['service_id'];?>&username=<?php echo $user_name;?>&authkey=<?php echo $authkay;?>" target="_blank"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png"><?php echo $linkText;?></a>   -->    
               
                      
                      
                        </td>
                      </tr>
                        
				<?php }
					
				}else{ ?>
                	<tr class="even pointer">
                      	<td colspan="6" class=" ">No Data Found</td>
                    </tr>
                <?php } ?>
                </tbody>
              </table>
              </div>
            </div>
          </div>
        </div>
        <?php } ?>
        <!-- Factory Section End-->
        
        
        
        
        
        <!-- Shop Section Start -->
       <?php
        $query = db_select('ld_user_service_info', 'us');
		$query->leftJoin('ld_service_master', 'sm', 'sm.id=us.service_id');
		$query->leftJoin('ld_act_master', 'a', 'a.id=us.act_id');
		$query->leftJoin('users', 'u', 'u.uid=us.uid');
		$query->leftJoin('ld_users_details', 'lud', 'lud.uid=us.uid');
		$query ->fields('a', array( 'act_title'));
		$query ->fields('u', array( 'name'));
		$query ->fields('us', array( 'uid','service_id','application_time'));
		$query ->fields('sm', array( 'service_name','directorate_name','directorate_code','service_type'));
		$query ->fields('lud', array( 'ld_pass' ));
		$query->condition('us.uid',trim($user->uid),'=');
		$query->condition('sm.directorate_code','S','=');
		$query->orderBy('sm.service_type','ASC');
		$query->orderBy('us.service_id','ASC');
		//echo $query; exit;
		$service = $query->execute();
		$servicedatashops = $service->fetchAll();
		
		
		
		$service_url 	= 	"https://wbshopsonline.in/webservices/REST/getEservicesStatusData";
			
		$ch 			= 	curl_init();
		$headers		=	array();
		$curl_post_data_s = 	array(
			"user_name"	=> $user_name,
			"source"	=> "WBLD",
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
		curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode( $curl_post_data_s ) );
		curl_setopt($ch, CURLOPT_POST, true);
		$results_s		=	curl_exec($ch);
		$errors			=	curl_error($ch);
		curl_close($ch);
		$x_s				=	json_encode( $results_s );
		$tmp_s 			= 	json_decode(json_decode(trim($x_s)), TRUE);
		
		//print_r($tmp_s);
		//exit;
		
		if(!empty($servicedatashops)){ 
	  ?>
        <div class="panel"> <a class="panel-heading collapsed" role="tab" id="headingFour" data-toggle="collapse" data-parent="#accordion" href="#collapseFour" aria-expanded="false" aria-controls="collapseFour">
          <h4 class="panel-title">Directorate of Shops</h4> <span class="glyphicon glyphicon-plus pull-right"></span>
          </a>
          <div id="collapseFour" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingFour">
            <div class="panel-body">
              <div class="table-responsive">
                <table class="table table-striped jambo_table bulk_action myalign">
                <thead>
                  <tr class="headings">
                    <th class="column-title">Establishment Name</th>
                    <th class="column-title widthfix">Service Name </th>
                    <th class="column-title" style="text-align:center;">Category </th>
                    <th class="column-title">Application Date </th>
                    <th class="column-title" style="text-align:center;">Application Status </th>
                    <th class="column-title no-link last" style="text-align:center;">Action</th>
                  </tr>
                </thead>
                <tbody>
                <?php $current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/final_submit.png" alt="" title="">';?>
                <?php
				if(!empty($tmp_s['content']['error'])){ 
				  	foreach($servicedatashops as $val){
				?>
                  <tr class="even pointer">
                      	<td class=" ">Not Assigned</td>
                    	<td class=" "><?php echo $val->service_name;?></td>
                        <td class=" "><?php if($val->service_type=="1"){ echo "Pre-Establishement";}else if($val->service_type=="2"){echo "Pre-Operation";}else if($val->service_type=="3"){echo "Others";}else{echo "--";}?></td>
                        <td class=" ">Not Assigned</td>
                    	<td class=" ">Not Assigned</td>
                        <td class="last" align="center">
                    	<!--<a class="icon-table" href="#"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/coming_soon.png">Coming Soon</a> -->
                  
                   <?php if($val->service_id=='30'){?>
                   <a class="icon-table" href="
                   https://wbshopsonline.in/shop/forms/form_b?src=WBLD&service_id=<?php echo $val->service_id;?>&username=<?php echo $user_name;?>&authkey=<?php echo $authkay;?>" target="_blank"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a>
                   <?php }?>
                    <?php if($val->service_id=='49'){?>
                   <a class="icon-table" href="
                   https://wbshopsonline.in/shop/forms/form_d?src=WBLD&service_id=<?php echo $val->service_id;?>&username=<?php echo $user_name;?>&authkey=<?php echo $authkay;?>" target="_blank"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a>
                   <?php }?>
                    <?php if($val->service_id=='50'){?>
                   <a class="icon-table" href="
                   https://wbshopsonline.in/shop/forms/form_c?src=WBLD&service_id=<?php echo $val->service_id;?>&username=<?php echo $user_name;?>&authkey=<?php echo $authkay;?>" target="_blank"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a>
                   <?php }?>
                    <?php if($val->service_id=='51'){?>
                   <a class="icon-table" href="
                   https://wbshopsonline.in/shop/forms/form_e?src=WBLD&service_id=<?php echo $val->service_id;?>&username=<?php echo $user_name;?>&authkey=<?php echo $authkay;?>" target="_blank"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a>
                   <?php }?>
                  <!-- <a class="icon-table" href="https://wbfactoryonline.in/factory/forms/form_caf?src=WBLD&service_id=46&username=<?php echo $user_name;?>&authkey=<?php echo $authkay;?>" target="_blank"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/coming_soon.png">Apply Online</a>-->
                    </td>
                  </tr>
                  <?php }} elseif(!empty($tmp_s['content'])){
					  //echo "aa997"; exit;
					  //print_r($servicedatashops); exit;
					  //print_r($tmp_f['content']);
					$newservicedatashops = array();
					for($j=0;$j<sizeof($servicedatashops);$j++){
						//echo "service_id-->".$servicedatashops[$j]->service_id."<br>";
						 for($k=0; $k<sizeof($tmp_s['content']); $k++){
							//echo "service_id_webservice-->".$tmp_s['content'][$k]['service_id']."<br>";
							if(trim($servicedatashops[$j]->service_id) == trim($tmp_s['content'][$k]['service_id'])){
								
								//echo $tmp_f['content'][$k]['application_no'];
								
								//$newservicedatafactory[$j]['user_service_info_id'] = $servicedatafactory[$j]->id;
								//$newservicedatafactory[$j]['act_title'] = $servicedatafactory[$j]->act_title;
								$newservicedatashops[$j]['name'] = $servicedatashops[$j]->name;
								$newservicedatashops[$j]['uid'] = $servicedatashops[$j]->uid;
								$newservicedatashops[$j]['service_id'] = $servicedatashops[$j]->service_id;
								//$newservicedatashops[$j]['application_time'] = $servicedatashops[$j]->application_time;
								$newservicedatashops[$j]['service_name'] = $servicedatashops[$j]->service_name;
								$newservicedatashops[$j]['service_type'] = $servicedatashops[$j]->service_type;
								$newservicedatashops[$j]['directorate_name'] = $servicedatashops[$j]->directorate_name;
								$newservicedatashops[$j]['directorate_code'] = $servicedatashops[$j]->directorate_code;
								$newservicedatashops[$j]['coming_soon'] = $servicedatashops[$j]->coming_soon;
								$newservicedatashops[$j]['ld_pass'] = $servicedatashops[$j]->ld_pass;
								
								
								$newservicedatashops[$j]['e_name'] = $tmp_s['content'][$k]['unit_name'];
								$newservicedatashops[$j]['status'] = $tmp_s['content'][$k]['application_status'];
								//$newservicedatashops[$j]['final_submit_status'] = $tmp_s['content'][$k]['final_submit_status'];
								$newservicedatashops[$j]['application_no'] = $tmp_s['content'][$k]['application_no'];
								$newservicedatashops[$j]['application_date'] = $tmp_s['content'][$k]['application_date'];
								break;
								
								
							}else{
								$newservicedatashops[$j]['name'] = $servicedatashops[$j]->name;
								$newservicedatashops[$j]['uid'] = $servicedatashops[$j]->uid;
								$newservicedatashops[$j]['service_id'] = $servicedatashops[$j]->service_id;
								//$newservicedatashops[$j]['application_time'] = $servicedatashops[$j]->application_time;
								$newservicedatashops[$j]['service_name'] = $servicedatashops[$j]->service_name;
								$newservicedatashops[$j]['service_type'] = $servicedatashops[$j]->service_type;
								$newservicedatashops[$j]['directorate_name'] = $servicedatashops[$j]->directorate_name;
								$newservicedatashops[$j]['directorate_code'] = $servicedatashops[$j]->directorate_code;
								$newservicedatashops[$j]['coming_soon'] = $servicedatashops[$j]->coming_soon;
								$newservicedatashops[$j]['ld_pass'] = $servicedatashops[$j]->ld_pass;
								
								
								$newservicedatashops[$j]['e_name'] = 'Not Assigned';
								$newservicedatashops[$j]['status'] = 'Not Assigned';
								$newservicedatashops[$j]['application_no'] = 'Not Assigned';
								$newservicedatashops[$j]['application_date'] = 'Not Assigned';
							}
						 }
					}
					
					//print_r($newservicedatashops);
					//exit;
					foreach($newservicedatashops as $key=>$val){
                    	if(trim($val['status']) == 'SUBMITTED TO OFFICE'){
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/applied.png" alt="" title="Applied">';
							$linkText = '<a class="icon-table" href="https://wbshopsonline.in/dashboard?src=WBLD&service_id='.$val['service_id'].'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">View Details</a>';
							//$linkText = 'View Details';
							
						}elseif(trim($val['status']) == 'FORWARDED TO CONCERN AUTHORITY'){
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/forward.png" alt="" title="Forwarded">';
							$linkText = 'View Details';
						}elseif(trim($val['status']) == 'CERTIFICATE READY FOR DOWNLOAD'){
							$current_status = '<img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/download-icon.png" alt="" title="Download Certificate">';
							$linkText = 'View Details';
						}else{
							$current_status = 'Not Assigned';
                            
                           if($val['service_id']=='30'){
                   $linkText = '<a class="icon-table" href="
                   https://wbshopsonline.in/shop/forms/form_b?src=WBLD&service_id='.$val->service_id.'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a>';
							}
                 if($val['service_id']=='49'){
					 $linkText = '<a class="icon-table" href="
                   https://wbshopsonline.in/shop/forms/form_d?src=WBLD&service_id='.$val->service_id.'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a>';
				 }
                  if($val['service_id']=='50'){
					 $linkText = '<a class="icon-table" href="
                   https://wbshopsonline.in/shop/forms/form_c?src=WBLD&service_id='.$val->service_id.'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a>';  
				  }
                   if($val['service_id']=='51'){
					 $linkText = '<a class="icon-table" href="
                   https://wbshopsonline.in/shop/forms/form_e?src=WBLD&service_id='.$val->service_id.'&username='.$user_name.'&authkey='.$authkay.'" target="_blank"> <img src="'.$base_root.$base_path.'sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a>';  
				   }
						}?>
                         <tr class="even pointer">
                            <td class=" "><?php echo $val['e_name'];?></td>
                            <td class=" "><?php echo $val['service_name'];?></td>
                            <td class=" "><?php if($val['service_type']=="1"){ echo "Pre-Establishement";}else if($val['service_type']=="2"){echo "Pre-Operation";}else if($val['service_type']=="3"){echo "Others";}else{echo "--";}?></td>
                            <td class=" "><?php if($val['application_date']!='Not Assigned'){echo format_date(strtotime($val['application_date']), 'custom', 'd-m-Y');}else{echo "Not Assigned";}?></td>
                            <td class=" "><div class="status-icon"><?php echo $current_status;?></div></td>
                            <td class="last" align="center">
                            <!--<a class="icon-table" href="#"><img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/coming_soon.png">Coming Soon</a> -->
                      		<?php echo $linkText;?>
                   <?php /*?>   <a class="icon-table" href="https://wbfactoryonline.in/factory/forms/form_caf?src=WBLD&service_id=<?php echo $val['service_id'];?>&username=<?php echo $user_name;?>&authkey=<?php echo $authkay;?>" target="_blank"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png">Apply Online</a><?php */?>
              
              <?php /*?> <a class="icon-table" href="https://wbshopsonline.in/shop/forms/form_caf?src=WBLD&service_id=<?php echo $val['service_id'];?>&username=<?php echo $user_name;?>&authkey=<?php echo $authkay;?>" target="_blank"> <img src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/images/apply-icon.png"><?php echo $linkText;?></a>  <?php */?>
               
               
               
                      
                      
                        </td>
                      </tr>
                        
				<?php }
					
				}else{ ?>
                	<tr class="even pointer">
                      	<td colspan="6" class=" ">No Data Found</td>
                    </tr>
                <?php } ?>
                </tbody>
              </table>
              </div>
            </div>
          </div>
        </div>
        <?php }?>
        <!-- Shop Section End-->
        
        
        
        
        <!-- Modal Section Start-->
        <form name="modalfrm" id="modalfrm" action="" method="post">
        <div id="myModal" class="modal fade" role="dialog" data-backdrop="static">
          <div class="modal-dialog">
        
            <!-- Modal content-->
            <div class="modal-content">
              <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal">&times;</button>
                <h4 class="modal-title">Rate your experience!!</h4>
                <input type="hidden" id="user_servive_info_id" name="user_servive_info_id" value="">
              </div>
              <div class="modal-body">
                <p>
                <section>
                    <div class="row lead evaluation">
                    	<div class="myerr_msg" style="display:none"></div>
                        <div id="colorstar" class="starrr ratable" ></div>
                        <span id="count">0</span> star(s) - <span id="meaning"></span><br><br>
                            <div class='indicators' style="display:block">
                                <div id='textwr'>What went wrong?</div><br>
                                <input id="rate[]" name="rate[]" type="text" placeholder="" class="form-control input-md" style="display:none;">
                                <input id="rating[]" name="rating[]" type="text" placeholder="" class="form-control input-md rateval" style="display:none;">
                                
                                <span class="button-checkbox">
                                <button type="button" class="btn criteria buttondashboardstar" data-color="info">Easy availability of relevant information</button>
                                 <input type="checkbox" class="hidden" id="1" value="1_I"  />
                                 <input type="hidden" id="feedbackans_1" class="myoptnchk" value="NOVAL">
                                </span>
                                
                                <span class="button-checkbox">
                                <button type="button" class="btn criteria buttondashboardstar" data-color="info">Process of Online submission</button>
                                 <input type="checkbox" class="hidden" id="2" value="2_S"  />
                                 <input type="hidden" id="feedbackans_2" class="myoptnchk" value="NOVAL">
                                </span>
                               
                                <span class="button-checkbox">
                                <button type="button" class="btn criteria buttondashboardstar" data-color="info">Process of Online payment</button>
                                 <input type="checkbox" class="hidden" id="3" value="3_P"  />
                                 <input type="hidden" id="feedbackans_3" class="myoptnchk" value="NOVAL">
                                </span>
                                
                                <span class="button-checkbox">
                                <button type="button" class="btn criteria buttondashboardstar" data-color="info"> User-friendly interface</button>
                                 <input type="checkbox" class="hidden" id="4" value="4_U"  />
                                 <input type="hidden" id="feedbackans_4" class="myoptnchk" value="NOVAL">
                                </span>
                               
                            </div>
                    </div>
                </section>
                </p>
               
              </div>
              <div class="modal-footer">
                <!--<button type="button" class="btn btn-default" data-dismiss="modal">Close</button>-->
                <input type="hidden" value="NOVAL" name="feedback_ans" id="feedback_ans">
                <input type="hidden" name="frmsubmt" value="frmsubmt">
                <button type="button" class="btn btn-success" id="myratingsubmit">Submit</button>
              </div>
            </div>
        
          </div>
        </div>
        </form>
        <!-- Modal Section End -->
        
        
      </div>
      
      <div class="shadow"></div> 
      
      <!-- Common Return Link start-->
        <?php //print_r($servicedatalc); //echo $servicedata[0]->name."--".$servicedata[0]->ld_pass; exit;?>
        <a target="_blank"href="https://wblc.gov.in/user-authenticate-ld/<?php echo encryption_decryption_wblabour('encrypt', $servicedatalc[0]->name); ?>/<?php echo encryption_decryption_wblabour('encrypt', $servicedatalc[0]->ld_pass); ?>/<?php echo encryption_decryption_wblabour('encrypt', 14); ?>" class="btn temporary-id">Submission of Common Return (CRF)</a>
      <!-- Common Return Link End-->
      
      
      
      
      <!-- Modal -->
      	<form name="addservice" id="addservice" action="" method="post">
        <div id="myModalAddService" class="modal fade" role="dialog">
          <div class="modal-dialog">
        
            <!-- Modal content-->
            <div class="modal-content">
              <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal">&times;</button>
                <h4 class="modal-title">Add More Services</h4>
              </div>
              <div class="modal-body">
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
					$query = db_select('ld_service_master','s');
					$query->leftJoin('ld_act_master', 'a', 'a.id=s.act_id');
					$query->fields('s',array('id','act_id','service_name','directorate_name','directorate_code','service_type'));
					$query->fields('a',array('act_title','directorate_code'));
					$query->condition('s.is_active','Y','=');
					$query->orderBy('s.service_type','ASC');
					$result = $query->execute();
					$result_data = $result->fetchAll();
					
					
				
                	$i = 0;
					if(!empty($result_data)){
					foreach($result_data as $data){ $i++;
					
					/*$query1 = db_select('ld_user_service_info', 'us');
					$query1->leftJoin('ld_service_master', 's', 'us.service_id=s.id');
					$query1 ->fields('us', array( 'id','uid','service_id','application_time'));
					$query->fields('s',array('id','act_id','directorate_code'));
					$query1->condition('us.uid',trim($user->uid),'=');
					$query1->condition('us.service_id',trim($data->id),'=');
					//$query1->condition('us.service_id',trim($data->service_id),'=');
					$query1->condition('s.directorate_code','LC','=');
					$result1 = $query1->execute();
					$result_data1 = $result1->fetchAll();*/
					
					$query1 = db_select('ld_user_service_info','us');
					$query1->fields('us',array('id','uid','service_id','application_time'));
					$query1->condition('us.uid',trim($user->uid),'=');
					$query1->condition('us.service_id',trim($data->id),'=');
					$result1 = $query1->execute(); 
					$result_data1 = $result1->fetchAll();
					
					if(empty($result_data1)){
					?>
					
					  <tr class="even pointer">
						<td class=" "><?php echo $data->directorate_name;?></td>
						<td class=" "><?php echo $data->service_name.", ".$data->act_title;?></td>
						 <td class=" "><?php if($data->service_type=="1"){ echo "Pre-Establishement";}else if($data->service_type=="2"){echo "Pre-Operation";}else if($data->service_type=="3"){echo "Others";}else{echo "--";}?></td>
						<td class=" "><!--<div class="form-group has-success">
							<label class="cbx-label" for="check-theme-1h"></label>
							<input type="checkbox" checked="checked" id="dt_<?php echo $i;?>" value="<?php echo $data->id;?>" data-toggle="checkbox-x" data-theme="krajee-flatblue" data-three-state="false" data-size="xl">
						  </div>-->	
						  <div class="btn-group checkbox-panel" data-toggle="buttons">
						  <label class="btn btn-default" onClick="checkingUncked()">
						  <input type="checkbox" class="chkelgbltbtn"  name="chk_add_service[]" id="dt_<?php echo $i;?>" value="<?php echo $data->id."_".$data->act_id;?>" autocomplete="off"><span class="glyphicon glyphicon-ok"></span>
						  </label>			
		
		</div></td>
					  </tr>
					  
					<?php }}
						$makeBtnProp = 'processBtnEnabled';
					 }else{ $makeBtnProp='processBtnDisabled';?> 
					 <tr class="even pointer"><td class="" colspan="3"> You are not elligible for any services</td></tr>
					 <?php }?>
					</tbody>
				  </table>
              </div>
              <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                <input type="hidden" name="user_id" value="<?php echo $user->uid;?>">
                <input type="hidden" name="addservice_submit" value="addservice">
                <button type="submit" id="<?php echo $makeBtnProp;?>" class="btn btn-success" data-toggle="modal" data-target="#popup">Add Service</button>
              </div>
            </div>
        
          </div>
        </div>
        </form>
        <!-- Modal End-->
      
      
      
      
      
      	<div class="icon-legend">
        <h2>icon legend</h2>
        <div class="table-responsive">
        <table class="table table-striped jambo_table bulk_action myalign icon-table">
        <tbody>
        <tr>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/applicant_called_by.png" width="" height="" alt=""><span>Application Called By</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/verification.png" width="" height="" alt=""> <span>Verification</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/applied.png" width="" height="" alt=""> <span>Applied</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/approved.png" width="" height="" alt=""> <span>Approved</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/backed.png" width="" height="" alt=""> <span>backed</span></td>
        </tr>
        <tr>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/back_for_correction.png" width="" height="" alt=""> <span>Back for correction</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/error.png" width="" height="" alt=""> <span>Error</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/fees_paid_but_not_final_submit.png" width="" height="" alt=""> <span>Fees Paid but not Final Submit</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/paynow.png" width="" height="" alt=""> <span>Pay Now</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/final_submit.png" width="" height="" alt=""> <span>Final Submit</span></td>
        </tr>
        <tr>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/forward.png" width="" height="" alt=""> <span>Forward</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/incomplete.png" width="" height="" alt=""> <span>Incomplete</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/in_process.png" width="" height="" alt=""> <span>In-Process</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/issued.png" width="" height="" alt=""> <span>Issued</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/pending.png" width="" height="" alt=""> <span>Pending</span></td>
        </tr>
        <tr>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/rectification.png" width="" height="" alt=""> <span>Rectification</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/reject.png" width="" height="" alt=""> <span>Reject</span></td>
        <td><img src="<?php echo $base_root.$base_path;?>sites/all/modules/dashboard/images/fees_pending.png" width="" height="" alt=""> <span>Fees Pending</span></td>
        <td>&nbsp;  </td>
        <td>&nbsp;  </td>
        </tr>
        
        </tbody>
        </table>
        </div>
        </div>

      
      
    </div>
  </div>
</div>
</body>

<!-- jQuery -->
<?php /*?><script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/jquery/dist/jquery.min.js"></script>
<!-- Bootstrap -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/bootstrap/dist/js/bootstrap.min.js"></script>
<!-- FastClick -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/fastclick/lib/fastclick.js"></script>
<!-- NProgress -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/nprogress/nprogress.js"></script><?php */?>
<!-- Chart.js -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/Chart.js/dist/Chart.min.js"></script>
<!-- gauge.js -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/gauge.js/dist/gauge.min.js"></script>
<!-- bootstrap-progressbar -->
<?php /*?><script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/bootstrap-progressbar/bootstrap-progressbar.min.js"></script>
<!-- iCheck -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/iCheck/icheck.min.js"></script>
<!-- Skycons -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/skycons/skycons.js"></script>
<!-- Flot -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.js"></script>
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.pie.js"></script>
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.time.js"></script>
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.stack.js"></script>
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.resize.js"></script>
<!-- Flot plugins -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/flot.orderbars/js/jquery.flot.orderBars.js"></script>
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/flot-spline/js/jquery.flot.spline.min.js"></script>
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/flot.curvedlines/curvedLines.js"></script>
<!-- DateJS -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/DateJS/build/date.js"></script>
<!-- JQVMap -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/jqvmap/dist/jquery.vmap.js"></script>
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/jqvmap/dist/maps/jquery.vmap.world.js"></script>
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/jqvmap/examples/js/jquery.vmap.sampledata.js"></script>
<!-- bootstrap-daterangepicker -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/moment/min/moment.min.js"></script>
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/bootstrap-daterangepicker/daterangepicker.js"></script><?php */?>

<script src="<?php print $base_root.$base_path?>sites/all/modules/dashboard/build/js/star_rating.js"></script>
<!-- Custom Theme Scripts -->
<script src="<?php print $base_root.$base_path?>sites/all/modules/dashboard/build/js/custom.min.js"></script>

<?php
$query_rating = db_select('ld_user_service_star_rating', 'ur');
$query_rating ->fields('ur', array( 'rating','user_service_info_id' ));
$query_rating->condition('ur.uid',trim($user->uid),'=');
$ratingdata = $query_rating->execute();
$ratingrs = $ratingdata->fetchAll();
//print_r($ratingrs); exit();
foreach($ratingrs as $r){
if($r->rating=='0'){
?>
<script type="text/javascript"> 
//$( document ).ready(function() { alert("hi"); });
</script>

<script type="text/javascript"> 
    jQuery(window).on('load',function(){ //alert("hi");
		jQuery('#user_servive_info_id').val('<?php echo $r->user_service_info_id?>');
        jQuery('#myModal').modal('show');
    });
</script>
<?php }}?>
<script type="text/javascript">
jQuery('.collapse').on('shown.bs.collapse', function(){
jQuery(this).parent().find(".glyphicon-plus").removeClass("glyphicon-plus").addClass("glyphicon-minus");
}).on('hidden.bs.collapse', function(){ 
jQuery(this).parent().find(".glyphicon-minus").removeClass("glyphicon-minus").addClass("glyphicon-plus");
});
</script>
