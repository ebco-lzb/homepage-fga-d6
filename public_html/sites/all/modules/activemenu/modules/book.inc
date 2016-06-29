<?php

/**
 * Implementation of hook_activemenu().
 */
function book_activemenu($settings) {
  $items = array();
  
  if (! empty($settings['book']['enable'])) {
    $items[$settings['book']['type']]['#block-book-0'] = 'activemenu/book';
  }

  return $items;
}

/**
 * Implementation of hook_activemenu().
 *
 * Note that this menu is only for .inc files in activemenu's directory.
 * Other modules should implement hook_menu() directly.
 */
function book_activemenu_menu() {
  $items = array();

  $items['activemenu/book'] = array(
    'title' => 'activemenu book',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
    'page callback' => 'activemenu_js_book',
  );

  return $items;
}

/**
 * Menu callback. Handle the activemenu for book menus.
 *
 * This callback is registered in activemenu_menu().
 */
function activemenu_js_book() {
  if ($path = activemenu_get_request_path()) {
    // The book menu will use the nid as the key, so we take the second part of the path which will be the nid.
    $arg = explode('/', drupal_get_normal_path(urldecode($path)));
    $menu = '';
    if ($arg[0] == 'node' && is_numeric($arg[1])) {
      $nid = $arg[1];
      $node = node_load($nid);
      if (node_access('view', $node)) {
        $menu = menu_tree_output(menu_tree_all_data($node->book['menu_name'], $node->book));
      }
    }
    print drupal_to_js(array('status' => TRUE, 'content' => $menu));
  }
}

/**
 * Implementation of hook_activemenu_settings().
 */
function book_activemenu_settings($settings) {
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Book'),
  );
  
  $form['enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate AJAX menu for books'),
    '#default_value' => isset($settings['enable']) ? $settings['enable'] : 0,
  );
  
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Menu type'),
    '#options' => activemenu_get_menu_types(),
    '#default_value' => isset($settings['type']) ? $settings['type'] : 'tree',
  );
  
  return $form;
}
