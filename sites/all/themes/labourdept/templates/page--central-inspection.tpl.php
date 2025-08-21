<?php global $base_root,$base_path,$user;
$url = '';
$url_tmpdashboard='';
$url_login_page='';
$urlarr = $_SERVER['HTTP_HOST'] . request_uri();
$urlarr = explode("/",$urlarr);
if (in_array("cmsentry", $urlarr)){
	$url = 'LEFTPANNEL';
}
if (in_array("tmpdashboard", $urlarr)){
	$url_tmpdashboard = 'TEMPORARY_DASHBOARD';
}
if (in_array("login", $urlarr)){
	$url_login_page = 'LOGIN';
}


$query_get_schedule = db_select('ld_inspection_schedule', 's');
$query_get_schedule->fields('s', array('id','from_dt','to_dt','directorate_code','confirm_flag'));
$query_get_schedule->condition('confirm_flag', '1');
$query_get_schedule->orderBy('s.id','DESC');
$query_get_schedule->range(0, 1);
$result_get_rs = $query_get_schedule->execute();
$result_get_schedule_data = $result_get_rs->fetchAssoc();
if(!empty($result_get_schedule_data)){
	$disabled_upto = format_date(strtotime($result_get_schedule_data['to_dt']), 'custom', 'd-m-Y');
}
//print_r($result_get_schedule_data);
?>

<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/style.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/inner-page.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/responsive.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/bootstrap.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/font-awesome.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/style2.css" rel="stylesheet">
<!--<link href='https://fonts.googleapis.com/css?family=Lato:400,300,100,700,900' rel='stylesheet' type='text/css'>-->
<!--<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.min.js"></script> -->   
<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery-1.9.1.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/bootstrap.min.js"></script> 
<!--for bootstrap datepicker-->
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/bootstrap-datepicker.css" rel="stylesheet">
<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/bootstrap-datepicker.js"></script>  

<!--</script><script type="text/javascript" src="//translate.google.com/translate_a/element.js?cb=googleTranslateElementInit"></script>
<script type="text/javascript">
function googleTranslateElementInit() {
  new google.translate.TranslateElement({pageLanguage: 'en',includedLanguages: 'en,bn,hi', layout: google.translate.TranslateElement.InlineLayout.SIMPLE}, 'google_translate_element');
}
</script>-->

