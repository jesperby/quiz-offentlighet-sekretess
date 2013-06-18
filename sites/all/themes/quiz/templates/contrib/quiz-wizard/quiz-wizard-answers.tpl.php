<?php print render($page['back']); ?>

<div id="questions" class="node">
  <?php foreach ($page['questions'] as $question): ?>
    <div <?php print drupal_attributes($question['attributes']); ?>>
      <h2 class="title sub-title"><?php print $question['title']; ?></h2>
      <div class="question-content">

        <div class="legible">
          <h3 class="title sub-title"><?php print t('Scenario'); ?></h3>
          <?php print render($question['scenario']); ?>
        </div>

        <div class="legible">
          <h3 class="title sub-title"><?php print t('Answer'); ?></h3>
          <?php print render($question['answers']); ?>
        </div>

        <div class="legible">
          <h3 class="title sub-title"><?php print t('Comment'); ?></h3>
          <?php print render($question['help_text']); ?>
        </div>

      </div>
    </div>
  <?php endforeach; ?>
</div>