<?php
  $magic_file = 'sites/all/modules/mimedetect/magic.mgc';
  $finfo = finfo_open(FILEINFO_MIME, $magic_file);
  if (!$finfo) {
    echo "Opening fileinfo database failed";
    exit();
  }
?>
