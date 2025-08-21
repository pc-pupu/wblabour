<?php global $base_root,$base_path;?>

	<?php
     //echo$GLOBALS['base_url'].'/default/files/'.$val['field_body_photo']; die; 
	?>
    	<div class="service_section1">
        	<div class="row">
             <?php  $i= 0; foreach($rows as $val){ $i++;?> 
                <div class="col-sm-3">
                	<div class="law_pic">
                       
                       <?php //l(t('<img src="'.$GLOBALS['base_url'].'/default/files/'.$val['field_body_photo'].'>'), 
	 							//$val['field_link_path'], array('html' => TRUE, 'attributes'=>array('title' =>'About Us', 'target' => '_blank')));?>
                        
                        
                        
						<a href="<?php print $base_root.$base_path.$val['field_link_path'];?>"> <?php print $val['field_body_photo']; ?> </a>
                        <?php if($i == 1 || $i == 2 || $i == 5){ ?>
                        <div class="section_name wow bounceInLeft" data-wow-delay=".3s"> <?php print $val['title']; ?> </div>
                        <?php } if($i == 3 || $i == 6){?>
                        <div class="section_name wow bounceInDown" data-wow-delay="0.4s"> <?php print $val['title']; ?> </div>
                        <?php } if($i == 4 || $i == 7 || $i == 8){?>
                        <div class="section_name wow bounceInRight" data-wow-delay="0.5s"> <?php print $val['title']; ?> </div>
                        <?php }?>
                    </div>
                </div>
                  <?php	 }	?>	
            </div>
        </div>
        
        <!--<div class="service_section2">
        	<div class="row">
            	<div class="col-sm-3">
                	<div class="law_pic">
               	    	<a href="#"><img src="<?php //print $base_root.$base_path?>sites/all/themes/labourdept/images/small_pic3.jpg" alt=""></a>
                        <div class="section_name wow bounceInLeft" data-wow-delay=".3s">Schemes</div>
                    </div>
                </div>

            </div>
        </div>-->
