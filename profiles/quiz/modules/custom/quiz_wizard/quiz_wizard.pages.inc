<?php
/**
 * Main pages for the Quiz form module.
 */

/**
 * Main form function for the quiz.
 *
 * This will control the entire flow for the quiz, by deciding which content to
 * show depending on the step.
 */
function quiz_wizard_quiz_form($form, &$form_state) {
  // Set the initial step to 1, if the step hasn't been set.
  $form_state['step'] = isset($form_state['step']) ? $form_state['step'] : 1;

  // Set the number of questions for this quiz.
  $form_state['questions'] = isset($form_state['questions']) ? $form_state['questions'] : quiz_wizard_get_num_questions_configured();

  // If we have stored values for this step, it means that the user has answered
  // this question. In that case, we'll display the correct answer for this
  // question. Otherwise, we'll simply display the question form which allows
  // the user to answer it.
  if (isset($form_state['storage'][$form_state['step']])) {
    // Load the question node.
    $question = node_load($form_state['storage'][$form_state['step']]['nid']);

    // Add a title and a class to the form, which indicates whether or not the
    // answer was correct.
    $title = $form_state['storage'][$form_state['step']]['correct'] ? t("Congratulations, you're correct!") : t("Oops, your answer was wrong.");
    $form['title'] = array(
      '#prefix' => '<h2>',
      '#suffix' => '</h2>',
      '#markup' => $title,
    );
    $form['#attributes']['class'][] = $form_state['storage'][$form_state['step']]['correct'] ? 'correct' : 'wrong';

    // Display the help text that corresponds to the answer that the user
    // supplied.
    $help_text = field_get_items('node', $question, 'field_case_help_texts');
    $form['help_text'] = field_view_value('node', $question, 'field_case_help_texts', $help_text[$form_state['storage'][$form_state['step']]['answer']], 'answer');

    // If there are more questions left, add a button that loads the next
    // question. Otherwise, we'll add a button that finishes the quiz, by
    // creating a quiz round node and redirects the user to that node.
    if ($form_state['step'] < $form_state['questions']) {
      // Button for next question.
      $form['actions'] = array('#type' => 'actions');
      $form['actions']['next'] = array(
        '#type' => 'submit',
        '#value' => t('Next question'),
        '#submit' => array('quiz_wizard_quiz_form_next_submit'),
        '#ajax' => array(
  				'wrapper' => 'quiz-wizard-wrapper',
  				'callback' => 'quiz_wizard_quiz_form_ajax_callback',
  			),
      );
    }
    else {
      // Button that completes the quiz.
      $form['actions'] = array('#type' => 'actions');
      $form['actions']['review'] = array(
        '#type' => 'submit',
        '#value' => t('Review result'),
        '#submit' => array('quiz_wizard_quiz_form_review_submit'),
      );
    }
  }
  else {
    // Determine which question the form should be based on. If the user already
    // submitted the form, the question will be stored in the
    // $form_state['input'] array. Otherwise, we'll load a random question.
    if (isset($form_state['input']['question'])) {
      // Load the stored question.
      $question = node_load($form_state['input']['question']);
    }
    else {
      // Build an array of the questions that already has been answered.
      $answered_questions = array();
      if (isset($form_state['storage'])) {
        foreach ($form_state['storage'] as $step => $question) {
          $answered_questions[] = $question['nid'];
        }
      }

      // Load a random question, excluding the ones that has been answered.
      $question = quiz_wizard_get_question($answered_questions);
    }

    // Store the question nid in a hidden variable.
    $form['question'] = array(
      '#type' => 'hidden',
      '#value' => $question->nid,
    );

    // Create the title for this question.
    $args = array(
      '@current' => $form_state['step'],
      '@total' => $form_state['questions'],
      '@question' => $question->title,
    );
    $form['title'] = array(
      '#prefix' => '<h2>',
      '#suffix' => '</h2>',
      '#markup' => t('Question @current/@total: @question', $args),
    );

    // Add the scenario from this question. This will be a renderable array
    // based on the configuration for the default view mode. We'll remove the
    // weight though, in order to keep the flow in the way that we want it.
    $form['scenario'] = field_view_field('node', $question, 'field_scenario', 'question');
    unset($form['scenario']['#weight']);

    // Create the input for the answer. The options will be based on the ones
    // that has been stored for the question, so we'll create the array based on
    // the values for that field.
    $options = array();
    foreach (field_get_items('node', $question, 'field_answers') as $answer) {
      $options[] = $answer['safe_value'];
    }
    $form['answer'] = array(
      '#type' => 'radios',
      '#title' => t('Answer'),
      '#options' => $options,
      '#required' => TRUE,
      '#attributes' => array('class' => array('quiz-answer-element')),
    );

    // If the form should get auto submitted, attach the required JS that will
    // add this behavior.
    if (quiz_wizard_get_auto_submit()) {
      $form['answer']['#attached'] = array(
        'js' => array(drupal_get_path('module', 'quiz_wizard') . '/quiz_wizard.js'),
      );
    }

    // Add a submit button that evaluates and stores the answer.
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['evaluate'] = array(
      '#type' => 'submit',
      '#value' => t('Evaluate'),
      '#submit' => array('quiz_wizard_quiz_form_evaluate_submit'),
      '#ajax' => array(
				'wrapper' => 'quiz-wizard-wrapper',
				'callback' => 'quiz_wizard_quiz_form_ajax_callback',
			),
    );
  }

  // Wrap the entire form in a div. This allows us to specify which wrapper to
  // replace when using AJAX.
  $form['#prefix'] = '<div id="quiz-wizard-wrapper">';
  $form['#suffix'] = '</div>';

  return $form;
}

