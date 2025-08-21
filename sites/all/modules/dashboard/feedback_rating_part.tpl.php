<?php global $user,$base_root,$base_path,$base_url;
	$authkay=$user->sid;
	$user_name=$user->name;?>

<?php 
?>


<!-- For new Rating -->
<style type="text/css">
  .rating {
  display: inline-block;
  position: relative;
  height: 50px;
  line-height: 50px;
  font-size: 50px;
}

.rating label {
  position: absolute;
  top: 0;
  left: 0;
  height: 100%;
  cursor: pointer;
}

.rating label:last-child {
  position: static;
}

.rating label:nth-child(1) {
  z-index: 5;
}

.rating label:nth-child(2) {
  z-index: 4;
}

.rating label:nth-child(3) {
  z-index: 3;
}

.rating label:nth-child(4) {
  z-index: 2;
}

.rating label:nth-child(5) {
  z-index: 1;
}

.rating label input {
  position: absolute;
  top: 0;
  left: 0;
  opacity: 0;
}

.rating label .icon {
  float: left;
  color: transparent;
}

.rating label:last-child .icon {
  color: #000;
}

.rating:not(:hover) label input:checked ~ .icon,
.rating:hover label:hover input ~ .icon {
  color: #09f;
}

.rating label input:focus:not(:checked) ~ .icon:last-child {
  color: #000;
  text-shadow: 0 0 5px #09f;
}
</style>
<!-- For new Rating End -->

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
<!-- <link href="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/build/css/custom.css" rel="stylesheet"> -->

<body class="nav-md" onLoad="init_chart_doughnut_edit('<?php echo $lc_service_count?>','<?php echo $boilers_service_count?>','<?php echo $factory_service_count?>','<?php echo $shops_service_count?>')">
	
	
<div class="row">
 <!-- <h4 class="brief"><div class="col-md-12">Welcome on Board</div></h4> -->
  
  
  <div class="col-md-12 col-sm-12 col-xs-12">
    <div class="x_content">
      <div class="accordion" id="accordion" role="tablist" aria-multiselectable="true">
      
      
        
        
        
        
        <!-- Modal Section Start-->
        <form name="modalfrm" id="modalfrm" action="" method="post"  >
        <div id="myModal" class="feedback" role="dialog" data-backdrop="static" style="display:block;">
          <div class="modal-dialog">
            <div class="modal-content">
              <div class="modal-header">
                <!-- <button type="button" class="close" data-dismiss="modal">&times;</button> -->
                <h4 class="modal-title">Rate your experience</h4>
                <input type="hidden" id="user_servive_info_id" name="user_servive_info_id" value="">
              </div>
              <div class="modal-body">
				  
                    <div class="evaluation">
						<div class="quality" id="meaning"></div>
                        <div id="colorstar" class="starrr ratable" ></div>
						
                            <div class="indicators" style="display:block">
                                <!-- <div class="why" id="textwr">What went wrong?</div> -->
                               <!-- <form class="rating"> -->
                                <div class="rating" >
                                <label>
                                  <input type="radio" name="stars" value="1" />
                                  <span class="icon">★</span>
                                </label>
                                <label>
                                  <input type="radio" name="stars" value="2" />
                                  <span class="icon">★</span>
                                  <span class="icon">★</span>
                                </label>
                                <label>
                                  <input type="radio" name="stars" value="3" />
                                  <span class="icon">★</span>
                                  <span class="icon">★</span>
                                  <span class="icon">★</span>   
                                </label>
                                <label>
                                  <input type="radio" name="stars" value="4" />
                                  <span class="icon">★</span>
                                  <span class="icon">★</span>
                                  <span class="icon">★</span>
                                  <span class="icon">★</span>
                                </label>
                                <label>
                                  <input type="radio" name="stars" value="5" />
                                  <span class="icon">★</span>
                                  <span class="icon">★</span>
                                  <span class="icon">★</span>
                                  <span class="icon">★</span>
                                  <span class="icon">★</span>
                                </label>
                              <!-- </form> -->
								                </div>
                								
                               
                            </div>
                            <input type="hidden" name="id_star" id="id_star">
                            <textarea name="feedback_txt" id="feedback_txt" placeholder="Please enter your feedback"></textarea>
                    </div>
                
				  
			 </div>  
              <div class="modal-footer">
                <input type="hidden" value="NOVAL" name="feedback_ans" id="feedback_ans">
                <input type="hidden" name="frmsubmt" value="frmsubmt">
                <button type="button" class="btn btn-success" id="myratingsubmit_1">Submit</button>
              </div>
            </div>
        
          </div>
        </div>
        </form>
        
        
      </div>
      
      <div class="shadow"></div> 
      
     
      
      
      
      
   
     
      
      
      	

      
      
    </div>
  </div>
</div>




</body>


<!-- Chart.js -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/Chart.js/dist/Chart.min.js"></script>
<!-- gauge.js -->
<script src="<?php print $base_root.$base_path ?>sites/all/modules/dashboard/vendors/gauge.js/dist/gauge.min.js"></script>

<script src="<?php print $base_root.$base_path?>sites/all/modules/dashboard/build/js/star_rating.js"></script>
<!-- Custom Theme Scripts -->
<script src="<?php print $base_root.$base_path?>sites/all/modules/dashboard/build/js/custom.min.js"></script>

<?php
$query_rating = db_select('ld_user_service_star_rating', 'ur');
$query_rating ->fields('ur', array( 'rating','user_service_info_id' ));
$query_rating->condition('ur.uid',trim($user->uid),'=');
$ratingdata = $query_rating->execute();
$ratingrs = $ratingdata->fetchAll();
foreach($ratingrs as $r){
if($r->rating=='0'){
?>
<script type="text/javascript">
    jQuery(window).on('load',function(){
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

/*---------  For new Rating  ----------*/
$(':radio').change(function() {
  $('#id_star').val(this.value);
  console.log('New star rating: ' + this.value);
  //alert('New star rating: ' + this.value);
});

$('#myratingsubmit_1').click(function(){
  alert('New star rating: ' + $('#id_star').val());
  alert('Message:- '+$('#feedback_txt').val());
});

</script>
