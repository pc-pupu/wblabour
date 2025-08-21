<?php global $base_root,$base_path;


// $results = db_query('select * from site_counter order by site_counter_id desc');
   
//    $records = $results->fetchAssoc();

//    $lastValue = $records['last_value'];

//    $newValue = $lastValue+1;

//    $site_counter_id = 1;

//    $timeStamp = time();


//    $updateDetails = array(
    
//     'last_value' => $newValue,

//     'update_time' => $timeStamp
    
   
    
//     );

//    db_update('site_counter')
//     ->fields($updateDetails)
//     ->condition('site_counter_id', $site_counter_id, '=')
//     ->execute();


 ?>
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta http-equiv="Content-Security-Policy" content="default-src *; style-src 'self' 'unsafe-inline'; script-src 'self' 'unsafe-inline' 'unsafe-eval' http://www.google.com">
<!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
<title>::Department of Labour::</title>
<!-- Bootstrap -->
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/style.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/inner-page.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/responsive.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/bootstrap.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/bootstrap.min.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/font-awesome.css" rel="stylesheet">
<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/style2.css" rel="stylesheet">
<link href="https://fonts.googleapis.com/css?family=Lato:400,300,100,700,900" rel="stylesheet" type="text/css">
<link href="https://fonts.googleapis.com/css?family=Poppins:400,500,600,700&display=swap" rel="stylesheet">

<!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
<!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
<!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
<![endif]-->

</script>


<script type="text/javascript" src="//translate.google.com/translate_a/element.js?cb=googleTranslateElementInit"></script>

<script type="text/javascript">
function googleTranslateElementInit() {
  new google.translate.TranslateElement({pageLanguage: 'en',includedLanguages: 'en,bn,hi', layout: google.translate.TranslateElement.InlineLayout.SIMPLE}, 'google_translate_element');
}
</script>

<!-- <style type="text/css">
  
  .blinking {
    animation: blinkingText 1.5s infinite;
}
.blinking:hover {
    animation: none;
}

@keyframes blinkingText {
    0% { opacity: 1; }
    50% { opacity: 0; }
    100% { opacity: 1; }
}
</style> -->
</head>
<body>
	