/**
 * Form submit for the evaluate button.
 *
 * This will evaluate the answer, and store the necessary information in the
 * $form_state array.
 */
function quiz_wizard_quiz_form_evaluate_submit($form, &$form_state) {
  // Load the full question node, and get the correct answer.
  $question = node_load($form_state['values']['question']);
  $correct_answer = field_get_items('node', $question, 'field_correct_answer');

  // Add the supplied information to the storage array. Save values for the
  // question nid, the supplied answer and a bool indicating whether or the the
  // answer was correct.
  $form_state['storage'][$form_state['step']] = array(
    'nid' => $form_state['values']['question'],
    'answer' => $form_state['values']['answer'],
    'correct' => $form_state['values']['answer'] == $correct_answer[0]['value'],
  );

  // Always rebuild the form when using multi-step forms.
  $form_state['rebuild'] = TRUE;
}

/**
 * Form submit for the next question button.
 *
 * This will simply increase the step by 1, which will display the next question
 * to the user.
 */
function quiz_wizard_quiz_form_next_submit($form, &$form_state) {
  // Increase the step.
  $form_state['step']++;

  // Always rebuild the form when using multi-step forms.
  $form_state['rebuild'] = TRUE;
}

/**
 * Form submit for the review button.
 *
 * This is the last submit function for the multi-step form. The purpose of this
 * funciton is to create the quiz round node based on the question evaluations.
 */
