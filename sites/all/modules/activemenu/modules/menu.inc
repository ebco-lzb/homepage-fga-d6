<?php

function menu_activemenu($settings) {
  $items = array();
  $menus = menu_get_menus();
  // The Navigation menu is handled by the user module.
  unset($menus['navigation']);
  foreach (array_keys($menus) as $name) {
    if (! empty($settings['menu'][$name]['enable'])) {
      $items[$settings['menu'][$name]['type']]['#block-menu-'. $name] = 'activemenu/menu';
    }
  }
  return $items;
}

/**
 * Implementation of hook_activemenu_settings().
 */
function menu_activemenu_settings($settings) {
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Menus'),
  );
  
  $menus = menu_get_menus();
  // The Navigation menu is handled by the user module.
  unset($menus['navigation']);
  
  foreach ($menus as $name => $title) {
    $form[$name] = array(
      '#type' => 'fieldset',
      '#title' => $title,
    );
    
    $form[$name]['enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Activate AJAX menu for %menu', array('%menu' => $title)),
      '#default_value' => isset($settings[$name]['enable']) ? $settings[$name]['enable'] : 0,
    );
    
    $form[$name]['type'] = array(
      '#type' => 'select',
      '#title' => t('Menu type'),
      '#options' => activemenu_get_menu_types(),
      '#default_value' => isset($settings[$name]['type']) ? $settings[$name]['type'] : 'tree',
    );
  }
  
  return $form;
}