<header>
  <div class="whitebg1 navbar-static-top header">
    <div class="container">
      <div class="row clearfix">
        <div class="col-sm-6 col-md-6">
        	<div class="social_media">
            	<i class="fa fa-twitter-square" aria-hidden="true"></i>
                <i class="fa fa-facebook-square" aria-hidden="true"></i>
                 <a href="<?php print $base_root.$base_path?>screen-reader-access" class="login_link" style="margin-top: 9px;float: right;margin-left: 10px;"><i class="fa fa-sign-in" aria-hidden="true"></i> Screen Reader Access</a>
            </div>
            <div class="google_translate_box"><div id="google_translate_element"></div></div>
        </div>
        
        <div class="col-sm-6 col-md-4 pull-right">
        	<div class="register">
            <div class="login-panel">  
            	<div class="total-visitor">
					<?php //print render($page['header']);?>
                 </div>
                <?php if(user_is_logged_in()){?>
                <i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>user/logout" class="login_link">Logout</a>&nbsp;&nbsp;&nbsp;
                    <?php }else{?>
                    
						<!--<i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>enlogin" class="login_link">Login</a>&nbsp;&nbsp;&nbsp;-->
                        <i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>assetlogin" class="login_link">Employee Login</a>&nbsp;&nbsp;&nbsp;
                        <i class="fa fa-sign-in" aria-hidden="true"></i> <a href="<?php print $base_root.$base_path?>user" class="login_link">Admin Login</a>&nbsp;&nbsp;&nbsp;
                      <?php }?>  
                </div>
                    <div class="text-icon">
                		<a href="#" id="large"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon3.png"> </a>
                		<a href="#" id="small"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon4.png" ></a>
                		<a href="#" id="medium" class="selected"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon5.png"></a>
                 		<a href="javascript:void(0)"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/icon6.png" onClick="backchng();"></a>
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
                    <img src="<?php print $logo; ?>" alt="<?php print t('Department of Labour Logo'); ?>" class="logo-img" />
                  </a>
                <?php endif; ?>
            </div>
          </div>
          <div class="col-sm-6">
          <!--<div class="Awards-btm">
          <a href="<?php print $base_root.$base_path?>awards-and-achievements" title="Awards & Achievements">
          <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/Awards_btm.gif" alt="Awards & Achievements"></a>
          </div>-->
          <div class="cm-pic">
          	<!-- <img src="<?php// print $base_root.$base_path?>sites/all/themes/labourdept/images/cm.png" alt="CM"> -->
           </div>
            <div class="serach_padding">
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
      </div>
    </nav>
  </div>

  <div class="custom-feedback">

  <a href="https://wblabour.gov.in/may-we-help-you/" class="feedback-btn" style="color: white!important; text-decoration: none!important;">Feedback</a>
    

  </div>
  
  
  <div class="news-ticker-box">
    <div class="container">
		<div class="row">
			<div class="col-xs-12 text-center">
			<div class="site-meta">
				<!--<span class="blinking_bar" style="display: inline;">For any technical enquiry with respect to COVID19, you may kindly email on <strong><a href="mailto:technicalquery.covid19@gov.in">technicalquery.covid19@gov.in</a></strong> <a href="<?php print $base_root.$base_path?>sites/default/files/UpdatedTelesurveythrough1921.pdf" target="_BLANK" class="pl-80">Tele survey from <i class="fa fa-phone" aria-hidden="true"></i> 1921</a></span>-->
               
                <span class="blinking_bar" style="display: inline;">বিনামূল্যে সরকারি পরিষেবা পেতে চলুন <a href="https://bsk.wb.gov.in" target="_blank"><strong>বাংলা সহায়তা কেন্দ্রে</strong></a> অথবা লগ ইন করুন <a href="https://bsk.wb.gov.in" target="_blank"><strong>https://bsk.wb.gov.in</strong></a> </span>
                <marquee style="color:red; background-color: yellow; font-size: x-large;"><b>Portal will be under maintenance w. e. f. 14th August 2025, 6:00 PM</b></marquee>
			</div>
			</div>
		</div>
	</div>
  </div>
  
  
  


  
  <div id="carousel-example-generic" class="carousel slide" data-ride="carousel"> 
    <!-- Indicators -->
    <ol class="carousel-indicators">
      <li data-target="#carousel-example-generic" data-slide-to="0" class="active"></li>
      <li data-target="#carousel-example-generic" data-slide-to="1"></li>
      <li data-target="#carousel-example-generic" data-slide-to="2"></li>
      <li data-target="#carousel-example-generic" data-slide-to="3"></li>
      <!-- <li data-target="#carousel-example-generic" data-slide-to="4"></li> -->
    </ol>
    
 
    
    <!-- Wrapper for slides -->
    <div class="carousel-inner" role="listbox">
      <div class="item active"> <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/banner.jpg" width="100%" alt=""></div>
      <div class="item"> <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/banner1.jpg" width="100%" alt="Banner Of Guiding Unemployed Youth Towards Gainful Employment"></div>
      <div class="item"> <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/banner2.jpg" width="100%" alt="Banner Of Ensuring Well-being of Workers in Tea and Jute Sector"></div>
       <div class="item"> <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/banner3.jpg" width="100%" alt="Banner Of Promoting Safe and Secure Workforce Through Social Security Schemes"></div>

       <!-- <div class="item"> <img src="<?php //print $base_root.$base_path?>sites/all/themes/labourdept/images/yoga.jpg" width="100%" alt="Banner Of International Yoga Day"></div> -->
    </div>
    
    <!-- Controls --> 
    <a class="left carousel-control" href="#carousel-example-generic" role="button" data-slide="prev"> <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span> <span class="sr-only">Previous</span> </a> <a class="right carousel-control" href="#carousel-example-generic" role="button" data-slide="next"> <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span> <span class="sr-only">Next</span> </a> </div>

    <div class="news-ticker-box">
    <div class="container">
    <div class="row">
      <div class="col-xs-12 text-center">
      <div class="site-meta">
               
                <span class="blinking_bar blinking" style="display: inline; font-size: 22px!important;">Migrant Workers : <a href="https://karmasathips.wblabour.gov.in/" target="_blank"><strong>Click Here to Register in Karmasathi (Parijayee Shramik)</strong></a> </span>
      </div>
      </div>
    </div>
  </div>
  </div>
  
</header>

<div class="news-ticker-box"> 
 <div class="container">
              <div class="col-md-12">
                <div class="news-ticker">

                <div class="region region-news-section">
                  <div id="block-slidernews-slidernews-block" class="block block-slidernews">
                    <div class="content asd">
                    <?php print render($page['news_section']);?>
                    </div>
                  </div>
                </div>
                
                 </div>
              </div>
              
           
      </div>
</div>
	
<div class="whitebg2"> 
    <div class="container">
      
      <div class="three_sections">
        <div class="row clearfix">
        
        
           <div class="col-md-12">
         	 <div class="relief_fund">
   <div class="row">
    <div class="col-md-12 relief_fund_title">
     <h1>West Bengal State Emergency Relief Fund </h1>
    </div>
    <div class="col-md-12 relief_fund_content">
     <p><strong style="color:#343685;">For any technical enquiry with respect to COVID19, you may kindly email on <a href="mailto:technicalquery.covid19@gov.in">technicalquery.covid19@gov.in</a> <a href="<?php print $base_root.$base_path?>sites/default/files/UpdatedTelesurveythrough1921.pdf" target="_BLANK" class="pl-80">Tele survey from <i class="fa fa-phone" aria-hidden="true"></i> 1921</a></strong></p>
    <p>The West Bengal State Government Appeals ALL to contribute in West Bengal State Emergency Relief Fund and assist the State in prevention and control of situation arising out of unforeseen emergencies like <strong>COVID-19 (CORONA)</strong>.</p>
    <p><strong style="color:#343685;">The contributions can be both made through Cheque/ DD / Debit Card / Credit Card / UPI and kind.</strong></p>
     <p>Bank details for <strong style="color:#343685;"> Cheque/ DD / Debit Card / Credit Card / UPI Contribution</strong> are as follows:</p>
    <div class="row">
     <div class="col-md-6">
        <table width="100%" border="1">
  <tr>
    <td><strong>A/c Name   :</strong></td>
    <td>West Bengal State Emergency Relief Fund</td>
  </tr>
  <tr>
    <td><strong>A/c No     :</strong></td>
    <td>628005501339</td>
  </tr>
  <tr>
    <td><strong>Bank       :</strong></td>
    <td>ICICI Bank Ltd. , <strong>Branch     :</strong> Howrah</td>
  </tr>
   <tr>
    <td><strong>IFS Code   :</strong></td>
    <td>ICIC0006280</td>
  </tr>
  
  <tr>
    <td><strong>Swift Code   :</strong></td>
    <td>ICICINBBCTS</td>
  </tr>
  
   <tr>
    <td><strong>MICR Code  :</strong></td>
    <td>700229010</td>
  </tr>
