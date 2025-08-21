<?php
	/*$total_appl_boilers = 0;
	for($i=0; $i<sizeof($service_boiler['result']); $i++){
		 $total_appl_boilers += $service_boiler['result'][$i]['total_application'];
	}
	
	$total_appl_lc = 0;
	for($i=0; $i<sizeof($service_lc['result']); $i++){
		 $total_appl_lc += $service_lc['result'][$i]['total_application'];
	}
	
	$tot = 0;
	$tot = $total_appl_boilers + $total_appl_lc;*/
	
	$total_appl_boilers = 3666;
	$total_appl_lc = 10520;
	$total_court = 5450;
	$total_shops = 40264;
	$total_factory = 13150;
	$tot = 73150;
	//print_r($service_arr); exit;
?>
		<div class="card card-statistics total-registration-box dashboard-count-box dashboard-banner">
            <h4 class="bold-text"><span class="counter"><?php print $tot;?></span></h4>
            <h2>Total Number of Application</h2>
        </div>
	
		<div class="row content-area"> 
			
        <div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 mb-4">
            <a href="https://wblabour.gov.in/dwsearch" target="_blank"><div class="card card-statistics lc-box dashboard-count-box">
                <div class="card-body">
                    <div class="clearfix">
                        <div class="float-left">
                            <h4 class="text-white">
                              <i class="fa fa-chart-line highlight-icon"></i>
                          </h4>
                        </div>
                        <div class="float-left">
                            <p class="card-text text-white">Labour Commissionerate</p>
                            <h4 class="bold-text text-white"><span class="counter"><?php print $total_appl_lc;?></span></h4>
                        </div>
                    </div>
                    <p class="text-white"><i class="fa fa-box-open"></i> Total Application </p>
                </div>
            </div></a>
        </div>
        <div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 mb-4">
           <a href="https://wblabour.gov.in/boilersearch" target="_blank"> <div class="card card-statistics boiler-box dashboard-count-box">
                <div class="card-body">
                    <div class="clearfix">
                        <div class="float-left">
                            <h4 class="text-white">
                            <i class="fa fa-chart-pie highlight-icon"></i>
                          </h4>
                        </div>
                        <div class="float-left">
                            <p class="card-text text-white">Directorate of Boilers</p>
                            <h4 class="bold-text text-white"><span class="counter"><?php print $total_appl_boilers;?></span></h4>
                        </div>
                    </div>
                    <p class="text-white"><i class="fa fa-box-open"></i> Total Application </p>
                </div>
            </div></a>
        </div>
        <div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 mb-4">
            <div class="card card-statistics factories-box dashboard-count-box">
                <div class="card-body">
                    <div class="clearfix">
                        <div class="float-left">
                            <h4 class="text-white">
                            <i class="fa fa-signal highlight-icon"></i>
                          </h4>
                        </div>
                        <div class="float-left">
                            <p class="card-text text-white">Directorate of Factories</p>
                            <h4 class="bold-text text-white"><span class="counter"><?php print $total_factory;?></span></h4>
                        </div>
                    </div>
                    <p class="text-white"><i class="fa fa-box-open"></i> Total Application </p>
                </div>
            </div>
        </div>
        <div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 mb-4">
            <div class="card card-statistics shop-box dashboard-count-box">
                <div class="card-body">
                    <div class="clearfix">
                        <div class="float-left">
                            <h4 class="text-white">
                            <i class="fa fa-chart-bar highlight-icon"></i>
                          </h4>
                        </div>
                        <div class="float-left">
                            <p class="card-text text-white"> Shops & Establishment</p>
                            <h4 class="bold-text text-white"><span class="counter"><?php print $total_shops;?></span></h4>
                        </div>
                    </div>
                    <p class="text-white"><i class="fa fa-box-open"></i> Total Application </p>
                </div>
            </div>
        </div>
        <div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 mb-4">
            <div class="card card-statistics employment-box dashboard-count-box">
                <div class="card-body">
                    <div class="clearfix">
                        <div class="float-left">
                            <h4 class="text-white">
                            <i class="fa fa-chart-bar highlight-icon"></i>
                          </h4>
                        </div>
                        <div class="float-left">
                            <p class="card-text text-white">Directorate of Employment</p>
                            <h4 class="bold-text text-white"><span class="counter">000</span></h4>
                        </div>
                    </div>
                    <p class="text-white"><i class="fa fa-box-open"></i> Total Application </p>
                </div>
            </div>
        </div>
        <div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 mb-4">
            <div class="card card-statistics courts-box dashboard-count-box">
                <div class="card-body">
                    <div class="clearfix">
                        <div class="float-left">
                            <h4 class="text-white">
                            <i class="fa fa-chart-area highlight-icon"></i>
                          </h4>
                        </div>
                        <div class="float-left">
                            <p class="card-text text-white">Industrial Tribunals & </br>Labour Courts</p>
                            <h4 class="bold-text text-white"><span class="counter"><?php print $total_court;?></span></h4>
                        </div>
                    </div>
                    <p class="text-white"><i class="fa fa-box-open"></i> Total Application </p>
                </div>
            </div>
        </div>
        <div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 mb-4">
            <div class="card card-statistics institute-box dashboard-count-box">
                <div class="card-body">
                    <div class="clearfix">
                        <div class="float-left">
                            <h4 class="text-white">
                            <i class="fa fa-chart-pie highlight-icon"></i>
                          </h4>
                        </div>
                        <div class="float-left">
                            <p class="card-text text-white"> State Labour Institute</p>
                            <h4 class="bold-text text-white"><span class="counter">000</span></h4>
                        </div>
                    </div>
                    <p class="text-white"><i class="fa fa-box-open"></i> Total Application </p>
                </div>
            </div>
        </div>
        <div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 mb-4">
            <div class="card card-statistics ESI-box dashboard-count-box">
                <div class="card-body">
                    <div class="clearfix">
                        <div class="float-left">
                            <h4 class="text-white">
                            <i class="fa fa-signal highlight-icon"></i>
                          </h4>
                        </div>
                        <div class="float-left">
                            <p class="card-text text-white"> ESI (MB) SCHEME</p>
                            <h4 class="bold-text text-white"><span class="counter">000</span></h4>
                        </div>
                    </div>
                    <p class="text-white"><i class="fa fa-box-open"></i> Total Application </p>
                </div>
            </div>
        </div>
		
		</div>
    


<script src="https://code.jquery.com/jquery-1.12.4.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/waypoints/4.0.1/jquery.waypoints.min.js"></script>
<script src="build/js/jquery.countup.js"></script>
<script>
$('.counter').countUp();
</script>
	