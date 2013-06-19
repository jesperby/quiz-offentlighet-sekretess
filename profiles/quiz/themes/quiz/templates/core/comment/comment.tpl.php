<div class="<?php print $classes; ?> box"<?php print $attributes; ?>>
  <?php print $picture ?>

  <?php print render($title_prefix); ?>
    <h3 class="title sub-title"<?php print $title_attributes; ?>>
      <?php print $title ?>
    </h3>
  <?php print render($title_suffix); ?>

  <p class="metadata">
    <?php if ($new) { ?>
      <span class="new"><?php print $new; ?></span>
    <?php }
    print $submitted; ?>
  </p>

  <div class="legible comment-content"<?php print $content_attributes; ?>>
    <?php
      hide($content['links']);
      print render($content);
      print render($content['links']);

    if ($signature) { ?>
      <div class="comment-user-signature">
        <?php print $signature ?>
      </div>
    <?php } ?>
  </div>
</div>
