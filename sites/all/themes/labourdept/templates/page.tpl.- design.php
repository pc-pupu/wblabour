<?php global $base_root,$base_path;
$url = '';
$urlarr = $_SERVER['HTTP_HOST'] . request_uri();
$urlarr = explode("/",$urlarr);
if (in_array("cmsentry", $urlarr)){
	$url = 'LEFTPANNEL';
}

if (in_array("custom_donate", $urlarr)){
	$custom_forms = 'customforms';
}
echo $custom_forms;
?>
<!DOCTYPE html>
<html lang="en"><head>
<meta charset="utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<meta name="viewport" content="width=device-width, initial-scale=1">
<!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
<title>::Department of Labour::</title>

<!-- Bootstrap -->
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/style.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/inner-page.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/responsive.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/bootstrap.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/font-awesome.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/style2.css" rel="stylesheet">
<!--<link href='https://fonts.googleapis.com/css?family=Lato:400,300,100,700,900' rel='stylesheet' type='text/css'>-->
<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.min.js"></script>     
<!--for bootstrap datepicker-->
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/bootstrap-datepicker.css" rel="stylesheet">
<link href="<?php print $base_path ?>sites/all/modules/dashboard/build/css/custom.css" rel="stylesheet">
<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/bootstrap-datepicker.js"></script>  
<!--end bootstrap datepicker-->

<!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
<!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
<!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
</head>
<body>
<script language="javascript">

$(window).scroll(function() {
    if ($(this).scrollTop() > 1){  
        $('.header').addClass("sticky");
    }
    else{
        $('.header').removeClass("sticky");
    }
});


</script>


<header>
  <div class="whitebg1 navbar-static-top header">
    <div class="container">
      <div class="row clearfix">
        <div class="col-sm-6">
        	<div class="social_media">
            	<i class="fa fa-twitter-square" aria-hidden="true"></i>
                <i class="fa fa-facebook-square" aria-hidden="true"></i>
            </div>
        </div>
        <div class="col-sm-6">
        	<div class="register">
            	<!--<i class="fa fa-sign-in" aria-hidden="true"></i> <a href="#" class="login_link">Login</a> &nbsp;&nbsp;&nbsp;-->
                 <?php if(user_is_logged_in()){?>
                <i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>user/logout" class="login_link">Logout</a>&nbsp;&nbsp;&nbsp;
                    <?php }else{?>
						<i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>user" class="login_link">Login</a>&nbsp;&nbsp;&nbsp;
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
          <?php print render($page['top_links']); ?>
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
        
        
        
  <?php if($custom_forms = 'customforms'){?>
  
  		<div class="container body">
      <div class="main_container">
     <div class="x_panel">
              <div class="x_title">
                <h2>Form Design </h2>
                
                <div class="clearfix"></div>
              </div>
              <div class="x_content">
                <br />

                <h4>Horizontal labels</h4>
                <p class="font-gray-dark">
                  Using the grid system you can control the position of the labels. The form example below has the <b>col-md-10</b> which sets the width to 10/12 and <b>center-margin</b> which centers it.
                </p>
                


                <h4>Vertical labels</h4>
                <p class="font-gray-dark">
                  For making labels vertical you have two options, either use the apropiate grid <b>.col-</b> class or wrap the form in the <b>form-vertical</b> class.
                </p>
                <div class="col-md-8 center-margin">
                  <form class="form-horizontal form-label-left">
                    <div class="form-group">
                      <label>Email address</label>
                      <input type="email" class="form-control" placeholder="Enter email">
                    </div>
                    <div class="form-group">
                      <label>Password</label>
                      <input type="password" class="form-control" placeholder="Password">
                    </div>

                  </form>
                </div>

                
              </div>
            </div>
            </div>
            </div>
		<?php //print render($page['content']); ?>	
  <?php }else{?>

  <div class="whitebg2"> 
  <div class="about_body">
	<!-- container starts here -->
    
 <div class="container">
 	<div class="row"> 
		<?php print $breadcrumb; ?>
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
	  	if($content_type == 'contact_us' || $content_type== 'services' || $content_type == 'about_us' || $content_type == 'citizen_corner' || $content_type == 'rti' || $content_type == 'boards_spio_sapio' || $content_type == 'spios_and_sapios' || $content_type == 'boards' || $content_type == 'forms_and_procedures' || $uri == 'may-we-help-you' || $url == 'LEFTPANNEL'){
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
  
  
  
  <div class="section5 text-center"> 
      <div class="section5inner">  
        <h2>If you have any questions, please feel free to drop us a line</h2>
        <a href="may-we-help-you" class="btn-style-three">click Here</a>
      </div>
    </div> 
  
  
  
</div>
<!--end body here-->

</div>

<?php }?>

<footer>


<div class="footer-top-wrapper">
    <div class="container">
        <?php print render($page['labour_footer']);?>
    </div>
</div>


<div class="footer-bottom-wrapper">
    <div class="container">

     
    <div class="footer_link">
      <div class="footer_box">
         <div class="row">
           <div class="col-md-12">
             <?php print render($page['labour_footer1']);?>
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
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/main.js"></script>

<script>
function backchng(){
	var bgcolor = String($("body").css("background-color"));
		if(bgcolor.length==18){
	  		$("body").css("background-color","#000000");
		}else{
			$("body").css("background-color","#ffffff");
		}
}
</script>
<!-- sticky header starts-->

<script type="text/javascript">
                // When the document is ready
                $(document).ready(function () {
                    $('#casenoyear').datepicker({
						orientation: 'bottom auto',
                        minViewMode: 'years',
                        autoclose: true,
                        format: 'yyyy'
                    }); 
					
					$('#awarddate').datepicker({
                        //minViewMode: 'years',
						orientation: 'bottom auto',
                        autoclose: true,
                        format: 'dd-mm-yyyy'
                    }); 
					$('#dateofbirth').datepicker({
                        //minViewMode: 'years',
						orientation: 'bottom auto',
                        autoclose: true,
                        format: 'dd-mm-yyyy'
                    }); 
					
					 
                
                });
            </script>

</body>
</html>