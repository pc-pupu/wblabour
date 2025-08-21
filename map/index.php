<html>
  <style>
      /* Always set the map height explicitly to define the size of the div
       * element that contains the map. */
      #map-canvas {
        height: 99%;  
        width: 99%;
      }
      /* Optional: Makes the sample page fill the window. */
      html, body {
        /*height: 100%;*/
        margin: 0;
        padding: 0;
      }
      .delete-menu {
        position: absolute;
        background: white;
        padding: 3px;
        color: #666;
        font-weight: bold;
        border: 1px solid #999;
        font-family: sans-serif;
        font-size: 12px;
        box-shadow: 1px 3px 3px rgba(0, 0, 0, .3);
        margin-top: -10px;
        margin-left: 10px;
        cursor: pointer;
      }
      .delete-menu:hover {
        background: #eee;
      }
    </style>
<script src="js/jquery.min.js" type="text/javascript"></script>
<!--<script type="text/javascript" src="https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false"></script>-->
<script type="text/javascript" src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCCnw26n7vQGH5fOxppwFhUjao6OD2JZdc"></script>
<script src="js/mapUtility.js" type="text/javascript"></script>
    <script type="text/javascript">
        //var bermudaTriangle;
		//var markers = [];
		var map;
        function initialize() {
            var myLatLng = new google.maps.LatLng(22.5765, 88.4796);
            var mapOptions = {
                zoom: 16,
                center: myLatLng,
                mapTypeId: google.maps.MapTypeId.RoadMap
            };

            map = new google.maps.Map(document.getElementById('map-canvas'),
            mapOptions);
			
			// add marker
			/*var vMarker = new google.maps.Marker({
				position: new google.maps.LatLng(22.5765, 88.4796),
				title: "Click for more information",
				draggable: true
			});*/
			
			/*google.maps.event.addListener(map, 'click', function(e) {
			  placeMarkerAndPanTo(e.latLng, map);
			});*/
			
			google.maps.event.addDomListener(document.getElementById('addmarker'), 'click', addMarkers);
			

			
			/*google.maps.event.addListener(vMarker, 'dragend', function (evt) {
				$("#txtLat").val(evt.latLng.lat().toFixed(6));
				$("#txtLng").val(evt.latLng.lng().toFixed(6));
		
				map.panTo(evt.latLng);
			});*/

			//map.setCenter(vMarker.position);
			
			
			
			//polygon
			
			var flightPlanCoordinates = [
				new google.maps.LatLng(22.579280, 88.472745),
				new google.maps.LatLng(22.579835, 88.469376)
			];
			flightPath = new google.maps.Polyline({
			  path: flightPlanCoordinates,
			  strokeColor: '#FF0000',
			  strokeOpacity: 1.0,
			  strokeWeight: 2,
			  editable: true,
			  draggable: true
			});
			
			 var deleteMenu = new DeleteMenu();

			google.maps.event.addListener(flightPath, 'rightclick', function(e) {
			  // Check if click was on a vertex control point
			  if (e.vertex == undefined) {
				return;
			  }
			  deleteMenu.open(map, flightPath.getPath(), e.vertex);
			});
			
            /*var triangleCoords = [
            new google.maps.LatLng(28.525416, 79.870605),
            new google.maps.LatLng(27.190518, 77.530518),
            new google.maps.LatLng(29.013807, 77.67334)

        ];*/
            // Construct the polygon 
            /*bermudaTriangle = new google.maps.Polygon({
                paths: triangleCoords,
                draggable: true,
                editable: true,
                strokeColor: '#FF0000',
                strokeOpacity: 0.8,
                strokeWeight: 2,
                fillColor: '#FF0000',
                fillOpacity: 0.35
            });

            bermudaTriangle.setMap(map);*/
			flightPath.setMap(map);
			//vMarker.setMap(map);
			
			//var NewMapCenter = map.getCenter();
			google.maps.event.addListener(flightPath, "dragend", getPath);
			google.maps.event.addListener(flightPath.getPath(), "insert_at", getPath);
			google.maps.event.addListener(flightPath.getPath(), "remove_at", getPath);
			google.maps.event.addListener(flightPath.getPath(), "set_at", getPath);
			
			
			/*google.maps.event.addListener(bermudaTriangle, "dragend", getPolygonCoords);
            google.maps.event.addListener(bermudaTriangle.getPath(), "insert_at", getPolygonCoords);
            google.maps.event.addListener(bermudaTriangle.getPath(), "remove_at", getPolygonCoords);
            google.maps.event.addListener(bermudaTriangle.getPath(), "set_at", getPolygonCoords);*/
			google.maps.event.addListener(map, 'zoom_changed', function() {
				//alert('hi'+map.getZoom());
				document.getElementById("#zoomMap").value = 'abcd';
			 });
			 
			 
			 var html = "<input type='text' id='pind' value='' onkeyup='saveData()'/>";
			 
			 var infowindow = new google.maps.InfoWindow({
				content: html
			});

			 
			/*google.maps.event.addListener(vMarker, 'click', function () {
				infowindow.open(map, vMarker);
			});*/
 
        }
		
		function addMarkers(){
			var IT = new google.maps.LatLng(22.5765, 88.4796);
			var marker = new google.maps.Marker({
				map: map,
				position: IT,
				draggable: true
			});
			
		}
		
		function placeMarkerAndPanTo(latLng, map) {
			var marker = new google.maps.Marker({
			  position: latLng,
			  map: map,
			  draggable: true
			});
			//map.panTo(latLng);
		  }
		
		function getPath() {
		   var path = flightPath.getPath();
		   var len = path.getLength();
		   var coordStr = "";
		   for (var i=0; i<len; i++) {
			 coordStr += path.getAt(i).toUrlValue(6)+"<br>";
		   }
		   document.getElementById('info').innerHTML = coordStr;
		}

        /*function getPolygonCoords() {
            var len = bermudaTriangle.getPath().getLength();
            var htmlStr = "";
            for (var i = 0; i < len; i++) {
                htmlStr += bermudaTriangle.getPath().getAt(i).toUrlValue(5) + "<br>";
            }
            document.getElementById('info').innerHTML = htmlStr;
        }  */
		
		
		function saveData(){
			var x = document.getElementById("pind").value;
			//alert(x);
    		document.getElementById("pintxt").value = x;
		}
		
		
		
		
		
		function DeleteMenu() {
        this.div_ = document.createElement('div');
        this.div_.className = 'delete-menu';
        this.div_.innerHTML = 'Delete';

        var menu = this;
        google.maps.event.addDomListener(this.div_, 'click', function() {
          menu.removeVertex();
        });
      }
      DeleteMenu.prototype = new google.maps.OverlayView();

      DeleteMenu.prototype.onAdd = function() {
        var deleteMenu = this;
        var map = this.getMap();
        this.getPanes().floatPane.appendChild(this.div_);

        // mousedown anywhere on the map except on the menu div will close the
        // menu.
        this.divListener_ = google.maps.event.addDomListener(map.getDiv(), 'mousedown', function(e) {
          if (e.target != deleteMenu.div_) {
            deleteMenu.close();
          }
        }, true);
      };

      DeleteMenu.prototype.onRemove = function() {
        google.maps.event.removeListener(this.divListener_);
        this.div_.parentNode.removeChild(this.div_);

        // clean up
        this.set('position');
        this.set('path');
        this.set('vertex');
      };

      DeleteMenu.prototype.close = function() {
        this.setMap(null);
      };

      DeleteMenu.prototype.draw = function() {
        var position = this.get('position');
        var projection = this.getProjection();

        if (!position || !projection) {
          return;
        }

        var point = projection.fromLatLngToDivPixel(position);
        this.div_.style.top = point.y + 'px';
        this.div_.style.left = point.x + 'px';
      };

      /**
       * Opens the menu at a vertex of a given path.
       */
      DeleteMenu.prototype.open = function(map, path, vertex) {
        this.set('position', path.getAt(vertex));
        this.set('path', path);
        this.set('vertex', vertex);
        this.setMap(map);
        this.draw();
      };

      /**
       * Deletes the vertex from the path.
       */
      DeleteMenu.prototype.removeVertex = function() {
        var path = this.get('path');
        var vertex = this.get('vertex');

        if (!path || vertex == undefined) {
          this.close();
          return;
        }

        path.removeAt(vertex);
        this.close();
      };
	  
	  function addMRKAR(){
		  //alert('hi'+IT);
		 
		  placeMarkerAndPanTo(IT);
	  }
    </script>
</head>

<body onLoad="initialize()">
    <div id="map-canvas" style="height: 350px; width: auto;">
    </div>
    <div id="info" style="position: absolute; font-family: Arial; font-size: 14px;">
    </div>
    <input id="txtLat" type="text" value="28.47399" /><br />
    <input id="txtLng" type="text" value="77.026489" />
    <input id="zoomMap" type="text" name="zoomMap" value="15" />
    <input type="text" id="pintxt" name="pintxt" value="">
    <input type="button" id="addmarker" name="addmarker" value="Add Markar">
</body>
</html>