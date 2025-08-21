	<?php global $base_root,$base_path;?>
         <div class="section_headding2">
              <h1><?php print $rows[0]['title'];?></h1>
            </div>
            <div class="small_img"> <?php print $rows[0]['field_body_img'];?> </div>
              <div class="doing_business_box">
                <div class="small_text"><?php print $rows[0]['body'];?></div>
                <div class="small_btn">
                
                <a href="<?php print $base_root.$base_path.'disclaimer';?>" class="swo_btm"><img src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/images/SWO_btm.gif" alt="ease-of-doing-business" ></a>
                <a href="<?php print $base_root.$base_path.'ease-of-doing-business';?>" class="read_more">Read More</a> 
                
                
                </div>
                
            </div>