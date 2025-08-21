<?php global $base_root,$base_path;?>
<?php 
if($logged_in) {
global $user;
$url_arr = $_SERVER['REQUEST_URI'];
$currnt_page = explode("/",$url_arr);
$userData = getAllUidInfoFromPid($user->uid);
?>	
<!DOCTYPE html>
<html lang="en">
	<head>
		<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
		<meta charset="utf-8" />
		<title>Assets - Dashboard</title>

		<meta name="description" content="overview &amp; stats" />
		<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0" />

		<!-- bootstrap & fontawesome -->
		<link rel="stylesheet" href="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/css/bootstrap.min.css" />
		<link rel="stylesheet" href="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/font-awesome/4.5.0/css/font-awesome.min.css" />

		<!-- text fonts -->

        <link href='//fonts.googleapis.com/css?family=Roboto+Slab' rel='stylesheet' type='text/css'>
		<link href="https://fonts.googleapis.com/css?family=Open+Sans:400,600,700" rel="stylesheet">
		<link href="https://fonts.googleapis.com/css?family=Viga" rel="stylesheet">

		<!-- ace styles -->
		<link rel="stylesheet" href="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/css/ace.min.css" class="ace-main-stylesheet" id="main-ace-style" />
		
		<!--[if lte IE 9]>
			<link rel="stylesheet" href="assets/css/ace-part2.min.css" class="ace-main-stylesheet" />
		<![endif]-->
		<link rel="stylesheet" href="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/css/ace-skins.min.css" />
		<link rel="stylesheet" href="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/css/ace-rtl.min.css" />
        
        
        <script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/asset/js/jquery-1.9.1.js"></script> 
        
                <!--for bootstrap datepicker-->
        <link href="<?php print $base_root.$base_path?>sites/all/themes/asset/css/bootstrap-datepicker.css" rel="stylesheet">
        <script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/asset/js/bootstrap-datepicker.js"></script>  
        
        
        <script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/asset/js/moment.js"></script>  
        <link href="<?php print $base_root.$base_path?>sites/all/themes/asset/css/bootstrap-datetimepicker.css" rel="stylesheet">
        <script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/asset/js/bootstrap-datetimepicker.js" charset="UTF-8"></script>


		<!--[if lte IE 9]>
		  <link rel="stylesheet" href="assets/css/ace-ie.min.css" />
		<![endif]-->

		<!-- inline styles related to this page -->

		<!-- ace settings handler -->
		<script src="<?php print $base_root.$base_path?>sites/all/themes/asset/assets/js/ace-extra.min.js"></script>

		<!-- HTML5shiv and Respond.js for IE8 to support HTML5 elements and media queries -->

		<!--[if lte IE 8]>
		<script src="assets/js/html5shiv.min.js"></script>
		<script src="assets/js/respond.min.js"></script>
		<![endif]-->
        
	</head>

	<body class="no-skin">
		
		<div id="navbar" class="navbar navbar-default ace-save-state">
			<div class="navbar-container ace-save-state" id="navbar-container">
			
				
				<button type="button" class="navbar-toggle menu-toggler pull-left" id="menu-toggler" data-target="#sidebar">
					<span class="sr-only">Toggle sidebar</span>
					<span class="icon-bar"></span>

					<span class="icon-bar"></span>

					<span class="icon-bar"></span>
				</button>

				<div class="navbar-header pull-left">
					<a href="#" class="navbar-brand">
						<small>
							<img src="<?php echo $base_root.$base_path.'sites/all/themes/asset/images/Asset_logo.png'?>"  style="width: 25px;"/> Asset Declaration Management System |
                             <?php if($userData['role_name']=='assetadmin'){
								 echo "Admin Control Dashboard";
							 }else{
							  	 echo !empty($userData['fname'])? $userData['fname'].', '.$userData['designation'].', '.$userData['hrms_id']  : 'Please fillup your profile first'; 
							 }?>
						</small>
					</a>
				</div>

				<div class="navbar-buttons navbar-header pull-right" role="navigation">
					<ul class="nav ace-nav">
									<li><a href="<?php echo $base_root.$base_path.'user/logout'?>">
										<i class="ace-icon fa fa-power-off"></i>
										Logout
									</a>
									</li>
									<li>
									<a href="<?php echo $base_root.$base_path.'profileupdate'?>">
										<i class="ace-icon fa fa-user"></i>
										Profile
									</a>
								</li>
					</ul>
				</div>
					
			</div>	
				
		</div>
		<!--<div class="breadcrumbs ace-save-state" id="breadcrumbs">
			<div class="row">
			<div class="col-md-10">
				<span class="user-info"><i class="fa fa-user"></i> Welcome, <?php echo $userData['name'];?></span>
				</div>
			<div class="col-md-2">
			
						<ul class="breadcrumb">
							<li><i class="fa fa-home"></i> Home</li
						</ul>
				</div>
				</div>
	  </div>-->

		<div class="main-container ace-save-state no-skin" id="main-container">
			<script type="text/javascript">
				try{ace.settings.loadState('main-container')}catch(e){}
			</script>

			<div id="sidebar" class="sidebar responsive ace-save-state">
				<script type="text/javascript">
					try{ace.settings.loadState('sidebar')}catch(e){}
				</script>

                
                <ul class="nav nav-list">
                	<?php
						
						if (($user->uid!=0) && array_key_exists(9, $user->roles)) {
							$it_manager_mane = menu_tree_all_data('menu-asset-admin-user');
							foreach($it_manager_mane as $val){
								if(!$val['link']['hidden']){
									$link = drupal_get_path_alias($val['link']['link_path']);
									
									//Active Class Logic
									$active_class = '';
									$open_class = '';
									if(trim($currnt_page[1]) == trim($link)){
										$active_class = 'active';	
									}
									if($val['link']['has_children']){
											
											foreach($val['below'] as $level2_link){
												$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
												if(trim($currnt_page[1]) == trim($level2_path_link)){
													$active_class = 'active open';
												}
											}
											
									}
									?>	
                
                                    <li class="<?php echo $active_class." ".$open_class;?>">
                                    	<a href="<?php print $base_root.$base_path.$link;?>" class="<?php if($val['link']['has_children']){?> dropdown-toggle<?php }?>">
                                            
                                          <?php 
										  if(trim($val['link']['link_title']) == 'Dashboard'){
												echo '<i class="menu-icon fa fa-tachometer"></i>';
											}elseif(trim($val['link']['link_title']) == 'User'){
												echo '<i class="menu-icon fa fa-user"></i>';
											}elseif(trim($val['link']['link_title']) == 'Receive DoA'){
												echo '<i class="menu-icon fa fa-check-circle"></i>';
											}elseif(trim($val['link']['link_title']) == 'Received List of DoA'){
												echo '<i class="menu-icon fa fa-list-ul"></i>'; 
											}elseif(trim($val['link']['link_title']) == 'Pending List of DoA'){
												echo '<i class="menu-icon fa fa-hourglass-half"></i>';
											}elseif(trim($val['link']['link_title']) == 'Yearly Received DoA'){
												echo '<i class="menu-icon fa fa-table"></i>';
											}elseif(trim($val['link']['link_title']) == 'GroupA Officers DoA'){
												echo '<i class="menu-icon fa fa-object-group"></i>';
											}elseif(trim($val['link']['link_title']) == 'INBOX'){
												echo '<i class="menu-icon fa fa-envelope"></i>';
											}elseif(trim($val['link']['link_title']) == 'OUTBOX'){
												echo '<i class="menu-icon fa fa-download"></i>';
											}elseif(trim($val['link']['link_title']) == 'Backlog DoA'){
												echo '<i class="menu-icon fa fa-folder-open"></i>';
											}
											else{
												echo '<i class="menu-icon fa fa-tachometer"></i>';
											}?> 
                                            
                                            
                                            
                                            
                                            
                                            
                                            <!--<i class="menu-icon fa fa-tachometer"></i>-->
                                            <span class="menu-text"> <?php print $val['link']['link_title']?> </span>
                                            <?php if($val['link']['has_children']){?><b class="arrow fa fa-angle-down"></b><?php }?>
                                        </a>
                                        <b class="arrow"></b>
                                        
                                   <?php if(!empty($val['below'])){?>
                                                     
                                           <ul class="submenu">
                                            <?php foreach($val['below'] as $level2){
                                                    if(!$level2['link']['hidden']){
                                                        $level2_path = drupal_get_path_alias($level2['link']['link_path']);
														//active logic
														$subactive = '';
														if(trim($currnt_page[1]) == trim($level2_path)){
															$subactive = 'active';
														}
														
														?>
                                                            <li class="<?php echo $subactive;?>">
                                                                <a href="<?php print $base_root.$base_path.$level2_path;?>" class="">
                                                                    <i class="menu-icon fa fa-caret-right"></i>
                                                                    <?php print $level2['link']['link_title'];?>
                                                                </a>
                                
                                                                <b class="arrow"></b>
                                                            </li>
                                                                    
                                                    <?php }
                                                }?>
                                              </ul>      
                                     <?php }?>
                                     
                                     </li>
                       
                		<?php }
							}
						}elseif (($user->uid!=0) && array_key_exists(8, $user->roles)) {
							$it_manager_mane = menu_tree_all_data('menu-asset-user');
							foreach($it_manager_mane as $val){
								if(!$val['link']['hidden']){
									$link = drupal_get_path_alias($val['link']['link_path']);
									
									//Active Class Logic
									$active_class = '';
									$open_class = '';
									if(trim($currnt_page[1]) == trim($link)){
										$active_class = 'active';	
									}
									if($val['link']['has_children']){
											
											foreach($val['below'] as $level2_link){
												$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
												if(trim($currnt_page[1]) == trim($level2_path_link)){
													$active_class = 'active open';
												}
											}
											
									} 
									?>	 
                
                                    <li class="<?php echo $active_class." ".$open_class;?>">
                                    	<a href="<?php print $base_root.$base_path.$link;?>" class="<?php if($val['link']['has_children']){?> dropdown-toggle<?php }?>">
                                        	<?php 
											if(trim($val['link']['link_title']) == 'Dashboard'){
												echo '<i class="menu-icon fa fa-tachometer"></i>';
											}elseif(trim($val['link']['link_title']) == 'Received List of DoA'){
												echo '<i class="menu-icon fa fa-list-ul"></i>'; 
											}elseif(trim($val['link']['link_title']) == 'Pending List of DoA'){
												echo '<i class="menu-icon fa fa-hourglass-half"></i>';
											}elseif(trim($val['link']['link_title']) == 'Yearly Received DoA'){
												echo '<i class="menu-icon fa fa-table"></i>';
											}elseif(trim($val['link']['link_title']) == 'GroupA Officers DoA'){
												echo '<i class="menu-icon fa fa-object-group"></i>';
											}elseif(trim($val['link']['link_title']) == 'OUTBOX'){
												echo '<i class="menu-icon fa fa-download"></i>';
											}elseif(trim($val['link']['link_title']) == 'Backlog DoA'){
												echo '<i class="menu-icon fa fa-folder-open"></i>';
											}
											else{
												echo '<i class="menu-icon fa fa-tachometer"></i>';
											}?>
                                        	
                                            <!--<i class="menu-icon fa fa-tachometer"></i>-->
                                            <span class="menu-text"> <?php print $val['link']['link_title']?> </span>
                                            <?php if($val['link']['has_children']){?><b class="arrow fa fa-angle-down"></b><?php }?>
                                        </a>
                                        <b class="arrow"></b>
                                        
                                   <?php if(!empty($val['below'])){?>
                                                     
                                           <ul class="submenu">
                                            <?php foreach($val['below'] as $level2){
                                                    if(!$level2['link']['hidden']){
                                                        $level2_path = drupal_get_path_alias($level2['link']['link_path']);
														//active logic
														$subactive = '';
														if(trim($currnt_page[1]) == trim($level2_path)){
															$subactive = 'active';
														}
														
														?>
                                                            <li class="<?php echo $subactive;?>">
                                                                <a href="<?php print $base_root.$base_path.$level2_path;?>" class="">
                                                                    <i class="menu-icon fa fa-caret-right"></i>
                                                                    <?php print $level2['link']['link_title'];?>
                                                                </a>
                                
                                                                <b class="arrow"></b>
                                                            </li>
                                                                    
                                                    <?php }
                                                }?>
                                              </ul>      
                                     <?php }?>
                                     
                                     </li>
                       
                		<?php }
							}
						}elseif (($user->uid!=0) && array_key_exists(10, $user->roles)) {
							$it_manager_mane = menu_tree_all_data('menu-asset-directorate-admin-men');
							foreach($it_manager_mane as $val){
								if(!$val['link']['hidden']){
									$link = drupal_get_path_alias($val['link']['link_path']);
									
									//Active Class Logic
									$active_class = '';
									$open_class = '';
									if(trim($currnt_page[1]) == trim($link)){
										$active_class = 'active';	
									}
									if($val['link']['has_children']){
											
											foreach($val['below'] as $level2_link){
												$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
												if(trim($currnt_page[1]) == trim($level2_path_link)){
													$active_class = 'active open';
												}
											}
											
									} 
									?>	 
                                    
                                    <?php
									if($link=='directorate-inbox-list-from-field'  && $userData['directorate_code']!='LC'){
										
									}elseif($link=='field-outbox-accept-reject'  && $userData['directorate_code']!='LC'){
										
									}else{?>
                
                                    <li class="<?php echo $active_class." ".$open_class;?>">
                                    	<a href="<?php print $base_root.$base_path.$link;?>" class="<?php if($val['link']['has_children']){?> dropdown-toggle<?php }?>">
                                        	<?php 
											if(trim($val['link']['link_title']) == 'Receive DoA'){
												echo '<i class="menu-icon fa fa-check-circle"></i>';
											}elseif(trim($val['link']['link_title']) == 'Received List of DoA'){
												echo '<i class="menu-icon fa fa-list-ul"></i>'; 
											}elseif(trim($val['link']['link_title']) == 'Pending List of DoA'){
												echo '<i class="menu-icon fa fa-hourglass-half"></i>';
											}elseif(trim($val['link']['link_title']) == 'Yearly Received DoA'){
												echo '<i class="menu-icon fa fa-table"></i>';
											}elseif(trim($val['link']['link_title']) == 'GroupA Officers DoA'){
												echo '<i class="menu-icon fa fa-object-group"></i>';
											}elseif(trim($val['link']['link_title']) == 'OUTBOX'){
												echo '<i class="menu-icon fa fa-download"></i>';
											}elseif(trim($val['link']['link_title']) == 'Backlog DoA'){
												echo '<i class="menu-icon fa fa-folder-open"></i>';
											}
											else{
												echo '<i class="menu-icon fa fa-tachometer"></i>';
											}?>
                                        	
                                            <!--<i class="menu-icon fa fa-tachometer"></i>-->
                                            <span class="menu-text"> <?php print $val['link']['link_title']?> </span>
                                            <?php if($val['link']['has_children']){?><b class="arrow fa fa-angle-down"></b><?php }?>
                                        </a>
                                        <b class="arrow"></b>
                                        
                                   <?php if(!empty($val['below'])){?>
                                                     
                                           <ul class="submenu">
                                            <?php foreach($val['below'] as $level2){
                                                    if(!$level2['link']['hidden']){
                                                        $level2_path = drupal_get_path_alias($level2['link']['link_path']);
														//active logic
														$subactive = '';
														if(trim($currnt_page[1]) == trim($level2_path)){
															$subactive = 'active';
														}
														
														?>
                                                            <li class="<?php echo $subactive;?>">
                                                                <a href="<?php print $base_root.$base_path.$level2_path;?>" class="">
                                                                    <i class="menu-icon fa fa-caret-right"></i>
                                                                    <?php print $level2['link']['link_title'];?>
                                                                </a>
                                
                                                                <b class="arrow"></b>
                                                            </li>
                                                                    
                                                    <?php }
                                                }?>
                                              </ul>      
                                     <?php }?>
                                     
                                     </li>
                       				<?php }?>
                		<?php }
							}
						}elseif (($user->uid!=0) && array_key_exists(11, $user->roles)) {
							$it_manager_mane = menu_tree_all_data('menu-asset-field-meanu');
							foreach($it_manager_mane as $val){
								if(!$val['link']['hidden']){
									$link = drupal_get_path_alias($val['link']['link_path']);
									
									//Active Class Logic
									$active_class = '';
									$open_class = '';
									if(trim($currnt_page[1]) == trim($link)){
										$active_class = 'active';	
									}
									if($val['link']['has_children']){
											
											foreach($val['below'] as $level2_link){
												$level2_path_link = drupal_get_path_alias($level2_link['link']['link_path']);
												if(trim($currnt_page[1]) == trim($level2_path_link)){
													$active_class = 'active open';
												}
											}
											
									} 
									?>	 
                
                                    <li class="<?php echo $active_class." ".$open_class;?>">
                                    	<a href="<?php print $base_root.$base_path.$link;?>" class="<?php if($val['link']['has_children']){?> dropdown-toggle<?php }?>">
                                        	<?php 
											if(trim($val['link']['link_title']) == 'Receive DOA'){
												echo '<i class="menu-icon fa fa-check-circle"></i>';
											}elseif(trim($val['link']['link_title']) == 'Received List of DOA'){
												echo '<i class="menu-icon fa fa-list-ul"></i>'; 
											}elseif(trim($val['link']['link_title']) == 'Pending List of DOA'){
												echo '<i class="menu-icon fa fa-hourglass-half"></i>';
											}elseif(trim($val['link']['link_title']) == 'Yearly Received DOA'){
												echo '<i class="menu-icon fa fa-table"></i>';
											}elseif(trim($val['link']['link_title']) == 'GroupA Officers DOA'){
												echo '<i class="menu-icon fa fa-object-group"></i>';
											}elseif(trim($val['link']['link_title']) == 'OUTBOX'){
												echo '<i class="menu-icon fa fa-download"></i>';
											}elseif(trim($val['link']['link_title']) == 'Backlog DOA'){
												echo '<i class="menu-icon fa fa-folder-open"></i>';
											}
											else{
												echo '<i class="menu-icon fa fa-tachometer"></i>';
											}?>
                                        	
                                            <!--<i class="menu-icon fa fa-tachometer"></i>-->
                                            <span class="menu-text"> <?php print $val['link']['link_title']?> </span>
                                            <?php if($val['link']['has_children']){?><b class="arrow fa fa-angle-down"></b><?php }?>
                                        </a>
                                        <b class="arrow"></b>
                                        
                                   <?php if(!empty($val['below'])){?>
                                                     
                                           <ul class="submenu">
                                            <?php foreach($val['below'] as $level2){
                                                    if(!$level2['link']['hidden']){
                                                        $level2_path = drupal_get_path_alias($level2['link']['link_path']);
														//active logic
														$subactive = '';
														if(trim($currnt_page[1]) == trim($level2_path)){
															$subactive = 'active';
														}
														
														?>
                                                            <li class="<?php echo $subactive;?>">
                                                                <a href="<?php print $base_root.$base_path.$level2_path;?>" class="">
                                                                    <i class="menu-icon fa fa-caret-right"></i>
                                                                    <?php print $level2['link']['link_title'];?>
                                                                </a>
                                


                                                                <b class="arrow"></b>
                                                            </li>
                                                                    
                                                    <?php }
                                                }?>
                                              </ul>      
                                     <?php }?>
                                     
                                     </li>
                       
                		<?php }
							}
						}?>
                   </ul>
                    
					

				<div class="sidebar-toggle sidebar-collapse" id="sidebar-collapse">
					<i id="sidebar-toggle-icon" class="ace-icon fa fa-angle-double-right ace-save-state" data-icon1="ace-icon fa fa-angle-double-left" data-icon2="ace-icon fa fa-angle-double-right"></i>
				</div>
			</div>

			<div class="main-content">
				<div class="main-content-inner">

					<div class="page-content">
						<div class="row">
							<div class="col-xs-12">
                            	<?php if ($messages): ?>
                                    <div class="alert">
                                      <?php print $messages; ?>
                                    </div>
                                <?php endif; ?>
                                
								<?php if ($tabs): ?>
                                <div class="tabs">
                                  <?php print render($tabs); ?>
                                </div>
                                <?php endif; ?>
                                
								<!-- PAGE CONTENT BEGINS -->
								<?php print render($page['content']); ?>
								<!-- PAGE CONTENT ENDS -->
							</div><!-- /.col -->
						</div><!-- /.row -->
					</div><!-- /.page-content -->
				</div>
			</div><!-- /.main-content -->

			<div class="footer">
				<div class="footer-inner">
					<div class="footer-content">
						<span class="bigger-120">
							Asset Declaration Management System &copy; 2019-2020
						</span>
						
					</div>
				</div>
			</div>

			<a href="#" id="btn-scroll-up" class="btn-scroll-up btn btn-sm btn-inverse">
				<i class="ace-icon fa fa-angle-double-up icon-only bigger-110"></i>
			</a>
		</div><!-- /.main-container -->



<?php 
} ?>





		<!-- basic scripts -->

		<!--[if !IE]> -->
		<!--<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/jquery-2.1.4.min.js"></script>-->

		<!-- <![endif]-->

		<!--[if IE]>
