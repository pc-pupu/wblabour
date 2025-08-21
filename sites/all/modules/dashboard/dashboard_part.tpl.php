<?php global $user,$base_root,$base_path,$base_url; ?>

<?php if($_REQUEST['frmsubmt'] == 'frmsubmt' && $_REQUEST['user_servive_info_id']!=""){
	$query_rating = db_update('ld_user_service_star_rating');
	$query_rating->fields(array('rating'=>$_REQUEST['rating'][0]));
	$query_rating->condition('uid',trim($user->uid),'=');
	$query_rating->condition('user_service_info_id',trim($_REQUEST['user_servive_info_id']),'=');
	$rs = $query_rating->execute();
}

	$last_2_digit_current_yr = date("y");
	$qry = db_query("select LPAD( cast(v.mid+1 as bigint) :: text,6,'0') from (select max(clin_no) as mid, extract(YEAR from created_date) as yr from ld_establishment_details group by extract(YEAR from created_date) )v where v.yr = ". date('Y'));
	$result =$qry->fetchall();
	//echo $result[0]->lpad;

	$estservice_list_query = db_select('ld_user_service_info', 'us');
	$estservice_list_query ->leftJoin('ld_establishment_details', 'led', 'us.est_id = led.est_id');
	$estservice_list_query ->fields('led', array( 'est_id','e_clinid','clin_no','district','subdivision', 'created_date'));
	$estservice_list_query ->fields('us', array( 'service_id','status','directorate_code' ));
	$estservice_list_query ->condition('us.uid',trim($user->uid),'=');
	$service = $estservice_list_query->execute();
	$servicedata = $service->fetchAll();
	//print_r($servicedata); exit;
	foreach($servicedata as $val){
		 $district_code = str_pad($val->district,2,'0',STR_PAD_LEFT);
		 $sub_div_last_2_digit = substr(trim($val->subdivision), -2);
		
		
		//echo "-->".date('y',strtotime($val->created_date));
		if(trim($val->directorate_code)=='LC'){
			if(trim($val->service_id)=='1' && trim($val->status)=='0'){
				insertStarRatingTable($user->uid,$val->service_id);
			}
			if(trim($val->service_id)=='2' && trim($val->status)=='0'){
				insertStarRatingTable($user->uid,$val->service_id);
			}
			if(trim($val->service_id)=='3' && trim($val->status)=='0'){
				insertStarRatingTable($user->uid,$val->service_id);
			}
			if(trim($val->service_id)=='4' && trim($val->status)=='0'){
				insertStarRatingTable($user->uid,$val->service_id);
			}
			if(trim($val->status)=='I'){
				$CLIN_NO = trim($district_code).trim($sub_div_last_2_digit).trim($last_2_digit_current_yr).trim($result[0]->lpad);
				updateClin($val->est_id,$val->e_clinid,$val->clin_no,$CLIN_NO,$result[0]->lpad);
			}
		}
		if(trim($val->directorate_code)=='B'){
			if(trim($val->service_id)=='32' && trim($val->status)=='3'){
				insertStarRatingTable($user->uid,$val->service_id);
			}
			if(trim($val->service_id)=='33' && trim($val->status)=='3'){
				insertStarRatingTable($user->uid,$val->service_id);
			}
			if(trim($val->status)=='5'){
				updateClin($val->est_id,$val->e_clinid,$val->clin_no,$CLIN_NO,$result[0]->lpad);
			}
		}
		if(trim($val->directorate_code)=='F'){
			if(trim($val->service_id)=='46' && trim($val->status)=='4'){
				insertStarRatingTable($user->uid,$val->service_id);
			}
			if(trim($val->service_id)=='44' && trim($val->status)=='4'){
				insertStarRatingTable($user->uid,$val->service_id);
			}
			if(trim($val->service_id)=='45' && trim($val->status)=='4'){
				insertStarRatingTable($user->uid,$val->service_id);
			}
			if(trim($val->status)=='16'){
				$CLIN_NO = trim($district_code).trim($sub_div_last_2_digit).trim($last_2_digit_current_yr).trim($result[0]->lpad);
				updateClin($val->est_id,$val->e_clinid,$val->clin_no,$CLIN_NO,$result[0]->lpad);
			}
		}
		
	}
	
	function insertStarRatingTable($user_id,$user_service_info_id){
		//echo "--->".$user_id."-->".$user_service_info_id; exit;
		$query_chk_rating = db_select('ld_user_service_star_rating', 'ur');
		$query_chk_rating ->fields('ur', array( 'id' ));
		$query_chk_rating->condition('ur.uid',trim($user_id),'=');
		$query_chk_rating->condition('ur.user_service_info_id',$user_service_info_id,'=');
		$rating = $query_chk_rating->execute();
		$ratingdata = $rating->fetchAssoc();
		//print_r($ratingdata); exit;
		if(empty($ratingdata)){
			$rating 		= 	array(
				'uid' 			=> $user_id,
				'user_service_info_id' 	=> $user_service_info_id, 
				'rating' 		=> 0, 
			);
			db_insert('ld_user_service_star_rating')->fields($rating)->execute();
		}
	}
	
	function updateClin($est_id,$e_clinid,$clin_no,$GEN_CLIN_NO,$lpad_v){
		if($e_clinid == "" && $clin_no == 0){
			$query = db_update('ld_establishment_details');
			$query->fields(array('e_clinid'=>trim($GEN_CLIN_NO),'clin_no'=>trim($lpad_v)));
			$query->condition('est_id',trim($est_id),'=');
			$query->execute();
		}
	}
