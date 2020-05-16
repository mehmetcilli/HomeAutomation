<?php
$val1 = $_POST['val1']; // A filtrer
$val2 = $_POST['val2']; // A filtrer

 
$fichierouvert = fopen ('texte.txt', 'w'); // Mode w = fichier écrasé !!!
if (!fwrite($fichierouvert, $val1 . PHP_EOL . $val2 . PHP_EOL)) {
  die("Impossible d'écrire dans le fichier 'config.txt'");
}
fclose ($fichierouvert);
echo "Paramètres enregistrés";
?>