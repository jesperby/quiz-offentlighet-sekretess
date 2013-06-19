<?php

// Remove things from $content so we can render them separately
hide($content['comments']);
hide($content['links']); ?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php // Only display node title if it's not a single node
  if (!$page) {
    print render($title_prefix); ?>
    <h2 class="title sub-title" <?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php print render($title_suffix);
  }

  // Metadata. Post author and timestamp.
  if ($display_submitted) { ?>
    <p class="metadata"><?php print $submitted; ?></p>
  <?php } ?>

  <div class="legible">
    <?php
      print render($content);
      print render($content['links']);
    ?>
  </div>

  <?php print render($content['comments']); ?>

</div>