<header>
  <div class="whitebg1 navbar-static-top header">
    <div class="container">
      <div class="row clearfix">
        <div class="col-sm-6">
        	<div class="social_media">
            	<i class="fa fa-twitter-square" aria-hidden="true"></i>
                <i class="fa fa-facebook-square" aria-hidden="true"></i>
            </div>
            <!--<div class="google_translate_box"><div id="google_translate_element"></div></div>-->
        </div>
        <div class="col-sm-6">
        	<div class="register">
            	<div id="google_translate_element"></div>
            	<!--<i class="fa fa-sign-in" aria-hidden="true"></i> <a href="#" class="login_link">Login</a> &nbsp;&nbsp;&nbsp;-->
                 <?php if(user_is_logged_in()){?>
                <i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>user/logout" class="login_link">Logout</a>&nbsp;&nbsp;&nbsp;
                    <?php }else{?>
						<i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>enlogin" class="login_link">Login</a>&nbsp;&nbsp;&nbsp;
                        <i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>user" class="login_link">Admin Login</a>&nbsp;&nbsp;&nbsp;
                      <?php }?> 
             <!--   <i class="fa fa-pencil-square-o" aria-hidden="true"></i> 
                <a href="#" class="login_link">Register</a>&nbsp;&nbsp;&nbsp; -->
                <a href="#" id="large"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon3.png" alt=""> </a>
                		<a href="#" id="small"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon4.png" alt=""></a>
                		<a href="#" id="medium" class="selected"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon5.png" alt=""></a>
                 		<a href="javascript:void(0)"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon6.png" alt="" onClick="backchng();"></a>
            </div>
        </div>
        
      </div>
    </div>
  </div>
  <div class="bluebg">
    <div class="container">
      <div class="row">
        <div class="logobg clearfix">
          <div class="col-sm-6">
          	<div class="logo_new">
            	<?php if ($logo): ?>
                  <a href="<?php print $front_page; ?>" title="<?php print t('Department of Labour'); ?>" rel="home" id="logo">
                    <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="logo-img" />
                  </a>
                <?php endif; ?>
            </div>
          </div>
          <div class="col-sm-6">
          <div class="Awards-btm">
          <a href="<?php print $base_root.$base_path?>awards-and-achievements" title="Awards & Achievements">
          <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/Awards_btm.gif" alt=""></a>
          </div>
            <div class="serach_padding">
              <!--<div id="imaginary_container">
                <div class="input-group stylish-input-group">
                  <input type="text" class="form-control"  placeholder="Search" >
                  <span class="input-group-addon">
                  <button type="submit"> <span class="glyphicon glyphicon-search"></span> </button>
                  </span> </div>
              </div>
              <input name="" type="text" placeholder="Search" class="top_search"> 
              <button type="submit"><span class="glyphicon glyphicon-search"></span></button>-->
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  
  <div class="greenbg">
    <nav class="navbar navbar-default navbar-static-top">
      <div class="container">
        <div class="navbar-header">
          <button aria-controls="navbar" aria-expanded="false" data-target="#navbar" data-toggle="collapse" class="navbar-toggle collapsed" type="button"> <span class="sr-only">Toggle navigation</span> <span class="icon-bar"></span> <span class="icon-bar"></span> <span class="icon-bar"></span> </button>
        </div>
        <div class="navbar-collapse collapse" id="navbar">
           <?php  
		   if (($user->uid!=0) && array_key_exists(5, $user->roles)) {
			   
			  $tree = menu_tree_all_data('menu-dashboard');
			  ?>
              
			  <ul class="nav navbar-nav">
            <?php foreach($tree as $val){
				$link = drupal_get_path_alias($val['link']['link_path']);
				if($val['link']['link_path']=='comprehensive-information-sheet'){
					if($url_tmpdashboard!='TEMPORARY_DASHBOARD'){
				?>
                <li><a href="<?php print $link;?>"><?php print $val['link']['link_title'];?></a></li>
                <?php }}else{?>
              <li><a href="<?php print $link;?>"><?php print $val['link']['link_title'];?></a></li>
              <?php }}?>
			  </ul>
              
			<?php }elseif (($user->uid!=0) && array_key_exists(2, $user->roles)) {
					if (in_array("cmsentry", $urlarr)){
						$dashboard_link = $base_root.$base_path.$urlarr[1]."/"."cmscircular";
					}else{
						$dashboard_link = "cmsentry/cmscircular";
					}
				 ?>
				<ul class="nav navbar-nav">
					<li><a href="<?php print $dashboard_link;?>">Dashboard</a></li>
				</ul>
			<?php }else{
				print render($page['top_links']);
			}
		  ?>
        </div>
        <!--/.nav-collapse --> 
      </div>
    </nav>
  </div>
  
  
    <?php /*?><div class="about_banner">
	<div class="container">
    	<h2><?php //print $title;?></h2>
    </div>
</div><?php */?>

    
    <!-- Controls --> 
      <!--</div>-->
  