<script src="assets/js/jquery-1.11.3.min.js"></script>
<![endif]-->
		<script type="text/javascript">
			if('ontouchstart' in document.documentElement) document.write("<script src='<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/jquery.mobile.custom.min.js'>"+"<"+"/script>");
		</script>
		<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/bootstrap.min.js"></script>

		<!-- page specific plugin scripts -->

		<!--[if lte IE 8]>
		  <script src="assets/js/excanvas.min.js"></script>
		<![endif]-->
		<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/jquery-ui.custom.min.js"></script>
		<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/jquery.ui.touch-punch.min.js"></script>
		<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/jquery.easypiechart.min.js"></script>
		<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/jquery.sparkline.index.min.js"></script>
		<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/jquery.flot.min.js"></script>
		<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/jquery.flot.pie.min.js"></script>
		<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/jquery.flot.resize.min.js"></script>

		<!-- ace scripts -->
		<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/ace-elements.min.js"></script>
		<!--<script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/ace.min.js"></script>-->
        <script src="<?php echo $base_root.$base_path;?>sites/all/themes/asset/assets/js/ace.js"></script>

		<!-- inline scripts related to this page -->
		<script type="text/javascript">
			jQuery(function($) {
				
				$('.form').find('input, textarea').on('keyup blur focus', function (e) {
				  var $this = $(this),
					  label = $this.prev('label');
				
					  if (e.type === 'keyup') {
							if ($this.val() === '') {
						  label.removeClass('active highlight');
						} else {
						  label.addClass('active highlight');
						}
					} else if (e.type === 'blur') {
						if( $this.val() === '' ) {
							label.removeClass('active highlight'); 
							} else {
							label.removeClass('highlight');   
							}   
					} else if (e.type === 'focus') {
					  
					  if( $this.val() === '' ) {
							label.removeClass('highlight'); 
							} 
					  else if( $this.val() !== '' ) {
							label.addClass('highlight');
							}
					}
				
				});
				
			})
		
		</script>
        
        <script type="text/javascript">
                // When the document is ready
                jQuery(document).ready(function(){
					jQuery('.datepiker_yr').datepicker({
                        minViewMode: 'years',
						orientation: 'auto',
                        autoclose: true,
                        format: 'yyyy',
						//endDate: '+0d'
                    });
					
					jQuery('.datepiker').datepicker({
                       // minViewMode: 'years',
						orientation: 'auto',
                        autoclose: true,
                        format: 'dd-mm-yyyy',
						//endDate: '+0d'
                    });
					
					jQuery('.backlogdate').datepicker({
					//minViewMode: 'years',
					orientation: 'auto',
					autoclose: true,
					format: 'dd-mm-yyyy',
					startDate : '01-01-2020',
					endDate : '08-12-2020'
					//endDate: '+0d'
				});
				
				jQuery('.servicedate').datepicker({
					// minViewMode: 'years',
						orientation: 'auto',
                        autoclose: true,
                        format: 'dd-mm-yyyy',
						endDate: '+0d'
				});
				
				
				// set default dates
				var start = new Date();
				// set end date to max one year period:
				//var end = new Date(new Date().setYear(start.getFullYear()+1));
				var end = new Date();
				
				jQuery('#yearfrom').datepicker({
					startDate : start,
					endDate   : end
				// update "toDate" defaults whenever "fromDate" changes
				}).on('changeDate', function(){
					// set the "toDate" start to not be later than "fromDate" ends:
					//alert($(this).val());
					jQuery('#yearto').datepicker('setStartDate', $(this).val());
					getDaysCal(jQuery('#yearfrom').val(),jQuery('#yearto').val());
				}); 
				
				jQuery('#yearto').datepicker({
					//startDate : start,
					endDate   : end
				// update "fromDate" defaults whenever "toDate" changes
				}).on('changeDate', function(){
					// set the "fromDate" end to not be later than "toDate" starts:
					//alert($(this).val());
					jQuery('#yearfrom').datepicker('setEndDate', $(this).val());
					getDaysCal(jQuery('#yearfrom').val(),jQuery('#yearto').val());
				});
				
					 
                });
				
				function getDaysCal(frm_dt,to_dt){
					//alert('frmdt-->'+frm_dt+'todt-->'+to_dt);
					
					var startDay = parseDate(frm_dt);
					var endDay = parseDate(to_dt);
					
					/*alert((endDay-startDay)/(1000*60*60*24));*/
					
					//alert(datediff(parseDate(frm_dt), parseDate(to_dt)));
					jQuery('#duration').val(Math.round((endDay-startDay)/(1000*60*60*24))+1);
					//alert(Math.round((endDay-startDay)/(1000*60*60*24))+1);
				}
				function parseDate(str) {
					var mdy = str.split('-');
					return new Date(mdy[2], mdy[1]-1, mdy[0]);
				}
            </script>

	</body>
</html>
