<?php global  $base_root,$base_path,$base_url ;?>
<style>
    .graphbrdr tbody{
		border:none;
	}
	.myprofilepic{
		/*width: 100px;*/
    	margin-top: 0px !important;
    	/*margin-left: 93px !important;*/
	}
	/*.profile_details .bottom{
		display:none;
	}*/
    </style>

    <!-- Bootstrap -->
    <!--<link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap/dist/css/bootstrap.min.css" rel="stylesheet">-->
    <!-- Font Awesome -->
    <link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/font-awesome/css/font-awesome.min.css" rel="stylesheet">
    <link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/font-awesome/css/font-awesome.css" rel="stylesheet">
    <!-- NProgress -->
    <link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/nprogress/nprogress.css" rel="stylesheet">
    <!-- iCheck -->
    <link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/iCheck/skins/flat/green.css" rel="stylesheet">
	
    <!-- bootstrap-progressbar -->
    <link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-progressbar/css/bootstrap-progressbar-3.3.4.min.css" rel="stylesheet">
    <!-- JQVMap -->
    <link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jqvmap/dist/jqvmap.min.css" rel="stylesheet"/>
    <!-- bootstrap-daterangepicker -->
    <link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-daterangepicker/daterangepicker.css" rel="stylesheet">

    <!-- Custom Theme Style -->
    <link href="<?php print $base_path ?>sites/all/modules/dashboard/build/css/custom.css" rel="stylesheet">

   <div class="right_col" role="main">
          
          
          <div class="row">
          
          <div class="col-md-8 col-sm-8 col-xs-12">
              <div class="x_panel">
                <div class="x_title">
                  <h2>Daily active users <small>Sessions</small></h2>
                  <ul class="nav navbar-right panel_toolbox">
                    <li><a class="collapse-link"><i class="fa fa-chevron-up"></i></a>
                    </li>
                    <li class="dropdown">
                      <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><i class="fa fa-wrench"></i></a>
                      <ul class="dropdown-menu" role="menu">
                        <li><a href="#">Settings 1</a>
                        </li>
                        <li><a href="#">Settings 2</a>
                        </li>
                      </ul>
                    </li>
                    <li><a class="close-link"><i class="fa fa-close"></i></a>
                    </li>
                  </ul>
                  <div class="clearfix"></div>
                </div>
                <div class="x_content">
                  <ul class="list-unstyled timeline">
                    <li>
                      <div class="block">
                        <div class="tags">
                          <img src="<?php print $base_path ?>sites/all/modules/dashboard/images/user.png" alt="" class="img-circle img-responsive myprofilepic">
                        </div>
                        
                        <div class="block_content">
                          <table class="data table table-striped no-margin">
                              <thead>
                                <tr><th><i class="fa fa-birthday-cake"></i> DOB : 15-06-1981</li></th></tr>
                                <tr><th><i class="fa fa-envelope"></i> Email : test@gmail.com</th></tr>
                                <tr><th><i class="fa fa-phone"></i> Phone : 9874563210</th></tr>
                                <tr><th class="hidden-phone"><i class="fa fa-map-marker"></i> Pin : 700001</th></tr>
                                <tr><th><i class="fa fa-building"></i> Address: 1 Kiran Sankar Roy Road, New Seceratery Building, Kolkata</th></tr>
                              </thead>
                             
                            </table>
                        </div>
                      </div>
                    </li>
                    
                    
                  </ul>

                </div>
              </div>
            </div>
          
          
          
          
          <div class="col-md-4 col-sm-4 col-xs-12">
              <div class="x_panel tile fixed_height_320 overflow_hidden">
                <div class="x_title">
                  <h2>Service Graph</h2>
                  <ul class="nav navbar-right panel_toolbox">
                    <li><a class="collapse-link"><i class="fa fa-chevron-up"></i></a>
                    </li>
                    <li class="dropdown">
                      <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><i class="fa fa-wrench"></i></a>
                      <ul class="dropdown-menu" role="menu">
                        <li><a href="#">Settings 1</a>
                        </li>
                        <li><a href="#">Settings 2</a>
                        </li>
                      </ul>
                    </li>
                    <li><a class="close-link"><i class="fa fa-close"></i></a>
                    </li>
                  </ul>
                  <div class="clearfix"></div>
                </div>
                <div class="x_content graphbrdr">
                  <table class="" style="width:100%">
                    
                    <tr>
                      <td>
                        <canvas class="canvasDoughnut" height="140" width="140" style="margin: 15px 10px 10px 0"></canvas>
                      </td>
                      <td>
                        <table class="tile_info">
                          <tr>
                            <td>
                              <p><i class="fa fa-square blue"></i>CLRA </p>
                            </td>
                            <td>30%</td>
                          </tr>
                          <tr>
                          	<td>
                              <p><i class="fa fa-square red"></i>BOCWA </p>
                            </td>
                            <td>25%</td>
                            <!--<td>
                              <p><i class="fa fa-square green"></i>Android </p>
                            </td>
                            <td>10%</td>-->
                          </tr>
                          <tr>
                            <td>
                              <p><i class="fa fa-square purple"></i>ISMW </p>
                            </td>
                            <td>20%</td>
                          </tr>
                          <tr>
                            <td>
                              <p><i class="fa fa-square aero"></i>MTW </p>
                            </td>
                            <td>15%</td>
                          </tr>
                          <tr>
                            <td>
                              <p><i class="fa fa-square green-new"></i>INFORMATION </p>
                            </td>
                            <td>10%</td>
                          </tr>
                        </table>
                      </td>
                    </tr>
                  </table>
                </div>
              </div>
            </div>
          </div>
          
          <br />

          <div class="row">
            <div class="col-md-12 col-sm-12 col-xs-12">
                <div class="x_panel">
                  <div class="x_title">
                    <h2>Table design</h2>
                    <ul class="nav navbar-right panel_toolbox">
                      <li><a class="collapse-link"><i class="fa fa-chevron-up"></i></a>
                      </li>
                      <li class="dropdown">
                        <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><i class="fa fa-wrench"></i></a>
                        <ul class="dropdown-menu" role="menu">
                          <li><a href="#">Settings 1</a>
                          </li>
                          <li><a href="#">Settings 2</a>
                          </li>
                        </ul>
                      </li>
                      <li><a class="close-link"><i class="fa fa-close"></i></a>
                      </li>
                    </ul>
                    <div class="clearfix"></div>
                  </div>

                  <div class="x_content">


                    <div class="table-responsive">
                      <table class="table table-striped jambo_table bulk_action">
                        <thead>
                          <tr class="headings">
                            <th class="column-title">Directorate </th>
                            <th class="column-title">Service ID </th>
                            <th class="column-title">Service Name </th>
                            <th class="column-title">Status </th>
                            <th class="column-title">TimeLine </th>
                            <th class="column-title">Checklist </th>
                            <th class="column-title">Sop </th>
                            <th class="column-title no-link last"><span class="nobr">Link</span></th>
                          </tr>
                        </thead>

                        <tbody>
                          <tr class="even pointer">
                            <td class=" ">Boiler Directorate
                            <td class=" ">2541874</td>
                            <td class=" ">CLERA</td>
                            <td class=" "><button type="button" class="btn btn-primary">Applied</button></td>
                            <td class=" ">24 days</td>
                            <td class=" last"><a href="#">View</a></td>
                            <td class=" last"><a href="#">View</a></td>
                            <td class=" last"><a href="#">View</a></td>
                          </tr>
                          <tr class="odd pointer">
                            <td class=" ">Labour Comissionarate
                            <td class=" ">2541874</td>
                            <td class=" ">CLERA</td>
                            <td class=" "><button type="button" class="btn btn-warning">Warning</button></td>
                            <td class=" ">24 days</td>
                            <td class=" last"><a href="#">View</a></td>
                            <td class=" last"><a href="#">View</a></td>
                            <td class=" last"><a href="#">View</a></td>
                          </tr>
                          
                          <tr class="odd pointer">
                            <td class=" ">Factory
                            <td class=" ">2541874</td>
                            <td class=" ">CLERA</td>
                            <td class=" "><button type="button" class="btn btn-success">Success</button></td>
                            <td class=" ">24 days</td>
                            <td class=" last"><a href="#">View</a></td>
                            <td class=" last"><a href="#">View</a></td>
                            <td class=" last"><a href="#">View</a></td>
                          </tr>
                        </tbody>
                      </table>
                    </div>
							
						
                  </div>
                </div>
              </div>

          </div>
          <br />

          <div class="row">


            <div class="col-md-4 col-sm-4 col-xs-12">
              <div class="x_panel tile fixed_height_320">
                <div class="x_title">
                  <h2>App Versions</h2>
                  <ul class="nav navbar-right panel_toolbox">
                    <li><a class="collapse-link"><i class="fa fa-chevron-up"></i></a>
                    </li>
                    <li class="dropdown">
                      <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><i class="fa fa-wrench"></i></a>
                      <ul class="dropdown-menu" role="menu">
                        <li><a href="#">Settings 1</a>
                        </li>
                        <li><a href="#">Settings 2</a>
                        </li>
                      </ul>
                    </li>
                    <li><a class="close-link"><i class="fa fa-close"></i></a>
                    </li>
                  </ul>
                  <div class="clearfix"></div>
                </div>
                <div class="x_content">
                  <h4>App Usage across versions</h4>
                  <div class="widget_summary">
                    <div class="w_left w_25">
                      <span>0.1.5.2</span>
                    </div>
                    <div class="w_center w_55">
                      <div class="progress">
                        <div class="progress-bar bg-green" role="progressbar" aria-valuenow="60" aria-valuemin="0" aria-valuemax="100" style="width: 66%;">
                          <span class="sr-only">60% Complete</span>
                        </div>
                      </div>
                    </div>
                    <div class="w_right w_20">
                      <span>123k</span>
                    </div>
                    <div class="clearfix"></div>
                  </div>

                  <div class="widget_summary">
                    <div class="w_left w_25">
                      <span>0.1.5.3</span>
                    </div>
                    <div class="w_center w_55">
                      <div class="progress">
                        <div class="progress-bar bg-green" role="progressbar" aria-valuenow="60" aria-valuemin="0" aria-valuemax="100" style="width: 45%;">
                          <span class="sr-only">60% Complete</span>
                        </div>
                      </div>
                    </div>
                    <div class="w_right w_20">
                      <span>53k</span>
                    </div>
                    <div class="clearfix"></div>
                  </div>
                  <div class="widget_summary">
                    <div class="w_left w_25">
                      <span>0.1.5.4</span>
                    </div>
                    <div class="w_center w_55">
                      <div class="progress">
                        <div class="progress-bar bg-green" role="progressbar" aria-valuenow="60" aria-valuemin="0" aria-valuemax="100" style="width: 25%;">
                          <span class="sr-only">60% Complete</span>
                        </div>
                      </div>
                    </div>
                    <div class="w_right w_20">
                      <span>23k</span>
                    </div>
                    <div class="clearfix"></div>
                  </div>
                  <div class="widget_summary">
                    <div class="w_left w_25">
                      <span>0.1.5.5</span>
                    </div>
                    <div class="w_center w_55">
                      <div class="progress">
                        <div class="progress-bar bg-green" role="progressbar" aria-valuenow="60" aria-valuemin="0" aria-valuemax="100" style="width: 5%;">
                          <span class="sr-only">60% Complete</span>
                        </div>
                      </div>
                    </div>
                    <div class="w_right w_20">
                      <span>3k</span>
                    </div>
                    <div class="clearfix"></div>
                  </div>
                  <div class="widget_summary">
                    <div class="w_left w_25">
                      <span>0.1.5.6</span>
                    </div>
                    <div class="w_center w_55">
                      <div class="progress">
                        <div class="progress-bar bg-green" role="progressbar" aria-valuenow="60" aria-valuemin="0" aria-valuemax="100" style="width: 2%;">
                          <span class="sr-only">60% Complete</span>
                        </div>
                      </div>
                    </div>
                    <div class="w_right w_20">
                      <span>1k</span>
                    </div>
                    <div class="clearfix"></div>
                  </div>

                </div>
              </div>
            </div>

            <div class="col-md-4 col-sm-4 col-xs-12">
              <div class="x_panel tile fixed_height_320 overflow_hidden">
                <div class="x_title">
                  <h2>Device Usage</h2>
                  <ul class="nav navbar-right panel_toolbox">
                    <li><a class="collapse-link"><i class="fa fa-chevron-up"></i></a>
                    </li>
                    <li class="dropdown">
                      <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><i class="fa fa-wrench"></i></a>
                      <ul class="dropdown-menu" role="menu">
                        <li><a href="#">Settings 1</a>
                        </li>
                        <li><a href="#">Settings 2</a>
                        </li>
                      </ul>
                    </li>
                    <li><a class="close-link"><i class="fa fa-close"></i></a>
                    </li>
                  </ul>
                  <div class="clearfix"></div>
                </div>
                <div class="x_content">
                  <table class="" style="width:100%">
                    <tr>
                      <th style="width:37%;">
                        <p>Top 5</p>
                      </th>
                      <th>
                        <div class="col-lg-7 col-md-7 col-sm-7 col-xs-7">
                          <p class="">Device</p>
                        </div>
                        <div class="col-lg-5 col-md-5 col-sm-5 col-xs-5">
                          <p class="">Progress</p>
                        </div>
                      </th>
                    </tr>
                    <tr>
                      <td>
                        <canvas class="canvasDoughnut" height="140" width="140" style="margin: 15px 10px 10px 0"></canvas>
                      </td>
                      <td>
                        <table class="tile_info">
                          <tr>
                            <td>
                              <p><i class="fa fa-square blue"></i>CLRA </p>
                            </td>
                            <td>30%</td>
                          </tr>
                          <tr>
                          	<td>
                              <p><i class="fa fa-square red"></i>BOCWA </p>
                            </td>
                            <td>25%</td>
                            <!--<td>
                              <p><i class="fa fa-square green"></i>Android </p>
                            </td>
                            <td>10%</td>-->
                          </tr>
                          <tr>
                            <td>
                              <p><i class="fa fa-square purple"></i>ISMW </p>
                            </td>
                            <td>20%</td>
                          </tr>
                          <tr>
                            <td>
                              <p><i class="fa fa-square aero"></i>MTW </p>
                            </td>
                            <td>15%</td>
                          </tr>
                          <tr>
                            <td>
                              <p><i class="fa fa-square green-new"></i>OTHER </p>
                            </td>
                            <td>10%</td>
                          </tr>
                        </table>
                      </td>
                    </tr>
                  </table>
                </div>
              </div>
            </div>


            <div class="col-md-4 col-sm-4 col-xs-12">
              <div class="x_panel tile fixed_height_320">
                <div class="x_title">
                  <h2>Quick Settings</h2>
                  <ul class="nav navbar-right panel_toolbox">
                    <li><a class="collapse-link"><i class="fa fa-chevron-up"></i></a>
                    </li>
                    <li class="dropdown">
                      <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><i class="fa fa-wrench"></i></a>
                      <ul class="dropdown-menu" role="menu">
                        <li><a href="#">Settings 1</a>
                        </li>
                        <li><a href="#">Settings 2</a>
                        </li>
                      </ul>
                    </li>
                    <li><a class="close-link"><i class="fa fa-close"></i></a>
                    </li>
                  </ul>
                  <div class="clearfix"></div>
                </div>
                <div class="x_content">
                  <div class="dashboard-widget-content">
                    <ul class="quick-list">
                      <li><i class="fa fa-calendar-o"></i><a href="#">Settings</a>
                      </li>
                      <li><i class="fa fa-bars"></i><a href="#">Subscription</a>
                      </li>
                      <li><i class="fa fa-bar-chart"></i><a href="#">Auto Renewal</a> </li>
                      <li><i class="fa fa-line-chart"></i><a href="#">Achievements</a>
                      </li>
                      <li><i class="fa fa-bar-chart"></i><a href="#">Auto Renewal</a> </li>
                      <li><i class="fa fa-line-chart"></i><a href="#">Achievements</a>
                      </li>
                      <li><i class="fa fa-area-chart"></i><a href="#">Logout</a>
                      </li>
                    </ul>

                    <div class="sidebar-widget">
                        <h4>Profile Completion</h4>
                        <canvas width="150" height="80" id="chart_gauge_01" class="" style="width: 160px; height: 100px;"></canvas>
                        <div class="goal-wrapper">
                          <span id="gauge-text" class="gauge-value pull-left">0</span>
                          <span class="gauge-value pull-left">%</span>
                          <span id="goal-text" class="goal-value pull-right">100%</span>
                        </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>

          </div>


          
        </div>

    <!-- jQuery -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jquery/dist/jquery.min.js"></script>
    <!-- Bootstrap -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap/dist/js/bootstrap.min.js"></script>
    <!-- FastClick -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/fastclick/lib/fastclick.js"></script>
    <!-- NProgress -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/nprogress/nprogress.js"></script>
    <!-- Chart.js -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Chart.js/dist/Chart.min.js"></script>
    <!-- gauge.js -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/gauge.js/dist/gauge.min.js"></script>
    <!-- bootstrap-progressbar -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-progressbar/bootstrap-progressbar.min.js"></script>
    <!-- iCheck -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/iCheck/icheck.min.js"></script>
    <!-- Skycons -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/skycons/skycons.js"></script>
    <!-- Flot -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.js"></script>
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.pie.js"></script>
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.time.js"></script>
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.stack.js"></script>
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.resize.js"></script>
    <!-- Flot plugins -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/flot.orderbars/js/jquery.flot.orderBars.js"></script>
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/flot-spline/js/jquery.flot.spline.min.js"></script>
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/flot.curvedlines/curvedLines.js"></script>
    <!-- DateJS -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/DateJS/build/date.js"></script>
    <!-- JQVMap -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jqvmap/dist/jquery.vmap.js"></script>
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jqvmap/dist/maps/jquery.vmap.world.js"></script>
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jqvmap/examples/js/jquery.vmap.sampledata.js"></script>
    <!-- bootstrap-daterangepicker -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/moment/min/moment.min.js"></script>
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-daterangepicker/daterangepicker.js"></script>

    <!-- Custom Theme Scripts -->
    <script src="<?php print $base_path ?>sites/all/modules/dashboard/build/js/custom.min.js"></script>
    

