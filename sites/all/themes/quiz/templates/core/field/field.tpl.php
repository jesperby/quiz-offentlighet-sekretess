<?php if (!$label_hidden) {
  print $label . ':';
}

foreach ($items as $delta => $item) {
  print render($item);
}