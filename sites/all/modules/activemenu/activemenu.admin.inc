<?php
  
/**
 * Menu callback: options for activemenu.
 */
function activemenu_admin() {
  $form = array(
    '#theme' => 'system_settings_form',
    '#submit' => array(
      'system_settings_form_submit',
      'menu_rebuild',
      'drupal_rebuild_theme_registry',
    ),
  );
  
  $form['activemenu_settings'] = array(
    '#tree' => TRUE,
  );
  
  $activemenu_settings = variable_get('activemenu_settings', array());
  
  foreach (module_implements('activemenu_settings') as $module) {
    $settings = isset($activemenu_settings[$module]) ? $activemenu_settings[$module] : array();
    $form['activemenu_settings'][$module] = call_user_func($module .'_activemenu_settings', $settings);
  }
  
  $form['theme_registry'] = array(
    '#type' => 'fieldset',
    '#title' => t('Alter theme registry'),
    '#description' => t('If you encounter some issues with another module which modifies the menu items before rendering (e.g. menu_firstchild module), you may enable this feature. Please notice that the theme function which renders a menu_item_link element will no more be %old but %new. You may need to update some of your theme code if you used to override the original theming function.', array('%old' => 'theme_menu_item_link()', '%new' => 'theme_activemenu_menu_item_link()')),
  );
  
  $form['theme_registry']['activemenu_theme_registry_alter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use replacement function for menu_item_link theme'),
    '#default_value' => variable_get('activemenu_theme_registry_alter', 0),
  );
  
  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );
  $form['buttons']['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults') );

  return $form;
}