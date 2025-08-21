<meta name="viewport" content="width=device-width, initial-scale=1">
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
        

<?php print render($page['content']); ?>


<footer>

 <?php if (!array_key_exists(5, $user->roles)) {?> 
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
<script>
function backchng(){
	var bgcolor = String(jQuery("body").css("background-color"));
		if(bgcolor.length==18){
	  		jQuery("body").css("background-color","#000000");
		}else{
			jQuery("body").css("background-color","#ffffff");
		}
}
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