</table>
</br>
     <h3>For contribution in kind contact : <a href="mailto:wbsacs@gmail.com"><strong>wbsacs@gmail.com</strong></a> </h3>
     <p>For further details: <a href="<?php print $base_root.$base_path?>sites/default/files/relieffund/West_Bengal_State_Emergency_Relief_Fund.pdf" target="_blank"><strong><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/pdf-icon.png" width="40" height="" alt="pdf-icon"> Click Here</strong></a> </p>
     </div>
     
      <div class="col-md-3 text-center">
       <strong style="color:#F00">Please CLICK the ICON below to make ONLINE PAYMENT</strong></br>
      <a href="https://eazypay.icicibank.com/eazypayLink?P1=m9BPa3/GAmP3nzLWEHC4zA==" target="_blank" ><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/covid19.png" width="" height="" alt="relief_fund_btm" class="relief_fund_btm"></a>
   </div>
   
    <div class="col-md-3 text-center">     
      <strong style="color:#F00">Have you already contributed?</strong></br>
      <a href="https://excise.wb.gov.in/wbserf/Page/WBSERF_Generate_Receipt.aspx" target="_blank"><strong>Download Acknowledgment Receipt</strong> </a></br>     
      <a href="https://excise.wb.gov.in/wbserf/Page/WBSERF_Generate_Receipt.aspx" target="_blank" ><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/Receipt.png" width="" height="" alt="relief_fund_btm" class="relief_fund_btm"></a>  
    </div>
   
    </div>
     </div>
    </div>
   </div>
    		</div>
        
        	  <div class="col-md-12 notes-home">
           <div class="notes-home-pad">
        	<div class="panel panel-default">
          	<div class="panel-heading"><span class="glyphicon glyphicon-list-alt"></span> <b>Training on Compassionate Appointment <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/newicon.gif" alt="New"></b></div>
         	 <div class="panel-body">
        
                <ul class="news11" style="">
                					<li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/142-Emp.pdf" target="_blank">
									  Notification-142-Emp, dated 1st November, 2007
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                   <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/50-EMP.pdf" target="_blank">
									 Notification-50-Emp/1M-25/98, Dated Kolkata, the 1st March, 2011
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/251-EMP.pdf" target="_blank">
									  Notificaion-251 EMP, dated 3rd December, 2013
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/96-Emp.pdf" target="_blank">
									  Notification-96 EMP, dated 28th April, 2015
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/No165-Emp.pdf" target="_blank">
									  Notification-165 EMP, dated 4th June, 2015
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                  <li style="" class="news-item">
								    <a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/26-Emp.pdf" target="_blank">
									Notification-26 EMP, dated 1st March, 2016
									<img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                 <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/WB-up-to-date-amendments.pdf" target="_blank">
									  West Bengal Scheme for Compassionate Appointment, 2013 with up-to-date amendments, made by various Notification from time to time, till 31/03/2022
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
								  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/SOP.pdf" target="_blank">
									  Standard Operating Procedure (SOP) , on Compassionate Appointment
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
								  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/FAQ.pdf" target="_blank">
									  Frequently Asked Question (FAQ) , on Compassionate Appointment
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
								  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/CommonChecklist.pdf" target="_blank">
									  Common Checklist to be used for processing an application for employment on compassionate ground vide Memorandum No Labr/63/EMP(EC), dated 06.04.22.
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                  <li class="news-item"><a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/Training-on-Compassionate-Appointment.pptx_08_04_22.pdf" target="_blank">
                                  Power Point Presentation on Training on Compassionate Appointment
                                   <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a></li>
 								  <li class="news-item"><a href="#">Training Video (To be uploaded)</a></li>
                      </ul>  
                                 
              
          </div>
          	</div>
            </div>
            </div>
          <div class="col-md-4">
            <div class="section_headding1">
              <h1>Our Directorates</h1>
              <div class="many_section clearfix">
                <ul>
                  <li class="boxbgcolor1">
                    <a href="http://www.wblc.gov.in/" target="_blank" data-toggle="tooltip"  title="">
                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/owl-icon1.png" alt="Labour Commissionerate" class=" boxbgcolor1sub animated bounce"></a>
                    <p>Labour Commissionerate</p>
                  </li>
                  <li class="boxbgcolor2">
                    <a href="#" data-toggle="tooltip" title="">
                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/8.png" alt="Employment"  class=" boxbgcolor1sub animated bounce"></a>
                  <p>Employment</p>
                  </li>
                   <li class="boxbgcolor3">
                   <a href="http://factories.wb.gov.in" data-toggle="tooltip"   target="_blank" title="">
                   <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/4.png" alt="Factories"  class=" boxbgcolor1sub animated bounce"></a>
                    <p>Factories</p>
                   </li>
                  <li class="boxbgcolor4">
                    <a href="http://wbboilers.gov.in/" data-toggle="tooltip"   target="_blank" title="">
                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/5.png" alt="Boilers"  class=" boxbgcolor1sub animated bounce"></a>
                  <p>Boilers</p>
                  </li>
                  
                  <li class="boxbgcolor5">
                     <a href="/labour-welfare-board" data-toggle="tooltip"   target="_blank" title="">
                     <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/10.png" alt="Boards"  class=" boxbgcolor1sub animated bounce"></a>
                   <p>Boards</p>
                   </li>
                  <li class="boxbgcolor6">
                  <a href="/industrial-tribunals-and-labour-courts-directorate" data-toggle="tooltip"   target="_blank" title="">
                  <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/7.png" alt="Industrial Tribunals & Labour Courts"  class=" boxbgcolor1sub animated bounce"></a>
                   <p>Industrial Tribunals &amp; Labour Courts</p>
                   </li>
                  
                   <li class="boxbgcolor7">                
                     <a href="http://esiwb.gov.in/" data-toggle="tooltip"   target="_blank" title="">
                     <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/9.png" alt="ESI (MB) SCHEME"  class=" boxbgcolor1sub animated bounce"></a>
                   <p>ESI (MB) SCHEME </p>
                   </li>
                  
                  <li class="boxbgcolor8">
                   <a href="/employees-compensation-directorate" data-toggle="tooltip"   target="_blank" title="">
                   <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/11.png" alt="Employees' Compensation"  class=" boxbgcolor1sub animated bounce"></a>
                  <p>Employees' Compensation</p>
                  </li>
                  
                  <li class="boxbgcolor9">
                   <a href="#" data-toggle="tooltip" title="">
                   <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/12.png" alt="State Labour Institute"  class=" boxbgcolor1sub animated bounce"></a>
                   <p>State Labour Institute</p>
                  </li>
                  
                  
                </ul>
              </div>
            </div>
          </div>
          <div class="col-md-4">
            <?php //print render($page['ease_of_doing_business']); ?>
             <?php //print render($page['from_the_desk_of']); ?>
          </div>
          
		 
	
          
          <!--<div class="panel-footer"> <ul class="pagination pull-right" style="margin: 0px;">
            <li><a href="#" class="prev"><span class="glyphicon glyphicon-chevron-down"></span></a>
            </li>
            <li><a href="#" class="next">
                <span class="glyphicon glyphicon-chevron-up"></span></a>
            </li></ul>
            <div class="clearfix">

            </div>
        </div>--!>
        </div>
      </div>
