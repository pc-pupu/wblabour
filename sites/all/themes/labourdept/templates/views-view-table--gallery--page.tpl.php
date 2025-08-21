<?php global $base_root,$base_path;?>



<link href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/font-awesome.css" rel="stylesheet">
<link rel="stylesheet" href="<?php print $base_root.$base_path?>sites/all/themes/labourdept/css/simplelightbox.min.css">
<link href='https://fonts.googleapis.com/css?family=Lato:400,300,100,700,900' rel='stylesheet' type='text/css'>





 <script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/vendor/jquery-1.11.3.min.js"></script>
 <script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/vendor/modernizr-2.8.3.min.js"></script>
 
 
 <div class="container gallery">
    <ul class="thumbnails">
         <?php foreach($rows as $val){?>    
        <li class="col-sm-3">
        	<figure class="featured-thumbnail">
                <a class="thumbnail"  href="<?php print $base_root.$base_path?>sites/default/files/gallery/<?php print $val["filename"]?>">
                <img class="group1" src="<?php print $base_root.$base_path?>sites/default/files/gallery/<?php print $val["filename"]?>" style="height:170px; margin-top:0px" title="<?php print $val["title"]?>" />
                </a>
               </figure> 
            </li> <!--end thumb -->
            <?php }?>
    </ul><!--end thumbnails -->
</div>

        
        
        <!-- Simple Lightbox -->
        <script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/simple-lightbox.min.js"></script>
        <!-- Sticky -->
        <script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.sticky.js"></script>
        <!-- OWL-Carousel -->
        <script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/owl.carousel.min.js"></script>
        <!-- jQuery inview -->
        <script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.inview.js"></script>
        <!-- Shuffle jQuery -->
        <script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.shuffle.min.js"></script>
        <!-- Main JS -->
        <script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/vendor/main.js"></script>