<div class="stat-block stat-block-participants">
  <?php if ($block->subject) {
    print render($title_prefix); ?>
    <h2 class="title sub-title"><?php print $block->subject ?></h2>
    <?php print render($title_suffix);
  } ?>

  <p class="stat"><?php print $content; ?></p>
</div>