?>

<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/bootstrap/dist/css/bootstrap.min.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/bootstrap/dist/css/star_rating.css" rel="stylesheet">
<!--<link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/build/css/star_rating.css" rel="stylesheet">-->

		
        
        
        
        
        
        
        <h3 class="page-heading mb-4">Welcome on Board</h3>
                    <div class="row">
                        <div class="col-xl-4 col-lg-4 col-md-4 col-sm-6 mb-4">
                            <div class="card card-statistics total-registration-box">
                                <div class="card-body">
                                    <div class="clearfix">
                                        <div class="float-left">
                                            <h4 class="text-white">
												<i class="fa fa-chart-bar highlight-icon" aria-hidden="true"></i>
											  </h4>
                                        </div>
                                        <div class="float-right">
                                            <p class="card-text text-white">Services</p>
                                            <h4 class="bold-text text-white">97</h4>
                                        </div>
                                    </div>
                                    <p class="text-white"><i class="fa fa-box-open"></i> Services Available</p>
                                </div>
                            </div>
                        </div>
                        <div class="col-xl-4 col-lg-4 col-md-4 col-sm-6 mb-4">
                            <div class="card card-statistics lc-box">
                                <div class="card-body">
                                    <div class="clearfix">
                                        <div class="float-left">
                                            <h4 class="text-white">
											  <i class="fa fa-chart-line highlight-icon"></i>
										  </h4>
                                        </div>
                                        <div class="float-right">
                                            <p class="card-text text-white">Services Availed</p>
                                            <h4 class="bold-text text-white">0</h4>
                                        </div>
                                    </div>
                                    <p class="text-white"><i class="fa fa-box-open"></i> &nbsp; </p>
                                </div>
                            </div>
                        </div>
                        <div class="col-xl-4 col-lg-4 col-md-4 col-sm-6 mb-4">
                            <div class="card card-statistics boiler-box">
                                <div class="card-body">
                                    <div class="clearfix">
                                        <div class="float-left">
                                            <h4 class="text-white">
											<i class="fa fa-chart-pie highlight-icon"></i>
										  </h4>
                                        </div>
                                        <div class="float-right">
                                            <p class="card-text text-white">Application Submitted</p>
                                            <h4 class="bold-text text-white">650</h4>
                                        </div>
                                    </div>
                                    <p class="text-white"><i class="fa fa-box-open"></i> &nbsp; </p>
                                </div>
                            </div>
                        </div>
                        <!--<div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 mb-4">
                            <div class="card card-statistics factories-box">
                                <div class="card-body">
                                    <div class="clearfix">
                                        <div class="float-left">
                                            <h4 class="text-white">
											<i class="fa fa-signal highlight-icon"></i>
										  </h4>
                                        </div>
                                        <div class="float-right">
                                            <p class="card-text text-white">Directorate of Factories</p>
                                            <h4 class="bold-text text-white">625</h4>
                                        </div>
                                    </div>
                                    <p class="text-white"><i class="fa fa-box-open"></i> Total Services </p>
                                </div>
                            </div>
                        </div>-->
                    </div>

                    <div class="row mb-4">
                        <div class="col-xl-12 col-lg-12 col-md-12 col-sm-12">
                            <div class="card">
                                <div class="card-body">
                                    <div class="row">
                                        <div class="col-xl-12 col-lg-12 col-md-12 col-sm-12 col-xs-12">
											<div class="card-title mb-4">
												<h5>All Establishment Locations</h5>
												<div class="add"><a href="<?php print $base_root.$base_path?>add-establishment"><img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/icons/plus.png" alt=""> Add </a></div>
											</div>
                                             <?php print $mydata_table;?>
                                        </div>
                                        <!-- <div class="col-xl-7 col-lg-7 col-md-12 col-sm-12 col-xs-12 map">
                                            <iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d3684.2539852778664!2d88.34098931495953!3d22.569602085184307!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x3a0277a200f6df61%3A0xca19a1b2688346e!2sNew+Secretariat+Building!5e0!3m2!1sen!2sin!4v1533894126896" width="100%" height="420" frameborder="0"  allowfullscreen></iframe>
                                        </div> -->

                                        <div class="col-xl-12 col-lg-12 col-md-12 col-sm-12 col-xs-12 map">
                                           <?php print $map;?>
                                        </div>

                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                    
                    





        <!-- Modal Section Start-->
        <form name="modalfrm" id="modalfrm" action="" method="post">
        <div id="myModal" class="modal fade" role="dialog" data-backdrop="static">
          <div class="modal-dialog">
        
            <!-- Modal content-->
            <div class="modal-content">
              <div class="modal-header">
                <h4 class="modal-title">Please Rate your valuable feedback which will help us to improve better</h4>
                <button type="button" class="close" data-dismiss="modal">&times;</button>
                <input type="hidden" id="user_servive_info_id" name="user_servive_info_id" value="">
              </div>
              <div class="modal-body">
                <p>
                <section>
                    <div class="lead evaluation">
                    	<div class="myerr_msg" style="display:none"></div>
                        <div id="colorstar" class="starrr ratable" ></div>
                        <span id="count">0</span> star(s) - <span id="meaning"></span><br><br>
                            <div class='indicators' style="display:none">
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
       

                    

         