/*
Template Name: Effacy - Creative One Page Template
Author: ThemeBite
Author URI: http://themebite.com/
Version: 1.0
Developed and Designed By: ThemeBite
*/
/*
====================================
[ JS TABLE OF CONTENT ]
------------------------------------
    1.0 - Parallax Effect
    2.0 - PreLoader
    3.0 - Sticky Menu
    4.0 - Text-Rotator
    5.0 - jQuery Smooth Scroll
    6.0 - Responsive Menu
    7.0 - Scroll Spy
    8.0 - Testimonial Carousel
    9.0 - Partners Carousel
    10  - Blog Post Carousel
    11  - Photo Gallery
    12  - jQuery Light Box 
    13  - Counter Section 
    14  - Goolge Map 
-------------------------------------
[ END JS TABLE OF CONTENT ]
=====================================
*/
$(window).load(function() {


   

    // Partners Carousel 
    $("#partners-carousel").owlCarousel({
        // Partners Carousel Settings
        navigation: false,
        pagination: false,
        autoPlay: 3000, //Set AutoPlay to 3 seconds
        items: 5,
        itemsDesktop: [1199, 3],
        itemsDesktopSmall: [979, 3],
        stopOnHover: true,
    });



  

    // Portfolio Gallery

    if ($('#grid').length > 0) {
        // Initialize plugin
        var $grid = $('#grid');
        $(window).load(function() {
            $grid.shuffle({
                itemSelector: '.thumbnails' // The Child Item of the parent #grid
            });
        });

        // Re-Shuffle the gallery
        $('#filter li').on('click', function(e) {
            e.preventDefault();

            // Active class on li
            $('#filter li').removeClass('active');
            $(this).addClass('active');

            // Filter item
            var groupName = $(this).attr('data-group');

            // Reshuffle item
            $grid.shuffle('shuffle', groupName);
        });
    }

    // Simple Light Box
    var gallery = $('.thumbnails a').simpleLightbox({
        navText: ['<i class="fa fa-angle-left"></i>', '<i class="fa fa-angle-right"></i>'],
        closeText: '<i class="fa fa-times"></i>',
    });

    // Counter JS
    $('.our-awards-section').on('inview', function(event, visible, visiblePartX, visiblePartY) {
        if (visible) {
            $(this).find('.timer').each(function() {
                var $this = $(this);
                $({
                    Counter: 0
                }).animate({
                    Counter: $this.text()
                }, {
                    duration: 3000,
                    easing: 'swing',
                    step: function() {
                        $this.text(Math.ceil(this.Counter));
                    }
                });
            });
            $(this).off('inview');
        }
    });

      });