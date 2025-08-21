<?php global $user,$base_root,$base_path,$base_url; ?>


<?php
	if(in_array('maptrackuser', $user->roles)) {?>
    
    <!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>SWO</title>
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.2.0/css/all.css" integrity="sha384-hWVjflwFxL6sNzntih27bfxkr27PmbbK/iSvJ+a4+0owXq79v+lsFkW54bOGbiDQ" crossorigin="anonymous">
    <link rel="stylesheet" href="<?php print $base_root.$base_path?>sites/all/themes/est/css/style_prc.css" />
    <link rel="stylesheet" href="<?php print $base_root.$base_path?>sites/all/themes/est/css/perfect-scrollbar.min.css" />
    <link rel="stylesheet" href="<?php print $base_root.$base_path?>sites/all/themes/est/css/fSelect.css">
    
    <script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/est/js/jquery-1.9.1.js"></script> 
	<link href="<?php print $base_root.$base_path?>sites/all/themes/est/css/bootstrap-datepicker.css" rel="stylesheet">
    <script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/est/js/bootstrap-datepicker.js"></script>
    
    <script language="javascript" src="<?php print $base_root.$base_path?>code/highstock.js"></script>
    <script language="javascript" src="<?php print $base_root.$base_path?>code/highcharts-3d.js"></script>
    <script language="javascript" src="<?php print $base_root.$base_path?>code/modules/exporting.js"></script>
    <script language="javascript" src="<?php print $base_root.$base_path?>code/modules/export-data.js"></script>
      
</head>

<body>

    <div class="container-scroller">

        <nav class="navbar navbar-default col-lg-12 col-12 p-0 fixed-top d-flex flex-row">
            <div class="text-center navbar-brand-wrapper">
                <a class="navbar-brand brand-logo" href="<?php print $base_root.$base_path?>dashboard-prcsec"><img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/logo.png" /></a>
                <a class="navbar-brand brand-logo-mini" href="<?php print $base_root.$base_path?>dashboard-prcsec"><img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/logo-min.png" alt=""></a>
            </div>
            <div class="navbar-menu-wrapper d-flex align-items-center">
					<div class="user-name"><?php if($user->uid=='1461'){?>Welcome, Principal Secretary<?php }elseif($user->uid=='1523'){?> Welcome, Special Secretary<?php }elseif($user->uid=='1650'){?> Welcome, Officer on Special Duty, IT & eGov<?php }?></div>
					<div class="logout"><a href="<?php print $base_root.$base_path?>user/logout"><i class="fa fa-sign-out-alt"></i> Logout</a></div>
            </div>
        </nav>
        <?php /*?><?php
        $urlarr = $_SERVER['HTTP_HOST'] . request_uri();
		$urlarr = explode("/",$urlarr);
		if (in_array("dashboard-prcsec", $urlarr)){?>
			<div class="card card-statistics total-registration-box dashboard-count-box">
            	<h4 class="bold-text"><span class="counter">3520</span></h4>
                <h2>Total number of application</h2>
            </div>
		<?php }
		?><?php */?>
            
      

        <div class="container-fluid">
			
            <div class="row">

                <div class="content-wrapper">
                    <?php if ($messages): ?>
                        <div id="messages"><div class="section clearfix">
                          <?php print $messages; ?>
                        </div></div> 
                      <?php endif; ?>
					<?php print render($page['content']); ?>
                    
                 </div>      

                <footer class="footer">
                    <div class="container-fluid clearfix">
						<span class="float-left"><strong>&copy; 2018 - 2019 Department of Labour</strong> - All Rights Reserved </span>
						<span class="float-right"><img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/nic_logo.png" width="" height="" alt=""/></span>
                    </div>
                </footer>

            </div>
        </div>

    </div>

    

   <!-- <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/jquery.min.js"></script>-->
    <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/popper.min.js"></script>
    <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/bootstrap.min.js"></script>
    <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/perfect-scrollbar.jquery.min.js"></script>
    <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/off-canvas.js"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/waypoints/4.0.1/jquery.waypoints.min.js"></script>
	<script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/jquery.countup.js"></script>
	<script>
	$('.counter').countUp();
	</script>
    
     <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/fSelect.js"></script>
    <script>
	(function($) {
		$(function() {
			$('.district_name').fSelect();
		});
	})(jQuery);
	</script>
	
	<script type="text/javascript">
		jQuery(document).ready(function(){
			jQuery('.datepiker').datepicker({
				//minViewMode: 'years',
				orientation: 'auto',
				autoclose: true,
				format: 'dd-mm-yyyy',
				//endDate: '+0d'
			});
			
			jQuery('.datepikersecfrom').datepicker({
				//minViewMode: 'years',
				orientation: 'auto',
				autoclose: true,
				format: 'dd-mm-yyyy',
				startDate : '01-01-2015',
				endDate : '+d'
				//endDate: '+0d'
			});
			
			jQuery('.datepikersecto').datepicker({
				//minViewMode: 'years',
				orientation: 'auto',
				autoclose: true,
				format: 'dd-mm-yyyy',
				endDate : '+d'
				//endDate: '+0d'
			});
			
			
			jQuery('.datepikersecfromlc').datepicker({
				//minViewMode: 'years',
				orientation: 'auto',
				autoclose: true,
				format: 'dd-mm-yyyy',
				startDate : '01-01-2015',
				endDate : '+d'
				//endDate: '+0d'
			});
			
			jQuery('.datepikersectolc').datepicker({
				//minViewMode: 'years',
				orientation: 'auto',
				autoclose: true,
				format: 'dd-mm-yyyy',
				endDate : '+d'
				//endDate: '+0d'
			});
			
			
		});
	</script>
</body>
</html>
    
	<?php }else{
		
		$query = db_select('ld_users_details', 'us');
$query->leftJoin('users', 'u', 'u.uid=us.uid');
$query ->fields('us', array( 'fname','mname','lname','gender','dob','mobile','email','pincode','state','district','subdivision','areatype','block','panchayat','policestation','postoffice','address','ldapplicationflag'));
$query ->fields('u', array( 'name'));
$query->condition('us.uid',trim($user->uid),'=');
$result = $query->execute();
$data = $result->fetchObject();
		?>


<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>SWO</title>
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.2.0/css/all.css" integrity="sha384-hWVjflwFxL6sNzntih27bfxkr27PmbbK/iSvJ+a4+0owXq79v+lsFkW54bOGbiDQ" crossorigin="anonymous">
    <link rel="stylesheet" href="<?php print $base_root.$base_path?>sites/all/themes/est/css/style.css" />
    <link rel="stylesheet" href="<?php print $base_root.$base_path?>sites/all/themes/est/css/perfect-scrollbar.min.css" />
    
    <script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/est/js/jquery-1.9.1.js"></script> 
	<link href="<?php print $base_root.$base_path?>sites/all/themes/est/css/bootstrap-datepicker.css" rel="stylesheet">
    <script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/est/js/bootstrap-datepicker.js"></script>  
</head>

<body>

    <div class="container-scroller">

        <nav class="navbar navbar-default col-lg-12 col-12 p-0 fixed-top d-flex flex-row">
            <div class="text-center navbar-brand-wrapper">
                <a class="navbar-brand brand-logo" href="index.html"><img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/logo.png" /></a>
                <a class="navbar-brand brand-logo-mini" href="index.html"><img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/logo-min.png" alt=""></a>
            </div>
            <div class="navbar-menu-wrapper d-flex align-items-center">
                <button class="navbar-toggler navbar-toggler d-none d-lg-block navbar-dark align-self-center mr-3" type="button" data-toggle="minimize">
                    <span class="navbar-toggler-icon"></span>
                </button>

                <form class="form-inline ml-lg-auto mt-md-0 d-none d-lg-block">
                    <input class="form-control mr-sm-2 search" type="text" placeholder="Search">
                </form>
                <button class="navbar-toggler navbar-dark navbar-toggler-right d-lg-none align-self-center" type="button" data-toggle="offcanvas">
                    <span class="navbar-toggler-icon"></span>
                </button>
            </div>
        </nav>

        <div class="container-fluid">
            <div class="row row-offcanvas row-offcanvas-right">

                
					
                    <nav class="bg-white sidebar sidebar-offcanvas" id="sidebar">
                    <div class="user-info">
                        <p class="name"><i class="fa fa-user"></i> <?php if(!empty($data->fname) && (!empty($data->lname))){echo $data->fname." ".$data->mname." ".$data->lname;}else{ echo "N/A";}?></p>
                        <span class="online"><i class="fa fa-envelope"></i> <?php if(!empty($data->email)){ echo $data->email;}else{ echo "N/A";}?></span>
                    </div>
                    <ul class="nav">
                        <li class="nav-item active">
                            <a class="nav-link" href="<?php print $base_root.$base_path?>dashboard">
                                <img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/icons/dashboard.png" alt="">
                                <span class="menu-title">Dashboard</span>
                            </a>
                        </li>

                         <li class="nav-item ">
                            <a class="nav-link" href="<?php print $base_root.$base_path?>establishment">
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/icons/establishment.png" alt="">    
                                    <span class="menu-title">All Establishments</span>
                                </a>
                        </li>
						
                       <!--  <li class="nav-item">
                           <a class="nav-link" data-toggle="collapse" href="#sample-pages" aria-expanded="false" aria-controls="sample-pages">
                                <img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/icons/establishment.png" alt="">
                                <span class="menu-title">Establishments <i class="fa fa-angle-down"></i></span>
                            </a>
							
							<div class="collapse" id="sample-pages">
							<ul class="nav flex-column sub-menu">
							  <li class="nav-item">
								<a class="nav-link" href="<?php print $base_root.$base_path?>add-establishment">
									<img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/icons/plus.png" alt="">	
								  	<span class="menu-title">Add Establishments</span>
								</a>
							  </li>
								<li class="nav-item">
								<a class="nav-link" href="<?php print $base_root.$base_path?>establishment">
									<img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/icons/008-list.png" alt="">	
								  	<span class="menu-title">All Establishments</span>
								</a>
							  </li>

							</ul>
						  </div>
						</li> -->
                            <li class="nav-item">
                                <a class="nav-link" href="<?php print $base_root.$base_path?>profile">
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/icons/settings.png" alt="">
                                    <span class="menu-title">My Profile</span>
                                </a>
                            </li>


                            <li class="nav-item">
                                <a class="nav-link" href="<?php print $base_root.$base_path?>user/logout">
                                    <img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/icons/logout.png" alt="">
                                    <span class="menu-title">Logout</span>
                                </a>
                            </li>

                    </ul>
                    </nav>
                    
                    
					
					
                <div class="content-wrapper">
                    <?php if ($messages): ?>
                        <div id="messages"><div class="section clearfix">
                          <?php print $messages; ?>
                        </div></div> <!-- /.section, /#messages -->
                      <?php endif; ?>
					<?php print render($page['content']); ?>
                    
                 </div>

                       

                <footer class="footer">
                    <div class="container-fluid clearfix">
						<span class="float-left"><strong>&copy; 2018 - 2019 Department of Labour</strong> - All Rights Reserved </span>
						<span class="float-right"><img src="<?php print $base_root.$base_path?>sites/all/themes/est/images/nic_logo.png" width="" height="" alt=""/></span>
                    </div>
                </footer>

            </div>
        </div>

    </div>

    <!--<div id="addservice" class="modal fade" role="dialog">
        <div class="modal-dialog">
            <div class="modal-content">
                <div class="modal-header">
                    <h4 class="modal-title">Add Service</h4>
                    <button type="button" class="close" data-dismiss="modal">&times;</button>
                </div>
                <div class="modal-body">
                    <form class="forms-sample">
                        <div class="col-xl-12">
                            <div class="selectpicker">
                                <select class="form-control p-input">
                                    <option>---Establishment Name---</option>
                                    <option>testLD boiler</option>
                                    <option>testLD boiler</option>
                                </select>
                            </div>
                        </div>
                        <div class="col-xl-12">
                            <div class="selectpicker">
                                <select class="form-control p-input">
                                    <option>---Directorate---</option>
                                    <option>Labour Commission</option>
                                    <option>Directorate of Boilers</option>
                                    <option>Directorate of Factories</option>
                                </select>
                            </div>
                        </div>

                        <div class="col-xl-12">
                            <div class="selectpicker">
                                <select class="form-control p-input">
                                    <option>---Services---</option>
                                    <option>Registration of Boilers under The Boilers Act, 1923</option>
                                    <option>Registration of Boilers under The Boilers Act, 1923</option>
                                    <option>Registration of Boilers under The Boilers Act, 1923</option>
                                </select>
                            </div>
                        </div>
                    </form>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-primary" data-dismiss="modal">Add</button>
                </div>
            </div>

        </div>
    </div>-->

   <!-- <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/jquery.min.js"></script>-->
    <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/popper.min.js"></script>
    <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/bootstrap.min.js"></script>
    <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/perfect-scrollbar.jquery.min.js"></script>
    <script src="<?php print $base_root.$base_path?>sites/all/themes/est/js/off-canvas.js"></script>
	
	<script type="text/javascript">
		// When the document is ready
		jQuery(document).ready(function(){
			jQuery('.datepiker').datepicker({
				//minViewMode: 'years',
				orientation: 'auto',
				autoclose: true,
				format: 'dd-mm-yyyy',
				//endDate: '+0d'
			});
			
			
		});
	</script>
</body>
</html>    
    
 <?php }?>   
                    
                    
                    



