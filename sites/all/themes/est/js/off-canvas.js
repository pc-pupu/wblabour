(function($) {
  'use strict';
  $(document).on('mouseenter mouseleave', '.sidebar .nav-item', function (ev) {
      var body = $('body');
      var sidebarIconOnly = body.hasClass("sidebar-icon-only");
      if(!('ontouchstart' in document.documentElement)) {
        if(sidebarIconOnly) {
          var $menuItem = $(this),
          $menuTitle = $('.menu-title', $menuItem),
          $submenuWrapper = $('> .collapse', $menuItem);
          if(ev.type === 'mouseenter') {
            $menuTitle.addClass('show');
            $submenuWrapper.addClass('show');
          }
          else {
            $menuTitle.removeClass('show');
            $submenuWrapper.removeClass('show');
          }
        }
      }

  });
})(jQuery);


(function($) {
  'use strict';
  $(function() {
    $('[data-toggle="offcanvas"]').on("click", function () {
      $('.row-offcanvas').toggleClass('active')
    });
  });
})(jQuery);



(function($) {
  'use strict';
  $(function() {
    // $('#sidebar .nav').perfectScrollbar();
    $('.container-scroller').perfectScrollbar( {suppressScrollX: true});
    $('[data-toggle="minimize"]').on("click", function () {
      $('body').toggleClass('sidebar-icon-only');
    });
  });

  $(".form-check label,.form-radio label").append('<i class="input-helper"></i>');
})(jQuery);


$(function() {
	var $a = $(".tabs li");
	$a.click(function() {
		$a.removeClass("active");
		$(this).addClass("active");
	});
});

function toggleIcon(e) {
    $(e.target)
        .prev('.panel-heading')
        .find(".more-less")
        .toggleClass('fa-plus fa-minus');
}
$('.panel-group').on('hidden.bs.collapse', toggleIcon);
$('.panel-group').on('shown.bs.collapse', toggleIcon);
