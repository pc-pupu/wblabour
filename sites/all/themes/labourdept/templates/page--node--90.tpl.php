<?php global $base_root,$base_path;?>
<!DOCTYPE html>
<html lang="en">
<head>
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

<!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
<!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
<!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
</script><script type="text/javascript" src="//translate.google.com/translate_a/element.js?cb=googleTranslateElementInit"></script>
<script type="text/javascript">
function googleTranslateElementInit() {
  new google.translate.TranslateElement({pageLanguage: 'en',includedLanguages: 'en,bn,hi', layout: google.translate.TranslateElement.InlineLayout.SIMPLE}, 'google_translate_element');
}
</script>    
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
            <div class="google_translate_box"><div id="google_translate_element"></div></div>
        </div>
        <div class="col-sm-6">
        	<div class="register">
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
      </div>
  
</header>
<!--start body here-->
        
        
        
  

  <div class="whitebg2"> 
  <div class="about_body">
	<!-- container starts here -->
    
 <div class="container">
 	<div class="row"> 
    	<?php print $breadcrumb; ?>
        <?php if($messages){ print $messages; } ?>
        <div class="about_body_main col-md-12">
            <div class="about_one">
            		<h1><span><?php print $title[0];?></span><?php print substr($title, 1); ?></h1>
                    <br>
                    <video controls>
                      <source src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/video/Video__Best_Practices__2.mp4" type="video/mp4">
                      Your browser does not support the video tag.
                    </video>
             </div>
         </div>       
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

</body>
</html>
