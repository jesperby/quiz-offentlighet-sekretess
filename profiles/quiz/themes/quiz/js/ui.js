(function ($) {


  //
  // Debugger that shows view port size. Helps when making responsive designs.
  //
  function showViewPortSize(display) {
    if(display) {
      var height = jQuery(window).height();
      var width = jQuery(window).width();
      jQuery('body').prepend('<div id="viewportsize" style="z-index:9999;position:fixed;top:40px;left:5px;color:#fff;background:#000;padding:10px">Height: '+height+'<br>Width: '+width+'</div>');
      jQuery(window).resize(function() {
        height = jQuery(window).height();
        width = jQuery(window).width();
        jQuery('#viewportsize').html('Height: '+height+'<br>Width: '+width);
      });
    }
  }


  //
  // Debugger that shows view port size. Helps when making responsive designs.
  //
  function mobileMenuSetup() {
    var menu = $('.header .nav');
    if(menu.length) {
      menu.find('.display-mobile-menu').click(function(e){
        menu.find('> .menu').toggleClass('mobile-show');
        e.preventDefault();
      });
    }
  }


  //
  // Run on document ready
  //
  jQuery(document).ready(function() {
    showViewPortSize(false);
    mobileMenuSetup();
  });


  //
  // Run on document ready and every time Drupal makes an ajax action (like views filter)
  //
  Drupal.behaviors.quiz = {
    attach: function (context, settings) {

      // Do stuff

    }
  };


}(jQuery));