</header>
<!--start body here-->
        
        

  <div class="whitebg2"> 
  <div class="about_body">
	<!-- container starts here -->
    
 <div class="container">
 	<div class="row"> 
    	<?php if (!array_key_exists(5, $user->roles)) {?>
		<?php //print $breadcrumb; ?>
        <?php }?>
        <?php if($messages){ print $messages; } ?>
       <?php //print_r(menu_navigation_links('menu-about-us-menu'));?>
       <?php
	   	$_SERVER['REQUEST_URI_PATH'] = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);
		$segments = explode('/', $_SERVER['REQUEST_URI_PATH']);
		$uri = @$segments[1]; 
	   ?>
      <?php 
	  	$content_type = isset($node) ? $node->type : '';
		//echo $node->type;
	    //$content_type = node_type_get_name($node);
	  	if($content_type == 'contact_us' || $content_type== 'services' || $content_type == 'about_us' || $content_type=='b_easy' || $content_type == 'citizen_corner' || $content_type == 'rti' || $content_type == 'boards_spio_sapio' || $content_type == 'spios_and_sapios' || $content_type == 'boards' || $content_type == 'forms_and_procedures' || $uri == 'may-we-help-you' || $url == 'LEFTPANNEL'){
	  ?> 
      <div class="sidebar_box">
         <div class="col-xs-12  col-md-4 sidebar-left">
								

								<ul class="practice-listing">
                                	<?php if($content_type == 'contact_us'){
                                 	 //print render($page['contact_us_menu']); 
									$menu = menu_navigation_links('menu-common-left-menu');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									

                                   	}else if($content_type == 'services'){
										
									// print render($page['services_menu']);
									
									$menu = menu_navigation_links('menu-services-menu');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									
									}else if($content_type == 'about_us'){
									 //print render($page['about_us_menu']);
									 
									 $menu = menu_navigation_links('menu-about-us-menu');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									 
									}else if ($content_type == 'b_easy'){
										
										$menu = menu_navigation_links('menu-b-easy-menu');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									
									}else if ($content_type == 'citizen_corner' || $uri == 'may-we-help-you'){
										
										$menu = menu_navigation_links('menu-citizen-corner-menu');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									
									}else if ($content_type == 'rti'){
										
										$menu = menu_navigation_links('menu-rti');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									
									}else if ($content_type == 'spios_and_sapios'){
										
										$menu = menu_navigation_links('menu-list-of-spio-sapio');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									
									}									
									else if ($content_type == 'boards'){
										
										$menu = menu_navigation_links('menu-boards-menu');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									
									}
									else if ($content_type == 'boards_spio_sapio'){
										
										$menu = menu_navigation_links('menu-list-of-spio-sapio-boards');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									
									}else if ($content_type == 'forms_and_procedures'){
										
										$menu = menu_navigation_links('menu-forms-and-procedures');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									
									}
									else if ($url == 'LEFTPANNEL'){
										
										$menu = menu_navigation_links('menu-content-management');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									
									}
									
									?>
                                    
								</ul>
							</div>
          </div>
          
          <div class="about_body_main col-md-8 custom-form-class">
        
        	<!-- about_one starts here -->
            <div class="about_one">
            
            	<h1><span><?php print $title[0];?></span><?php print substr($title, 1); ?></h1>
                      <!--Labour Department-->
                      <!--<div class="contact_area animated bounceIn">-->
                      <?php print render($page['content']); ?>
                     <!-- </div>-->
                      <!--Labour Department-->
 
            </div>
        </div>
		<?php }else{?>
        	
        	<div class="about_body_main col-md-12 custom-form-class">
        	<!-- about_one starts here -->
            <div class="about_one">
        	
   
   			<?php print render($page['content']); ?>
    
            </div>
            </div>
        <?php }?>
        
    </div>
 </div>
  
 
 <?php if (!array_key_exists(5, $user->roles)) {
	 	if($url_login_page != 'LOGIN'){ 
	 
	 ?> 
  
  <div class="section5 text-center"> 
      <div class="section5inner">  
        <h2>If you have any questions, please feel free to drop us a line</h2>
        <a href="may-we-help-you" class="btn-style-three">click Here</a>
      </div>
    </div> 
  <?php }}?>
  
  
</div>
<!--end body here-->

</div>



<footer>

 <?php if (array_key_exists(2, $user->roles)) { }
 elseif (!array_key_exists(5, $user->roles)) {?> 
<div class="footer-top-wrapper">
    <div class="container">
        <?php print render($page['labour_footer']);?>
    </div>
</div>
<?php }?>


<div class="footer-bottom-wrapper">
    <div class="container">

     
    <div class="footer_link">
      <div class="footer_box">
         <div class="row">
           <div class="col-md-12">
             <?php print render($page['labour_footer1']);?>
             Last Updated On : <?php echo date('d-m-Y');?>
            <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/nic_logo.png" class="img-responsive" align="middle" style="margin-top:-42px;">
            </div>
           </div>
         </div>
      </div>
    
    </div>
</div>

</footer>