</div>


			<!--<div class="col-md-4">
        	 <?php //print render($page['from_the_desk_of_new']); ?>
          </div>--!>
        </div>
      </div>
      
    </div>
  </div>
	
<div class="count-bar">
			<div class="container">
				
			<div class="row">
				
			
				
			<div class="col-md-8">
				<h3>Online e-Services</h3>
				<div class="row">
			<div class="col-lg-3">
				<div class="count-box">	
				  <span class="counter">7101</span>
				  <p class="count-text ">Contractor License<br/>Under CLRA</p>
				</div>	
			</div>

			<div class="col-lg-3">
			  <div class="count-box">			
				  <span class="counter">2004</span>
				  <p class="count-text "> Establishment Regn <br/> Under BOCWA</p>
			  </div>	  
			</div>

			<div class="col-lg-3">
				<div class="count-box">			
				 <span class="counter">12245</span>
				 <p class="count-text ">Boilers <br/>Registered</p> 
				</div>	
			</div>
			
			<div class="col-lg-3">
				<div class="count-box">			
				 <span class="counter">17803</span>
				 <p class="count-text ">Factories <br/>Registered</p>
				</div>	
			</div>
					
				</div>
				
			</div>
				
			<div class="col-md-4">
				
 			 <a href="<?php print $base_root.$base_path?>daily-session">
				<div class="graph-widget">
    
				<div class="section section-graph">
				  <div class="graph-info">
					<i class="fa fa-flag"></i>
					<span class="graph-info-big">Infographic</span>
				  </div>
				  <div id="graph"></div>
				</div>


			  </div>
			</a>
			</div>		
				
				
			</div>
	</div>	
 </div>
	

