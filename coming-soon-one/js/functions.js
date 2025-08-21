
/* Background Images
-------------------------------------------------------------------*/
var  pageTopImage = jQuery('#page-top').data('background-image');
var  aboutImage = jQuery('#about').data('background-image');
var  subscribeImage = jQuery('#subscribe').data('background-image');
var  contactImage = jQuery('#contact').data('background-image');

if (pageTopImage) {  jQuery('#page-top').css({ 'background-image':'url(' + pageTopImage + ')' }); };
if (aboutImage) {  jQuery('#about').css({ 'background-image':'url(' + aboutImage + ')' }); };
if (subscribeImage) {  jQuery('#subscribe').css({ 'background-image':'url(' + subscribeImage + ')' }); };
if (contactImage) {  jQuery('#contact').css({ 'background-image':'url(' + contactImage + ')' }); };

/* Background Images End
-------------------------------------------------------------------*/



/* Document Ready function
-------------------------------------------------------------------*/
jQuery(document).ready(function($) {
	"use strict";


    /* Window Height Resize
    -------------------------------------------------------------------*/
    var windowheight = jQuery(window).height();
    if(windowheight > 650)
    {
         $('.pattern').removeClass('height-resize');
    }
    /* Window Height Resize End
    -------------------------------------------------------------------*/


    
	/* Main Menu   
	-------------------------------------------------------------------*/
	$('#main-menu #headernavigation').onePageNav({
		currentClass: 'active',
		changeHash: false,
		scrollSpeed: 750,
		scrollThreshold: 0.5,
		scrollOffset: 0,
		filter: '',
		easing: 'swing'
	});  

	/* Main Menu End  
	-------------------------------------------------------------------*/




	/* Time Countdown 
	-------------------------------------------------------------------*/
	/*$('#time_countdown').countDown({
        
        // targetDate: {
        //     'day': 30,
        //     'month': 9,
        //     'year': 2015,
        //     'hour': 0,
        //     'min': 0,
        //     'sec': 0
        // },
        // omitWeeks: true

         targetOffset: {
            'day':      10,
            'month':    0,
            'year':     0,
            'hour':     23,
            'min':      59,
            'sec':      3
		},
		omitWeeks: true
		

	    });*/
	   
	  
	


	/* Next Section   
	-------------------------------------------------------------------*/
	$('.next-section .go-to-about').click(function() {
    	$('html,body').animate({scrollTop:$('#about').offset().top}, 1000);
  	});
  	$('.next-section .go-to-subscribe').click(function() {
    	$('html,body').animate({scrollTop:$('#subscribe').offset().top}, 1000);
  	});
  	$('.next-section .go-to-contact').click(function() {
    	$('html,body').animate({scrollTop:$('#contact').offset().top}, 1000);
  	});
  	$('.next-section .go-to-page-top').click(function() {
    	$('html,body').animate({scrollTop:$('#page-top').offset().top}, 1000);
  	});

  	/* Next Section End
	-------------------------------------------------------------------*/




  /* Subscribe
  -------------------------------------------------------------------*/
    $(".news-letter").ajaxChimp({
        callback: mailchimpResponse,
        url: "http://jeweltheme.us10.list-manage.com/subscribe/post?u=a3e1b6603a9caac983abe3892&amp;id=257cf1a459" // Replace your mailchimp post url inside double quote "".  
    });

    function mailchimpResponse(resp) {
         if(resp.result === 'success') {
         
            $('.alert-success').html(resp.msg).fadeIn().delay(3000).fadeOut();
            
        } else if(resp.result === 'error') {
            $('.alert-warning').html(resp.msg).fadeIn().delay(3000).fadeOut();
        }  
    };




	/* Subscribe End
	-------------------------------------------------------------------*/




	/* Contact
	-------------------------------------------------------------------*/
    // Email from Validation
  $('#contact-submit').click(function(e){ 

    //Stop form submission & check the validation
    e.preventDefault();


    $('.first-name-error, .last-name-error, .contact-email-error, .contact-subject-error, .contact-message-error').hide();

    // Variable declaration
    var error = false;
    var k_first_name = $('#first_name').val();
    var k_last_name = $('#last_name').val();
    var k_email = $('#contact_email').val(); 
    var k_subject = $('#subject').val(); 
    var k_message = $('#message').val();

    // Form field validation
    if(k_first_name.length == 0){
      var error = true; 
      $('.first-name-error').html('<i class="fa fa-exclamation"></i> First name is required.').fadeIn();
    }  

    if(k_last_name.length == 0){
      var error = true;
      $('.last-name-error').html('<i class="fa fa-exclamation"></i> Last name is required.').fadeIn();
    }  

    if(k_email.length != 0 && validateEmail(k_email)){
       
    } else {
      var error = true; 
      $('.contact-email-error').html('<i class="fa fa-exclamation"></i> Please enter a valid email address.').fadeIn();
    }

    if(k_subject.length == 0){
      var error = true;
     $('.contact-subject-error').html('<i class="fa fa-exclamation"></i> Subject is required.').fadeIn();
    } 

    if(k_message.length == 0){
      var error = true;
      $('.contact-message-error').html('<i class="fa fa-exclamation"></i> Please provide a message.').fadeIn();
    }  

    // If there is no validation error, next to process the mail function
    if(error == false){

        $('#contact-submit').hide();
        $('#contact-loading').fadeIn();
        $('.contact-error-field').fadeOut();


      // Disable submit button just after the form processed 1st time successfully.
      $('#contact-submit').attr({'disabled' : 'true', 'value' : 'Sending' });

      /* Post Ajax function of jQuery to get all the data from the submission of the form as soon as the form sends the values to email.php*/
      $.post("php/contact.php", $("#contact-form").serialize(),function(result){
        //Check the result set from email.php file.
        if(result == 'sent'){



          //If the email is sent successfully, remove the submit button
          $('#first_name').remove();
          $('#last_name').remove(); 
          $('#contact_email').remove();
          $('#subject').remove(); 
          $('#message').remove();
          $('#contact-submit').remove(); 

          $('.contact-box-hide').slideUp();
          $('.contact-message').html('<i class="fa fa-check contact-success"></i><div>Your message has been sent.</div>').fadeIn();
        } else {
          $('.btn-contact-container').hide();
          $('.contact-message').html('<i class="fa fa-exclamation contact-error"></i><div>Something went wrong, please try again later.</div>').fadeIn();
            
        }
      });
    }
  });  
 
         
  function validateEmail(sEmail) {
    var filter = /^([\w-\.]+)@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.)|(([\w-]+\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\]?)$/;
    if (filter.test(sEmail)) {
      return true;
    } else {
      return false;
    }
  } 
 

	/* Contact End
	-------------------------------------------------------------------*/


    

    



});

