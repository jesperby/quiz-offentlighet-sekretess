<div class="header center">
  <?php
  //
  // Logo and slogan. Usually placed in header.
  //
  if ($site_name || $site_slogan) {
    if ($site_name) {
      if ($title) {
        $tagname = 'div';
      } else {
        $tagname = 'h1';
      } ?>
      <<?php print $tagname; ?> class="site-name">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
          <?php if($logo) { ?>
            <img src="<?php print $logo ?>" alt="<?php print $site_name ?>" />
          <?php } else {
            print $site_name;
          } ?>
        </a>
      </<?php print $tagname; ?>>
    <?php } ?>

    <?php if($site_slogan) { ?>
      <p class="site-slogan"><?php print $site_slogan; ?></p>
    <?php }
  }

  //
  // Main navigation region. Place menus here.
  //
  if ($page['main_navigation']) { ?>
    <div class="nav">
      <a href="#" class="display-mobile-menu">Menu</a>
      <?php print render($page['main_navigation']); ?>
    </div>
  <?php } ?>
</div>


<?php
//
// System messages. Should be placed prominently.
//
if($messages) { ?>
  <div class="system-messages center">
    <?php print $messages; ?>
  </div>
<?php }


//
// Contextual actions given by Drupal - tabs and actions.
// If you want to use these, ensure they look nice and are well
// placed. They'll only be visible to logged in users.
// If not, just delete them.
//
if (!empty($tabs['#primary']) || $action_links) { ?>
  <div class="system-links center">
    <?php if (!empty($tabs['#primary'])) { ?>
      <div class="system-tabs">
        <?php print render($tabs); ?>
      </div>
    <?php } ?>
    <?php if ($action_links) { ?>
      <ul class="action-links">
        <?php print render($action_links); ?>
      </ul>
    <?php } ?>
  </div>
<?php }?>


<div class="center main-content">
  <?php
  //
  // Page title. Visible when viewing individual nodes
  // and lists (like those created by views or taxonomy).
  //
  if ($title) {
    print render($title_prefix); ?>
    <h1 class="title" id="page-title">
      <?php print $title; ?>
    </h1>
    <?php print render($title_suffix);
  }

  //
  // Main page content
  //
  print render($page['content']); ?>
</div>