<!--<div class="testimonial">
<div class="container">
	<div class="row">
		<div class="col-sm-12">
			<h2>See What <b>Entrepreneur</b> Say About Us</h2>
			<div id="myCarousel" class="carousel slide" data-ride="carousel">
				<ol class="carousel-indicators">
					<li data-target="#myCarousel" data-slide-to="0" class="active"></li>
					<li data-target="#myCarousel" data-slide-to="1"></li>
					<li data-target="#myCarousel" data-slide-to="2"></li>
				</ol>   
				<div class="carousel-inner">
					<div class="item carousel-item active">
						<div class="row">
							<div class="col-sm-6">
								<div class="testimonial-wrapper">
									<div class="testimonial"><span class="laquo">&nbsp;</span>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam eu sem tempor, varius quam at, luctus dui. Mauris magna metus, dapibus nec turpis vel, semper malesuada ante, commodo iacul viverra. <span class="raquo">&nbsp;</span></div>
									<div class="media">
										<div class="media-body">
											<div class="overview">
												<div class="name"><b>User Name</b></div>
												<div class="star-rating">
													<ul class="list-inline">
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star-half-o"></i></li>
													</ul>
												</div>
											</div>										
										</div>
									</div>
								</div>								
							</div>
							<div class="col-sm-6">
								<div class="testimonial-wrapper">
									<div class="testimonial"><span class="laquo">&nbsp;</span> Vestibulum quis quam ut magna consequat faucibus. Pellentesque eget mi suscipit tincidunt. Utmtc tempus dictum. Pellentesque virra. Quis quam ut magna consequat faucibus, metus id mi gravida. <span class="raquo">&nbsp;</span></div>
									<div class="media">
										<div class="media-body">
											<div class="overview">
												<div class="name"><b>User Name</b></div>
												<div class="star-rating">
													<ul class="list-inline">
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star-o"></i></li>
													</ul>
												</div>
											</div>
										</div>
									</div>
								</div>								
							</div>
						</div>			
					</div>
					<div class="item carousel-item">
						<div class="row">
							<div class="col-sm-6">
								<div class="testimonial-wrapper">
									<div class="testimonial"><span class="laquo">&nbsp;</span> Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam eu sem tempor, varius quam at, luctus dui. Mauris magna metus, dapibus nec turpis vel, semper malesuada ante, commodo iacul viverra. <span class="raquo">&nbsp;</span></div>
									<div class="media">
										<div class="media-body">
											<div class="overview">
												<div class="name"><b>User Name</b></div>	
												<div class="star-rating">
													<ul class="list-inline">
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star-o"></i></li>
													</ul>
												</div>
											</div>
										</div>
									</div>
								</div>								
							</div>
							<div class="col-sm-6">
								<div class="testimonial-wrapper">
									<div class="testimonial"><span class="laquo">&nbsp;</span> Vestibulum quis quam ut magna consequat faucibus. Pellentesque eget mi suscipit tincidunt. Utmtc tempus dictum. Pellentesque virra. Quis quam ut magna consequat faucibus, metus id mi gravida. <span class="raquo">&nbsp;</span></div>
									<div class="media">
										<div class="media-body">
											<div class="overview">
												<div class="name"><b>User Name</b></div>
												<div class="star-rating">
													<ul class="list-inline">
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star-o"></i></li>
													</ul>
												</div>
											</div>										
										</div>
									</div>
								</div>								
							</div>
						</div>			
					</div>
					<div class="item carousel-item">
						<div class="row">
							<div class="col-sm-6">
								<div class="testimonial-wrapper">
									<div class="testimonial"><span class="laquo">&nbsp;</span> Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam eu sem tempor, varius quam at, luctus dui. Mauris magna metus, dapibus nec turpis vel, semper malesuada ante, commodo iacul viverra. <span class="raquo">&nbsp;</span></div>
									<div class="media">
										<div class="media-body">
											<div class="overview">
												<div class="name"><b>User Name</b></div>
												<div class="star-rating">
													<ul class="list-inline">
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star-o"></i></li>
													</ul>
												</div>
											</div>										
										</div>
									</div>
								</div>								
							</div>
							<div class="col-sm-6">
								<div class="testimonial-wrapper">
									<div class="testimonial"><span class="laquo">&nbsp;</span> Vestibulum quis quam ut magna consequat faucibus. Pellentesque eget mi suscipit tincidunt. Utmtc tempus dictum. Pellentesque virra. Quis quam ut magna consequat faucibus, metus id mi gravida. <span class="raquo">&nbsp;</span></div>
									<div class="media">
										<div class="media-body">
											<div class="overview">
												<div class="name"><b>User Name</b></div>
												<div class="star-rating">
													<ul class="list-inline">
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star"></i></li>
														<li class="list-inline-item"><i class="fa fa-star-o"></i></li>
													</ul>
												</div>
											</div>										
										</div>
									</div>
								</div>								
							</div>
						</div>			
					</div>
				</div>
			</div>
		</div>
	</div>
</div>
</div>-->
		
<div class="grybg">
	<div class="container">
  <?php print render($page['body_area']);?>
    </div>
  </div>
  