/* Document Ready function End
-------------------------------------------------------------------*/


/* Preloder 
-------------------------------------------------------------------*/
$(window).load(function () {    
    "use strict";
    $("#loader").fadeOut();
    $("#preloader").delay(350).fadeOut("slow");
});
 /* Preloder End
-------------------------------------------------------------------*/


(function (e) {
		  e.fn.countdown = function (t, n) {
		  function i() {
			eventDate = Date.parse(r.date) / 1e3;
			currentDate = Math.floor(e.now() / 1e3);
			if (eventDate <= currentDate) {
			  n.call(this);
			  clearInterval(interval)
			}
			seconds = eventDate - currentDate;
			days = Math.floor(seconds / 86400);
			seconds -= days * 60 * 60 * 24;
			hours = Math.floor(seconds / 3600);
			seconds -= hours * 60 * 60;
			minutes = Math.floor(seconds / 60);
			seconds -= minutes * 60;
			days == 1 ? thisEl.find(".timeRefDays").text("day") : thisEl.find(".timeRefDays").text("days");
			hours == 1 ? thisEl.find(".timeRefHours").text("hour") : thisEl.find(".timeRefHours").text("hours");
			minutes == 1 ? thisEl.find(".timeRefMinutes").text("minute") : thisEl.find(".timeRefMinutes").text("minutes");
			seconds == 1 ? thisEl.find(".timeRefSeconds").text("second") : thisEl.find(".timeRefSeconds").text("seconds");
			if (r["format"] == "on") {
			  days = String(days).length >= 2 ? days : "0" + days;
			  hours = String(hours).length >= 2 ? hours : "0" + hours;
			  minutes = String(minutes).length >= 2 ? minutes : "0" + minutes;
			  seconds = String(seconds).length >= 2 ? seconds : "0" + seconds
			}
			if (!isNaN(eventDate)) {
			  thisEl.find(".days").text(days);
			  thisEl.find(".hours").text(hours);
			  thisEl.find(".minutes").text(minutes);
			  thisEl.find(".seconds").text(seconds)
			} else {
			  //alert("Invalid date. Example: 30 Tuesday 2013 15:50:00");
			  clearInterval(interval)
			}
		  }
		  var thisEl = e(this);
		  var r = {
			date: null,
			format: null
		  };
		  t && e.extend(r, t);
		  i();
		  interval = setInterval(i, 1e3)
		  }
		  })(jQuery);
		  $(document).ready(function () {
		  function e() {
			var e = new Date;
			e.setDate(e.getDate() + 60);
			dd = e.getDate();
			mm = e.getMonth() + 1;
			y = e.getFullYear();
			futureFormattedDate = mm + "/" + dd + "/" + y;
			return futureFormattedDate
		  }
		  $("#countdown").countdown({
			date: "19 September 2017 15:00:00", // Change this to your desired date to countdown to
			format: "on"
		  });
		});
   
