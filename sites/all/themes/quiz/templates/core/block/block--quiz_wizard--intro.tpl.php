<div class="box">
  <?php if ($block->subject) {
    print render($title_prefix); ?>
    <h2 class="title sub-title"><?php print $block->subject ?></h2>
    <?php print render($title_suffix);
  } ?>

  <div class="legible">
    <?php print $content; ?>
  </div>
</div>