function quiz_wizard_quiz_form_review_submit($form, &$form_state) {
  // Create the initial values required by the node.
  $values = array(
    'type' => 'quiz_round',
    'field_number_of_questions' => array(
      LANGUAGE_NONE => array(
        array('value' => $form_state['questions']),
      ),
    ),
  );

  // Process each answer.
  $correct_answers = 0;
  foreach ($form_state['storage'] as $question => $result) {
    // Add the nid for this question to the appropriate field.
    $values['field_q' . $question . '_nid'] = array(
      LANGUAGE_NONE => array(
        array('value' => $result['nid']),
      ),
    );

    // Add the supplied answer to the appropriate field.
    $values['field_q' . $question . '_a'] = array(
      LANGUAGE_NONE => array(
        array('value' => $result['answer']),
      ),
    );

    // Increase the number of correct answers if this answer was correct.
    $correct_answers = $result['correct'] ? $correct_answers + 1 : $correct_answers;
  }

  // Add the number of correct answers to the values.
  $values['field_number_of_correct_answers'] = array(
    LANGUAGE_NONE => array(
      array('value' => $correct_answers),
    ),
  );

  // Calculate the achieved rate, and set the title of the node to the
  // configured pass or fail title.
  $achivied_rate = ($correct_answers / $form_state['questions']) * 100;
  $values['title'] = $achivied_rate >= quiz_wizard_get_pass_rate() ? quiz_wizard_get_pass_title() : quiz_wizard_get_fail_title();

  // Add the pass or fail text depending on the achieved rate.
  $values['field_score_text'] = array(
    LANGUAGE_NONE => array($achivied_rate >= quiz_wizard_get_pass_rate() ? quiz_wizard_get_pass_text() : quiz_wizard_get_fail_text())
  );

  // Create the node, and redirect the user to the node page.
  $node = entity_create('node', $values);
  node_save($node);
  drupal_goto('node/' . $node->nid);
}

/**
 * AJAX callback used by the multi-step quiz form.
 *
 * This will simply return the entire form, which will render it automatically.
 */
function quiz_wizard_quiz_form_ajax_callback($form, &$form_state) {
  return $form;
}

/**
 * Page callback for the answers page.
 *
 * @param object $node
 *   The quiz round node that we should base the answers on.
 *
 * @return array
 *   A renderable page array used by the quiz_wizard_answers theme implementation.
 */
function quiz_wizard_quiz_answers($node) {
  // Wrap the entire node object.
  $wrapper = entity_metadata_wrapper('node', $node);

  // Setup the initial page structure.
  $page = array(
    '#theme' => 'quiz_wizard_answers',
    'back' => array(
      '#theme' => 'link',
      '#text' => t('Back to the result'),
      '#path' => 'node/' . $node->nid,
      '#options' => array(
        'attributes' => array(),
      ),
    ),
    'questions' => array(),
  );

  // Process each question, based on the number of questions that has been
  // answered.
  for ($i = 1; $i <= $wrapper->field_number_of_questions->value(); $i++) {
    // Get the question nid and answer based on the current question count.
    $question_nid = $wrapper->{'field_q' . $i . '_nid'}->value();
    $supplied_answer = $wrapper->{'field_q' . $i . '_a'}->value();

    // Load the question node and the correct answer.
    $question = node_load($question_nid);
    $question_wrapper = entity_metadata_wrapper('node', $question);
    $correct_answer = $question_wrapper->field_correct_answer->value();

    // Add a class that indicates whether or not the user supplied the correct
    // answer.
    $page['questions'][$i]['attributes']['class'] = array($supplied_answer == $correct_answer ? 'correct' : 'wrong');

    // Add the question title and scenario to the page.
    $page['questions'][$i]['title'] = $question->title;
    $page['questions'][$i]['scenario'] = field_view_field('node', $question, 'field_scenario', 'answer');

    // Create the basic structure for an item list, which we will add items to.
    $page['questions'][$i]['answers'] = array(
      '#theme' => 'item_list',
      '#items' => array(),
      '#type' => 'ol',
    );

    // Add each answer to the item list, and add a class that indicates if this
    // is the correct answer, or if the user answered the wrong question.
    foreach ($question_wrapper->field_answers->value() as $key => $value) {
      $page['questions'][$i]['answers']['#items'][] = array(
        'data' => $value,
        'class' => array($correct_answer == $key ? 'correct' : ($supplied_answer == $key ? 'wrong' : '')),
      );
    }

    // Add the help text to the page, based on the supplied answer.
    $help_text = field_get_items('node', $question, 'field_case_help_texts');
    $page['questions'][$i]['help_text'] = field_view_value('node', $question, 'field_case_help_texts', $help_text[$supplied_answer], 'answer');
  }

  // Return the renderable array.
  return $page;
}
