<div<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
    <nav class="navigation">
    <?=drupal_render(menu_tree_output(menu_build_tree('main-menu')))?>
    </nav>
  </div>
</div>

<?
// This once was:
/*
<div<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
    <?php if ($main_menu || $secondary_menu): ?>
    <nav class="navigation">
      <?php print theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => array('links', 'inline', 'clearfix', 'main-menu')), 'heading' => array('text' => t('Main menu'),'level' => 'h2','class' => array('element-invisible')))); ?>
      <?php print theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary-menu', 'class' => array('links', 'inline', 'clearfix', 'secondary-menu')), 'heading' => array('text' => t('Secondary menu'),'level' => 'h2','class' => array('element-invisible')))); ?
    </nav>
    <?php endif; ?>
  </div>
</div>

*/
?>