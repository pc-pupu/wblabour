<!--<link rel='stylesheet prefetch' href='http://logicbox.net/jquery/simplyscroll/jquery.simplyscroll.css'>-->
<style type="text/css">
.simply-scroll-container { /* Container DIV - automatically generated */
	position: relative;
}

	.simply-scroll-clip { /* Clip DIV - automatically generated */
		position: relative;
		overflow: hidden;
	}

	.simply-scroll-list { /* UL/OL/DIV - the element that simplyScroll is inited on */
		overflow: hidden;
		margin: 0;
		padding: 0;
		list-style: none;
	}
	
		.simply-scroll-list li {
			padding: 0;
			margin: 0;
			list-style: none;
		}
	
		.simply-scroll-list li img {
			border: none;
			display: block;
		}
	
	.simply-scroll-btn {
		position: absolute;
		background-image: url(buttons.png);
		width: 42px;
		height: 44px;
		z-index:3;
		cursor: pointer;
	}
	
	.simply-scroll-btn-left {
		left: 6px;
		bottom: 6px;
		background-position: 0 -44px;
	}
	.simply-scroll-btn-left.disabled {
		background-position: 0 0 !important;
	}
	.simply-scroll-btn-left:hover, .simply-scroll-btn-left:focus {
		background-position: 0 -88px;
	}
	
	.simply-scroll-btn-right {
		right: 6px;
		bottom: 6px;
		background-position: -84px -44px;
	}
	.simply-scroll-btn-right.disabled {
		background-position: -84px 0 !important;
	}
	.simply-scroll-btn-right:hover, .simply-scroll-btn-right:focus {
		background-position: -84px -88px;
	}
	
	.simply-scroll-btn-up {
		right: 6px;
		top: 6px;
		background-position: -126px -44px;
	}
	.simply-scroll-btn-up.disabled {
		background-position: -126px 0 !important;
	}
	.simply-scroll-btn-up:hover, .simply-scroll-btn-up:focus {
		background-position: -126px -88px;
	}
	
	.simply-scroll-btn-down {
		right: 6px;
		bottom: 6px;
		background-position: -42px -44px;
	}
	.simply-scroll-btn-down.disabled {
		background-position: -42px 0 !important;
	}
	.simply-scroll-btn-down:hover, .simply-scroll-btn-down:focus {
		background-position: -42px -88px;
	}
	
	.simply-scroll-btn-pause {
		right: 6px;
		bottom: 6px;
		background-position: -168px -44px;
	}
	.simply-scroll-btn-pause:hover, .simply-scroll-btn-pause:focus {
		background-position: -168px -88px;
	}
	
	.simply-scroll-btn-pause.active {
		background-position: -84px -44px;
	}
	.simply-scroll-btn-pause.active:hover, .simply-scroll-btn-pause.active:focus {
		background-position: -84px -88px;
	}

/* Custom class modifications - override classees

.simply-scroll is default

*/

.simply-scroll { /* Customisable base class for style override DIV */
	width: 100%;
	height: 80px;
	margin-bottom: 1em;
}

	.simply-scroll .simply-scroll-clip {
		width: 100%;
		height: 80px;
	}
	
		.simply-scroll .simply-scroll-list {}
		
		.simply-scroll .simply-scroll-list li {
			float: left;
			/*width: 290px;*/
			width:217px;
			height: 80px;
			margin-right:10px;
		}
		.simply-scroll .simply-scroll-list li img {}
	
	.simply-scroll .simply-scroll-btn {}
	
	.simply-scroll .simply-scroll-btn-left {}
	.simply-scroll .simply-scroll-btn-left.disabled {}
	.simply-scroll .simply-scroll-btn-left:hover {}
	
	.simply-scroll .simply-scroll-btn-right {}
	.simply-scroll .simply-scroll-btn-right.disabled {}
	.simply-scroll .simply-scroll-btn-right:hover {}
	
	.simply-scroll .simply-scroll-btn-up {}
	.simply-scroll .simply-scroll-btn-up.disabled {}
	.simply-scroll .simply-scroll-btn-up:hover {}
	
	.simply-scroll .simply-scroll-btn-down {}
	.simply-scroll .simply-scroll-btn-down.disabled {}
	.simply-scroll .simply-scroll-btn-down:hover {}







</style>
		<ul class="thumbnails" id="scroller">
                    <li class="col-sm-2 col-md-offset-2">
    						<div class="fff">
								<div class="thumbnail">
                                <?php //print_r($rows);?>
								<a href="https://mygov.in/" target="_blank"> <?php print $rows[0]['field_ad_img'];?> </a>
								</div>
                            </div>
                        </li>
                      <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="http://www.banglarmukh.gov.in/"  target="_blank" ><?php print $rows[1]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>
                        <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="https://www.employmentbankwb.gov.in/" target="_blank">
                                    	<?php print $rows[2]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>
                        <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="http://wbfin.nic.in/"  target="_blank" >
                                    	<?php print $rows[3]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>  
                        <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="http://wbidc.com/"  target="_blank" >
                                    	<?php print $rows[4]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>
                        <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="https://www.ssy.wblabour.gov.in/"  target="_blank" >
                                    	<?php print $rows[10]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>
                        
                        <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="http://wbtdc.gov.in/"  target="_blank" >
                                    	<?php print $rows[5]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>
                        
                        <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<!--<a href="http://wbpower.nic.in/"  target="_blank" >-->
                                   		 <a href="https://silpasathi.wb.gov.in/"  target="_blank" >
                                    	<?php print $rows[6]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>
                        
                        <!--<li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="http://wbcmo.gov.in/"  target="_blank" >
                                    	<?php print $rows[7]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>-->
                        
                        <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="http://ncs.gov.in/"  target="_blank" >
                                    	<?php print $rows[8]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>
                        <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="https://www.ssy.wblabour.gov.in/"  target="_blank" >
                                    	<?php print $rows[9]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>
                         <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="https://bsk.wb.gov.in"  target="_blank" >
                                    	<?php print $rows[11]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>
                        <li class="col-sm-2">
							<div class="fff">
								<div class="thumbnail">
									<a href="http://karmasangbad.wblabour.gov.in/"  target="_blank" >
                                    	<?php print $rows[12]['field_ad_img'];?></a>
								</div>
                            </div>
                        </li>
                        
            </ul>
 <?php
  global $base_root,$base_path;
?>           
 <script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery-2.1.3.min.js"></script>
 <script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.simplyscroll.min.js"></script>
<script type="application/javascript">
$("#scroller").simplyScroll();
</script>