<div class="whitebg2">
  	<div class="container">
    	<div class="row clearfix">
        	<div class="col-lg-2">
            	<div class="labour_glance">
                	<h3>Labour Department Statistics at a Glance</h3>
                </div>
            </div>
            <div class="col-md-2">
            	<div class="green">
                	
                    <h4 style="text-align:center;" class="wow bounceInLeft" style="visibility: visible; animation-name: bounceInLeft;"><span class="element1">Labour Commissionerate (LC)|Principal Employees Under CLRA|
Contractor License Under CLRA|Renewal of License Under CLRA|Establishment Regn Under BOCWA|Trade Union Registered|Inspection Note</span></h4>
                    <p class="wow bounceInRight" style="visibility: visible; padding: 36px 10px 0 0;
  text-align: right;
  position:absolute;
  right:17px;
  top:75px; animation-name: bounceInRight;"><span class="element1">
  <?php
  	$service_url 	= 	"https://wblc.gov.in/labourdept/eservices/viewAllReport";
	$ch 			= 	curl_init();
	$headers		=	array();
	$curl_post_data = 	array();
	$tmp 			=	array();
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
	//print_r($tmp); exit;
	if(!empty($tmp['content'])){
		//total_license_renewal_application
		echo "&nbsp;".$tmp['content']['total_lc_reg_license']."|".$tmp['content']['total_clra_application']."|".$tmp['content']['total_license_application']."|".$tmp['content']['total_license_renewal_application']."|".$tmp['content']['total_bocwa_application']."|".$tmp['content']['total_tu_registration']."|".$tmp['content']['total_inspection_reports'];
	}
  ?></span></p>
                   
                   
                     
                    
                </div>
            </div>
            <div class="col-md-2">
            	<div class="green2">
  
                        <h4 style="text-align:center;" class="wow bounceInLeft" style="animation-name: bounceInLeft;"><span class="element2">Shops & Establishment|Registration of <br> Shops & Establishment|
Transport Workers Beneficiary Regn</span></h4>
                    <p class="wow bounceInRight" style="visibility: visible; padding: 36px 10px 0 0;
  text-align: right;
  position:absolute;
  right:17px;
  top:75px; animation-name: bounceInRight;"><span class="element2">&nbsp;|215|1,267</span></p>
                    
                </div>
            </div>
            <div class="col-md-2">
            	<div class="green3">
                	<h4 style="text-align:center;" class="wow bounceInLeft" style="visibility: visible; animation-name: bounceInLeft;"><span class="element3">Directorate <br> of <br> Employment|Job seekers enrolled in Employment Bank|Yuvasree identified (Cumulative)|Yuvasree benefitted (Cumulative)|Domestic workers trained</span></h4>
                   <p class="wow bounceInRight" style="visibility: visible;padding: 36px 10px 0 0;
  text-align: right;
  position:absolute;
  right:17px;
  top:75px; animation-name: bounceInRight;"><span class="element3">&nbsp;|23,09,813|2,19,986|1,31,624|10,143</span></p>
                </div>
            </div>
            <div class="col-md-2">
            	<div class="green4">
                    <h4 style="text-align:center;" class="wow bounceInLeft" style="visibility: visible; animation-name: bounceInLeft;"><span class="element4">Directorate <br> of <br> Boilers|Boilers Registered|Renewal Boilers|Economiser Registered|Renewal Economiser</span></h4>
                   <p class="wow bounceInRight" style="visibility: visible;padding: 36px 10px 0 0;
  text-align: right;
  position:absolute;
  right:17px;
  top:75px; animation-name: bounceInRight;"><span class="element4">&nbsp;|12,245|8,205|206|60</span></p>
                    
                </div>
            </div>
            <div class="col-md-2">
            	<div class="green5">
                	<h4 style="text-align:center;" class="wow bounceInLeft" style="visibility: visible; animation-name: bounceInLeft;"><span class="element5">Directorate <br> of <br> Factories|Factories Registered|
Employment in Regd. Factories</span></h4>
                    <p class="wow bounceInRight" style="visibility: visible;padding: 36px 10px 0 0;
  text-align: right;
  position:absolute;
  right:17px;
  top:75px; animation-name: bounceInRight;"><span class="element5">&nbsp;|17,803|11,33,090</span></p>
                </div>
            </div>
        </div>
    </div>
  </div>
  
<div class="bottom_carousel">
  	<div class="container">
<div class="col-xs-12">
    <div class="carousel slide" id="myCarousel">
        <div class="carousel-inner">
            <div class="item active">
            
            <?php print render($page['body_advertisement']);?>
                   
              </div>  
        </div>
        
                              
    </div>
        
</div>      

</div>
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
           <div class="col-md-10 text-center">
            <?php print render($page['labour_footer1']);?>
            Last Updated On : <?php echo date('d-m-Y');?>
            <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/nic_logo.png" class="img-responsive ftr-logo-nic" align="middle" alt="NIC LOGO">
            <!--<a href="#" class="ftr-mob" onClick="myChat()">
            <img src="<?php //print $base_root.$base_path?>sites/all/themes/labourdept/images/live-chat.png" class="img-responsive" align="middle">
            </a>-->
            
            </div>

            <div class="col-md-2 text-right">

               <div class="site-count"><span class="counter counterVal">7738004</span><span class="site-counter-text">Site Counter</span></div>
              

            </div>
           </div>
         </div>
      </div>
    
    </div>
