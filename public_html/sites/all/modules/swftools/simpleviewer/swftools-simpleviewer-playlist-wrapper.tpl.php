<?php

/**
 * @file
 * Template for the xml wrapper around a SimpleViewer playlist.
 */

/**
 * Prepare xml output for a playlist
 * The markup is placed in a template so that it can be easily over-ridden by the theme system
 * to allow flexibility
 * 
 * This template wraps the xml headers and footers around the xml markup that was produced using
 * the wijering4-playlist-elements template.
 * 
 * Available variables:
 * - $header: An array of data that can be used to inject variables to the markup.
 * - $xml: The markup that describes all the playlist elements.
 * 
 */

// Open xml file
print '<?xml version="1.0" encoding="UTF-8"?>';

$attributes = drupal_attributes($header['xml_vars']);
$attributes = str_replace(array('#', '0x'), '', $attributes);

// Define gallery settings
print '<simpleviewergallery ' . $attributes . '>';

// Output image list
print $xml;

// Close gallery
print '</simpleviewergallery>';

?>
