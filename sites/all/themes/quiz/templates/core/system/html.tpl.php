<!DOCTYPE html>
<html class="no-js" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<head>
  <?php print $head; ?>
  <script>(function(H){H.className=H.className.replace(/\bno-js\b/,'js')})(document.documentElement)</script>
  <title><?php print $head_title; ?></title>

  <link rel="icon" type="image/png" href="/<?php print drupal_get_path('theme', $GLOBALS['theme']); ?>/img/icons/favicon.png"> <?php /* Standard favicon */ ?>
  <link rel="apple-touch-icon-precomposed" sizes="144x144" href="/<?php print drupal_get_path('theme', $GLOBALS['theme']); ?>/img/icons/apple-touch-icon-144x144-precomposed.png"> <?php /* For third-generation iPad with high-resolution Retina display */ ?>
  <link rel="apple-touch-icon-precomposed" sizes="114x114" href="/<?php print drupal_get_path('theme', $GLOBALS['theme']); ?>/img/icons/apple-touch-icon-114x114-precomposed.png"> <?php /* For iPhone with high-resolution Retina display */ ?>
  <link rel="apple-touch-icon-precomposed" sizes="72x72" href="/<?php print drupal_get_path('theme', $GLOBALS['theme']); ?>/img/icons/apple-touch-icon-72x72-precomposed.png"> <?php /* For first- and second-generation iPad */ ?>
  <link rel="apple-touch-icon-precomposed" href="/<?php print drupal_get_path('theme', $GLOBALS['theme']); ?>/img/icons/apple-touch-icon-precomposed.png"> <?php /* For non-Retina iPhone, iPod Touch, and Android 2.1+ devices */ ?>

  <?php print $styles; ?>
</head>

<body class="<?php print $classes; ?>">
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
  <?php print $scripts; ?>
</body>
</html>