</div>

</footer>



<!--<div id="myModal" class="modal" tabindex="-1" role="dialog" >
  <div class="modal-dialog" role="document"  style="width:80%">
    <div class="modal-content" style="overflow: hidden;"> 
      <div class="modal-body">
          <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
       <div class="col-md-12 notes-home">
           <div class="notes-home-pad">
        	<div class="panel panel-default">
          	<div class="panel-heading"><span class="glyphicon glyphicon-list-alt"></span> <b>Training on Compassionate Appointment <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/newicon.gif" alt="New"></b></div>
         	 <div class="panel-body">
        
                <ul class="news11" style="">
                					<li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/142-Emp.pdf" target="_blank">
									  Notification-142-Emp, dated 1st November, 2007
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                   <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/50-EMP.pdf" target="_blank">
									 Notification-50-Emp/1M-25/98, Dated Kolkata, the 1st March, 2011
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/251-EMP.pdf" target="_blank">
									  Notificaion-251 EMP, dated 3rd December, 2013
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/96-Emp.pdf" target="_blank">
									  Notification-96 EMP, dated 28th April, 2015
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/No165-Emp.pdf" target="_blank">
									  Notification-165 EMP, dated 4th June, 2015
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                  <li style="" class="news-item">
								    <a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/26-Emp.pdf" target="_blank">
									Notification-26 EMP, dated 1st March, 2016
									<img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                 <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/WB-up-to-date-amendments.pdf" target="_blank">
									  West Bengal Scheme for Compassionate Appointment, 2013 with up-to-date amendments, made by various Notification from time to time, till 31/03/2022
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
								  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/SOP.pdf" target="_blank">
									  Standard Operating Procedure (SOP) , on Compassionate Appointment
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
								  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/FAQ.pdf" target="_blank">
									  Frequently Asked Question (FAQ) , on Compassionate Appointment
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
								  <li style="" class="news-item">
                                  	<a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/CommonChecklist.pdf" target="_blank">
									  Common Checklist to be used for processing an application for employment on compassionate ground vide Memorandum No Labr/63/EMP(EC), dated 06.04.22.
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a>
								  </li>
                                  <li class="news-item"><a href="<?php print $base_root.$base_path?>sites/default/files/upload/edu/Training-on-Compassionate-Appointment.pptx_08_04_22.pdf" target="_blank">
                                  			Power Point Presentation on Training on Compassionate Appointment
                                            <img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/img/important.gif" alt="important"></a></li>
 								  <li class="news-item"><a href="#">Training Video (To be uploaded)</a></li>
                      </ul>  
                                 
              
          </div>
          	</div>
            </div>
            </div>
      </div>
    </div>
  </div>
</div>-->



<?php /*?><div id="myModal" class="modal fade" role="dialog" data-backdrop="static">
          <div class="modal-dialog">
        
            <!-- Modal content-->
            <div class="modal-content">
              <div class="modal-header">
                <h4 class="modal-title">Rate your experience on your <strong></strong></h4>
                <button type="button" class="btn-close" aria-label="Close" data-bs-dismiss="modal"></button>
                <input type="hidden" id="user_servive_info_id" name="user_servive_info_id" value="">
              </div>
              <div class="modal-body">
                <p>
                <section>
                    <div class="lead evaluation">
                    	<div class="myerr_msg" style="display:none"></div>
                        <div id="colorstar" class="starrr ratable" ></div>
                        <span id="count">0</span> star - <span id="meaning"></span><br>
                            <div class='indicators' style="display:none">
                                <div id='textwr'>What went wrong?</div>
                                <input id="rate[]" name="rate[]" type="text" placeholder="" class="form-control input-md" style="display:none;">
                                <input id="rating[]" name="rating[]" type="text" placeholder="" class="form-control input-md rateval" style="display:none;">
                                
                                <span class="button-checkbox">
                                <button type="button" class="btn btn-outline-secondary criteria buttondashboardstar" data-color="secondary">Easy availability of relevant information</button>
                                 <input type="checkbox" class="hidden" id="1" value="1_I"  />
                                 <input type="hidden" id="feedbackans_1" class="myoptnchk" value="NOVAL">
                                </span>
                                
                                <span class="button-checkbox">
                                <button type="button" class="btn btn-outline-secondary criteria buttondashboardstar" data-color="secondary">Process of Online submission</button>
                                 <input type="checkbox" class="hidden" id="2" value="2_S"  />
                                 <input type="hidden" id="feedbackans_2" class="myoptnchk" value="NOVAL">
                                </span>
                               
                                <span class="button-checkbox">
                                <button type="button" class="btn btn-outline-secondary criteria buttondashboardstar" data-color="secondary">Process of Online payment</button>
                                 <input type="checkbox" class="hidden" id="3" value="3_P"  />
                                 <input type="hidden" id="feedbackans_3" class="myoptnchk" value="NOVAL">
                                </span>
                                
                                <span class="button-checkbox">
                                <button type="button" class="btn btn-outline-secondary criteria buttondashboardstar" data-color="secondary"> User-friendly interface</button>
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
        </div><?php */?>




