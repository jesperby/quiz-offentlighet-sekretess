<?php


// ----------------
// GENERAL SETUP OF THEME
// ----------------


/**
 *
 * hook_css_alter()
 * - Used to kill standard stylesheets loaded with Drupal.
 *
 **/
function quiz_css_alter(&$css) {
  unset($css[drupal_get_path('module', 'system') . '/defaults.css']);
  unset($css[drupal_get_path('module', 'system') . '/system.css']);
  unset($css[drupal_get_path('module', 'system') . '/system.menus.css']);
  unset($css[drupal_get_path('module', 'system') . '/system.messages.css']);
  unset($css[drupal_get_path('module', 'system') . '/system.theme.css']);
  unset($css[drupal_get_path('module', 'system') . '/system.admin.css']);
  unset($css[drupal_get_path('module', 'user') . '/user.css']);
  unset($css[drupal_get_path('module', 'comment') . '/comment.css']);
  unset($css[drupal_get_path('module', 'node') . '/node.css']);
  unset($css[drupal_get_path('module', 'field') . '/theme/field.css']);
  unset($css[drupal_get_path('module', 'filter') . '/filter.css']);
}


/**
 *
 * hook_html_head_alter()
 * - Remove generator tag from <head>.
 * - Remove default shortcut icon from head so we can automatically load it from theme instead.
 *
 **/
function quiz_html_head_alter(&$head_elements) {
  unset($head_elements['system_meta_generator']);
  unset($head_elements['metatag_shortlink']);
  foreach ($head_elements as $key => $element) {
    if (isset($element['#attributes']['rel']) && $element['#attributes']['rel'] == 'shortcut icon') {
      unset($head_elements[$key]);
    }
  }
}


/**
 *
 * hook_preprocess_page()
 * - Add classes on correction page
 * - Remove default messages from front page
 *
 **/
function quiz_preprocess_page(&$variables) {

  // Add classes to questions
  if(arg(0) == 'node' && arg(2) == 'answers') {
    $i = 1;
    foreach($variables['page']['content']['system_main']['questions'] as $question) {
      $variables['page']['content']['system_main']['questions'][$i]['attributes']['class'][] = 'box';
      $i++;
    }
  }

  // Unset default messages on front
  if (drupal_is_front_page()) {
    $variables['title'] = '';
    unset($variables['page']['content']['system_main']['default_message']);
  }
  if(arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))) {
    unset($variables['page']['content']['system_main']['term_heading']['#prefix']);
    unset($variables['page']['content']['system_main']['term_heading']['#suffix']);
  }
}


// ----------------
// FORM TWEAKS
// ----------------


/**
 *
 * hook_form()
 * - Remove anonymous div not needed in HTML5.
 *   See here for original:
 *   http://api.drupal.org/api/drupal/includes%21form.inc/function/theme_form/7
 *
 **/
function quiz_form($variables) {
  $element = $variables['element'];
  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = "UTF-8";
  }
  return '<form' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</form>';
}


/**
 *
 * hook_form_alter()
 * - Add classes and wrappers to question form
 *
 **/
function quiz_form_alter(&$form, &$form_state, $form_id) {
  switch($form_id) {
    case 'quiz_wizard_quiz_form':

      // Adding class and removing hidden fields from top
      $form['#attributes']['class'][] = 'box';
      $form['question']['#weight'] = 255;

      // Adding class to title
      $form['title']['#prefix'] = '<h2 class="title sub-title">';
      $form['title']['#suffix'] = '</h2>';

      // Adding wrapper to scenario
      if(isset($form['scenario'])) {
        $form['scenario']['#prefix'] = '<div class="legible">';
        $form['scenario']['#suffix'] = '</div>';
      }
      if(isset($form['help_text'])) {
        $form['help_text']['#prefix'] = '<div class="legible">';
        $form['help_text']['#suffix'] = '</div>';
      }
      //print '<pre>' . print_r($form, 1) . '</pre>'; die;
      //if(!isset($form['actions']['evaluate'])) {
      //  print '<pre>' . print_r($form, 1) . '</pre>'; die;
      //}
      break;
  }
}


/**
 *
 * hook_textarea()
 * - Remove the annoying and ugly Drupal grippie. Totally useless in modern browsers.
 *
 **/
function quiz_textarea($variables) {
  $element = $variables['element'];
  $element['#attributes']['name'] = $element['#name'];
  $element['#attributes']['id'] = $element['#id'];
  $element['#attributes']['cols'] = $element['#cols'];
  $element['#attributes']['rows'] = $element['#rows'];
  _form_set_class($element, array('form-textarea'));

  $wrapper_attributes = array(
    'class' => array('form-textarea-wrapper'),
  );

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    $wrapper_attributes['class'][] = 'resizable';
  }

  $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  $output .= '</div>';
  return $output;
}




// ----------------
// OTHER THINGS
// ----------------


/**
 *
 * theme_item_list()
 * - Overriding in order to remove hard coded div. See...
 *   http://api.drupal.org/api/drupal/includes!theme.inc/function/theme_item_list/7
 *   ... for original
 *
 **/
function quiz_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  $output = '';
  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    $i = 0;
    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      $i++;
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }
      if ($i == 1) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  return $output;
}