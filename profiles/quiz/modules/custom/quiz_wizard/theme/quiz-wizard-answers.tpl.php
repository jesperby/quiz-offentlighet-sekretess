<?php print render($page['back']); ?>

<div id="questions">
  <?php foreach ($page['questions'] as $question): ?>
    <div <?php print drupal_attributes($question['attributes']); ?>>
      <h2><?php print $question['title']; ?></h2>
      <div class="question-content">
        <h3><?php print t('Scenario'); ?></h3>
        <?php print render($question['scenario']); ?>
        <h3><?php print t('Answer'); ?></h3>
        <?php print render($question['answers']); ?>
        <h3><?php print t('Comment'); ?></h3>
        <?php print render($question['help_text']); ?>
      </div>
    </div>
  <?php endforeach; ?>
</div>