<!-- jQuery (necessary for Bootstrap's JavaScript plugins) --> 


<!-- Include all compiled plugins (below), or include individual files as needed --> 
<?php /*?><script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/textresize.js"></script> 

<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/bootstrap.min.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/news.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/news2.js"></script>
        
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/owl.carousel.min.js"></script>
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.scrollUp.js"></script>
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/script.js"></script>
<script type="text/javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/tickerme.min.js"></script>
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/wow.min.js"></script>


<!----slid4e_menu----->
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jasny-bootstrap.min.js"></script>
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/main.js"></script><?php */?>
<style>
/*.markholiday{
	color:#FF0000;
}*/
/*Sunday*/
.calendar-table table tr td:first-child {
color: red;
}
/*Monday*/
.calendar-table table tr td:first-child +td {
color:#06F;
}
/*Saturday*/
.calendar-table table tr td:first-child +td +td +td +td +td +td{
color:red;
}
</style>
<link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-daterangepicker/daterangepicker.css" rel="stylesheet">
<!-- bootstrap-daterangepicker -->
 <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/moment/min/moment.min.js"></script>
 <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-daterangepicker/daterangepicker.js"></script>
<script type="text/javascript">
	// When the document is ready
	jQuery(document).ready(function(){
		//var holidays = ["02-09-2017","03-09-2017","04-09-2017"];
		/*jQuery('#inspectionrange').daterangepicker({
			isInvalidDate: function(date) {
			  return (date.day() == 0 || date.day() == 6 || date.day() == 1 || date.format('DD-MM-YYYY') == '23-11-2017');
			  if (date.format('YYYY-MM-DD') == '2017-11-20') {
					return true; 
				} else {
					return false; 
				}
			}
		});*/
		jQuery('#inspectionrange').daterangepicker(
		{
			autoUpdateInput: false,
			//dateLimit: { months: 3 },
			//linkedCalendars: false,
			isInvalidDate: function(date) {
			  var disable_upto = moment('<?php echo $disabled_upto;?>', 'DD-MM-YYYY');
			  //var disabled_start = moment('13-09-2017', 'DD-MM-YYYY');
			  //var disabled_end = moment('21-09-2017', 'DD-MM-YYYY');
			  //return date.isAfter(disabled_start) && date.isBefore(disabled_end);
			  	
			  /*return (date.day() == 0 || date.day() == 6 || date.day() == 1 || 
			  date.format('DD-MM-YYYY') == ['19-09-2017'] || date.format('DD-MM-YYYY') == ['26-09-2017'] || date.format('DD-MM-YYYY') == ['27-09-2017'] || 
			  date.format('DD-MM-YYYY') == ['28-09-2017'] || date.format('DD-MM-YYYY') == ['29-09-2017'] || date.format('DD-MM-YYYY') == ['30-09-2017'] ||
			  date.format('DD-MM-YYYY') == ['01-10-2017'] || date.format('DD-MM-YYYY') == ['02-10-2017'] || date.format('DD-MM-YYYY') == ['03-10-2017'] ||
			  date.format('DD-MM-YYYY') == ['04-10-2017'] || date.format('DD-MM-YYYY') == ['05-10-2017'] || date.format('DD-MM-YYYY') == ['06-10-2017'] ||
			  date.format('DD-MM-YYYY') == ['19-10-2017'] || date.format('DD-MM-YYYY') == ['20-10-2017'] || (date<=disable_upto));*/
			  
			  return (date.day() == 0 || date.day() == 6 || date.day() == 1 || 
			  date.format('DD-MM-YYYY') == ['01-01-2018'] || date.format('DD-MM-YYYY') == ['12-01-2018'] || date.format('DD-MM-YYYY') == ['22-01-2018'] || 
			  date.format('DD-MM-YYYY') == ['23-01-2018'] || date.format('DD-MM-YYYY') == ['26-01-2018'] || date.format('DD-MM-YYYY') == ['14-02-2018'] ||
			  date.format('DD-MM-YYYY') == ['01-03-2018'] || date.format('DD-MM-YYYY') == ['02-03-2018'] || date.format('DD-MM-YYYY') == ['30-03-2018'] ||
			  date.format('DD-MM-YYYY') == ['01-05-2018'] || date.format('DD-MM-YYYY') == ['09-05-2018'] || date.format('DD-MM-YYYY') == ['15-08-2018'] ||
			  date.format('DD-MM-YYYY') == ['22-08-2018'] || date.format('DD-MM-YYYY') == ['03-09-2018'] || (date<=disable_upto));
			},
			locale: {
			  format: 'DD-MM-YYYY'
			},
			minDate: new Date(),
			maxDate: '31-12-2018'
		}, 
		function(start, end, label) {
			alert("A new date range was chosen: " + start.format('DD-MM-YYYY') + ' to ' + end.format('DD-MM-YYYY'));
		});
		
		
		jQuery('#inspectionrange').on('apply.daterangepicker', function(ev, picker) {
			  $(this).val(picker.startDate.format('DD-MM-YYYY') + ' to ' + picker.endDate.format('DD-MM-YYYY'));
		 });
		
		jQuery('#inspectionrange').on('cancel.daterangepicker', function(ev, picker) {
			  $(this).val('');
		 });

		 
	
	});
</script>
    

 <script>
////********************** Disable Mouse Right Click, Cut, Copy & Paste ******************************///////////

jQuery(document).ready(function () {
    //Disable cut copy paste
    jQuery('body').bind('cut copy paste', function(e) {
        e.preventDefault();
    });
   
    //Disable mouse right click
    jQuery("body").on("contextmenu",function(e){
        return false;
    });
});
</script>           










