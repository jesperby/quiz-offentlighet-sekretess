(function($) {

  Drupal.behaviors.quizWizard = {
    attach: function(context, settings) {

      // Find the necessary elements.
      $answerInputs = $('#quiz-wizard-wrapper input[name="answer"]').not('.processed');
      $answerSubmit = $('#quiz-wizard-wrapper input[type="submit"]');

      // Bail out if we couldn't find the necessary elements.
      if (!$answerInputs.length || !$answerSubmit.length) {
        return;
      }

      // When changing the value for the answer, trigger the mousedown event for
      // the submit button. This will trigger the AJAX submit for the entire
      // form.
      $answerInputs.change(function() {
        $answerSubmit.mousedown();
      }).addClass('processed');

      // Hide the submit button.
      $answerSubmit.hide();

    }
  };

}(jQuery));
