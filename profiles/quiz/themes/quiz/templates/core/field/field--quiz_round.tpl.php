<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden) { ?>
    <h2 class="title sub-title"><?php print $label; ?></h2>
  <?php }

  foreach ($items as $delta => $item) {
    print render($item);
  } ?>
</div>