<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.min.js"></script> 
<!--charts-->	
<script src='<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/highcharts.js'></script>
<script  src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/index.js"></script>	
	
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.auto-text-rotating.min.js"></script>
<!--- js for text resize-->
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/textresize.js"></script> 
<!-- Include all compiled plugins (below), or include individual files as needed --> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/bootstrap.min.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/news.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/news2.js"></script>
        
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/owl.carousel.min.js"></script>
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.scrollUp.js"></script>
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/script.js"></script>
<script type="text/javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/tickerme.min.js"></script>
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/wow.min.js"></script>
<!----slide_menu----->
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jasny-bootstrap.min.js"></script>
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/main.js"></script>
	
<!--counter-->
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.waypoints.min.js"></script>
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.countup.js"></script>
<script>
$('.counter').countUp();
</script>


<script type="text/javascript"> 
    jQuery(window).on('load',function(){ //alert("hi";
        jQuery('#myModal').modal('show');
    });
</script>
	
<!--testimonial--> 	
<script>
$(document).ready(function() {
  $('#quote-carousel').carousel({
    pause: true,
    interval: 4000,
  });
});	
</script>

<!-- sticky header starts-->
<script>

$(window).scroll(function() {
    if (jQuery(this).scrollTop() > 1){  
        jQuery('.header').addClass("sticky");
    }
    else{
        jQuery('.header').removeClass("sticky");
    }
});
</script>
<!-- sticky header ends-->



<!-- js for the tooltip starts-->
<script>
jQuery(document).ready(function(){
    jQuery('[data-toggle="tooltip"]').tooltip();  
	
	/*jQuery('.boxbgcolor1sub').each(function() {
        animationHover(this, 'bounce');
		animationClick(this, 'bounce');
		
    }); */
	
	

$('.element1').atrotating({
	type: 'html',
	animation: 'fade',
	animationSpeed: 2000,
	animationEasing: 'swing',
	animationType: 'full',

	delay: 5000,
	delayStart: 5000,
});

$('.element2').atrotating({
	type: 'html',
	animation: 'fade',
	animationSpeed: 2000,
	animationEasing: 'swing',
	animationType: 'full',

	delay: 5000,
	delayStart: 5000,
});

$('.element3').atrotating({
	type: 'html',
	animation: 'fade',
	animationSpeed: 2000,
	animationEasing: 'swing',
	animationType: 'full',

	delay: 5000,
	delayStart: 5000,
});
$('.element4').atrotating({
	type: 'html',
	animation: 'fade',
	animationSpeed: 2000,
	animationEasing: 'swing',
	animationType: 'full',

	delay: 5000,
	delayStart: 5000,
});
$('.element5').atrotating({
	type: 'html',
	animation: 'fade',
	animationSpeed: 2000,
	animationEasing: 'swing',
	animationType: 'full',

	delay: 5000,
	delayStart: 5000,
});
	
$('.boilers').atrotating({
	type: 'html',
});
	
});

</script>

<script>
wow = new WOW(
  {
	animateClass: 'animated',
	offset:       100,
	callback:     function(box) {
	  console.log("WOW: animating <" + box.tagName.toLowerCase() + ">")
	}
  }
);
wow.init();
document.getElementById('moar').onclick = function() {
  var section = document.createElement('section');
  section.className = 'section--purple wow fadeInDown';
  this.parentNode.insertBefore(section, this);
};
function backchng(){
	var bgcolor = String($("body").css("background-color"));
		if(bgcolor.length==18){
	  		$("body").css("background-color","#000000");
			$("h1").css("color","#fffa2f");
			$("h2").css("color","#fffa2f");
			$("h3").css("color","#fffa2f");
			$("h4").css("color","#fffa2f");
			$("h5").css("color","#fffa2f");
			$("h6").css("color","#fffa2f");
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
		}else{
			$("body").css("background-color","#ffffff");
			$("h1").css("color","#696969");
			$("h2").css("color","#696969");
			$("h3").css("color","#008bbb");
			$("h4").css("color","#696969");
			$("h5").css("color","#696969");
			$("h6").css("color","#696969");
			$("a.login_link").css("color", "#696969");
			$("table").css("color", "#696969");
			$("label.radios").css("color", "#696969");
			$("input").css("color", "#696969");
			$("tr.even").css("background-color","#696969");
			$("tr.odd").css("background-color","#696969");
			$("label").css("color", "#696969");
			$("a").css("color", "#696969");
			$(".footer_box p").css("color", "#696969");
			$(".dropdown-menu").css("background-color","#696969");
		}
}
</script>

<script>
function myChat() {
    window.open("https://wblabour.gov.in/node/135", "_blank", "toolbar=yes,scrollbars=yes,resizable=yes,top=100,left=500,width=400,height=400");
}
</script>



</body>
</html>
