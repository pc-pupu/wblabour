//$.noConflict();
jQuery(document).ready(function() {
	//jQuery('#menu').menu();
	var timer;
	
        jQuery('li.dropdown').on('mouseenter', function (event) {

			//alert('ok');
            event.stopImmediatePropagation();
            event.stopPropagation();

            jQuery(this).removeClass('open menu-animating').addClass('menu-animating');
            var that = this;


            if (timer) {
                clearTimeout(timer);
                timer = null;
            }


            timer = setTimeout(function () {

                jQuery(that).removeClass('menu-animating');
                jQuery(that).addClass('open');

            }, 300);   // 300ms as animation end time


        });

        // on mouse leave

        jQuery('li.dropdown').on('mouseleave', function (event) {

            var that = this;

            jQuery(this).removeClass('open menu-animating').addClass('menu-animating');


            if (timer) {
                clearTimeout(timer);
                timer = null;
            }

            timer = setTimeout(function () {

                jQuery(that).removeClass('menu-animating');
                jQuery(that).removeClass('open');

            }, 300);  // 300ms as animation end time

        });
	
});

var ie = jQuery.browser.msie && jQuery.browser.version < 8.0;
 
jQuery.fn.menu = function() {
	jQuery(this).find('li').each(function() {
		if (jQuery(this).find('> ul').size() > 0) {
			jQuery(this).addClass('has_child');
		}
	});

	var closeTimer = null;
	var menuItem = null;
	
	function cancelTimer() {
		if (closeTimer) {
			window.clearTimeout(closeTimer);
			closeTimer = null;
		}
	}
	
	function close() {
		jQuery(menuItem).find('> ul ul').hide();
		ie ? jQuery(menuItem).find('> ul').fadeOut() : jQuery(menuItem).find('> ul').slideUp(250);
		menuItem = null;
	}
	
	jQuery(this).find('li').hover(function() {
		cancelTimer();
		
		var parent = false;
		jQuery(this).parents('li').each(function() { 
			if (this == menuItem) parent = true;
		});
		if (menuItem != this && !parent) close();
		
		jQuery(this).addClass('hover');
		ie ? jQuery(this).find('> ul').fadeIn() : jQuery(this).find('> ul').slideDown(250);
	}, function() {
		jQuery(this).removeClass('hover');
		menuItem = this;
		cancelTimer();
		closeTimer = window.setTimeout(close, 500);
	});
	



	if (ie) {
		jQuery(this).find('ul a').css('display', 'inline-block');
		jQuery(this).find('ul ul').css('top', '0');
	}
}