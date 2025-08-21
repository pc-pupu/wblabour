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

?>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/style.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/inner-page.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/responsive.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/bootstrap.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/font-awesome.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/style2.css" rel="stylesheet">
<link href='https://fonts.googleapis.com/css?family=Lato:400,300,100,700,900' rel='stylesheet' type='text/css'>
<!--<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.min.js"></script> -->   
<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery-1.9.1.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/bootstrap.min.js"></script> 
<!--for bootstrap datepicker-->
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/bootstrap-datepicker.css" rel="stylesheet">
<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/bootstrap-datepicker.js"></script>  

<!--<script type="text/javascript" src="//translate.google.com/translate_a/element.js?cb=googleTranslateElementInit"></script>
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
                <a href="<?php print $base_root.$base_path?>screen-reader-access" class="login_link" style="margin-top: 9px;float: right;margin-left: 10px;"><i class="fa fa-sign-in" aria-hidden="true"></i> Screen Reader Access</a>
            </div>
            <!--<div class="google_translate_box"><div id="google_translate_element"></div></div>-->
        </div>
         <div class="col-sm-6 col-md-4 pull-right">
        	<div class="register">
            <div class="login-panel">  
            	<div id="google_translate_element"></div>
            	<!--<i class="fa fa-sign-in" aria-hidden="true"></i> <a href="#" class="login_link">Login</a> &nbsp;&nbsp;&nbsp;-->
                 <?php if(user_is_logged_in()){?>
                <i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>user/logout" class="login_link">Logout</a>&nbsp;&nbsp;&nbsp;
                    <?php }else{?>
                    
						<!--<i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>enlogin" class="login_link">Login</a>&nbsp;&nbsp;&nbsp;-->
                        <i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>assetlogin" class="login_link">Employee Login</a>&nbsp;&nbsp;&nbsp;
                        <i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>user" class="login_link">Admin Login</a>&nbsp;&nbsp;&nbsp;
                      <?php }?> 
                      </div>
             <!--   <i class="fa fa-pencil-square-o" aria-hidden="true"></i> 
                <a href="#" class="login_link">Register</a>&nbsp;&nbsp;&nbsp; -->
                <div class="text-icon">
                <a href="#" id="large"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon3.png" alt=""> </a>
                		<a href="#" id="small"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon4.png" alt=""></a>
                		<a href="#" id="medium" class="selected"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon5.png" alt=""></a>
                 		<a href="javascript:void(0)"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon6.png" alt="" onClick="backchng();"></a>
                        </div>
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
                  <a href="<?php print $front_page; ?>" title="<?php print t('Single Window Clearance System'); ?>" rel="home" id="logo">
                    <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="logo-img" />
                  </a>
                <?php endif; ?>
            </div>
          </div>
          <div class="col-sm-6">
          <!--<div class="Awards-btm">
          <a href="<?php print $base_root.$base_path?>awards-and-achievements" title="Awards & Achievements">
          <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/Awards_btm.gif" alt=""></a> Department of Labour
          </div>-->
          <div class="cm-pic">
          	<!-- <img src="<?php //print $base_root.$base_path?>sites/all/themes/labourdept/images/cm.png" alt="CM"> -->
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

  <?php
  // if(isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] === 'on')
  // {
  // 	$currentUrl = "https://"; 
  // }   
           
   
            
    // Append the host(domain name, ip) to the URL.   
    //$currentUrl.= $_SERVER['HTTP_HOST'];   
    
    // Append the requested resource location to the URL   
    $currentUrl = $_SERVER['REQUEST_URI'];    
      
    if($currentUrl!='/may-we-help-you' && $currentUrl!='/may-we-help-you/add') { 

  ?>

  <div class="custom-feedback">

  <a href="<?php print $base_root.$base_path?>may-we-help-you/" class="feedback-btn" style="color: white!important; text-decoration: none!important;">Feedback</a>
    

  </div>
  

  <?php
}

  ?>
  
  
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
  <div class="about_body login_msg_off">
	<!-- container starts here -->
    
 <div class="container">
 	<div class="row"> 
    	<?php if (!array_key_exists(5, $user->roles)) {?>
		<?php // print $breadcrumb; ?>
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
	  	if($content_type == 'contact_us' || $content_type== 'services' || $content_type == 'about_us' || $content_type=='b_easy' || $content_type == 'citizen_corner' || $content_type == 'rti' || $content_type == 'boards_spio_sapio' || $content_type == 'spios_and_sapios' || $content_type == 'boards' || $content_type == 'forms_and_procedures' || $uri == 'may-we-help-you' || $content_type == 'ease_of_doing_business_inner' || 
		$url == 'LEFTPANNEL'){
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
									
									}
									else if($content_type == 'ease_of_doing_business_inner'){
										
									//print_r (menu_navigation_links('menu-ease-of-doing-business')); exit;
									
									$menu = menu_navigation_links('menu-ease-of-doing-business');
											print theme('links', array(
											'links' => $menu,
											'attributes' => array(
											'id' => 'main-menu',
											),
										));
									
									}
									else if($content_type == 'about_us'){
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
  
<!--  <div class="section5 text-center"> 
      <div class="section5inner">  
        <h2>If you have any questions, please feel free to drop us a line</h2>
        <a href="may-we-help-you" class="btn-style-three">click Here</a>
      </div>
    </div> -->
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
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/textresize.js"></script> 

<?php /*?><script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/bootstrap.min.js"></script> 
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

<script>
function backchng(){
	var bgcolor = String(jQuery("body").css("background-color"));
		if(bgcolor.length==18){
	  		jQuery("body").css("background-color","#000000");
			$("body").css("background-color","#000000");
			$("h1").css("color","#fffa2f");
			$("h2").css("color","#fffa2f");
			$("h3").css("color","#fffa2f");
			$("h4").css("color","#fffa2f");
			$("h5").css("color","#fffa2f");
			$("h6").css("color","#fffa2f");
			$("p").css("color", "#fffa2f");
			$("a.login_link").css("color", "#fffa2f");
			$("table").css("color", "#fffa2f");
			$("label.radios").css("color", "#fffa2f");
			$("input").css("color", "#fffa2f");
			$("tr.even").css("background-color","#000000");
			$("tr.odd").css("background-color","#000000");
			$("label").css("color", "#fffa2f");
			$("a").css("color", "#fffa2f");
			$(".footer_box p").css("color", "#fffa2f");
			$(".dropdown-menu").css("background-color","#000000");
			$(".sidebar-left .practice-listing li a").css("background-color","#000000");
		}else{
			jQuery("body").css("background-color","#ffffff");
			jQuery("h1").css("color","#696969");
			jQuery("h2").css("color","#696969");
			jQuery("h3").css("color","#008bbb");
			jQuery("h4").css("color","#696969");
			jQuery("h5").css("color","#696969");
			jQuery("h6").css("color","#696969");
			jQuery("p").css("color", "#696969");
			jQuery("a.login_link").css("color", "#696969");
			jQuery("table").css("color", "#696969");
			jQuery("label.radios").css("color", "#696969");
			jQuery("input").css("color", "#696969");
			jQuery("tr.even").css("background-color","#696969");
			jQuery("tr.odd").css("background-color","#696969");
			jQuery("label").css("color", "#696969");
			jQuery("a").css("color", "#696969");
			jQuery(".footer_box p").css("color", "#696969");
			jQuery(".dropdown-menu").css("background-color","#ffffff");
			jQuery(".sidebar-left .practice-listing li a").css("background-color","#ddd");
		}
}
</script>
<!-- sticky header starts-->

<script type="text/javascript">
                // When the document is ready
                jQuery(document).ready(function(){
                    jQuery('#casenoyear').datepicker({
						orientation: 'bottom auto',
                        minViewMode: 'years',
                        autoclose: true,
                        format: 'yyyy'
                    }); 
					
					jQuery('#awarddate').datepicker({
                        //minViewMode: 'years',
						orientation: 'bottom auto',
                        autoclose: true,
                        format: 'dd-mm-yyyy'
                    }); 
					jQuery('#dateofbirth').datepicker({
                        //minViewMode: 'years',
						orientation: 'bottom auto',
                        autoclose: true,
                        format: 'dd-mm-yyyy',
						endDate: '+0d'
                    }); 
					
				 jQuery('#awarddatefrom').datepicker({
                        //minViewMode: 'years',
						orientation: 'bottom auto',
                        autoclose: true,
                        format: 'dd-mm-yyyy',
						endDate: '+0d'
                    });
			    jQuery('#awarddateto').datepicker({
                        //minViewMode: 'years',
						orientation: 'bottom auto',
                        autoclose: true,
                        format: 'dd-mm-yyyy',
						endDate: '+0d'
                    });	
                });
            </script>

<script>
////********************** Disable Mouse Right Click, Cut, Copy & Paste ******************************///////////

/*jQuery(document).ready(function () {
    jQuery('body').bind('cut copy paste', function(e) {
        e.preventDefault();
    });
    jQuery("body").on("contextmenu",function(e){
        return false;
    });
});*/
</script>