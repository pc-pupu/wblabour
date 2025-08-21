 jQuery(document).ready(function($) {
            $(".main-tab").zozoTabs({
                position: "top-left",
                multiline: true,
                style: "contained",
                theme: "flat-nephritis",
                spaced: true,
                rounded: false,
                bordered: false,
                dark: true,
                animation: {
                    easing: "easeInOutExpo",
                    duration: 600,
                    effects: "slideH"
                }
            });

            /* jQuery activation and setting options for second tabs*/
            $(".sub-header").zozoTabs({
                position: "top-left",
                orientation: "vertical",
                multiline: true,
                style: "contained",
                theme: "flat-nephritis",
                spaced: true,
                rounded: false,
                dark: true,
                animation: {
                    easing: "easeInOutExpo",
                    duration: 450,
                    effects: "slideV"
                }
            });

            $(".nested-tabs").zozoTabs({
                position: "top-left",
                theme: "red",
                style: "underlined",
                rounded: false,
                shadows: false,
                defaultTab: "tab1",
                animation: {
                    easing: "easeInOutCirc",
                    effects: "slideV"
                },
                size: "medium"
            });
        });
    
        $(window).scroll(function() {
            if ($(this).scrollTop() > 1) {
                $('.header').addClass("sticky");
            } else {
                $('.header').removeClass("sticky");
            }
        });
   
        $(document).ready(function() {
            $('[data-toggle="tooltip"]').tooltip();

            $('.boxbgcolor1sub').each(function() {
                animationHover(this, 'bounce');
                animationClick(this, 'bounce');
            });

        });
    

    
        // Carousel Auto-Cycle
        $(document).ready(function() {
            $('.carousel').carousel({
                interval: 1000
            })

            $('.carousel1').carousel({
                interval: 3000
            })

            $('.toggle').click(function(event) {
                event.preventDefault();
                var target = $(this).attr('href');
                $(target).toggleClass('hidden show');
            });

        });

        $(function() {
            var Accordion = function(el, multiple) {
                this.el = el || {};
                this.multiple = multiple || false;

                // Variables privadas
                var links = this.el.find('.link');
                // Evento
                links.on('click', {
                    el: this.el,
                    multiple: this.multiple
                }, this.dropdown)
            }

            Accordion.prototype.dropdown = function(e) {
                var $el = e.data.el;
                $this = $(this),
                    $next = $this.next();

                $next.slideToggle();
                $this.parent().toggleClass('open');

                if (!e.data.multiple) {
                    $el.find('.submenu').not($next).slideUp().parent().removeClass('open');
                };
            }

            var accordion = new Accordion($('#accordion'), false);
            var accordion = new Accordion($('#accordion1'), true);
        });